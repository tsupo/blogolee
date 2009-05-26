/*
 *  postArticle.h
 *      �L���� blog �ɓ��e����v���O����
 *      (�u�����������v�̃\�[�X cocousagi.h �𗬗p�A����)
 *
 *      written by H.Tsujimura      2 Jul 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * History:
 * $Log: /comm/blogolee/postArticle.h $
 * 
 * 2     09/05/27 1:47 tsupo
 * 1.22��
 * 
 * 21    09/05/26 21:52 Tsujimura543
 * tumblr �ւ̓��e�ɑΉ�
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 20    09/03/24 20:02 Tsujimura543
 * �E�F�u���u���O�� XML-RPC API �o�R�ł͂Ȃ����̏��X���폜
 * 
 * 19    09/03/20 22:48 Tsujimura543
 * �͂Ăȃ_�C�A���[(�� Atom API �ł̓��e)�ɑΉ�����
 * 
 * 18    09/03/16 20:49 Tsujimura543
 * �E�F�u���u���O�� XMLRPC API �Ή���ƊJ�n
 * 
 * 17    08/09/10 23:01 Tsujimura543
 * loginExciteBlog(), postExciteBlog(), getCategoryListExciteBlog(),
 * getBlogIDsExciteBlog(), getCategoryIDwithName()
 * �� xmlRPC.dll ����ڊ�
 * 
 * 16    08/09/10 21:41 Tsujimura543
 * loginEchoo(), postEchoo(), getCategoryListEchoo(),
 * getBlogIDsEchoo() �� xmlRPC.dll ����ڊ�
 * 
 * 15    08/09/10 18:01 Tsujimura543
 * loginRakuten(), postRakuten(), getCategoryListRakuten(),
 * getBlogIDsRakuten(), getCategoryIDbyName(), getCategoryIDs()
 * �� xmlRPC.dll ����ڊ�
 * 
 * 14    08/09/09 23:56 Tsujimura543
 * loginWebry(), postWebry(), getCategoryListWebry(), getBlogIDsWebry()
 * �� xmlRPC.dll ����ڊ�
 * 
 * 13    08/09/09 22:49 Tsujimura543
 * loginMixi() �� postMixi() �� xmlRPC.dll ����ڊ�
 * 
 * 12    08/09/09 22:19 Tsujimura543
 * loginFC2NETWORK() �� postFC2NETWORK() �� xmlRPC.dll ����ڊ�
 * 
 * 11    08/09/09 21:42 Tsujimura543
 * loginKinugasa() �� postKinugasa() �� xmlRPC.dll ����ڊ�
 * 
 * 10    08/09/09 19:58 Tsujimura543
 * loginColors() �� postColors() �� xmlRPC.dll ����ڊ�
 * 
 * 9     07/11/30 2:01 Tsujimura543
 * Jugem�A���v���O!�A�h���R���u���O�A���܂ɂĂ������L�����̐�p������p�~
 * 
 * 8     07/10/29 20:34 Tsujimura543
 * (1) XML-RPC API �o�R�ł� ���v���O! �ւ̃A�N�Z�X�ɑΉ�
 * (2) XML-RPC API �o�R�ł̃h���R���u���O�̃J�e�S���ꗗ�擾�A�J�e�S���ݒ�
 *     �ɑΉ�
 * 
 * 7     07/03/13 21:16 Tsujimura543
 * �u�������߁v���i�̌f�ڌ�����ς��邱�Ƃ��ł���悤�ɂ���
 * (+ �f�t�H���g�̌f�ڌ�����10������4���ɕύX)
 * 
 * 6     07/03/12 15:23 Tsujimura543
 * BLOGKIND�񋓑̂���l sweetBox ���폜
 * 
 * 5     07/03/03 1:08 Tsujimura543
 * postArticleOnXMLRPC() �� postArticleOnAtomAPI() �̃v���g�^�C�v�錾��
 * �w�b�_�t�@�C���Ɏ����Ă���
 * 
 * 4     07/03/03 1:07 Tsujimura543
 * ��������A�t�B�b�N�X
 *
 * 3     07/03/03 0:44 Tsujimura543
 * ���e����(�N���������b)�̎w��@�\�͂�������p�~����
 * [���e�����͏�Ɍ��ݎ����ƂȂ�]
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * �t�B�b�N�X
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 * 
 * ------------------------------------------------------------------------
 * �ȉ��́Acocousagi.h �̕ύX����
 * ------------------------------------------------------------------------
 * 7     07/02/24 2:05 Tsujimura543
 * JUGEM �� �h���R���u���O �� XML-RPC API �o�R�ł̓��e�ɑΉ�
 * 
 * 6     07/01/23 15:45 Tsujimura543
 * �y�V�u���O�ɃJ�e�S���w�肵�ē��e�ł���悤�ɂ���
 * 
 * 5     06/10/13 17:21 Tsujimura543
 * �R�����g���C��
 * 
 * 4     06/10/13 17:20 Tsujimura543
 * �E�F�u���u���O�ɓ��e����ꍇ�A�u�����������v�N�����̃p�����[�^�Ńe���v
 * ���[�gID���w�肵�Ă̓��e���ł���悤�ɂ���
 * 
 * 3     06/10/02 20:06 Tsujimura543
 * ���̑��A���ʒ�`�� cocousagi.h �֏W��
 * 
 * 2     06/10/02 20:01 Tsujimura543
 * COUSAGI_INFO �̒�`�� cocousagi.h �ֈړ�
 * 
 * 1     06/10/02 20:00 Tsujimura543
 * �\���̂̐錾�A�v���g�^�C�v�錾�Ȃǂ� cocousagi.c ���番�����A
 * cocousagi.h ���쐬
 */

