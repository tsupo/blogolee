/*
 * BlogIDSelectDlg.h  : ブログクライアント BloGolEe
 *      Blog ID 選択ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  「ここうさぎ」で使っているソースコードをそのまま流用
 *
 * $Log: /comm/blogolee/BlogIDSelectDlg.h $
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

#if !defined(AFX_BLOGIDSELECTDLG_H__D8F46A4C_89A9_4DD9_9B52_7A7B750C75B6__INCLUDED_)
#define AFX_BLOGIDSELECTDLG_H__D8F46A4C_89A9_4DD9_9B52_7A7B750C75B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "blogoleeDlg.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "xmlRPC.h"
#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg ダイアログ

class CBlogIDSelectDlg : public CDialog
{
// コンストラクション
private:
    BLOGINF *m_blogList;
    int     m_numOfBlogs;

    void    initBlogList( void );

public:
	CBlogIDSelectDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

    ~CBlogIDSelectDlg() {
        if ( m_blogList )
            delete [] m_blogList;
    }

    void    initialize( BLOGINF *blogList, int numOfBlogs );

// ダイアログ データ
	//{{AFX_DATA(CBlogIDSelectDlg)
	enum { IDD = IDD_BLOGID_DIALOG };
	CListBox	m_blogIDlist;
	int		m_blogIDlistIndex;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CBlogIDSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CBlogIDSelectDlg)
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeListBlogid();
	afx_msg void OnDblclkListBlogID();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BLOGIDSELECTDLG_H__D8F46A4C_89A9_4DD9_9B52_7A7B750C75B6__INCLUDED_)
