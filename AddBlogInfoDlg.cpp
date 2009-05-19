/*
 * AddBlogInfoDlg.cpp : ブログクライアント BloGolEe
 *      ブログ情報追加ダイアログ
 *
 *          written by H.Tsujimura  18 Mar 2005 / 2 Mar 2007
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードをそのまま流用
 *
 * $Log: /comm/blogolee/AddBlogInfoDlg.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 11    09/03/23 17:51 Tsujimura543
 * Windows Live Spaces およびウェブリブログの blogID の扱いに関する修正
 * 
 * 10    09/03/20 22:48 Tsujimura543
 * はてなダイアリー(の Atom API での投稿)に対応した
 * 
 * 9     09/03/16 20:49 Tsujimura543
 * ウェブリブログの XMLRPC API 対応作業開始
 * 
 * 8     07/11/30 2:03 Tsujimura543
 * (1) Jugem、ヤプログ!、ドリコムブログの XML-RPC API 経由ではない方の
 *     諸々を削除
 * (2) しまにてぃ内日記関連の諸々を削除 (2007年11月30日でサービス終了)
 * 
 * 7     07/10/29 20:34 Tsujimura543
 * (1) XML-RPC API 経由での ヤプログ! へのアクセスに対応
 * (2) XML-RPC API 経由でのドリコムブログのカテゴリ一覧取得、カテゴリ設定
 *     に対応
 * 
 * 6     07/03/12 18:31 Tsujimura543
 * selectBlog() を導入し、リファクタリング
 * 
 * 5     07/03/12 15:23 Tsujimura543
 * BLOGKIND列挙体から値 sweetBox を削除
 * 
 * 4     07/03/12 5:07 Tsujimura543
 * Visual Studio 2005 でもビルドできるようにコードを修正
 * 
 * 3     07/03/03 0:04 Tsujimura543
 * 不要になったコメントを削除
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * フィックス
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe 暫定版 (動作確認済み)
 */

#include "blogolee.h"
#include "AddBlogInfoDlg.h"
#include "EndPointDlg.h"
#include "BlogIDSelectDlg.h"
#include "utility.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/AddBlogInfoDlg.cpp 1     09/05/14 3:47 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddBlogInfoDlg ダイアログ


CAddBlogInfoDlg::CAddBlogInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddBlogInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddBlogInfoDlg)
	m_blogID = _T("");
	m_blogName = _T("");
	m_blogPassword = _T("");
	m_blogUserName = _T("");
	m_endpointURL = _T("");
	m_blogURL = _T("");
	//}}AFX_DATA_INIT

    m_blogInfo = NULL;
    m_blogKind = unset;
    m_useCbox  = false;
    m_mode     = true;
}


void CAddBlogInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddBlogInfoDlg)
	DDX_Control(pDX, IDC_COMBO_BLOG_LIST, m_blogKindList);
	DDX_Text(pDX, IDC_EDIT_BLOGID, m_blogID);
	DDV_MaxChars(pDX, m_blogID, 48);
	DDX_Text(pDX, IDC_EDIT_BLOGNAME, m_blogName);
	DDV_MaxChars(pDX, m_blogName, 127);
	DDX_Text(pDX, IDC_EDIT_BLOGPASSWORD, m_blogPassword);
	DDV_MaxChars(pDX, m_blogPassword, 16);
	DDX_Text(pDX, IDC_EDIT_BLOGUSERNAME, m_blogUserName);
	DDV_MaxChars(pDX, m_blogUserName, 32);
	DDX_Text(pDX, IDC_EDIT_ENDPOINTURL, m_endpointURL);
	DDV_MaxChars(pDX, m_endpointURL, 384);
	DDX_Text(pDX, IDC_EDIT_BLOGURL, m_blogURL);
	DDV_MaxChars(pDX, m_blogURL, 384);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddBlogInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CAddBlogInfoDlg)
	ON_BN_CLICKED(IDC_BUTTON_MOREINFO, OnButtonMoreInfo)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_BLOG_LIST, OnSelchangeComboBlogList)
	ON_EN_UPDATE(IDC_EDIT_BLOGUSERNAME, OnUpdateEditBlogUserName)
	ON_EN_UPDATE(IDC_EDIT_BLOGPASSWORD, OnUpdateEditBlogPassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddBlogInfoDlg 追加メソッド

void    CAddBlogInfoDlg::switchEndpointURL()
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );

    if ( m_mode )
        m_endpointURL = "";

    if ( (m_blogKind == bloggerAPI)  ||
         (m_blogKind == metaWeblog)  ||
         (m_blogKind == mtAPI)       ||
         (m_blogKind == atomAPI)     ||
         (m_blogKind == newPostOnly)    )
        p->SetReadOnly( FALSE );
    else
        p->SetReadOnly( TRUE );

    if ( (m_blogKind == typepad)      ||
         (m_blogKind == typepadJapan) ||
         (m_blogKind == cocolog)      ||
         (m_blogKind == cocologFree)  ||
         (m_blogKind == blogzine)     ||
         (m_blogKind == newsHandler)  ||
         (m_blogKind == ameblo)       ||
         (m_blogKind == seesaa)       ||
         (m_blogKind == netLaputa)    ||
         (m_blogKind == blogG)        ||
         (m_blogKind == fc2blog)      ||
         (m_blogKind == gooBlog)      ||
         (m_blogKind == msnSpaces)    ||
         (m_blogKind == drecomX)      ||
         (m_blogKind == yaplogX)      ||
         (m_blogKind == jugemX)       ||
         (m_blogKind == webryX)       ||
         (m_blogKind == livedoor)     ||
         (m_blogKind == lovelog)      ||
         (m_blogKind == sonet)        ||
         (m_blogKind == vox)          ||
         (m_blogKind == hatena)       ||
         (m_blogKind == blogger)      ||
         (m_blogKind == movableType)     ) {
        int blogKindIndex = -1;
        int i;

        for ( i = 0; i < m_blogInfo->m_numOfBlogKinds; i++ ) {
            if ( m_blogInfo->m_blogKindInfo[i].blogKind == (blogKind)m_blogKind )
                break;
        }
        blogKindIndex = i;
        if ( m_endpointURL.GetLength() == 0 )
            m_endpointURL = m_blogInfo->m_blogKindInfo[blogKindIndex].endpointURL;
    }
    else
        m_endpointURL = "";

    p->SetWindowText( m_endpointURL );
}

void    CAddBlogInfoDlg::switchBlogID()
{
    CEdit   *cp = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );

    if ( m_mode )
        m_blogID = "";
    cp->SetWindowText( m_blogID );

    if ( m_useCbox ) {
        m_blogID = "0";
        cp->SetWindowText( m_blogID );
    }
    else if ( /* (m_blogKind == movableType)  || */
                 (m_blogKind == bloggerAPI)   ||
                 (m_blogKind == metaWeblog)   ||
                 (m_blogKind == mtAPI)        ||
                 (m_blogKind == atomAPI)         )
        cp->SetReadOnly( FALSE );
    /*
    else if ( (m_blogKind == typepad)      ||
              (m_blogKind == typepadJapan) ||
              (m_blogKind == cocolog)      ||
              (m_blogKind == cocologFree)  ||
              (m_blogKind == blogzine)     ||
              (m_blogKind == newsHandler)  ||
              (m_blogKind == ameblo)       ||
              (m_blogKind == seesaa)       ||
              (m_blogKind == netLaputa)    ||
              (m_blogKind == blogG)        ||
              (m_blogKind == fc2blog)      ||
              (m_blogKind == gooBlog)      ||
              (m_blogKind == msnSpaces)    ||
              (m_blogKind == drecomX)      ||
              (m_blogKind == yaplogX)      ||
              (m_blogKind == jugemX)       ||
              (m_blogKind == webryX)       ||
              (m_blogKind == livedoor)     ||
              (m_blogKind == lovelog)      ||
              (m_blogKind == sonet)        ||
              (m_blogKind == vox)          ||
              (m_blogKind == hatena)       ||
              (m_blogKind == blogger)         )
        cp->SetReadOnly( TRUE );
    */
    else
        cp->SetReadOnly( TRUE );
}

