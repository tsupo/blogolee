/*
 * EditBlogInfoDlg.cpp : �u���O�N���C�A���g BloGolEe
 *      �u���O���ҏW�_�C�A���O
 *
 *          written by H.Tsujimura  11 Mar 2005 / 2 Mar 2007
 *
 *      Copyright (c) 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *  �u�����������v�Ŏg���Ă���\�[�X�R�[�h�����̂܂ܗ��p
 *
 * $Log: /comm/blogolee/EditBlogInfoDlg.cpp $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     07/11/30 3:08 Tsujimura543
 * OnButtonAddBlog(), OnButtonModifyBlog() �ŗ����邱�Ƃ�����s��ɑΏ�
 * 
 * 5     07/11/30 2:03 Tsujimura543
 * (1) Jugem�A���v���O!�A�h���R���u���O�� XML-RPC API �o�R�ł͂Ȃ�����
 *     ���X���폜
 * (2) ���܂ɂĂ������L�֘A�̏��X���폜 (2007�N11��30���ŃT�[�r�X�I��)
 * 
 * 4     07/03/12 15:55 Tsujimura543
 * BLOGKIND �֘A�̕\�L�𓝈� (enum blogKind �Ə����Ă���Aint �Ə����Ă���
 * ���Ă���)
 * 
 * 3     07/03/03 0:05 Tsujimura543
 * �s�v�ɂȂ����R�����g���폜
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * �t�B�b�N�X
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 */

#include "blogolee.h"
#include "EditBlogInfoDlg.h"
#include "AddBlogInfoDlg.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/EditBlogInfoDlg.cpp 1     09/05/14 3:47 tsupo $";
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditBlogInfoDlg �_�C�A���O


CEditBlogInfoDlg::CEditBlogInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditBlogInfoDlg::IDD, pParent)
{
    m_blogInfo      = NULL;
    m_currentBlogID = 0;
    m_blogKind      = unset;
    m_blogName      = "";
    m_blogUsername  = "";
    m_blogPassword  = "";
    m_blogID        = "";
    m_blogURL       = "";
    m_endpointURL   = "";
    m_useCbox       = false;

	//{{AFX_DATA_INIT(CEditBlogInfoDlg)
	m_blogInfoString = _T("");
	//}}AFX_DATA_INIT
}


void CEditBlogInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditBlogInfoDlg)
	DDX_Control(pDX, IDC_LIST_BLOG, m_blogList);
	DDX_LBString(pDX, IDC_LIST_BLOG, m_blogInfoString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditBlogInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CEditBlogInfoDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_BLOG, OnButtonAddBlog)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_BLOG, OnButtonDeleteBlog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_BLOG, OnButtonModifyBlog)
	ON_LBN_SELCHANGE(IDC_LIST_BLOG, OnSelchangeListBlog)
	ON_WM_SHOWWINDOW()
	ON_LBN_DBLCLK(IDC_LIST_BLOG, OnDblclkListBlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditBlogInfoDlg ���b�Z�[�W �n���h��

void CEditBlogInfoDlg::OnButtonAddBlog() 
{
	CAddBlogInfoDlg dlg;

    dlg.m_blogInfo = m_blogInfo;
    dlg.m_mode     = true;
    int res = dlg.DoModal();
    if ( res == IDOK ) {
        CBlogoleeApp   *cp = (CBlogoleeApp *)AfxGetApp();

        cp->m_blogList[cp->m_numOfBlogs].blogKind = dlg.m_blogKind;
        strcpy( cp->m_blogList[cp->m_numOfBlogs].blogName,
                (const char *)(dlg.m_blogName) );
        strcpy( cp->m_blogList[cp->m_numOfBlogs].blogUsername,
                (const char *)(dlg.m_blogUserName) );
        strcpy( cp->m_blogList[cp->m_numOfBlogs].blogPassword,
                (const char *)(dlg.m_blogPassword) );
        strcpy( cp->m_blogList[cp->m_numOfBlogs].blogID,
                (const char *)(dlg.m_blogID) );
        strcpy( cp->m_blogList[cp->m_numOfBlogs].blogURL,
                (const char *)(dlg.m_blogURL) );
        cp->m_blogList[cp->m_numOfBlogs].useCbox = dlg.m_useCbox;

        m_blogKind = dlg.m_blogKind;
        if ( (m_blogKind == movableType) ||
             (m_blogKind == bloggerAPI)  ||
             (m_blogKind == metaWeblog)  ||
             (m_blogKind == mtAPI)       ||
             (m_blogKind == atomAPI)     ||
             (m_blogKind == newPostOnly)    ) {    
            strcpy( cp->m_blogList[cp->m_numOfBlogs].endpointURL,
                    (const char *)(dlg.m_endpointURL) );
            m_endpointURL = dlg.m_endpointURL;
        }

        m_currentBlogID = cp->m_numOfBlogs;
        m_blogName      = dlg.m_blogName;
        m_blogUsername  = dlg.m_blogUserName;
        m_blogPassword  = dlg.m_blogPassword;
        m_blogID        = dlg.m_blogID;
        m_blogURL       = dlg.m_blogURL;
        m_useCbox       = dlg.m_useCbox;

        (cp->m_numOfBlogs)++;

        CString str;
        CString blogKindString = "";
        for ( int j = 0; j < m_blogInfo->m_numOfBlogKinds; j++ ) {
            if ( m_blogKind == m_blogInfo->m_blogKindInfo[j].blogKind ) {
                blogKindString = m_blogInfo->m_blogKindInfo[j].blogKindString;
                break;
            }
        }

        str = m_blogName;
        str += " (";
        str += blogKindString;
        str += ")";
        str += " [";
        if ( m_blogID.GetLength() > 0 )
            str += m_blogID;
        else
            str += "---";
        str += "]";
        m_blogList.AddString( str );
        m_blogList.SetCurSel( m_currentBlogID );

        // �ublog �폜�v�{�^���� enable �ɂ���
        CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_DELETE_BLOG );
        p->EnableWindow( TRUE );

        if ( cp->m_numOfBlogs >= MAX_NUM_OF_BLOGS ) {
            // �ublog �ǉ��v�{�^���� disable �ɂ���
            CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_ADD_BLOG );
            p->EnableWindow( FALSE );
        }

        // �u�o�^���C���v�{�^���� enable �ɂ���
        p = (CButton *)GetDlgItem( IDC_BUTTON_MODIFY_BLOG );
        p->EnableWindow( TRUE );
    }

    OnSelchangeListBlog();  /* {@@} */
}

