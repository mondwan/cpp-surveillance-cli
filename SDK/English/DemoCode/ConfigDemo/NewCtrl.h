#pragma once

#define NOMODIFY_SIZE 0
#define MODIFY_SIZE 1
// CNewCtrl

class CNewCtrl : public CWnd
{
	DECLARE_DYNAMIC(CNewCtrl)

public:
	CNewCtrl();
	virtual ~CNewCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	BOOL  m_bIsMove;
	BOOL  m_bIsPush;
	CPoint m_OldPoint;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	CRect m_rtMove;
	void SetMoveRect(CRect rtMove);
	int m_nFlags;
};


