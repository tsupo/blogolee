/*
 *  colors.c
 *      COLORS 内日記投稿処理
 *
 *      written by H.Tsujimura    27 Dec 2005 / 2 Oct 2006
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードを少し改造して流用
 *
 * History:
 * $Log: /comm/blogolee/blogs/colors.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     08/09/09 19:58 Tsujimura543
 * loginColors() と postColors() を xmlRPC.dll から移管
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
 * 1     06/10/02 18:38 Tsujimura543
 * cocousagi.c から COLORS 特有の処理を分離
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
 * COLORS向け投稿処理
 */

int
loginColors( const char *username,  // (I) COLORS ID (メールアドレス)
             const char *password,  // (I) パスワード
             char       *cookie )   // (O) クッキー
{
    int         ret = 0;
    char        *request;
    char        *response;
    char        url[MAX_URLLENGTH];
    size_t      sz = MAX_CONTENT_SIZE * 2;

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
    memset( response, 0x00, sz );

    strcpy( url, "http://clrs.jp/index.php" );
    setTargetURL( url );
    sprintf( request,
             "mode=sign&"
             "user=%s&"
             "password=%s&"
             "submit=%s&"
             "auto=on",
             username, password,
             encodeURL("ログイン") );

 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            "application/x-www-form-urlencoded",
 //                            request, response, cookie,
 //                            NULL, NULL );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

 // if ( ret == -1 )
 //     ret = 0;        /* サーバとの通信失敗 */
 // else
    if ( *response ) {
        if ( strstr( response, " alt=\"ログアウト\" " ) != NULL )
            ret = 1;    /* ログイン成功 */
        else
            ret = 0;    /* ログイン失敗 */
    }

    free( response );
    free( request  );

    return ( ret );
}


int
postColors( const char *username,   // (I) COLORS ID (メールアドレス)
            const char *password,   // (I) パスワード
            char       *cookie,     // (I/O) クッキー
            const char *title,      // (I) 記事題名
            const char *body )      // (I) 記事本文
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    contentType[128];
    char    checkcode[64];
    char    dummy[4096];
    char    *separator = getMultiPartID();
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
    memset( response, 0x00, sz );

    /* 投稿 */
    Sleep( 2000 );  /* 念のため */
    strcpy( url, "http://clrs.jp/add_diary.php?mode=addconfirm" );
    setTargetURL( url );
    sprintf( contentType, "multipart/form-data; boundary=%s", separator );
    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "magicword", 0, "入口", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "subject", 0, title, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "body", 0, body, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "MAX_FILE_SIZE", 0, "300000", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "upload_img", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "img_url1_width", 0, "0", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "img_url1", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "img_url2_width", 0, "0", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "img_url2", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "Submit", 0, "確　認", NULL ) );
    sprintf( request + strlen( request ), "--%s--\r\n", separator );

    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL );
    sprintf( dummy,
             "%sReferer: %s\r\n", cookie,
             "http://clrs.jp/add_diary.php" );
 // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
 //                            contentType,
 //                            request, response, dummy,
 //                            NULL, NULL );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, contentType, request, response, dummy );

    /* checkcode 取得 */
    checkcode[0] = NUL;
    if ( response[0] ) {
        char    *p = strstr( response, "name=\"checkcode\"" );
        char    *q;

        if ( p ) {
            p += 16;
            q = strstr( p, "value=\"" );
            if ( q ) {
                p = q + 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( checkcode, p, q - p );
                    checkcode[q - p] = NUL;
                }
            }
        }
    }
    ret = -1;

    /* 投稿確認 */
    if ( checkcode[0] ) {
        Sleep( 2000 );  /* 念のため */
        memset( response, 0x00, sz );
        strcpy( url, "http://clrs.jp/add_diary.php?mode=addexec" );
        setTargetURL( url );
        sprintf( request,
                 "magicword=%s&"
                 "checkcode=%s&"
                 "subject=%s&"
                 "body=%s&"
                 "upload_img=&"
                 "img_url1=&"
                 "img_url1_width=0&"
                 "img_url2=&"
                 "img_url2_width=0&"
                 "Submit=%s",
                 "入口", checkcode, title, body, "作　成" );
        sprintf( dummy,
                 "%sReferer: %s\r\n", cookie,
                 "http://clrs.jp/add_diary.php?mode=addconfirm" );

     // ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
     //                            "application/x-www-form-urlencoded",
     //                            request, response, dummy,
     //                            NULL, NULL );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, dummy );
        if ( response[0] )
            ret = 1;
    }

    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}


char    *
editForColors( char *text )
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

    /* この関数の処理内容                */
    /*   (1) <br /> を改行に置換する     */
    /*   (2) <p>, <cite>, <a> を取り除く */
    /*   (3) <blockquote> を取り除く     */

    while ( *p ) {
        if ( !strncmp( p, "<br />", 6 ) ) {
            /* (1) <br /> を [:br:] に置換する */
            const char  *pp = "\r\n";

            p += 6;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "<p>", 3 ) ) {
            /* (2a1) <p> を取り除く */
            p += 3;
        }
        else if ( !strncmp( p, "</p>", 4 ) ) {
            /* (2a2) </p> を取り除く */
            const char  *pp = "\r\n";

            p += 4;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "<cite>", 6 ) ) {
            /* (2b1) <cite> を取り除く */
            const char  *pp = "『";

            p += 6;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "</cite>", 7 ) ) {
            /* (2b2) </cite> を取り除く */
            const char  *pp = "』";

            p += 7;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "<a ", 3 ) ) {
            /* (2c1) <a> を取り除く */
            p += 3;
            while ( *p && (*p != '>') )
                p++;
            if ( *p == '>' )
                p++;
        }
        else if ( !strncmp( p, "</a>", 4 ) ) {
            /* (2c2) </a> を取り除く */
            p += 4;
        }
        else if ( !strncmp( p, "<blockquote>", 12 ) ) {
            /* (3a) <blockquote> を取り除く */
            const char  *pp = ">>\r\n";

            p += 12;
            while ( *pp )
                *q++ = *pp++;
        }
        else if ( !strncmp( p, "</blockquote>", 13 ) ) {
            /* (3b) </blockquote> を取り除く */
            const char  *pp = "\r\n<<\r\n";

            p += 13;
            while ( *pp )
                *q++ = *pp++;
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
postArticleOnColors( const char *username,  /* ユーザ名(メールアドレス) */
                     const char *password,  /* パスワード               */
                     char *title,           /* 投稿記事題名 */
                     char *body )           /* 投稿記事本文 */
{
    int     ret     = 0;
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( title[0] && (strlen(title) > 40) ) {
            /* COLORS では、記事のタイトルは 40 バイト以内 */
            /*     (40バイトより長いと投稿に失敗する)      */
            strcpy( title, sjis2utf( "今日の日記" ) );
        }
        if ( loginColors( username, password, cookie ) ) {
            char    *t;

            /* COLORSでは使えないタグを別の表現に置換 */
            t = editForColors( body );
            strcpy( body, t );

            ret = postColors( username, password, cookie,
                              title, body );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login に失敗しました。\n" );
        else
            MessageBox( NULL, "login に失敗しました。    ",
                        "COLORS", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
