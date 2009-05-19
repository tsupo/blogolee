/*
 * blogoleeDlg.h  : �u���O�N���C�A���g BloGolEe
 *      ���C���_�C�A���O �w�b�_�[�t�@�C��
 *          written by H.Tsujimura  15 Oct 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 *      (�u�����������E�B�U�[�h�v�̃\�[�X carotDlg.h �𗬗p�A����)
 *
 * $Log: /comm/blogolee/blogoleeDlg.h $
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 19    09/03/19 20:24 Tsujimura543
 * �E�F�u���u���O�̃e���v���[�g�֘A�������폜
 * 
 * 18    07/11/30 2:00 Tsujimura543
 * Jugem ������p�����A�ϐ����폜�A�p�~
 * 
 * 17    07/03/27 19:16 Tsujimura543
 * proxy�����蓮�Őݒ肷�邽�߂̃{�^����ǉ�
 * 
 * 16    07/03/13 23:45 Tsujimura543
 * CBlogoleeMini�N���X���t�����h�N���X�Ɏw��
 * 
 * 15    07/03/13 21:16 Tsujimura543
 * �u�������߁v���i�̌f�ڌ�����ς��邱�Ƃ��ł���悤�ɂ���
 * (+ �f�t�H���g�̌f�ڌ�����10������4���ɕύX)
 * 
 * 14    07/03/13 19:56 Tsujimura543
 * proxy�ݒ���� BlogoleeApp ���ɕێ�����悤�ɂ���
 * 
 * 13    07/03/12 15:55 Tsujimura543
 * BLOGKIND �֘A�̕\�L�𓝈� (enum blogKind �Ə����Ă���Aint �Ə����Ă���
 * ���Ă���)
 * 
 * 12    07/03/12 15:37 Tsujimura543
 * (1) encodeParameter() �� decodeParameter() �� utility.{h,cpp} �ֈړ�
 * (2) ��L�ɑΉ����� freeParameter() ��ʓr�p��
 * 
 * 11    07/03/08 23:09 Tsujimura543
 * �R�����g���C��
 * 
 * 10    07/03/08 23:08 Tsujimura543
 * (1) �f�[�^�t�@�C�����S���Ȃ���ԂŋN�������Ƃ��̋����������������ɂ�
 *     �ďC��
 * (2) ���[�U�C���^�[�t�F�[�X�������
 * 
 * 9     07/03/07 15:37 Tsujimura543
 * ���t�@�N�^�����O
 * 
 * 8     07/03/07 0:47 Tsujimura543
 * ������̃A�t�B���G�C�g���������{�̈ȊO�́A�قڎ�������
 * 
 * 7     07/03/06 6:06 Tsujimura543
 * makeXsltOfSearchResult() ��ǉ�
 * 
 * 6     07/03/06 4:42 Tsujimura543
 * makeXmlOfSearchResult() ��ǉ�
 * 
 * 5     07/03/06 3:40 Tsujimura543
 * �u�z�b�g�y�b�p�[�v�̃O�����T�[�`�������I�ɓ���
 * 
 * 4     07/03/06 0:09 Tsujimura543
 * ���\�b�h���ύX (OnExecutePostArticle)
 * 
 * 3     07/03/03 1:06 Tsujimura543
 * switchArticleKeyword(), switchArticleExtended(), switchArticleSummary()
 * ��ǉ�
 * 
 * 2     07/03/03 0:44 Tsujimura543
 * ���e����(�N���������b)�̎w��@�\�͂�������p�~����
 * [���e�����͏�Ɍ��ݎ����ƂȂ�]
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 */

#if !defined(AFX_BLOGOLEEDLG_H__4EC01EE8_9A20_479E_8525_1687A83623DC__INCLUDED_)
#define AFX_BLOGOLEEDLG_H__4EC01EE8_9A20_479E_8525_1687A83623DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BLOGOLEE_NUM_OF_BLOG_KINDS      48
#define BLOGOLEE_MAX_BLOG_NAME_LENGTH   MAX_BLOGNAMELENGTH

