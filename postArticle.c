/*
 *  postArticle.c
 *      �L���� blog �ɓ��e����v���O����
 *      (�u�����������v�̃\�[�X cocousagi.c �𗬗p�A����)
 *
 *      written by H.Tsujimura      2 Jul 2004 / 2 Mar 2007
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2008 by H.Tsujimura (tsupo@na.rim.or.jp)
 *      All Rights Reserved.
 *
 * History:
 * $Log: /comm/blogolee/postArticle.c $
 * 
 * 3     09/05/29 7:55 tsupo
 * 1.23��
 * 
 * 30    09/05/28 18:41 Tsujimura543
 * (1) �o�O�C�� (Amazon API �֘A�����Ń������j��)
 * (2) �o�b�t�@�I�[�o�[�����΍������
 * 
 * 29    09/05/27 22:19 Tsujimura543
 * Amazon API ����� �y�V API �֌W���A�b�v�f�[�g
 * (Amazon API �̔F�؂͖��Ή� �� xmlRPC.dll ���̑Ή��Ɠ����ɍ�Ɨ\��)
 * 
 * 28    09/05/27 19:42 Tsujimura543
 * getKeyword() ���C��
 * 
 * 2     09/05/27 1:47 tsupo
 * 1.22��
 * 
 * 27    09/05/26 21:52 Tsujimura543
 * tumblr �ւ̓��e�ɑΉ�
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 26    09/03/24 18:58 Tsujimura543
 * Windows Live Spaces �g���� metaWeblog API �̗p�u���O��
 * �u�J�e�S���w��v�t�����e�ɑΉ�
 * 
 * 25    09/03/20 22:48 Tsujimura543
 * �͂Ăȃ_�C�A���[(�� Atom API �ł̓��e)�ɑΉ�����
 * 
 * 24    09/03/16 20:49 Tsujimura543
 * �E�F�u���u���O�� XMLRPC API �Ή���ƊJ�n
 * 
 * 23    08/09/10 23:01 Tsujimura543
 * loginExciteBlog(), postExciteBlog(), getCategoryListExciteBlog(),
 * getBlogIDsExciteBlog(), getCategoryIDwithName()
 * �� xmlRPC.dll ����ڊ�
 * 
 * 22    08/09/10 21:41 Tsujimura543
 * loginEchoo(), postEchoo(), getCategoryListEchoo(),
 * getBlogIDsEchoo() �� xmlRPC.dll ����ڊ�
 * 
 * 21    08/09/10 18:01 Tsujimura543
 * loginRakuten(), postRakuten(), getCategoryListRakuten(),
 * getBlogIDsRakuten(), getCategoryIDbyName(), getCategoryIDs()
 * �� xmlRPC.dll ����ڊ�
 * 
 * 20    08/09/09 23:56 Tsujimura543
 * loginWebry(), postWebry(), getCategoryListWebry(), getBlogIDsWebry()
 * �� xmlRPC.dll ����ڊ�
 * 
 * 19    08/09/09 22:49 Tsujimura543
 * loginMixi() �� postMixi() �� xmlRPC.dll ����ڊ�
 * 
 * 18    08/09/09 22:19 Tsujimura543
 * loginFC2NETWORK() �� postFC2NETWORK() �� xmlRPC.dll ����ڊ�
 * 
 * 17    08/09/09 21:42 Tsujimura543
 * loginKinugasa() �� postKinugasa() �� xmlRPC.dll ����ڊ�
 * 
 * 16    08/09/09 19:58 Tsujimura543
 * loginColors() �� postColors() �� xmlRPC.dll ����ڊ�
 * 
 * 15    08/02/18 23:11 Tsujimura543
 * copyright �\�����A�b�v�f�[�g
 * 
 * 14    08/02/15 22:46 Tsujimura543
 * similaritySearch() �� AWS3.0 �x�[�X�̂��̂��� ECS4.0 �x�[�X�ֈڍs
 * 
 * 13    07/11/30 2:01 Tsujimura543
 * Jugem�A���v���O!�A�h���R���u���O�A���܂ɂĂ������L�����̐�p������p�~
 * 
 * 12    07/10/29 20:34 Tsujimura543
 * (1) XML-RPC API �o�R�ł� ���v���O! �ւ̃A�N�Z�X�ɑΉ�
 * (2) XML-RPC API �o�R�ł̃h���R���u���O�̃J�e�S���ꗗ�擾�A�J�e�S���ݒ�
 *     �ɑΉ�
 * 
 * 11    07/09/04 22:01 Tsujimura543
 * setVerbose() �̑�2�����ǉ��ɔ����ύX
 * 
 * 10    07/03/13 21:16 Tsujimura543
 * �u�������߁v���i�̌f�ڌ�����ς��邱�Ƃ��ł���悤�ɂ���
 * (+ �f�t�H���g�̌f�ڌ�����10������4���ɕύX)
 * 
 * 9     07/03/12 18:36 Tsujimura543
 * utility.h ���C���N���[�h����悤�ɂ���
 * 
 * 8     07/03/12 18:31 Tsujimura543
 * selectBlog() �𓱓����A���t�@�N�^�����O
 * 
 * 7     07/03/12 5:08 Tsujimura543
 * (1) Visual Studio 2005 �ł��r���h�ł���悤�ɃR�[�h���C��
 * (2) �ꕔ�̃_�C�A���O�̕������C��
 * 
 * 6     07/03/10 6:23 Tsujimura543
 * "--- powered by BloGolEe ---" �ɖ��ߍ��ރ����N���ύX
 * 
 * 5     07/03/06 1:38 Tsujimura543
 * �u�y�V�v�̂������ߏ��i�Љ�@�\��ǉ�
 * 
 * 4     07/03/06 0:34 Tsujimura543
 * �u�������߁v�@�\����u�֘A�L����񋓂���v�@�\���폜
 * 
 * 3     07/03/05 22:27 Tsujimura543
 * setKeywordLink() �̈����ǉ��ɔ����C��
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * �t�B�b�N�X
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe �b��� (����m�F�ς�)
 * 
 * ------------------------------------------------------------------------
 * �ȉ��́Acocousagi.c �̕ύX����
 * ------------------------------------------------------------------------
 * 170   07/02/24 2:05 Tsujimura543
 * JUGEM �� �h���R���u���O �� XML-RPC API �o�R�ł̓��e�ɑΉ�
 * 
 * 169   07/02/14 21:45 Tsujimura543
 * ���e���g���C�������C��
 * 
 * 168   07/02/14 16:46 Tsujimura543
 * XML-RPC API ����� Atom API �ł̓��e���̃^�C���A�E�g���Ԃ�
 * ���߂ɂ��Ă݂�
 * 
 * 167   07/01/23 15:33 Tsujimura543
 * (1) �y�V�u���O�̐V�����Ǘ���ʂɑΉ�
 * (2) �y�V�u���O�ɃJ�e�S���w�肵�ē��e�ł���悤�ɂ���
 * 
 * 166   06/10/13 17:21 Tsujimura543
 * �R�����g���C��
 * 
 * 165   06/10/13 17:20 Tsujimura543
 * �E�F�u���u���O�ɓ��e����ꍇ�A�u�����������v�N�����̃p�����[�^�Ńe���v
 * ���[�gID���w�肵�Ă̓��e���ł���悤�ɂ���
 * 
 * 164   06/10/02 20:13 Tsujimura543
 * blog_info_tbl[] �̎��̂� blogInfo.c �֕���
 * 
 * 163   06/10/02 20:01 Tsujimura543
 * COUSAGI_INFO �̒�`�� cocousagi.h �ֈړ�
 * 
 * 162   06/10/02 19:59 Tsujimura543
 * (1) cocousagi.c ���� JUGEM ���L�̏����𕪗����Ajugem.c �ֈڏ�
 * (2) �\���̂̐錾�A�v���g�^�C�v�錾�Ȃǂ� cocousagi.h �֕���
 * 
 * 161   06/10/02 19:50 Tsujimura543
 * cocousagi.c ���� excite�u���O ���L�̏����𕪗����Aexcite.c �ֈڏ�
 * 
 * 160   06/10/02 19:34 Tsujimura543
 * cocousagi.c ���� ���v���O! ���L�̏����𕪗����Ayaplog.c �ֈڏ�
 * 
 * 159   06/10/02 19:30 Tsujimura543
 * cocousagi.c ���� �h���R���u���O ���L�̏����𕪗����Adrecom.c �ֈڏ�
 * 
 * 158   06/10/02 19:22 Tsujimura543
 * cocousagi.c ���� mixi ���L�̏����𕪗����Amixi.c �ֈڏ�
 * 
 * 157   06/10/02 19:18 Tsujimura543
 * cocousagi.c ���� �L�k�K�T ���L�̏����𕪗����Akinugasa.c �ֈڏ�
 * 
 * 156   06/10/02 19:11 Tsujimura543
 * cocousagi.c ���� FC2NETWORK ���L�̏����𕪗����Afc2network.c �ֈڏ�
 * 
 * 155   06/10/02 19:06 Tsujimura543
 * cocousagi.c ���� �G�R���O ���L�̏����𕪗����Aechoo.c �ֈڏ�
 * 
 * 154   06/10/02 19:01 Tsujimura543
 * cocousagi.c ���� �E�F�u���u���O ���L�̏����𕪗����Awebry.c �ֈڏ�
 * 
 * 153   06/10/02 18:54 Tsujimura543
 * cocousagi.c ���� �y�V�u���O ���L�̏����𕪗����Arakuten.c �ֈڏ�
 * 
 * 152   06/10/02 18:39 Tsujimura543
 * cocousagi.c ���� COLORS ���L�̏����𕪗����Acolors.c �ֈڏ�
 * 
 * 151   06/10/02 18:28 Tsujimura543
 * cocousagi.c ���� OpenPNE ���L�̏����𕪗����AopenPNE.c �ֈڏ�
 * 
 * 150   06/10/02 18:20 Tsujimura543
 * cocousagi.c ���� ���܂ɂĂ� ���L�̏����𕪗��Asimanity.c �ֈڏ�
 * 
 * 149   06/10/02 18:12 Tsujimura543
 * cocousagi.c ���� livedoor Blog ���L�̏����𕪗��Alivedoor.c �ֈڏ�
 * 
 * 148   06/10/02 13:43 Tsujimura543
 * livedoor Blog �̍č\�z�������C�� (URL ���z�肵�Ă�����̂�蒷���Ȃ�
 * �ꍇ�����邱�Ƃ������BURL �̊i�[�̈�T�C�Y�𑝂₵��)
 * 
 * 147   06/09/19 11:50 Tsujimura543
 * powered by cocousagi �̃����N��� 3.00 �ł̔z�z�y�[�W�� URL �ɕύX
 * 
 * 146   06/09/15 21:17 Tsujimura543
 * OpenPNE / ���܂ɂĂ� �ւ̓��e���̃^�C�g���̒��������������͂����Ă݂�
 * 
 * 145   06/09/15 20:40 Tsujimura543
 * loginSimanity() �̈��������炵�� (���L�����������Ȃ�K�v�Ȃ�����)
 * 
 * 144   06/09/15 20:34 Tsujimura543
 * ���܂ɂĂ� �ɑΉ����Ă݂�
 * 
 * 143   06/09/15 20:07 Tsujimura543
 * OpenPNE �ɑΉ����Ă݂�
 * 
 * 142   06/09/14 19:49 Tsujimura543
 * Vox �ɑΉ����Ă݂�
 * 
 * 141   06/09/12 12:27 Tsujimura543
 * CP932 �ł͂Ȃ��������������Ă���Ƃ̎w�E(Visual Studio 2005)�Ɋ�Â��A
 * �\�[�X�R�[�h�̐��������{
 * 
 * 140   06/09/11 18:28 Tsujimura543
 * �y�V�L�� �� �y�V�u���O
 * 
 * 139   06/09/08 21:51 Tsujimura543
 * MSN Spaces �� Windows Live Spaces �ւ̖��̕ύX�ɑΉ�
 * 
 * 138   06/09/07 18:58 Tsujimura543
 * So-net blog �̏ꍇ�AAtom API �o�R�ł̃p�X���[�h(�̃G���R�[�h����)��
 * 64�o�C�g���傫���Ȃ邱�Ƃ����邱�Ƃ������B�p�X���[�h�i�[�̈�̃T�C�Y
 * �𑝂₵��
 * 
 * 137   06/09/06 17:06 Tsujimura543
 * �A���[�o�u���O�̋L�����e���A�^�C�g����48������蒷���Ɠ��e�Ɏ��s����
 * ���Ƃ������B48������蒷���ꍇ�́A�Z���^�C�g���ɍ����ւ���悤�ɂ���
 * 
 * 136   06/09/04 14:35 Tsujimura543
 * COLORS �ւ̓��e���A�L���^�C�g����40�o�C�g��蒷���ꍇ�͌x����
 * �o���ďI�����Ă����̂��A�Z���^�C�g���𐶐����ē��e����悤�ɕύX
 * 
 * 135   06/09/04 13:33 Tsujimura543
 * �o�b�t�@�I�[�o�[������h�~���邽�߁AsetUpReceiveBuffer() �𓱓��B
 * 
 * 134a  06/09/03 20:20 tsupo
 * (1) cookie �܂����C��
 * (2) Visuau Studio 2005 �Ńr���h�����Ƃ��Ɍ��o����� warning ������
 *     �\�[�X���C�� (Visual Studio 6 �ł� Visual Studio 2005 �ł��B��
 *     ��\�[�X�̂܂܁A���Ȃ��r���h�ł���悤�ɂ���)
 * 
 * 134   06/08/31 13:16 Tsujimura543
 * ������M���[�h������
 * 
 * 133   06/08/29 21:19 Tsujimura543
 * �u�L�������vAPI�̂ݕ����Ƃ̂��ƂȂ̂ŁA�u�o�吶���vAPI�֘A�̏�����
 * USE_HAIKU �� #define ����Ă���Ƃ��̂ݗL���Ƃ����`�ɂ���
 * 
 * 132   06/07/26 16:36 Tsujimura543
 * �h���R���u���O�֓��e���鏈�����C��
 * 
 * 131   06/05/31 15:04 Tsujimura543
 * �㗝���e���ɕK�v�ɉ����� <br /> ��t�����鏈������ꂽ
 * 
 * 130   06/05/30 13:21 Tsujimura543
 * autoMode �L�����̓�����C�� (�K�v�ɉ�����<pre>�`</pre>��body��
 * �͂ނ悤�ɂ���)
 * 
 * 129   06/03/15 21:58 Tsujimura543
 * livedoor Blog �̃G���h�|�C���g URL �� ATOMURL_LIVEDOOR_200507 �ɌŒ�
 * 
 * 128   06/03/09 19:28 Tsujimura543
 * �}�C�v���t�B�[���֘A�̏��������S�ɍ폜
 * 
 * 127   06/03/09 19:20 Tsujimura543
 * cocousagi.c ���͕̂ύX�Ȃ� (xmlRPC.dll �̕ύX�̂�)
 * (1) 2006�N3��1���́u�E�F�u���u���O�v���j���[�A���ɑΉ�
 * (2) 2006�N3��6���́u���v���O!�v���j���[�A���ɑΉ�
 * (3) �G�R���O�̐V���� login �V�[�P���X�ɑΉ� (������ς�����̂��͕s��)
 * 
 * 126   06/02/28 14:17 Tsujimura543
 * MSN Spaces �ɑΉ�
 * 
 * 125   06/01/27 20:34 Tsujimura543
 * livedoor Blog �̍č\�z������ǉ�����
 * 
 * 124   06/01/26 14:51 Tsujimura543
 * �A���[�o�u���O�� Atom API �Ɏb��Ή�
 * 
 * 123   06/01/25 19:20 Tsujimura543
 * excite Blog �̃��O�C�������A���e������ύX (������ǉ�)
 * 
 * 122   06/01/04 18:23 Tsujimura543
 * COLORS �������e������ fix
 * 
 * 121   05/12/27 20:26 Tsujimura543
 * ���e���s���́u���e�Ɏ��s���܂����B�v�ƕ\������悤�ɂ���
 * 
 * 120   05/12/27 19:21 Tsujimura543
 * COLORS �̃_�C�A���[�ɂ����e�ł���悤�ɂ��Ă݂�
 * 
 * 119   05/12/06 17:44 Tsujimura543
 * ��M���̃t�@�C���̂��Ƃ�� w/r ���� w+t/r+b �ɕύX(Windows�̏ꍇ)
 * [���e���ʂɗ]���ȃS�~�������Ƃ����錻�ۂɑ΂���΍�]
 * 
 * 118   05/11/28 15:07 Tsujimura543
 * �R�R���O�t���[�� goo Blog �ɑΉ�
 * (�R�R���O�t���[�͓���m�F�ς݁Agoo Blog �̓A�J�E���g�������Ă��Ȃ��̂�
 * ����m�F�͂��Ă��Ȃ�)
 * 
 * 117   05/09/21 22:37 Tsujimura543
 * RSA�������ʊi�[�̈�̉���� free() ���� freeRSAbuffer() �ɕύX
 * 
 * 116   05/09/21 11:37 Tsujimura543
 * �ݒ�t�@�C�����̃p�X���[�h�̈Í����ɑΉ�
 * 
 * 115   05/08/17 15:19 Tsujimura543
 * (1) postEntryOnAtomAPI() �� editEntryOnAtomAPI() �̈����ǉ��ɑΉ�
 * (2) �G�f�B�^�N�����̃f�t�H���g�̎w��� notepad ���� notepad.exe �ɂ���
 * 
 * 114   05/08/11 14:02 Tsujimura543
 * isPostingOK() �̘A�����e�������̋L���^�C�g���� utf2sjis() ���鏈����
 * NULL ���Ԃ��Ă����Ƃ��ɗ����Ă��܂��s����C��
 * 
 * 113   05/08/10 16:04 Tsujimura543
 * lcc-win32 �ł��R���p�C���ł���悤�ɁA�w�b�_�t�@�C���̃C���N���[�h����
 * ��ύX
 * 
 * 112   05/07/20 15:42 Tsujimura543
 * livedoor Blog �̐V���G���h�|�C���gURL�g�������֘A�������C��
 * 
 * 111   05/07/20 15:17 Tsujimura543
 * livedoor Blog �̐V�G���h�|�C���gURL�Ŏ����Ă݂đʖڂȂ�A���G���h�|�C��
 * �gURL���g���悤�ɂ��Ă݂�
 * 
 * 110   05/07/19 18:56 Tsujimura543
 * So-net blog �ɑΉ�
 * 
 * 109   05/07/13 18:43 Tsujimura543
 * �A���[�o�u���O�̕����R�[�h�̕ύX�ɑΉ������ƂɘR�ꂪ�������̂ŁA
 * ���������Ή���Ƃ����{����
 * 
 * 108   05/07/13 17:34 Tsujimura543
 * �A���[�o�u���O�̕����R�[�h�̕ύX�ARSS �� URL �̍ĕύX�ɑΉ�
 * 
 * 107   05/04/27 16:55 Tsujimura543
 * �R�R���O�Ŏ擾�����J�e�S�����̕����������񕜂ł��Ȃ��ꍇ�ł��A
 * �u�J�e�S���w��Ȃ��v�œ��e�ł���悤�ɂ���
 * 
 * 106   05/04/21 19:12 Tsujimura543
 * editForRakuten() ��ǉ����A�y�V�L��ł͎g���Ȃ���������������悤�ɂ���
 * 
 * 105   05/04/21 16:43 Tsujimura543
 * �y�V�L��ɑΉ��B���e�ł��邱�Ƃ��m�F
 * 
 * 104   05/04/20 15:33 Tsujimura543
 * ��M���e���́u�o����r�܂��� Blog Pet API�v���Ăяo���̂�}������悤��
 * ����
 * 
 * 103   05/04/14 15:45 Tsujimura543
 * FC2BLOG �ɑΉ��B���e�ł��邱�Ƃ��m�F
 * 
 * 102   05/04/05 10:27 Tsujimura543
 * �A���[�o�u���O�� RSS �� URL �ύX�ɔ����C��
 * 
 * 101   05/04/01 21:06 Tsujimura543
 * 2.23 ��
 * 
 * 100   05/04/01 21:04 Tsujimura543
 * (1) �A���u���̃��j���[�A����A�u�����������E�B�U�[�h�v�Ŏw�肵���J�e�S��
 *     �����f����Ȃ��Ȃ��Ă��܂����s����C��
 * (2) ���v���O! �� login �菇�ύX�ɔ��� xmlRPC.dll �̏C���̉e�������ɋy��
 *     �Ȃ����Ƃ��m�F
 * 
 * 99    05/04/01 16:53 Tsujimura543
 * �A���[�o�u���O�̃��j���[�A���ɔ����d�l�ύX(XML-RPC API �̔p�~�A
 * �Ǘ���ʂ̕ύX)�ɑΉ�
 * 
 * 98    05/03/29 15:02 Tsujimura543
 * FC2NETWORK �������e�����ł̉��s�̈����𒲐�
 * 
 * 97    05/03/29 14:58 Tsujimura543
 * FC2NETWORK �������e�������C��
 * 
 * 96    05/03/29 14:16 Tsujimura543
 * (1) Windows 98 ��(Windows 95�ł�?)�������Ă��錻��(notepad ���I�����Ȃ�
 *     �����ɂǂ�ǂ񏈗�����ɐi��ł���)�ɑΏ�
 * (2) FC2NETWORK���̓��L�ɑΉ�
 * 
 * 95    05/03/25 21:47 Tsujimura543
 * JUGEM�̓��e�����������ŃJ�e�S�����̎w����ł���悤�ɂ���
 * 
 * 94    05/03/25 20:48 Tsujimura543
 * excite�u���O�̓��e�����������ŃJ�e�S�����̎w����ł���悤�ɂ���
 * 
 * 93    05/03/25 19:50 Tsujimura543
 * ���v���O�̓��e�����������ŃJ�e�S�����̎w����ł���悤�ɂ���
 * 
 * 92    05/03/25 19:17 Tsujimura543
 * �G�R���O�̓��e�����������ŃJ�e�S�����̎w����ł���悤�ɂ���
 * 
 * 91    05/03/25 15:06 Tsujimura543
 * �E�F�u���u���O�̓��e�����������ŃJ�e�S����(�e�[�}��)�̎w����ł���悤
 * �ɂ���
 * 
 * 90    05/03/16 16:46 Tsujimura543
 * �w�肵���J�e�S���ɐ��������e����Ȃ����Ƃ�����s��ɑΏ�
 * 
 * 89    05/03/14 19:26 Tsujimura543
 * ��M�@�\��ǉ�
 * 
 * 88    05/03/08 20:36 Tsujimura543
 * �uSweetBox Blog�v�ɋL�q�𓝈�
 * 
 * 87    05/03/08 17:06 Tsujimura543
 * SweetBox Blog �ɑΉ�
 * 
 * 86    05/03/07 23:23 Tsujimura543
 * NetLaputa �� 269g �ɑΉ�
 * 
 * 85    05/02/21 22:53 Tsujimura543
 * �A���[�o�u���O�ƃE�F�u���u���O���A�t�B���G���g�\�u���O�Ƃ��Ĉ����悤
 * �ɕύX
 * 
 * 84    05/02/21 22:45 Tsujimura543
 * ���v���O�ƃh���R���̋L�������ɖ��ߍ��ފG�������y�b�g�̎�ނɍ��킹��
 * �ς���悤�ɂ���
 * 
 * 83    05/02/21 14:31 Tsujimura543
 * �A���[�o�u���O�ł� NewsHandler �݊� XML-RPC API ���g���邱�Ƃ��m�F�B
 * �����I�� XML-RPC API ���g���ē��e���鏈����K�p���Ă݂��B
 * 
 * 82    05/02/21 13:37 Tsujimura543
 * Newshandler �ł��u�A�����e�`�F�b�N�v�@�\�������悤�ɂ���
 * 
 * 81    05/02/21 13:16 Tsujimura543
 * NewsHandler �����̊Ԃɂ� MovableType �݊� API ���T�|�[�g����
 * �悤�ɂȂ��Ă����̂ŁA�J�e�S���֘A�̏����� Movable Type �݊� API
 * �����Ƃ��Ĉ����悤�ɂ���
 * 
 * 80    05/02/18 20:53 Tsujimura543
 * 2.00 ��
 * 
 * 79    05/02/18 17:43 Tsujimura543
 * �u���������v����uBlogPet�v�ւ̈ڍs�ɔ����C���̑�3�e
 *   -C �I�v�V������ǉ�
 * 
 * 78    05/02/18 17:24 Tsujimura543
 * �u���������v����uBlogPet�v�ւ̈ڍs�ɔ����C���̑�2�e
 *   ���e����J�e�S���� BlogPet �̎�ʂɍ��킹�ĕς���悤�ɂ���
 * 
 * 77    05/02/18 16:51 Tsujimura543
 * �u���������v����uBlogPet�v�ւ̈ڍs�ɔ����C���̑�1�e
 *  (1) BlogPet �̎�ʂ�I���E�ݒ�\�ɂ���
 *  (2) ���e�L���̓��e�� BlogPet �̎�ʂɍ��킹�ĕς���悤�ɂ���
 *  (3) ���e�L���� powered by cocousagi �̕�����𖄂ߍ��ނ悤�ɂ���
 * 
 * 76    04/11/29 19:10 Tsujimura543
 * 1.50 ��
 * 
 * 75    04/11/29 19:03 Tsujimura543
 * �}�C�v���t�B�[���֘A�֐����R�����g�A�E�g
 * 
 * 74    04/11/29 18:44 Tsujimura543
 * Seesaa Blog �ւ̓��e(XML-RPC API ���N�G�X�g)�� https �ōs�Ȃ��悤�ɂ���
 * 
 * 73    04/11/29 18:30 Tsujimura543
 * �A�}�]���̂������ߏ��i�֘A�������C��
 * 
 * 72    04/11/29 13:26 Tsujimura543
 * �R���\�[�����͊֘A�֐��𕪗��AxmlRPC.dll �ֈڊ�
 * 
 * 71    04/11/29 11:42 Tsujimura543
 * blog ��ʑI����ʂ� 80x23 �ȓ��ɂ����܂�悤�ɏC�� (blog��ʑ����ɑΉ�)
 * 
 * 70    04/11/26 22:15 Tsujimura543
 * �E�F�u���u���O�ł͋L���̑薼��50�o�C�g���傫���Ǝ��s���邱�Ƃ�
 * �����B�΍�����{ (1.50 RC1 ��)
 * 
 * 69    04/11/26 21:47 Tsujimura543
 * �s�v�ɂȂ����ϐ����폜
 * 
 * 68    04/11/26 21:39 Tsujimura543
 * �E�F�u���u���O�ɓ��e�ł��邱�Ƃ��m�F
 * 
 * 67    04/11/26 13:19 Tsujimura543
 * �G�R���O�ɓ��e�ł��邱�Ƃ��m�F
 * 
 * 66    04/11/25 19:03 Tsujimura543
 * �G�R���O�Ή��� (���얢�m�F)
 * 
 * 65    04/11/17 19:19 Tsujimura543
 * 1.44��
 * 
 * 64    04/11/11 11:29 Tsujimura543
 * Windows 98 �ł̓���m�F�I�� (1.43 ������)
 * 
 * 63    04/11/10 11:03 Tsujimura543
 * Windows 98 �����ƁA��Ɂu�֘A���Ђ͌�����܂���ł����v�ɂȂ��Ă���
 * �����ۂɎb��Ώ�(���{�I�Ȍ����́u�����������E�B�U�[�h�v�̕��ɂ���Ǝv��
 * ���)
 * (1.43 RC4 ��)
 * 
 * 62    04/11/08 10:25 Tsujimura543
 * </dt>�̑}���ʒu���Ԉ���Ă����̂��C���B
 * (1.43 RC3 ��)
 * 
 * 61    04/11/05 17:55 Tsujimura543
 * �h���R���u���O���u�������߁v�w�薳���Ώ�(�A�t�B���G�C�g�֎~)�����ɂ���
 * (1.43 RC2 ��)
 * 
 * 60    04/11/05 15:33 Tsujimura543
 * (1) ���v���O�A�h���R���u���O�ŋL���{���������Ɠ��e�Ɏ��s���邱�Ƃ�
 *     �����B�΍��g�ݍ��ށB 
 * (2) excite�u���O���u�������߁v�w�薳���Ώۂɂ���
 *     (�A�t�B���G�C�g���֎~����Ă��邽��)
 * 
 * 59    04/11/04 18:12 Tsujimura543
 * ��������Afix (1.43 RC1 ��)
 * 
 * 58    04/11/02 22:00 Tsujimura543
 * ������������Ђ��u�������߁v��������Ȃ��ꍇ�́A�u���ׂĂ̏��i�v��
 * ������������悤�ɂ���
 * 
 * 57    04/11/02 20:47 Tsujimura543
 * �A�}�]���́u��������&�z�r�[�v�̌����ɑΉ�
 * 
 * 56    04/11/02 18:01 Tsujimura543
 * (1) ����T�C�g�ɕ���blog���J�݂��Ă���ꍇ��blogID���菈�����C��
 * (2) MovableType API �ɂĎ擾�����J�e�S���̐���0�̂Ƃ��ɃA�v���P�[�V����
 *     �G���[�ɂȂ�s��ɑΏ�
 * 
 * 55    04/11/01 20:09 Tsujimura543
 * �x�����x��4�ł� warning �� 0 �ɂ���
 * 
 * 54    04/11/01 19:54 Tsujimura543
 * �w�u���������v����̂������߁x�������I�Ɏ���
 * 
 * 53    04/10/27 15:34 Tsujimura543
 * -V �I�v�V������ǉ�
 * 
 * 52    04/10/27 15:03 Tsujimura543
 * �u���������̋@���������Ƃ��v�ɗ]���Ƀ�����������悤�Ƃ��Ă����o�O��
 * �C��
 * 
 * 51    04/10/15 16:26 Tsujimura543
 * �A���[�o�u���O�̊Ǘ���ʂ̃o�O���C�ɔ����A�����N���ߍ��݂𕜊�������
 * [��ʌ��J�� 1.42]
 * 
 * 50    04/10/15 15:22 Tsujimura543
 * NewsHandler �̏ꍇ�̂݁A���e�������������Ȓl�ɂȂ錻�ۂɑΏ�
 * (�T�[�o���̕s��ł��邪�A�u�����������v���Ŏb��Ώ����Ă���)
 * 
 * 49    04/10/14 14:21 Tsujimura543
 * ���e�҂�ID��blog�̃I�[�i�[��ID����ID�̏ꍇ�ɑΉ� (JUGEM�̏ꍇ)
 * 
 * 48    04/10/13 16:32 Tsujimura543
 * -u, -U �I�v�V������ǉ�
 * 
 * 47    04/10/12 13:48 Tsujimura543
 * title �� body �̗̈�T�C�Y�𑝂₵�A�m�ۂ���ꏊ���X�^�b�N����q�[�v��
 * �ύX
 * 
 * 46    04/10/08 20:29 Tsujimura543
 * �L�k�K�T�����L�Ή�
 * 
 * 45    04/09/29 13:37 Tsujimura543
 * ��ʌ��J�� 1.41
 *   (�J�e�S���I���֘A�o�OFix [xmlRPC.dll �̂ݏC��])
 * 
 * 44    04/09/28 17:40 Tsujimura543
 * �}�C�v���t�B�[���������ΏۊO�Ƃ��� [��ʌ��J�� 1.40]
 * 
 * 43    04/09/28 16:40 Tsujimura543
 * �h���R���u���O�Ή�
 * 
 * 42    04/09/28 15:22 Tsujimura543
 * �A���[�o�u���O�Ή�
 * 
 * 41    04/09/17 16:10 Tsujimura543
 * �G���[���b�Z�[�W��ǉ�
 * 
 * 40    04/09/13 15:03 Tsujimura543
 * ���e�ɐ����������ǂ����A���b�Z�[�W���o���悤�ɂ��� (���e�ɂ͐���
 * ���Ă��邪���r���h�ɂ͎��s���Ă���ꍇ�����邽�߁A�u���Ԃ�A���e
 * �ɐ��������v�Ƃ����B���ȃ��b�Z�[�W�ɂ��Ă���)
 * 
 * 39    04/09/07 13:44 Tsujimura543
 * �ulogin �Ɏ��s���܂����B�v�Ƃ����G���[���b�Z�[�W��ǉ��B
 * 
 * 38    04/09/07 13:35 Tsujimura543
 * mixi �̓��L�ɑΉ� (���e�ł��邱�Ƃ��m�F�ς�)
 * 
 * 37    04/09/06 14:22 Tsujimura543
 * "<![CDATA[ "�� "]]>" �Ƃ��������񂪔o�咆�ɏo�������ꍇ�A�ēx�o����擾
 * �������悤�ɂ���(�擾�Ď��s�͍ő�3��܂Ŏ��s)
 * 
 * 36    04/09/03 15:53 Tsujimura543
 * ��ʌ��J�� 1.3.1
 * 
 * 35    04/09/03 15:37 Tsujimura543
 * ��ʌ��J���� 1.3.1 RC1
 *   �}�C�v���t�B�[���ɑΉ� (���ۂɓ��e�ł��邱�Ƃ��m�F)
 * 
 * 34    04/09/02 20:12 Tsujimura543
 * �L�[���[�h�����N�ŕ������������������ꍇ�́A�L�[���[�h�����N�Ȃ���
 * �L���𓊍e����悤�ɂ��� (�����������������͌����_�ł͕s��)
 * 
 * [     04/08/31 22:34 Tsujimura543      ]
 * [��ʌ��J�� 1.2.5 xmlRPC.dll �݂̂̏C��]
 *
 * 33    04/08/31 16:37 Tsujimura543
 * ��ʌ��J�� 1.2.4
 * 
 * 32    04/08/31 16:36 Tsujimura543
 * �L������userName�����̕����񂪑��݂��Ȃ��ꍇ�A�j�b�N�l�[���u��������
 * �L���{���̐擪�ɃS�~���t���Ă��܂��s����C��(��������ԂŁu�͂Ă�
 * �L�[���[�h�����N�vAPI���Ăяo���Ɖ�����͈͂��L���S���ɋy��ł��܂�)
 * 
 * 31    04/08/31 14:40 Tsujimura543
 * ��ʌ��J����
 * 
 * 30    04/08/31 14:03 Tsujimura543
 * �j�b�N�l�[���u�������C�� (�u�������Ώۂ�userName���L�����ɕ�����
 * ���݂���ƋL���{���̐擪�̕������������Ȃ��Ă��܂��s��ɑΏ�)
 * 
 * 29    04/08/30 19:29 Tsujimura543
 * ��ʌ��J�� (1.2.3)
 * (1) �A�����e�������O���I�v�V������ǉ�
 * (2) �ublog���[�U���v���u�w�肵���j�b�N�l�[���v�ɒu������@�\��ǉ�
 * 
 * 28    04/08/30 18:30 Tsujimura543
 * (1) 1�T�Ԃ�1�񂵂����e���Ȃ��悤�ɐ�������͂����A60�T�Ԃ�1�񂵂����e
 *     ���Ȃ��悤�ɂȂ��Ă����o�O���C��
 * (2) getRecentPostTitlesViaRSS() ��ǉ��BJUGEM�Aexcite�u���O�A���v���O��
 *     �A�����e�����ł���悤�ɂ��Ă݂�
 * 
 * 27    04/08/27 18:26 Tsujimura543
 * ��ʌ��J�� (1.2.1)
 *   ���v���O�ɑΉ� (���ۂɓ��e�ł��邱�Ƃ��m�F)
 * 
 * 26    04/08/27 11:28 Tsujimura543
 * excite�u���O�Ή� (���ۂɓ��e�ł��邱�Ƃ��m�F�ς�)
 * 
 * 25    04/08/27 9:29 Tsujimura543
 * blog��ʂ� newPostOnly �̂Ƃ��̏������C��
 *   (�Θb�`���ł̎g�p���� blog ID �̓��͂����鏈���������Ă���)
 * 
 * 24    04/08/25 16:59 Tsujimura543
 * JUGEM �ɑΉ� (XML-RPC API �� Atom API ���g�킸�A�Ǝ���@�ɂđΉ�)
 * 
 * 23    04/08/24 16:37 Tsujimura543
 * ��ʌ��J�� (1.1.4)
 * 
 * 22    04/08/24 14:44 Tsujimura543
 * �ݒ�t�@�C���� unsupported ���w�肵���ꍇ�A�����I�Ɂublog���[�U���v�A
 * �ublog���e�p�p�X���[�h�v���N���A����悤�ɂ���
 * 
 * 21    04/08/24 14:20 Tsujimura543
 * �R�����g�C���A�ǉ�
 * 
 * 20    04/08/24 14:16 Tsujimura543
 * Blog��ʂ� unsupported ��ǉ�
 * 
 * 19    04/08/24 11:24 Tsujimura543
 * �ݒ����ÓI�Ɋm�ۂ���̂���߁A���I�Ɋm�ۂ���悤�ɂ���
 * 
 * 18    04/08/24 11:11 Tsujimura543
 * �ݒ�t�@�C���� keywordLink: on �Ə����Ă��A�L�[���[�h�����N�����ߍ���
 * ��Ȃ��s����C��
 * 
 * 17    04/08/20 16:52 Tsujimura543
 * ���e�� blog �� localhost ���ɑ��݂���ꍇ�ɑΉ�
 * 
 * 16    04/08/19 13:46 Tsujimura543
 * ��ʌ��J�� (1.1.3)
 *   Windows 95 �n�̏ꍇ�̃L�[���͏��������P
 * 
 * 15    04/08/19 10:46 Tsujimura543
 * ��ʌ��J�� (1.1.2) �� ���ǁA���J����
 * 
 * 14    04/08/19 9:31 Tsujimura543
 * News-Handler ����� metaWeblog.newPost �̂݃T�|�[�g���Ă��� blog
 * (�u�����������甠�v���܂�)�ɑΉ�
 * 
 * 13    04/08/19 8:52 Tsujimura543
 * blog_info_tbl[] �� atomAPI ��ǉ�����̂�Y��Ă��� (�� �ǉ��ς�)
 * 
 * 12    04/08/17 18:50 Tsujimura543
 * �R�����g�̌뎚�C��
 * 
 * 11    04/08/17 17:03 Tsujimura543
 * ��ʌ��J�� (1.1.1)
 * 
 * 10    04/08/17 14:40 Tsujimura543
 * ���t�@�N�^�����O�����{
 * 
 * 9     04/08/17 12:25 Tsujimura543
 * blogger API, metaWeblog API �̂݃T�|�[�g�� blog �ւ̑Ή�����(����͖��m�F)
 * 
 * 8     04/08/16 19:09 Tsujimura543
 * blogger API �̂݃T�|�[�g���Ă��� blog�AmetaWeblog API �̂݃T�|�[�g����
 * ���� blog �ւ̑Ή���ǉ�
 * 
 * 7     04/08/13 15:06 Tsujimura543
 * Atom API �o�R�ł̓��e�ł��u�A�����e�}�~�@�\�v�������悤�ɂ���
 * 
 * 6     04/08/13 13:55 Tsujimura543
 * �o��r���̗v�ہA�L�[���[�h�����N���݂̗v�ۂ�Θb�^���[�h�ł�
 * �I���ł���悤�ɂ���
 * 
 * 5     04/08/13 10:56 Tsujimura543
 * (1) Movable Type �ւ̓��e����m�F����
 * (2) �Θb�^�ł̃p�����[�^���͂ɂ�铮��m�F����
 * 
 * 4     04/08/13 9:48 Tsujimura543
 * Seesaa BLOG �ɂē���m�F
 *  (���e�����Ɏ��Ԃ�������悤�Ȃ̂ŁA�^�C���A�E�g���Ԃ̌��������K�v)
 * 
 * 3     04/08/12 21:18 Tsujimura543
 * �R�R���O�ȊO�ɂ��Ή�(�Ƃ肠�����Alivedoor Blog �ɂē���m�F����)
 * 
 * 2     04/07/07 11:37 Tsujimura543
 * ��ʌ��J�� (1.0.1)
 */

