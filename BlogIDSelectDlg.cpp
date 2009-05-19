/*
 * BlogIDSelectDlg.cpp : ブログクライアント BloGolEe
 *      Blog ID 選択ダイアログ
 *
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードをそのまま流用
 *
 * $Log: /comm/blogolee/BlogIDSelectDlg.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * フィックス
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe 暫定版 (動作確認済み)
 */

#include "blogolee.h"
#include "BlogIDSelectDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/BlogIDSelectDlg.cpp 1     09/05/14 3:47 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg ダイアログ


CBlogIDSelectDlg::CBlogIDSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlogIDSelectDlg::IDD, pParent)
{
    m_blogList   = NULL;
    m_numOfBlogs = 0;

	//{{AFX_DATA_INIT(CBlogIDSelectDlg)
	m_blogIDlistIndex = -1;
	//}}AFX_DATA_INIT
}


void CBlogIDSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlogIDSelectDlg)
	DDX_Control(pDX, IDC_LIST_BLOGID, m_blogIDlist);
	DDX_LBIndex(pDX, IDC_LIST_BLOGID, m_blogIDlistIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBlogIDSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CBlogIDSelectDlg)
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(IDC_LIST_BLOGID, OnSelchangeListBlogid)
	ON_LBN_DBLCLK(IDC_LIST_BLOGID, OnDblclkListBlogID)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg 独自追加コード

void    CBlogIDSelectDlg::initialize( BLOGINF *blogList, int numOfBlogs )
{
    if ( blogList && (numOfBlogs > 0) ) {
        if ( m_blogList )
            delete [] m_blogList;
        m_blogList   = new BLOGINF [numOfBlogs];
        m_numOfBlogs = numOfBlogs;

        for ( int i = 0; i < numOfBlogs; i++ )
            m_blogList[i] = blogList[i];
    }
}

void    CBlogIDSelectDlg::initBlogList()
{
    char    *p;

    for ( int i = 0; i < m_numOfBlogs; i++ ) {
        p = utf2sjis( m_blogList[i].blogName );
        m_blogIDlist.AddString( p ? p : m_blogList[i].blogName );
    }
}


/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg メッセージ ハンドラ

void CBlogIDSelectDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
    if ( m_blogIDlistIndex == -1 ) {
        // blog ID 未選択の場合
        MessageBox( "blog を選択してください    ",
                    "blog 未選択", MB_OK|MB_ICONWARNING );
        return;
    }
	
	CDialog::OnOK();
}

void CBlogIDSelectDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
    if ( bShow && m_blogList ) {
        m_blogIDlist.InitStorage( m_numOfBlogs,
                                  BLOGOLEE_MAX_BLOG_NAME_LENGTH );
        initBlogList();
    }	
}

void CBlogIDSelectDlg::OnSelchangeListBlogid() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    int location = m_blogIDlist.GetCurSel();
    if ( location >= 0 )
        m_blogIDlistIndex = location;
}

void CBlogIDSelectDlg::OnDblclkListBlogID() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
    OnSelchangeListBlogid();
    OnOK();
}
