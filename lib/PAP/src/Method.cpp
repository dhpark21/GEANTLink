/*
    Copyright 2015-2016 Amebis
    Copyright 2016 G�ANT

    This file is part of G�ANTLink.

    G�ANTLink is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    G�ANTLink is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with G�ANTLink. If not, see <http://www.gnu.org/licenses/>.
*/

#include "StdAfx.h"

using namespace std;
using namespace winstd;


//////////////////////////////////////////////////////////////////////
// eap::method_pap::packet
//////////////////////////////////////////////////////////////////////

eap::method_pap::packet::packet() :
    m_code((EapCode)0),
    m_id(0)
{
}


eap::method_pap::packet::packet(_In_ const packet &other) :
    m_code(other.m_code),
    m_id  (other.m_id  ),
    m_data(other.m_data)
{
}


eap::method_pap::packet::packet(_Inout_ packet &&other) :
    m_code(std::move(other.m_code)),
    m_id  (std::move(other.m_id  )),
    m_data(std::move(other.m_data))
{
}


eap::method_pap::packet& eap::method_pap::packet::operator=(_In_ const packet &other)
{
    if (this != std::addressof(other)) {
        m_code = other.m_code;
        m_id   = other.m_id  ;
        m_data = other.m_data;
    }

    return *this;
}


eap::method_pap::packet& eap::method_pap::packet::operator=(_Inout_ packet &&other)
{
    if (this != std::addressof(other)) {
        m_code = std::move(other.m_code);
        m_id   = std::move(other.m_id  );
        m_data = std::move(other.m_data);
    }

    return *this;
}


void eap::method_pap::packet::clear()
{
    m_code = (EapCode)0;
    m_id   = 0;
    m_data.clear();
}


//////////////////////////////////////////////////////////////////////
// eap::method_pap
//////////////////////////////////////////////////////////////////////

eap::method_pap::method_pap(_In_ module &module, _In_ config_method_pap &cfg, _In_ credentials_pap &cred) :
    m_cred(cred),
    m_phase(phase_unknown),
    m_phase_prev(phase_unknown),
    method(module, cfg, cred)
{
}


eap::method_pap::method_pap(_Inout_ method_pap &&other) :
    m_cred      (          other.m_cred       ),
    m_packet_res(std::move(other.m_packet_res)),
    m_phase     (std::move(other.m_phase     )),
    m_phase_prev(std::move(other.m_phase_prev)),
    method      (std::move(other             ))
{
}


eap::method_pap& eap::method_pap::operator=(_Inout_ method_pap &&other)
{
    if (this != std::addressof(other)) {
        assert(std::addressof(m_cred) == std::addressof(other.m_cred)); // Move method with same credentials only!
        (method&)*this = std::move(other             );
        m_packet_res   = std::move(other.m_packet_res);
        m_phase        = std::move(other.m_phase     );
        m_phase_prev   = std::move(other.m_phase_prev);
    }

    return *this;
}


void eap::method_pap::process_request_packet(
    _In_bytecount_(dwReceivedPacketSize) const EapPacket           *pReceivedPacket,
    _In_                                       DWORD               dwReceivedPacketSize,
    _Inout_                                    EapPeerMethodOutput *pEapOutput)
{
    assert(pReceivedPacket && dwReceivedPacketSize >= 4);
    assert(pEapOutput);

    m_module.log_event(&EAPMETHOD_PACKET_RECV, event_data((unsigned int)eap_type_pap), event_data((unsigned int)dwReceivedPacketSize - 4), event_data::blank);

    if (pReceivedPacket->Id == 0) {
        m_module.log_event(&EAPMETHOD_METHOD_HANDSHAKE_START2, event_data((unsigned int)eap_type_pap), event_data::blank);
        m_phase = phase_init;
    }

    m_phase_prev = m_phase;
    switch (m_phase) {
    case phase_init: {
        // Convert username and password to UTF-8.
        sanitizing_string identity_utf8, password_utf8;
        WideCharToMultiByte(CP_UTF8, 0, m_cred.m_identity.c_str(), (int)m_cred.m_identity.length(), identity_utf8, NULL, NULL);
        WideCharToMultiByte(CP_UTF8, 0, m_cred.m_password.c_str(), (int)m_cred.m_password.length(), password_utf8, NULL, NULL);

        // PAP passwords must be padded to 16B boundary according to RFC 5281. Will not add random extra padding here, as length obfuscation should be done by outer transport layers.
        size_t padding_password_ex = (16 - password_utf8.length()) % 16;
        password_utf8.append(padding_password_ex, 0);

        size_t
            size_identity    = identity_utf8.length(),
            size_password    = password_utf8.length(),
            padding_identity = (4 - size_identity         ) % 4,
            padding_password = (4 - password_utf8.length()) % 4,
            size_identity_outer,
            size_password_outer;

        m_packet_res.m_code = EapCodeResponse;
        m_packet_res.m_id    = pReceivedPacket->Id;
        m_packet_res.m_data.clear();
        m_packet_res.m_data.reserve(
            (size_identity_outer = 
            4                + // Diameter AVP Code
            4                + // Diameter AVP Flags & Length
            size_identity)   + // Identity
            padding_identity + // Identity padding
            (size_password_outer = 
            4                + // Diameter AVP Code
            4                + // Diameter AVP Flags & Length
            size_password)   + // Password
            padding_password); // Password padding

        // Diameter AVP Code User-Name (0x00000001)
        m_packet_res.m_data.push_back(0x00);
        m_packet_res.m_data.push_back(0x00);
        m_packet_res.m_data.push_back(0x00);
        m_packet_res.m_data.push_back(0x01);

        // Diameter AVP Flags & Length
        unsigned int identity_hdr = htonl((diameter_avp_flag_mandatory << 24) | (unsigned int)size_identity_outer);
        m_packet_res.m_data.insert(m_packet_res.m_data.end(), (unsigned char*)&identity_hdr, (unsigned char*)(&identity_hdr + 1));

        // Identity
        m_packet_res.m_data.insert(m_packet_res.m_data.end(), identity_utf8.begin(), identity_utf8.end());
        m_packet_res.m_data.insert(m_packet_res.m_data.end(), padding_identity, 0);

        // Diameter AVP Code User-Password (0x00000002)
        m_packet_res.m_data.push_back(0x00);
        m_packet_res.m_data.push_back(0x00);
        m_packet_res.m_data.push_back(0x00);
        m_packet_res.m_data.push_back(0x02);

        // Diameter AVP Flags & Length
        unsigned int password_hdr = htonl((diameter_avp_flag_mandatory << 24) | (unsigned int)size_password_outer);
        m_packet_res.m_data.insert(m_packet_res.m_data.end(), (unsigned char*)&password_hdr, (unsigned char*)(&password_hdr + 1));

        // Password
        m_packet_res.m_data.insert(m_packet_res.m_data.end(), password_utf8.begin(), password_utf8.end());
        m_packet_res.m_data.insert(m_packet_res.m_data.end(), padding_password, 0);

        m_phase = phase_finished;
        break;
    }

    case phase_finished:
        break;
    }

    pEapOutput->fAllowNotifications = TRUE;
    pEapOutput->action = EapPeerMethodResponseActionSend;
}