#ifdef  WIN32
#include <time.h>
#include <process.h>
#else
#include <sys/time.h>
#endif
#include "xmlRPC.h"
#include "atomAPI.h"
#include "amazon.h"
#include "rakuten.h"
#include "encryptRSA.h"
#include "postArticle.h"
#include "utility.h"
#include <assert.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/blogolee/postArticle.c 3     09/05/29 7:55 tsupo $";
#endif

extern BLOG_INFO    blog_info_tbl[];


/*
 *  �L�[���[�h���o
 */
#ifndef	iskanji1
#define	iskanji1(s)	((((s)>=0x81) && ((s)<=0x9f)) || \
			 (((s)>=0xe0) && ((s)<=0xfc)))
#endif
#ifndef	iskanji2
#define	iskanji2(s)	((((s)>=0x40) && ((s)<=0x7e)) || \
			 (((s)>=0x80) && ((s)<=0xfc)))
#endif

char    *
getKeyword( const char *body, char *keyword )
{
    const char  *kana1  = "�@";
    const char  *kana2  = "��";
    const char  *kana3  = "�[";
    const char  *kanji1 = "��";
    const char  *p = body;
    int         found    = 0;
    int         kanji    = 0;
    int         yokomoji = 0;
    int         idiom    = 0;

    /*
     *  �����݂̂�3�����ȏ�A������ꍇ�A�܂��̓J�^�J�i�݂̂�4�����ȏ�A��
     *  ����ꍇ�A�L�[���[�h�Ƃ݂Ȃ��Ē��o����
     */

    while ( *p ) {
        if ( !kanji && iskanji1( (unsigned char)*p ) ) {
            kanji = 1;
        }
        else if ( kanji && iskanji2( (unsigned char)*p ) ) {
            kanji = 0;
            if ( ((*(p - 1) >= kana1[0]) && (*(p - 1) <= kana2[0])) ||
                 ((*(p - 1) == kana3[0]) && (*p == kana3[1])      )    ) {
                yokomoji++;
                idiom    = 0;
            }
            else if ( *(p - 1) >= kanji1[0] ) {
                idiom++;
                yokomoji = 0;
            }
            else {
                if ( yokomoji >= 4 ) {
                    found = 1;
                    strncpy( keyword,
                             p - (((yokomoji + 1) * 2) - 1),
                             yokomoji * 2 );
                    keyword[yokomoji * 2] = NUL;
                    break;
                }
                if ( idiom >= 3 ) {
                    found = 1;
                    strncpy( keyword,
                             p - (((idiom + 1) * 2) - 1),
                             idiom * 2 );
                    keyword[idiom * 2] = NUL;
                    break;
                }
                yokomoji = 0;
                idiom    = 0;
            }
        }
        else {
            if ( yokomoji >= 4 ) {
                found = 1;
                strncpy( keyword,
                         p - (yokomoji * 2),
                         yokomoji * 2 );
                keyword[yokomoji * 2] = NUL;
                break;
            }
            if ( idiom >= 3 ) {
                found = 1;
                strncpy( keyword,
                         p - (idiom * 2),
                         idiom * 2 );
                keyword[idiom * 2] = NUL;
                break;
            }

            kanji    = 0;
            yokomoji = 0;
            idiom    = 0;
        }
        p++;
    }

    if ( !found )
        strcpy( keyword, "�u���O" );

    return ( keyword );
}


