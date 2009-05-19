/*
 * ProxyInfoDialog.h  : �u���O�N���C�A���g BloGolEe
 *      proxy���ݒ�_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  9 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/ProxyInfoDialog.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/03/10 5:22 Tsujimura543
 * ���[�U���ƃp�X���[�h�̎w�肪�K�v��proxy�T�[�o�ɂ��b��I�ɑΉ����Ă݂�
 * 
 * 1     07/03/09 19:28 Tsujimura543
 * �V�K�쐬 (����m�F�ς�)
 */

#if !defined(AFX_PROXYINFODIALOG_H__BC9CC1B1_FB91_4C68_BFED_B0DEFFAD68CC__INCLUDED_)
#define AFX_PROXYINFODIALOG_H__BC9CC1B1_FB91_4C68_BFED_B0DEFFAD68CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProxyInfoDialog �_�C�A���O

class CProxyInfoDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CProxyInfoDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CProxyInfoDialog)
	enum { IDD = IDD_DIALOG_PROXY_INFO };
	CString	m_proxyServerName;
	UINT	m_proxyPortNumber;
	CString	m_proxyUserName;
	CString	m_proxyPassword;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CProxyInfoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
    void    switchOK();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CProxyInfoDialog)
	afx_msg void OnUpdateEditProxyPortNumber();
	afx_msg void OnUpdateEditProxyServerName();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUpdateEditProxyUserName();
	afx_msg void OnUpdateEditProxyPassword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PROXYINFODIALOG_H__BC9CC1B1_FB91_4C68_BFED_B0DEFFAD68CC__INCLUDED_)