void CEditBlogInfoDlg::OnButtonDeleteBlog() 
{
    int     location = m_blogList.GetCurSel();

    if ( location == LB_ERR )
        return;

    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
    if ( cp->m_numOfBlogs <= 1 )
        return;

    int res = MessageBox( "�{���ɍ폜���Ă��\���܂���?    ",
                          "�폜�m�F", MB_YESNO|MB_ICONWARNING );
    if ( res != IDYES )
        return;

    // �폜���s
    for ( long i = location; i < cp->m_numOfBlogs - 1; i++ ) {
        strcpy( cp->m_blogList[i].blogID,
                cp->m_blogList[i + 1].blogID );
        strcpy( cp->m_blogList[i].blogName,
                cp->m_blogList[i + 1].blogName );
        strcpy( cp->m_blogList[i].blogUsername,
                cp->m_blogList[i + 1].blogUsername );
        strcpy( cp->m_blogList[i].blogPassword,
                cp->m_blogList[i + 1].blogPassword );
        strcpy( cp->m_blogList[i].endpointURL,
                cp->m_blogList[i + 1].endpointURL );

        cp->m_blogList[i].blogKind = cp->m_blogList[i + 1].blogKind;
        cp->m_blogList[i].useCbox  = cp->m_blogList[i + 1].useCbox;

        // �J�e�S���֘A
        if ( cp->m_blogList[i].numOfCategories ==
                                    cp->m_blogList[i + 1].numOfCategories ) {
            for ( int j = 0; j < cp->m_blogList[i].numOfCategories; j++ )
                strcpy( cp->m_blogList[i].catagory[j],
                        cp->m_blogList[i + 1].catagory[j] );
        }
        else {
            if ( cp->m_blogList[i].numOfCategories > 0 ) {
                int j;
                for ( j = 0; i < cp->m_blogList[i].numOfCategories; j++ )
                    free( cp->m_blogList[i].catagory[j] );
                free( cp->m_blogList[i].catagory );
            }

            if ( cp->m_blogList[i + 1].numOfCategories > 0 ) {
                cp->m_blogList[i].catagory =
                    (char **)malloc( sizeof ( char *) *
                                      cp->m_blogList[i + 1].numOfCategories );
                if ( cp->m_blogList[i].catagory ) {
                    int j;
                    for (j = 0; i < cp->m_blogList[i+1].numOfCategories; j++){
                        cp->m_blogList[i].catagory[j] =
                                (char *)malloc(
                                        sizeof ( char ) * MAX_CATNAMELENGTH );
                        if ( cp->m_blogList[i].catagory[j] )
                            strcpy( cp->m_blogList[i].catagory[j],
                                    cp->m_blogList[i + 1].catagory[j] );
                    }
                }
            }
        }
    }

    (cp->m_numOfBlogs)--;
    cp->m_blogList[cp->m_numOfBlogs].blogID[0]        = NUL;
    cp->m_blogList[cp->m_numOfBlogs].blogName[0]      = NUL;
    cp->m_blogList[cp->m_numOfBlogs].blogUsername[0]  = NUL;
    cp->m_blogList[cp->m_numOfBlogs].blogPassword[0]  = NUL;
    cp->m_blogList[cp->m_numOfBlogs].endpointURL[0]   = NUL;
    cp->m_blogList[cp->m_numOfBlogs].blogURL[0]       = NUL;
    cp->m_blogList[cp->m_numOfBlogs].blogKind         = unset;
    cp->m_blogList[cp->m_numOfBlogs].useCbox          = false;
    if ( cp->m_blogList[cp->m_numOfBlogs].numOfCategories > 0 ) {
        int i;
        for (i = 0; i < cp->m_blogList[cp->m_numOfBlogs].numOfCategories; i++)
            free( cp->m_blogList[cp->m_numOfBlogs].catagory[i] );
        free( cp->m_blogList[cp->m_numOfBlogs].catagory );
    }
    cp->m_blogList[cp->m_numOfBlogs].catagory         = NULL;
    cp->m_blogList[cp->m_numOfBlogs].numOfCategories  = 0;

    m_blogList.DeleteString( location );

    if ( location > 0 )
        location--;
    m_blogList.SetCurSel( location );
    m_currentBlogID = location;

    if ( cp->m_numOfBlogs <= 1 ) {
        // �ublog �폜�v�{�^���� disable �ɂ���
        CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_DELETE_BLOG );
        p->EnableWindow( FALSE );
    }

    OnSelchangeListBlog();  /* {@@} */
}