#define BLOGOLEE_INF_EOF_STRING         "## end of file ##"

/////////////////////////////////////////////////////////////////////////////
// CBlogoleeDlg �_�C�A���O

class CBlogoleeDlg : public CDialog
{
// �\�z
friend class CBlogoleeMini;
public:
    HCURSOR     m_hCursor;
    CFont       m_cFont;

    BLOGKIND    m_blogKind;
    int         m_numOfBlogKinds;

    struct blogKindInfo {
        BLOGKIND    blogKind;
        char        *blogKindString;
        char        *blogKindID;
        char        *endpointURL;
    }       m_blogKindInfo[BLOGOLEE_NUM_OF_BLOG_KINDS];

#define MAX_FOOD_CD_LEN     6
#define MAX_FOOD_NAME_LEN   48
    int     m_numOfFoodCodes;
    struct foodCodeInfo {
        char    foodCD[MAX_FOOD_CD_LEN];
        char    foodName[MAX_FOOD_NAME_LEN];
    }       *m_foodCodeInfo;
    char    m_foodCode[MAX_FOOD_CD_LEN];
    int     m_prefCode;
    int     m_hotelTypeNum;

#define MAX_AREA_CODE_LEN   8
#define MAX_AREA_NAME_LEN   128
    int     m_numOfAreaCodes;
    struct areaCodeInfo {
        char    areaCode[MAX_AREA_CODE_LEN];
        char    areaName[MAX_AREA_NAME_LEN];
    }       *m_areaCodeInfo;
    char    m_areaCode[MAX_AREA_CODE_LEN];

private:
    void    switchKeyword( bool value );
    void    switchSimilarity( bool value );
    void    switchAssociateID( bool value );
    void    switchAffiliateID( bool value );
    void    switchEndpointURL( int blogKindIndex = -1 );
    void    switchBlogID( const char *blogID = NULL );
    void    switchBlogInfo();
    void    switchBrowseBlog();
    void    initBlogKindList();

    void    switchArticleKeyword();
    void    switchArticleExtended();
    void    switchArticleSummary();

    void    switchPostArticle();

    void    loadSetting( FILE *fp );
    void    loadSetting( void );
    void    saveSetting( FILE *fp, bool savedForcely );
    void    saveSetting( bool savedForcely = FALSE );
    bool    checkSetting( const char *filename );

    void    makeHeadOfXslt(
                    FILE       *fp,
                    const char *selector,
                    const char *sourceHref = NULL );
    void    makeTailOfXslt( FILE *fp, bool jalan = false );
    CString makeXmlOfSearchResult( const char *base, const char *response );

    int     getFoodCodeInfo();
    void    makeXsltOfSearchShopResult( const char *base );
    CString makeXmlOfSearchShopResult( const char *response );

    int     getAreaCodeInfo();
    void    changeAreaInfo( int prefCode );

    void    makeXsltOfSearchOnsenResult( const char *base );
    CString makeXmlOfSearchOnsenResult( const char *response );
    void    makeXsltOfSearchHotelResult( const char *base );
    CString makeXmlOfSearchHotelResult( const char *response );

    void    switchJalanLink();
    CString searchJalan();
    void    makeAffiliateLink( const char *filename );

    bool    createBlogList();
    bool    allocateBlogInfo();
    void    createBlogInfo();
    void    loadBlogInfo( FILE *fp = NULL );
    void    saveBlogInfo( FILE *fp = NULL );
    bool    checkBlogInfo( const char *filename );
    void    registerBlogInfoFromFile( FILE *fp );

    bool    getStringValue(
                const char *inputString,
                const char *targetName,
                char       *stringValue );
    bool    getStringValue(
                const char *inputString,
                const char *targetName,
                CString    &param );
    bool    getStringValue(
                const char *inputString,
                const char *paramName,
                CString    &param,
                int        idc,
                int        paramAreaSize = MAX_NAMELEN );
    bool    getStringValue(
                const char      *inputString,
                const char      *targetName,
                int             &blogIndex );

    bool    getParameter( bool savedForcely = FALSE );

    bool    checkEncodedPassword( const char *filename );

