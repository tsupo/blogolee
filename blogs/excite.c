/*
 *  excite.c
 *      exciteブログ 投稿処理
 *
 *      written by H.Tsujimura    27 Aug 2004 / 2 Oct 2006
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードを少し改造して流用
 *
 * History:
 * $Log: /comm/blogolee/blogs/excite.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     08/09/11 0:01 Tsujimura543
 * ソースを整理
 * 
 * 5     08/09/10 23:01 Tsujimura543
 * loginExciteBlog(), postExciteBlog(), getCategoryListExciteBlog(),
 * getBlogIDsExciteBlog() を xmlRPC.dll から移管
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
 * 1     06/10/02 19:50 Tsujimura543
 * cocousagi.c から exciteブログ 特有の処理を分離
 */

#ifdef  WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "xmlRPC.h"
#include "../postArticle.h"

/*
 * exciteブログ向け投稿処理
 */

#define IPADDR_LENGTH   ((3 + 1 + 3 + 1 + 3 + 1 + 3) + 1)
                                            /* aaa.bbb.ccc.ddd */
#define EID_LENGTH      32
#define TEMPKEY_LENGTH  32

#ifdef  RESEARCH_FOR_EXCITEBLOG
void    saveReport( const char *htmlSrcCode )
{
    char        filename[MAX_PATH];
    FILE        *fp;
    int         cnt  = 1;
    BOOL        done = FALSE;
    static int  pre  = 0;

    if ( !pre ) {
        do {
            sprintf( filename,
                     cnt > 9999 ? "report%06d.log"
                                : "report%04d.log",
                     cnt );
            fp = fopen( filename, "r" );
            if ( fp ) {
                fclose( fp );
                cnt++;
                if ( cnt > 999999 )
                    cnt = 0;
            }
            else
                done = TRUE;
        } while ( !done );

        pre = cnt;
        fp = fopen( filename, "w" );
    }
    else {
        sprintf( filename,
                 pre > 9999 ? "report%06d.log"
                            : "report%04d.log",
                 pre );
        fp = fopen( filename, "a" );
    }

    if ( fp ) {
        fputs( htmlSrcCode, fp );
        fclose( fp );
    }
}
/* ↑↑↑  ここまで  ↑↑↑ */
#endif  /* RESEARCH_FOR_EXCITEBLOG */

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
static char *
getUserIpOnExciteBlog( char *ipAddr, char *p3p )
{
    char    *p, *q;
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    response = (char *)malloc( sz );
    if ( !response )
        return ( ipAddr );

    strcpy( url, "http://www.exblog.jp/" );
    setUpReceiveBuffer( response, sz );
    http_get( url, response );
#ifdef  RESEARCH_FOR_EXCITEBLOG
    saveReport( "\n===--- getUserIpOnExciteBlog() ---===\n" );
    saveReport( response );
#endif  /* RESEARCH_FOR_EXCITEBLOG */
    p = strstr( response, "<input type=\"hidden\" name=\"userip\" value=\"" );
    if ( p ) {
        p += strlen( "<input type=\"hidden\" name=\"userip\" value=\"" );
        q = strchr( p, '\"' );
        if ( q ) {
            strncpy( ipAddr, p, q - p );
            ipAddr[q - p] = '\0';
        }
    }

    free( response );

    return ( ipAddr );
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

static char *
getMyBlogURL( char *myBlogURL, const char *htmlSrcCode )
{
    char    *p, *q;

    p = strstr( htmlSrcCode, "self.location.href=\'" );
    if ( p ) {
        p += 20;
        q = strchr( p, '\'' );
        if ( q ) {
            strncpy( myBlogURL, p, q - p );
            myBlogURL[q - p] = '\0';
        }
    }

    return ( myBlogURL );
}


static char *
getEID( char *eid, const char *htmlSrcCode )
{
    char    *p, *q, *r;

    p = strstr( htmlSrcCode,
                "<A HREF=http://www.exblog.jp/blog/insert.asp?" );
    if ( !p )
        p = strstr( htmlSrcCode,
                    "<a href=\"http://www.exblog.jp/myblog/?" );
    if ( p ) {
        p = strchr( p, '?' );
        if ( p ) {
            p = strchr( p, '=' );
            if ( p && *++p ) {
                q = strchr( p, '>' );
                r = strchr( p, '"' );
                if ( q && r && (q > r) )
                    q = r;
                if ( q ) {
                    strncpy( eid, p, q - p );
                    eid[q - p] = '\0';
                }
            }
        }
    }

    return ( eid );
}

static char *
getTempKey( char *tempkey, const char *htmlSrcCode )
{
    char    *p, *q;

    p = strstr( htmlSrcCode, "<input type=\"hidden\" name=\"tempkey\"" );
    if ( p ) {
        p += strlen( "<input type=\"hidden\" name=\"tempkey\"" );
        p = strchr( p, '\"' );
        if ( p && *++p ) {
            q = strchr( p, '\"' );
            if ( q ) {
                strncpy( tempkey, p, q - p );
                tempkey[q - p] = '\0';
            }
        }
    }

    return ( tempkey );
}

static char *
getCgiID( int *categoryID, char *catName, const char *htmlSrcCode )
{
    getCategoryIDwithName( categoryID, catName, htmlSrcCode, 2,
                           "<select name=\"cgiid\"", "</select>",
                           "<option value=\"", "</option>",
                           CHARSET_UTF8 );

    if ( !(*catName) )
        strcpy( catName, encodeURL( sjis2utf( "未分類" ) ) );

    return ( catName );
}


int
loginExciteBlog( const char *username,
                 const char *password,
                 char       *cookie,
                 char       *myBlogURL,
                 char       *eid )
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    ipAddr[IPADDR_LENGTH];  /* aaa.bbb.ccc.ddd */
    char    p3p[BUFSIZ];
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !username || !(*username) ||
         !password || !(*password) ||
         !cookie )
         return ( ret );

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );
    memset( p3p,     0x00, BUFSIZ );
    memset( ipAddr,  0x00, IPADDR_LENGTH );

    getUserIpOnExciteBlog( ipAddr, p3p );

    if ( ipAddr[0] != NUL ) {
        strcpy( url,
                "http://www.exblog.jp/authid.asp"
             // "https://sec.exblog.jp/authid.asp"
            );
        sprintf( request,
                 "userip=%s&"
                 "returnurl=http%%3A%%2F%%2Fwww.exblog.jp&"
                 "loginurl=http%%3A%%2F%%2Fwww.exblog.jp&"
                 "userid=%s&"
                 "userpwd=%s&"
                 "ssl=1",
                 ipAddr, username, password );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        if ( *response ) {
#ifdef  RESEARCH_FOR_EXCITEBLOG
            saveReport( "\n===--- loginExciteBlog() ---===\n" );
            saveReport( response );
#endif  /* RESEARCH_FOR_EXCITEBLOG */
            if ( strstr( response, sjis2utf("ようこそ") ) != NULL ) {
                char    *cookie2;

                ret = 1;    /* ログイン成功 */
                getMyBlogURL( myBlogURL, response );
                getEID( eid, response );
                cookie2 = (char *)malloc( strlen(cookie) + 1 );
                if ( cookie2 )
                    strcpy( cookie2, strstr( cookie, "Cookie: " ) + 8 );

                /* login 済み状態を示す cookie を取得 */
                setUpReceiveBuffer( response, sz );
                http_getEx( myBlogURL, response, cookie );
                if ( cookie2 ) {
                    /* 2つの cookie を合体 */
                    char    *p = strstr( cookie, "; " );
                    strcpy( p ? p + 2 : cookie + strlen( cookie ) - 2,
                            cookie2 );
                    free( cookie2 );
                }
            }
            else
                ret = 0;    /* ログイン失敗 */
        }
    }

    free( response );
    free( request  );

    return ( ret );
}

