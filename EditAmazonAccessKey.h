/*
 * EditAmazonAccessKey.h  : ブログクライアント BloGolEe
 *      Amazon Access Key 設定ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  1 Jun 2009
 *
 *      Copyright (c) 2009 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/EditAmazonAccessKey.h $
 * 
 * 1     09/06/02 3:49 tsupo
 * VSSサーバ拠点を変更
 * 
 * 2     09/06/01 21:40 Tsujimura543
 * Amazon Product Advertising API 対応 (動作確認済み)
 * 
 * 1     09/06/01 20:05 Tsujimura543
 * 最初の版
 */

#if !defined(AFX_EDITAMAZONACCESSKEY_H__6B59DCE1_7D9F_47E9_99B8_CD531335EDC0__INCLUDED_)
#define AFX_EDITAMAZONACCESSKEY_H__6B59DCE1_7D9F_47E9_99B8_CD531335EDC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// EditAmazonAccessKey ダイアログ

class EditAmazonAccessKey : public CDialog
{
// コンストラクション
public:
	EditAmazonAccessKey(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(EditAmazonAccessKey)
	enum { IDD = IDD_EDIT_AMAZON_ACCESS_KEY };
	CString	m_accessKeyID;
	CString	m_accessKeySecret;
	//}}AFX_DATA

// オーバーライド
	//{{AFX_VIRTUAL(EditAmazonAccessKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// メッセージ マップ関数
	//{{AFX_MSG(EditAmazonAccessKey)
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_EDITAMAZONACCESSKEY_H__6B59DCE1_7D9F_47E9_99B8_CD531335EDC0__INCLUDED_)
