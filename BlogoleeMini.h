/*
 * BlogoleeMini.h  : ブログクライアント BloGolEe
 *      第2メインダイアログ ヘッダーファイル
 *          written by H.Tsujimura  13 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/BlogoleeMini.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 3     09/03/19 20:24 Tsujimura543
 * ウェブリブログのテンプレート関連処理を削除
 * 
 * 2     07/11/30 2:51 Tsujimura543
 * コメントを修正
 * 
 * 1     07/03/13 23:42 Tsujimura543
 * 新規作成 (実験的に第2のメインダイアログを作ってみた)
 */

#if !defined(AFX_BLOGOLEEMINI_H__A0628D4C_F92C_4063_A9E3_79885E5BF9D4__INCLUDED_)
#define AFX_BLOGOLEEMINI_H__A0628D4C_F92C_4063_A9E3_79885E5BF9D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "blogoleeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeMini ダイアログ

class CBlogoleeMini : public CDialog
{
// コンストラクション
public:
	CBlogoleeMini(CWnd* pParent = NULL);   // 標準のコンストラクタ

    CBlogoleeDlg    *m_dlg;
    bool            m_keyword;
    bool            m_similarity;

// ダイアログ データ
	//{{AFX_DATA(CBlogoleeMini)
	enum { IDD = IDD_BLOGOLEE_MINI_DIALOG };
	CListBox	m_categoryList;
	CString	m_articleTitle;
	CString	m_articleSummary;
	CString	m_articleDescription;
	CString	m_categoryName;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CBlogoleeMini)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    void    switchKeyword( bool value );
    void    switchSimilarity( bool value );
    void    switchPostArticle();
    void    switchCategoryList();
    void    switchBlogInfo();

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CBlogoleeMini)
	afx_msg void OnUpdateEditArticleTitle();
	afx_msg void OnUpdateEditArticleSummary();
	afx_msg void OnUpdateEditArticle();
	afx_msg void OnButtonSwitchBlog();
	afx_msg void OnButtonBrowseBlog();
	afx_msg void OnButtonGetCategories();
	afx_msg void OnExit();
	afx_msg void OnPostArticle();
	afx_msg void OnButtonLarge();
	afx_msg void OnRadioKeywordOn();
	afx_msg void OnRadioKeywordOff();
	afx_msg void OnRadioSimilarityOn();
	afx_msg void OnRadioSimilarityOff();
	afx_msg void OnSelchangeListCategory();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BLOGOLEEMINI_H__A0628D4C_F92C_4063_A9E3_79885E5BF9D4__INCLUDED_)