int
postExciteBlog( const char *username,
                const char *password,
                char       *cookie,
                const char *myBlogURL,      /* マイブログ トップページ URL */
                                            /*   (login中は管理画面になる) */
                const char *eid,            /* excite ID (blog ID 相当)    */
                int        categoryID,      /* カテゴリID */
                const char *categoryName,   /* カテゴリ名 */
                const char *title,          /* 題名       */
                const char *body,           /* 本文       */
                const char *extend )        /* 追記       */
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
 // char    p3p[BUFSIZ];
    char    tempkey[TEMPKEY_LENGTH];
    char    catName[MAX_CATNAMELENGTH];
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !username || !(*username) ||
         !password || !(*password) ||
         !title    || !(*title)    ||
         !body     || !(*body)     ||
         !cookie   || !(*cookie)   ||
         !eid      || !(*eid)         )
         return ( ret );

    if ( categoryID <= 0 )
        categoryID = 1; /* 未分類 */

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    /* tempkeyの取得 */
 // sprintf( url, "http://www.exblog.jp/blog/insert.asp?eid=%s", eid );
    sprintf( url, "http://www.exblog.jp/myblog/entry/new/?eid=%s", eid );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
#ifdef  RESEARCH_FOR_EXCITEBLOG
    saveReport( "\n===--- getTempKey() & getCgiID() ---===\n" );
    saveReport( response );
