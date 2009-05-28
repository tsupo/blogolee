/*
 * blogolee.cpp : ブログクライアント BloGolEe
 *      CBlogoleeApp 本体
 *
 *          written by H.Tsujimura  2 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/blogolee.cpp $
 * 
 * 2     09/05/29 7:55 tsupo
 * 1.23版
 * 
 * 5     09/05/27 22:19 Tsujimura543
 * Amazon API および 楽天 API 関係をアップデート
 * (Amazon API の認証は未対応 → xmlRPC.dll 側の対応と同時に作業予定)
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     07/03/13 19:56 Tsujimura543
 * proxy設定情報を BlogoleeApp 内に保持するようにした
 * 
 * 3     07/03/09 19:31 Tsujimura543
 * proxy情報の取得、設定タイミングを CBlogoleeDlg ダイアログの
 * OnShowWindow() 実行開始以降に変更
 * 
 * 2     07/03/03 1:07 Tsujimura543
 * いったん、フィックス
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe 暫定版 (動作確認済み)
 */

#include "blogolee.h"
#include "blogoleeDlg.h"
#include "AboutDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/blogolee.cpp 2     09/05/29 7:55 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeApp

BEGIN_MESSAGE_MAP(CBlogoleeApp, CWinApp)
	//{{AFX_MSG_MAP(CBlogoleeApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeApp クラスの構築

CBlogoleeApp::CBlogoleeApp()
{
    m_useProxy  = false;        // ここでは、暫定的に false に設定しておく
    m_proxyType = autoDetect;
    m_proxyServer   = _T("");
    m_proxyPort     = 0;
    m_proxyUsername = _T("");
    m_proxyPassword = _T("");

    m_asID          = _T("");
    m_aaID          = _T("");
    m_rdID          = _T("");
    m_raID          = _T("");
    m_raID2         = _T("");
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CBlogoleeApp オブジェクト

CBlogoleeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeApp クラスの初期化

BOOL CBlogoleeApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合
#endif

    m_numOfBlogs = 0;
    m_blogList   = NULL;

	CBlogoleeDlg dlg;
	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
        ;
	}
	else if (nResponse == IDCANCEL)
	{
        ;
	}

    if ( m_blogList ) {
        for ( int i = 0; i < m_numOfBlogs; i++ ) {
            if ( m_blogList[i].numOfCategories > 0 ) {
                for ( int j = 0; j < m_blogList[i].numOfCategories; j++ )
                    free( m_blogList[i].catagory[j] );
                free( m_blogList[i].catagory );
                m_blogList[i].numOfCategories = 0;
                m_blogList[i].catagory        = NULL;
            }
        }
        delete [] m_blogList;

        base64( NULL, 0 );
        encodeURL( NULL );
        translateURL( NULL );
    }

	return FALSE;
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CBlogoleeApp::WinHelp(DWORD dwData, UINT nCmd) 
{
 // CWinApp::WinHelp(dwData, nCmd);
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

// ダイアログを実行するためのアプリケーション コマンド
void CBlogoleeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
