/*
 * AddBlogInfoDlg.h  : �u���O�N���C�A���g BloGolEe
 *      �u���O���ǉ��_�C�A���O
 *          written by H.Tsujimura  18 Mar 2005 / 2 Mar 2007
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�����̂܂ܗ��p
 *
 * $Log: /comm/blogolee/AddBlogInfoDlg.h $
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

#if !defined(AFX_ADDBLOGINFODLG_H__AADF46FB_7234_4E4E_960D_D0BE767D9699__INCLUDED_)
#define AFX_ADDBLOGINFODLG_H__AADF46FB_7234_4E4E_960D_D0BE767D9699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "blogoleeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CAddBlogInfoDlg �_�C�A���O

class CAddBlogInfoDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CAddBlogInfoDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

    CBlogoleeDlg    *m_blogInfo;
    BLOGKIND        m_blogKind;
    bool            m_useCbox;
    bool            m_mode; /* true: blog �ǉ� / false: �o�^���ҏW */

    void        switchBlogName();
    void        switchBlogID();
    void        switchBlogURL();
    void        switchEndpointURL();
    void        switchMoreInfo();

// �_�C�A���O �f�[�^
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


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAddBlogInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
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
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ADDBLOGINFODLG_H__AADF46FB_7234_4E4E_960D_D0BE767D9699__INCLUDED_)
