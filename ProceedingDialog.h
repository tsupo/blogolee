/*
 * ProceedingDialog.h  : ブログクライアント BloGolEe
 *      進行状況表示ダイアログ ヘッダーファイル
 *          written by H.Tsujimura  10 Nov 2005 / 9 Mar 2007
 *
 *  「ソーシャルブックマーク管理プログラム」で使っているソースコードを
 *  そのまま流用
 *
 * $Log: /comm/blogolee/ProceedingDialog.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 1     07/03/09 20:13 Tsujimura543
 * bookey のソースを流用
 * 
 * ------------------------------------------------------------------------
 * 以下は、bookey/ProceedingDialog.h の変更履歴
 * ------------------------------------------------------------------------
 * 2     06/07/03 23:37 Tsujimura543
 * ProceedingDialog の DestroyWindow() 時に例外が発生することがある件の
 * 暫定対処を実施 (デバッグ版でしか発生しない?)
 * 
 * 1     05/11/10 21:17 Tsujimura543
 * 新規作成
 */

#if !defined(AFX_PROCEEDINGDIALOG_H__3176E431_89B4_48A3_B3B0_030CF818F828__INCLUDED_)
#define AFX_PROCEEDINGDIALOG_H__3176E431_89B4_48A3_B3B0_030CF818F828__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// ProceedingDialog ダイアログ

class ProceedingDialog : public CDialog
{
// コンストラクション
public:
	ProceedingDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ
    void    ChangeDialogText( const char *title, const char *message );
    void    ResetDialogText();

// ダイアログ データ
	//{{AFX_DATA(ProceedingDialog)
	enum { IDD = IDD_PROCEEDING_DIALOG };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(ProceedingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(ProceedingDialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PROCEEDINGDIALOG_H__3176E431_89B4_48A3_B3B0_030CF818F828__INCLUDED_)
