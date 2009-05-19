/*
 * EditBlogInfoDlg.h  : �u���O�N���C�A���g BloGolEe
 *      �u���O���ҏW�_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  11 Mar 2005 / 2 Mar 2007
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�����̂܂ܗ��p
 *
 * $Log: /comm/blogolee/EditBlogInfoDlg.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     07/11/30 2:00 Tsujimura543
 * Jugem ������p�����A�ϐ����폜�A�p�~
 * 
 * 3     07/03/12 15:55 Tsujimura543
 * BLOGKIND �֘A�̕\�L�𓝈� (enum blogKind �Ə����Ă���Aint �Ə����Ă���
 * ���Ă���)
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * �t�B�b�N�X
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 */

#if !defined(AFX_EDITBLOGINFODLG_H__01554EFB_4A32_4DC2_82B1_76600E74E837__INCLUDED_)
#define AFX_EDITBLOGINFODLG_H__01554EFB_4A32_4DC2_82B1_76600E74E837__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "blogoleeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CEditBlogInfoDlg �_�C�A���O

class CEditBlogInfoDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CEditBlogInfoDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

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

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CEditBlogInfoDlg)
	enum { IDD = IDD_BLOG_DIALOG };
	CListBox	m_blogList;
	CString	m_blogInfoString;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CEditBlogInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
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
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_EDITBLOGINFODLG_H__01554EFB_4A32_4DC2_82B1_76600E74E837__INCLUDED_)