void    CAddBlogInfoDlg::switchBlogName()
{
    CEdit   *cp = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );

    if ( m_mode )
        m_blogName = "";

    if ( m_useCbox ) {
        m_blogName = "BlogPet 飼育箱";
        cp->SetReadOnly( TRUE );
    }
    else if ( /* (m_blogKind == movableType)  || */
                 (m_blogKind == bloggerAPI)   ||
                 (m_blogKind == metaWeblog)   ||
                 (m_blogKind == mtAPI)        ||
                 (m_blogKind == atomAPI)         )
        cp->SetReadOnly( FALSE );
    else if ( (m_blogKind == typepad)      ||
              (m_blogKind == typepadJapan) ||
              (m_blogKind == cocolog)      ||
              (m_blogKind == cocologFree)  ||
              (m_blogKind == blogzine)     ||
              (m_blogKind == newsHandler)  ||
              (m_blogKind == ameblo)       ||
              (m_blogKind == seesaa)       ||
              (m_blogKind == netLaputa)    ||
              (m_blogKind == blogG)        ||
              (m_blogKind == fc2blog)      ||
              (m_blogKind == gooBlog)      ||
              (m_blogKind == msnSpaces)    ||
              (m_blogKind == drecomX)      ||
              (m_blogKind == yaplogX)      ||
              (m_blogKind == jugemX)       ||
              (m_blogKind == webryX)       ||
              (m_blogKind == livedoor)     ||
              (m_blogKind == lovelog)      ||
              (m_blogKind == sonet)        ||
              (m_blogKind == vox)          ||
              (m_blogKind == hatena)       ||
              (m_blogKind == blogger)         ) {
        cp->SetReadOnly( TRUE );
    }
    else if ( m_blogKind == kinugasa ) {
        m_blogName = "キヌガサ";
        cp->SetReadOnly( TRUE );
    }
    else if ( m_blogKind == mixi ) {
        m_blogName = "mixi";
        cp->SetReadOnly( TRUE );
    }
    else if ( m_blogKind == fc2network ) {
        m_blogName = "FC2NETWORK";
        cp->SetReadOnly( TRUE );
    }
    else if ( m_blogKind == colors ) {
        m_blogName = "COLORS";
        cp->SetReadOnly( TRUE );
    }
    else if ( m_blogKind == openPne ) {
        m_blogName = "OpenPNE";
        cp->SetReadOnly( TRUE );
    }
    else
        cp->SetReadOnly( TRUE );

    cp->SetWindowText( m_blogName );
}

void        CAddBlogInfoDlg::switchBlogURL()
{
    CEdit   *cp = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
    
    if ( m_mode )
        m_blogURL = "";

    if ( m_blogKind == kinugasa )
        m_blogURL = "http://kinugasa.cc/diary.php";
    else if ( m_blogKind == mixi )
        m_blogURL = "http://mixi.jp/list_diary.pl";
    else if ( m_blogKind == fc2network )
        m_blogURL = "http://network.fc2.com/diary/index.php";
    else if ( m_blogKind == colors )
        m_blogURL = "http://clrs.jp/list_diary.php";
    else if ( m_blogKind == openPne )
        m_blogURL = "http://openpne.jp/?m=pc&a=page_fh_diary_list";

    cp->SetWindowText( m_blogURL );
}

