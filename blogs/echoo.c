/*
 *  echoo.c
 *      エコログ投稿処理
 *
 *      written by H.Tsujimura    25 Nov 2004 / 2 Oct 2006
 *
 *      Copyright (c) 2004, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードを少し改造して流用
 *
 * History:
 * $Log: /comm/blogolee/blogs/echoo.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     08/09/10 21:41 Tsujimura543
 * loginEchoo(), postEchoo(), getCategoryListEchoo(),
 * getBlogIDsEchoo() を xmlRPC.dll から移管
 * 
 * 4     07/03/06 0:08 Tsujimura543
 * コメントを修正
 * 
 * 3     07/03/06 0:06 Tsujimura543
 * 標準エラー出力にエラーメッセージを出力できない場合は、メッセージボック
 * スを使ってエラーメッセージを表示するようにした
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * フィックス
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe 暫定版 (動作確認済み)
 * 
 * 2     06/10/02 20:08 Tsujimura543
 * cocousagi.h をインクルードするようにする
 * 
 * 1     06/10/02 19:05 Tsujimura543
 * cocousagi.c から エコログ 特有の処理を分離
 */

#ifdef  WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "xmlRPC.h"
#include "multipart.h"
#include "../postArticle.h"

/*
 * エコログ向け投稿処理
 */

/* 指定文字列は10進文字列か否か */
int
isDecString( const char *p )
{
    int ret = 1;

    while ( *p ) {
        if ( (*p >= '0') && (*p <= '9') ) {
            p++;
            continue;
        }

        ret = 0;
        break;
    }

    return ( ret );
}

int
selectOpenClassification()
{
    int     openClass = 0, i = 6;
    int     numOfOpenClasses = 6;
    BOOL    done = FALSE;

    do {
        fputs( "\n公開区分: \n", stderr );
        fputs( "\t[1] 下書き\n", stderr );
        fputs( "\t[2] Echoo!お友達のみ公開\n", stderr );
        fputs( "\t[3] ゆびとまお友達のみ公開\n", stderr );
        fputs( "\t[4] Echoo!内のみ公開\n", stderr );
        fputs( "\t[5] ゆびとま内のみ公開\n", stderr );
        fputs( "\t[6] 外部公開\n", stderr );
        done = inputNumeric( &i, 1, numOfOpenClasses );
    } while ( !done );

    switch ( i ) {
    case 1:
        openClass = 0;
        break;
    case 2:
        openClass = 1;
        break;
    case 3:
        openClass = 2;
        break;
    case 4:
        openClass = 3;
        break;
    case 5:
        openClass = 6;
        break;
    case 6:
    default:
        openClass = 4;
        break;
    }

    return ( openClass );
}

int
loginEchoo( const char *username,   // (I) Echoo! ID (メールアドレス)
            const char *password,   // (I) パスワード
            char       *cookie,     // (O) クッキー
            char       *myBlogURL ) // (O) 自blogトップページURL
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !username || !(*username) ||
         !password || !(*password) ||
         !cookie )
         return ( ret );

 // if ( !username )
 //     username = xmlrpc_p->userName;
 // if ( !password )
 //     password = xmlrpc_p->password;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    strcpy( url, "https://echoo.yubitoma.or.jp/index.htm" );
    setTargetURL( url );
    sprintf( request,
             "loginid=%s&"
             "pw=%s"     /*
             "&submit=%s"*/,
             username, password /* ,
             encodeURL(sjis2euc("ログイン")) */ );
    setUpReceiveBuffer( response, sz );
 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            "application/x-www-form-urlencoded",
 //                            request, response, cookie,
 //                            NULL, NULL );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

 // if ( ret == -1 )
 //     ret = 0;        /* サーバとの通信失敗 */
 // else
    if ( *response ) {
        if ( strstr( response, sjis2euc("さんのマイホームです") ) != NULL ) {
            char    *p, *q;
            ret = 1;    /* ログイン成功 */

            /* 自blog URLを取得 */
            p = strstr( response, sjis2euc( "マイエコログ表示" ) );
            if ( p ) {
                while ( *p ) {
                    p--;
                    if ( (*p == ':') && !strncmp( p - 4, "http", 4 ) ) {
                        p -= 4;
                        q = strchr( p, '"' );
                        if ( q ) {
                            strncpy( myBlogURL, p, q - p );
                            myBlogURL[q - p] = NUL;
                            break;
                        }
                    }
                }
            }
        }
        else
            ret = 0;    /* ログイン失敗 */
    }

    free( response );
    free( request  );

    return ( ret );
}


