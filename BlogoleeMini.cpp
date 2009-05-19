/*
 * BlogoleeMini.cpp : ブログクライアント BloGolEe
 *      第2メインダイアログ
 *
 *          written by H.Tsujimura  13 Mar 2007
 *
 *      Copyright (c) 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/BlogoleeMini.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 10    09/03/24 18:58 Tsujimura543
 * Windows Live Spaces 拡張版 metaWeblog API 採用ブログの
 * 「カテゴリ一覧取得」に対応
 * 
 * 9     09/03/20 22:48 Tsujimura543
 * はてなダイアリー(の Atom API での投稿)に対応した
 * 
 * 8     09/03/19 20:24 Tsujimura543
 * ウェブリブログのテンプレート関連処理を削除
 * 
 * 7     09/03/16 20:49 Tsujimura543
 * ウェブリブログの XMLRPC API 対応作業開始
 * 
 * 6     08/02/18 23:11 Tsujimura543
 * copyright 表示をアップデート
 * 
 * 5     08/02/18 23:08 Tsujimura543
 * バージョン情報をリソースから取得して表示するようにした
 * 
 * 4     07/11/30 2:03 Tsujimura543
 * (1) Jugem、ヤプログ!、ドリコムブログの XML-RPC API 経由ではない方の
 *     諸々を削除
 * (2) しまにてぃ内日記関連の諸々を削除 (2007年11月30日でサービス終了)
 * 
 * 3     07/10/29 20:34 Tsujimura543
 * (1) XML-RPC API 経由での ヤプログ! へのアクセスに対応
 * (2) XML-RPC API 経由でのドリコムブログのカテゴリ一覧取得、カテゴリ設定
 *     に対応
 * 
 * 2     07/03/14 0:08 Tsujimura543
 * メインダイアログと第2メインダイアログの間の連携機能を改良
 * 
 * 1     07/03/13 23:42 Tsujimura543
 * 新規作成 (実験的に第2のメインダイアログを作ってみた)
 */

#include "blogolee.h"
#include "BlogoleeMini.h"
#include "EditBlogInfoDlg.h"
#include "ProceedingDialog.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/BlogoleeMini.cpp 1     09/05/14 3:47 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeMini ダイアログ

CBlogoleeMini::CBlogoleeMini(CWnd* pParent /*=NULL*/)
	: CDialog(CBlogoleeMini::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlogoleeMini)
	m_articleTitle = _T("");
	m_articleSummary = _T("");
	m_articleDescription = _T("");
	m_categoryName = _T("");
	//}}AFX_DATA_INIT
}

void CBlogoleeMini::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlogoleeMini)
	DDX_Control(pDX, IDC_LIST_CATEGORY, m_categoryList);
	DDX_Text(pDX, IDC_EDIT_ARTICLE_TITLE, m_articleTitle);
	DDV_MaxChars(pDX, m_articleTitle, 128);
	DDX_Text(pDX, IDC_EDIT_ARTICLE_SUMMARY, m_articleSummary);
	DDV_MaxChars(pDX, m_articleSummary, 256);
	DDX_Text(pDX, IDC_EDIT_ARTICLE, m_articleDescription);
	DDV_MaxChars(pDX, m_articleDescription, 65536);
	DDX_LBString(pDX, IDC_LIST_CATEGORY, m_categoryName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBlogoleeMini, CDialog)
	//{{AFX_MSG_MAP(CBlogoleeMini)
	ON_EN_UPDATE(IDC_EDIT_ARTICLE_TITLE, OnUpdateEditArticleTitle)
	ON_EN_UPDATE(IDC_EDIT_ARTICLE_SUMMARY, OnUpdateEditArticleSummary)
	ON_EN_UPDATE(IDC_EDIT_ARTICLE, OnUpdateEditArticle)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH_BLOG, OnButtonSwitchBlog)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_BLOG, OnButtonBrowseBlog)
	ON_BN_CLICKED(IDC_BUTTON_GET_CATEGORIES, OnButtonGetCategories)
	ON_BN_CLICKED(IDCANCEL, OnExit)
	ON_BN_CLICKED(IDOK, OnPostArticle)
	ON_BN_CLICKED(IDC_BUTTON_LARGE, OnButtonLarge)
	ON_BN_CLICKED(IDC_RADIO_KEYWORD_ON, OnRadioKeywordOn)
	ON_BN_CLICKED(IDC_RADIO_KEYWORD_OFF, OnRadioKeywordOff)
	ON_BN_CLICKED(IDC_RADIO_SIMILARITY_ON, OnRadioSimilarityOn)
	ON_BN_CLICKED(IDC_RADIO_SIMILARITY_OFF, OnRadioSimilarityOff)
	ON_LBN_SELCHANGE(IDC_LIST_CATEGORY, OnSelchangeListCategory)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeMini 追加メソッド

