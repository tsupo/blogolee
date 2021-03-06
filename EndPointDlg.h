/*
 * EndPointDlg.h : ブログクライアント BloGolEe
 *      エンドポイントURL設定・編集ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードをそのまま流用
 *
 * $Log: /comm/blogolee/EndPointDlg.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * フィックス
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe 暫定版 (動作確認済み)
 */

#if !defined(AFX_ENDPOINTDLG_H__F9B8577B_82FC_4364_A132_CA5444A71003__INCLUDED_)
#define AFX_ENDPOINTDLG_H__F9B8577B_82FC_4364_A132_CA5444A71003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EndPointDlg.h : ヘッダー ファイル
//

#ifdef __cplusplus
extern "C" {
#endif
#include "xmlRPC.h"
#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CEndPointDlg ダイアログ

class CEndPointDlg : public CDialog
{
// コンストラクション
public:
	CEndPointDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CEndPointDlg)
	enum { IDD = IDD_ENDPOINT_DIALOG };
	CString	m_endPointURL;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CEndPointDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CEndPointDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ENDPOINTDLG_H__F9B8577B_82FC_4364_A132_CA5444A71003__INCLUDED_)
