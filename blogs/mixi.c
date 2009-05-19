/*
 *  mixi.c
 *      mixi 内日記投稿処理
 *
 *      written by H.Tsujimura    7 Sep 2004 / 2 Oct 2006
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードを少し改造して流用
 *
 * History:
 * $Log: /comm/blogolee/blogs/mixi.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     09/03/23 16:34 Tsujimura543
 * 現行の仕様に合わせて修正
 * 
 * 5     08/09/09 22:49 Tsujimura543
 * loginMixi() と postMixi() を xmlRPC.dll から移管
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
 * 3     07/01/29 13:38 Tsujimura543
 * title の URLエンコードは、postMixi() 内で実行するのではなく、postMixi()
 * の呼び出し元であらかじめ実行しておく、という仕様に変更
 * 
 * 2     06/10/02 20:08 Tsujimura543
 * cocousagi.h をインクルードするようにする
 * 
 * 1     06/10/02 19:22 Tsujimura543
 * cocousagi.c から mixi 特有の処理を分離
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
 * mixi向け投稿処理
 */

int
loginMixi( const char *username,    // (I) mixi ID (メールアドレス)
           const char *password,    // (I) パスワード
           char       *cookie,      // (O) クッキー
           char       *id        )  // (O) mixi ID (数字)
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE;

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

    strcpy( url, "http://mixi.jp/login.pl" );
    sprintf( request,
             "next_url=%s&"
             "email=%s&"
             "password=%s&"
             "sticky=on",
             "%2Fhome.pl",
             username, password );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        if ( strstr( response, "url=/check.pl" ) != NULL ) {
            strcpy( url, "http://mixi.jp/check.pl?n=%2Fhome.pl" );
            setUpReceiveBuffer( response, sz );
            http_getEx( url, response, cookie );
            if ( *response ) {
                if ( strstr( response, "href=\"show_profile.pl" ) != NULL ) {
                    char    *p = strstr( response,
                                         "http://mixi.jp/add_diary.pl?id=" );
                    if ( p ) {
                        char    *q;

                        p += 31;
                        q = strchr( p, '"' );
                        if ( q ) {
                            strncpy( id, p, q - p );
                            id[q - p] = NUL;
                        }
                    }

                    ret = 1;    /* ログイン成功 */
                }
            }
        }
    }

    free( response );
    free( request  );

    return ( ret );
}


int
postMixi( const char *id,       // (I) mixi ID (数字)
          char       *cookie,   // (I/O) クッキー
          const char *title,    // (I) 記事題名
          const char *body )    // (I) 記事本文
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    char    contentType[128];
    char    post_key[64];
    char    dummy[MAX_COOKIE_LEN + MAX_URLLENGTH];
    char    *separator = getMultiPartID();
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !title    || !(*title)    ||
         !body     || !(*body)     ||
         !cookie   || !(*cookie)      )
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

    /* 投稿ページを取得 */
    strcpy( url, "http://mixi.jp/home.pl" );
    sprintf( dummy, "%sReferer: %s\r\n", cookie, url );
    sprintf( url, "http://mixi.jp/add_diary.pl?id=", id );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );

    /* 投稿 */
    sprintf( contentType, "multipart/form-data; boundary=%s", separator );

    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "news_id", 0, NULL, NULL ) );
    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "campaign_id", 0, NULL, NULL ) );
    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "invite_campaign", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "id", 0, id, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "news_title", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "news_url", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "movie_id", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "movie_title", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "movie_url", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "submit", 0, "main", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "diary_title", 0, title, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "diary_body", 0, body, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "photo1", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "photo2", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "photo3", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "orig_size", 0, "1", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "tag_id", 0, "0", NULL ) );
    sprintf( request + strlen( request ), "--%s--\r\n", separator );

    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL );
    sprintf( dummy, "%sReferer: %s\r\n", cookie, url );

    strcpy( url, "http://mixi.jp/add_diary.pl" );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, contentType, request, response, dummy );

    /* post_key 取得 */
    post_key[0] = NUL;
    if ( *response ) {
        char    *p = strstr( response, "name=post_key value=\"" );

        if ( !p ) {
            p = strstr( response, "name=\"post_key\" value=\"" );
            if ( p )
                p += 2;
        }

        if ( p ) {
            char    *q;

            p += 21;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( post_key, p, q - p );
                post_key[q - p] = NUL;
            }
        }
    }

    /* 投稿確認 */
    if ( post_key[0] ) {
        char    *p = strstr( cookie, "; path=" );
        if ( p )
            strcpy( p, "\r\n" );
        sprintf( request,
                 "submit=confirm&"
                 "packed=&"
                 "post_key=%s&"
                 "news_id=&"
                 "campaign_id=&"
                 "invite_campaign=&"
                 "id=%s&"
                 "diary_title=%s&"
                 "diary_body=%s&"
                 "news_title=&"
                 "news_url=&"
                 "movie_id=&"
                 "movie_title=&"
                 "movie_url=&"
                 "tag_id=0",
                 post_key, id,
                 title, body );
        sprintf( dummy, "%sReferer: %s\r\n", cookie, url );
        strcpy( url, "http://mixi.jp/add_diary.pl" );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, dummy );
        if ( *response )
            ret = 1;
    }

    free( response );
    free( request  );

    return ( ret );
}