int
postEchoo( const char *username,    // (I) Echoo! ID (メールアドレス)
           const char *password,    // (I) パスワード
           char       *cookie,      // (I/O) クッキー
           const char *categoryID,  // (I) カテゴリID (10進整数)
                                    //     または カテゴリ名
           const char *title,       // (I) 記事題名
           const char *body )       // (I) 記事本文
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    catID[36];
    char    url[MAX_URLLENGTH];
    char    contentType[128];
    char    *separator = getMultiPartID();
    char    *p;
    int     openClass;
    size_t  sz = MAX_CONTENT_SIZE * 4;

    if ( !username || !(*username) ||
         !password || !(*password) ||
         !title    || !(*title)    ||
         !body     || !(*body)     ||
         !cookie   || !(*cookie)      )
        return ( ret );

 // if ( !username )
 //     username = xmlrpc_p->userName;
 // if ( !password )
 //     password = xmlrpc_p->password;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    setUpReceiveBuffer( response, sz );
    if ( !categoryID || !(*categoryID) ) {
        /* カテゴリ一覧の取得 */
     // httpGetBufferWithSession(
     //     "http://echoo.yubitoma.or.jp/blog/entry.htm",
     //     response, TRUE, NULL, NULL, cookie,
     //     NULL, NULL );
        http_getEx( "http://echoo.yubitoma.or.jp/blog/entry.htm",
                     response, cookie );

        /* カテゴリの選択 */
        getCategoryIDstring( catID, response,
                             "<option value=\"\">--",
                           "</select>&nbsp;&nbsp;<a href=\"./category.htm\">",
                             "<option value=\"", "\">",
                             CHARSET_EUCJP );
    }
    else if ( !isDecString( categoryID ) ) {
        /* カテゴリ一覧の取得 */
     // httpGetBufferWithSession(
     //     "http://echoo.yubitoma.or.jp/blog/entry.htm",
     //     response, TRUE, NULL, NULL, cookie,
     //     NULL, NULL );
        http_getEx( "http://echoo.yubitoma.or.jp/blog/entry.htm",
                    response, cookie );

        /* カテゴリ名 → カテゴリID 変換 */
        getCategoryIDbyName( catID, categoryID, response,
                             "<option value=\"\">--",
                           "</select>&nbsp;&nbsp;<a href=\"./category.htm\">",
                             "<option value=\"", "\">",
                             CHARSET_EUCJP );
    }
    else
        strncpy( catID, categoryID, 32 );

    /* 公開区分の選択 */
    openClass = selectOpenClassification();

    /* 投稿 */
    sprintf( contentType, "multipart/form-data; boundary=%s", separator );
    strcpy( url, "http://echoo.yubitoma.or.jp/blog/entry.htm" );
    setTargetURL( url );
    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "e_kind", 0,
#if 0
                    "http://echoo.yubitoma.or.jp/blog/entry.htm?e_kind=1"
#else
                    "1"
#endif
                    , NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "title", 0, sjis2euc( title ), NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "category", 0, catID, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "entry", 0, sjis2euc( body ), NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "imgfile", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "amazon", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "trackbackurl", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_INTEGER,
                               "b_open", openClass, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "w_place", 0, "NULL", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "echoo_entry", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "eid", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "proc", 0, "kakunin", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "amazon_hidden", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "tmp_title", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "image", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "e_title", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "person", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "flg", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "sdate", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "m_factur", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "search_mode", 0, NULL, NULL ) );
    sprintf( request + strlen( request ), "--%s--\r\n", separator );

    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL );
    setUpReceiveBuffer( response, sz );
 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            contentType,
 //                            request, response, cookie,
 //                            NULL, NULL );
    http_postEx( url, contentType, request, response, cookie );

    /* 投稿確認 */
    strcpy( url, "http://echoo.yubitoma.or.jp/blog/entry.htm" );
    setTargetURL( url );