void CEditBlogInfoDlg::OnButtonModifyBlog() 
{
	CAddBlogInfoDlg dlg;
    int             res;

    OnSelchangeListBlog();

    dlg.m_blogInfo = m_blogInfo;
    dlg.m_mode     = false;

    dlg.m_blogKind      = m_blogKind;
    dlg.m_blogName      = m_blogName;
    dlg.m_blogUserName  = m_blogUsername;
    dlg.m_blogPassword  = m_blogPassword;
    dlg.m_blogID        = m_blogID;
    dlg.m_blogURL       = m_blogURL;
    dlg.m_endpointURL   = m_endpointURL;
    dlg.m_useCbox       = m_useCbox;

    res = dlg.DoModal();
    if ( res == IDOK ) {
        m_blogKind      = dlg.m_blogKind;
        m_blogName      = dlg.m_blogName;
        m_blogUsername  = dlg.m_blogUserName;
        m_blogPassword  = dlg.m_blogPassword;
        m_blogID        = dlg.m_blogID;
        m_blogURL       = dlg.m_blogURL;
        m_useCbox       = dlg.m_useCbox;

        CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();
        cp->m_blogList[m_currentBlogID].blogKind = m_blogKind;
        strcpy( cp->m_blogList[m_currentBlogID].blogName,
                (const char *)m_blogName );
        strcpy( cp->m_blogList[m_currentBlogID].blogUsername,
                (const char *)m_blogUsername );
        strcpy( cp->m_blogList[m_currentBlogID].blogPassword,
                (const char *)m_blogPassword );
        strcpy( cp->m_blogList[m_currentBlogID].blogID,
                (const char *)m_blogID );
        strcpy( cp->m_blogList[m_currentBlogID].blogURL,
                (const char *)m_blogURL );
        cp->m_blogList[m_currentBlogID].useCbox = m_useCbox;

        // �X�V���ꂽ�f�[�^�����Ɂublog �I�����v���ĕ`��
        m_blogList.ResetContent();

        CString str;
        CString blogKindString;
        for ( long i = 0; i < cp->m_numOfBlogs; i++ ) {
            blogKindString = "";
            for ( int j = 0; j < m_blogInfo->m_numOfBlogKinds; j++ ) {
                if ( cp->m_blogList[i].blogKind ==
                                m_blogInfo->m_blogKindInfo[j].blogKind ) {
                    blogKindString = 
                                m_blogInfo->m_blogKindInfo[j].blogKindString;
                    break;
                }
            }

            if ( cp->m_blogList[i].blogName[0] )
                str = cp->m_blogList[i].blogName;
            else
                str = "blog�����ݒ�";
            str += " (";
            str += blogKindString;
            str += ")";
            str += " [";
            if ( cp->m_blogList[i].blogID[0] )
                str += cp->m_blogList[i].blogID;
            else
                str += "---";
            str += "]";

            m_blogList.AddString( str );
        }

        m_blogList.SetCurSel( m_currentBlogID );
    }

    OnSelchangeListBlog();  /* {@@} */
}

