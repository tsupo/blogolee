/*
 * blogolee.cpp : �u���O�N���C�A���g BloGolEe
 *      CBlogoleeApp �{��
 *
 *          written by H.Tsujimura  2 Mar 2007
 *
 *      Copyright (c) 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * $Log: /comm/blogolee/blogolee.cpp $
 * 
 * 2     09/05/29 7:55 tsupo
 * 1.23��
 * 
 * 5     09/05/27 22:19 Tsujimura543
 * Amazon API ����� �y�V API �֌W���A�b�v�f�[�g
 * (Amazon API �̔F�؂͖��Ή� �� xmlRPC.dll ���̑Ή��Ɠ����ɍ�Ɨ\��)
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     07/03/13 19:56 Tsujimura543
 * proxy�ݒ���� BlogoleeApp ���ɕێ�����悤�ɂ���
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

#include "blogolee.h"
#include "blogoleeDlg.h"
#include "AboutDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/blogolee.cpp 2     09/05/29 7:55 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeApp

BEGIN_MESSAGE_MAP(CBlogoleeApp, CWinApp)
	//{{AFX_MSG_MAP(CBlogoleeApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeApp �N���X�̍\�z

CBlogoleeApp::CBlogoleeApp()
{
    m_useProxy  = false;        // �����ł́A�b��I�� false �ɐݒ肵�Ă���
    m_proxyType = autoDetect;
    m_proxyServer   = _T("");
    m_proxyPort     = 0;
    m_proxyUsername = _T("");
    m_proxyPassword = _T("");

    m_asID          = _T("");
    m_aaID          = _T("");
    m_rdID          = _T("");
    m_raID          = _T("");
    m_raID2         = _T("");
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CBlogoleeApp �I�u�W�F�N�g

CBlogoleeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeApp �N���X�̏�����

BOOL CBlogoleeApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ
#endif

    m_numOfBlogs = 0;
    m_blogList   = NULL;

	CBlogoleeDlg dlg;
	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
        ;
	}
	else if (nResponse == IDCANCEL)
	{
        ;
	}

    if ( m_blogList ) {
        for ( int i = 0; i < m_numOfBlogs; i++ ) {
            if ( m_blogList[i].numOfCategories > 0 ) {
                for ( int j = 0; j < m_blogList[i].numOfCategories; j++ )
                    free( m_blogList[i].catagory[j] );
                free( m_blogList[i].catagory );
                m_blogList[i].numOfCategories = 0;
                m_blogList[i].catagory        = NULL;
            }
        }
        delete [] m_blogList;

        base64( NULL, 0 );
        encodeURL( NULL );
        translateURL( NULL );
    }

	return FALSE;
}

#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
void CBlogoleeApp::WinHelp(DWORD dwData, UINT nCmd) 
{
 // CWinApp::WinHelp(dwData, nCmd);
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CBlogoleeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
