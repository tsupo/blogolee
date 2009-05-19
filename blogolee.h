/*
 * blogolee.h  : �u���O�N���C�A���g BloGolEe
 *      ���C���w�b�_�[�t�@�C��
 *          written by H.Tsujimura  2 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/blogolee.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     07/03/27 19:16 Tsujimura543
 * proxy�����蓮�Őݒ肷�邽�߂̃{�^����ǉ�
 * 
 * 5     07/03/13 19:56 Tsujimura543
 * proxy�ݒ���� BlogoleeApp ���ɕێ�����悤�ɂ���
 * 
 * 4     07/03/12 15:55 Tsujimura543
 * BLOGKIND �֘A�̕\�L�𓝈� (enum blogKind �Ə����Ă���Aint �Ə����Ă���
 * ���Ă���)
 * 
 * 3     07/03/09 19:31 Tsujimura543
 * proxy���̎擾�A�ݒ�^�C�~���O�� CBlogoleeDlg �_�C�A���O��
 * OnShowWindow() ���s�J�n�ȍ~�ɕύX
 * 
 * 2     07/03/03 1:07 Tsujimura543
 * ��������A�t�B�b�N�X
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 */

#if !defined(AFX_BLOGOLEE_H__7F295C77_CAB1_498D_8193_940C5E0EE066__INCLUDED_)
#define AFX_BLOGOLEE_H__7F295C77_CAB1_498D_8193_940C5E0EE066__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Windows �w�b�_�[����w�ǎg�p����Ȃ��X�^�b�t�����O���܂��B

#include <afxwin.h>         // MFC �̃R�A����ѕW���R���|�[�l���g
#include <afxext.h>         // MFC �̊g������
#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �R���� �R���g���[�� �T�|�[�g
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows �R���� �R���g���[�� �T�|�[�g
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifdef __cplusplus
extern "C" {
#endif
#include "xmlRPC.h"
#include "atomAPI.h"
#include "postArticle.h"
#ifdef __cplusplus
}
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� blogolee.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

#define MAX_NUM_OF_BLOGS    48
#define MAX_CATS    32  /* ����blog���J�e�S���ő吔 (�b��l) */
#define MAX_TMPLS   128 /* �e���v���[�g�ő吔 (�b��l) for �E�F�u���u���O */

class CBlogoleeApp : public CWinApp
{
public:
	CBlogoleeApp();

    volatile enum proxyType {
        autoDetect,     // proxy �g�p�󋵎����擾 (default)
        manualSetting,  // proxy �g�p�󋵎蓮�ݒ�A�ݒ�t�@�C������擾
        specialSetting, // proxy �g�p�󋵎蓮�ݒ�(���[�U���g�ɂ���Đݒ�ς�)
        notUsed         // proxy �͎g�p���Ȃ�    (���[�U���g�ɂ���Đݒ�ς�)
    }           m_proxyType;
    bool        m_useProxy;                  /* proxy ���g�����ۂ�          */
    CString     m_proxyServer;
    int         m_proxyPort;
    CString     m_proxyUsername;
    CString     m_proxyPassword;

    long        m_numOfBlogs;                /* ���e�Ώۂ� Blog �̐�        */
    struct blogList {                        /* ���e�Ώۂ� Blog �̃��X�g    */
        BLOGKIND blogKind;                      /*  blog ���               */
        char     blogName[MAX_BLOGNAMELENGTH];  /*  blog �̖��O             */
        char     blogOwnerName[MAX_NAMELEN];    /*  blog �̃I�[�i�[�̖��O   */
        char     blogUsername[MAX_NAMELEN];     /*  blog ���O�C�����[�U��   */
        char     blogPassword[MAX_PASSWDLEN + 1];/* blog ���O�C���p�X���[�h */
        char     blogID[MAX_BLOGIDLENGTH + 1];  /*  blog ID                 */
        char     blogURL[MAX_URLLENGTH];        /*  blog �g�b�v�y�[�W URL   */
        char     endpointURL[MAX_URLLENGTH];    /*  �G���h�|�C���gURL       */
        bool     useCbox;                       /*  for �gBlog Pet ���甠�h */
        long     numOfCategories;               /*  �J�e�S���[�̐�          */
        char     **catagory;                    /*  �J�e�S���[�̃��X�g      */
    }   *m_blogList;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CBlogoleeApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CBlogoleeApp)
	afx_msg void OnAppAbout();
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_BLOGOLEE_H__7F295C77_CAB1_498D_8193_940C5E0EE066__INCLUDED_)
