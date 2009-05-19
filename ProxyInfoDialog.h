/*
 * ProxyInfoDialog.h  : ブログクライアント BloGolEe
 *      proxy情報設定ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  9 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/ProxyInfoDialog.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/03/10 5:22 Tsujimura543
 * ユーザ名とパスワードの指定が必要なproxyサーバにも暫定的に対応してみた
 * 
 * 1     07/03/09 19:28 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#if !defined(AFX_PROXYINFODIALOG_H__BC9CC1B1_FB91_4C68_BFED_B0DEFFAD68CC__INCLUDED_)
#define AFX_PROXYINFODIALOG_H__BC9CC1B1_FB91_4C68_BFED_B0DEFFAD68CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProxyInfoDialog ダイアログ

class CProxyInfoDialog : public CDialog
{
// コンストラクション
public:
	CProxyInfoDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CProxyInfoDialog)
	enum { IDD = IDD_DIALOG_PROXY_INFO };
	CString	m_proxyServerName;
	UINT	m_proxyPortNumber;
	CString	m_proxyUserName;
	CString	m_proxyPassword;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CProxyInfoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    void    switchOK();

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CProxyInfoDialog)
	afx_msg void OnUpdateEditProxyPortNumber();
	afx_msg void OnUpdateEditProxyServerName();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUpdateEditProxyUserName();
	afx_msg void OnUpdateEditProxyPassword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PROXYINFODIALOG_H__BC9CC1B1_FB91_4C68_BFED_B0DEFFAD68CC__INCLUDED_)