void    CAddBlogInfoDlg::switchMoreInfo()
{
    CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_MOREINFO );

    if ( (m_blogKind == movableType)  ||
         (m_blogKind == bloggerAPI)   ||
         (m_blogKind == metaWeblog)   ||
         (m_blogKind == mtAPI)        ||
         (m_blogKind == atomAPI)      ||
         (m_blogKind == typepad)      ||
         (m_blogKind == typepadJapan) ||
         (m_blogKind == cocolog)      ||
         (m_blogKind == cocologFree)  ||
         (m_blogKind == blogzine)     ||
         (m_blogKind == newsHandler)  ||
         (m_blogKind == ameblo)       ||
         (m_blogKind == seesaa)       ||
         (m_blogKind == netLaputa)    ||
         (m_blogKind == blogG)        ||
         (m_blogKind == fc2blog)      ||
         (m_blogKind == gooBlog)      ||
         (m_blogKind == msnSpaces)    ||
         (m_blogKind == drecomX)      ||
         (m_blogKind == yaplogX)      ||
         (m_blogKind == jugemX)       ||
         (m_blogKind == webryX)       ||
         (m_blogKind == livedoor)     ||
         (m_blogKind == lovelog)      ||
         (m_blogKind == sonet)        ||
         (m_blogKind == vox)          ||
         (m_blogKind == hatena)       ||
         (m_blogKind == blogger)      ||
         (m_blogKind == exciteBlog)   ||
         (m_blogKind == echoo)        ||
         (m_blogKind == rakuten)         ) {
        if ( (m_blogUserName.GetLength() > 0) &&
             (m_blogPassword.GetLength() > 0)    )
            bp->EnableWindow( TRUE );
        else
            bp->EnableWindow( FALSE );
    }
    else
        bp->EnableWindow( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// CAddBlogInfoDlg メッセージ ハンドラ

void CAddBlogInfoDlg::OnButtonMoreInfo() 
{
	// 追加情報取得
    CEdit   *p;

#define MAX_BLOGS       30  /* 同一システム内最大設置可能blog数 */

    if ( (m_blogKind == movableType) ||
         (m_blogKind == metaWeblog)  ||
         (m_blogKind == mtAPI)       ||
         (m_blogKind == atomAPI)        ) {
        // エンドポイントURLの自動取得を試みる
        //  -- トップページ URL を取得
        char    topPageURL[MAX_URLLENGTH + 1];
        CEndPointDlg    dialog;
        int res = dialog.DoModal();
        if ( (res == IDOK) && (dialog.m_endPointURL.GetLength() > 0) ) {
            strcpy( topPageURL, (const char *)dialog.m_endPointURL );
            m_blogURL = topPageURL;
            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
            p->SetWindowText( m_blogURL );

            // -- エンドポイントURL と blog ID を取得
            char    id[MAX_BLOGIDLENGTH + 1];
            char    *url = NULL;

            memset( id, 0x00, MAX_BLOGIDLENGTH + 1 );
            if ( m_blogKind == atomAPI ) {
                CWaitCursor cur;    // マウスカーソルを砂時計表示
                url = getEndpointURLbyAutoDiscoveryOnAtomAPI(
                                                     topPageURL, id );
            }
            else {
                CWaitCursor cur;    // マウスカーソルを砂時計表示
                url = getEndpointURLbyAutoDiscovery( topPageURL, id );
            }

            if ( url && *url ) {
                MessageBox( "エンドポイントURLの取得に成功しました。    ",
                            "取得成功", MB_OK|MB_ICONINFORMATION );
                m_endpointURL = url;
                p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
                p->SetWindowText( m_endpointURL );

                if ( id[0] ) {
                    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
                    m_blogID = id;
                    p->SetWindowText( m_blogID );

                    // -- blog名の取得
                    BLOGINF blogInfo[MAX_BLOGS];
                    int     numOfBlogs = MAX_BLOGS;
                    int     r;

                    setTargetURL( m_endpointURL );
                    if ( m_blogKind == atomAPI ) {
                        //  --- Atom API 系の場合
                        CWaitCursor cur;    // マウスカーソルを砂時計表示
                        r = getBlogIDsOnAtomAPI( m_blogUserName, m_blogPassword,
                                                 &numOfBlogs, blogInfo );
                    }
                    else {
                        //  --- blogger API 系の場合
                        CWaitCursor cur;    // マウスカーソルを砂時計表示
                        r = getBlogIDs( m_blogUserName, m_blogPassword,
                                        &numOfBlogs, blogInfo );    /* blogger API */
                    }

                    if ( r == 1 ) {
                        MessageBox( "blog名の取得に成功しました。    ",
                                    "取得成功", MB_OK|MB_ICONINFORMATION );
                        m_blogName = utf2sjis( blogInfo[0].blogName );  /* 確定 */
                        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
                        p->SetWindowText( (const char *)m_blogName );
                    }
                    else if ( r > 1 ) {
                        for ( int i = 0; i < r; i++ ) {
                            if ( !strcmp( (const char *)m_blogID, blogInfo[i].blogID ) ) {
                                MessageBox( "blog名の取得に成功しました。    ",
                                            "取得成功", MB_OK|MB_ICONINFORMATION );
                                m_blogName = utf2sjis( blogInfo[i].blogName );  /* 確定 */
                                p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
                                p->SetWindowText( (const char *)m_blogName );
                                break;
                            }
                        }
                    }
                    else {
                        MessageBox( "blog名の取得に失敗しました。\n\n"
                                    "ユーザ名、パスワードが正しいか確認してください。    ",
                                    "設定確認", MB_OK|MB_ICONWARNING );
                    }
                }
            }
            else
                MessageBox( "エンドポイントURLの取得に失敗しました。\n\n"
                            "ユーザ名、パスワードが正しいか確認してください。    ",
                            "設定確認", MB_OK|MB_ICONWARNING );
        }
    }
    else if ( (m_blogKind == bloggerAPI)   ||
              (m_blogKind == typepad)      ||
              (m_blogKind == typepadJapan) ||
              (m_blogKind == cocolog)      ||
              (m_blogKind == cocologFree)  ||
              (m_blogKind == blogzine)     ||
              (m_blogKind == newsHandler)  ||
              (m_blogKind == ameblo)       ||
              (m_blogKind == seesaa)       ||
              (m_blogKind == netLaputa)    ||
              (m_blogKind == blogG)        ||
              (m_blogKind == fc2blog)      ||
              (m_blogKind == gooBlog)      ||
              (m_blogKind == msnSpaces)    ||
              (m_blogKind == drecomX)      ||
              (m_blogKind == yaplogX)      ||
              (m_blogKind == jugemX)       ||
              (m_blogKind == webryX)       ||
              (m_blogKind == livedoor)     ||
              (m_blogKind == lovelog)      ||
              (m_blogKind == sonet)        ||
              (m_blogKind == vox)          ||
              (m_blogKind == hatena)       ||
              (m_blogKind == blogger)         ) {
        // blog ID の自動取得を試みる
        //  -- 複数の blog が存在する場合は一覧表示し、
        //     ユーザに選択してもらう

        if ( m_blogPassword.GetLength() <= 0 ) {
            // blog ID の取得にはパスワード必須
            MessageBox( "blog ID の自動取得を試みます。\n"
                        "blog ID の自動取得には、「blog にloginする"
                        "ときのパスワード」が必要です。    \n"
                        "blog にloginするときのパスワードを設定して"
                        "ください。",
                        "設定確認", MB_OK|MB_ICONWARNING );
            return;
        }

        BLOGINF blogInfo[MAX_BLOGS];
        int     numOfBlogs = MAX_BLOGS;
        int     r;

        /* --- 投稿可能な blog 一覧の取得 */
        if ( m_blogKind == jugemX ) {
            if ( m_blogUserName.GetLength() > 0 ) {
                char        url[MAX_URLLENGTH];
                const char  *q = strchr( m_endpointURL, '$' );

                if ( q )
                    q++;
                else
                    q = ".jugem.jp/admin/xmlrpc.php";
                sprintf( url, "http://%s%s",
                         (const char *)m_blogUserName,
                         q );

                m_endpointURL = url;
                p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
                p->SetWindowText( m_endpointURL );
            }
        }
        if ( m_blogKind == hatena ) {
            if ( strstr( m_endpointURL, "{hatenaID}" ) ) {
                m_endpointURL =
                    "http://d.hatena.ne.jp/" + m_blogUserName + "/atom/blog";
                p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
                p->SetWindowText( m_endpointURL );
            }
        }

        blogInfo[0].blogName[0] = NUL;
        setTargetURL( m_endpointURL );
        if ( (m_blogKind == livedoor) ||
             (m_blogKind == lovelog)  ||
             (m_blogKind == sonet)    ||
             (m_blogKind == ameblo)   ||
             (m_blogKind == vox)      ||
             (m_blogKind == hatena)   ||
             (m_blogKind == blogger)     ) {
            //  --- Atom API 系の場合
            CWaitCursor cur;    // マウスカーソルを砂時計表示
            r = getBlogIDsOnAtomAPI( m_blogUserName, m_blogPassword,
                                     &numOfBlogs, blogInfo );
                    /* 備考: 本家の blogger.com に対しては blogger API */
                    /*       ではなく Atom API を適用する              */
        }
        else {
            //  --- blogger API 系の場合
            CWaitCursor cur;    // マウスカーソルを砂時計表示
            r = getBlogIDs( m_blogUserName, m_blogPassword,
                            &numOfBlogs, blogInfo );    /* blogger API */
        }
        if ( (r >= 1) && (blogInfo[0].blogName[0] == NUL) ) {
            /* FC2BLOG のように取得に失敗しても r == 1 となる blog 対策 */
            MessageBox( "blog ID の取得に失敗しました。\n"
                        "ユーザ名、パスワードが正しいか確認してください。    ",
                        "取得失敗", MB_OK|MB_ICONWARNING );
        }
        else if ( r == 1 ) {
            MessageBox( "blog ID の取得に成功しました。    ",
                        "取得成功", MB_OK|MB_ICONINFORMATION );
            m_blogName = utf2sjis( blogInfo[0].blogName );  /* 確定 */
            m_blogID   = blogInfo[0].blogID;                /* 確定 */
            m_blogURL  = blogInfo[0].url;                   /* 確定 */

            if ( m_blogID == "" )
                if ( (m_blogKind == msnSpaces) ||
                     (m_blogKind == webryX)       )
                    m_blogID = "MyBlog";

            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
            p->SetWindowText( (const char *)m_blogName );

            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
            p->SetWindowText( (const char *)m_blogID );

            if ( !strncmp( m_blogURL, m_endpointURL, strlen(m_endpointURL) ) ) {
                if ( m_blogKind == livedoor )
                    m_blogURL = "http://blog.livedoor.jp/" + m_blogUserName + "/";
                if ( m_blogKind == lovelog )
                    m_blogURL = "http://blog.dion.ne.jp/" + m_blogUserName + "/";
                if ( m_blogKind == ameblo )
                    m_blogURL = "http://ameblo.jp/" + m_blogUserName + "/";
                if ( m_blogKind == sonet )
                    m_blogURL = "http://blog.so-net.ne.jp/" + m_blogUserName + "/";
            }
            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
            p->SetWindowText( m_blogURL );
        }
        else if ( r > 1 ) {
            /* ---- 投稿先 blog の選択 */
            int rr = selectBlog( blogInfo, r );
            if ( (rr >= 0) && (rr < r) ) {
                r = rr;
                m_blogName = utf2sjis( blogInfo[r].blogName );  /* 確定 */
                m_blogID   = blogInfo[r].blogID;                /* 確定 */
                m_blogURL  = blogInfo[r].url;                   /* 確定 */

                if ( m_blogID == "" )
                    if ( (m_blogKind == msnSpaces) ||
                         (m_blogKind == webryX)       )
                        m_blogID = "MyBlog";

                p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
                p->SetWindowText( (const char *)m_blogName );

                p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
                p->SetWindowText( (const char *)m_blogID );

                p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
                p->SetWindowText( m_blogURL );

                MessageBox( "blog ID の取得に成功しました。    ",
                            "取得成功", MB_OK|MB_ICONINFORMATION );
            }
        }
        else {
            MessageBox( "blog ID の取得に失敗しました。\n"
                        "ユーザ名、パスワードが正しいか確認してください。    ",
                        "取得失敗", MB_OK|MB_ICONWARNING );
        }
    }
    else if ( m_blogKind == newPostOnly ) {
        m_blogID = "0";
        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
        p->SetWindowText( (const char *)m_blogID );
    }
    else if ( (m_blogKind == exciteBlog) ||
              (m_blogKind == echoo)      ||
              (m_blogKind == rakuten)       ) {
        BLOGINF blogInfo[MAX_BLOGS];
        int     numOfBlogs = MAX_BLOGS;
        int     r = 0;

        CWaitCursor cur;    // マウスカーソルを砂時計表示

        switch ( m_blogKind ) {
        case exciteBlog:
            r = getBlogIDsExciteBlog( m_blogUserName, m_blogPassword,
                                      &numOfBlogs, blogInfo );
            break;

        case echoo:
            r = getBlogIDsEchoo( m_blogUserName, m_blogPassword,
                                 &numOfBlogs, blogInfo );
            break;

        case rakuten:
            r = getBlogIDsRakuten( m_blogUserName, m_blogPassword,
                                   &numOfBlogs, blogInfo );
            break;
        }

        if ( r == 1 ) {
            MessageBox( "blog URL の取得に成功しました。    ",
                        "取得成功", MB_OK|MB_ICONINFORMATION );

            m_blogURL  = blogInfo[0].url;
            m_blogName = blogInfo[0].blogName;

            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
            p->SetWindowText( (const char *)m_blogName );

            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
            p->SetWindowText( m_blogURL );

            if ( m_blogKind == exciteBlog ) {
                m_blogID = blogInfo[0].blogID;
                p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
                p->SetWindowText( m_blogID );
            }
        }
        else if ( r <= 0 ) {
            MessageBox("blog URL の取得に失敗しました。"
                       "ユーザ名、パスワードが正しいか確認してください。    ",
                       "取得失敗", MB_OK|MB_ICONWARNING );
        }
    }
}

void CAddBlogInfoDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        if ( m_blogInfo ) {
            m_blogKindList.InitStorage( BLOGOLEE_NUM_OF_BLOG_KINDS,
                                        BLOGOLEE_MAX_BLOG_NAME_LENGTH );
            m_blogKindList.ResetContent();
            for ( int i = 0; i < m_blogInfo->m_numOfBlogKinds; i++ ) {
                m_blogKindList.AddString( m_blogInfo->m_blogKindInfo[i].blogKindString );
            }
        }

        CEdit   *p;
        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
        p->SetReadOnly( TRUE );
        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGURL );
        p->SetReadOnly( TRUE );
        p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
        p->SetReadOnly( TRUE );
        p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
        p->SetReadOnly( TRUE );

        CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_MOREINFO );
        bp->EnableWindow( FALSE );

        if ( m_mode == false ) {
            long    location = -1;

            if ( (m_blogKind == newPostOnly) && (m_useCbox == true) ) {
                // 「BlogPet 飼育箱」のための特別処理
                for ( location = 0; location < m_blogInfo->m_numOfBlogKinds; location++ ) {
                    if ( !strcmp( m_blogInfo->m_blogKindInfo[location].blogKindString,
                                  "BlogPet 飼育箱" ) )
                        break;
                }
            }
            else {
                for ( location = 0; location < m_blogInfo->m_numOfBlogKinds; location++ ) {
                    if ( m_blogKind == m_blogInfo->m_blogKindInfo[location].blogKind )
                        break;
                }
            }

            if ( (location >= 0) && (location < m_blogInfo->m_numOfBlogKinds) )
                m_blogKindList.SetCurSel( location );

            OnSelchangeComboBlogList();
            SetWindowText( "登録情報修正" );
        }
    }
}