void    CBlogoleeMini::switchKeyword( bool value )
{
    CButton *p;

    if ( value == true ) {
        p = (CButton *)GetDlgItem( IDC_RADIO_KEYWORD_ON );
        p->SetCheck( 1 );

        p = (CButton *)GetDlgItem( IDC_RADIO_KEYWORD_OFF );
        p->SetCheck( 0 );

        m_keyword = true;
    }
    else {
        p = (CButton *)GetDlgItem( IDC_RADIO_KEYWORD_OFF );
        p->SetCheck( 1 );

        p = (CButton *)GetDlgItem( IDC_RADIO_KEYWORD_ON );
        p->SetCheck( 0 );

        m_keyword = false;
    }
}

void    CBlogoleeMini::switchSimilarity( bool value )
{
    CButton *p;

    if ( (m_dlg->m_blogKind == exciteBlog) ||
         (m_dlg->m_blogKind == mixi)       ||
         (m_dlg->m_blogKind == kinugasa)   ||
         (m_dlg->m_blogKind == fc2network) ||
         (m_dlg->m_blogKind == echoo)      ||
         (m_dlg->m_blogKind == colors)     ||
         (m_dlg->m_blogKind == openPne)    ||
         (m_dlg->m_blogKind == rakuten) /* ||
         (m_dlg->m_blogKind == webry)   */    ) {
        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_ON );
        p->EnableWindow( FALSE );

        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_OFF );
        p->EnableWindow( FALSE );
        value = false;
    }
    else {
        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_ON );
        p->EnableWindow( TRUE );

        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_OFF );
        p->EnableWindow( TRUE );
    }

    if ( value == true ) {
        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_ON );
        p->SetCheck( 1 );

        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_OFF );
        p->SetCheck( 0 );

        m_similarity = true;
    }
    else {
        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_OFF );
        p->SetCheck( 1 );

        p = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_ON );
        p->SetCheck( 0 );

        m_similarity = false;
    }
}

void    CBlogoleeMini::switchPostArticle()
{
    CButton *q = (CButton *)GetDlgItem( IDOK );

    if ( ( m_articleTitle.GetLength() > 0)      &&
         (m_articleDescription.GetLength() > 0)    )
        q->EnableWindow( TRUE );
    else
        q->EnableWindow( FALSE );
}

