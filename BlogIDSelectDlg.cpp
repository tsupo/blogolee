/*
 * BlogIDSelectDlg.cpp : �u���O�N���C�A���g BloGolEe
 *      Blog ID �I���_�C�A���O
 *
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�����̂܂ܗ��p
 *
 * $Log: /comm/blogolee/BlogIDSelectDlg.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * �t�B�b�N�X
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 */

#include "blogolee.h"
#include "BlogIDSelectDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/BlogIDSelectDlg.cpp 1     09/05/14 3:47 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg �_�C�A���O


CBlogIDSelectDlg::CBlogIDSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlogIDSelectDlg::IDD, pParent)
{
    m_blogList   = NULL;
    m_numOfBlogs = 0;

	//{{AFX_DATA_INIT(CBlogIDSelectDlg)
	m_blogIDlistIndex = -1;
	//}}AFX_DATA_INIT
}


void CBlogIDSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlogIDSelectDlg)
	DDX_Control(pDX, IDC_LIST_BLOGID, m_blogIDlist);
	DDX_LBIndex(pDX, IDC_LIST_BLOGID, m_blogIDlistIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBlogIDSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CBlogIDSelectDlg)
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(IDC_LIST_BLOGID, OnSelchangeListBlogid)
	ON_LBN_DBLCLK(IDC_LIST_BLOGID, OnDblclkListBlogID)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg �Ǝ��ǉ��R�[�h

void    CBlogIDSelectDlg::initialize( BLOGINF *blogList, int numOfBlogs )
{
    if ( blogList && (numOfBlogs > 0) ) {
        if ( m_blogList )
            delete [] m_blogList;
        m_blogList   = new BLOGINF [numOfBlogs];
        m_numOfBlogs = numOfBlogs;

        for ( int i = 0; i < numOfBlogs; i++ )
            m_blogList[i] = blogList[i];
    }
}

void    CBlogIDSelectDlg::initBlogList()
{
    char    *p;

    for ( int i = 0; i < m_numOfBlogs; i++ ) {
        p = utf2sjis( m_blogList[i].blogName );
        m_blogIDlist.AddString( p ? p : m_blogList[i].blogName );
    }
}


/////////////////////////////////////////////////////////////////////////////
// CBlogIDSelectDlg ���b�Z�[�W �n���h��

void CBlogIDSelectDlg::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
    if ( m_blogIDlistIndex == -1 ) {
        // blog ID ���I���̏ꍇ
        MessageBox( "blog ��I�����Ă�������    ",
                    "blog ���I��", MB_OK|MB_ICONWARNING );
        return;
    }
	
	CDialog::OnOK();
}

void CBlogIDSelectDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
    if ( bShow && m_blogList ) {
        m_blogIDlist.InitStorage( m_numOfBlogs,
                                  BLOGOLEE_MAX_BLOG_NAME_LENGTH );
        initBlogList();
    }	
}

void CBlogIDSelectDlg::OnSelchangeListBlogid() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
    int location = m_blogIDlist.GetCurSel();
    if ( location >= 0 )
        m_blogIDlistIndex = location;
}

void CBlogIDSelectDlg::OnDblclkListBlogID() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
    OnSelchangeListBlogid();
    OnOK();
}
