/*
 * blogolee.h  : ブログクライアント BloGolEe
 *      メインヘッダーファイル
 *          written by H.Tsujimura  2 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/blogolee.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     07/03/27 19:16 Tsujimura543
 * proxy情報を手動で設定するためのボタンを追加
 * 
 * 5     07/03/13 19:56 Tsujimura543
 * proxy設定情報を BlogoleeApp 内に保持するようにした
 * 
 * 4     07/03/12 15:55 Tsujimura543
 * BLOGKIND 関連の表記を統一 (enum blogKind と書いてたり、int と書いてたり
 * していた)
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

#if !defined(AFX_BLOGOLEE_H__7F295C77_CAB1_498D_8193_940C5E0EE066__INCLUDED_)
#define AFX_BLOGOLEE_H__7F295C77_CAB1_498D_8193_940C5E0EE066__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Windows ヘッダーから殆ど使用されないスタッフを除外します。

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifdef __cplusplus
extern "C" {
#endif
#include "xmlRPC.h"
#include "atomAPI.h"
#include "postArticle.h"
#ifdef __cplusplus
}
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeApp:
// このクラスの動作の定義に関しては blogolee.cpp ファイルを参照してください。
//

#define MAX_NUM_OF_BLOGS    48
#define MAX_CATS    32  /* 同一blog内カテゴリ最大数 (暫定値) */
#define MAX_TMPLS   128 /* テンプレート最大数 (暫定値) for ウェブリブログ */

class CBlogoleeApp : public CWinApp
{
public:
	CBlogoleeApp();

    volatile enum proxyType {
        autoDetect,     // proxy 使用状況自動取得 (default)
        manualSetting,  // proxy 使用状況手動設定、設定ファイルから取得
        specialSetting, // proxy 使用状況手動設定(ユーザ自身によって設定済み)
        notUsed         // proxy は使用しない    (ユーザ自身によって設定済み)
    }           m_proxyType;
    bool        m_useProxy;                  /* proxy を使うか否か          */
    CString     m_proxyServer;
    int         m_proxyPort;
    CString     m_proxyUsername;
    CString     m_proxyPassword;

    long        m_numOfBlogs;                /* 投稿対象の Blog の数        */
    struct blogList {                        /* 投稿対象の Blog のリスト    */
        BLOGKIND blogKind;                      /*  blog 種別               */
        char     blogName[MAX_BLOGNAMELENGTH];  /*  blog の名前             */
        char     blogOwnerName[MAX_NAMELEN];    /*  blog のオーナーの名前   */
        char     blogUsername[MAX_NAMELEN];     /*  blog ログインユーザ名   */
        char     blogPassword[MAX_PASSWDLEN + 1];/* blog ログインパスワード */
        char     blogID[MAX_BLOGIDLENGTH + 1];  /*  blog ID                 */
        char     blogURL[MAX_URLLENGTH];        /*  blog トップページ URL   */
        char     endpointURL[MAX_URLLENGTH];    /*  エンドポイントURL       */
        bool     useCbox;                       /*  for “Blog Pet 飼育箱” */
        long     numOfCategories;               /*  カテゴリーの数          */
        char     **catagory;                    /*  カテゴリーのリスト      */
    }   *m_blogList;

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CBlogoleeApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CBlogoleeApp)
	afx_msg void OnAppAbout();
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BLOGOLEE_H__7F295C77_CAB1_498D_8193_940C5E0EE066__INCLUDED_)
