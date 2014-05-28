// ChannelNameSet.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ChannelNameSet.h"
#include "ClientDemo5Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChannelNameSet dialog


CChannelNameSet::CChannelNameSet(CWnd* pParent /*=NULL*/)
	: CDialog(CChannelNameSet::IDD, pParent)
{

	//{{AFX_DATA_INIT(CChannelNameSet)
	//}}AFX_DATA_INIT

	m_nChannelTotal=NET_MAX_CHANNUM;
 	for (int i = 0; i < NET_MAX_CHANNUM; ++i)
 	{
 		m_edit[i] = NULL;
 		m_static[i] = NULL;
 	}
	m_pBuf=NULL;
	m_nWidth=0;
	m_nHeight=0;
}


void CChannelNameSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CChannelNameSet, CDialog)
	//{{AFX_MSG_MAP(CChannelNameSet)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChannelNameSet message handlers

BOOL CChannelNameSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CChannelNameSet::CleanAll()
{

	int i = 0;
	for ( i = 0; i < m_nChannelTotal; ++i )
	{
 		if ( m_edit[i] && m_static[i])
 		{
			delete m_edit[i];
			delete m_static[i];
			m_edit[i] = NULL;
			m_static[i] = NULL;
		}
	}
	//OutputDebugString("\ntest\n");
}
void CChannelNameSet::InitDlgInfo(SDK_ChannelNameConfigAll *pChannelName,int nbyChanNum )
{

	m_nChannelTotal = nbyChanNum;
	if ( pChannelName != NULL)
	{
		memcpy( &m_ChannelName ,pChannelName ,sizeof(m_ChannelName));
	}else
	{
		memset( &m_ChannelName ,0 ,sizeof(m_ChannelName));
	}

	BOOL value=InitWindow();
	if (value)
	{
		for (int i = 0; i < m_nChannelTotal; i++)
		{
			
			m_edit[i]->SetWindowText(pChannelName->channelTitle[i]);
		}
	}

	

	
}
BOOL CChannelNameSet::InitWindow()
{
	CRect rcStatic;
	CRect rcEdit;
	CString Num;
#define MAX_CHANNEL_PER_ROW 3
	int nSect = m_nChannelTotal / MAX_CHANNEL_PER_ROW;
	int nOffset = m_nChannelTotal % MAX_CHANNEL_PER_ROW;
	GetDlgItem(IDC_STATIC1)->GetWindowRect(rcStatic);
	ScreenToClient(rcStatic);
	GetDlgItem(IDC_STATIC1)->MoveWindow(&rcStatic);
	
	GetDlgItem(IDC_EDIT_C1)->GetWindowRect(rcEdit);
	ScreenToClient(rcEdit);
	GetDlgItem(IDC_EDIT_C1)->MoveWindow(&rcEdit);
	
	GetDlgItem(IDC_EDIT_C1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	rcStatic.left += 10;
	rcStatic.right += 40;
	rcEdit.left += 40;
	rcEdit.right += 100;
	for (int i = 0; i < nSect; i++)
	{
		CRect orgrcStatic = rcStatic;
		CRect orgrcEdit = rcEdit;
		//	char *Num;
		for (int j = 0; j < MAX_CHANNEL_PER_ROW; j++)
		{

			Num.Format("%s%d",_CS("ConfigManage.CAM"),1+j+i*MAX_CHANNEL_PER_ROW);
			if (m_edit[j+i*MAX_CHANNEL_PER_ROW]==NULL&&m_static[j+i*MAX_CHANNEL_PER_ROW] == NULL)
			{
		
			m_edit[j+i*MAX_CHANNEL_PER_ROW] = new CEdit();
			m_static[j+i*MAX_CHANNEL_PER_ROW] = new CStatic();
			m_edit[j+i*MAX_CHANNEL_PER_ROW]->Create(SS_BLACKFRAME|WS_BORDER|WS_CHILD|WS_VISIBLE,orgrcEdit,this,IDC_EDIT_CNS+j+i*MAX_CHANNEL_PER_ROW);
			m_static[j+i*MAX_CHANNEL_PER_ROW]->Create(Num,WS_CHILD|WS_VISIBLE,orgrcStatic,this,IDC_STATIC_CNS+j+i*MAX_CHANNEL_PER_ROW);
			orgrcEdit.left += 140;
			orgrcEdit.right += 140;
			orgrcStatic.left += 140;
			orgrcStatic.right += 140;
			m_edit[j+i*MAX_CHANNEL_PER_ROW]->LimitText(8);
			}
		}
		if (i < nSect)
		{
			rcStatic.top += 30;
			rcStatic.bottom += 30;
			rcEdit.top += 30;
			rcEdit.bottom += 30;
		}
	}
	if (nOffset>0)
	{
		CRect orgrcStatic = rcStatic;
		CRect orgrcEdit = rcEdit;
	
		for (int i = 0; i < nOffset; i++)
		{
			Num.Format("%s%d",_CS("ConfigManage.CAM"),1+i+nSect*MAX_CHANNEL_PER_ROW);
			if (m_edit[i+nSect*MAX_CHANNEL_PER_ROW] == NULL&&m_static[i+nSect*MAX_CHANNEL_PER_ROW] == NULL)
			{
		
			m_edit[i+nSect*MAX_CHANNEL_PER_ROW] = new CEdit();
			m_static[i+nSect*MAX_CHANNEL_PER_ROW] = new CStatic();
			m_edit[i+nSect*MAX_CHANNEL_PER_ROW]->Create(SS_BLACKFRAME|WS_BORDER|WS_CHILD|WS_VISIBLE,orgrcEdit,this,IDC_EDIT_CNS+i+nSect*MAX_CHANNEL_PER_ROW);
			m_static[i+nSect*MAX_CHANNEL_PER_ROW]->Create(Num,WS_CHILD|WS_VISIBLE,orgrcStatic,this,IDC_STATIC_CNS+i+nSect*MAX_CHANNEL_PER_ROW);
			
			orgrcEdit.left += 140;
			orgrcEdit.right += 140;
			orgrcStatic.left += 140;
			orgrcStatic.right += 140;
			m_edit[i+nSect*MAX_CHANNEL_PER_ROW]->LimitText(8);
			}
		}
	}
	return TRUE;
}

void CChannelNameSet::SaveChannelNS()
{
	CString ChannelName;
	for (int i = 0; i < m_nChannelTotal; i++)
	{
		if (m_edit[i] != NULL)
		{
			m_edit[i]->GetWindowText(ChannelName);
			strcpy( m_ChannelName.channelTitle[i], ChannelName.GetBuffer(0) );
		}
	}
}

//浮点数据转换为固定浮点数。
FIXED FixedFromDouble(double d)
{
	long l;
	l = (long) (d * 65536L);
	return *(FIXED *)&l;
}
void SetMat(LPMAT2 lpMat)
{
	lpMat->eM11 = FixedFromDouble(2);
	lpMat->eM12 = FixedFromDouble(0);
	lpMat->eM21 = FixedFromDouble(0);
	lpMat->eM22 = FixedFromDouble(2);
}

void CChannelNameSet::freeData()
{
	if ( m_pBuf )
	{
		free( m_pBuf );
		m_pBuf = NULL;
	}
}
//获取一个字符的点阵信息
int CChannelNameSet::GetBuffer(int ch, int nFont)
{
	freeData();
	
	//创建字体。
	CFont   hFont; 
	hFont.CreateFont(nFont,0,0,0, 
		FW_NORMAL,0, 
		0,0,DEFAULT_CHARSET, 
		OUT_TT_PRECIS,CLIP_TT_ALWAYS,   
		PROOF_QUALITY   ,DEFAULT_PITCH,   
		"宋体 "); 
	
	//设置字体到当前设备。
	CDC*pDC = GetDC();
	CFont* pOldFont = pDC->SelectObject( &hFont);
	
	//设置字体图形变换矩阵         
	MAT2 mat2;
	SetMat(&mat2);
	
	GLYPHMETRICS gm;
	
	//获取这个字符图形需要的字节的大小。
	DWORD dwNeedSize = pDC->GetGlyphOutline(ch,GGO_BITMAP,&gm,0,NULL,&mat2);
	if (dwNeedSize > 0 && dwNeedSize < 0xFFFF)
	{
		if( ch == '\t' ) 
			return 4 * gm.gmCellIncX; 
		
		m_pBuf = (byte*)(malloc(dwNeedSize));
		if ( m_pBuf)
		{
			//获取字符图形的数据到缓冲区。
			pDC->GetGlyphOutline(ch,GGO_BITMAP,&gm,dwNeedSize,m_pBuf,&mat2);
			m_nWidth = gm.gmBlackBoxX;
			m_nHeight = gm.gmBlackBoxY;
		}
	}
	else if( dwNeedSize == 0xFFFFFFFF || dwNeedSize == 0 || ch < 0x21 ) 
	{ 
		//要生成的文字是空格或tab只需返回宽度 
		if( ch == ' ') 
			return gm.gmCellIncX; 
		else   if( ch == '\t' ) 
			return 4 * gm.gmCellIncX; 
		else 
		{
			UINT nSubstituteChar = ' '; 
			pDC-> GetGlyphOutline( nSubstituteChar, GGO_NATIVE, &gm, 
				0, NULL, &mat2 ); 
			if( ch < 256 ) //西文 
				return gm.gmCellIncX; 
			else //中文空两个空格 
				return 2*gm.gmCellIncX; 
		} 
	} 
	else
	{
		dwNeedSize = 0;
	}
	
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);
	
	return dwNeedSize;
}
#include <winsock.h>	//htons需要
void CChannelNameSet::GetData()//获取点阵信息
{
	if (m_nChannelTotal == 1)
	{
		//临时记录信息。高度最大24
		char g_tmp[24][256] = {0};
		int g_len = 0;		//所以字体宽度的字节数
		int g_Height = 24;	//字体高度，暂时固定

		int nFont = 12;
		int nSize = strlen(m_ChannelName.channelTitle[0]);

		for ( int i = 0; i < nSize; )
		{
			int nRet = 0;
			if ( m_ChannelName.channelTitle[0][i] >= 0 )
			{
				while(1)
				{
					nRet = GetBuffer(m_ChannelName.channelTitle[0][i], nFont);
					if ( nRet && m_nHeight > g_Height )
					{
						nFont --;
					}
					else
						break;
				}
			}
			else
			{
				short *pbuf = (short *)(m_ChannelName.channelTitle[0] + i);
				nRet = GetBuffer(htons(pbuf[0]), nFont);
				while(1)
				{
					nRet = GetBuffer(htons(pbuf[0]), nFont);
					if ( nRet && m_nHeight > g_Height )
					{
						nFont --;
					}
					else
						break;
				}
				
				i ++;
			}
			i ++ ;
			
			if ( nRet > 0 )
			{
				if ( m_pBuf == NULL )
				{
					//说明是特殊字符了
					int widthByte = ((nRet +7) >> 3);	//宽度代表的字节数，以8为单位
					g_len += widthByte;
				}
				else
				{
					//如果设置的字体高度大于24，超过范围，改小字体
					int nPos = (g_Height-m_nHeight)/2;	//高度偏移量，使得字体居中
					int widthTrue = nRet/m_nHeight;		//实际buf中占用的宽度字节
					int widthByte = ((m_nWidth +7) >> 3);	//汉字点阵占用的宽度，以8为单位
					
					for ( int iTmp = 0; iTmp < m_nHeight; iTmp ++ )
					{
						memcpy( g_tmp[iTmp + nPos] + g_len, m_pBuf + iTmp*widthTrue, widthByte);
					}
					g_len += widthByte;
				}
			}
		}

		//确保是8的倍数，一个字节8位
		int nLen = ((g_len +3) >> 2) << 2; 

		freeData();
		m_pBuf = new byte[g_Height*nLen];

		for ( int iTmp = 0; iTmp < g_Height; iTmp ++ )
		{
			memcpy(m_pBuf + iTmp*nLen, g_tmp[iTmp], nLen);
		}
		m_nWidth = nLen*8;
		m_nHeight = g_Height;

	}
}

void CChannelNameSet::OnButtonApply() 
{
 	SaveChannelNS();
	GetData();
	CClientDemo5Dlg*MainDlg=((CClientDemo5Dlg*)AfxGetMainWnd());
	MainDlg->m_pBuf=m_pBuf;
//	memcpy(MainDlg->m_pBuf, m_pBuf, m_nWidth*m_nHeight/8);
	MainDlg->m_nWidth=m_nWidth;
	MainDlg->m_nHeigth=m_nHeight;
 	((CClientDemo5Dlg*)AfxGetMainWnd())->setChannelNS(&m_ChannelName);
}

void CChannelNameSet::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetChannelNS();
}

void CChannelNameSet::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CleanAll();
}
