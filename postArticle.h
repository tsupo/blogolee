/*
 *  postArticle.h
 *      記事を blog に投稿するプログラム
 *      (「ここうさぎ」のソース cocousagi.h を流用、改造)
 *
 *      written by H.Tsujimura      2 Jul 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * History:
 * $Log: /comm/blogolee/postArticle.h $
 * 
 * 2     09/05/27 1:47 tsupo
 * 1.22版
 * 
 * 21    09/05/26 21:52 Tsujimura543
 * tumblr への投稿に対応
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 20    09/03/24 20:02 Tsujimura543
 * ウェブリブログの XML-RPC API 経由ではない方の諸々を削除
 * 
 * 19    09/03/20 22:48 Tsujimura543
 * はてなダイアリー(の Atom API での投稿)に対応した
 * 
 * 18    09/03/16 20:49 Tsujimura543
 * ウェブリブログの XMLRPC API 対応作業開始
 * 
 * 17    08/09/10 23:01 Tsujimura543
 * loginExciteBlog(), postExciteBlog(), getCategoryListExciteBlog(),
 * getBlogIDsExciteBlog(), getCategoryIDwithName()
 * を xmlRPC.dll から移管
 * 
 * 16    08/09/10 21:41 Tsujimura543
 * loginEchoo(), postEchoo(), getCategoryListEchoo(),
 * getBlogIDsEchoo() を xmlRPC.dll から移管
 * 
 * 15    08/09/10 18:01 Tsujimura543
 * loginRakuten(), postRakuten(), getCategoryListRakuten(),
 * getBlogIDsRakuten(), getCategoryIDbyName(), getCategoryIDs()
 * を xmlRPC.dll から移管
 * 
 * 14    08/09/09 23:56 Tsujimura543
 * loginWebry(), postWebry(), getCategoryListWebry(), getBlogIDsWebry()
 * を xmlRPC.dll から移管
 * 
 * 13    08/09/09 22:49 Tsujimura543
 * loginMixi() と postMixi() を xmlRPC.dll から移管
 * 
 * 12    08/09/09 22:19 Tsujimura543
 * loginFC2NETWORK() と postFC2NETWORK() を xmlRPC.dll から移管
 * 
 * 11    08/09/09 21:42 Tsujimura543
 * loginKinugasa() と postKinugasa() を xmlRPC.dll から移管
 * 
 * 10    08/09/09 19:58 Tsujimura543
 * loginColors() と postColors() を xmlRPC.dll から移管
 * 
 * 9     07/11/30 2:01 Tsujimura543
 * Jugem、ヤプログ!、ドリコムブログ、しまにてぃ内日記向けの専用処理を廃止
 * 
 * 8     07/10/29 20:34 Tsujimura543
 * (1) XML-RPC API 経由での ヤプログ! へのアクセスに対応
 * (2) XML-RPC API 経由でのドリコムブログのカテゴリ一覧取得、カテゴリ設定
 *     に対応
 * 
 * 7     07/03/13 21:16 Tsujimura543
 * 「おすすめ」商品の掲載件数を変えることができるようにした
 * (+ デフォルトの掲載件数を10件から4件に変更)
 * 
 * 6     07/03/12 15:23 Tsujimura543
 * BLOGKIND列挙体から値 sweetBox を削除
 * 
 * 5     07/03/03 1:08 Tsujimura543
 * postArticleOnXMLRPC() と postArticleOnAtomAPI() のプロトタイプ宣言も
 * ヘッダファイルに持ってくる
 * 
 * 4     07/03/03 1:07 Tsujimura543
 * いったん、フィックス
 *
 * 3     07/03/03 0:44 Tsujimura543
 * 投稿日時(年月日時分秒)の指定機能はいったん廃止する
 * [投稿日時は常に現在時刻となる]
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * フィックス
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe 暫定版 (動作確認済み)
 * 
 * ------------------------------------------------------------------------
 * 以下は、cocousagi.h の変更履歴
 * ------------------------------------------------------------------------
 * 7     07/02/24 2:05 Tsujimura543
 * JUGEM と ドリコムブログ の XML-RPC API 経由での投稿に対応
 * 
 * 6     07/01/23 15:45 Tsujimura543
 * 楽天ブログにカテゴリ指定して投稿できるようにした
 * 
 * 5     06/10/13 17:21 Tsujimura543
 * コメントを修正
 * 
 * 4     06/10/13 17:20 Tsujimura543
 * ウェブリブログに投稿する場合、「ここうさぎ」起動時のパラメータでテンプ
 * レートIDを指定しての投稿ができるようにした
 * 
 * 3     06/10/02 20:06 Tsujimura543
 * その他、共通定義を cocousagi.h へ集約
 * 
 * 2     06/10/02 20:01 Tsujimura543
 * COUSAGI_INFO の定義も cocousagi.h へ移動
 * 
 * 1     06/10/02 20:00 Tsujimura543
 * 構造体の宣言、プロトタイプ宣言などを cocousagi.c から分離し、
 * cocousagi.h を作成
 */

