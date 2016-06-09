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

#pragma comment(lib, "Msi.lib")
#pragma comment(lib, "msxml6.lib")

using namespace std;
using namespace winstd;


//////////////////////////////////////////////////////////////////////
// eap::config_ttls
//////////////////////////////////////////////////////////////////////

eap::config_ttls::config_ttls(_In_ module &mod) :
    m_inner(NULL),
    config_tls(mod)
{
}


eap::config_ttls::config_ttls(const _In_ config_ttls &other) :
    m_inner(other.m_inner ? (config_method*)other.m_inner->clone() : NULL),
    config_tls(other)
{
}


eap::config_ttls::config_ttls(_Inout_ config_ttls &&other) :
    m_inner(other.m_inner),
    config_tls(std::move(other))
{
    other.m_inner = NULL;
}


eap::config_ttls::~config_ttls()
{
    if (m_inner)
        delete m_inner;
}


eap::config_ttls& eap::config_ttls::operator=(const _In_ config_ttls &other)
{
    if (this != &other) {
        (config_tls&)*this = other;
        if (m_inner) delete m_inner;
        m_inner = other.m_inner ? (config_method*)other.m_inner->clone() : NULL;
    }

    return *this;
}


eap::config_ttls& eap::config_ttls::operator=(_Inout_ config_ttls &&other)
{
    if (this != &other) {
        (config_tls&&)*this = std::move(other);
        if (m_inner) delete m_inner;
        m_inner = other.m_inner;
        other.m_inner = NULL;
    }

    return *this;
}


DWORD eap::config_ttls::save(_In_ IXMLDOMDocument *pDoc, _In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError) const
{
    const bstr bstrNamespace(L"urn:ietf:params:xml:ns:yang:ietf-eap-metadata");
    DWORD dwResult;

    // <InnerAuthenticationMethod>
    com_obj<IXMLDOMElement> pXmlElInnerAuthenticationMethod;
    if ((dwResult = eapxml::create_element(pDoc, pConfigRoot, bstr(L"eap-metadata:InnerAuthenticationMethod"), bstr(L"InnerAuthenticationMethod"), bstrNamespace, &pXmlElInnerAuthenticationMethod)) != ERROR_SUCCESS) {
        *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <InnerAuthenticationMethod> element."), NULL);
        return dwResult;
    }

    if (dynamic_cast<const config_pap*>(m_inner)) {
        // <InnerAuthenticationMethod>/<NonEAPAuthMethod>
        if ((dwResult = eapxml::put_element_value(pDoc, pXmlElInnerAuthenticationMethod, bstr(L"NonEAPAuthMethod"), bstrNamespace, bstr(L"PAP"))) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error creating <NonEAPAuthMethod> element."), NULL);
            return dwResult;
        }

        // <InnerAuthenticationMethod>/...
        if ((dwResult = m_inner->save(pDoc, pXmlElInnerAuthenticationMethod, ppEapError)) != ERROR_SUCCESS)
            return dwResult;
    } else
        return dwResult = ERROR_NOT_SUPPORTED;

    return config_tls::save(pDoc, pConfigRoot, ppEapError);
}