void    CBlogoleeMini::switchCategoryList()
{
    CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_GET_CATEGORIES );
    if ( (m_dlg->m_blogKind == movableType)  ||
         (m_dlg->m_blogKind == bloggerAPI)   ||
         (m_dlg->m_blogKind == metaWeblog)   ||
         (m_dlg->m_blogKind == mtAPI)        ||
         (m_dlg->m_blogKind == atomAPI)      ||
         (m_dlg->m_blogKind == typepad)      ||
         (m_dlg->m_blogKind == typepadJapan) ||
         (m_dlg->m_blogKind == cocolog)      ||
         (m_dlg->m_blogKind == cocologFree)  ||
         (m_dlg->m_blogKind == blogzine)     ||
         (m_dlg->m_blogKind == newsHandler)  ||
         (m_dlg->m_blogKind == seesaa)       ||
         (m_dlg->m_blogKind == netLaputa)    ||
         (m_dlg->m_blogKind == blogG)        ||
         (m_dlg->m_blogKind == fc2blog)      ||
         (m_dlg->m_blogKind == gooBlog)      ||
         (m_dlg->m_blogKind == msnSpaces)    ||
         (m_dlg->m_blogKind == webryX)       ||
         (m_dlg->m_blogKind == drecomX)      ||
         (m_dlg->m_blogKind == yaplogX)      ||
         (m_dlg->m_blogKind == jugemX)       ||
         (m_dlg->m_blogKind == livedoor)     ||
         (m_dlg->m_blogKind == lovelog)   /* ||
         (m_dlg->m_blogKind == ameblo)       ||
         (m_dlg->m_blogKind == sonet)        ||
         (m_dlg->m_blogKind == vox)          ||
         (m_dlg->m_blogKind == hatena)       ||
         (m_dlg->m_blogKind == blogger)   */     ) {
            /* 注意: So-net blog, Blogger.com, アメーバブログ では Atom API */
            /*       によるカテゴリの取得は今のところサポートされていない   */
        // 「カテゴリ一覧取得」ボタンを enable にする
        bp->EnableWindow( TRUE );
    }
    else if ( (m_dlg->m_blogKind == echoo)      ||
              (m_dlg->m_blogKind == exciteBlog) ||
              (m_dlg->m_blogKind == rakuten)       ) {
        // 「カテゴリ一覧取得」ボタンを enable にする
        bp->EnableWindow( TRUE );
    }
    else {
        // 「カテゴリ一覧取得」ボタンを disable にする
        bp->EnableWindow( FALSE );
    }

    m_categoryList.ResetContent();
    m_categoryName = "";
}

void    CBlogoleeMini::switchBlogInfo()
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_BLOG_NAME );
    p->SetWindowText( m_dlg->m_blogName );

    if ( m_dlg->m_article_title.GetLength() > 0 ) {
        m_articleTitle = m_dlg->m_article_title;

        p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_TITLE );
        p->SetWindowText( m_articleTitle );
    }
    else
        m_articleTitle = _T("");

    if ( m_dlg->m_article_summary.GetLength() > 0 ) {
        m_articleSummary = m_dlg->m_article_summary;

        p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_SUMMARY );
        p->SetWindowText( m_articleSummary );
    }
    else
        m_articleSummary = _T("");

    if ( m_dlg->m_article_description.GetLength() > 0 ) {
        m_articleDescription = m_dlg->m_article_description;

        p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE );
        p->SetWindowText( m_articleDescription );
    }
    else
        m_articleDescription = _T("");

    m_keyword    = m_dlg->m_keyword;
    m_similarity = m_dlg->m_similarity;
    CButton *bp = (CButton *)GetDlgItem( IDC_RADIO_KEYWORD_ON );
    bp->SetCheck( m_keyword ? 1 : 0 );

    bp = (CButton *)GetDlgItem( IDC_RADIO_KEYWORD_OFF );
    bp->SetCheck( m_keyword ? 0 : 1 );

    bp = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_ON );
    bp->SetCheck( m_similarity ? 1 : 0 );

    bp = (CButton *)GetDlgItem( IDC_RADIO_SIMILARITY_OFF );
    bp->SetCheck( m_similarity ? 0 : 1 );

    switchCategoryList();
    switchKeyword( m_keyword );
    switchSimilarity( m_similarity );
    switchPostArticle();
}

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeMini メッセージ ハンドラ

void CBlogoleeMini::OnUpdateEditArticleTitle() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_TITLE );
    p->GetWindowText( m_articleTitle );
    switchPostArticle();
}

void CBlogoleeMini::OnUpdateEditArticleSummary() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE_SUMMARY );
    p->GetWindowText( m_articleSummary );
}

void CBlogoleeMini::OnUpdateEditArticle() 
{
    CEdit   *p = (CEdit *)GetDlgItem( IDC_EDIT_ARTICLE );
    p->GetWindowText( m_articleDescription );
    switchPostArticle();
}