#ifndef __POST_ARTICLE_H__
#define __POST_ARTICLE_H__

#define YES     TRUE
#define NO      FALSE

/*
 *  blog種別
 */
#define BLOGKIND_NEWPOSTONLY    0xFE    /* metaWeblog.newPost のみサポート */
                                        /* している blog                   */
#define BLOGKIND_NOSUPPORT      0xFF    /* 未サポート blog                 */

typedef enum blogKind {
    unset        = -1,                      // 未設定
    typepad      = BLOGKIND_TYPEPAD,        // Typepad, Typepad France,
                                            //   TypePad Germany
    typepadJapan = BLOGKIND_TYPEPADJAPAN,   // Typepad Japan
    cocolog      = BLOGKIND_COCOLOG,        // ココログ
    cocologFree  = BLOGKIND_COCOLOGFREE,    // ココログフリー
    blogzine     = BLOGKIND_BLOGZINE,       // ブログ人
    newsHandler  = BLOGKIND_NEWSHANDLER,    // News-Handler
    seesaa       = BLOGKIND_SEESAABLOG,     // Seesaa BLOG
    netLaputa    = BLOGKIND_NETLAPUTA,      // NetLaputa
    blogG        = BLOGKIND_269G,           // 269g
    livedoor     = BLOGKIND_LIVEDOOR,       // livedoor Blog
    lovelog      = BLOGKIND_LOVELOG,        // LOVELOG
    sonet        = BLOGKIND_SONET,          // So-net blog
    blogger      = BLOGKIND_BLOGGER,        // Blogger
    vox          = BLOGKIND_VOX,            // Vox
    hatena       = BLOGKIND_HATENADIARY,    // はてなダイアリー
    msnSpaces    = BLOGKIND_MSNSPACES,      // Windows Live Spaces (MSN Spaces)
    movableType  = BLOGKIND_MOVABLETYPE,    // Movable Type または BOXERBLOG
    bloggerAPI   = BLOGKIND_BLOGGERAPI,     // blogger API サポート blog
    metaWeblog   = BLOGKIND_METAWEBLOG,     // metaWeblog API サポート blog
    mtAPI        = BLOGKIND_MTAPI,          // MovableType API
                                            //   (+ 拡張 metaWeblog API)
                                            //   サポート blog
    atomAPI      = BLOGKIND_ATOMAPI,        // Atom API サポート blog
    newPostOnly  = BLOGKIND_NEWPOSTONLY,    // metaWeblog.newPost のみサポート
                                            //   している blog
    jugemX       = BLOGKIND_JUGEM_X,        // JUGEM (XML-RPC API)
    exciteBlog   = BLOGKIND_EXCITEBLOG,     // exciteブログ
    yaplogX      = BLOGKIND_YAPLOG_X,       // ヤプログ! (XML-RPC API)
    drecomX      = BLOGKIND_DRECOMBLOG_X,   // ドリコムブログ (XML-RPC API)
    webryX       = BLOGKIND_WEBRY_X,        // ウェブリブログ (XML-RPC API)
    mixi         = BLOGKIND_MIXI,           // mixi内日記
    ameblo       = BLOGKIND_AMEBLO,         // アメーバブログ
    kinugasa     = BLOGKIND_KINUGASA,       // キヌガサ内日記
    echoo        = BLOGKIND_ECHOO,          // エコログ (Echoo!内日記)
    fc2network   = BLOGKIND_FC2NETWORK,     // FC2NETWORK内日記
    fc2blog      = BLOGKIND_FC2BLOG,        // FC2BLOG
    rakuten      = BLOGKIND_RAKUTEN,        // 楽天ブログ (楽天広場)
    gooBlog      = BLOGKIND_GOOBLOG,        // goo Blog
    colors       = BLOGKIND_COLORS,         // COLORS内ダイアリー
    openPne      = BLOGKIND_OPENPNE,        // OpenPNE
    tumblr       = BLOGKIND_TUMBLR,         // tumblr
    unsupported  = BLOGKIND_NOSUPPORT       // 未サポート blog
}   BLOGKIND;