#define MAX_TITLE_LEN   512
#define MAX_BODY_LEN    (MAX_CONTENT_SIZE * 16)
#define MAX_POSTID_LEN  MAX_POSTIDLENGTH
#define MAX_HAIKU_LEN   1024
#define MAX_PROMPT_LEN  80

#define MAX_CATS        32  /* ����blog���J�e�S���ő吔 (�b��l)           */
#define MAX_USERS       20  /* ����blog���ő僆�[�U��   (�b��l)           */
#define MAX_BLOGS       10  /* ����V�X�e�����ő�ݒu�\blog�� (�R�R���O) */
#define RECENT_ENTRIES  15  /* �A�����e�}�~�`�F�b�N�Ɏg���L���̎擾��      */


/*
 *  blog ID �̎擾�E�ݒ�
 */

void
setBlogID( char *blogID, BLOGKIND blogType )
{
    if ( !(blogID[0]) ) {
        // CBlogoleeDlg::OnExecutePostArticle() ���s���_�� blogID �͊m��ς݂Ȃ̂ŁA
        // �ȉ��̏��������s����邱�Ƃ͂Ȃ�(���A�R�[�h�͎c���Ă���)
        BLOGINF blogInfo[MAX_BLOGS];
        char    prompt[MAX_PROMPT_LEN];
        char    buf[BUFSIZ];
        int     numOfBlogs = MAX_BLOGS;
        int     r, i;

        /* --- ���e�\�� blog �ꗗ�̎擾 */
        if ( (blogType == livedoor) ||
             (blogType == lovelog)  ||
             (blogType == sonet)    ||
             (blogType == blogger)  ||
             (blogType == vox)      ||
             (blogType == hatena)   ||
             (blogType == atomAPI)     )
            r = getBlogIDsOnAtomAPI( NULL, NULL, &numOfBlogs, blogInfo );
        else
            r = getBlogIDs( NULL, NULL, &numOfBlogs, blogInfo );
                                                            /* blogger API */
        if ( r == 1 )
            strcpy( (char *)blogID, blogInfo[0].blogID );/* �m�� */
        else if ( r > 1 ) {
            /* ---- ���e�� blog �̑I�� */
            if ( isatty( fileno( stdin ) ) ) {
                do {
                    for ( i = 0; i < r; i++ ) {
                        printf( "(%d)\t%s (blogID: %s)\n",
                                i + 1,
                                utf2sjis( blogInfo[i].blogName ),
                                blogInfo[i].blogID );
                    }
                    sprintf( prompt, "�ǂ� blog �ɓ��e���܂���? (1 - %d): ", r );
                    inputString( (char *)buf, prompt, FALSE );
                    i = atoi( buf );
                    if ( (i >= 1) && (i <= r) ) {
                        strcpy( blogID, blogInfo[i - 1].blogID );
                        break;
                    }
                } while ( (i < 1) || (i > r) );
            }
            else {
                int rr = -1;
                do {
                    rr = selectBlog( blogInfo, r );
                    if ( (rr >= 0) && (rr < r) )
                        strcpy( blogID, blogInfo[rr].blogID );
                } while ( (rr < 0) || (rr >= r) );
            }
        }
    }
#ifdef  _DEBUG
    if ( isatty( fileno( stderr ) ) )
        fprintf( stderr, "blogID = %s\n", blogID );
#endif
}