void CAddBlogInfoDlg::OnSelchangeComboBlogList() 
{
	int location = m_blogKindList.GetCurSel();

    m_blogKind = m_blogInfo->m_blogKindInfo[location].blogKind;

    if ( !strcmp( m_blogInfo->m_blogKindInfo[location].blogKindString, "BlogPet 飼育箱" ) )
        m_useCbox = true;
    else
        m_useCbox = false;

    switchBlogName();
    switchBlogURL();
    switchBlogID();
    switchEndpointURL();
    switchMoreInfo();
}

void CAddBlogInfoDlg::OnUpdateEditBlogUserName() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGUSERNAME );
    p->GetWindowText( m_blogUserName );

    switchMoreInfo();
}

void CAddBlogInfoDlg::OnUpdateEditBlogPassword() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGPASSWORD );
    p->GetWindowText( m_blogPassword );

    switchMoreInfo();
}

void CAddBlogInfoDlg::OnOK() 
{
    // 入力内容チェック
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGUSERNAME );
    p->GetWindowText( m_blogUserName );
    if ( m_blogUserName.GetLength() == 0 ) {
        MessageBox( "「ユーザ名、または ID」を設定してください    ",
                    "設定確認", MB_OK|MB_ICONWARNING );
        return;
    }

    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGPASSWORD );
    p->GetWindowText( m_blogPassword );
    if ( m_blogPassword.GetLength() == 0 ) {
        MessageBox( "「パスワード」を設定してください    ",
                    "設定確認", MB_OK|MB_ICONWARNING );
        return;
    }

    if ( m_blogKind == unset ) {
        MessageBox( "「blog の種類」を設定してください    ",
                    "設定確認", MB_OK|MB_ICONWARNING );
        return;
    }

    p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGNAME );
    p->GetWindowText( m_blogName );
    if ( m_blogName.GetLength() == 0 ) {
        if ( (m_blogKind == movableType)  ||
             (m_blogKind == bloggerAPI)   ||
             (m_blogKind == metaWeblog)   ||
             (m_blogKind == mtAPI)        ||
             (m_blogKind == atomAPI)      ||
             (m_blogKind == newPostOnly)  ||   
             (m_blogKind == typepad)      ||
             (m_blogKind == typepadJapan) ||
             (m_blogKind == cocolog)      ||
             (m_blogKind == cocologFree)  ||
             (m_blogKind == blogzine)     ||
             (m_blogKind == newsHandler)  ||
             (m_blogKind == ameblo)       ||
             (m_blogKind == seesaa)       ||
             (m_blogKind == netLaputa)    ||
             (m_blogKind == blogG)        ||
             (m_blogKind == fc2blog)      ||
             (m_blogKind == gooBlog)      ||
             (m_blogKind == msnSpaces)    ||
             (m_blogKind == drecomX)      ||
             (m_blogKind == yaplogX)      ||
             (m_blogKind == jugemX)       ||
             (m_blogKind == webryX)       ||
             (m_blogKind == livedoor)     ||
             (m_blogKind == lovelog)      ||
             (m_blogKind == sonet)        ||
             (m_blogKind == vox)          ||
             (m_blogKind == hatena)       ||
             (m_blogKind == blogger)      ||
             (m_blogKind == exciteBlog)   ||
             (m_blogKind == echoo)        ||
             (m_blogKind == rakuten)         ) {
            // 追加情報取得
            OnButtonMoreInfo();
        }

        if ( m_blogName.GetLength() == 0 ) {
            MessageBox( "「blog 名」を設定してください    ",
                        "設定確認", MB_OK|MB_ICONWARNING );
            return;
        }
    }

    if ( (m_blogKind == movableType)  ||
         (m_blogKind == bloggerAPI)   ||
         (m_blogKind == metaWeblog)   ||
         (m_blogKind == mtAPI)        ||
         (m_blogKind == atomAPI)      ||
         (m_blogKind == newPostOnly)  ||   
         (m_blogKind == typepad)      ||
         (m_blogKind == typepadJapan) ||
         (m_blogKind == cocolog)      ||
         (m_blogKind == cocologFree)  ||
         (m_blogKind == blogzine)     ||
         (m_blogKind == newsHandler)  ||
         (m_blogKind == ameblo)       ||
         (m_blogKind == seesaa)       ||
         (m_blogKind == netLaputa)    ||
         (m_blogKind == blogG)        ||
         (m_blogKind == fc2blog)      ||
         (m_blogKind == gooBlog)      ||
         (m_blogKind == msnSpaces)    ||
         (m_blogKind == drecomX)      ||
         (m_blogKind == yaplogX)      ||
         (m_blogKind == jugemX)       ||
         (m_blogKind == webryX)       ||
         (m_blogKind == livedoor)     ||
         (m_blogKind == lovelog)      ||
         (m_blogKind == sonet)        ||
         (m_blogKind == vox)          ||
         (m_blogKind == hatena)       ||
         (m_blogKind == blogger)         ) {
        if ( m_blogID.GetLength() == 0 ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_BLOGID );
            p->GetWindowText( m_blogID );
            if ( m_blogID.GetLength() == 0 ) {
                MessageBox( "「blog ID」を設定してください    ",
                            "設定確認", MB_OK|MB_ICONWARNING );
                return;
            }
        }

        if ( m_useCbox ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
            p->GetWindowText( m_endpointURL );
        }
        if ( m_endpointURL.GetLength() == 0 ) {
            p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINTURL );
            p->GetWindowText( m_endpointURL );
            if ( m_endpointURL.GetLength() == 0 ) {
                MessageBox( "「エンドポイントURL」を設定してください    ",
                            "設定確認", MB_OK|MB_ICONWARNING );
                return;
            }
        }
    }

	CDialog::OnOK();
}