void
rebuildOnLivedoor(
        const char *username,
        const char *password,
        const char *blogID
    );

int
postArticleOnXMLRPC( const char *blogID,        /* 投稿先 blog ID     */
                     BLOGKIND   blogType,       /* blog 種別          */
                     const char *title,         /* 投稿記事題名       */
                     const char *body,          /* 投稿記事本文       */
                     const char *extended,      /* 投稿記事追記       */
                     const char *description,   /* 投稿記事概要       */
                     const char *keyword,       /* 投稿記事キーワード */
                     const char *catName );     /* 投稿対象カテゴリ名 */

int
postArticleOnAtomAPI(
        const char *blogID,       /* 投稿先 blog ID     */
        BLOGKIND   blogType,      /* blog 種別          */
        const char *title,        /* 投稿記事題名       */
        const char *body,         /* 投稿記事本文       */
        const char *description,  /* 投稿記事概要       */
        const char *catName       /* 投稿対象カテゴリ名 */
     //,char       *endpointURL   /* エンドポイントURL  */
    );

int
postArticleOnExcite( const char *userName,      /* ユーザ名     */
                     const char *password,      /* パスワード   */
                     char       *title,         /* 投稿記事題名 */
                     char       *body,          /* 投稿記事本文 */
                     char       *extended,      /* 投稿記事追記 */
                     const char *categoryName );/* カテゴリ名   */

int
postArticleOnMixi( const char *username,    /* mixi ID (メールアドレス) */
                   const char *password,    /* パスワード               */
                   char       *title,       /* 投稿記事題名             */
                   char       *body );      /* 投稿記事本文             */

int
postArticleOnKinugasa(
        const char *username,   /* キヌガサ ID(メールアドレス) */
        const char *password,   /* パスワード                  */
        char       *title,      /* 投稿記事題名                */
        char       *body );     /* 投稿記事本文                */

int
postArticleOnFC2NETWORK( const char *username,  /* メールアドレス */
                         const char *password,  /* パスワード     */
                         char       *title,     /* 投稿記事題名   */
                         char       *body );    /* 投稿記事本文   */

int
postArticleOnEchoo( const char *userName,       /* ユーザ名     */
                    const char *password,       /* パスワード   */
                    char       *title,          /* 投稿記事題名 */
                    char       *body,           /* 投稿記事本文 */
                    const char *categoryName ); /* カテゴリ名   */

int
postArticleOnRakuten( const char *userName,       /* ユーザ名     */
                      const char *password,       /* パスワード   */
                      char       *title,          /* 投稿記事題名 */
                      char       *body,           /* 投稿記事本文 */
                      const char *categoryName ); /* カテゴリ名   */

int
postArticleOnColors(
        const char *username,           /* ユーザ名(メールアドレス) */
        const char *password,           /* パスワード               */
        char       *title,              /* 投稿記事題名             */
        char       *body );             /* 投稿記事本文             */

