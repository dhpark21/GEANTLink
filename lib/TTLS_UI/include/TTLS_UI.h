/*
    Copyright 2015-2020 Amebis
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

class wxTLSTunnelConfigWindow;
class wxPEAPConfigWindow;
class wxTTLSConfigWindow;

#pragma once

#include "../../TLS_UI/include/TLS_UI.h"

#include "../../TTLS/include/Config.h"

#include "../../EapHost_UI/include/EapHost_UI.h"
#include "../../PAP_UI/include/PAP_UI.h"
#include "../../MSCHAPv2_UI/include/MSCHAPv2_UI.h"
#include "../../GTC_UI/include/GTC_UI.h"

#include "../../EapHost/include/Config.h"
#include "../../PAP/include/Config.h"
#include "../../MSCHAPv2/include/Config.h"
#include "../../GTC/include/Config.h"

#include <WinStd/Win.h>

#include <wx/choicebk.h>
#include <wx/icon.h>
#include <wx/stattext.h>

#include <Windows.h>


/// \addtogroup EAPBaseGUI
/// @{

///
/// TLS tunnel configuration scrollable window
///
class wxTLSTunnelConfigWindow : public wxEAPConfigWindow
{
public:
    ///
    /// Constructs a configuration window
    ///
    /// \param[in]    prov    Provider configuration data
    /// \param[inout] cfg     Method configuration data
    /// \param[in]    parent  Parent window
    ///
    wxTLSTunnelConfigWindow(eap::config_provider &prov, eap::config_method &cfg, wxWindow* parent);

    ///
    /// Destructs the configuration window
    ///
    virtual ~wxTLSTunnelConfigWindow();

protected:
    /// \cond internal
    virtual bool TransferDataToWindow();
    virtual void OnInitDialog(wxInitDialogEvent& event);
    virtual void OnUpdateUI(wxUpdateUIEvent& event);
    /// \endcond

protected:
    wxStaticText *m_outer_title;                ///< Outer authentication title
    wxEAPIdentityConfigPanel *m_outer_identity; ///< Outer identity configuration panel
    wxPanel *m_tls;                             ///< TLS configuration panel
    wxStaticText *m_inner_title;                ///< Inner authentication title
    wxChoicebook *m_inner_type;                 ///< Inner authentication type
};


///
/// PEAP configuration scrollable window
///
class wxPEAPConfigWindow : public wxTLSTunnelConfigWindow
{
public:
    ///
    /// Constructs a configuration window
    ///
    /// \param[in]    prov    Provider configuration data
    /// \param[inout] cfg     Method configuration data
    /// \param[in]    parent  Parent window
    ///
    wxPEAPConfigWindow(eap::config_provider &prov, eap::config_method &cfg, wxWindow* parent);

protected:
    /// \cond internal
    virtual bool TransferDataToWindow();
    virtual bool TransferDataFromWindow();
    /// \endcond

protected:
    eap::config_method_eapmschapv2 m_cfg_eapmschapv2;       ///< EAP-MSCHAPv2 configuration to hold data until applied
    wxMSCHAPv2ConfigPanel          *m_panel_eapmschapv2;    ///< EAP-MSCHAPv2 config panel
    eap::config_method_eapgtc      m_cfg_eapgtc;            ///< EAP-GTC configuration to hold data until applied
    wxGTCConfigPanel               *m_panel_eapgtc;         ///< EAP-GTC config panel
#if EAP_INNER_EAPHOST
    eap::config_method_eaphost     m_cfg_eaphost;           ///< Inner EAP configuration to hold data until applied
    wxEapHostConfigPanel           *m_panel_eaphost;        ///< Inner EAP config panel
#endif
};

///
/// EAP-TTLS configuration scrollable window
///
class wxTTLSConfigWindow : public wxPEAPConfigWindow
{
public:
    ///
    /// Constructs a configuration window
    ///
    /// \param[in]    prov    Provider configuration data
    /// \param[inout] cfg     Method configuration data
    /// \param[in]    parent  Parent window
    ///
    wxTTLSConfigWindow(eap::config_provider &prov, eap::config_method &cfg, wxWindow* parent);

protected:
    /// \cond internal
    virtual bool TransferDataToWindow();
    virtual bool TransferDataFromWindow();
    /// \endcond

protected:
    eap::config_method_pap         m_cfg_pap;           ///< PAP configuration to hold data until applied
    wxPAPConfigPanel               *m_panel_pap;        ///< PAP config panel
    eap::config_method_mschapv2    m_cfg_mschapv2;      ///< MSCHAPv2 configuration to hold data until applied
    wxMSCHAPv2ConfigPanel          *m_panel_mschapv2;   ///< MSCHAPv2 config panel
};

/// @}
