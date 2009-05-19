/*
 * EditBlogInfoDlg.h  : ブログクライアント BloGolEe
 *      ブログ情報編集ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  11 Mar 2005 / 2 Mar 2007
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードをそのまま流用
 *
 * $Log: /comm/blogolee/EditBlogInfoDlg.h $
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

#if !defined(AFX_EDITBLOGINFODLG_H__01554EFB_4A32_4DC2_82B1_76600E74E837__INCLUDED_)
#define AFX_EDITBLOGINFODLG_H__01554EFB_4A32_4DC2_82B1_76600E74E837__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "blogoleeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CEditBlogInfoDlg ダイアログ

class CEditBlogInfoDlg : public CDialog
{
// コンストラクション
public:
	CEditBlogInfoDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

    CBlogoleeDlg    *m_blogInfo;
    long            m_currentBlogID;
    BLOGKIND        m_blogKind;
    bool            m_useCbox;
    CString         m_blogName;
    CString         m_blogUsername;
    CString         m_blogPassword;
    CString         m_blogID;
    CString         m_blogURL;
    CString         m_endpointURL;

// ダイアログ データ
	//{{AFX_DATA(CEditBlogInfoDlg)
	enum { IDD = IDD_BLOG_DIALOG };
	CListBox	m_blogList;
	CString	m_blogInfoString;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CEditBlogInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CEditBlogInfoDlg)
	afx_msg void OnButtonAddBlog();
	afx_msg void OnButtonDeleteBlog();
	afx_msg void OnButtonModifyBlog();
	afx_msg void OnSelchangeListBlog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDblclkListBlog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_EDITBLOGINFODLG_H__01554EFB_4A32_4DC2_82B1_76600E74E837__INCLUDED_)