void CEditBlogInfoDlg::OnSelchangeListBlog() 
{
    CString         str;
    int             location = m_blogList.GetCurSel();
    CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();

    if ( location == LB_ERR ) {
        OnCancel();
        return;
    }

    m_currentBlogID = location;
    m_blogKind      = cp->m_blogList[m_currentBlogID].blogKind;
    m_blogName      = cp->m_blogList[m_currentBlogID].blogName;
    m_blogUsername  = cp->m_blogList[m_currentBlogID].blogUsername;
    m_blogPassword  = cp->m_blogList[m_currentBlogID].blogPassword;
    m_blogID        = cp->m_blogList[m_currentBlogID].blogID;
    m_blogURL       = cp->m_blogList[m_currentBlogID].blogURL;
    m_endpointURL   = cp->m_blogList[m_currentBlogID].endpointURL;
    m_useCbox       = cp->m_blogList[m_currentBlogID].useCbox;
}

void CEditBlogInfoDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
    if ( bShow ) {
        CBlogoleeApp    *cp = (CBlogoleeApp *)AfxGetApp();

        if ( cp->m_numOfBlogs > 0 ) {
            CString str;
            CString blogKindString;

            for ( long i = 0; i < cp->m_numOfBlogs; i++ ) {
                blogKindString = "";
                for ( int j = 0; j < m_blogInfo->m_numOfBlogKinds; j++ ) {
                    if ( cp->m_blogList[i].blogKind ==
                                m_blogInfo->m_blogKindInfo[j].blogKind ) {
                        blogKindString =
                                m_blogInfo->m_blogKindInfo[j].blogKindString;
                        break;
                    }
                }

                if ( cp->m_blogList[i].blogName[0] )
                    str = cp->m_blogList[i].blogName;
                else
                    str = "blog�����ݒ�";
                str += " (";
                str += blogKindString;
                str += ")";
                str += " [";
                if ( cp->m_blogList[i].blogID[0] )
                    str += cp->m_blogList[i].blogID;
                else
                    str += "---";
                str += "]";
                m_blogList.AddString( str );
            }

            if ( cp->m_numOfBlogs <= 1 ) {
                // �ublog �폜�v�{�^���� disable �ɂ���
                CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_DELETE_BLOG );
                p->EnableWindow( FALSE );
            }

            m_blogList.SetCurSel( m_currentBlogID );

            long    n = m_currentBlogID;
            m_blogKind      = cp->m_blogList[n].blogKind;
            m_blogName      = cp->m_blogList[n].blogName;
            m_blogUsername  = cp->m_blogList[n].blogUsername;
            m_blogPassword  = cp->m_blogList[n].blogPassword;
            m_blogID        = cp->m_blogList[n].blogID;
            m_blogURL       = cp->m_blogList[n].blogURL;
            m_endpointURL   = cp->m_blogList[n].endpointURL;
            m_useCbox       = cp->m_blogList[n].useCbox;
        }
        else {
            SetWindowText( "blog �o�^" );

            // �ublog �폜�v�{�^���� disable �ɂ���
            CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_DELETE_BLOG );
            p->EnableWindow( FALSE );

            // �u�o�^���C���v�{�^���� disable �ɂ���
            p = (CButton *)GetDlgItem( IDC_BUTTON_MODIFY_BLOG );
            p->EnableWindow( FALSE );
        }

        if ( cp->m_numOfBlogs >= MAX_NUM_OF_BLOGS ) {
            // �ublog �ǉ��v�{�^���� disable �ɂ���
            CButton *p = (CButton *)GetDlgItem( IDC_BUTTON_ADD_BLOG );
            p->EnableWindow( FALSE );
        }
    }
}

void CEditBlogInfoDlg::OnDblclkListBlog() 
{
    OnOK();
}