int
postArticleOnOpenPNE(
        const char *username,           /* ユーザ名(メールアドレス) */
        const char *password,           /* パスワード               */
        char       *title,              /* 投稿記事題名             */
        char       *body );             /* 投稿記事本文             */

int
postArticleOnSimanity(
        const char *username,           /* ユーザ名(メールアドレス) */
        const char *password,           /* パスワード               */
        char       *title,              /* 投稿記事題名             */
        char       *body );             /* 投稿記事本文             */

int
postArticleOnTumblr(
        const char *username,           /* ユーザ名(メールアドレス) */
        const char *password,           /* パスワード               */
        const char *group,              /* 投稿先のtumblelog        */
        char       *title,              /* 投稿記事題名             */
        char       *body );             /* 投稿記事本文             */

char    *
editForMixi( char *text );

char    *
editForColors( char *text );


char    *
getCategoryIDbyName(
        char       *catID,          /* (O) カテゴリID (文字列)      */
        const char *categoryName,   /* (I) カテゴリ名               */
        const char *htmlSrcCode,    /* (I) 管理画面htmlソースコード */
        const char *beginSelect,    /* (I) <select>                 */
        const char *endSelect,      /* (I) </select>                */
        const char *beginOption,    /* (I) <option>                 */
        const char *endOption,      /* (I) </option>                */
        int        charSet          /* (I) 文字コード               */
    );

int
getCategoryIDwithName(
        int        *categoryID,     /* (I/O) カテゴリID             */
        char       *categoryName,   /* (O)   カテゴリ名             */
        const char *htmlSrcCode,    /* (I) 管理画面htmlソースコード */
        int        minimumID,       /* (I) カテゴリID最小値         */
        const char *beginSelect,    /* (I) <select>                 */
        const char *endSelect,      /* (I) </select>                */
        const char *beginOption,    /* (I) <option>                 */
        const char *endOption,      /* (I) </option>                */
        int        charSet          /* (I) 文字コード               */
    );

int
getCategoryIDs(
        long         *numOfCategories,  /* (I) 取得するカテゴリの数     */
                                        /* (O) 取得したカテゴリの数     */
        CATLISTINF_t categories,        /* (O) 取得したカテゴリ情報     */
        const char   *htmlSrcCode,      /* (I) 管理画面htmlソースコード */
        const char   *beginSelect,      /* (I) <select>                 */
        const char   *endSelect,        /* (I) </select>                */
        const char   *beginOption,      /* (I) <option>                 */
        const char   *endOption,        /* (I) </option>                */
        int          charSet            /* (I) 文字コード               */
    );

char    *
getCategoryIDstring( 
        char       *catID,          /* (O) カテゴリID (文字列)      */
        const char *htmlSrcCode,    /* (I) 管理画面htmlソースコード */
        const char *beginSelect,    /* (I) <select>                 */
        const char *endSelect,      /* (I) </select>                */
        const char *beginOption,    /* (I) <option>                 */
        const char *endOption,      /* (I) </option>                */
        int        charSet          /* (I) 文字コード               */
    );


int
getCategoryListExciteBlog(
    const char   *userName,         // (I) ユーザ名
    const char   *password,         // (I) パスワード
    long         *numOfCategories,  // (I) 取得するカテゴリの数
                                    // (O) 取得したカテゴリの数
    CATLISTINF_t categories );      // (O) 取得したカテゴリ情報

int
getBlogIDsExciteBlog(
    const char *userName,       // (I) ユーザ名
    const char *password,       // (I) パスワード
    int        *numberOfBlogs,  // (I) 取得する blog 情報の数
                                // (O) 取得した blog 情報の数
    BLOGINF    *blogInfo );     // (O) 取得した blog 情報