void CBlogoleeMini::OnButtonSwitchBlog() 
{
    CEditBlogInfoDlg    dlg;
    
    dlg.m_currentBlogID = m_dlg->m_currentBlogID;
    dlg.m_blogInfo      = m_dlg;

    int res = dlg.DoModal();
    if ( res == IDOK ) {
        CWaitCursor cur;    // マウスカーソルを砂時計表示
        int blogKindIndex = -1;

        // blog 切替
        m_dlg->m_currentBlogID = dlg.m_currentBlogID;
        m_dlg->m_blogKind      = dlg.m_blogKind;
        m_dlg->m_blogName      = dlg.m_blogName;
        m_dlg->m_blogUserName  = dlg.m_blogUsername;
        m_dlg->m_blogPassword  = dlg.m_blogPassword;
        m_dlg->m_blogID        = dlg.m_blogID;
        m_dlg->m_blogURL       = dlg.m_blogURL;

        if ( m_dlg->m_blogKind == jugemX ) {
            if ( m_dlg->m_blogUserName.GetLength() > 0 ) {
                char        url[MAX_URLLENGTH];
                const char  *q = strchr( m_dlg->m_endpointURL, '$' );

                if ( q )
                    q++;
                else
                    q = ".jugem.jp/admin/xmlrpc.php";
                sprintf( url, "http://%s%s",
                         (const char *)m_dlg->m_blogUserName,
                         q );

                m_dlg->m_endpointURL = url;
             // CEdit *p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINT_URL );
             // p->SetWindowText( m_dlg->m_endpointURL );
            }
        }
        if ( m_dlg->m_blogKind == hatena ) {
            if ( strstr( m_dlg->m_endpointURL, "{hatenaID}" ) ) {
                m_dlg->m_endpointURL =
                    "http://d.hatena.ne.jp/" + m_dlg->m_blogUserName + "/atom/blog";
            }
        }

        if ( dlg.m_endpointURL.GetLength() > 0 )
            m_dlg->m_endpointURL = dlg.m_endpointURL;
        else {
            int j;
            for ( j = 0; j < m_dlg->m_numOfBlogKinds; j++ ) {
                if ( m_dlg->m_blogKind == m_dlg->m_blogKindInfo[j].blogKind ) {
                    blogKindIndex = j;
                    break;
                }
            }
            if ( blogKindIndex >= 0 )
                m_dlg->m_endpointURL = m_dlg->m_blogKindInfo[j].endpointURL;
            else
                m_dlg->m_endpointURL = "";
        }

        m_categoryList.ResetContent();
        m_categoryName  = "";

        if ( m_dlg->m_blogID.GetLength() > 0 )
            m_dlg->switchBlogID( m_dlg->m_blogID );
        else
            m_dlg->switchBlogID();
        m_dlg->switchBlogInfo();
        m_dlg->switchBrowseBlog();
        m_dlg->switchArticleKeyword();
        m_dlg->switchArticleExtended();
        m_dlg->switchArticleSummary();
        m_dlg->saveBlogInfo();
    }

    CWaitCursor cur;    // マウスカーソルを砂時計表示
    m_dlg->loadBlogInfo();

    switchBlogInfo();
}

void CBlogoleeMini::OnButtonBrowseBlog() 
{
    char            cmd[BUFSIZ];
    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();

    cmd[0] = NUL;
    if ( cp->m_blogList[m_dlg->m_currentBlogID].blogURL[0] ) {
        // blog (または SNS の日記)を見る
        strcpy( cmd, cp->m_blogList[m_dlg->m_currentBlogID].blogURL );
        ShellExecute( NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL );
    }
}