    bool    IsInner( int id, WORD wX, WORD wY );

    bool    m_keyword;      // �u�͂Ăȃ_�C�A���[�L�[���[�h�v���g�����ۂ�
    bool    m_similarity;   // �u�������߁v���g�����ۂ�

    char    m_settingDir[MAX_PATH];  // �ݒ�t�@�C���i�[�f�B���N�g��
    char    m_settingFile[MAX_PATH]; // �ݒ�t�@�C����
    char    m_blogInfoFile[MAX_PATH];// ���e�Ώۂ� blog �̈ꗗ
    char    m_editorPath[MAX_PATH];  // �L���ҏW�p�G�f�B�^�̃p�X��
    long    m_currentBlogID;         // �J�����g blog ID (index)

#define DEFAULT_RECOMENDED_ITEMS    4
    int     m_numOfRecomended;

public:
	CBlogoleeDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^
    ~CBlogoleeDlg() {
        if ( m_foodCodeInfo )
            delete [] m_foodCodeInfo;
        if ( m_areaCodeInfo )
            delete [] m_areaCodeInfo;
        m_cFont.DeleteObject();
    }

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CBlogoleeDlg)
	enum { IDD = IDD_BLOGOLEE_DIALOG };
	CComboBox	m_hotelType;
	CComboBox	m_areaList2;
	CComboBox	m_areaList;
	CComboBox	m_foodeCodeList;
	CComboBox	m_blogKindList;
	CListBox	m_categoryList;
	CString	m_blogPassword;
	CString	m_blogUserName;
	CString	m_endpointURL;
	CString	m_blogID;
	CString	m_associateID;
	CString	m_categoryName;
	CString	m_blogName;
	CString	m_blogURL;
	CString	m_rakuten_affiliateID;
	CString	m_article_title;
	CString	m_article_keyword;
	CString	m_article_summary;
	CString	m_article_description;
	CString	m_article_extended;
	CString	m_foodKeyword;
	CString	m_foodName;
	CString	m_sid;
	CString	m_pidForJalan;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CBlogoleeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;
    bool  m_initialized;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CBlogoleeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExecutePostArticle();
	afx_msg void OnRadioKeywordOn();
	afx_msg void OnRadioKeywordOff();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnExit();
	afx_msg void OnRadioSimlarityOn();
	afx_msg void OnRadioSimilarityOff();
	afx_msg void OnKillfocusEditAssociateId();
	afx_msg void OnButtonGetCategories();
	afx_msg void OnSelchangeListCategory();
	afx_msg void OnSelchangeComboBlogKind();
	afx_msg void OnKillfocusEditEndpointURL();
	afx_msg void OnButtonSwitchBlog();
	afx_msg void OnKillfocusEditBlogUsername();
	afx_msg void OnKillfocusEditBlogPassword();
	afx_msg void OnKillfocusEditBlogID();
	afx_msg void OnButtonBrowseBlog();
	afx_msg void OnKillfocusEditRakutenId();
	afx_msg void OnKillfocusEditArticleKeyword();
	afx_msg void OnKillfocusEditArticleSummary();
	afx_msg void OnKillfocusEditArticleExtended();
	afx_msg void OnButtonFoodSearch();
	afx_msg void OnSelchangeComboFoodcd();
	afx_msg void OnKillfocusEditFoodKeyword();
	afx_msg void OnWebHotpepper();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnWebJalan();
	afx_msg void OnSelchangeComboAreaList();
	afx_msg void OnSelchangeComboAreaList2();
	afx_msg void OnSelchangeComboHotelType();
	afx_msg void OnButtonHotelSearch();
	afx_msg void OnButtonJalanLink();
	afx_msg void OnUpdateEditJalanSid();
	afx_msg void OnUpdateEditJalanPid();
	afx_msg void OnUpdateEditArticleTitle();
	afx_msg void OnUpdateEditArticle();
	afx_msg void OnButtonSmall();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnButtonProxy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_BLOGOLEEDLG_H__4EC01EE8_9A20_479E_8525_1687A83623DC__INCLUDED_)