char    *
similaritySearch(
        const char *body,   /* (I) �L���{��                              */
        int        mode,    /* (I) ���ߍ��݃��[�h [1: �摜, 2: �e�L�X�g] */
        int        numOfRecomended  /* (I) �������ߏ��i�f�ڌ���          */
    )
{
    int         numOfAmazon   = numOfRecomended;
    int         numOfRakuten  = numOfRecomended;
    AMAZON_LITE             *ap;
    RAKUTEN_API_REQUEST     rrp;
    RAKUTEN_API_RESPONSE    *rp;
    int         ret, i, n = 0, m = 0;
    char        keyword[BUFSIZ];
#if 0
    time_t      t = time( NULL );
    struct tm   *tm = localtime( &t );
    int         yy = tm->tm_year + 1900;
    int         mm = tm->tm_mon + 1;
    int         dd = tm->tm_mday;
#endif
    char        *sim = NULL;
    int         len = 0;

    /* �֘A�L������ (bulkfeeds �𗘗p) */
    getKeyword( body, keyword ); /* �L���{������L�[���[�h�𒊏o */
#ifdef  _DEBUG
    if ( isatty( fileno( stderr ) ) )
        fprintf( stderr, "�L�[���[�h: %s\n", keyword );
#endif

    /* �֘A���i���� (Amazon Web Services �𗘗p) */
    ap = (AMAZON_LITE *)malloc( sizeof ( AMAZON_LITE ) * numOfAmazon );
    if ( ap ) {
        char    *searchTitle = "";
        int     searchMode   = AMAZON_MODE_TOYS;

        /* �܂��A�u��������&�z�r�[�v�Ō��� */
#ifdef  USE_AWS30
        ret = searchItemsOnAmazon( AMAZON_TYPE_LITE,
                                   searchMode,
                                   AMAZON_STYPE_KEYWORD, keyword,
                                   &numOfAmazon, ap );
#else
        ret = searchItemsOnAmazon4( AMAZON_TYPE_SMALL,
                                    searchMode,
                                    AMAZON_STYPE_ITEMSEARCH, keyword,
                                    &numOfAmazon, ap );
#endif

        if ( numOfAmazon == 0 ) {
            /* �q�b�g��0�Ȃ�A���߂āu�a���v�Ō��� */
            numOfAmazon = numOfRecomended;
            searchMode  = AMAZON_MODE_JBOOKS;
#ifdef  USE_AWS30
            ret = searchItemsOnAmazon( AMAZON_TYPE_LITE,
                                       searchMode,
                                       AMAZON_STYPE_KEYWORD, keyword,
                                       &numOfAmazon, ap );
#else
            ret = searchItemsOnAmazon4( AMAZON_TYPE_SMALL,
                                        searchMode,
                                        AMAZON_STYPE_ITEMSEARCH, keyword,
                                        &numOfAmazon, ap );
#endif
        }
        if ( numOfAmazon == 0 ) {
            /* �q�b�g��0�Ȃ�A���x�́u���ׂĂ̏��i�v�Ō��� */
            numOfAmazon = numOfRecomended;
            searchMode  = AMAZON_MODE_BLENDED;
#ifdef  USE_AWS30
            ret = searchItemsOnAmazon( AMAZON_TYPE_LITE,
                                       searchMode,
                                       AMAZON_STYPE_KEYWORD, keyword,
                                       &numOfAmazon, ap );
#else
            ret = searchItemsOnAmazon4( AMAZON_TYPE_SMALL,
                                        searchMode,
                                        AMAZON_STYPE_ITEMSEARCH, keyword,
                                        &numOfAmazon, ap );
#endif
        }
        if ( numOfAmazon == 0 ) {
            /* �q�b�g��0�Ȃ�A�Ō�́u�a��-���ǂ������v�̃x�X�g�Z���[���擾 */
            numOfAmazon = numOfRecomended;
            searchMode  = AMAZON_MODE_JBOOKS;
            searchTitle = "���ǂ��������Ѓx�X�g�Z���[";
#ifdef  USE_AWS30
            ret = getSalesRankingOnAmazon( AMAZON_TYPE_LITE,
                                           searchMode,
                                           AMAZON_NODE_CHILDREN,
                                           searchTitle,
                                           &numOfAmazon, ap );
#else
            ret = getSalesRankingOnAmazon4( AMAZON_TYPE_SMALL,
                                            searchMode,
                                            AMAZON_NODE_CHILDREN,
                                            searchTitle,
                                            &numOfAmazon, ap );
#endif
        }

        if ( numOfAmazon == 0 ) {
            if ( isatty( fileno( stderr ) ) )
                fprintf( stderr,
                         "�g%s�h�֘A���Ђ͌�����܂���ł����B\n", keyword);
            else {
                char    buf[BUFSIZ];
                sprintf( buf,
                         "�u%s�v�Ɋ֘A���鏑�Ђ͌�����܂���ł����B    ",
                         keyword );
                MessageBox( NULL, buf,
                            "Amazon Web �T�[�r�X", MB_OK|MB_ICONWARNING );
            }
        }
        else {
            char    *pp;

            if ( !sim ) {
                sim = (char *)malloc( MAX_CONTENT_SIZE * 16 );
                if ( !sim )
                    return ( sim );
                len = 0;
            }

            for ( i = 0, n = 1; i < numOfAmazon; i++ ) {
                pp = utf2sjis( ap[i].productName );
                if ( !pp || !(*pp) )
                    continue;

                if ( n == 1 ) {
                    if ( searchTitle[0] )
                        sprintf( sim + len,
                                 "<hr />"
                                 "%s�������ߏ��i ("
                                 "<strong>%s</strong>)%s",
                                 mode == 1 ? "<p>" : "<dl><dt>",
                                 searchTitle,
                                 mode == 1 ? "</p>\n<p>" : "</dt>\n" );
                    else
                        sprintf( sim + len,
                                 "<hr />"
                                 "%s�������ߏ��i ("
                                 "<strong>�g%s�h�Ɋ֘A����%s�̈ꗗ</strong>)"
                                 "%s",
                                 mode == 1 ? "<p>" : "<dl><dt>",
                                 keyword,
                                 searchMode == AMAZON_MODE_TOYS
                                    ? "��������"
                                    :
                                 searchMode == AMAZON_MODE_BLENDED
                                    ? "���i"
                                    : "����",
                                 mode == 1 ? "</p>\n<p>" : "</dt>\n" );
                }

                switch ( mode ) {
                case 1:
                    /* �摜���ߍ��� */
                    sprintf( sim + strlen( sim ),
                             "<a href=\"%s\">"
                             "<img src=\"%s\" alt=\"%s\" border=\"0\" />"
                             "</a>\n",
                             ap[i].url, ap[i].imageURLmedium, pp );
                    break;

                case 2:
                default:
                    /* �e�L�X�g���ߍ��� */
                    {
                        char *qq = strchr( ap[i].url, '?' );
                        if ( qq )
                            *qq = NUL;
                    }
                    sprintf( sim + strlen( sim ),
                             "<dd><a href=\"%s\">%s</a></dd>\n",
                             ap[i].url, pp );
                    break;
                }

                n++;

                if ( mode == 2 )
                    if ( n >= 4 )
                        break;/* �b��(yaplog��2000�����܂ł������e�ł��Ȃ�) */
            }

            if ( n > 1 ) {
                switch ( mode ) {
                case 1:
                    /* �摜���ߍ��� */
                    strcat( sim, "</p>\n" );
                    break;

                case 2:
                default:
                    /* �e�L�X�g���ߍ��� */
                    strcat( sim, "</dl>\n" );
                    break;
                }
            }
        }

        free( ap );
    }

    /* �֘A���i���� (�y�VWeb�T�[�r�X�𗘗p) */
    memset( &rrp,  0x00, sizeof (RAKUTEN_API_REQUEST)  );
    strcpy( rrp.keyword, keyword );
    rrp.hits = numOfRakuten;
    rp = itemSearchOnRakutenWebAPIex( &rrp );
    if ( rp ) {
        if ( rp->numOfItems <= 0 ) {
            if ( isatty( fileno( stderr ) ) )
                fprintf( stderr,
                         "�g%s�h�֘A���i�͌�����܂���ł����B\n",
                         keyword );
            else {
                char    buf[BUFSIZ];
                sprintf( buf, "�u%s�v�Ɋ֘A���鏤�i�͌�����܂���ł����B    ",
                         keyword );
                MessageBox( NULL, buf,
                            "�y�VWeb�T�[�r�X", MB_OK|MB_ICONWARNING );
            }
        }
        else {
            if ( !sim ) {
                sim = (char *)malloc( MAX_CONTENT_SIZE * 16 );
                if ( !sim )
                    return ( sim );
                len = 0;
            }

            m = 1;
            for ( i = 0; i < rp->numOfItems; i++ ) {
                /*
                printf( "[%d] %s\n", i + 1, rp->item[i].itemName );
                printf( "\t%s %s[%s]\n", rp->item[i].itemUrl,
                        rp->item[i].shopName, rp->item[i].shopCode );
                printf( "\t%s\n", rp->item[i].affiliateUrl );
                printf( "\t%s\n", rp->item[i].mediumImageUrl );
                printf( "\t%s\n", rp->item[i].smallImageUrl );
                printf( "\t%s\n", rp->item[i].shopUrl );
                printf( "\t%s\n", rp->item[i].itemCaption );
                printf( "\t%s %d�~\n", rp->item[i].itemCode,
                        rp->item[i].itemPrice );
                printf( "\t%f\n", rp->item[i].affiliateRate );
                printf( "\t%d / %f\n", rp->item[i].reviewCount,
                        rp->item[i].reviewAverage );
                */

                if ( m == 1 ) {
                    sprintf( sim + len,
                             "<hr />"
                             "%s�������ߏ��i ("
                             "<strong>�g%s�h�Ɋ֘A���鏤�i�̈ꗗ</strong>)"
                             "%s",
                             mode == 1 ? "<p>" : "<dl><dt>",
                             keyword,
                             mode == 1 ? "</p>\n<p>" : "</dt>\n" );
                }

                switch ( mode ) {
                case 1:
                    /* �摜���ߍ��� */
                    sprintf( sim + strlen( sim ),
                             "<a href=\"%s\">"
                             "<img src=\"%s\" alt=\"%s\" border=\"0\" />"
                             "</a>\n",
                             rp->item[i].affiliateUrl,
                             rp->item[i].mediumImageUrl,
                             rp->item[i].itemName );
                    break;

                case 2:
                default:
                    /* �e�L�X�g���ߍ��� */
                    sprintf( sim + strlen( sim ),
                             "<dd><a href=\"%s\">%s</a></dd>\n",
                             rp->item[i].affiliateUrl,
                             rp->item[i].itemName );
                    break;
                }

                m++;

                if ( mode == 2 )
                    if ( (n + m) >= 4 )
                        break;/* �b��(yaplog��2000�����܂ł������e�ł��Ȃ�) */
            }

            if ( m > 1 ) {
                switch ( mode ) {
                case 1:
                    /* �摜���ߍ��� */
                    strcat( sim, "</p>\n" );
                    break;

                case 2:
                default:
                    /* �e�L�X�g���ߍ��� */
                    strcat( sim, "</dl>\n" );
                    break;
                }
            }
        }

        freeRakutenApiResponce( rp );
    }

    return ( sim );
}


