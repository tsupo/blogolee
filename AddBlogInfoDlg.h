/*
 * AddBlogInfoDlg.h  : ブログクライアント BloGolEe
 *      ブログ情報追加ダイアログ
 *          written by H.Tsujimura  18 Mar 2005 / 2 Mar 2007
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードをそのまま流用
 *
 * $Log: /comm/blogolee/AddBlogInfoDlg.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     07/11/30 2:00 Tsujimura543
 * Jugem 向け専用処理、変数を削除、廃止
 * 
 * 3     07/03/12 15:55 Tsujimura543
 * BLOGKIND 関連の表記を統一 (enum blogKind と書いてたり、int と書いてたり
 * していた)
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * フィックス
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe 暫定版 (動作確認済み)
 */

#if !defined(AFX_ADDBLOGINFODLG_H__AADF46FB_7234_4E4E_960D_D0BE767D9699__INCLUDED_)
#define AFX_ADDBLOGINFODLG_H__AADF46FB_7234_4E4E_960D_D0BE767D9699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "blogoleeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CAddBlogInfoDlg ダイアログ

class CAddBlogInfoDlg : public CDialog
{
// コンストラクション
public:
	CAddBlogInfoDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

    CBlogoleeDlg    *m_blogInfo;
    BLOGKIND        m_blogKind;
    bool            m_useCbox;
    bool            m_mode; /* true: blog 追加 / false: 登録情報編集 */

    void        switchBlogName();
    void        switchBlogID();
    void        switchBlogURL();
    void        switchEndpointURL();
    void        switchMoreInfo();

// ダイアログ データ
	//{{AFX_DATA(CAddBlogInfoDlg)
	enum { IDD = IDD_ADD_BLOGINFO_DIALOG };
	CComboBox	m_blogKindList;
	CString	m_blogID;
	CString	m_blogName;
	CString	m_blogPassword;
	CString	m_blogUserName;
	CString	m_endpointURL;
	CString	m_blogURL;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAddBlogInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAddBlogInfoDlg)
	afx_msg void OnButtonMoreInfo();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeComboBlogList();
	afx_msg void OnUpdateEditBlogUserName();
	afx_msg void OnUpdateEditBlogPassword();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ADDBLOGINFODLG_H__AADF46FB_7234_4E4E_960D_D0BE767D9699__INCLUDED_)