#ifndef __POST_ARTICLE_H__
#define __POST_ARTICLE_H__

#define YES     TRUE
#define NO      FALSE

/*
 *  blog���
 */
#define BLOGKIND_NEWPOSTONLY    0xFE    /* metaWeblog.newPost �̂݃T�|�[�g */
                                        /* ���Ă��� blog                   */
#define BLOGKIND_NOSUPPORT      0xFF    /* ���T�|�[�g blog                 */

typedef enum blogKind {
    unset        = -1,                      // ���ݒ�
    typepad      = BLOGKIND_TYPEPAD,        // Typepad, Typepad France,
                                            //   TypePad Germany
    typepadJapan = BLOGKIND_TYPEPADJAPAN,   // Typepad Japan
    cocolog      = BLOGKIND_COCOLOG,        // �R�R���O
    cocologFree  = BLOGKIND_COCOLOGFREE,    // �R�R���O�t���[
    blogzine     = BLOGKIND_BLOGZINE,       // �u���O�l
    newsHandler  = BLOGKIND_NEWSHANDLER,    // News-Handler
    seesaa       = BLOGKIND_SEESAABLOG,     // Seesaa BLOG
    netLaputa    = BLOGKIND_NETLAPUTA,      // NetLaputa
    blogG        = BLOGKIND_269G,           // 269g
    livedoor     = BLOGKIND_LIVEDOOR,       // livedoor Blog
    lovelog      = BLOGKIND_LOVELOG,        // LOVELOG
    sonet        = BLOGKIND_SONET,          // So-net blog
    blogger      = BLOGKIND_BLOGGER,        // Blogger
    vox          = BLOGKIND_VOX,            // Vox
    hatena       = BLOGKIND_HATENADIARY,    // �͂Ăȃ_�C�A���[
    msnSpaces    = BLOGKIND_MSNSPACES,      // Windows Live Spaces (MSN Spaces)
    movableType  = BLOGKIND_MOVABLETYPE,    // Movable Type �܂��� BOXERBLOG
    bloggerAPI   = BLOGKIND_BLOGGERAPI,     // blogger API �T�|�[�g blog
    metaWeblog   = BLOGKIND_METAWEBLOG,     // metaWeblog API �T�|�[�g blog
    mtAPI        = BLOGKIND_MTAPI,          // MovableType API
                                            //   (+ �g�� metaWeblog API)
                                            //   �T�|�[�g blog
    atomAPI      = BLOGKIND_ATOMAPI,        // Atom API �T�|�[�g blog
    newPostOnly  = BLOGKIND_NEWPOSTONLY,    // metaWeblog.newPost �̂݃T�|�[�g
                                            //   ���Ă��� blog
    jugemX       = BLOGKIND_JUGEM_X,        // JUGEM (XML-RPC API)
    exciteBlog   = BLOGKIND_EXCITEBLOG,     // excite�u���O
    yaplogX      = BLOGKIND_YAPLOG_X,       // ���v���O! (XML-RPC API)
    drecomX      = BLOGKIND_DRECOMBLOG_X,   // �h���R���u���O (XML-RPC API)
    webryX       = BLOGKIND_WEBRY_X,        // �E�F�u���u���O (XML-RPC API)
    mixi         = BLOGKIND_MIXI,           // mixi�����L
    ameblo       = BLOGKIND_AMEBLO,         // �A���[�o�u���O
    kinugasa     = BLOGKIND_KINUGASA,       // �L�k�K�T�����L
    echoo        = BLOGKIND_ECHOO,          // �G�R���O (Echoo!�����L)
    fc2network   = BLOGKIND_FC2NETWORK,     // FC2NETWORK�����L
    fc2blog      = BLOGKIND_FC2BLOG,        // FC2BLOG
    rakuten      = BLOGKIND_RAKUTEN,        // �y�V�u���O (�y�V�L��)
    gooBlog      = BLOGKIND_GOOBLOG,        // goo Blog
    colors       = BLOGKIND_COLORS,         // COLORS���_�C�A���[
    openPne      = BLOGKIND_OPENPNE,        // OpenPNE
    tumblr       = BLOGKIND_TUMBLR,         // tumblr
    unsupported  = BLOGKIND_NOSUPPORT       // ���T�|�[�g blog
}   BLOGKIND;


