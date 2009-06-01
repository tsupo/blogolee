/*
 * EditAmazonAccessKey.cpp : ブログクライアント BloGolEe
 *      Amazon Access Key 設定ダイアログ
 *          written by H.Tsujimura  1 Jun 2009
 *
 *      Copyright (c) 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/EditAmazonAccessKey.cpp $
 * 
 * 1     09/06/02 3:49 tsupo
 * VSSサーバ拠点を変更
 * 
 * 2     09/06/01 21:40 Tsujimura543
 * Amazon Product Advertising API 対応 (動作確認済み)
 * 
 * 1     09/06/01 20:05 Tsujimura543
 * 最初の版
 */

#include "blogolee.h"
#include "EditAmazonAccessKey.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/EditAmazonAccessKey.cpp 1     09/06/02 3:49 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EditAmazonAccessKey ダイアログ

EditAmazonAccessKey::EditAmazonAccessKey(CWnd* pParent /*=NULL*/)
	: CDialog(EditAmazonAccessKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditAmazonAccessKey)
	m_accessKeyID = _T("");
	m_accessKeySecret = _T("");
	//}}AFX_DATA_INIT
}

void EditAmazonAccessKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditAmazonAccessKey)
	DDX_Text(pDX, IDC_EDIT_ACCESS_KEY_ID, m_accessKeyID);
	DDV_MaxChars(pDX, m_accessKeyID, 128);
	DDX_Text(pDX, IDC_EDIT_ACCESS_KEY_SECRET, m_accessKeySecret);
	DDV_MaxChars(pDX, m_accessKeySecret, 128);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(EditAmazonAccessKey, CDialog)
	//{{AFX_MSG_MAP(EditAmazonAccessKey)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditAmazonAccessKey メッセージ ハンドラ

void EditAmazonAccessKey::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ACCESS_KEY_ID );
        p->SetWindowText( m_accessKeyID );

        p = (CEdit *)GetDlgItem( IDC_EDIT_ACCESS_KEY_SECRET );
        p->SetWindowText( m_accessKeySecret );
    }
}

void EditAmazonAccessKey::OnOK() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ACCESS_KEY_ID );
    p->GetWindowText( m_accessKeyID );

    p = (CEdit *)GetDlgItem( IDC_EDIT_ACCESS_KEY_SECRET );
    p->GetWindowText( m_accessKeySecret );

    if ( m_accessKeyID.GetLength()     > 0 &&
         m_accessKeySecret.GetLength() > 0    )
    	CDialog::OnOK();
}