#if 0
    sprintf( request,
             "e_kind=1&"
             "tmp_title=&"
             "image=&"
             "person=&"
             "flg=&"
             "sdate=&"
             "m_factur=&"
             "search_mode=&"
             "title=%s&",
             sjis2euc( title ) );
    sprintf( request + strlen( request ),
             "entry=%s&"
             "category=%s&"
             "proc=write&"
             "b_open=%d&"
             "w_place=NULL&"
             "MAX_FILE_SIZE=",
             encodeURL( sjis2euc( body ) ), catID, openClass );
    setUpReceiveBuffer( response, sz );
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               "application/x-www-form-urlencoded",
                               request, response, cookie );
#else
    /* 投稿確認画面も application/x-www-form-urlencoded →      */
    /*                         multipart/form-data に変更された */
    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "e_kind", 0, "1", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "tmp_title", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "image", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "e_title", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "person", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "flg", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "sdate", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "m_factur", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "search_mode", 0, NULL, NULL ) );

    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "title", 0, sjis2euc( title ), NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "entry", 0, sjis2euc( body ), NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "category", 0, catID, NULL ) );

    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "proc", 0, "write", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_INTEGER,
                               "b_open", openClass, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "w_place", 0, "NULL", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "MAX_FILE_SIZE", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "imgsize", 0, "150", NULL ) );
    sprintf( request + strlen( request ), "--%s--\r\n", separator );

    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL );
    setUpReceiveBuffer( response, sz );
 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            contentType,
 //                            request, response, cookie,
 //                            NULL, NULL );
    http_postEx( url, contentType, request, response, cookie );
    ret = 1;
#endif

    if ( !(response[0])                           ||
         (((p = euc2sjis(response)) != NULL) &&
          !strstr( p, "記事修正・削除" )        )    ) {
        // 投稿失敗
        fputs( "投稿に失敗しました。\n", stderr );
        ret = -1;
    }

    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}

int
getCategoryListEchoo(
    const char   *userName,         // (I) ユーザ名
    const char   *password,         // (I) パスワード
    long         *numOfCategories,  // (I) 取得するカテゴリの数
                                    // (O) 取得したカテゴリの数
    CATLISTINF_t categories )       // (O) 取得したカテゴリ情報
{
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    int     numOfCats = 0;
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !numOfCategories                      ||
         (*numOfCategories <= 0)               ||
         !categories                              )
        return ( numOfCats );

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginEchoo( userName, password, cookie, url ) ) {
            request  = (char *)malloc( MAX_CONTENT_SIZE );
            if ( !request ) {
                free( cookie );
                return ( numOfCats );
            }
            response = (char *)malloc( sz );
            if ( !response ) {
                free( request );
                free( cookie );
                return ( numOfCats );
            }
            memset( request,  0x00, MAX_CONTENT_SIZE );

            /* カテゴリ一覧の取得 */
            setUpReceiveBuffer( response, sz );
         // httpGetBufferWithSession(
         //     "http://echoo.yubitoma.or.jp/blog/entry.htm",
         //     response, TRUE, NULL, NULL, cookie,
         //     NULL, NULL );
            http_getEx( "http://echoo.yubitoma.or.jp/blog/entry.htm",
                        response, cookie );

            /* カテゴリ情報の抽出 */
            numOfCats = getCategoryIDs( numOfCategories, categories,
                                        response,
                                        "<option value=\"\">--",
                           "</select>&nbsp;&nbsp;<a href=\"./category.htm\">",
                                        "<option value=\"", "\">",
                                        CHARSET_EUCJP );

            free( response );
            free( request  );
        }

        free( cookie );
    }

    *numOfCategories = numOfCats;

    return ( numOfCats );
}