void
rebuildOnLivedoor(
        const char *username,
        const char *password,
        const char *blogID
    );

int
postArticleOnXMLRPC( const char *blogID,        /* ���e�� blog ID     */
                     BLOGKIND   blogType,       /* blog ���          */
                     const char *title,         /* ���e�L���薼       */
                     const char *body,          /* ���e�L���{��       */
                     const char *extended,      /* ���e�L���ǋL       */
                     const char *description,   /* ���e�L���T�v       */
                     const char *keyword,       /* ���e�L���L�[���[�h */
                     const char *catName );     /* ���e�ΏۃJ�e�S���� */

int
postArticleOnAtomAPI(
        const char *blogID,       /* ���e�� blog ID     */
        BLOGKIND   blogType,      /* blog ���          */
        const char *title,        /* ���e�L���薼       */
        const char *body,         /* ���e�L���{��       */
        const char *description,  /* ���e�L���T�v       */
        const char *catName       /* ���e�ΏۃJ�e�S���� */
     //,char       *endpointURL   /* �G���h�|�C���gURL  */
    );

int
postArticleOnExcite( const char *userName,      /* ���[�U��     */
                     const char *password,      /* �p�X���[�h   */
                     char       *title,         /* ���e�L���薼 */
                     char       *body,          /* ���e�L���{�� */
                     char       *extended,      /* ���e�L���ǋL */
                     const char *categoryName );/* �J�e�S����   */

int
postArticleOnMixi( const char *username,    /* mixi ID (���[���A�h���X) */
                   const char *password,    /* �p�X���[�h               */
                   char       *title,       /* ���e�L���薼             */
                   char       *body );      /* ���e�L���{��             */

int
postArticleOnKinugasa(
        const char *username,   /* �L�k�K�T ID(���[���A�h���X) */
        const char *password,   /* �p�X���[�h                  */
        char       *title,      /* ���e�L���薼                */
        char       *body );     /* ���e�L���{��                */

int
postArticleOnFC2NETWORK( const char *username,  /* ���[���A�h���X */
                         const char *password,  /* �p�X���[�h     */
                         char       *title,     /* ���e�L���薼   */
                         char       *body );    /* ���e�L���{��   */

int
postArticleOnEchoo( const char *userName,       /* ���[�U��     */
                    const char *password,       /* �p�X���[�h   */
                    char       *title,          /* ���e�L���薼 */
                    char       *body,           /* ���e�L���{�� */
                    const char *categoryName ); /* �J�e�S����   */

int
postArticleOnRakuten( const char *userName,       /* ���[�U��     */
                      const char *password,       /* �p�X���[�h   */
                      char       *title,          /* ���e�L���薼 */
                      char       *body,           /* ���e�L���{�� */
                      const char *categoryName ); /* �J�e�S����   */