/*
 *  ���e�L�����H
 */
BOOL
_makeEntry(
        int    useHatenaLink,
        int    useSimilarity,
        int    numOfRecomended,
        char   *body,
        size_t body_size
    )
{
    BOOL    ret  = FALSE;
    char    *sim = NULL, *pp;

    if ( useSimilarity )
        sim = similaritySearch( body, useSimilarity, numOfRecomended );

    if ( useHatenaLink == 1 ) {
        /* �L�[���[�h�����N���ߍ��� */
        char    *p, *result;
        size_t  sz = MAX_BODY_LEN;

        result = (char *)malloc( MAX_BODY_LEN );
        if ( result ) {
            memset( result, 0x00, MAX_BODY_LEN );
            p = setKeywordLink( sjis2utf( body ),
                                result, sz, 0, CNAME_GENERAL,
                                "_blank", "hatena" );
            if ( p && *p && strcmp( p, "(null)" ) ) {
                if ( !strncmp( p, ";lt=;lt=", 8 ) ) {
                    /* �����������o                       */
                    /*  �� �L�[���[�h�����N���ߍ��݂𒆎~ */
                    if ( isatty( fileno( stderr ) ) )
                        fputs( "�u�͂ĂȃL�[���[�h�����N�v�ŕ�������������"
                               "�܂���!!\n"
                               "�L�[���[�h�����N�̖��ߍ��݂𒆎~���܂��B\n",
                               stderr );
                    else
                        MessageBox( NULL,
                                    "�u�͂ĂȃL�[���[�h�����N�v�ŕ���������"
                                    "�����܂���!!    \n�L�[���[�h�����N�̖�"
                                    "�ߍ��݂𒆎~���܂��B\n",
                                    "�u�͂ĂȃL�[���[�h�����N�v�ŃG���[",
                                    MB_OK|MB_ICONWARNING );
                }
                else {
                    char    *q = utf2sjis( p );
                    if ( q ) {
                        size_t  l = strlen( q );
                        if ( l > body_size ) {
                            strncpy( body, q, body_size - 1 );
                            body[body_size - 1] = NUL;
                        }
                        else
                            strcpy( body, q );
                    }
                }
            }
            else {
                /* �͂Ăȃ_�C�A���[�L�[���[�h���������NAPI�� */
                /* �@�\���Ă��Ȃ��ꍇ                        */
                char    *q;

                memset( result, 0x00, MAX_BODY_LEN );
                p = changeHatenaKeyword( body, result, MODE_HTML );
                q = euc2sjis( p );
                if ( q ) {
                    size_t  l = strlen( q );
                    if ( l > body_size ) {
                        strncpy( body, q, body_size - 1 );
                        body[body_size - 1] = NUL;
                    }
                    else
                        strcpy( body, q );
                }
            }
#ifdef  _DEBUG
            if ( isatty( fileno( stderr ) ) )
                fprintf( stderr, "����: %s\n", body );
#endif
            free( result );
        }
    }

    if ( sim ) {
        if ( strlen( body ) + strlen( sim ) < body_size )
            strcat( body, sim );
        free( sim );
    }

    pp = strrchr( body, '<' );
    if ( pp && !strncmp( pp, "</p>", 4 ) ) {
        strcpy( pp,
          "<br />--- powered by <a href=\""
          "http://watcher.moe-nifty.com/memo/2007/03/blogolee.html"
          "\">BloGolEe</a> ---</p>\n" );
    }
    assert( strlen( body ) < body_size );

    ret = TRUE;

    return ( ret );
}


/*
 *  Atom API �n���e����
 */

int
postArticleOnAtomAPI(
        const char *blogID,       /* ���e�� blog ID     */
        BLOGKIND   blogType,      /* blog ���          */
        const char *title,        /* ���e�L���薼       */
        const char *body,         /* ���e�L���{��       */
        const char *description,  /* ���e�L���T�v       */
        const char *catName       /* ���e�ΏۃJ�e�S���� */
     //,char       *endpointURL   /* �G���h�|�C���gURL  */
    )
{
    int             ret = 0;
    char            summary[BUFSIZ];
    char            postID[MAX_POSTIDLENGTH + 1];
    CATLISTINF_t    categories;
    int             found = FALSE;
    CATLISTINFEX    catEx;
    char            *content;
    CATLISTINF      categoryList[MAX_CATS];
    long            numOfC = MAX_CATS;
    int             numOfCategories;
    int             i;
    char            *subject;
    char            *categoryName;
    BOOL            bRet;

    /* categoryId ���擾 */
    catEx.numberOfCategories = 0;
    categories = (CATLISTINF *)malloc( sizeof ( CATLISTINF ) * 1 );
    numOfCategories = 
        listCategoriesOnAtomAPI( NULL, NULL, blogID, &numOfC, categoryList );
    for ( i = 0; i < numOfCategories; i++ ) {
        categoryName = utf2sjis( categoryList[i].categoryName );

        if ( catName && catName[0] &&
             !strcmp( categoryName, catName ) ) {
            catEx.numberOfCategories = 1;
            strcpy( catEx.categoryName[0], sjis2utf( catName ) );
            found = TRUE;
            break;
        }
    }
    free( (char *)categories );

    /* ���e */
    content = (char *)malloc( (MAX_BODY_LEN * 3) / 2 );
    subject = (char *)malloc( strlen( title ) * 18 + BUFSIZ + 1 );
    strcpy( subject, sjis2utf( title ) );

    if ( blogType == ameblo ) {
        if ( strlen( subject ) >= 48 * 2 ) {
            /* �A���[�o�u���O�ł́A�L���̃^�C�g���� 48�����ȓ� */
            /*     (48������蒷���Ɠ��e�Ɏ��s����)            */
            strcpy( subject, 
                    sjis2utf( "�����̓��L" ) );
        }
    }
    if ( blogType == vox ) {
        if ( strlen( subject ) >= 80 ) {
            /* vox �ł́A�L���̃^�C�g���� 80�o�C�g�ȓ�              */
            /*     (80������蒷���Ƃ��ӂꂽ�����͎̂Ă��Ă��܂�) */
            strcpy( subject, 
                    sjis2utf( "�����̓��L" ) );
        }
    }

    if ( description && *description )
        strcpy( summary, sjis2utf(description) );
    else
        strcpy( summary,
                sjis2utf(
                    "���̋L���́u�u���O�N���C�A���g BloGolEe�v"
                    "�ɂ�铊�e�ł��B" ) );
    strcpy( content, sjis2utf( body ) );

    setTimeoutTime( DEFAULT_HTTP_TIMEOUT * 4 );
    bRet = postEntryOnAtomAPI( NULL, NULL, blogID, 
                               subject,  /* �薼           */
                               summary,  /* �T�v           */
                               content,  /* �{��           */
                               &catEx,   /* �J�e�S��       */
                               TRUE,     /* ���e���       */
                               postID    /* ���e��̋L��ID */
                             );
    setTimeoutTime( DEFAULT_HTTP_TIMEOUT );

    free( subject );
    free( content );

    ret = (bRet == TRUE) ? 1 : 0;

    return ( ret );
}


