#include "JxqyScriptEditor.h"
#include "helperFun.h"

#include "wx/msgdlg.h"
#include "wx/filedlg.h"

//(*InternalHeaders(JxqyScriptEditor)
#include <wx/string.h>
//*)

//(*IdInit(JxqyScriptEditor)
const long JxqyScriptEditor::ID_AUINOTEBOOK1 = wxNewId();
const long JxqyScriptEditor::MYID_SAVEALL = wxNewId();
const long JxqyScriptEditor::MYID_CLOSE = wxNewId();
const long JxqyScriptEditor::MYID_CLOSEALL = wxNewId();
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
END_EVENT_TABLE()

JxqyScriptEditor::JxqyScriptEditor(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(JxqyScriptEditor)
    wxBoxSizer* BoxSizer1;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,600));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    m_AuiBook = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_CLOSE_ON_ALL_TABS|wxAUI_NB_DEFAULT_STYLE);
    BoxSizer1->Add(m_AuiBook, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
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
    MenuBar1->Append(Menu1, _T("�ļ�"));
    Menu2 = new wxMenu();
    MenuBar1->Append(Menu2, _T("����"));
    SetMenuBar(MenuBar1);
    SetSizer(BoxSizer1);
    Layout();
    //*)
    Init();
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
	JxqyStc *stc = GetInitlizedJxqyStc();
    m_AuiBook->AddPage(stc, wxT("δ����"));
}

void JxqyScriptEditor::OnOpenFile(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnSave(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnSaveAs(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnSaveAll(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnClose(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnCloseAll(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnExit(wxCommandEvent& event)
{

}
void JxqyScriptEditor::OnPageClose(wxAuiNotebookEvent& event)
{
    int pageIdx = event.GetSelection();
    JxqyStc *stc = (JxqyStc*)m_AuiBook->GetPage(pageIdx);
    if(stc)
    {
        if(stc->GetModify())
        {
            wxString title = m_AuiBook->GetPageText(pageIdx);
            wxString msg = wxT("�����ļ� \"") + title + wxT("\" ?");
            int ret = wxMessageBox(msg, wxT("����"), wxCANCEL | wxYES_NO | wxICON_QUESTION |wxCENTER);
            if(ret == wxYES)
            {
                if(stc->FilePathEmpty())
                {
                    wxFileDialog fileDlg(this,
                                         wxT("�����ļ�"),
                                         wxEmptyString,
                                         title,
                                         wxT("txt(*.txt)|*.txt|�����ļ�(*.*)|*.*"),
                                         wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
                    if(fileDlg.ShowModal() == wxID_OK)
                    {
                        if(!stc->SaveToFile(fileDlg.GetPath()))
                        {
                            wxMessageBox(wxT("����ʧ�ܣ�"), wxT("����"), wxOK | wxCENTER | wxICON_ERROR);
                            event.Veto();
                        }
                    }
                }
                else
                {
                    if(!stc->Save())
                    {
                        wxMessageBox(wxT("����ʧ�ܣ�"), wxT("����"), wxOK | wxCENTER | wxICON_ERROR);
                        event.Veto();
                    }
                }
            }
            else if(ret == wxCANCEL)
				event.Veto();
        }
    }
}
JxqyStc* JxqyScriptEditor::GetInitlizedJxqyStc()
{
	JxqyStc *stc = new JxqyStc(m_AuiBook);
	stc->SetFunctionKeywordFromFile(m_cfg.GetLexerFilePath());
	return stc;
}