int
postArticleOnColors(
        const char *username,           /* ���[�U��(���[���A�h���X) */
        const char *password,           /* �p�X���[�h               */
        char       *title,              /* ���e�L���薼             */
        char       *body );             /* ���e�L���{��             */

int
postArticleOnOpenPNE(
        const char *username,           /* ���[�U��(���[���A�h���X) */
        const char *password,           /* �p�X���[�h               */
        char       *title,              /* ���e�L���薼             */
        char       *body );             /* ���e�L���{��             */

int
postArticleOnSimanity(
        const char *username,           /* ���[�U��(���[���A�h���X) */
        const char *password,           /* �p�X���[�h               */
        char       *title,              /* ���e�L���薼             */
        char       *body );             /* ���e�L���{��             */

int
postArticleOnTumblr(
        const char *username,           /* ���[�U��(���[���A�h���X) */
        const char *password,           /* �p�X���[�h               */
        const char *group,              /* ���e���tumblelog        */
        char       *title,              /* ���e�L���薼             */
        char       *body );             /* ���e�L���{��             */

char    *
editForMixi( char *text );

char    *
editForColors( char *text );


char    *
getCategoryIDbyName(
        char       *catID,          /* (O) �J�e�S��ID (������)      */
        const char *categoryName,   /* (I) �J�e�S����               */
        const char *htmlSrcCode,    /* (I) �Ǘ����html�\�[�X�R�[�h */
        const char *beginSelect,    /* (I) <select>                 */
        const char *endSelect,      /* (I) </select>                */
        const char *beginOption,    /* (I) <option>                 */
        const char *endOption,      /* (I) </option>                */
        int        charSet          /* (I) �����R�[�h               */
    );

int
getCategoryIDwithName(
        int        *categoryID,     /* (I/O) �J�e�S��ID             */
        char       *categoryName,   /* (O)   �J�e�S����             */
        const char *htmlSrcCode,    /* (I) �Ǘ����html�\�[�X�R�[�h */
        int        minimumID,       /* (I) �J�e�S��ID�ŏ��l         */
        const char *beginSelect,    /* (I) <select>                 */
        const char *endSelect,      /* (I) </select>                */
        const char *beginOption,    /* (I) <option>                 */
        const char *endOption,      /* (I) </option>                */
        int        charSet          /* (I) �����R�[�h               */
    );

int
getCategoryIDs(
        long         *numOfCategories,  /* (I) �擾����J�e�S���̐�     */
                                        /* (O) �擾�����J�e�S���̐�     */
        CATLISTINF_t categories,        /* (O) �擾�����J�e�S�����     */
        const char   *htmlSrcCode,      /* (I) �Ǘ����html�\�[�X�R�[�h */
        const char   *beginSelect,      /* (I) <select>                 */
        const char   *endSelect,        /* (I) </select>                */
        const char   *beginOption,      /* (I) <option>                 */
        const char   *endOption,        /* (I) </option>                */
        int          charSet            /* (I) �����R�[�h               */
    );

char    *
getCategoryIDstring( 
        char       *catID,          /* (O) �J�e�S��ID (������)      */
        const char *htmlSrcCode,    /* (I) �Ǘ����html�\�[�X�R�[�h */
        const char *beginSelect,    /* (I) <select>                 */
        const char *endSelect,      /* (I) </select>                */
        const char *beginOption,    /* (I) <option>                 */
        const char *endOption,      /* (I) </option>                */
        int        charSet          /* (I) �����R�[�h               */
    );


int
getCategoryListExciteBlog(
    const char   *userName,         // (I) ���[�U��
    const char   *password,         // (I) �p�X���[�h
    long         *numOfCategories,  // (I) �擾����J�e�S���̐�
                                    // (O) �擾�����J�e�S���̐�
    CATLISTINF_t categories );      // (O) �擾�����J�e�S�����

int
getBlogIDsExciteBlog(
    const char *userName,       // (I) ���[�U��
    const char *password,       // (I) �p�X���[�h
    int        *numberOfBlogs,  // (I) �擾���� blog ���̐�
                                // (O) �擾���� blog ���̐�
    BLOGINF    *blogInfo );     // (O) �擾���� blog ���

