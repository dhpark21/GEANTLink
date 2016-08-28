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

#include "StdAfx.h"

using namespace std;
using namespace winstd;


//////////////////////////////////////////////////////////////////////
// eap::credentials_ttls
//////////////////////////////////////////////////////////////////////

eap::credentials_ttls::credentials_ttls(_In_ module &mod) :
    credentials_tls(mod)
{
}


eap::credentials_ttls::credentials_ttls(_In_ const credentials_ttls &other) :
    m_inner(other.m_inner ? (credentials*)other.m_inner->clone() : nullptr),
    credentials_tls(other)
{
}


eap::credentials_ttls::credentials_ttls(_Inout_ credentials_ttls &&other) :
    m_inner(std::move(other.m_inner)),
    credentials_tls(std::move(other))
{
}


eap::credentials_ttls& eap::credentials_ttls::operator=(_In_ const credentials_ttls &other)
{
    if (this != &other) {
        (credentials_tls&)*this = other;
        m_inner.reset(other.m_inner ? (credentials*)other.m_inner->clone() : nullptr);
    }

    return *this;
}


eap::credentials_ttls& eap::credentials_ttls::operator=(_Inout_ credentials_ttls &&other)
{
    if (this != &other) {
        (credentials_tls&)*this = std::move(other);
        m_inner                 = std::move(other.m_inner);
    }

    return *this;
}


eap::config* eap::credentials_ttls::clone() const
{
    return new credentials_ttls(*this);
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


void eap::credentials_ttls::save(_In_ IXMLDOMDocument *pDoc, _In_ IXMLDOMNode *pConfigRoot) const
{
    assert(pDoc);
    assert(pConfigRoot);

    credentials_tls::save(pDoc, pConfigRoot);

    const bstr bstrNamespace(L"urn:ietf:params:xml:ns:yang:ietf-eap-metadata");
    HRESULT hr;

    if (m_inner) {
        // <InnerAuthenticationMethod>
        winstd::com_obj<IXMLDOMElement> pXmlElInnerAuthenticationMethod;
        if (FAILED(hr = eapxml::create_element(pDoc, winstd::bstr(L"InnerAuthenticationMethod"), bstrNamespace, &pXmlElInnerAuthenticationMethod)))
            throw com_runtime_error(hr, __FUNCTION__ " Error creating <InnerAuthenticationMethod> element.");

        m_inner->save(pDoc, pXmlElInnerAuthenticationMethod);

        if (FAILED(hr = pConfigRoot->appendChild(pXmlElInnerAuthenticationMethod, NULL)))
            throw com_runtime_error(hr, __FUNCTION__ " Error appending <InnerAuthenticationMethod> element.");
    }
}


void eap::credentials_ttls::load(_In_ IXMLDOMNode *pConfigRoot)
{
    assert(pConfigRoot);
    HRESULT hr;

    credentials_tls::load(pConfigRoot);

    if (m_inner) {
        // Load inner credentials.
        com_obj<IXMLDOMNode> pXmlElInnerAuthenticationMethod;
        if (FAILED(hr = eapxml::select_node(pConfigRoot, bstr(L"eap-metadata:InnerAuthenticationMethod"), &pXmlElInnerAuthenticationMethod)))
            throw com_runtime_error(hr, __FUNCTION__ " Error selecting <InnerAuthenticationMethod> element.");

        m_inner->load(pXmlElInnerAuthenticationMethod);
    }
}


void eap::credentials_ttls::operator<<(_Inout_ cursor_out &cursor) const
{
    credentials_tls::operator<<(cursor);
    cursor << *m_inner;
}


size_t eap::credentials_ttls::get_pk_size() const
{
    return
        credentials_tls::get_pk_size() +
        pksizeof(*m_inner);
}


void eap::credentials_ttls::operator>>(_Inout_ cursor_in &cursor)
{
    credentials_tls::operator>>(cursor);
    cursor >> *m_inner;
}


void eap::credentials_ttls::store(_In_z_ LPCTSTR pszTargetName) const
{
    assert(0); // Not that we would ever store inner&outer credentials to Windows Credential Manager joined, but for completness sake... Here we go:

    credentials_tls::store(pszTargetName);

    m_inner->store(pszTargetName);
}


void eap::credentials_ttls::retrieve(_In_z_ LPCTSTR pszTargetName)
{
    assert(0); // Not that we would ever retrieve inner&outer credentials to Windows Credential Manager joined, but for completness sake... Here we go:

    credentials_tls::retrieve(pszTargetName);

    m_inner->retrieve(pszTargetName);
}


LPCTSTR eap::credentials_ttls::target_suffix() const
{
    assert(0); // Not that we would ever store inner&outer credentials to Windows Credential Manager joined, but for completness sake... Here we go:
    return _T("TTLS");
}


wstring eap::credentials_ttls::get_identity() const
{
    // Outer identity has the right-of-way.
    wstring identity(credentials_tls::get_identity());
    if (!identity.empty())
        return identity;

    // Inner identity.
    return m_inner->get_identity();
}


eap::credentials::source_t eap::credentials_ttls::combine(
    _In_       const credentials             *cred_cached,
    _In_       const config_method_with_cred &cfg,
    _In_opt_z_       LPCTSTR                 pszTargetName)
{
    source_t src;

    // Combine outer credentials first.
    src = credentials_tls::combine(
        cred_cached,
        cfg,
        pszTargetName);
    if (src == source_unknown) {
        // Outer credentials are unknown. Enough unknowness.
        return source_unknown;
    }

    // Combine inner credentials.
    return m_inner->combine(
        cred_cached ? ((const credentials_ttls*)cred_cached)->m_inner.get() : NULL,
        *((const config_method_ttls&)cfg).m_inner,
        pszTargetName);
}
