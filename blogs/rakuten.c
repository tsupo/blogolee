/*
 *  rakuten.c
 *      楽天ブログ投稿処理
 *
 *      written by H.Tsujimura    21 Apr 2005 / 2 Oct 2006
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードを少し改造して流用
 *
 * History:
 * $Log: /comm/blogolee/blogs/rakuten.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     08/09/10 18:02 Tsujimura543
 * loginRakuten(), postRakuten(), getCategoryListRakuten(),
 * getBlogIDsRakuten() を xmlRPC.dll から移管
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
 * 3     07/01/23 15:33 Tsujimura543
 * (1) 楽天ブログの新しい管理画面に対応
 * (2) 楽天ブログにカテゴリ指定して投稿できるようにした
 * 
 * 2     06/10/02 20:08 Tsujimura543
 * cocousagi.h をインクルードするようにする
 * 
 * 1     06/10/02 18:54 Tsujimura543
 * cocousagi.c から 楽天ブログ 特有の処理を分離
 */

#ifdef  WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "xmlRPC.h"
#include "../postArticle.h"

/*
 * 「楽天広場」改め「楽天ブログ」向け投稿処理
 */

/* 自 blog URL を取得 */
static char *
getBlogURL( char *url, const char *htmlSrc )
{
    const char  *p, *q;

    p = strstr( htmlSrc, sjis2euc("Myページの確認") );
    if ( p ) {
        while ( p > htmlSrc ) {
            if ( *--p != 'h' )
                continue;
            if ( !strncmp( p, "href=\"http://plaza.rakuten.co.jp/", 33 ) ) {
                p += 6;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( url, p, q - p );
                    url[q - p] = NUL;
                }
                break;
            }
        }
    }

    return ( url );
}

int
loginRakuten( const char *username,
              const char *password,
              char       *cookie,
              char       *myBlogURL )
{
    int     ret = 0;
    char    *request;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;
    char    url[MAX_URLLENGTH];

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

    memset( request, 0x00, MAX_CONTENT_SIZE );
    strcpy( url,
     "https://grp02.id.rakuten.co.jp/rms/nid/vc?__event=login&service_id=59");
    setTargetURL( url );
    sprintf( request,
             "u=%s&"
             "p=%s&"
             "autologin=true",
             username, password );
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
        if ( strstr( response, "class=\"loginUser\"" ) &&
             strstr( response, "class=\"blogData\"" )     ) {
            ret = 1;    /* ログイン成功 */
            getBlogURL( myBlogURL, response );
        }
        else
            ret = 0;    /* ログイン失敗 */
    }

    free( response );
    free( request  );

    return ( ret );
}


int
postRakuten( const char *username,
             const char *password,
             char       *cookie,
             const char *categoryName,  /* カテゴリ名 */
             const char *title,         /* 題名       */
             const char *body )         /* 本文       */
{
    int         ret = 0;
    char        *request;
    char        *response;
    size_t      sz = MAX_CONTENT_SIZE * 4;
    char        url[MAX_URLLENGTH];
    char        var_dummy[80];
    char        ch[80];
    int         yyyy, mm, dd;
    time_t      t;
    struct tm   *tm;
    int         categoryID = 0; /* デフォルトは「カテゴリ未分類」 */

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

    /* var_dummy 取得 */
    memset( request, 0x00, MAX_CONTENT_SIZE );
    var_dummy[0] = NUL;
    ch[0]        = NUL;
    strcpy( url, "http://my.plaza.rakuten.co.jp/?func=diary&act=write" );
    setUpReceiveBuffer( response, sz );
 // httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
 //                           NULL, NULL );
    http_getEx( url, response, cookie );
    if ( response[0] ) {
        char    *p = strstr( response, "name=\"var_dummy\"" );
        char    *q;

        if ( p ) {
            p += 16;
            q = strstr( p, "value=\"" );
            if ( q ) {
                q += 7;
                p = strchr( q, '"' );
                if ( p ) {
                    strncpy( var_dummy, q, p - q );
                    var_dummy[p - q] = NUL;
                }
            }
        }

        p = strstr( response, "name=\"ch\"" );
        if ( p ) {
            p += 9;
            q = strstr( p, "value=\"" );
            if ( q ) {
                q += 7;
                p = strchr( q, '"' );
                if ( p ) {
                    strncpy( ch, q, p - q );
                    ch[p - q] = NUL;
                }
            }
        }

        if ( categoryName && *categoryName ) {
            /* カテゴリ名 → カテゴリID 変換 */
            char    catID[64];

            getCategoryIDbyName( catID, categoryName, response,
                                 "<select name=\"cate_id\">",
                                 "</select>",
                                 "<option value=\"", "\">",
                                 CHARSET_EUCJP );
            if ( *catID )
                categoryID = atol( catID );
        }

        /* 投稿 */
        strcpy( url, "http://my.plaza.rakuten.co.jp/" );
        setTargetURL( url );

        t  = time( NULL );
        tm = localtime( &t );
        yyyy = tm->tm_year + 1900;
        mm   = tm->tm_mon + 1;
        dd   = tm->tm_mday;

        sprintf( request,
                 "theme_id=0&current_theme_id=0&ex_cate_id=0&"
                 "cate_id=%d&"  /* カテゴリID (テーマID) */
                 "d_title=%s&"  /* 題名 (160バイト以内)  */
                 "d_text=%s&"   /* 本文 */
                 "d_img_service=&"
                 "d_img_filename=&"
                 "d_img_position=0&"
                 "d_feel=1&"    /* 気持ち (普通: 1) */
                 "d_himitsu=&"  /* 非公開日記 */
                 "s_d_img_fileid=&"
                 "s_d_img_position=&"
                 "s_d_imgurl=&"
                 "s_d_img_title=&"
                 "s_d_img_w=&"
                 "s_d_img_h=&"
                 "t_img_service=&"
                 "char_dummy=%s&"
                 "var_dummy=%s&"
                 "d_date=%04d-%02d-%02d&"
                 "func=diary&act=write&"
                 "sub_act=insert&"
                 "ch=%s",
                 categoryID,
                 title, body, sjis2euc( "◇楽天◇"),
                 var_dummy, yyyy, mm, dd, ch );

        setUpReceiveBuffer( response, sz );
     // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
     //                            "application/x-www-form-urlencoded",
     //                            request, response, cookie,
     //                            NULL, NULL );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        if ( response[0] &&
             strstr( response, sjis2euc( "書き込みが完了しました" ) ) )
            ret = 0;    /* 投稿成功 */
        else
            ret = -1;   /* 投稿失敗 */
        /* 注意: 楽天広場は1日3件までしか投稿できない。4件目を投稿しようと */
        /*       するとエラーになる                                        */
    }
    else
        ret = -1;

    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}