void CBlogoleeMini::OnButtonGetCategories() 
{
    m_categoryList.ResetContent();
    // パラメータ確定
    if ( m_dlg->getParameter() == false )
        return;

    // 念のためにいったん保存
    m_dlg->saveSetting();
    m_dlg->saveBlogInfo();

    ProceedingDialog    *pdlg;
    pdlg = new ProceedingDialog();
    pdlg->Create( IDD_PROCEEDING_DIALOG );
    pdlg->ChangeDialogText( "カテゴリ一覧取得中",
                            "カテゴリ一覧取得中……" );

	/* カテゴリ一覧取得 */
    if ( (m_dlg->m_blogKind == typepad)       ||
         (m_dlg->m_blogKind == typepadJapan ) ||
         (m_dlg->m_blogKind == cocolog )      ||
         (m_dlg->m_blogKind == cocologFree )  ||
         (m_dlg->m_blogKind == blogzine )     ||
         (m_dlg->m_blogKind == seesaa )       ||
         (m_dlg->m_blogKind == netLaputa )    ||
         (m_dlg->m_blogKind == blogG )        ||
         (m_dlg->m_blogKind == newsHandler )  ||
         (m_dlg->m_blogKind == fc2blog )      ||
         (m_dlg->m_blogKind == gooBlog )      ||
         (m_dlg->m_blogKind == drecomX)       ||
         (m_dlg->m_blogKind == yaplogX)       ||
         (m_dlg->m_blogKind == jugemX)        ||
         (m_dlg->m_blogKind == movableType )  ||
         (m_dlg->m_blogKind == mtAPI )           ) {
        /* MovableType 互換 API 利用可能 blog の場合 */
        CWaitCursor cur;    // マウスカーソルを砂時計表示
        CATLISTINF  categoryList[MAX_CATS];
        long        numOfCategories;

        if ( m_dlg->m_blogKind == jugemX ) {
            if ( m_dlg->m_blogUserName.GetLength() > 0 ) {
                char        url[MAX_URLLENGTH];
                const char  *q = strchr( m_dlg->m_endpointURL, '$' );

                if ( q )
                    q++;
                else
                    q = ".jugem.jp/admin/xmlrpc.php";
                sprintf( url, "http://%s%s",
                         (const char *)m_dlg->m_blogUserName,
                         q );

                m_dlg->m_endpointURL = url;
             // CEdit *p = (CEdit *)GetDlgItem( IDC_EDIT_ENDPOINT_URL );
             // p->SetWindowText( m_endpointURL );
            }
        }

        setTargetURL( m_dlg->m_endpointURL );
        numOfCategories = MAX_CATS;
        getCategoryList( (const char *)m_dlg->m_blogID,
                         (const char *)m_dlg->m_blogUserName,
                         (const char *)m_dlg->m_blogPassword,
                         &numOfCategories,
                         categoryList );    /* Movable Type API */
        if ( numOfCategories > 0 ) {
            int numOfCats = 0;
            for ( long i = 0; i < numOfCategories; i++ ) {
                char    *p = utf2sjis( categoryList[i].categoryName );
                if ( p ) {
                    m_categoryList.AddString( p );
                    numOfCats++;
                }
            }
            numOfCategories = numOfCats;
        }
    }
    else
    if ( (m_dlg->m_blogKind == msnSpaces) ||
         (m_dlg->m_blogKind == webryX )      ) {
        /* Windows Live Spaces 拡張版 metaWeblog API 採用 blog の場合 */
        CWaitCursor cur;    // マウスカーソルを砂時計表示
        CATEGORIES  categoryList[MAX_CATS];
        long        numOfC = MAX_CATS;
        int         numOfCategories;

        setTargetURL( m_dlg->m_endpointURL );
        numOfCategories = 
            getCategories( "MyBlog",
                           (const char *)m_dlg->m_blogUserName,
                           (const char *)m_dlg->m_blogPassword,
                           &numOfC,
                           categoryList );
        int numOfCats = 0;
        for ( long i = 0; i < numOfCategories; i++ ) {
            char    *p = utf2sjis( categoryList[i].categoryTitle );
            if ( p ) {
                m_categoryList.AddString( p );
                numOfCats++;
            }
        }
        numOfCategories = numOfCats;
    }
    else
    if ( (m_dlg->m_blogKind == livedoor) ||
         (m_dlg->m_blogKind == lovelog)  ||
         (m_dlg->m_blogKind == sonet)    ||
         (m_dlg->m_blogKind == ameblo)   ||
         (m_dlg->m_blogKind == livedoor) ||
         (m_dlg->m_blogKind == vox )     ||
         (m_dlg->m_blogKind == hatena)   ||
         (m_dlg->m_blogKind == blogger ) ||
         (m_dlg->m_blogKind == atomAPI )    ) {
        /* Atom API 利用可能 blog の場合 */
        CWaitCursor cur;    // マウスカーソルを砂時計表示
        CATLISTINF  categoryList[MAX_CATS];
        long        numOfC = MAX_CATS;
        int         numOfCategories;

        setTargetURL( m_dlg->m_endpointURL );
        numOfCategories = 
            listCategoriesOnAtomAPI( (const char *)m_dlg->m_blogUserName,
                                     (const char *)m_dlg->m_blogPassword,
                                     (const char *)m_dlg->m_blogID,
                                     &numOfC,
                                     categoryList );
        int numOfCats = 0;
        for ( long i = 0; i < numOfCategories; i++ ) {
            char    *p = utf2sjis( categoryList[i].categoryName );
            if ( p ) {
                m_categoryList.AddString( p );
                numOfCats++;
            }
        }
        numOfCategories = numOfCats;
    }
    else if ( (m_dlg->m_blogKind == echoo)      ||
              (m_dlg->m_blogKind == exciteBlog) ||
              (m_dlg->m_blogKind == rakuten)       ) {
        /* エコログ、exciteブログ、楽天ブログ の場合 */
        CWaitCursor cur;    // マウスカーソルを砂時計表示
        CATLISTINF  categoryList[MAX_CATS];
        long        numOfCategories;

        numOfCategories = MAX_CATS;

        switch ( m_dlg->m_blogKind ) {
        case echoo:
            getCategoryListEchoo( (const char *)m_dlg->m_blogUserName,
                                  (const char *)m_dlg->m_blogPassword,
                                  &numOfCategories,
                                  categoryList );
            break;

        case exciteBlog:
            getCategoryListExciteBlog( (const char *)m_dlg->m_blogUserName,
                                       (const char *)m_dlg->m_blogPassword,
                                       &numOfCategories,
                                       categoryList );
            break;

        case rakuten:
            getCategoryListRakuten( (const char *)m_dlg->m_blogUserName,
                                    (const char *)m_dlg->m_blogPassword,
                                    &numOfCategories,
                                    categoryList );
            break;
        }

        if ( numOfCategories > 0 ) {
            for ( long i = 0; i < numOfCategories; i++ ) {
                m_categoryList.AddString( categoryList[i].categoryName );
            }
        }
    }
    else {
        MessageBox(
          "申し訳ありませんが、このバージョンの “BloGolEe”では、    \n"
          "カテゴリ一覧の取得はできません",
                    "カテゴリ一覧取得", MB_OK|MB_ICONWARNING );
    }

    delete pdlg;
}

