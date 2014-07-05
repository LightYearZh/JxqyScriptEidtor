#include "JxqyScriptEditor.h"
#include "helperFun.h"
#include "ColourSettingDialog.h"

#include "wx/msgdlg.h"
#include "wx/fontdlg.h"
#include "wx/log.h"

#define SAVE_ERROR_MESSAGEDIALOG wxMessageBox(wxT("����ʧ�ܣ�"), wxT("����"), wxOK | wxCENTER | wxICON_ERROR)
#define VOTE_SAVE_ERROR_MESSAGEDIALOG wxMessageBox(wxT("����ʧ�ܣ��ر��ļ���"), wxT("����"), wxYES_NO | wxCENTER | wxICON_ERROR)

wxFileDialog* JxqyScriptEditor::GetFileSaveDialog(const wxString& defaultFileName)
{
    wxFileDialog *fileDlg = new wxFileDialog(this,
            wxT("�����ļ�"),
            wxEmptyString,
            defaultFileName,
            wxT("txt(*.txt)|*.txt|�����ļ�(*.*)|*.*"),
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    return fileDlg;
}
wxFileDialog* JxqyScriptEditor::GetFileOpenDialog()
{
    wxFileDialog *fileDlg = new wxFileDialog(this,
            wxT("���ļ�"),
            wxEmptyString,
            wxEmptyString,
            wxT("txt(*.txt)|*.txt|�����ļ�(*.*)|*.*"),
            wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    return fileDlg;
}

//(*InternalHeaders(JxqyScriptEditor)
#include <wx/string.h>
//*)

//(*IdInit(JxqyScriptEditor)
const long JxqyScriptEditor::ID_AUINOTEBOOK1 = wxNewId();
const long JxqyScriptEditor::MYID_SAVEALL = wxNewId();
const long JxqyScriptEditor::MYID_CLOSE = wxNewId();
const long JxqyScriptEditor::MYID_CLOSEALL = wxNewId();
const long JxqyScriptEditor::MYID_FONTSETTING = wxNewId();
const long JxqyScriptEditor::MYID_COLOURSETTING = wxNewId();
const long JxqyScriptEditor::MYID_WORDWRAP = wxNewId();
const long JxqyScriptEditor::MYID_FUNHELP = wxNewId();
const long JxqyScriptEditor::MYID_SHOWLINENUMBER = wxNewId();
const long JxqyScriptEditor::MYID_JXQY2 = wxNewId();
const long JxqyScriptEditor::MYID_YYCS = wxNewId();
const long JxqyScriptEditor::MYID_XJXQY = wxNewId();
//*)



BEGIN_EVENT_TABLE(JxqyScriptEditor,wxFrame)
    //(*EventTable(JxqyScriptEditor)
    //*)
    EVT_MENU(wxID_NEW, JxqyScriptEditor::OnNewFile)
    EVT_MENU(wxID_OPEN, JxqyScriptEditor::OnOpenFile)
    EVT_MENU(wxID_SAVE, JxqyScriptEditor::OnSave)
    EVT_MENU(wxID_SAVEAS, JxqyScriptEditor::OnSaveAs)
    EVT_MENU(MYID_SAVEALL, JxqyScriptEditor::OnSaveAll)
    EVT_MENU(MYID_CLOSE, JxqyScriptEditor::OnClose)
    EVT_MENU(MYID_CLOSEALL, JxqyScriptEditor::OnCloseAll)
    EVT_MENU(wxID_EXIT, JxqyScriptEditor::OnExit)
    EVT_MENU(MYID_FONTSETTING, JxqyScriptEditor::OnFontSetting)
    EVT_MENU(MYID_COLOURSETTING, JxqyScriptEditor::OnColourSetting)
    EVT_MENU(MYID_WORDWRAP, JxqyScriptEditor::OnWordWrap)
    EVT_MENU(MYID_FUNHELP, JxqyScriptEditor::OnFunctionHelpShow)
    EVT_MENU(MYID_SHOWLINENUMBER, JxqyScriptEditor::OnLineNumberShow)
    EVT_MENU(MYID_JXQY2, JxqyScriptEditor::OnFunctionFileChoose)
    EVT_MENU(MYID_YYCS, JxqyScriptEditor::OnFunctionFileChoose)
    EVT_MENU(MYID_XJXQY, JxqyScriptEditor::OnFunctionFileChoose)
END_EVENT_TABLE()

JxqyScriptEditor::JxqyScriptEditor(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(JxqyScriptEditor)
    wxBoxSizer* BoxSizer1;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,600));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    m_AuiBook = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_CLOSE_ON_ALL_TABS|wxAUI_NB_DEFAULT_STYLE);
    BoxSizer1->Add(m_AuiBook, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    m_menuBar = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu1, wxID_NEW, _T("�½��ĵ�\tCtrl+N"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem2);
    MenuItem1 = new wxMenuItem(Menu1, wxID_OPEN, _T("��...\tCtrl+O"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuItem3 = new wxMenuItem(Menu1, wxID_SAVE, _T("����\tCtrl+S"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu1, wxID_SAVEAS, _T("���Ϊ...\tCtrl+Alt+S"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem5 = new wxMenuItem(Menu1, MYID_SAVEALL, _T("��������\tCtrl+Shift+S"), _T("�������д򿪵��ļ�"), wxITEM_NORMAL);
    Menu1->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(Menu1, MYID_CLOSE, _T("�ر�\tCtrl+W"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem6);
    MenuItem7 = new wxMenuItem(Menu1, MYID_CLOSEALL, _T("�ر�����\tShift+Esc"), _T("�ر����д򿪵��ĵ�"), wxITEM_NORMAL);
    Menu1->Append(MenuItem7);
    MenuItem8 = new wxMenuItem(Menu1, wxID_EXIT, _T("�˳�\tAlt+F4"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem8);
    m_menuBar->Append(Menu1, _T("�ļ�"));
    Menu2 = new wxMenu();
    MenuItem9 = new wxMenuItem(Menu2, MYID_FONTSETTING, _T("��������..."), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem9);
    MenuItem10 = new wxMenuItem(Menu2, MYID_COLOURSETTING, _T("��ɫ����..."), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem10);
    Menu2->AppendSeparator();
    MenuItem11 = new wxMenuItem(Menu2, MYID_WORDWRAP, _T("�Զ�����"), wxEmptyString, wxITEM_CHECK);
    Menu2->Append(MenuItem11);
    MenuItem12 = new wxMenuItem(Menu2, MYID_FUNHELP, _T("��ʾ��������"), wxEmptyString, wxITEM_CHECK);
    Menu2->Append(MenuItem12);
    MenuItem16 = new wxMenuItem(Menu2, MYID_SHOWLINENUMBER, _T("��ʾ����"), wxEmptyString, wxITEM_CHECK);
    Menu2->Append(MenuItem16);
    Menu2->AppendSeparator();
    MenuItem13 = new wxMenuItem(Menu2, MYID_JXQY2, _T("������Ե��"), wxEmptyString, wxITEM_RADIO);
    Menu2->Append(MenuItem13);
    MenuItem14 = new wxMenuItem(Menu2, MYID_YYCS, _T("��Ӱ��˵"), wxEmptyString, wxITEM_RADIO);
    Menu2->Append(MenuItem14);
    MenuItem15 = new wxMenuItem(Menu2, MYID_XJXQY, _T("�½�����Ե"), wxEmptyString, wxITEM_RADIO);
    Menu2->Append(MenuItem15);
    m_menuBar->Append(Menu2, _T("����"));
    SetMenuBar(m_menuBar);
    SetSizer(BoxSizer1);
    Layout();
    Center();

    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&JxqyScriptEditor::OnFrameClose);
    //*)
    Init();
    AddNewFile();

    m_menuBar->Check(MYID_WORDWRAP, m_cfg.IsWordWrap());
    m_menuBar->Check(MYID_FUNHELP, m_cfg.IsFunctionHelpShow());
    m_menuBar->Check(MYID_SHOWLINENUMBER, m_cfg.IsShowLineNumber());
    switch(m_cfg.GetLexerType())
    {
    case ConfigManager::LEX_JXQY2:
        m_menuBar->Check(MYID_JXQY2, true);
        break;
    case ConfigManager::LEX_YYCS:
        m_menuBar->Check(MYID_YYCS, true);
        break;
    case ConfigManager::LEX_XJXQY:
        m_menuBar->Check(MYID_XJXQY, true);
        break;
    default:
        break;
    }
}

JxqyScriptEditor::~JxqyScriptEditor()
{
    //(*Destroy(JxqyScriptEditor)
    //*)
    Uninit();
}
void JxqyScriptEditor::Init()
{

    m_AuiBook->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &JxqyScriptEditor::OnPageClose, this);
}

void JxqyScriptEditor::Uninit()
{

    m_AuiBook->Unbind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &JxqyScriptEditor::OnPageClose, this);
}


void JxqyScriptEditor::OnNewFile(wxCommandEvent& event)
{
    AddNewFile();
}

void JxqyScriptEditor::OnOpenFile(wxCommandEvent& event)
{
    wxFileDialog *fileDlg = GetFileOpenDialog();

    if(fileDlg->ShowModal() == wxID_OK)
    {
        int openedIdx = GetOpenedFile(fileDlg->GetPath());
        if(openedIdx != -1)
        {
            m_AuiBook->SetSelection(openedIdx);
        }
        else
        {
            JxqyStc *stc = GetInitlizedJxqyStc();
            stc->OpenFromFile(fileDlg->GetPath());
            m_AuiBook->AddPage(stc, stc->GetFileName(), true);
            m_AuiBook->SetPageToolTip(m_AuiBook->GetPageIndex(stc), stc->GetFilePath());
        }
    }
    delete fileDlg;
}

void JxqyScriptEditor::OnSave(wxCommandEvent& event)
{
    SavePageToFile();
}

void JxqyScriptEditor::OnSaveAs(wxCommandEvent& event)
{
	wxFileDialog *fileDlg = GetFileSaveDialog(GetPageTiltleClean());
	if(fileDlg->ShowModal() == wxID_OK)
	{
		SavePageToFile(-1, fileDlg->GetPath());
	}
	delete fileDlg;
}

void JxqyScriptEditor::OnSaveAll(wxCommandEvent& event)
{
	size_t counts = m_AuiBook->GetPageCount();
	int cur_sel = m_AuiBook->GetSelection();
	JxqyStc *stc;
	for(size_t i = 0; i < counts; i++)
	{
		stc = (JxqyStc*) m_AuiBook->GetPage(i);
		if(stc)
		{
			if(stc->GetModify() || stc->FilePathEmpty())
			{
				if(stc->FilePathEmpty())
					m_AuiBook->SetSelection(i);
				SavePageToFile((int)i);
			}
		}
	}
	m_AuiBook->SetSelection(cur_sel);
}

void JxqyScriptEditor::OnClose(wxCommandEvent& event)
{
	ClosePage();
}

void JxqyScriptEditor::OnCloseAll(wxCommandEvent& event)
{
	CloseAllPage();
}

void JxqyScriptEditor::OnExit(wxCommandEvent& event)
{
	this->Close();
}

void JxqyScriptEditor::OnFontSetting(wxCommandEvent& event)
{
    wxFontData data;
    data.SetInitialFont(m_cfg.GetDefaultFont());
    wxFontDialog fontdlg(this, data);
    if(fontdlg.ShowModal() == wxID_OK)
    {
        m_cfg.SetDefaultFont(fontdlg.GetFontData().GetChosenFont());
        m_cfg.WriteConfig();
    }
    ResetOpenedPageStyle();
}

void JxqyScriptEditor::OnColourSetting(wxCommandEvent& event)
{
    ColourSettingDialog dlg(this);
    if(dlg.ShowModal() == wxID_OK)
    {
        m_cfg.ReadConfig();
        ResetOpenedPageStyle();
    }
}
void JxqyScriptEditor::OnWordWrap(wxCommandEvent& event)
{
    if(m_cfg.IsWordWrap())
    {
        m_cfg.SetWordWrap(false);
    }
    else
    {
        m_cfg.SetWordWrap(true);
    }
    m_cfg.WriteConfig();
    ResetOpenedPageStyle();
}
void JxqyScriptEditor::OnLineNumberShow(wxCommandEvent& event)
{
    if(m_cfg.IsShowLineNumber())
    {
        m_cfg.SetShowLineNumber(false);
    }
    else
    {
        m_cfg.SetShowLineNumber(true);
    }
    m_cfg.WriteConfig();
    ResetOpenedPageStyle();
}
void JxqyScriptEditor::OnFunctionHelpShow(wxCommandEvent& event)
{
    if(m_cfg.IsFunctionHelpShow())
    {
        m_cfg.SetFunctionHelpShow(false);
    }
    else
    {
        m_cfg.SetFunctionHelpShow(true);
    }
    m_cfg.WriteConfig();
    ResetOpenedPageStyle();
}

void JxqyScriptEditor::OnPageClose(wxAuiNotebookEvent& event)
{
    int pageIdx = event.GetSelection();
    JxqyStc *stc = (JxqyStc*)m_AuiBook->GetPage(pageIdx);
    if(stc)
    {
        if(stc->GetModify())
        {
            bool veto = false;
            wxString title = GetPageTiltleClean(pageIdx);
            wxString msg = wxT("�����ļ� \"") + title + wxT("\" ?");
            int ret = wxMessageBox(msg, wxT("����"), wxCANCEL | wxYES_NO | wxICON_QUESTION |wxCENTER);
            if(ret == wxYES)
            {
                SavePageToFile(pageIdx, wxEmptyString, title, &veto);
                if(veto) event.Veto();
            }
            else if(ret == wxCANCEL)
                event.Veto();
        }
    }
}

void JxqyScriptEditor::AddNewFile()
{
    JxqyStc *stc = GetInitlizedJxqyStc();
    m_AuiBook->AddPage(stc, wxT("δ����"), true);
    m_AuiBook->SetPageToolTip(m_AuiBook->GetPageIndex(stc), wxT("δ����"));
}


JxqyStc* JxqyScriptEditor::GetInitlizedJxqyStc()
{
    JxqyStc *stc = new JxqyStc(this);
    SetJxqyStcStyleFromSetting(stc);
    return stc;
}
void JxqyScriptEditor::SetJxqyStcStyleFromSetting(JxqyStc* stc)
{
//	stc->SetLexer(wxSTC_LEX_JXQY);
    stc->SetFunctionKeywordFromFile(m_cfg.GetLexerFilePath());

    //Default style
    wxFont defFont = m_cfg.GetDefaultFont();
    stc->StyleSetFont(wxSTC_STYLE_DEFAULT, defFont);
    stc->StyleSetForeground(wxSTC_STYLE_DEFAULT, m_cfg.GetStyleForegroundColour(0));
    stc->StyleSetBackground(wxSTC_STYLE_DEFAULT, m_cfg.GetStyleBackgroundColour(0));
    stc->StyleClearAll();

    //Text style
    stc->StyleSetForeground(wxSTC_JXQY_COMMENT, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_COMMENT));
    stc->StyleSetForeground(wxSTC_JXQY_FUNCTION, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_FUNCTION));
    stc->StyleSetForeground(wxSTC_JXQY_OPERATOR, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_OPERATOR));
    stc->StyleSetForeground(wxSTC_JXQY_STRING, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_STRING));
    stc->StyleSetForeground(wxSTC_JXQY_GOTOPOS, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_GOTOPOS));
    stc->StyleSetForeground(wxSTC_JXQY_VARIABLE, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_VARIABLE));
    stc->StyleSetForeground(wxSTC_JXQY_NUMBER, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_NUMBER));

    stc->StyleSetBackground(wxSTC_JXQY_COMMENT, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_COMMENT));
    stc->StyleSetBackground(wxSTC_JXQY_FUNCTION, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_FUNCTION));
    stc->StyleSetBackground(wxSTC_JXQY_OPERATOR, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_OPERATOR));
    stc->StyleSetBackground(wxSTC_JXQY_STRING, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_STRING));
    stc->StyleSetBackground(wxSTC_JXQY_GOTOPOS, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_GOTOPOS));
    stc->StyleSetBackground(wxSTC_JXQY_VARIABLE, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_VARIABLE));
    stc->StyleSetBackground(wxSTC_JXQY_NUMBER, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_NUMBER));

    //Indentation
    stc->SetTabWidth(4);
    stc->SetIndent(4);
    stc->SetUseTabs(true);
    stc->SetTabIndents (false);
    stc->SetBackSpaceUnIndents(false);
    stc->SetIndentationGuides(true);

    //Autocompletaion
    stc->AutoCompSetIgnoreCase(true);
    stc->AutoCompSetMaxWidth(50);

    //Line number
    if(m_cfg.IsShowLineNumber())
    {
        stc->StyleSetForeground(wxSTC_STYLE_LINENUMBER, m_cfg.GetStyleForegroundColour(wxSTC_STYLE_LINENUMBER));
        stc->StyleSetBackground(wxSTC_STYLE_LINENUMBER, m_cfg.GetStyleBackgroundColour(wxSTC_STYLE_LINENUMBER));
        stc->ShowLineNumber(true);
        stc->SetMarginWidth( 2, 0 );
        stc->SetMarginWidth( 1, 5 );
        stc->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
        stc->SetMarginWidth( 0, stc->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_9999") ) );
    }
    else
    {
        stc->SetMarginWidth( 0, 0 );
        stc->SetMarginWidth( 1, 0 );
        stc->SetMarginWidth( 2, 0 );
    }

    //Wordwrap
    if(m_cfg.IsWordWrap())
        stc->SetWrapMode(wxSTC_WRAP_WORD);
    else
        stc->SetWrapMode(wxSTC_WRAP_NONE);

    //FunctionHelpShow
    stc->SetShowCallTip(m_cfg.IsFunctionHelpShow());
}