int
getBlogIDsEchoo(
    const char *userName,       // (I) ユーザ名
    const char *password,       // (I) パスワード
    int        *numberOfBlogs,  // (I) 取得する/取得した blog 情報の数
    BLOGINF    *blogInfo )      // (O) 取得した blog 情報
{
    char    cookie[MAX_COOKIE_LEN];
    char    url[MAX_URLLENGTH];
    int     numOfBlogs = 0;

    cookie[0] = NUL;
    url[0]    = NUL;
    loginEchoo( userName, password, cookie, url );
    if ( url[0] ) {
        size_t  sz = MAX_CONTENT_SIZE;
        char    *response;

        strcpy( blogInfo[0].url, url );
        blogInfo[0].blogName[0] = NUL;
        blogInfo[0].blogID[0]   = NUL;

        response = (char *)malloc( sz );
        if ( response ) {
            setUpReceiveBuffer( response, sz );
            http_get( url, response );
            if ( *response ) {
                char        target[BUFSIZ];
                const char  *p, *q;

                target[0] = NUL;
                p = strstr( response, "<title>" );
                if ( p ) {
                    p += 7;
                    q = strstr( p, " - Echoo!" );
                    if ( q ) {
                        strncpy( target, p, q - p );
                        target[q - p] = NUL;
                    }
                }
                else {
                    p = strstr( response, "<h1><a href=\"" );
                    if ( p ) {
                        p = strchr( p + 13, '>' );
                        if ( p ) {
                            p++;
                            q = strstr( p, "</a>" );
                            if ( q ) {
                                strncpy( target, p, q - p );
                                target[q - p] = NUL;
                            }
                        }
                    }
                }

                if ( target[0] ) {
                    p = euc2sjis( target );
                    strcpy( blogInfo[0].blogName, p ? p : target );
                }
            }

            free( response );
        }

        numOfBlogs = 1;
    }

    *numberOfBlogs = numOfBlogs;

    return ( numOfBlogs );
}


char    *
editForEchoo( char *text )
{
    char    *p = text;
    char    *tmp, *q;

    if ( !p || !(*p) )
        return ( text );

    tmp = (char *)malloc( strlen( p ) + 1 );
    if ( tmp )
        q = tmp;
    else
        q = p;

    /* この関数の処理内容            */
    /*   (1) <br /> を改行に置換する */
    /*   (2) <p>, <cite> を取り除く  */
    /*   (3) class 属性を取り除く    */

    while ( *p ) {
        if ( !strncmp( p, "<br />", 6 ) ) {
            /* (1) <br /> を改行に置換する */
            p += 6;
            *q++ = '\r';
            *q++ = '\n';
        }
        else if ( !strncmp( p, "<p>", 3 ) ) {
            /* (2a1) <p> を取り除く */
            p += 3;
        }
        else if ( !strncmp( p, "</p>", 4 ) ) {
            /* (2a2) </p> を取り除く */
            p += 4;
            *q++ = '\r';
            *q++ = '\n';
        }
        else if ( !strncmp( p, "<cite>", 6 ) ) {
            /* (2b1) <cite> を取り除く */
            const char  *pp = "<i>";

            p += 6;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "</cite>", 7 ) ) {
            /* (2b2) </cite> を取り除く */
            const char  *pp = "</i>";

            p += 7;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "class=\"", 7 ) ) {
            /* (3) class="..." を取り除く */
            char    *r;
            p += 7;
            r = strchr( p, '"' );
            if ( r )
                p = r + 1;
        }
        else
            *q++ = *p++;
    }
    *q = NUL;

    if ( tmp ) {
        strcpy( text, tmp );
        free( tmp );
    }

    return ( text );
}

int
postArticleOnEchoo( const char *userName,       /* ユーザ名     */
                    const char *password,       /* パスワード   */
                    char       *title,          /* 投稿記事題名 */
                    char       *body,           /* 投稿記事本文 */
                    const char *categoryName )  /* カテゴリ名   */
{
    int     ret     = 0;
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );
    char    myBlogURL[MAX_URLLENGTH];

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginEchoo( userName, password, cookie, myBlogURL ) ) {
            const char  *t;

            t = editForEchoo( body );
            ret = postEchoo( userName, password, cookie,
                             (categoryName && *categoryName)
                                ? categoryName  /* カテゴリ名 */
                                : "",  /* カテゴリID: 空文字列 は「未設定」 */
                             title, t );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login に失敗しました。\n" );
        else
            MessageBox( NULL, "login に失敗しました。    ",
                        "エコログ", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