#endif  /* RESEARCH_FOR_EXCITEBLOG */
    getTempKey( tempkey, response );

    if ( categoryName && *categoryName ) {
        /* カテゴリ名 → カテゴリID 変換 */
        char    catID[64];
        char    *p;

        getCategoryIDbyName( catID, categoryName, response,
                             "<select name=\"cgiid\"", "</select>",
                             "<option value=\"", "</option>",
                             CHARSET_UTF8 );
        if ( *catID )
            categoryID = atol( catID );
        p = sjis2utf( categoryName );
        strcpy( catName, p ? p : categoryName );
    }
    else {
        /* categoryID に対応するカテゴリ名の取得 */
        getCgiID( &categoryID, catName, response );
    }

    /* 投稿 */
 // strcpy( url, "http://www.exblog.jp/blog/insert_exec.asp" );
    strcpy( url, "http://www.exblog.jp/myblog/entry/new/new.asp" );

    sprintf( request,
             "eid=%s&"
             "tempkey=%s&"
             "rtnurl=%s&"
             "cgiid=%d&"
             "cgname=%s&"
             "subject=%s&"
             "pstdate=0&"   /* 2004.10.08 管理画面の仕様変更に伴い、追加 */
             "content=%s&"
             "htmlflag=1&",
             eid, tempkey, myBlogURL, categoryID, catName,
             title, body );

    if ( extend && *extend )
        sprintf( request + strlen( request ),
                 "moreflag=1&"
                 "moresubject=%s%%20(%s)&"
                 "morecontent=%s&",
                 title, extend, encodeURL( sjis2utf( "つづき" ) ) );
    else
        strcat( request,
                "moreflag=0&"
                "moresubject=&"
                "morecontent=&" );

    strcat( request,
            "openflag=1&"
            "cmtflag=1&"
            "trbflag=1&"
            "trburl=&tburlslt=" );

    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
#ifdef  RESEARCH_FOR_EXCITEBLOG
    saveReport( sjis2utf( "\n===--- 投稿 ---===\n" ) );
    saveReport( response );
#endif  /* RESEARCH_FOR_EXCITEBLOG */

    encodeURL( NULL );
    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}