int
postArticleOnXMLRPC( const char *blogID,        /* ���e�� blog ID     */
                     BLOGKIND   blogType,       /* blog ���          */
                     const char *title,         /* ���e�L���薼       */
                     const char *body,          /* ���e�L���{��       */
                     const char *extended,      /* ���e�L���ǋL       */
                     const char *description,   /* ���e�L���T�v       */
                     const char *keyword,       /* ���e�L���L�[���[�h */
                     const char *catName )      /* ���e�ΏۃJ�e�S���� */
{
    int         ret = 0;
    int         found = FALSE;
    char        *categoryName;
    char        postID[MAX_POSTID_LEN + 1];
    CATLISTINF  categoryList[MAX_CATS];
    CATEGORY    category;
    long        numOfCategories;
    CONTENT     content;
    CONTENTINF  content0;
    CONTENTINF  content2;
    int         i;
    int         retry, retry2;
    BOOL        bRet = FALSE;

    if ( (blogType != bloggerAPI)  &&
         (blogType != metaWeblog)  &&
         (blogType != msnSpaces)   &&
         (blogType != webryX)      &&
         // ����: msnSpaces, webryX �� categoryId �ł͂Ȃ��u�J�e�S�����v���g��
         (blogType != jugemX)      &&
         (blogType != drecomX)     &&
         (blogType != yaplogX)     &&
         (blogType != newPostOnly)    ) {
        /* --�w��J�e�S���� categoryId ���擾 */
        numOfCategories = MAX_CATS;
        getCategoryList( blogID, NULL, NULL,
                         &numOfCategories,
                         categoryList );    /* Movable Type API */
        if ( numOfCategories > 0 ) {
            strcpy( category.categoryId, categoryList[0].categoryId );
            for ( i = 0; i < numOfCategories; i++ ) {
                categoryName = utf2sjis( categoryList[i].categoryName );

                if ( catName && catName[0] &&
                     !strcmp( categoryName, catName ) ) {
                    strcpy( category.categoryId, categoryList[i].categoryId );
                    found = TRUE;
                    break;
                }
            }
        }
    }

    /* -- ���e */
    if ( blogType == newsHandler ) {
        /* News-Handler �̏ꍇ�A���e�����𖾎����Ȃ��ƁA�ςȓ��e�����ɂȂ� */
        /* �Ă��܂����Ƃ����邽�߁A���ʂɑ΍���{�� (�{���́A�T�[�o�̌���  */
        /* ���������e�����ɂȂ�͂�)                                       */
        time_t      t = time( NULL );
        struct tm   *tm = gmtime( &t ); /* �O���j�b�W�W���� */
        sprintf( content.dateCreated,
                 "%04d%02d%02d %02d:%02d:%02d",
                 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                 tm->tm_hour, tm->tm_min, tm->tm_sec );
        /* ���l: yyyy-mm-ddThh:mm:ss �� yyyy-mm-ddThh:mm:ssZ �̌`�����ƕς� */
        /*       ���e����(1�N�O�Ƃ�)�ɂȂ�B yyyymmdd hh:mm:ss �`�����Ƃ��� */
        /*       ���������Ƃ������B                                         */
        /*       ���炩�ɃT�[�o���̕s����Ǝv���邪�A���C������邩�� */
        /*       ����Ȃ��̂ŁA�Ƃ肠�����A�N���C�A���g���őΏ����Ă���     */
    }
    else
        strcpy( content.dateCreated, "" );
    strcpy( content.description, sjis2utf(body) );
    strcpy( content.title,       sjis2utf(title) );
    content.mt_allow_comments = 1;
    content.mt_allow_pings    = 1;
    strcpy( content.mt_convert_breaks, "0" );
    if ( description && *description )
        strcpy( content.mt_excerpt, sjis2utf(description) );
    else
        strcpy( content.mt_excerpt,
                sjis2utf(
                    "���̋L���́u�u���O�N���C�A���g BloGolEe�v"
                    "�ɂ�铊�e�ł��B" ) );
    if ( extended && *extended )
        strcpy( content.mt_text_more, sjis2utf(extended) );
    else
        strcpy( content.mt_text_more, "" );
    if ( keyword && *keyword )
        strcpy( content.mt_keywords, sjis2utf(keyword) );
    else
        strcpy( content.mt_keywords, "BloGolEe" );
    content.numOfTrackbacks = 0;
    memset( &(content.mt_tb_ping_urls), 0x00,
            MAX_PINGS * MAX_LOGICALLINELEN );

    if ( (blogType == msnSpaces) ||
         (blogType == webryX)       ) {
        if ( catName && catName[0] ) {
            /* -- �J�e�S���ݒ� */
            content.numOfCategories = 1;
            strcpy( content.categories[0], catName );
            // ���̂Ƃ���A�J�e�S���w���1���� (�b��)
        }
    }

    memset( &content0, 0x00, sizeof ( CONTENTINF ) );
    if ( (blogType == msnSpaces) ||
         (blogType == webryX)       ) {
        CONTENTINFEX    content0x;
        int             num = 1;

        memset( &content0x, 0x00, sizeof ( CONTENTINFEX ) );
        getRecentPostsEx( "MyBlog", NULL, NULL, &num, &content0x );
                                                /* metaWeblog API */
        strcpy( content0.postid, content0x.postid );
    }
    else
        getRecentPost( blogID, NULL, NULL, &content0 );

    setTimeoutTime( DEFAULT_HTTP_TIMEOUT * 8 );
    retry = 5;
    do {
        memset( postID, 0x00, MAX_POSTID_LEN );
        retry--;
        if ( retry < 0 )
            break;
        if ( blogType == bloggerAPI )
            bRet = newPost( blogID, NULL, NULL, body, TRUE, postID );
                                                        /* blogger API */
        else
            bRet = newPostEx( blogID, NULL, NULL,
                              &content, TRUE, postID ); /* metaWeblog API */

        if ( postID[0] == NUL ) {
            retry2 = 5;
            do {
                retry2--;
                if ( retry2 < 0 )
                    break;
                Sleep( 8000 );
                memset( &content2, 0x00, sizeof ( CONTENTINF ) );
                if ( (blogType == msnSpaces) ||
                     (blogType == webryX)       ) {
                    CONTENTINFEX    content2x;
                    int             num = 1;

                    memset( &content2x, 0x00, sizeof ( CONTENTINFEX ) );
                    getRecentPostsEx( blogID, NULL, NULL, &num, &content2x );
                                                          /* metaWeblog API */
                    strcpy( content2.postid, content2x.postid );
                }
                else
                    getRecentPost( blogID, NULL, NULL, &content2 );

                if ( content2.postid[0]                                  &&
                     ((content0.postid[0] == NUL) ||
                      (strcmp( content2.postid, content0.postid ) != 0))    )
                    strcpy( postID, content2.postid );
            } while ( postID[0] == NUL );
        }
    } while ( postID[0] == NUL );

    if ( postID[0] && (found == TRUE) ) {
        if ( (blogType != msnSpaces) &&
             (blogType != webryX)       ) {
            /* -- �J�e�S���ݒ� */
            retry = 5;
            do {
                retry--;
                if ( retry < 0 )
                    break;
                Sleep( 2500 );
                category.isPrimary = TRUE;
                ret = setPostCategories( postID, NULL, NULL, 1, &category );
                                                    /* Movable Type API */
            } while ( ret == FALSE );

            /* -- rebuild */
         // if ( blogType == metaWeblog ) {
         //         /* �� blogType == metaWeblog �̂Ƃ��́A */
         //         /*    found == FALSE �Ȃ̂ŁA�����ɗ��� */
         //         /*    ���Ƃ͂��蓾�Ȃ�                  */
         //     /* metaWeblog API �̓T�|�[�g���Ă��邪 Movable Type �݊� */
         //     /* API �̓T�|�[�g���Ă��Ȃ� blog �̏ꍇ                  */
         //     editPostEx( postID, NULL, NULL, &content, 1 );
         // }
         // else {
                /* Movable Type �݊� API �T�|�[�g blog �̏ꍇ */
                retry = 5;
                do {
                    retry--;
                    if ( retry < 0 )
                        break;
                    Sleep( 2500 );
                    ret = publishPost(postID,NULL,NULL);/* Movable Type API */
                        /* ����: ���̊֐��̎��s���Ƀ^�C���A�E�g������������ */
                        /*       ���̓J�e�S�������f����Ă��Ȃ��\�������� */
                } while ( ret == FALSE );
         // }
        }
    }
    setTimeoutTime( DEFAULT_HTTP_TIMEOUT );

    ret = (bRet == TRUE) ? 1 : 0;

    return ( ret );
}


/*
 *  �L���� blog �ɓ��e����
 */

BOOL
postArticle(
        const ARTICLE_INFO *article,
        const POST_INFO    *postInfo
    )
{
    BOOL    b   = FALSE;
    int     ret = 0;

    /* ���� */
#ifdef  _DEBUG
    FILE    *fp = fopen( "./blogolee.log", "a" );
    if ( fp ) {
        time_t      t   = time( NULL );
        struct tm   *tm = localtime( &t );
        fprintf( fp,
                 "\n\n*** logging start: %d/%02d/%02d %02d:%02d:%02d ***\n",
                 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                 tm->tm_hour, tm->tm_min, tm->tm_sec );
    }
    setVerbose( TRUE, fp ? fp : stderr );
#endif
    setUseProxy( postInfo->useProxy );
    setBlogKind( postInfo->blogType );

    if ( postInfo->useSimilarity ) {
        if ( postInfo->amazonAssociateID[0] )
            setAssociateIdOnAmazon( postInfo->amazonAssociateID );
        if ( postInfo->amazonSubscriptionID[0] )
            setSubscriptionIDOnAmazon( postInfo->amazonSubscriptionID );
        if ( postInfo->rakutenAffiliateID[0] )
            setAffiliateIdOnRakuten2( postInfo->rakutenAffiliateID );
        if ( postInfo->rakutenDeveloperID[0] )
            setDeveloperIdOnRakuten( postInfo->rakutenDeveloperID );
    }

    _makeEntry( postInfo->useHatenaLink, postInfo->useSimilarity,
                postInfo->numOfRecomended,
                article->body, article->body_size );

    if ( postInfo->blogUserName[0] && postInfo->blogPassword[0] &&
         (postInfo->blogType != newPostOnly) &&
         (postInfo->blogType != exciteBlog)  &&
         (postInfo->blogType != mixi)        &&
         (postInfo->blogType != kinugasa)    &&
         (postInfo->blogType != echoo)       &&
         (postInfo->blogType != fc2network)  &&
         (postInfo->blogType != rakuten)     &&
         (postInfo->blogType != colors)      &&
         (postInfo->blogType != openPne)        ) {
        if ( !strncmp( postInfo->endpointURL, "http://localhost/", 17 ) )
            setUseProxy( FALSE );
        setTargetURL( postInfo->endpointURL );
        setUserInfo( postInfo->blogUserName, postInfo->blogPassword );

        /* -- ���e�� blog ID �̊m�� */
        setBlogID( (char *)(postInfo->blogID), postInfo->blogType );

        if ( !strncmp( postInfo->endpointURL, "http://localhost/", 17 ) &&
             postInfo->useProxy )
            setUseProxy( postInfo->useProxy );
    }

    if ( postInfo->blogUserName[0] && postInfo->blogPassword[0] ) {
        if ( !strncmp( postInfo->endpointURL, "http://localhost/", 17 ) )
            setUseProxy( FALSE );
        setTargetURL( postInfo->endpointURL );
        setUserInfo( postInfo->blogUserName, postInfo->blogPassword );

        /* ���e */
        if ( postInfo->blogType == exciteBlog )
            return ( postArticleOnExcite( postInfo->blogUserName,
                                          postInfo->blogPassword,
                                          article->title, article->body,
                                          article->extended,
                                          postInfo->categoryName ) );
                            /* excite�u���O��p���e���� */
        if ( postInfo->blogType == mixi )
            return ( postArticleOnMixi( postInfo->blogUserName,
                                        postInfo->blogPassword,
                                        article->title, article->body ) );
                            /* mixi��p���e���� */
        if ( postInfo->blogType == kinugasa )
            return ( postArticleOnKinugasa( postInfo->blogUserName,
                                            postInfo->blogPassword,
                                            article->title, article->body ) );
                            /* �L�k�K�T��p���e���� */
        if ( postInfo->blogType == echoo )
            return ( postArticleOnEchoo( postInfo->blogUserName,
                                         postInfo->blogPassword,
                                         article->title, article->body,
                                         postInfo->categoryName ) );
                            /* �G�R���O��p���e���� */
        if ( postInfo->blogType == fc2network )
            return ( postArticleOnFC2NETWORK( postInfo->blogUserName,
                                              postInfo->blogPassword,
                                              article->title,
                                              article->body ) );
                            /* FC2NETWORK��p���e���� */
        if ( postInfo->blogType == rakuten )
            return ( postArticleOnRakuten( postInfo->blogUserName,
                                           postInfo->blogPassword,
                                           article->title, article->body,
                                           postInfo->categoryName ) );
                            /* �y�V�L���p���e���� */
        if ( postInfo->blogType == colors )
            return ( postArticleOnColors( postInfo->blogUserName,
                                          postInfo->blogPassword,
                                          article->title, article->body ) );
                            /* COLORS��p���e���� */
        if ( postInfo->blogType == openPne )
            return ( postArticleOnOpenPNE( postInfo->blogUserName,
                                           postInfo->blogPassword,
                                           article->title, article->body ) );
                            /* OpenPNE��p���e���� */

        if ( postInfo->blogType == tumblr )
            return ( postArticleOnTumblr( postInfo->blogUserName,
                                          postInfo->blogPassword,
                                          postInfo->blogID[0]
                                            ? postInfo->blogID
                                            : postInfo->blogURL,
                                          article->title, article->body ) );
                            /* Tumblr��p���e���� */

        if ( postInfo->blogID[0] ) {
            if ( (postInfo->blogType == livedoor) ||
                 (postInfo->blogType == lovelog)  ||
                 (postInfo->blogType == sonet)    ||
                 (postInfo->blogType == ameblo)   ||
                 (postInfo->blogType == blogger)  ||
                 (postInfo->blogType == vox)      ||
                 (postInfo->blogType == hatena)   ||
                 (postInfo->blogType == atomAPI)     ) {
                ret = postArticleOnAtomAPI( postInfo->blogID,
                                            postInfo->blogType,
                                            article->title, article->body,
                                            article->extended,
                                            postInfo->categoryName
                                         // , (char *)(postInfo->endpointURL)
                                          );
                b = ret ? TRUE : FALSE;
                if ( b && (postInfo->blogType == livedoor) ) {
                    /* livedoor Blog �݂̂̓��ʂȏ��� */
                    BOOL    yesNo = NO;

                    if ( isatty( fileno( stderr ) ) ) {
                        fputs( "�L���𓊍e���܂����B\n", stderr );
                        inputYesNo( &yesNo, "blog ���č\�z���܂���?" );
                    }
                    else {
                        int r = MessageBox( NULL,
                                            "�L���𓊍e���܂����B\n"
                                            "blog ���č\�z���܂���?    ",
                                            "livedoor Blog",
                                            MB_YESNO|MB_ICONINFORMATION );
                        if ( r == IDYES )
                            yesNo = YES;
                    }
                    if ( yesNo == YES ) {
                        /* (blog �̊Ǘ���ʌo�R��)�����I�ɍč\�z���� */
                        rebuildOnLivedoor( postInfo->blogUserName,
                                           postInfo->blogPassword,
                                           postInfo->blogID );
                    }
                }
                return ( b );
                            /* Atom API �n���e���� */
            }
            else
                return ( postArticleOnXMLRPC( postInfo->blogID,
                                              postInfo->blogType,
                                              article->title, article->body,
                                              article->extended,
                                              article->summary,
                                              article->keyword,
                                              postInfo->categoryName ) );
                            /* XML-RPC API �n���e���� */
        }
    }

    if ( isatty( fileno( stdout ) ) ) {
        /* �W���o�͂֏����o�� */
        printf( "�薼: %s\n", utf2sjis( article->title ) );
        printf( "�{��: %s\n", article->body );
    }

#ifdef  _DEBUG
    if ( fp ) {
        time_t      t   = time( NULL );
        struct tm   *tm = localtime( &t );
        fprintf( fp,
                 "\n*** logging end:   %d/%02d/%02d %02d:%02d:%02d ***\n",
                 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                 tm->tm_hour, tm->tm_min, tm->tm_sec );
        fclose( fp );
    }
#endif

    return ( b );
}