DWORD eap::config_ttls::load(_In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError)
{
    assert(ppEapError);
    DWORD dwResult;

    // Load inner authentication configuration (<InnerAuthenticationMethod>).
    com_obj<IXMLDOMElement> pXmlElInnerAuthenticationMethod;
    if ((dwResult = eapxml::select_element(pConfigRoot, bstr(L"eap-metadata:InnerAuthenticationMethod"), &pXmlElInnerAuthenticationMethod)) != ERROR_SUCCESS) {
        *ppEapError = m_module.make_error(dwResult, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error selecting <InnerAuthenticationMethod> element."), NULL);
        return dwResult;
    }

    // Determine inner authentication type (<EAPMethod> and <NonEAPAuthMethod>).
    //DWORD dwMethodID;
    bstr bstrMethod;
    /*if (eapxml::get_element_value(pXmlElInnerAuthenticationMethod, bstr(L"eap-metadata:EAPMethod"), &dwMethodID) == ERROR_SUCCESS &&
        dwMethodID == EAP_TYPE_MSCHAPV2)
    {
        // MSCHAPv2
        // TODO: Add MSCHAPv2 support.
        return ERROR_NOT_SUPPORTED;
    } else*/ if (eapxml::get_element_value(pXmlElInnerAuthenticationMethod, bstr(L"eap-metadata:NonEAPAuthMethod"), &bstrMethod) == ERROR_SUCCESS &&
        CompareStringEx(LOCALE_NAME_INVARIANT, NORM_IGNORECASE, bstrMethod, bstrMethod.length(), L"PAP", -1, NULL, NULL, 0) == CSTR_EQUAL)
    {
        // PAP
        assert(!m_inner);
        m_inner = new eap::config_pap(m_module);
        if ((dwResult = m_inner->load(pXmlElInnerAuthenticationMethod, ppEapError)) != ERROR_SUCCESS)
            return dwResult;
    } else {
        *ppEapError = m_module.make_error(dwResult = ERROR_NOT_SUPPORTED, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Unsupported inner authentication method."), NULL);
        return dwResult;
    }

    return config_tls::load(pConfigRoot, ppEapError);
}


//////////////////////////////////////////////////////////////////////
// eap::credentials_ttls
//////////////////////////////////////////////////////////////////////

eap::credentials_ttls::credentials_ttls(_In_ module &mod) : credentials_tls(mod)
{
}


eap::credentials_ttls::credentials_ttls(_In_ const credentials_ttls &other) :
    m_inner(other.m_inner ? (credentials*)other.m_inner->clone() : NULL),
    credentials_tls(other)
{
}


eap::credentials_ttls::credentials_ttls(_Inout_ credentials_ttls &&other) :
    m_inner(other.m_inner),
    credentials_tls(std::move(other))
{
    other.m_inner = NULL;
}


eap::credentials_ttls& eap::credentials_ttls::operator=(_In_ const credentials_ttls &other)
{
    if (this != &other) {
        (credentials_tls&)*this = other;

        if (m_inner) delete m_inner;
        m_inner = other.m_inner ? (credentials*)other.m_inner->clone() : NULL;
    }

    return *this;
}


eap::credentials_ttls& eap::credentials_ttls::operator=(_Inout_ credentials_ttls &&other)
{
    if (this != &other) {
        (credentials_tls&)*this = std::move(other);

        if (m_inner) delete m_inner;
        m_inner = other.m_inner;
        other.m_inner = NULL;
    }

    return *this;
}



void eap::credentials_ttls::clear()
{
    credentials_tls::clear();
    if (m_inner)
        m_inner->clear();
}


bool eap::credentials_ttls::empty() const
{
    return credentials_tls::empty() && (!m_inner || m_inner->empty());
}



DWORD eap::credentials_ttls::load(_In_ IXMLDOMNode *pConfigRoot, _Out_ EAP_ERROR **ppEapError)
{
    assert(pConfigRoot);
    DWORD dwResult;

    if ((dwResult = credentials_tls::load(pConfigRoot, ppEapError)) != ERROR_SUCCESS)
        return dwResult;

    if (m_inner) {
        com_obj<IXMLDOMNode> pXmlElInnerAuthenticationMethod;
        if ((dwResult = eapxml::select_node(pConfigRoot, bstr(L"eap-metadata:InnerAuthenticationMethod"), &pXmlElInnerAuthenticationMethod)) != ERROR_SUCCESS) {
            *ppEapError = m_module.make_error(dwResult = ERROR_NOT_FOUND, 0, NULL, NULL, NULL, _T(__FUNCTION__) _T(" Error selecting <InnerAuthenticationMethod> element."), NULL);
            return dwResult;
        }

        if ((dwResult = m_inner->load(pXmlElInnerAuthenticationMethod, ppEapError)) != ERROR_SUCCESS)
            return dwResult;
    }

    return ERROR_SUCCESS;
}


DWORD eap::credentials_ttls::store(_In_ LPCTSTR pszTargetName, _Out_ EAP_ERROR **ppEapError) const
{
    DWORD dwResult;

    if ((dwResult = credentials_tls::store(pszTargetName, ppEapError)) != ERROR_SUCCESS)
        return dwResult;

    if (m_inner) {
        if ((dwResult = m_inner->store(pszTargetName, ppEapError)) != ERROR_SUCCESS)
            return dwResult;
    }

    return ERROR_SUCCESS;
}


DWORD eap::credentials_ttls::retrieve(_In_ LPCTSTR pszTargetName, _Out_ EAP_ERROR **ppEapError)
{
    DWORD dwResult;

    if ((dwResult = credentials_tls::retrieve(pszTargetName, ppEapError)) != ERROR_SUCCESS)
        return dwResult;

    if (m_inner) {
        if ((dwResult = m_inner->retrieve(pszTargetName, ppEapError)) != ERROR_SUCCESS)
            return dwResult;
    }

    return ERROR_SUCCESS;
}


//////////////////////////////////////////////////////////////////////
// eap::session_ttls
//////////////////////////////////////////////////////////////////////

eap::session_ttls::session_ttls() : session()
{
}


//////////////////////////////////////////////////////////////////////
// eap::peer_ttls
//////////////////////////////////////////////////////////////////////

eap::peer_ttls::peer_ttls() : peer()
{
}


DWORD eap::peer_ttls::initialize(_Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(ppEapError);

    // MSI's feature completeness check removed: It might invoke UI (prompt user for missing MSI),
    // which would be disasterous in EapHost system service.
#if 0
    // Perform the Microsoft Installer's feature completeness check manually.
    // If execution got this far in the first place (dependent DLLs are present and loadable).
    // Furthermore, this increments program usage counter.
    if (MsiQueryFeatureState(_T(PRODUCT_VERSION_GUID), _T("featEAPTTLS")) != INSTALLSTATE_UNKNOWN)
        MsiUseFeature(_T(PRODUCT_VERSION_GUID), _T("featEAPTTLS"));
#endif

    return ERROR_SUCCESS;
}


DWORD eap::peer_ttls::shutdown(_Out_ EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(ppEapError);
    return ERROR_SUCCESS;
}


DWORD eap::peer_ttls::get_identity(
    _In_                                   DWORD     dwFlags,
    _In_                                   DWORD     dwConnectionDataSize,
    _In_count_(dwConnectionDataSize) const BYTE      *pConnectionData,
    _In_                                   DWORD     dwUserDataSize,
    _In_count_(dwUserDataSize)       const BYTE      *pUserData,
    _In_                                   HANDLE    hTokenImpersonateUser,
    _Out_                                  BOOL      *pfInvokeUI,
    _Out_                                  DWORD     *pdwUserDataOutSize,
    _Out_                                  BYTE      **ppUserDataOut,
    _Out_                                  WCHAR     **ppwszIdentity,
    _Out_                                  EAP_ERROR **ppEapError)
{
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(dwConnectionDataSize);
    UNREFERENCED_PARAMETER(pConnectionData);
    UNREFERENCED_PARAMETER(dwUserDataSize);
    UNREFERENCED_PARAMETER(pUserData);
    UNREFERENCED_PARAMETER(hTokenImpersonateUser);
    UNREFERENCED_PARAMETER(pfInvokeUI);
    UNREFERENCED_PARAMETER(pdwUserDataOutSize);
    UNREFERENCED_PARAMETER(ppUserDataOut);
    UNREFERENCED_PARAMETER(ppwszIdentity);
    UNREFERENCED_PARAMETER(ppEapError);

    DWORD dwResult = ERROR_NOT_SUPPORTED;
    ETW_FN_DWORD(dwResult);
    return dwResult;
}


DWORD eap::peer_ttls::get_method_properties(
    _In_                                DWORD                     dwVersion,
    _In_                                DWORD                     dwFlags,
    _In_                                HANDLE                    hUserImpersonationToken,
    _In_                                DWORD                     dwEapConnDataSize,
    _In_count_(dwEapConnDataSize) const BYTE                      *pEapConnData,
    _In_                                DWORD                     dwUserDataSize,
    _In_count_(dwUserDataSize)    const BYTE                      *pUserData,
    _Out_                               EAP_METHOD_PROPERTY_ARRAY *pMethodPropertyArray,
    _Out_                               EAP_ERROR                 **ppEapError) const
{
    UNREFERENCED_PARAMETER(dwVersion);
    UNREFERENCED_PARAMETER(dwFlags);
    UNREFERENCED_PARAMETER(hUserImpersonationToken);
    UNREFERENCED_PARAMETER(dwEapConnDataSize);
    UNREFERENCED_PARAMETER(pEapConnData);
    UNREFERENCED_PARAMETER(dwUserDataSize);
    UNREFERENCED_PARAMETER(pUserData);
    UNREFERENCED_PARAMETER(pMethodPropertyArray);
    UNREFERENCED_PARAMETER(ppEapError);

    DWORD dwResult = ERROR_NOT_SUPPORTED;
    ETW_FN_DWORD(dwResult);
    return dwResult;
}