int
getBlogIDsRakuten(
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
    loginRakuten( userName, password, cookie, url );
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
                p = strstr( response,
                            "<td class=\"title_text\" id=\"title\">" );
                if ( p ) {
                    p += 34;
                    while ( (*p == ' ')  || (*p == '\t') ||
                            (*p == '\r') || (*p == '\n')    )
                        p++;
                    q = strstr( p, "</td>" );
                    if ( q ) {
                        while ( (q > p)                   &&
                                ( (*(q - 1) == ' ')  ||
                                  (*(q - 1) == '\t') ||
                                  (*(q - 1) == '\r') ||
                                  (*(q - 1) == '\n')    )    )
                            q--;
                        strncpy( target, p, q - p );
                        target[q - p] = NUL;
                    }
                }
                else {
                    p = strstr( response, "<title>" );
                    if ( p ) {
                        p += 7;
                        q = strstr( p, sjis2euc(" - 楽天") );
                        if ( q ) {
                            strncpy( target, p, q - p );
                            target[q - p] = NUL;
                        }
                    }
                    else {
                        p = strstr( response, " id=\"counter\">" );
                        if ( p ) {
                            p += 14;
                            p = strstr( p, "<font color=\"" );
                            if ( p ) {
                                p = strchr( p + 13, '>' );
                                if ( p ) {
                                    p++;
                                    q = strstr( p, sjis2euc("&nbsp;  楽天") );
                                    if ( q ) {
                                        strncpy( target, p, q - p );
                                        target[q - p] = NUL;
                                    }
                                }
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


int
getCategoryListRakuten(
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
        if ( loginRakuten( userName, password, cookie, url ) ) {
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
            strcpy( url,
                    "http://my.plaza.rakuten.co.jp/?func=diary&act=write" );
            setUpReceiveBuffer( response, sz );
         // httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
         //                           NULL, NULL );
            http_getEx( url, response, cookie );

            /* カテゴリ情報の抽出 */
            numOfCats = getCategoryIDs( numOfCategories, categories,
                                        response,
                                        "<select name=\"cate_id\">",
                                        "</select>",
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


char    *
editForRakuten( char *text )
{
    char    *p = text;
    char    *tmp, *q, *r;

    if ( !p || !(*p) )
        return ( text );

    tmp = (char *)malloc( strlen( p ) + 1 );
    if ( tmp )
        q = tmp;
    else
        q = p;

    /* この関数の処理内容                  */
    /*   (1) class="xxx" を取り除く [必須] */

    while ( *p ) {
        if ( !strncmp( p, "class=", 6 ) ) {
            /* (1) class="xxx" を取り除く */
            r = strchr( p + 6, '"' );
            if ( r ) {
                r = strchr( r + 1, '"' );
                if ( r ) {
                    p = r + 1;
                    continue;
                }
            }

            r = strchr( p + 6, ' ' );
            if ( r ) {
                p = r;
                *q++ = *p++;// ' '
            }
            else if ( ( r = strchr( p + 6, '>') ) != NULL ) {
                p = r;
                *q++ = *p++;// '>'
            }
            else
                p += 6;
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
postArticleOnRakuten(
    const char *userName,       /* ユーザ名     */
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
        if ( loginRakuten( userName, password, cookie, myBlogURL ) ) {
            char    *s, *t;

            s = sjis2euc( title );
            strcpy( title, s );
            t = sjis2euc( editForRakuten( body ) );
            strcpy( body,  t );
            ret = postRakuten( userName, password, cookie,
                               categoryName, title, body );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login に失敗しました。\n" );
        else
            MessageBox( NULL, "login に失敗しました。    ",
                        "楽天ブログ", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