int
getCategoryListEchoo(
    const char   *userName,         // (I) ���[�U��
    const char   *password,         // (I) �p�X���[�h
    long         *numOfCategories,  // (I) �擾����J�e�S���̐�
                                    // (O) �擾�����J�e�S���̐�
    CATLISTINF_t categories );      // (O) �擾�����J�e�S�����

int
getBlogIDsEchoo(
    const char *userName,       // (I) ���[�U��
    const char *password,       // (I) �p�X���[�h
    int        *numberOfBlogs,  // (I) �擾���� blog ���̐�
                                // (O) �擾���� blog ���̐�
    BLOGINF    *blogInfo );     // (O) �擾���� blog ���

int
getCategoryListRakuten(
    const char   *userName,         // (I) ���[�U��
    const char   *password,         // (I) �p�X���[�h
    long         *numOfCategories,  // (I) �擾����J�e�S���̐�
                                    // (O) �擾�����J�e�S���̐�
    CATLISTINF_t categories );      // (O) �擾�����J�e�S�����

int
getBlogIDsRakuten(
    const char *userName,       // (I) ���[�U��
    const char *password,       // (I) �p�X���[�h
    int        *numberOfBlogs,  // (I) �擾���� blog ���̐�
                                // (O) �擾���� blog ���̐�
    BLOGINF    *blogInfo );     // (O) �擾���� blog ���

int
getBlogIDsTumblr(
    const char *userName,       // (I) ���[�U��(���[���A�h���X)
    const char *password,       // (I) �p�X���[�h
    int        *numberOfBlogs,  // (I) �擾���� blog ���̐�
                                // (O) �擾���� blog ���̐�
    BLOGINF    *blogInfo );     // (O) �擾���� blog ���

/*
 *  blog ���
 */
typedef struct blog_info    {
    char        *blogToolName;  // blog�c�[����
    char        *blogTypeName;  // blogType �ɑΉ����镶����
    BLOGINFOTBL blogInfoTbl;    // blog���e�[�u��
}   BLOG_INFO;


/*
 *  ���e���̊e��p�����[�^
 */
typedef struct postArticleInfo  {
    char      blogUserName[MAX_USERIDLEN + 1];     /* blog login ��         */
    char      blogPassword[MAX_PASSWDLEN + 1];     /* blog �p�X���[�h       */
    char      blogID[MAX_BLOGIDLENGTH + 1];        /* blogID                */
    char      blogURL[MAX_URLLENGTH + 1];          /* blog URL              */
    BLOGKIND  blogType;                            /* blog���              */
    char      endpointURL[MAX_URLLENGTH + 1];      /* �G���h�|�C���gURL     */
    int       charSet;                             /* �����R�[�h���        */
    int       useHatenaLink;                  /* �L�[���[�h�����N���݂̗v�� */
    int       useProxy;                       /* proxy�o�R�ŒʐM���邩�ۂ�  */
    int       useSimilarity;                        /* �������߂��g�����ۂ� */
    char      amazonAssociateID[MAX_NAMELEN + 1];   /* Amazon�A�\�V�G�C�gID */
    char      rakutenAffiliateID[MAX_KEYLENGTH + 1];/* �y�V�A�t�B���G�C�gID */
    int       numOfRecomended;                      /* �������ߌf�ڌ���     */
    char      categoryName[MAX_CATIDLENGTH + 1];    /* ���e�Ώۂ̃J�e�S���� */
    char      templateID[MAX_CATIDLENGTH + 1];      /* �e���v���[�gID       */
}   POST_INFO;

typedef struct articleInfo {
    char      *title;       // �L���薼
    char      *body;        // �L���{��
    char      *summary;     // �L���T�v   (option)
    char      *extended;    // �ǋL       (option)
    char      *keyword;     // �L�[���[�h (option)
#if 0
    int       yyyy;         // ���e���� (�N)
    int       mm;           // ���e���� (��)
    int       dd;           // ���e���� (��)
    int       HH;           // ���e���� (��)
    int       MM;           // ���e���� (��)
    int       SS;           // ���e���� (�b)
#endif
}   ARTICLE_INFO;


#define EID_LENGTH      32  /* excite ID �ő咷 */


BOOL
postArticle(
        const ARTICLE_INFO *article,
        const POST_INFO    *postInfo
    );

#endif  /* __POST_ARTICLE_H__ */