void JxqyScriptEditor::ResetOpenedPageStyle()
{
    size_t count = m_AuiBook->GetPageCount();
    JxqyStc *stc;
    for(size_t i = 0; i < count; i++)
    {
        stc = (JxqyStc*)m_AuiBook->GetPage(i);
        if(stc)
        {
            SetJxqyStcStyleFromSetting(stc);
        }
    }
}
void JxqyScriptEditor::OnFunctionFileChoose(wxCommandEvent& event)
{
    int id = event.GetId();
    if(id == MYID_JXQY2)
        m_cfg.SetLexerType(ConfigManager::LEX_JXQY2);
    else if(id == MYID_YYCS)
        m_cfg.SetLexerType(ConfigManager::LEX_YYCS);
    else if(id == MYID_XJXQY)
        m_cfg.SetLexerType(ConfigManager::LEX_XJXQY);
    m_cfg.WriteConfig();
    ResetOpenedPageStyle();
}

int JxqyScriptEditor::GetOpenedFile(const wxString& path)
{
    size_t count = m_AuiBook->GetPageCount();
    JxqyStc *stc;
    for(size_t i = 0; i < count; i++)
    {
        stc = (JxqyStc*)m_AuiBook->GetPage(i);
        if(stc)
        {
            if(stc->GetFilePath() == path)
                return i;
        }
    }
    return -1;
}
void JxqyScriptEditor::SetPageChanged(bool changed, int idx)
{
    if(idx == -1)
        idx = m_AuiBook->GetSelection();
    wxString title = m_AuiBook->GetPageText(idx);
    if(!title.IsEmpty())
    {
        if(changed && title[0] != wxChar('*'))
        {
            title = wxT("*") + title;
            m_AuiBook->SetPageText(idx, title);
        }
        else if(!changed && title[0] == wxChar('*'))
        {
            title = title.Mid(1);
            m_AuiBook->SetPageText(idx, title);
        }
    }
}
bool JxqyScriptEditor::SavePageToFile(int idx, const wxString& path, const wxString &defaultFileName, bool *veto)
{
    wxLogNull lognull;
    if(m_AuiBook->GetPageCount() == 0) return false;

    if(idx == -1)
        idx = m_AuiBook->GetSelection();
    if(idx == -1) return false;

    if(veto) *veto = false;

    int ret;
    bool successed = true, cancled = false;
    wxString filename = defaultFileName.IsEmpty() ?  GetPageTiltleClean(idx) : defaultFileName;
    JxqyStc *stc = (JxqyStc*)m_AuiBook->GetPage(idx);
    if(stc)
    {
        if(stc->FilePathEmpty() && path.IsEmpty())
        {
            wxFileDialog *fileDlg = GetFileSaveDialog(filename);

            if(fileDlg->ShowModal() == wxID_OK)
            {
                if(!stc->SaveToFile(fileDlg->GetPath()))
                {
                    successed = false;
                }
            }
            else
            {
            	successed = false;
            	cancled = true;
            }
            delete fileDlg;
        }
        else if(!stc->FilePathEmpty() && path.IsEmpty())
        {
            if(!stc->Save())
            {
                successed = false;
            }
        }
        else if(!path.IsEmpty())
        {
            if(!stc->SaveToFile(path))
            {
                successed = false;
            }
        }
    }
    else
        successed = false;

    if(successed == false)
    {
        if(veto)
        {
        	if(cancled)
			{
				*veto = true;
			}
			else
			{
				ret = VOTE_SAVE_ERROR_MESSAGEDIALOG;
				if(ret == wxNO) *veto = true;
			}
        }
        else
        {
            if(!cancled)SAVE_ERROR_MESSAGEDIALOG;
        }
    }
    else
	{
		ResetPageTitleTooltip(idx);
	}

    return successed;
}

