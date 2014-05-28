#pragma once
#include "afxwin.h"
#include "ColorButton.h"



class CCruiseEdit : public CDialog
{
	DECLARE_DYNAMIC(CCruiseEdit)

public:
	CCruiseEdit(CWnd* pParent = NULL);   
	virtual ~CCruiseEdit();


	enum { IDD = IDD_CRUISEEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cruisepresent;
	int cruise_edit;
	CEdit m_edit_cruise;
	CColorButton m_mybuttonAddPreset;
	CColorButton m_mybuttonDelPreset;
	CColorButton m_mybuttonClearTour;
	
};
