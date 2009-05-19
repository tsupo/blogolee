/*
 *  livedoor.c
 *      livedoor Blog 再構築処理
 *
 *      written by H.Tsujimura    27 Jan 2006 / 2 Oct 2006
 *
 *      Copyright (c) 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードをそのまま流用
 *
 * History:
 * $Log: /comm/blogolee/blogs/livedoor.c $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
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
 * 3     07/02/14 16:46 Tsujimura543
 * http通信のタイムアウト時間を長めにしてみる
 * 
 * 2     06/10/02 20:08 Tsujimura543
 * cocousagi.h をインクルードするようにする
 * 
 * 1     06/10/02 18:11 Tsujimura543
 * cocousagi.c から livedoor Blog 特有の処理を分離
 */

#include "xmlRPC.h"
#include "../postArticle.h"

/*
 *  livedoor 向け再構築処理
 */
int
loginLivedoor( const char *username,
               const char *password,
               char       *cookie )
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !cookie   ||
         !username || !(*username) ||
         !password || !(*password)    )
         return ( ret );

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
    http_getEx( "http://blog.livedoor.com/",
                response, cookie );

    strcpy( url, "http://member.livedoor.com/login/index" );
    setTargetURL( url );
    sprintf( request,
             ".next=%s&"
             ".sv=blog&"
             "livedoor_id=%s&"
             "password=%s&"
             "auto_login=on\r\n",
             encodeURL("http://cms.blog.livedoor.com/cms/"),
             username, password );
    setUpReceiveBuffer( response, sz );
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );

    if ( *response ) {
        if ( strstr( response,
                     "<input type=\"hidden\" name=\"blog_id\"" ) != NULL )
            ret = 1;    /* ログイン成功 */
        else
            ret = 0;    /* ログイン失敗 */
    }
    else
        ret = 0;        /* ログイン失敗 */

    free( response );
    free( request  );

    return ( ret );
}

void
rebuildOnLivedoor(
        const char *username,
        const char *password,
        const char *blogID
    )
{
    char    *request;
    char    *response;
    char    *cookie;
    char    url[MAX_URLLENGTH * 16];
    int     ret;
    size_t  sz = MAX_CONTENT_SIZE * 32;

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return;
    request = (char *)malloc( MAX_COOKIE_LEN );
    if ( !request ) {
        free( cookie );
        return;
    }
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( cookie );
        return;
    }

    // livedoor Blog に login
    memset( cookie, 0x00, MAX_COOKIE_LEN );
    ret = loginLivedoor( username, password, cookie );
    if ( ret ) {
        // 「全ページ」の再構築を実行
        setTimeoutTime( DEFAULT_HTTP_TIMEOUT * 4 );
        strcpy( url, "http://cms.blog.livedoor.com/cms/rebuild/index" );
        sprintf( request,
                 "blog_id=%s&"
                 "command=css,index,rss,atom,monthly,category,articles:all&"
                 ".popup=0",
                 blogID );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        while ( *response ) {
            char    *p = strstr(response,
                                "<body onLoad=\"JavaScript: location.href='");
            char    *q;

            if ( p ) {
                 p += 41;
                 q = strchr( p, '\'' );
                 if ( q ) {
                    int    len;

                    strcpy(url, "http://cms.blog.livedoor.com/cms/rebuild/");
                    len = strlen( url );
                    strncat( url, p, q - p );
                    url[len + (q - p)] = NUL;

                    setTargetURL( url );
                    if ( isatty( fileno( stderr ) ) )
                        fprintf( stderr, "再構築中 %s ...", url );
                    setUpReceiveBuffer( response, sz );
                    http_getEx( url, response, cookie );
                    if ( isatty( fileno( stderr ) ) )
                        fputs( "\n", stderr );
                 }
            }
            else
                break;
        }
        setTimeoutTime( DEFAULT_HTTP_TIMEOUT );
    }

    free( response );
    free( request );
    free( cookie );
}
