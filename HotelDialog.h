/*
 * HotelDialog.h  : ブログクライアント BloGolEe
 *      ホテル情報表示ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  7 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/HotelDialog.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/03/07 22:39 Tsujimura543
 * 新規作成 (動作確認済み)
 */

#if !defined(AFX_HOTELDIALOG_H__FACA5207_C3C8_4885_8BED_AFFC7353DD1D__INCLUDED_)
#define AFX_HOTELDIALOG_H__FACA5207_C3C8_4885_8BED_AFFC7353DD1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "hotelInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CHotelDialog ダイアログ

class CHotelDialog : public CDialog
{
// コンストラクション
public:
	CHotelDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
    ~CHotelDialog() {
        m_cFont.DeleteObject();
    }

    HCURSOR     m_hCursor;
    CFont       m_cFont;

    int         m_numOfHotelInfo;
    int         m_currentHotelInfo;
    HotelInfo   *m_hotelInfo;

// ダイアログ データ
	//{{AFX_DATA(CHotelDialog)
	enum { IDD = IDD_DIALOG_HOTEL_INFO };
	CString	m_hotelInfoString;
	CString	m_hotelName;
	CString	m_hotelURL;
	CString	m_catchCopy;
	CString	m_description;
	CString	m_hotelAddress;
	CString	m_checkIn;
	CString	m_checkOut;
	CString	m_imageURL;
	CString	m_imageDescription;
	CString	m_textLink;
	CString	m_imageLink;
	CString	m_sid;
	CString	m_pid;
	CString	m_affiliateURL;
	//}}AFX_DATA

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CHotelDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
    void    showHotelInfo();
    CString makeAffilateURL( CString trailerURL, CString targetURL );
    CString makeAffilateURLforXHTML( CString affiliateURL );
    CString wordrap( CString url );

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CHotelDialog)
	afx_msg void OnButtonBackward();
	afx_msg void OnButtonForward();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnAffiliateURL();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_HOTELDIALOG_H__FACA5207_C3C8_4885_8BED_AFFC7353DD1D__INCLUDED_)
