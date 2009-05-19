/*
 * BlogoleeMini.h  : �u���O�N���C�A���g BloGolEe
 *      ��2���C���_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  13 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/BlogoleeMini.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 3     09/03/19 20:24 Tsujimura543
 * �E�F�u���u���O�̃e���v���[�g�֘A�������폜
 * 
 * 2     07/11/30 2:51 Tsujimura543
 * �R�����g���C��
 * 
 * 1     07/03/13 23:42 Tsujimura543
 * �V�K�쐬 (�����I�ɑ�2�̃��C���_�C�A���O������Ă݂�)
 */

#if !defined(AFX_BLOGOLEEMINI_H__A0628D4C_F92C_4063_A9E3_79885E5BF9D4__INCLUDED_)
#define AFX_BLOGOLEEMINI_H__A0628D4C_F92C_4063_A9E3_79885E5BF9D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "blogoleeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeMini �_�C�A���O

class CBlogoleeMini : public CDialog
{
// �R���X�g���N�V����
public:
	CBlogoleeMini(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    CBlogoleeDlg    *m_dlg;
    bool            m_keyword;
    bool            m_similarity;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CBlogoleeMini)
	enum { IDD = IDD_BLOGOLEE_MINI_DIALOG };
	CListBox	m_categoryList;
	CString	m_articleTitle;
	CString	m_articleSummary;
	CString	m_articleDescription;
	CString	m_categoryName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CBlogoleeMini)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
    void    switchKeyword( bool value );
    void    switchSimilarity( bool value );
    void    switchPostArticle();
    void    switchCategoryList();
    void    switchBlogInfo();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
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
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_BLOGOLEEMINI_H__A0628D4C_F92C_4063_A9E3_79885E5BF9D4__INCLUDED_)