char    *
editForMixi( char *text )
{
    char    *p = text;
    char    *tmp, *q;
    int     innerBlockquote = 0;

    if ( !p || !(*p) )
        return ( text );

    tmp = (char *)malloc( strlen( p ) + 1 );
    if ( tmp )
        q = tmp;
    else
        q = p;

    /* この関数の処理内容                                       */
    /*   (1) 改行を取り除く                                     */
    /*   (2) <br /> を改行に置換する                            */
    /*   (3) <p>, <cite>, <a> を取り除く                        */
    /*   (4) <blockquote> を取り除く                            */
    /*   (5) <blockquote> ～ </blockquote> の行頭に :) を入れる */

    while ( *p ) {
        if ( (*p == '\r') || (*p == '\n') ) {
            /* (1) 改行を取り除く */
            p++;
        }
        else if ( !strncmp( p, "<br />", 6 ) ) {
            /* (2) <br /> を改行に置換する */
            p += 6;
            *q++ = '\r';
            *q++ = '\n';
            if ( innerBlockquote ) {
                *q++ = ':';
                *q++ = ')';
                *q++ = ' ';
            }
        }
        else if ( !strncmp( p, "<p>", 3 ) ) {
            /* (3a1) <p> を取り除く */
            p += 3;
            if ( innerBlockquote ) {
                *q++ = ':';
                *q++ = ')';
                *q++ = ' ';
            }
        }
        else if ( !strncmp( p, "</p>", 4 ) ) {
            /* (3a2) </p> を取り除く */
            p += 4;
            *q++ = '\r';
            *q++ = '\n';
            if ( innerBlockquote ) {
                *q++ = ':';
                *q++ = ')';
                *q++ = ' ';
            }
        }
        else if ( !strncmp( p, "<cite>", 6 ) ) {
            /* (3b1) <cite> を取り除く */
            p += 6;
        }
        else if ( !strncmp( p, "</cite>", 7 ) ) {
            /* (3b2) </cite> を取り除く */
            p += 7;
        }
        else if ( !strncmp( p, "<a ", 3 ) ) {
            /* (3c1) <a> を取り除く */
            p += 3;
            while ( *p && (*p != '>') )
                p++;
            if ( *p == '>' )
                p++;
        }
        else if ( !strncmp( p, "</a>", 4 ) ) {
            /* (3c2) </a> を取り除く */
            p += 4;
        }
        else if ( !strncmp( p, "<blockquote>", 12 ) ) {
            /* (4a) <blockquote> を取り除く */
            innerBlockquote = 1;
            p += 12;
        }
        else if ( !strncmp( p, "</blockquote>", 13 ) ) {
            /* (4b) </blockquote> を取り除く */
            innerBlockquote = 0;
            p += 13;
            *q++ = '\r';
            *q++ = '\n';
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
postArticleOnMixi( const char *username,    /* mixi ID (メールアドレス) */
                   const char *password,    /* パスワード               */
                   char       *title,       /* 投稿記事題名             */
                   char       *body )       /* 投稿記事本文             */
{
    int     ret     = 0;
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );
    char    id[16];

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginMixi( username, password, cookie, id ) ) {
            char    *s, *t;

            s = sjis2euc( title );
            strcpy( title, s );
            t = editForMixi( body );/* mixiでは使えないタグを別の表現に置換 */
            strcpy( body, encodeURL( sjis2euc( t ) ) );

            ret = postMixi( id, cookie, encodeURL( title ), body );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login に失敗しました。\n" );
        else
            MessageBox( NULL, "login に失敗しました。    ",
                        "mixi", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
