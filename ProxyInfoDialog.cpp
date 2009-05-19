/*
 * ProxyInfoDialog.cpp : �u���O�N���C�A���g BloGolEe
 *      proxy���ݒ�_�C�A���O
 *
 *          written by H.Tsujimura  9 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/ProxyInfoDialog.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/03/10 5:22 Tsujimura543
 * ���[�U���ƃp�X���[�h�̎w�肪�K�v��proxy�T�[�o�ɂ��b��I�ɑΉ����Ă݂�
 * 
 * 1     07/03/09 19:28 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#include "blogolee.h"
#include "ProxyInfoDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/ProxyInfoDialog.cpp 1     09/05/14 3:47 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProxyInfoDialog �_�C�A���O

CProxyInfoDialog::CProxyInfoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProxyInfoDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProxyInfoDialog)
	m_proxyServerName = _T("");
	m_proxyPortNumber = 0;
	m_proxyUserName = _T("");
	m_proxyPassword = _T("");
	//}}AFX_DATA_INIT
}

void CProxyInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProxyInfoDialog)
	DDX_Text(pDX, IDC_EDIT_PROXY_SERVER_NAME, m_proxyServerName);
	DDV_MaxChars(pDX, m_proxyServerName, 384);
	DDX_Text(pDX, IDC_EDIT_PROXY_PORT_NUMBER, m_proxyPortNumber);
	DDV_MinMaxUInt(pDX, m_proxyPortNumber, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PROXY_USER_NAME, m_proxyUserName);
	DDV_MaxChars(pDX, m_proxyUserName, 32);
	DDX_Text(pDX, IDC_EDIT_PROXY_PASSWORD, m_proxyPassword);
	DDV_MaxChars(pDX, m_proxyPassword, 32);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProxyInfoDialog, CDialog)
	//{{AFX_MSG_MAP(CProxyInfoDialog)
	ON_EN_UPDATE(IDC_EDIT_PROXY_PORT_NUMBER, OnUpdateEditProxyPortNumber)
	ON_EN_UPDATE(IDC_EDIT_PROXY_SERVER_NAME, OnUpdateEditProxyServerName)
	ON_WM_SHOWWINDOW()
	ON_EN_UPDATE(IDC_EDIT_PROXY_USER_NAME, OnUpdateEditProxyUserName)
	ON_EN_UPDATE(IDC_EDIT_PROXY_PASSWORD, OnUpdateEditProxyPassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProxyInfoDialog �ǉ����\�b�h

void    CProxyInfoDialog::switchOK()
{
    CButton *q = (CButton *)GetDlgItem( IDOK );
    if ( (m_proxyServerName.GetLength() > 0) && (m_proxyPortNumber > 0) )
        q->EnableWindow( TRUE );
    else
        q->EnableWindow( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// CProxyInfoDialog ���b�Z�[�W �n���h��

void CProxyInfoDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow )
        switchOK();	
}

void CProxyInfoDialog::OnUpdateEditProxyServerName() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_SERVER_NAME );
    p->GetWindowText( m_proxyServerName );
    switchOK();
}

void CProxyInfoDialog::OnUpdateEditProxyPortNumber() 
{
    CString portNumberString;
    long    portNumber;
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_PORT_NUMBER );
    p->GetWindowText( portNumberString );
	
    if ( portNumberString.GetLength() > 0 ) {
        portNumber = atol( (const char *)portNumberString );
        if ( portNumber > 0 ) {
            m_proxyPortNumber = portNumber;
            switchOK();
        }
    }
}

void CProxyInfoDialog::OnUpdateEditProxyUserName() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_USER_NAME );
    p->GetWindowText( m_proxyUserName );
}

void CProxyInfoDialog::OnUpdateEditProxyPassword() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_PROXY_PASSWORD );
    p->GetWindowText( m_proxyPassword );
}
