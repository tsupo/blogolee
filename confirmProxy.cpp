/*
 * confirmProxy.cpp : ブログクライアント BloGolEe
 *      proxy情報設定確認処理
 *
 *          written by H.Tsujimura  9 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/confirmProxy.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 8     07/03/27 19:16 Tsujimura543
 * proxy情報を手動で設定するためのボタンを追加
 * 
 * 7     07/03/14 20:33 Tsujimura543
 * checkProxyInfo() を改良
 * 
 * 6     07/03/14 20:09 Tsujimura543
 * proxy.txt に書き出すポート番号の値がおかしい不具合を修正
 * 
 * 5     07/03/13 19:56 Tsujimura543
 * proxy設定情報を BlogoleeApp 内に保持するようにした
 * 
 * 4     07/03/10 5:22 Tsujimura543
 * ユーザ名とパスワードの指定が必要なproxyサーバにも暫定的に対応してみた
 * 
 * 3     07/03/09 21:23 Tsujimura543
 * FILE_CONFIG_PROXY を追加
 * 
 * 2     07/03/09 21:21 Tsujimura543
 * checkProxyInfo() を追加
 * 
 * 1     07/03/09 19:28 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#include "blogolee.h"
#include "ProxyInfoDialog.h"
#include "confirmProxy.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/confirmProxy.cpp 1     09/05/14 3:47 tsupo $";
#endif

#define FILE_CONFIG_PROXY   "./proxy.txt"   // proxyサーバ情報設定ファイル

int confirmProxyInfo( int            *useProxy,
                      char           *proxyServer,
                      unsigned short *proxyPort,
                      char           *proxyUserName,
                      char           *proxyPassword )
{
    int             ret = FALSE;
    CBlogoleeApp    *bp = (CBlogoleeApp *)AfxGetApp();

    int r = MessageBox( NULL,
                        "proxyサーバ経由でインターネットを利用していますか?",
                        "インターネット利用形態確認",
                        MB_YESNO|MB_ICONQUESTION );
    if ( r == IDYES ) {
        CProxyInfoDialog    dlg;
        dlg.DoModal();

        *useProxy = TRUE;
        strcpy( proxyServer, dlg.m_proxyServerName );
        *proxyPort = (unsigned short)(dlg.m_proxyPortNumber);

        bp->m_proxyServer = proxyServer;
        bp->m_proxyPort   = *proxyPort;

        if ( dlg.m_proxyUserName.GetLength() > 0 ) {
            bp->m_proxyUsername = dlg.m_proxyUserName;
            if ( dlg.m_proxyPassword.GetLength() > 0 )
                bp->m_proxyPassword = dlg.m_proxyPassword;
        }

        FILE    *fp;
        if ( ( fp = fopen( FILE_CONFIG_PROXY, "w" ) ) != NULL ) {
            fprintf( fp, "%s\n", proxyServer );
            fprintf( fp, "%d\n", *proxyPort );

            if ( dlg.m_proxyUserName.GetLength() > 0 ) {
                if ( proxyUserName )
                    strcpy( proxyUserName, dlg.m_proxyUserName );
                fprintf( fp, "%s\n", (const char *)dlg.m_proxyUserName );

                if ( dlg.m_proxyPassword.GetLength() > 0 ) {
                    if ( proxyPassword )
                        strcpy( proxyPassword, dlg.m_proxyPassword );
                    fprintf( fp, "%s\n", (const char *)dlg.m_proxyPassword );
                }
            }
            fclose( fp );
        }

        ret = TRUE;
    }
    else {
        *useProxy = FALSE;
        ret = TRUE;
    }

    bp->m_proxyType = CBlogoleeApp::manualSetting;
    bp->m_useProxy  = *useProxy == TRUE ? true : false;

    return ( ret );
}

bool
checkProxyInfo()
{
    bool    ret = isNecessaryToCheckProxyInfo() ? true : false;

    if ( ret )
        initProxyInfo();

    return ( ret );
}

void
initProxyInfo()
{
    unlink( FILE_CONFIG_PROXY );
}