int
getCategoryListEchoo(
    const char   *userName,         // (I) ユーザ名
    const char   *password,         // (I) パスワード
    long         *numOfCategories,  // (I) 取得するカテゴリの数
                                    // (O) 取得したカテゴリの数
    CATLISTINF_t categories );      // (O) 取得したカテゴリ情報

int
getBlogIDsEchoo(
    const char *userName,       // (I) ユーザ名
    const char *password,       // (I) パスワード
    int        *numberOfBlogs,  // (I) 取得する blog 情報の数
                                // (O) 取得した blog 情報の数
    BLOGINF    *blogInfo );     // (O) 取得した blog 情報

int
getCategoryListRakuten(
    const char   *userName,         // (I) ユーザ名
    const char   *password,         // (I) パスワード
    long         *numOfCategories,  // (I) 取得するカテゴリの数
                                    // (O) 取得したカテゴリの数
    CATLISTINF_t categories );      // (O) 取得したカテゴリ情報

int
getBlogIDsRakuten(
    const char *userName,       // (I) ユーザ名
    const char *password,       // (I) パスワード
    int        *numberOfBlogs,  // (I) 取得する blog 情報の数
                                // (O) 取得した blog 情報の数
    BLOGINF    *blogInfo );     // (O) 取得した blog 情報

int
getBlogIDsTumblr(
    const char *userName,       // (I) ユーザ名(メールアドレス)
    const char *password,       // (I) パスワード
    int        *numberOfBlogs,  // (I) 取得する blog 情報の数
                                // (O) 取得した blog 情報の数
    BLOGINF    *blogInfo );     // (O) 取得した blog 情報

/*
 *  blog 情報
 */
typedef struct blog_info    {
    char        *blogToolName;  // blogツール名
    char        *blogTypeName;  // blogType に対応する文字列
    BLOGINFOTBL blogInfoTbl;    // blog情報テーブル
}   BLOG_INFO;


/*
 *  投稿時の各種パラメータ
 */
typedef struct postArticleInfo  {
    char      blogUserName[MAX_USERIDLEN + 1];     /* blog login 名         */
    char      blogPassword[MAX_PASSWDLEN + 1];     /* blog パスワード       */
    char      blogID[MAX_BLOGIDLENGTH + 1];        /* blogID                */
    char      blogURL[MAX_URLLENGTH + 1];          /* blog URL              */
    BLOGKIND  blogType;                            /* blog種別              */
    char      endpointURL[MAX_URLLENGTH + 1];      /* エンドポイントURL     */
    int       charSet;                             /* 文字コード種別        */
    int       useHatenaLink;                  /* キーワードリンク埋設の要否 */
    int       useProxy;                       /* proxy経由で通信するか否か  */
    int       useSimilarity;                        /* おすすめを使うか否か */
    char      amazonAssociateID[MAX_NAMELEN + 1];   /* AmazonアソシエイトID */
    char      rakutenAffiliateID[MAX_KEYLENGTH + 1];/* 楽天アフィリエイトID */
    int       numOfRecomended;                      /* おすすめ掲載件数     */
    char      categoryName[MAX_CATIDLENGTH + 1];    /* 投稿対象のカテゴリ名 */
    char      templateID[MAX_CATIDLENGTH + 1];      /* テンプレートID       */
}   POST_INFO;

typedef struct articleInfo {
    char      *title;       // 記事題名
    char      *body;        // 記事本文
    char      *summary;     // 記事概要   (option)
    char      *extended;    // 追記       (option)
    char      *keyword;     // キーワード (option)
#if 0
    int       yyyy;         // 投稿日時 (年)
    int       mm;           // 投稿日時 (月)
    int       dd;           // 投稿日時 (日)
    int       HH;           // 投稿日時 (時)
    int       MM;           // 投稿日時 (分)
    int       SS;           // 投稿日時 (秒)
#endif
}   ARTICLE_INFO;


#define EID_LENGTH      32  /* excite ID 最大長 */


BOOL
postArticle(
        const ARTICLE_INFO *article,
        const POST_INFO    *postInfo
    );

#endif  /* __POST_ARTICLE_H__ */
