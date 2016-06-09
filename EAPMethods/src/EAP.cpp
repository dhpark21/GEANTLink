﻿/*
    Copyright 2015-2016 Amebis
    Copyright 2016 GÉANT

    This file is part of GÉANTLink.

    GÉANTLink is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GÉANTLink is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GÉANTLink. If not, see <http://www.gnu.org/licenses/>.
*/

#include <StdAfx.h>

using namespace std;
using namespace winstd;


//////////////////////////////////////////////////////////////////////
// eap::session
//////////////////////////////////////////////////////////////////////

eap::session::session()
{
}


eap::session::~session()
{
}


DWORD eap::session::begin(
    _In_                                   DWORD         dwFlags,
    _In_                             const EapAttributes *pAttributeArray,
    _In_                                   HANDLE        hTokenImpersonateUser,
    _In_                                   DWORD         dwConnectionDataSize,
    _In_count_(dwConnectionDataSize) const BYTE          *pConnectionData,
    _In_                                   DWORD         dwUserDataSize,
    _In_count_(dwUserDataSize)       const BYTE          *pUserData,
    _In_                                   DWORD         dwMaxSendPacketSize,
    _Out_                                  EAP_ERROR     **ppEapError)
{
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(pAttributeArray);
    UNREFERENCED_PARAMETER(hTokenImpersonateUser);
    UNREFERENCED_PARAMETER(dwConnectionDataSize);
    UNREFERENCED_PARAMETER(pConnectionData);
    UNREFERENCED_PARAMETER(dwUserDataSize);
    UNREFERENCED_PARAMETER(pUserData);
    UNREFERENCED_PARAMETER(dwMaxSendPacketSize);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_SUCCESS;
}


DWORD eap::session::end(_Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_SUCCESS;
}


