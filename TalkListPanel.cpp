#include "TalkListPanel.h"
#include "wx/log.h"
#include "wx/msgdlg.h"
#include "wx/filedlg.h"

TalkListPanel::TalkListPanel(wxWindow *parent)
	:TalkListPanelBase(parent),
	m_talkList()
{
	this->SetTitle(wxT("�Ի��б�"));

	m_columnIndex = m_listView->AppendTextColumn( wxT("����"), wxDATAVIEW_CELL_EDITABLE, 60, wxALIGN_CENTER );
	m_columnPortrait = m_listView->AppendTextColumn( wxT("ͷ��"), wxDATAVIEW_CELL_EDITABLE, 40, wxALIGN_CENTER );
	m_columnText = m_listView->AppendTextColumn( wxT("�ı�"), wxDATAVIEW_CELL_EDITABLE, 550, wxALIGN_LEFT );

	m_bAdd->SetToolTip(wxT("��ĩβ���"));
	m_bInsert->SetToolTip(wxT("�ڵ�ǰѡ��������"));
	m_bDelete->SetToolTip(wxT("ɾ����ǰѡ����"));
	m_stGoto->SetLabel(wxT("������"));
	m_bSaveTxt->SetLabel(wxT("����Ϊ�ı�..."));
	m_bSaveTxt->SetToolTip(wxT("�����txt�ļ��������ڸ����[Content\\TalkIndex.txt]"));
	m_bSave->SetLabel(wxT("����"));

	InitFromTalkList();
}

TalkListPanel::~TalkListPanel()
{
	//dtor
}

void TalkListPanel::InitFromTalkList()
{
	TalkIndex::iterator end = m_talkList.End();
	for(TalkIndex::iterator it = m_talkList.Begin();
		it != end;
		it++)
	{
		AppendItem(&(*it));
	}
}

wxVector<wxVariant> TalkListPanel::CreateItemData(int itemIndex, int portraitIndex, const wxString& text)
{
	wxVector<wxVariant> data;
	data.push_back(wxVariant(wxString::Format(wxT("%d"), itemIndex)));
	data.push_back(wxVariant(wxString::Format(wxT("%d"), portraitIndex)));
	data.push_back(wxVariant(text));
	return data;
}

int TalkListPanel::AppendItem(TalkDetail* detail)
{
	return AppendItem(detail->Index, detail->PortraitIndex, detail->Text);
}

int TalkListPanel::AppendItem(int itemIndex, int portraitIndex, const wxString& text)
{
	m_listView->AppendItem(CreateItemData(itemIndex, portraitIndex, text));
	return m_listView->GetItemCount() - 1;
}

int TalkListPanel::InsertItem(int row, int itemIndex, int portraitIndex, const wxString& text)
{
	m_listView->InsertItem(row, CreateItemData(itemIndex, portraitIndex, text));
	return row;
}

void TalkListPanel::SelectAndShowRow(int row)
{
	if(row < 0) return;
	m_listView->SelectRow(row);
	m_listView->EnsureVisible(m_listView->RowToItem(row));
}

void TalkListPanel::OnClose(wxCloseEvent& event)
{
	this->Show(false);
}

int TalkListPanel::GetItemIndex(int row)
{
	if(row == wxNOT_FOUND) return -1;
	wxVariant value;
	m_listView->GetValue(value, row, INDEX_COLUMN);
	long index;
	if(!value.GetString().ToLong(&index)) return -1;
	return index;
}

void TalkListPanel::OnItemEdited(wxDataViewEvent& event)
{
	int column = event.GetColumn();
	int row = m_listView->ItemToRow(event.GetItem());
	if(column == -1 || row == wxNOT_FOUND) return;

	TalkDetail *detail = m_talkList.GetItem(row);
	if(detail == NULL)
	{
		wxLogError(wxT("OnItemEdited index error!"));
	};

	long num;
	wxString str = event.GetValue().GetString();
	bool isNum = str.ToLong(&num);

	switch(column)
	{
	case INDEX_COLUMN:
		if(isNum)
		{
			detail->Index = num;
		}
		else
		{
			event.Veto();
		}
		break;
	case PORTRAIT_COLUMN:
		{
			if(isNum)
			{
				detail->PortraitIndex = num;
			}
			else
			{
				event.Veto();
			}
		}
		break;
	case TEXT_COLUMN:
		{
			detail->Text = str;
		}
		break;
	}
}

void TalkListPanel::OnAdd(wxCommandEvent& event)
{
	SelectAndShowRow(AppendItem(m_talkList.AppendItem()));
}

void TalkListPanel::OnInsert(wxCommandEvent& event)
{
	int row = m_listView->GetSelectedRow();
	if(row == wxNOT_FOUND) return;
	TalkDetail *detail = m_talkList.AddAfter(row);
	if(!detail) return;

	SelectAndShowRow(InsertItem(row+1, detail->Index, detail->PortraitIndex, detail->Text));
}

void TalkListPanel::OnDelete(wxCommandEvent& event)
{
	int row = m_listView->GetSelectedRow();
	if(row == wxNOT_FOUND) return;
	m_talkList.Delete(row);
	m_listView->DeleteItem(row);
	SelectAndShowRow(row);
}

void TalkListPanel::OnGoto(wxCommandEvent& event)
{
    SelectAndShowRow(m_talkList.GetListIndex(m_scGoto->GetValue()));
}

void TalkListPanel::OnSave(wxCommandEvent& event)
{
	if(wxMessageBox(wxT("������ļ������޸ġ�ȷ�����棿"),
					wxMessageBoxCaptionStr,
					wxYES_NO | wxCENTER | wxICON_QUESTION)
		 == wxYES)
	{
		m_talkList.Save();
	}
}

void TalkListPanel::OnSaveTxt(wxCommandEvent& event)
{
	wxFileDialog dialog(this,
            wxT("�����ļ�"),
            wxEmptyString,
            wxEmptyString,
            wxT("txt(*.txt)|*.txt|�����ļ�(*.*)|*.*"),
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if(dialog.ShowModal() == wxID_OK)
	{
		m_talkList.SaveAsTxt(dialog.GetPath());
	}
}