void CBlogoleeMini::OnExit() 
{
    OnCancel();
}

void CBlogoleeMini::OnPostArticle() 
{
    if ( (m_articleTitle.GetLength() > 0)       &&
         (m_articleDescription.GetLength() > 0)    )
        OnOK();
}

void CBlogoleeMini::OnButtonLarge() 
{
    if ( m_articleTitle.GetLength() > 0 )
        m_dlg->m_article_title = m_articleTitle;
    if ( m_articleSummary.GetLength() > 0 )
        m_dlg->m_article_summary = m_articleSummary;
    if ( m_articleDescription.GetLength() > 0 )
        m_dlg->m_article_description = m_articleDescription;

    EndDialog( IDC_BUTTON_LARGE );
}

void CBlogoleeMini::OnRadioKeywordOn() 
{
    m_keyword = true;
    switchKeyword( m_keyword );
}

void CBlogoleeMini::OnRadioKeywordOff() 
{
    m_keyword = false;
    switchKeyword( m_keyword );
}

void CBlogoleeMini::OnRadioSimilarityOn() 
{
    m_similarity = true;
    switchSimilarity( m_similarity );
}

void CBlogoleeMini::OnRadioSimilarityOff() 
{
    m_similarity = false;
    switchSimilarity( m_similarity );
}

void CBlogoleeMini::OnSelchangeListCategory() 
{
    CString     categoryString;
    int         location = m_categoryList.GetCurSel();

	m_categoryList.GetText( location, categoryString );
    m_categoryName = categoryString;
}

void CBlogoleeMini::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    CDialog::OnShowWindow(bShow, nStatus);

    if ( bShow ) {
        CStatic *s;
        CString str;
        str.LoadString( IDS_VERSION );
        s = (CStatic *)GetDlgItem( IDC_VERSION );
        s->SetWindowText( str );

        switchBlogInfo();
    }
}