void eap::method_pap::get_response_packet(
    _Inout_bytecap_(*dwSendPacketSize) EapPacket *pSendPacket,
    _Inout_                            DWORD     *pdwSendPacketSize)
{
    assert(pdwSendPacketSize);
    assert(pSendPacket);

    unsigned int
        size_data   = (unsigned int)m_packet_res.m_data.size(),
        size_packet = size_data + 4;
    unsigned short size_packet_limit = (unsigned short)std::min<unsigned int>(*pdwSendPacketSize, USHRT_MAX);

    // Not fragmented.
    if (size_packet <= size_packet_limit) {
        // No need to fragment the packet.
        m_module.log_event(&EAPMETHOD_PACKET_SEND, event_data((unsigned int)eap_type_pap), event_data((unsigned int)size_data), event_data::blank);
    } else {
        // But it should be fragmented.
        throw com_runtime_error(TYPE_E_SIZETOOBIG, __FUNCTION__ " PAP message exceeds 64kB.");
    }

    pSendPacket->Code = (BYTE)m_packet_res.m_code;
    pSendPacket->Id   = m_packet_res.m_id;
    *(unsigned short*)pSendPacket->Length = htons((unsigned short)size_packet);
    memcpy(pSendPacket->Data, m_packet_res.m_data.data(), size_data);
    m_packet_res.m_data.erase(m_packet_res.m_data.begin(), m_packet_res.m_data.begin() + size_data);
    *pdwSendPacketSize = size_packet;
}


void eap::method_pap::get_result(
    _In_    EapPeerMethodResultReason reason,
    _Inout_ EapPeerMethodResult       *ppResult)
{
    assert(ppResult);

    switch (reason) {
    case EapPeerMethodResultSuccess: {
        m_module.log_event(&EAPMETHOD_METHOD_SUCCESS, event_data((unsigned int)eap_type_pap), event_data::blank);
        m_cfg.m_auth_failed = false;

        ppResult->fIsSuccess = TRUE;
        ppResult->dwFailureReasonCode = ERROR_SUCCESS;

        break;
    }

    case EapPeerMethodResultFailure:
        m_module.log_event(
            m_phase_prev < phase_finished ? &EAPMETHOD_METHOD_FAILURE_INIT : &EAPMETHOD_METHOD_FAILURE,
            event_data((unsigned int)eap_type_pap), event_data::blank);

        // Mark credentials as failed, so GUI can re-prompt user.
        // But be careful: do so only after credentials were actually tried.
        m_cfg.m_auth_failed = m_phase == phase_finished;

        // Do not report failure to EapHost, as it will not save updated configuration then. But we need it to save it, to alert user on next connection attempt.
        // EapHost is well aware of the failed condition.
        //ppResult->fIsSuccess = FALSE;
        //ppResult->dwFailureReasonCode = EAP_E_AUTHENTICATION_FAILED;

        break;

    default:
        throw win_runtime_error(ERROR_NOT_SUPPORTED, __FUNCTION__ " Not supported.");
    }

    // Always ask EAP host to save the connection data.
    ppResult->fSaveConnectionData = TRUE;
}