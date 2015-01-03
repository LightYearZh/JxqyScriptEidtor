#include "TalkListPanel.h"

TalkListPanel::TalkListPanel(wxWindow *parent)
	:TalkListPanelBase(parent),
	m_talkList()
{
	m_columnIndex = m_listView->AppendTextColumn( wxT("����"), wxDATAVIEW_CELL_EDITABLE, 60, wxALIGN_CENTER );
	m_columnPortrait = m_listView->AppendTextColumn( wxT("ͷ��"), wxDATAVIEW_CELL_EDITABLE, 40, wxALIGN_CENTER );
	m_columnText = m_listView->AppendTextColumn( wxT("�ı�"), wxDATAVIEW_CELL_EDITABLE, 550, wxALIGN_LEFT );

	InitFromTalkList();
}

TalkListPanel::~TalkListPanel()
{
	//dtor
}

void TalkListPanel::InitFromTalkList()
{
	wxVector<wxVariant> data;
	TalkIndex::iterator end = m_talkList.End();
	for(TalkIndex::iterator it = m_talkList.Begin();
		it != end;
		it++)
	{
		data.clear();
		data.push_back(wxVariant(wxString::Format(wxT("%d"), it->first)));
		data.push_back(wxVariant(wxString::Format(wxT("%d"), it->second.PortraitIndex)));
		data.push_back(wxVariant(it->second.Text));
		m_listView->AppendItem(data);
	}
}

void TalkListPanel::OnClose(wxCloseEvent& event)
{
	this->Show(false);
}
