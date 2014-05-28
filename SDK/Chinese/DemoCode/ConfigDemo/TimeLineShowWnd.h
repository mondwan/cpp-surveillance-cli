// RecLineShowWnd.h: interface for the CRecLineShowWnd class.

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECLINESHOWWND_H__82887AFD_2546_4CEB_BB18_9125840D025E__INCLUDED_)
#define AFX_RECLINESHOWWND_H__82887AFD_2546_4CEB_BB18_9125840D025E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
typedef struct _REC_COLOR
{
	COLORREF clColor[100];

}REC_COLOR , *pREC_COLOR;
*/

#define COLOURNUM 720//24 * 60 / 2
class CTimeLineShowWnd : public CWnd  
{
public:
	CTimeLineShowWnd();
	virtual ~CTimeLineShowWnd();
	

	void InsertDrawSpace(DWORD dwBgSpace , DWORD dwEdSpace ,COLORREF clDrawColor);

	void DeleteDrawSpace(DWORD dwBgSpace , DWORD dwEdSpace);
	

	void DrawAllSpace(COLORREF clDrawColor);

	void CleanAllSpace();


	DWORD  GetColorPercent(COLORREF clDrawColor);


	COLORREF GetSpaceColor(DWORD dwGetSpace);


	void SetShowScale(BOOL bShow);


	void SetMiddleText(char * pchText , COLORREF clText = RGB(0,0,0));


	void Draw();
protected:

	//{{AFX_MSG(CSubWindow)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	COLORREF *m_pclRecColor;

	CString  m_MidText;	
	COLORREF m_MidTextColor;

	BOOL     m_bShowScale;
};

#endif // !defined(AFX_RECLINESHOWWND_H__82887AFD_2546_4CEB_BB18_9125840D025E__INCLUDED_)
