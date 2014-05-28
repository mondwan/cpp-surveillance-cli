

#include "stdafx.h"
#include "ClientDemo.h"
#include "CruiseEdit.h"



IMPLEMENT_DYNAMIC(CCruiseEdit, CDialog)

CCruiseEdit::CCruiseEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CCruiseEdit::IDD, pParent)
	, cruise_edit(0)
{

}

CCruiseEdit::~CCruiseEdit()
{
}

void CCruiseEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_cruisepresent);
	DDX_Control(pDX, IDC_EDIT1, m_edit_cruise);
}


BEGIN_MESSAGE_MAP(CCruiseEdit, CDialog)
END_MESSAGE_MAP()


BOOL CCruiseEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	m_mybuttonAddPreset.SubclassDlgItem(IDC_BUTTONADDPRESENT,this);
	m_mybuttonAddPreset.SetType(1000);
	m_mybuttonDelPreset.SubclassDlgItem(IDC_BUTTONDELETEPRESENT,this);
	m_mybuttonDelPreset.SetType(1000);
	m_mybuttonClearTour.SubclassDlgItem(IDC_BUTTONDELETECRUISE,this);
	m_mybuttonClearTour.SetType(1000);
	
	CString temp;
	for (int i=1;i<33;i++)
	{
		temp.Format("%d",i);
		m_cruisepresent.AddString(temp);
	}
	m_cruisepresent.SetCurSel(0);
	return true;
}