/*
 *  ���[�e�B���e�B�֐��Q
 */

/* Unicode(UCS-2BE) (%uXXXX or &#XXXXX;) �� UTF-8 (xxyyzz) �ϊ� */
char    *
convUnicode( unsigned long code )
{
    unsigned short  a, b, c, d;
    static char     codeStr[6];

    if ( code < 0x0080 ) {
        a = (unsigned short)code;
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = NUL;
    }
    else if ( code < 0x0800 ) {
        a = (unsigned short)(((code & 0x07C0) >> 6) | 0xC0);
        b = (unsigned short)(( code & 0x003F)       | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = NUL;
    }
    else if ( code < 0x010000 ) {
        a = (unsigned short)(((code & 0xF000) >> 12) | 0xE0);
        b = (unsigned short)(((code & 0x0FC0) >>  6) | 0x80);
        c = (unsigned short)(( code & 0x003F)        | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = (char)(c & 0xFF);
        codeStr[3] = NUL;
    }
    else {
        a = (unsigned short)(((code & 0x001C0000) >> 18) | 0xF0);
        b = (unsigned short)(((code & 0x0003F000) >> 12) | 0x80);
        c = (unsigned short)(((code & 0x00000FC0) >>  6) | 0x80);
        d = (unsigned short)(( code & 0x0000003F)        | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = (char)(c & 0xFF);
        codeStr[3] = (char)(d & 0xFF);
        codeStr[4] = NUL;
    }

    return ( codeStr );
}

char    *
decodeNumericReference( char *src )
{
    char    *p    = src;
    char    *temp = (char *)malloc( strlen( src ) + 1 );

    if ( temp ) {
        unsigned long   l;

        temp[0] = NUL;
        while ( *p ) {
            if ( (*p == '&') && (*(p + 1) == '#') ) {
                l = atol( p + 2 );
                strcat( temp, convUnicode( l ) );
                p = strchr( p + 2, ';' ) + 1;
            }
            else {
                l = temp[0] ? strlen( temp ) : 0;
                temp[l]     = *p;
                temp[l + 1] = NUL;
                p++;
            }
        }
        strcpy( src, temp );

        free( temp );
    }

    return ( src );
}


/* �Ǘ���ʑΘb�nblog�ł̃J�e�S��ID�擾 */
int
getCategoryIDfromStdin(
        int        *categoryID,  /* (I/O) �J�e�S��ID             */
        const char *htmlSrcCode, /* (I) �Ǘ����html�\�[�X�R�[�h */
        int        minimumID,    /* (I) �J�e�S��ID�ŏ��l         */
        const char *beginSelect, /* (I) <select>                 */
        const char *endSelect,   /* (I) </select>                */
        const char *beginOption, /* (I) <option>                 */
        const char *endOption,   /* (I) </option>                */
        int        charSet       /* (I) �����R�[�h               */
    )
{
    char    *p, *q, *r;
    char    buf[BUFSIZ];
    char    temp[MAX_CATNAMELENGTH];
    BOOL    done  = FALSE;
    int     defaultCatID = *categoryID;
    int     catID;
 // int     len11 = strlen( beginSelect );
    int     len12 = strlen( endSelect );
    int     len21 = strlen( beginOption );
    int     len22 = strlen( endOption );
    int     i = defaultCatID, numOfCategories;
    char    *categoryName;

    do {
        fputs( "\n�J�e�S��ID: \n", stderr );
        numOfCategories = 0;

        p = strstr( htmlSrcCode, beginSelect );
        if ( p ) {
            do {
                while ( *p &&
                        ((*p == '\r') || (*p == '\n') ||
                         (*p == ' ')  || (*p == '\t')    ) )
                    p++;
                if ( !(*p) || !strncmp( p, endSelect, len12 ) )
                    break;

                p = strstr( p, beginOption );
                if ( p ) {
                    p += len21;
                    catID = atol( p );
                    if ( catID >= minimumID ) {
                        q = strchr( p, '>' );
                        if ( q && *++q ) {
                            r = strchr( q, '<' );
                            if ( r ) {
                                strncpy( temp, q, r - q );
                                temp[r - q] = '\0';

                                switch ( charSet ) {
                                case CHARSET_EUCJP:
                                    categoryName = euc2sjis( temp );
                                    break;
                                case CHARSET_ISO2022JP:
                                    categoryName = jis2sjis( temp );
                                    break;
                                case CHARSET_UTF8:
                                    categoryName = utf2sjis( temp );
                                    break;
                                case CHARSET_SHIFTJIS:
                                default:
                                    categoryName = temp;
                                    break;
                                }

                                if ( categoryName )
                                    break;

                                fprintf( stderr, "\t[%d] %s\n",
                                         ++numOfCategories,
                                         categoryName );
                            }
                        }
                    }

                    p = strstr( p, endOption );
                    if ( p )
                        p += len22;
                }
                else
                    break;
            } while ( !done );

            if ( numOfCategories <= 1 ) {
                i = 1;
                if ( numOfCategories == 0 )
                    fputs( "\t0\n", stderr );
                break;
            }
        }
        else
            break;

        fprintf( stderr, "[1-%d]: �I�����Ă�������: ", numOfCategories );
        p = fgets( buf, BUFSIZ - 1, stdin );
        if ( !p ) {
            clearerr( stdin );
            continue;
        }

        while ( (*p == ' ') || (*p == '\t') )
            p++;
        q = p;
        while ( *q )
            q++;
        q--;
        while ( (q > p) &&
                ((*q == '\n') || (*q == '\r') ||
                 (*q == ' ')  || (*q == '\t')    ) ) {
            *q-- = '\0';
        }
        if ( p && *p && (q >= p) ) {
            i = atol( p );
            if ( (i > 0) && (i <= numOfCategories) )
                done = TRUE;
        }
    } while ( !done );

    *categoryID = i;

    return ( *categoryID );
}

char    *
getCategoryNameFromStdin(
        char       *catID,       /* (O) �J�e�S��ID (������)      */
        char       *categoryName,/* (I/O) �J�e�S����             */
        const char *htmlSrcCode, /* (I) �Ǘ����html�\�[�X�R�[�h */
        const char *beginSelect, /* (I) <select>                 */
        const char *endSelect,   /* (I) </select>                */
        const char *beginOption, /* (I) <option>                 */
        const char *endOption,   /* (I) </option>                */
        int        charSet       /* (I) �����R�[�h               */
    )
{
    char    *p, *q, *r;
    char    buf[BUFSIZ];
    char    temp[MAX_CATNAMELENGTH], *pp;
    BOOL    done  = FALSE;
 // int     len11 = strlen( beginSelect );
    int     len12 = strlen( endSelect );
    int     len21 = strlen( beginOption );
    int     len22 = strlen( endOption );
    int     i = 0, numOfCategories;

    do {
        fputs( "\n�J�e�S��ID: \n", stderr );
        numOfCategories = 0;

        p = strstr( htmlSrcCode, beginSelect );
        if ( p ) {
            p += strlen( beginSelect );
            do {
                while ( *p &&
                        ((*p == '\r') || (*p == '\n') ||
                         (*p == ' ')  || (*p == '\t')    ) )
                    p++;
                if ( !(*p) || !strncmp( p, endSelect, len12 ) )
                    break;

                p = strstr( p, beginOption );
                if ( p ) {
                    p += len21;
                    q = strchr( p, '>' );
                    if ( q && *++q ) {
                        r = strchr( q, '<' );
                        if ( r ) {
                            if ( r - q < MAX_CATNAMELENGTH - 1 ) {
                                strncpy( temp, q, r - q );
                                temp[r - q] = '\0';
                            }
                            else {
                                strncpy( temp, q, MAX_CATNAMELENGTH - 1 );
                                temp[MAX_CATNAMELENGTH - 1] = '\0';
                            }

                            switch ( charSet ) {
                            case CHARSET_EUCJP:
                                pp = euc2sjis( temp );
                                break;
                            case CHARSET_ISO2022JP:
                                pp = jis2sjis( temp );
                                break;
                            case CHARSET_UTF8:
                                pp = utf2sjis( temp );
                                break;
                            case CHARSET_SHIFTJIS:
                            default:
                                pp = temp;
                                break;
                            }

                            if ( pp )
                                break;

                            while ( (pp[strlen(pp) - 1] == '\r') ||
                                    (pp[strlen(pp) - 1] == '\n') ||
                                    (pp[strlen(pp) - 1] == '\t') ||
                                    (pp[strlen(pp) - 1] == ' ')     )
                                pp[strlen(pp) - 1] = NUL;

                            fprintf( stderr, "\t[%d] %s\n",
                                     ++numOfCategories,
                                     pp );
                        }
                    }

                    p = strstr( p, endOption );
                    if ( p )
                        p += len22;
                }
                else
                    break;
            } while ( !done );

            if ( numOfCategories <= 1 ) {
                if ( numOfCategories == 0 )
                    fputs( "\t0\n", stderr );
                break;
            }
        }
        else
            break;

        fprintf( stderr, "[1-%d]: �I�����Ă�������: ", numOfCategories );
        p = fgets( buf, BUFSIZ - 1, stdin );
        if ( !p ) {
            clearerr( stdin );
            continue;
        }

        while ( (*p == ' ') || (*p == '\t') )
            p++;
        q = p;
        while ( *q )
            q++;
        q--;
        while ( (q > p) &&
                ((*q == '\n') || (*q == '\r') ||
                 (*q == ' ')  || (*q == '\t')    ) ) {
            *q-- = '\0';
        }
        if ( p && *p && (q >= p) ) {
            i = atol( p );
            if ( (i > 0) && (i <= numOfCategories) )
                done = TRUE;
        }
    } while ( !done );

    if ( i > 0 ) {
        numOfCategories = 0;
        p = strstr( htmlSrcCode, beginSelect );
        if ( p ) {
            done = FALSE;
            p += strlen( beginSelect );
            do {
                while ( *p &&
                        ((*p == '\r') || (*p == '\n') ||
                         (*p == ' ')  || (*p == '\t')    ) )
                    p++;
                if ( !(*p) || !strncmp( p, endSelect, len12 ) )
                    break;

                p = strstr( p, beginOption );
                if ( p ) {
                    p += len21;
                    q = strchr( p, '>' );
                    r = strchr( p, '"' );
                    if ( r && q && (r < q) )
                        q = r;
                    if ( q && *++q ) {
                        if ( (q - 1) - p < MAX_CATIDLENGTH - 1 ) {
                            strncpy( catID, p, (q - 1) - p );
                            catID[(q - 1) - p] = NUL;
                        }
                        else {
                            strncpy( catID, p, MAX_CATIDLENGTH - 1 );
                            catID[MAX_CATIDLENGTH - 1] = NUL;
                        }

                        r = strchr( q, '<' );
                        if ( r ) {
                            strncpy( temp, q, r - q );
                            temp[r - q] = '\0';

                            switch ( charSet ) {
                            case CHARSET_EUCJP:
                                pp = euc2sjis( temp );
                                break;
                            case CHARSET_ISO2022JP:
                                pp = jis2sjis( temp );
                                break;
                            case CHARSET_UTF8:
                                pp = utf2sjis( temp );
                                break;
                            case CHARSET_SHIFTJIS:
                            default:
                                pp = temp;
                                break;
                            }

                            if ( pp )
                                break;

                            while ( (pp[strlen(pp) - 1] == '\r') ||
                                    (pp[strlen(pp) - 1] == '\n') ||
                                    (pp[strlen(pp) - 1] == '\t') ||
                                    (pp[strlen(pp) - 1] == ' ')     )
                                pp[strlen(pp) - 1] = NUL;

                            ++numOfCategories;
                            if ( numOfCategories == i ) {
                                strcpy( categoryName, pp );
                                done = TRUE;
                                break;
                            }
                        }
                    }

                    p = strstr( p, endOption );
                    if ( p )
                        p += len22;
                }
                else
                    break;
            } while ( !done );
        }
    }

    return ( categoryName );
}


int
getCategoryID( int        *categoryID,  /* (I/O) �J�e�S��ID             */
               const char *htmlSrcCode, /* (I) �Ǘ����html�\�[�X�R�[�h */
               int        minimumID,    /* (I) �J�e�S��ID�ŏ��l         */
               const char *beginSelect, /* (I) <select>                 */
               const char *endSelect,   /* (I) </select>                */
               const char *beginOption, /* (I) <option>                 */
               const char *endOption,   /* (I) </option>                */
               int        charSet       /* (I) �����R�[�h               */
             )
{
    int     defaultCatID = *categoryID;
    BOOL    found        = FALSE;

    if ( *categoryID == defaultCatID ) {
        /* �J�e�S���w��Ȃ��A�܂��̓f�t�H���g�J�e�S���w�� */
        getCategoryIDfromStdin( categoryID, htmlSrcCode, minimumID,
                                beginSelect, endSelect,
                                beginOption, endOption,
                                charSet );
    }

    if ( *categoryID >= defaultCatID ) {
        char    *p, *q, *r;
        int     catID, cnt = 0;
     // int     len11 = strlen( beginSelect );
        int     len12 = strlen( endSelect );
        int     len21 = strlen( beginOption );
        int     len22 = strlen( endOption );

        p = strstr( htmlSrcCode, beginSelect );
        if ( p ) {
            do {
                if ( !strncmp( p, endSelect, len12 ) )
                    break;

                p = strstr( p, beginOption );
                if ( p ) {
                    p += len21;

                    q = strchr( p, '>' );           /* for JUGEM */
                    r = strstr( p, "value=\"" );    /* for JUGEM */
                    if ( r && (r < q) )             /* for JUGEM */
                        p = r + 7;                  /* for JUGEM */

                    catID = atol( p );
                    if ( catID != defaultCatID )
                        cnt++;
                    if ( cnt == *categoryID ) {
                        *categoryID = catID;
                        found = TRUE;
                    }
                    else {
                        p = strstr( p, endOption );
                        if ( p )
                            p += len22;
                    }
                }
                else
                    break;
            } while ( !found );
        }
    }

    if ( !found )
        *categoryID = defaultCatID; /* �J�e�S���w��Ȃ� */

    return ( *categoryID );
}


int
getCategoryIDwithName(
        int        *categoryID,  /* (I/O) �J�e�S��ID             */
        char       *categoryName,/* (O)   �J�e�S����             */
        const char *htmlSrcCode, /* (I) �Ǘ����html�\�[�X�R�[�h */
        int        minimumID,    /* (I) �J�e�S��ID�ŏ��l         */
        const char *beginSelect, /* (I) <select>                 */
        const char *endSelect,   /* (I) </select>                */
        const char *beginOption, /* (I) <option>                 */
        const char *endOption,   /* (I) </option>                */
        int        charSet       /* (I) �����R�[�h               */
    )
{
    int     defaultCatID = *categoryID;
    BOOL    found        = FALSE;

    if ( *categoryID == defaultCatID ) {
        /* ������ */
        getCategoryIDfromStdin( categoryID, htmlSrcCode, minimumID,
                                beginSelect, endSelect,
                                beginOption, endOption,
                                charSet );
    }

    if ( *categoryID >= defaultCatID ) {
        char    *p, *q, *r;
        int     catID, cnt = 0;
     // int     len11 = strlen( beginSelect );
        int     len12 = strlen( endSelect );
        int     len21 = strlen( beginOption );
        int     len22 = strlen( endOption );

        p = strstr( htmlSrcCode, beginSelect );
        if ( p ) {
            do {
                if ( !strncmp( p, endSelect, len12 ) )
                    break;

                p = strstr( p, beginOption );
                if ( p ) {
                    p += len21;
                    catID = atol( p );
                    if ( catID != defaultCatID )
                        cnt++;
                    if ( cnt == *categoryID ) {
                        *categoryID = catID;
                        found = TRUE;
                        q = strchr( p, '>' );
                        if ( q && *++q ) {
                            r = strchr( q, '<' );
                            if ( r ) {
                                strncpy( categoryName, q, r - q );
                                categoryName[r - q] = '\0';
                            }
                        }
                    }
                    else {
                        p = strstr( p, endOption );
                        if ( p )
                            p += len22;
                    }
                }
                else
                    break;
            } while ( !found );
        }
    }

    if ( !found )
        *categoryName = NUL;

    return ( *categoryID );
}


char    *
getCategoryIDstring( 
        char       *catID,          /* (O) �J�e�S��ID (������)      */
        const char *htmlSrcCode,    /* (I) �Ǘ����html�\�[�X�R�[�h */
        const char *beginSelect,    /* (I) <select>                 */
        const char *endSelect,      /* (I) </select>                */
        const char *beginOption,    /* (I) <option>                 */
        const char *endOption,      /* (I) </option>                */
        int        charSet          /* (I) �����R�[�h               */
    )
{
    char    categoryName[128];

    getCategoryNameFromStdin( catID, categoryName, htmlSrcCode,
                              beginSelect, endSelect,
                              beginOption, endOption,
                              charSet );

    return ( catID );
}


/* �J�e�S���������ɃJ�e�S��ID���擾���� */
char    *
getCategoryIDbyName(
        char       *catID,          /* (O) �J�e�S��ID (������)      */
        const char *categoryName,   /* (I) �J�e�S���� (Shift_JIS)   */
        const char *htmlSrcCode,    /* (I) �Ǘ����html�\�[�X�R�[�h */
        const char *beginSelect,    /* (I) <select>                 */
        const char *endSelect,      /* (I) </select>                */
        const char *beginOption,    /* (I) <option>                 */
        const char *endOption,      /* (I) </option>                */
        int        charSet          /* (I) �����R�[�h               */
    )
{
    char    *p, *q, *r;
    char    temp[MAX_CATNAMELENGTH], *pp;
    char    value[MAX_CATNAMELENGTH];
    BOOL    done  = FALSE;
 // int     len11 = strlen( beginSelect );
    int     len12 = strlen( endSelect );
    int     len21 = strlen( beginOption );
    int     len22 = strlen( endOption );

    p = strstr( htmlSrcCode, beginSelect );
    if ( p ) {
        p += strlen( beginSelect );
        do {
            while ( *p &&
                    ((*p == '\r') || (*p == '\n') ||
                     (*p == ' ')  || (*p == '\t')    ) )
                p++;
            if ( !(*p) || !strncmp( p, endSelect, len12 ) )
                break;

            p = strstr( p, beginOption );
            if ( p ) {
                p += len21;
                q = strchr( p, '>' );
                if ( q && *++q ) {
                    r = strstr( p, "value=\"" );    /* for JUGEM */
                    if ( r && (r < q) )             /* for JUGEM */
                        p = r + 7;                  /* for JUGEM */
                    strncpy( value, p, (q - 1) - p );
                    value[(q - 1) - p] = NUL;
                    if ( value[strlen(value) - 1] == '"' )
                        value[strlen(value) - 1] = NUL;

                    r = strchr( q, '<' );
                    if ( r ) {
                        strncpy( temp, q, r - q );
                        temp[r - q] = '\0';

                        switch ( charSet ) {
                        case CHARSET_EUCJP:
                            pp = euc2sjis( temp );
                            break;
                        case CHARSET_ISO2022JP:
                            pp = jis2sjis( temp );
                            break;
                        case CHARSET_UTF8:
                            pp = utf2sjis( decodeNumericReference( temp ) );
                            break;
                        case CHARSET_SHIFTJIS:
                        default:
                            pp = temp;
                            break;
                        }

                        if ( pp )
                            break;

                        while ( (pp[strlen(pp) - 1] == '\r') ||
                                (pp[strlen(pp) - 1] == '\n') ||
                                (pp[strlen(pp) - 1] == '\t') ||
                                (pp[strlen(pp) - 1] == ' ')     )
                            pp[strlen(pp) - 1] = NUL;

                        if ( !strcmp( pp, categoryName ) ) {
                            strcpy( catID, value );
                            done = TRUE;
                            break;
                        }
                    }
                }

                p = strstr( p, endOption );
                if ( p )
                    p += len22;
            }
            else
                break;
        } while ( !done );
    }

    return ( catID );
}


/* �J�e�S���ꗗ�̎擾 */
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
    )
{
    int     numOfCats = 0;
    char    *p, *q, *r;
    char    temp[MAX_CATNAMELENGTH], *pp;
    BOOL    done  = FALSE;
 // int     len11 = strlen( beginSelect );
    int     len12 = strlen( endSelect );
    int     len21 = strlen( beginOption );
    int     len22 = strlen( endOption );

    p = strstr( htmlSrcCode, beginSelect );
    if ( p ) {
        p += strlen( beginSelect );
        do {
            while ( *p &&
                    ((*p == '\r') || (*p == '\n') ||
                     (*p == ' ')  || (*p == '\t')    ) )
                p++;
            if ( !(*p) || !strncmp( p, endSelect, len12 ) )
                break;
            if ( !(*p) != '<' ) {
                q = strchr( p, '<' );
                if ( q && (endSelect[0] == '<')      &&
                     !strncmp( q, endSelect, len12 )    )
                    break;
            }

            p = strstr( p, beginOption );
            if ( p ) {
                p += len21;
                q = strchr( p, '>' );
                if ( q && *++q ) {
                    r = strchr( q, '<' );
                    if ( r ) {
                        strncpy( temp, q, r - q );
                        temp[r - q] = '\0';

                        switch ( charSet ) {
                        case CHARSET_EUCJP:
                            pp = euc2sjis( temp );
                            break;
                        case CHARSET_ISO2022JP:
                            pp = jis2sjis( temp );
                            break;
                        case CHARSET_UTF8:
                            pp = utf2sjis( decodeNumericReference( temp ) );
                            break;
                        case CHARSET_SHIFTJIS:
                        default:
                            pp = temp;
                            break;
                        }

                        if ( pp )
                            break;

                        while ( (pp[strlen(pp) - 1] == '\r') ||
                                (pp[strlen(pp) - 1] == '\n') ||
                                (pp[strlen(pp) - 1] == '\t') ||
                                (pp[strlen(pp) - 1] == ' ')     )
                            pp[strlen(pp) - 1] = NUL;

                        sprintf( categories[numOfCats].categoryId, "%08d", numOfCats );
                        strcpy( categories[numOfCats].categoryName, pp );
                        numOfCats++;
                        if ( numOfCats >= *numOfCategories )
                            break;
                    }
                }

                p = strstr( p, endOption );
                if ( p )
                    p += len22;
            }
            else
                break;
        } while ( !done );
    }

    *numOfCategories = numOfCats;
    return ( numOfCats );
}