int
getCategoryListExciteBlog(
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
    char    p3p[BUFSIZ];
    char    eid[EID_LENGTH];
    int     numOfCats = 0;
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !numOfCategories                      ||
         (*numOfCategories <= 0)               ||
         !categories                              )
        return ( numOfCats );

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginExciteBlog( userName, password, cookie, url, eid ) ) {
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
            memset( request, 0x00, MAX_CONTENT_SIZE );
            memset( p3p,     0x00, BUFSIZ );

            /* カテゴリ一覧の取得 */
         // sprintf( url, "http://www.exblog.jp/blog/insert.asp?eid=%s", eid);
            sprintf(url, "http://www.exblog.jp/myblog/entry/new/?eid=%s",eid);
            setUpReceiveBuffer( response, sz );
            http_getEx( url, response, cookie );

            /* カテゴリ情報の抽出 */
            numOfCats = getCategoryIDs( numOfCategories, categories,
                                        response,
                                        "<select name=\"cgiid\"", "</select>",
                                        "<option value=\"", "</option>",
                                        CHARSET_UTF8 );
            if ( numOfCats == 0 ) {
                strcpy( categories[0].categoryId, "00000000" );
                strcpy( categories[0].categoryName, "未分類" );
                numOfCats = 1;
            }
            else if ( numOfCats > 0 ) {
                if ( !strcmp( categories[0].categoryName, "== 選択 ==" ) )
                    strcpy( categories[0].categoryName, "未分類" );
            }

            free( response );
            free( request  );
        }

        free( cookie );
    }

    *numOfCategories = numOfCats;

    return ( numOfCats );
}

int
getBlogIDsExciteBlog(
    const char *userName,       // (I) ユーザ名
    const char *password,       // (I) パスワード
    int        *numberOfBlogs,  // (I) 取得する/取得した blog 情報の数
    BLOGINF    *blogInfo )      // (O) 取得した blog 情報
{
    char    cookie[MAX_COOKIE_LEN];
    char    url[MAX_URLLENGTH];
    char    eid[EID_LENGTH];
    int     numOfBlogs = 0;

    cookie[0] = NUL;
    url[0]    = NUL;
    eid[0]    = NUL;
    loginExciteBlog( userName, password, cookie, url, eid );
    if ( url[0] ) {
        size_t  sz = MAX_CONTENT_SIZE;
        char    *response;

        strcpy( blogInfo[0].url,    url );
        strcpy( blogInfo[0].blogID, eid );
        blogInfo[0].blogName[0] = NUL;

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
                    q = strstr( p, "</title>" );
                    if ( q ) {
                        strncpy( target, p, q - p );
                        target[q - p] = NUL;
                    }
                }

                if ( target[0] ) {
                    p = utf2sjis( target );
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
postArticleOnExcite( const char *userName,      /* ユーザ名     */
                     const char *password,      /* パスワード   */
                     char       *title,         /* 投稿記事題名 */
                     char       *body,          /* 投稿記事本文 */
                     char       *extended,      /* 投稿記事追記 */
                     const char *categoryName ) /* カテゴリ名   */
{
    int     ret     = 0;
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );
    char    myBlogURL[MAX_URLLENGTH];
    char    eid[EID_LENGTH];

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginExciteBlog( userName, password, cookie, myBlogURL, eid ) ) {
            char    *s, *t;

            s = encodeURL( sjis2utf( title ) );
            strcpy( title, s );
            t = encodeURL( sjis2utf( body ) );
            strcpy( body,  t );
            if ( extended && *extended ) {
                char    *u;

                u = encodeURL( sjis2utf( extended ) );
                strcpy( extended, u );
            }
            ret = postExciteBlog( userName, password, cookie, myBlogURL, eid,
                                  1, /* カテゴリID: 暫定 (1 は「未分類」) */
                                  categoryName, /* カテゴリ名 */
                                  title, body,
                                  extended && *extended ? extended : NULL );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login に失敗しました。\n" );
        else
            MessageBox( NULL, "login に失敗しました。    ",
                        "exciteブログ", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