wxString JxqyScriptEditor::GetPageTiltleClean(int idx)
{
    if(idx == -1) idx = m_AuiBook->GetSelection();
    wxString title = m_AuiBook->GetPageText(idx);
    if(!title.IsEmpty() && title[0] == wxChar('*') )
    {
        title = title.Mid(1);
    }
    return title;
}
void JxqyScriptEditor::ResetPageTitleTooltip(int idx)
{
	if(idx == -1) idx = m_AuiBook->GetSelection();
	JxqyStc *stc = (JxqyStc*)m_AuiBook->GetPage(idx);
	if(stc)
	{
		m_AuiBook->SetPageText(idx, stc->GetFileName());
		m_AuiBook->SetPageToolTip(idx, stc->GetFilePath());
	}
}
bool JxqyScriptEditor::ClosePage(int idx, bool deletePage)
{
	if(idx == -1) idx = m_AuiBook->GetSelection();
	wxAuiNotebookEvent auievent;
	auievent.SetSelection(idx);
	auievent.SetEventType(wxEVT_AUINOTEBOOK_PAGE_CLOSE);
	//auievent.SetEventObject(this);
	m_AuiBook->GetEventHandler()->ProcessEvent(auievent);
	if(auievent.IsAllowed())
	{
		if(deletePage)m_AuiBook->DeletePage(idx);
		return true;
	}
	else
		return false;
}
bool JxqyScriptEditor::CloseAllPage()
{
	size_t count = m_AuiBook->GetPageCount();
    JxqyStc *stc;
    for(size_t i = 0; i < count; i++)
    {
        stc = (JxqyStc*)m_AuiBook->GetPage(i);
        if(stc)
        {
        	m_AuiBook->SetSelection(i);
            if(!ClosePage(i, false)) return false;
        }
    }
    m_AuiBook->DeleteAllPages();
    return true;
}


void JxqyScriptEditor::OnFrameClose(wxCloseEvent& event)
{
	if(CloseAllPage()) this->Destroy();
}
