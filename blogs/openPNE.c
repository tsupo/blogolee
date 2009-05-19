/*
 *  openPNE.c
 *      OpenPNE 内日記投稿処理
 *
 *      written by H.Tsujimura    15 Sep 2006 / 2 Oct 2006
 *
 *      Copyright (c) 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードを少し改造して流用
 *
 * History:
 * $Log: /comm/blogolee/blogs/openPNE.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     07/12/05 23:34 Tsujimura543
 * makeMultiPartItem() の引数追加に伴う修正を実施
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
 * 1     06/10/02 18:27 Tsujimura543
 * cocousagi.c から OpenPNE 特有の処理を分離
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
 *  OpenPNE 向け投稿処理
 */

BOOL
loginOpenPNE( const char *username, const char *password, char *cookie )
{
    BOOL    ret = FALSE;
    char    request[BUFSIZ];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );
    sprintf( request,
             "m=pc&"
             "a=do_o_login&"
             "username=%s&"
             "password=%s&"
             "is_save=1",
             username, password );
    setUpReceiveBuffer( response, sz );
    http_postEx( "http://openpne.jp/", "application/x-www-form-urlencoded",
                 request, response, cookie );
    if ( *response ) {
        if ( strstr( response, "a=do_inc_page_header_logout" ) )
            ret = TRUE; // ログイン成功
    }
    free( response );

    return ( ret );
}

int
postOpenPNE( const char *title, const char *body, char *cookie )
{
    int     ret = 0;
    char    url[MAX_URLLENGTH];
    char    *request;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;
    char    dummy[4096];
    char    sessid[64];
    char    contentType[128];
    char    *separator = getMultiPartID();

    sessid[0] = NUL;
    request = (char *)malloc( sz );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }

    // http://openpne.jp/?m=pc&a=page_h_diary_add を GET
    Sleep( 1000 );
    strcpy( url, "http://openpne.jp/?m=pc&a=page_h_diary_add" );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );

    // 投稿
    Sleep( 1000 );
    sprintf( contentType, "multipart/form-data; boundary=%s", separator );
    strcpy( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "m", 0, "pc", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "a", 0, "page_h_diary_add_confirm", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "MAX_FILE_SIZE", 0, "307200", NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "subject", 0, title, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "body", 0, body, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "upfile_1", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "upfile_2", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "upfile_3", 0, NULL, NULL ) );
    strcat( request, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "submit", 0, sjis2utf("　確認画面　"), NULL ));
    sprintf( request + strlen( request ), "--%s--\r\n", separator );
    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL ); // 後始末
    sprintf( dummy, "%sReferer: %s\r\n", cookie, url );
    strcpy( url, "http://openpne.jp/" );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, contentType,
                request, response, dummy );
    if ( *response ) {
        //  -- sessid を取得
        char    *p, *q;

        p = strstr( response, "name=\"sessid\" value=\"" );
        if ( p ) {
            p += 21;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( sessid, p, q - p );
                sessid[q - p] = NUL;
            }
        }
    }

    if ( sessid[0] ) {
        // 投稿確認
        Sleep( 1000 );
        sprintf( request,
                 "m=pc&"
                 "a=do_h_diary_add_insert_c_diary&"
                 "sessid=%s&"
                 "subject=%s&"
                 "body=%s&"
                 "tmpfile_1=&"
                 "tmpfile_2=&"
                 "tmpfile_3=&"
                 "submit=%s",
                 sessid, title, body, sjis2utf("　作 　成　") );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                    request, response, cookie );

        if ( *response ) {
            if ( strstr( response, sjis2utf("ここから：日記本文") ) )
                ret = 1; // 投稿成功
        }
    }

    free( response );
    free( request );

    return ( ret );
}

int
postArticleOnOpenPNE( const char *username,     /* ユーザ名(メールアドレス) */
                      const char *password,     /* パスワード               */
                      char *title,              /* 投稿記事題名             */
                      char *body )              /* 投稿記事本文             */
{
    int     ret     = 0;
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginOpenPNE( username, password, cookie ) ) {
            char    *s, *t;

            s = editForColors( body );  /* 暫定的に editForColors() を流用 */
            t = sjis2utf( s );
                /* OpenPNE では使えないタグを別の表現に置換 */
            strcpy( body, t ? t : s );

            ret = postOpenPNE( title, body, cookie );
        }

        free( cookie );
    }
    else {
        if ( isatty( fileno( stderr ) ) )
            fprintf( stderr, "login に失敗しました。\n" );
        else
            MessageBox( NULL, "login に失敗しました。    ",
                        "OpenPNE", MB_OK|MB_ICONWARNING );
    }

    return ( ret );
}
