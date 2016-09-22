﻿///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __WXEAP_UI_H__
#define __WXEAP_UI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class wxEAPBannerPanel;
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/choice.h>
#include <wx/checkbox.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class wxEAPConfigDialogBase
///////////////////////////////////////////////////////////////////////////////
class wxEAPConfigDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxEAPBannerPanel *m_banner;
		wxNotebook* m_providers;
		wxButton* m_prov_add;
		wxButton* m_prov_remove;
		wxButton* m_prov_advanced;
		wxStdDialogButtonSizer* m_buttons;
		wxButton* m_buttonsOK;
		wxButton* m_buttonsCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnProvAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProvRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProvAdvanced( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		wxEAPConfigDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("EAP Connection Configuration"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~wxEAPConfigDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class wxEAPGeneralDialogBase
///////////////////////////////////////////////////////////////////////////////
class wxEAPGeneralDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxEAPBannerPanel *m_banner;
		wxBoxSizer* m_panels;
		wxStdDialogButtonSizer* m_buttons;
		wxButton* m_buttonsOK;
		wxButton* m_buttonsCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		
	
	public:
		
		wxEAPGeneralDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~wxEAPGeneralDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class wxEAPCredentialsConnectionDialogBase
///////////////////////////////////////////////////////////////////////////////
class wxEAPCredentialsConnectionDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxEAPBannerPanel *m_banner;
		wxStdDialogButtonSizer* m_buttons;
		wxButton* m_buttonsOK;
		wxButton* m_buttonsCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		
	
	public:
		wxNotebook* m_providers;
		
		wxEAPCredentialsConnectionDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("EAP Credentials"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~wxEAPCredentialsConnectionDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class wxEAPBannerPanelBase
///////////////////////////////////////////////////////////////////////////////
class wxEAPBannerPanelBase : public wxPanel 
{
	private:
	
	protected:
	
	public:
		wxStaticText* m_title;
		
		wxEAPBannerPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = 0 ); 
		~wxEAPBannerPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class wxEAPNotePanelBase
///////////////////////////////////////////////////////////////////////////////
class wxEAPNotePanelBase : public wxPanel 
{
	private:
	
	protected:
		wxStaticBitmap* m_note_icon;
		wxBoxSizer* m_note_vert;
		wxStaticText* m_note_label;
	
	public:
		
		wxEAPNotePanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,-1 ), long style = wxSIMPLE_BORDER|wxTAB_TRAVERSAL ); 
		~wxEAPNotePanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class wxEAPCredentialsPassPanelBase
///////////////////////////////////////////////////////////////////////////////
class wxEAPCredentialsPassPanelBase : public wxPanel 
{
	private:
	
	protected:
		wxStaticBoxSizer* m_sb_credentials;
		wxStaticBitmap* m_credentials_icon;
		wxBoxSizer* m_sb_credentials_vert;
		wxStaticText* m_credentials_label;
		wxStaticText* m_identity_label;
		wxTextCtrl* m_identity;
		wxStaticText* m_password_label;
		wxTextCtrl* m_password;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		
	
	public:
		
		wxEAPCredentialsPassPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,-1 ), long style = wxTAB_TRAVERSAL ); 
		~wxEAPCredentialsPassPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class wxEAPProviderContactInfoPanelBase
///////////////////////////////////////////////////////////////////////////////
class wxEAPProviderContactInfoPanelBase : public wxPanel 
{
	private:
	
	protected:
		wxStaticBitmap* m_provider_contact_icon;
		wxStaticText* m_provider_contact_label;
		wxStaticText* m_provider_name_label;
		wxTextCtrl* m_provider_name;
		wxStaticText* m_provider_name_note;
		wxStaticText* m_provider_helpdesk_label;
		wxStaticText* m_provider_web_icon;
		wxTextCtrl* m_provider_web;
		wxStaticText* m_provider_email_icon;
		wxTextCtrl* m_provider_email;
		wxStaticText* m_provider_phone_icon;
		wxTextCtrl* m_provider_phone;
	
	public:
		
		wxEAPProviderContactInfoPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,-1 ), long style = wxTAB_TRAVERSAL ); 
		~wxEAPProviderContactInfoPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class wxEAPProviderIDPanelBase
///////////////////////////////////////////////////////////////////////////////
class wxEAPProviderIDPanelBase : public wxPanel 
{
	private:
	
	protected:
		wxStaticBitmap* m_provider_id_icon;
		wxStaticText* m_provider_id_label_outer;
		wxStaticText* m_provider_namespace_label;
		wxChoice* m_provider_namespace;
		wxStaticText* m_provider_id_label;
		wxTextCtrl* m_provider_id;
	
	public:
		
		wxEAPProviderIDPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,-1 ), long style = wxTAB_TRAVERSAL ); 
		~wxEAPProviderIDPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class wxEAPProviderLockPanelBase
///////////////////////////////////////////////////////////////////////////////
class wxEAPProviderLockPanelBase : public wxPanel 
{
	private:
	
	protected:
		wxStaticBitmap* m_provider_lock_icon;
		wxStaticText* m_provider_lock_label;
		wxCheckBox* m_provider_lock;
		wxStaticText* m_provider_lock_note;
	
	public:
		
		wxEAPProviderLockPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,-1 ), long style = wxTAB_TRAVERSAL ); 
		~wxEAPProviderLockPanelBase();
	
};

#endif //__WXEAP_UI_H__
