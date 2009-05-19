/*
 * AboutDlg.cpp : �u���O�N���C�A���g BloGolEe
 *      �Ő�(�o�[�W�����ԍ�)�\��
 *
 *          written by H.Tsujimura  2 Mar 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/AboutDlg.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/02/18 23:11 Tsujimura543
 * copyright �\�����A�b�v�f�[�g
 * 
 * 3     08/02/18 23:08 Tsujimura543
 * �o�[�W�����������\�[�X����擾���ĕ\������悤�ɂ���
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * �t�B�b�N�X
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 */

#include "blogolee.h"
#include "AboutDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/AboutDlg.cpp 1     09/05/14 3:47 tsupo $";
#endif

#if (WINVER >= 0x0500)
//#define IDC_HAND    MAKEINTRESOURCE(32649)
#ifdef IDC_HAND
#undef IDC_HAND
#endif
#endif /* WINVER >= 0x0500 */
#define IDC_HAND    IDC_HAND2

/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���Ă��� CAboutDlg �_�C�A���O

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
    m_hCursor = AfxGetApp()->LoadCursor( IDC_HAND );
}

CAboutDlg::~CAboutDlg()
{
    m_cFont.DeleteObject();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_WEB_URL, OnWebUrl)
	ON_BN_CLICKED(IDC_MAIL_ADDR, OnMailAddr)
	ON_WM_SETCURSOR()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CAboutDlg::OnWebUrl() 
{
	CString cmd;
	cmd.LoadString( IDS_WEB_URL );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

void CAboutDlg::OnMailAddr() 
{
	CString cmd;
	cmd.LoadString( IDS_MAIL_ADDR );
    ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
}

BOOL CAboutDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if ( nHitTest == HTCLIENT ) {
        // Web �� URL�����[���A�h���X�Ƀ}�E�X�|�C���^��������A
        // �w�J�[�\����\������
		DWORD   dwPos = GetMessagePos();
		WORD    wX    = LOWORD( dwPos );
		WORD    wY    = HIWORD( dwPos );
		CPoint  poCursor( wX, wY );
		CRect   rcClient;

        CStatic *s = (CStatic *)GetDlgItem( IDC_MAIL_ADDR );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }

        s = (CStatic *)GetDlgItem( IDC_WEB_URL );
        s->GetWindowRect( &rcClient );
        if ( (wX >= rcClient.left) && (wX <= rcClient.right)  &&
             (wY >= rcClient.top)  && (wY <= rcClient.bottom)    ) {
			SetCursor( m_hCursor );
            return TRUE;
        }
	}

    return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CAboutDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        // Web �� URL�ƃ��[���A�h���X�������t���ŕ\������
        LOGFONT tLogFont;
        CFont   *cWndFont;

        cWndFont = GetFont(); 
        cWndFont->GetLogFont( &tLogFont );
        tLogFont.lfUnderline = 1;
        m_cFont.CreateFontIndirect( &tLogFont );

        CStatic *s = (CStatic *)GetDlgItem( IDC_MAIL_ADDR );
        s->SetFont( &m_cFont, TRUE );

        s = (CStatic *)GetDlgItem( IDC_WEB_URL );
        s->SetFont( &m_cFont, TRUE );

        CString str;
        str.LoadString( IDS_VERSION );
        s = (CStatic *)GetDlgItem( IDC_VERSION );
        s->SetWindowText( str );
    }
}