DWORD eap::session::process_request_packet(
    _In_                                       DWORD               dwReceivedPacketSize,
    _In_bytecount_(dwReceivedPacketSize) const EapPacket           *pReceivedPacket,
    _Out_                                      EapPeerMethodOutput *pEapOutput,
    _Out_                                      EAP_ERROR           **ppEapError)
{
    UNREFERENCED_PARAMETER(dwReceivedPacketSize);
    UNREFERENCED_PARAMETER(pReceivedPacket);
    UNREFERENCED_PARAMETER(pEapOutput);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::get_response_packet(
    _Inout_                            DWORD              *pdwSendPacketSize,
    _Inout_bytecap_(*dwSendPacketSize) EapPacket          *pSendPacket,
    _Out_                              EAP_ERROR          **ppEapError)
{
    UNREFERENCED_PARAMETER(pdwSendPacketSize);
    UNREFERENCED_PARAMETER(pSendPacket);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::get_result(_In_ EapPeerMethodResultReason reason, _Out_ EapPeerMethodResult *ppResult, _Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(reason);
    UNREFERENCED_PARAMETER(ppResult);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::get_ui_context(
    _Out_ DWORD     *pdwUIContextDataSize,
    _Out_ BYTE      **ppUIContextData,
    _Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(pdwUIContextDataSize);
    UNREFERENCED_PARAMETER(ppUIContextData);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::set_ui_context(
    _In_                                  DWORD               dwUIContextDataSize,
    _In_count_(dwUIContextDataSize) const BYTE                *pUIContextData,
    _In_                            const EapPeerMethodOutput *pEapOutput,
    _Out_                                 EAP_ERROR           **ppEapError)
{
    UNREFERENCED_PARAMETER(dwUIContextDataSize);
    UNREFERENCED_PARAMETER(pUIContextData);
    UNREFERENCED_PARAMETER(pEapOutput);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::get_response_attributes(_Out_ EapAttributes *pAttribs, _Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(pAttribs);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


DWORD eap::session::set_response_attributes(const _In_ EapAttributes *pAttribs, _Out_ EapPeerMethodOutput *pEapOutput, _Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(pAttribs);
    UNREFERENCED_PARAMETER(pEapOutput);
    UNREFERENCED_PARAMETER(ppEapError);

    return ERROR_NOT_SUPPORTED;
}


//////////////////////////////////////////////////////////////////////
// eap::config
//////////////////////////////////////////////////////////////////////

eap::config::config(_In_ module &mod) :
    m_module(mod)
{
}


eap::config::config(_In_ const config &other) :
    m_module(other.m_module)
{
}


eap::config::config(_Inout_ config &&other) :
    m_module(other.m_module)
{
}


eap::config::~config()
{
}


eap::config& eap::config::operator=(_In_ const config &other)
{
    UNREFERENCED_PARAMETER(other);
    assert(&m_module == &other.m_module); // Copy configuration within same module only!
    return *this;
}


eap::config& eap::config::operator=(_Inout_ config &&other)
{
    UNREFERENCED_PARAMETER(other);
    assert(&m_module == &other.m_module); // Copy configuration within same module only!
    return *this;
}


//////////////////////////////////////////////////////////////////////
// eap::config_method
//////////////////////////////////////////////////////////////////////

eap::config_method::config_method(_In_ module &mod) :
    m_allow_save(true),
    config(mod)
{
}


eap::config_method::config_method(_In_ const config_method &other) :
    m_allow_save(other.m_allow_save),
    m_anonymous_identity(other.m_anonymous_identity),
    config(other)
{
}


eap::config_method::config_method(_Inout_ config_method &&other) :
    m_allow_save(std::move(other.m_allow_save)),
    m_anonymous_identity(std::move(other.m_anonymous_identity)),
    config(std::move(other))
{
}


eap::config_method& eap::config_method::operator=(_In_ const config_method &other)
{
    if (this != &other) {
        (config&)*this       = other;
        m_allow_save         = other.m_allow_save;
        m_anonymous_identity = other.m_anonymous_identity;
    }

    return *this;
}


eap::config_method& eap::config_method::operator=(_Inout_ config_method &&other)
{
    if (this != &other) {
        (config&&)*this      = std::move(other);
        m_allow_save         = std::move(other.m_allow_save);
        m_anonymous_identity = std::move(other.m_anonymous_identity);
    }

    return *this;
}


DWORD eap::config_method::save(_In_ IXMLDOMDocument *pDoc, _In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError) const
{
    const bstr bstrNamespace(L"urn:ietf:params:xml:ns:yang:ietf-eap-metadata");
    DWORD dwResult;

    // <ClientSideCredential>
    com_obj<IXMLDOMElement> pXmlElClientSideCredential;
    if ((dwResult = eapxml::create_element(pDoc, pConfigRoot, bstr(L"eap-metadata:ClientSideCredential"), bstr(L"ClientSideCredential"), bstrNamespace, &pXmlElClientSideCredential)) != ERROR_SUCCESS) {
        *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <ClientSideCredential> element."), NULL);
        return dwResult;
    }

    // <ClientSideCredential>/<allow-save>
    if ((dwResult = eapxml::put_element_value(pDoc, pXmlElClientSideCredential, bstr(L"allow-save"), bstrNamespace, m_allow_save)) != ERROR_SUCCESS) {
        *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <allow-save> element."), NULL);
        return dwResult;
    }

    // <ClientSideCredential>/<AnonymousIdentity>
    if (!m_anonymous_identity.empty())
        if ((dwResult = eapxml::put_element_value(pDoc, pXmlElClientSideCredential, bstr(L"AnonymousIdentity"), bstrNamespace, bstr(m_anonymous_identity))) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <AnonymousIdentity> element."), NULL);
            return dwResult;
        }

    return ERROR_SUCCESS;
}


DWORD eap::config_method::load(_In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(ppEapError);

    m_allow_save = true;
    m_anonymous_identity.clear();

    // <ClientSideCredential>
    com_obj<IXMLDOMElement> pXmlElClientSideCredential;
    if (eapxml::select_element(pConfigRoot, bstr(L"eap-metadata:ClientSideCredential"), &pXmlElClientSideCredential) == ERROR_SUCCESS) {
        // <allow-save>
        eapxml::get_element_value(pXmlElClientSideCredential, bstr(L"eap-metadata:allow-save"), &m_allow_save);

        // <AnonymousIdentity>
        eapxml::get_element_value(pXmlElClientSideCredential, bstr(L"eap-metadata:AnonymousIdentity"), m_anonymous_identity);
    }

    return ERROR_SUCCESS;
}


//////////////////////////////////////////////////////////////////////
// eap::credentials
//////////////////////////////////////////////////////////////////////

eap::credentials::credentials(_In_ module &mod) : config(mod)
{
}


eap::credentials::credentials(_In_ const credentials &other) :
    m_identity(other.m_identity),
    config(other)
{
}


eap::credentials::credentials(_Inout_ credentials &&other) :
    m_identity(std::move(other.m_identity)),
    config(std::move(other))
{
}


eap::credentials& eap::credentials::operator=(_In_ const credentials &other)
{
    if (this != &other) {
        (config&)*this = other;
        m_identity     = other.m_identity;
    }

    return *this;
}


eap::credentials& eap::credentials::operator=(_Inout_ credentials &&other)
{
    if (this != &other) {
        (config&)*this = std::move(other);
        m_identity     = std::move(other.m_identity);
    }

    return *this;
}


void eap::credentials::clear()
{
    m_identity.clear();
}


bool eap::credentials::empty() const
{
    return m_identity.empty();
}


DWORD eap::credentials::save(_In_ IXMLDOMDocument *pDoc, _In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError) const
{
    UNREFERENCED_PARAMETER(pDoc);
    UNREFERENCED_PARAMETER(pConfigRoot);
    UNREFERENCED_PARAMETER(ppEapError);

    // Yeah, right!? Credentials are non-exportable!
    return ERROR_NOT_SUPPORTED;
}


//////////////////////////////////////////////////////////////////////
// eap::credentials_pass
//////////////////////////////////////////////////////////////////////

eap::credentials_pass::credentials_pass(_In_ module &mod) : credentials(mod)
{
}


eap::credentials_pass::credentials_pass(_In_ const credentials_pass &other) :
    m_password(other.m_password),
    credentials(other)
{
}


eap::credentials_pass::credentials_pass(_Inout_ credentials_pass &&other) :
    m_password(std::move(other.m_password)),
    credentials(std::move(other))
{
}


eap::credentials_pass& eap::credentials_pass::operator=(_In_ const credentials_pass &other)
{
    if (this != &other) {
        (credentials&)*this = other;
        m_password          = other.m_password;
    }

    return *this;
}


eap::credentials_pass& eap::credentials_pass::operator=(_Inout_ credentials_pass &&other)
{
    if (this != &other) {
        (credentials&)*this = std::move(other);
        m_password          = std::move(other.m_password);
    }

    return *this;
}


void eap::credentials_pass::clear()
{
    credentials::clear();
    m_password.clear();
}


bool eap::credentials_pass::empty() const
{
    return credentials::empty() && m_password.empty();
}


DWORD eap::credentials_pass::load(_In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError)
{
    assert(pConfigRoot);
    UNREFERENCED_PARAMETER(ppEapError);

    eapxml::get_element_value(pConfigRoot, bstr(L"eap-metadata:UserName"), m_identity);

    bstr pass;
    if ((eapxml::get_element_value(pConfigRoot, bstr(L"eap-metadata:Password"), &pass)) == ERROR_SUCCESS)
        m_password = pass;
    SecureZeroMemory((BSTR)pass, sizeof(OLECHAR)*pass.length());

    return ERROR_SUCCESS;
}


DWORD eap::credentials_pass::store(_In_ LPCTSTR pszTargetName, _Out_ EAP_ERROR **ppEapError) const
{
    assert(pszTargetName);
    assert(ppEapError);
    DWORD dwResult;
    string password_enc;

    // Prepare cryptographics provider.
    crypt_prov cp;
    if (!cp.create(NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CryptAcquireContext failed."), NULL);
        return dwResult;
    }

    // Import the public key.
    HRSRC res = FindResource(m_module.m_instance, MAKEINTRESOURCE(IDR_EAP_KEY_PUBLIC), RT_RCDATA);
    assert(res);
    HGLOBAL res_handle = LoadResource(m_module.m_instance, res);
    assert(res_handle);
    crypt_key key;
    unique_ptr<CERT_PUBLIC_KEY_INFO, LocalFree_delete<CERT_PUBLIC_KEY_INFO> > keyinfo_data;
    DWORD keyinfo_size = 0;
    if (!CryptDecodeObjectEx(X509_ASN_ENCODING, X509_PUBLIC_KEY_INFO, (const BYTE*)::LockResource(res_handle), ::SizeofResource(m_module.m_instance, res), CRYPT_DECODE_ALLOC_FLAG, NULL, &keyinfo_data, &keyinfo_size)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CryptDecodeObjectEx failed."), NULL);
        return dwResult;
    }

    if (!key.import_public(cp, X509_ASN_ENCODING, keyinfo_data.get())) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Public key import failed."), NULL);
        return dwResult;
    }

    // Convert password to UTF-8.
    sanitizing_string password_utf8;
    WideCharToMultiByte(CP_UTF8, 0, m_password.c_str(), (int)m_password.length(), password_utf8, NULL, NULL);

    // Pre-allocate memory to allow space, as encryption will grow the data, and we need additional 16B at the end for MD5 hash.
    DWORD dwBlockLen;
    vector<char, sanitizing_allocator<char> > password(password_utf8.length());
    memcpy(password.data(), password_utf8.c_str(), sizeof(char)*password_utf8.length());
    if (!CryptGetKeyParam(key, KP_BLOCKLEN, dwBlockLen, 0)) dwBlockLen = 0;
    password.reserve((password.size() + dwBlockLen - 1) / dwBlockLen * dwBlockLen + 16);

    // Encrypt the password using our public key. Calculate MD5 hash and append it.
    crypt_hash hash;
    if (!hash.create(cp, CALG_MD5)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Creating MD5 hash failed."), NULL);
        return dwResult;
    }
    if (!CryptEncrypt(key, hash, TRUE, 0, password)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Encrypting password failed."), NULL);
        return dwResult;
    }
    vector<char> hash_bin;
    CryptGetHashParam(hash, HP_HASHVAL, hash_bin, 0);
    password.insert(password.end(), hash_bin.begin(), hash_bin.end());

    // Convert encrypted password to Base64, since CredProtectA() fail for binary strings.
    string password_base64;
    base64_enc enc;
    enc.encode(password_base64, password.data(), password.size());

    // Encrypt the password using user's key.
    CRED_PROTECTION_TYPE cpt;
    if (!CredProtectA(TRUE, password_base64.c_str(), (DWORD)password_base64.length(), password_enc, &cpt)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CredProtect failed."), NULL);
        return dwResult;
    }

    tstring target(target_name(pszTargetName));

    // Write credentials.
    assert(password_enc.size()*sizeof(char) < CRED_MAX_CREDENTIAL_BLOB_SIZE);
    assert(m_identity.length()              < CRED_MAX_USERNAME_LENGTH     );
    CREDENTIAL cred = {
        0,                                          // Flags
        CRED_TYPE_GENERIC,                          // Type
        (LPTSTR)target.c_str(),                     // TargetName
        _T(""),                                     // Comment
        { 0, 0 },                                   // LastWritten
        (DWORD)password_enc.size()*sizeof(char),    // CredentialBlobSize
        (LPBYTE)password_enc.data(),                // CredentialBlob
        CRED_PERSIST_ENTERPRISE,                    // Persist
        0,                                          // AttributeCount
        NULL,                                       // Attributes
        NULL,                                       // TargetAlias
        (LPTSTR)m_identity.c_str()                  // UserName
    };
    if (!CredWrite(&cred, 0)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CredWrite failed."), NULL);
        return dwResult;
    }

    return ERROR_SUCCESS;
}


DWORD eap::credentials_pass::retrieve(_In_ LPCTSTR pszTargetName, _Out_ EAP_ERROR **ppEapError)
{
    assert(pszTargetName);
    DWORD dwResult;

    // Read credentials.
    unique_ptr<CREDENTIAL, CredFree_delete<CREDENTIAL> > cred;
    if (!CredRead(target_name(pszTargetName).c_str(), CRED_TYPE_GENERIC, 0, (PCREDENTIAL*)&cred)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CredRead failed."), NULL);
        return dwResult;
    }

    m_identity = cred->UserName;

    // Decrypt the password using user's key.
    string password_base64;
    if (!CredUnprotectA(TRUE, (LPCSTR)(cred->CredentialBlob), cred->CredentialBlobSize/sizeof(char), password_base64)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CredUnprotect failed."), NULL);
        return dwResult;
    }

    // Convert Base64 to binary encrypted password, since CredProtectA() fail for binary strings.
    vector<char, sanitizing_allocator<char> > password;
    base64_dec dec;
    bool is_last;
    dec.decode(password, is_last, password_base64.c_str(), password_base64.length());

    // Prepare cryptographics provider.
    crypt_prov cp;
    if (!cp.create(NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CryptAcquireContext failed."), NULL);
        return dwResult;
    }

    // Create hash.
    crypt_hash hash;
    if (!hash.create(cp, CALG_MD5)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Creating MD5 hash failed."), NULL);
        return dwResult;
    }
    DWORD dwHashSize, dwHashSizeSize = sizeof(dwHashSize);
    CryptGetHashParam(hash, HP_HASHSIZE, (LPBYTE)&dwHashSize, &dwHashSizeSize, 0);
    if (password.size() < dwHashSize) {
        *ppEapError = m_module.make_error(dwResult = ERROR_INVALID_DATA, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Encrypted password too short."), NULL);
        return dwResult;
    }

    // Truncate hash from encrypted password.
    vector<char> hash_bin;
    size_t enc_size = password.size() - dwHashSize;
    hash_bin.assign(password.begin() + enc_size, password.end());
    password.resize(enc_size);

    // Import the private key.
    HRSRC res = FindResource(m_module.m_instance, MAKEINTRESOURCE(IDR_EAP_KEY_PRIVATE), RT_RCDATA);
    assert(res);
    HGLOBAL res_handle = LoadResource(m_module.m_instance, res);
    assert(res_handle);
    crypt_key key;
    unique_ptr<unsigned char[], LocalFree_delete<unsigned char[]> > keyinfo_data;
    DWORD keyinfo_size = 0;
    if (!CryptDecodeObjectEx(X509_ASN_ENCODING, PKCS_RSA_PRIVATE_KEY, (const BYTE*)::LockResource(res_handle), ::SizeofResource(m_module.m_instance, res), CRYPT_DECODE_ALLOC_FLAG, NULL, &keyinfo_data, &keyinfo_size)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" CryptDecodeObjectEx failed."), NULL);
        return dwResult;
    }

    if (!key.import(cp, keyinfo_data.get(), keyinfo_size, NULL, 0)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Private key import failed."), NULL);
        return dwResult;
    }

    // Decrypt the password using our private key. Calculate MD5 hash and verify it.
    if (!CryptDecrypt(key, hash, TRUE, 0, password)) {
        *ppEapError = m_module.make_error(dwResult = GetLastError(), 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Decrypting password failed."), NULL);
        return dwResult;
    }
    vector<char> hash2_bin;
    CryptGetHashParam(hash, HP_HASHVAL, hash2_bin, 0);
    if (hash_bin != hash2_bin) {
        *ppEapError = m_module.make_error(dwResult = ERROR_INVALID_DATA, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Invalid password data."), NULL);
        return dwResult;
    }

    // Convert password from UTF-8.
    MultiByteToWideChar(CP_UTF8, 0, password.data(), (int)password.size(), m_password);

    return ERROR_SUCCESS;
}


//////////////////////////////////////////////////////////////////////
// eap::module
//////////////////////////////////////////////////////////////////////

eap::module::module() :
    m_instance(NULL)
{
    m_ep.create(&EAPMETHOD_TRACE_EVENT_PROVIDER);
    m_ep.write(&EAPMETHOD_TRACE_EVT_MODULE_LOAD, event_data((BYTE)EAPMETHOD_TYPE), event_data::blank);

    m_heap.create(0, 0, 0);
}


eap::module::~module()
{
    m_ep.write(&EAPMETHOD_TRACE_EVT_MODULE_UNLOAD, event_data((BYTE)EAPMETHOD_TYPE), event_data::blank);
}


EAP_ERROR* eap::module::make_error(_In_ DWORD dwErrorCode, _In_ DWORD dwReasonCode, _In_ LPCGUID pRootCauseGuid, _In_ LPCGUID pRepairGuid, _In_ LPCGUID pHelpLinkGuid, _In_z_ LPCWSTR pszRootCauseString, _In_z_ LPCWSTR pszRepairString) const
{
    // Calculate memory size requirement.
    SIZE_T
        nRootCauseSize    = pszRootCauseString != NULL && pszRootCauseString[0] ? (wcslen(pszRootCauseString) + 1)*sizeof(WCHAR) : 0,
        nRepairStringSize = pszRepairString    != NULL && pszRepairString   [0] ? (wcslen(pszRepairString   ) + 1)*sizeof(WCHAR) : 0,
        nEapErrorSize = sizeof(EAP_ERROR) + nRootCauseSize + nRepairStringSize;

    EAP_ERROR *pError = (EAP_ERROR*)HeapAlloc(m_heap, 0, nEapErrorSize);
    if (!pError)
        return NULL;
    BYTE *p = (BYTE*)(pError + 1);

    // Fill the error descriptor.
    pError->dwWinError                = dwErrorCode;
    pError->type.eapType.type         = EAPMETHOD_TYPE;
    pError->type.eapType.dwVendorId   = 0;
    pError->type.eapType.dwVendorType = 0;
    pError->type.dwAuthorId           = 67532;
    pError->dwReasonCode              = dwReasonCode;
    pError->rootCauseGuid             = pRootCauseGuid != NULL ? *pRootCauseGuid : GUID_NULL;
    pError->repairGuid                = pRepairGuid    != NULL ? *pRepairGuid    : GUID_NULL;
    pError->helpLinkGuid              = pHelpLinkGuid  != NULL ? *pHelpLinkGuid  : GUID_NULL;
    if (nRootCauseSize) {
        pError->pRootCauseString = (LPWSTR)p;
        memcpy(pError->pRootCauseString, pszRootCauseString, nRootCauseSize);
        p += nRootCauseSize;
    } else
        pError->pRootCauseString = NULL;
    if (nRepairStringSize) {
        pError->pRepairString = (LPWSTR)p;
        memcpy(pError->pRepairString, pszRepairString, nRepairStringSize);
        p += nRepairStringSize;
    } else
        pError->pRepairString = NULL;

    // Write trace event.
    vector<EVENT_DATA_DESCRIPTOR> evt_desc;
    evt_desc.reserve(8);
    evt_desc.push_back(event_data(pError->dwWinError));
    evt_desc.push_back(event_data(pError->type.eapType.type));
    evt_desc.push_back(event_data(pError->dwReasonCode));
    evt_desc.push_back(event_data(&(pError->rootCauseGuid), sizeof(GUID)));
    evt_desc.push_back(event_data(&(pError->repairGuid), sizeof(GUID)));
    evt_desc.push_back(event_data(&(pError->helpLinkGuid), sizeof(GUID)));
    evt_desc.push_back(event_data(pError->pRootCauseString));
    evt_desc.push_back(event_data(pError->pRepairString));
    m_ep.write(&EAPMETHOD_TRACE_EAP_ERROR, (ULONG)evt_desc.size(), evt_desc.data());

    return pError;
}


BYTE* eap::module::alloc_memory(_In_ size_t size)
{
    return (BYTE*)HeapAlloc(m_heap, 0, size);
}


void eap::module::free_memory(_In_ BYTE *ptr)
{
    ETW_FN_VOID;

    // Since we do security here and some of the BLOBs contain credentials, sanitize every memory block before freeing.
    SecureZeroMemory(ptr, HeapSize(m_heap, 0, ptr));
    HeapFree(m_heap, 0, ptr);
}


void eap::module::free_error_memory(_In_ EAP_ERROR *err)
{
    ETW_FN_VOID;

    // pRootCauseString and pRepairString always trail the ppEapError to reduce number of (de)allocations.
    HeapFree(m_heap, 0, err);
}