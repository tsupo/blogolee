/*
 *  postArticle.c
 *      記事を blog に投稿するプログラム
 *      (「ここうさぎ」のソース cocousagi.c を流用、改造)
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
 * 1.23版
 * 
 * 30    09/05/28 18:41 Tsujimura543
 * (1) バグ修正 (Amazon API 関連処理でメモリ破壊)
 * (2) バッファオーバーラン対策を強化
 * 
 * 29    09/05/27 22:19 Tsujimura543
 * Amazon API および 楽天 API 関係をアップデート
 * (Amazon API の認証は未対応 → xmlRPC.dll 側の対応と同時に作業予定)
 * 
 * 28    09/05/27 19:42 Tsujimura543
 * getKeyword() を修正
 * 
 * 2     09/05/27 1:47 tsupo
 * 1.22版
 * 
 * 27    09/05/26 21:52 Tsujimura543
 * tumblr への投稿に対応
 * 
 * 1     09/05/14 3:47 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 26    09/03/24 18:58 Tsujimura543
 * Windows Live Spaces 拡張版 metaWeblog API 採用ブログの
 * 「カテゴリ指定」付き投稿に対応
 * 
 * 25    09/03/20 22:48 Tsujimura543
 * はてなダイアリー(の Atom API での投稿)に対応した
 * 
 * 24    09/03/16 20:49 Tsujimura543
 * ウェブリブログの XMLRPC API 対応作業開始
 * 
 * 23    08/09/10 23:01 Tsujimura543
 * loginExciteBlog(), postExciteBlog(), getCategoryListExciteBlog(),
 * getBlogIDsExciteBlog(), getCategoryIDwithName()
 * を xmlRPC.dll から移管
 * 
 * 22    08/09/10 21:41 Tsujimura543
 * loginEchoo(), postEchoo(), getCategoryListEchoo(),
 * getBlogIDsEchoo() を xmlRPC.dll から移管
 * 
 * 21    08/09/10 18:01 Tsujimura543
 * loginRakuten(), postRakuten(), getCategoryListRakuten(),
 * getBlogIDsRakuten(), getCategoryIDbyName(), getCategoryIDs()
 * を xmlRPC.dll から移管
 * 
 * 20    08/09/09 23:56 Tsujimura543
 * loginWebry(), postWebry(), getCategoryListWebry(), getBlogIDsWebry()
 * を xmlRPC.dll から移管
 * 
 * 19    08/09/09 22:49 Tsujimura543
 * loginMixi() と postMixi() を xmlRPC.dll から移管
 * 
 * 18    08/09/09 22:19 Tsujimura543
 * loginFC2NETWORK() と postFC2NETWORK() を xmlRPC.dll から移管
 * 
 * 17    08/09/09 21:42 Tsujimura543
 * loginKinugasa() と postKinugasa() を xmlRPC.dll から移管
 * 
 * 16    08/09/09 19:58 Tsujimura543
 * loginColors() と postColors() を xmlRPC.dll から移管
 * 
 * 15    08/02/18 23:11 Tsujimura543
 * copyright 表示をアップデート
 * 
 * 14    08/02/15 22:46 Tsujimura543
 * similaritySearch() を AWS3.0 ベースのものから ECS4.0 ベースへ移行
 * 
 * 13    07/11/30 2:01 Tsujimura543
 * Jugem、ヤプログ!、ドリコムブログ、しまにてぃ内日記向けの専用処理を廃止
 * 
 * 12    07/10/29 20:34 Tsujimura543
 * (1) XML-RPC API 経由での ヤプログ! へのアクセスに対応
 * (2) XML-RPC API 経由でのドリコムブログのカテゴリ一覧取得、カテゴリ設定
 *     に対応
 * 
 * 11    07/09/04 22:01 Tsujimura543
 * setVerbose() の第2引数追加に伴う変更
 * 
 * 10    07/03/13 21:16 Tsujimura543
 * 「おすすめ」商品の掲載件数を変えることができるようにした
 * (+ デフォルトの掲載件数を10件から4件に変更)
 * 
 * 9     07/03/12 18:36 Tsujimura543
 * utility.h をインクルードするようにした
 * 
 * 8     07/03/12 18:31 Tsujimura543
 * selectBlog() を導入し、リファクタリング
 * 
 * 7     07/03/12 5:08 Tsujimura543
 * (1) Visual Studio 2005 でもビルドできるようにコードを修正
 * (2) 一部のダイアログの文言を修正
 * 
 * 6     07/03/10 6:23 Tsujimura543
 * "--- powered by BloGolEe ---" に埋め込むリンク先を変更
 * 
 * 5     07/03/06 1:38 Tsujimura543
 * 「楽天」のおすすめ商品紹介機能を追加
 * 
 * 4     07/03/06 0:34 Tsujimura543
 * 「おすすめ」機能から「関連記事を列挙する」機能を削除
 * 
 * 3     07/03/05 22:27 Tsujimura543
 * setKeywordLink() の引数追加に伴う修正
 * 
 * 2     07/03/02 23:58 Tsujimura543
 * フィックス
 * 
 * 1     07/03/02 23:51 Tsujimura543
 * BloGolEe 暫定版 (動作確認済み)
 * 
 * ------------------------------------------------------------------------
 * 以下は、cocousagi.c の変更履歴
 * ------------------------------------------------------------------------
 * 170   07/02/24 2:05 Tsujimura543
 * JUGEM と ドリコムブログ の XML-RPC API 経由での投稿に対応
 * 
 * 169   07/02/14 21:45 Tsujimura543
 * 投稿リトライ処理を修正
 * 
 * 168   07/02/14 16:46 Tsujimura543
 * XML-RPC API および Atom API での投稿時のタイムアウト時間を
 * 長めにしてみる
 * 
 * 167   07/01/23 15:33 Tsujimura543
 * (1) 楽天ブログの新しい管理画面に対応
 * (2) 楽天ブログにカテゴリ指定して投稿できるようにした
 * 
 * 166   06/10/13 17:21 Tsujimura543
 * コメントを修正
 * 
 * 165   06/10/13 17:20 Tsujimura543
 * ウェブリブログに投稿する場合、「ここうさぎ」起動時のパラメータでテンプ
 * レートIDを指定しての投稿ができるようにした
 * 
 * 164   06/10/02 20:13 Tsujimura543
 * blog_info_tbl[] の実体を blogInfo.c へ分離
 * 
 * 163   06/10/02 20:01 Tsujimura543
 * COUSAGI_INFO の定義も cocousagi.h へ移動
 * 
 * 162   06/10/02 19:59 Tsujimura543
 * (1) cocousagi.c から JUGEM 特有の処理を分離し、jugem.c へ移譲
 * (2) 構造体の宣言、プロトタイプ宣言などを cocousagi.h へ分離
 * 
 * 161   06/10/02 19:50 Tsujimura543
 * cocousagi.c から exciteブログ 特有の処理を分離し、excite.c へ移譲
 * 
 * 160   06/10/02 19:34 Tsujimura543
 * cocousagi.c から ヤプログ! 特有の処理を分離し、yaplog.c へ移譲
 * 
 * 159   06/10/02 19:30 Tsujimura543
 * cocousagi.c から ドリコムブログ 特有の処理を分離し、drecom.c へ移譲
 * 
 * 158   06/10/02 19:22 Tsujimura543
 * cocousagi.c から mixi 特有の処理を分離し、mixi.c へ移譲
 * 
 * 157   06/10/02 19:18 Tsujimura543
 * cocousagi.c から キヌガサ 特有の処理を分離し、kinugasa.c へ移譲
 * 
 * 156   06/10/02 19:11 Tsujimura543
 * cocousagi.c から FC2NETWORK 特有の処理を分離し、fc2network.c へ移譲
 * 
 * 155   06/10/02 19:06 Tsujimura543
 * cocousagi.c から エコログ 特有の処理を分離し、echoo.c へ移譲
 * 
 * 154   06/10/02 19:01 Tsujimura543
 * cocousagi.c から ウェブリブログ 特有の処理を分離し、webry.c へ移譲
 * 
 * 153   06/10/02 18:54 Tsujimura543
 * cocousagi.c から 楽天ブログ 特有の処理を分離し、rakuten.c へ移譲
 * 
 * 152   06/10/02 18:39 Tsujimura543
 * cocousagi.c から COLORS 特有の処理を分離し、colors.c へ移譲
 * 
 * 151   06/10/02 18:28 Tsujimura543
 * cocousagi.c から OpenPNE 特有の処理を分離し、openPNE.c へ移譲
 * 
 * 150   06/10/02 18:20 Tsujimura543
 * cocousagi.c から しまにてぃ 特有の処理を分離、simanity.c へ移譲
 * 
 * 149   06/10/02 18:12 Tsujimura543
 * cocousagi.c から livedoor Blog 特有の処理を分離、livedoor.c へ移譲
 * 
 * 148   06/10/02 13:43 Tsujimura543
 * livedoor Blog の再構築処理を修正 (URL が想定しているものより長くなる
 * 場合があることが判明。URL の格納領域サイズを増やした)
 * 
 * 147   06/09/19 11:50 Tsujimura543
 * powered by cocousagi のリンク先を 3.00 版の配布ページの URL に変更
 * 
 * 146   06/09/15 21:17 Tsujimura543
 * OpenPNE / しまにてぃ への投稿時のタイトルの長さ調整処理をはずしてみた
 * 
 * 145   06/09/15 20:40 Tsujimura543
 * loginSimanity() の引数を減らした (日記を書くだけなら必要ないため)
 * 
 * 144   06/09/15 20:34 Tsujimura543
 * しまにてぃ に対応してみた
 * 
 * 143   06/09/15 20:07 Tsujimura543
 * OpenPNE に対応してみた
 * 
 * 142   06/09/14 19:49 Tsujimura543
 * Vox に対応してみた
 * 
 * 141   06/09/12 12:27 Tsujimura543
 * CP932 ではない文字が混入しているとの指摘(Visual Studio 2005)に基づき、
 * ソースコードの整理を実施
 * 
 * 140   06/09/11 18:28 Tsujimura543
 * 楽天広場 → 楽天ブログ
 * 
 * 139   06/09/08 21:51 Tsujimura543
 * MSN Spaces → Windows Live Spaces への名称変更に対応
 * 
 * 138   06/09/07 18:58 Tsujimura543
 * So-net blog の場合、Atom API 経由でのパスワード(のエンコード結果)が
 * 64バイトより大きくなることがあることが判明。パスワード格納領域のサイズ
 * を増やした
 * 
 * 137   06/09/06 17:06 Tsujimura543
 * アメーバブログの記事投稿時、タイトルが48文字より長いと投稿に失敗する
 * ことが判明。48文字より長い場合は、短いタイトルに差し替えるようにした
 * 
 * 136   06/09/04 14:35 Tsujimura543
 * COLORS への投稿時、記事タイトルが40バイトより長い場合は警告を
 * 出して終了していたのを、短いタイトルを生成して投稿するように変更
 * 
 * 135   06/09/04 13:33 Tsujimura543
 * バッファオーバーランを防止するため、setUpReceiveBuffer() を導入。
 * 
 * 134a  06/09/03 20:20 tsupo
 * (1) cookie まわりを修正
 * (2) Visuau Studio 2005 でビルドしたときに検出される warning を元に
 *     ソースを修正 (Visual Studio 6 でも Visual Studio 2005 でも。同
 *     一ソースのまま、問題なくビルドできるようにする)
 * 
 * 134   06/08/31 13:16 Tsujimura543
 * 強制代筆モードを実装
 * 
 * 133   06/08/29 21:19 Tsujimura543
 * 「記事生成」APIのみ復活とのことなので、「俳句生成」API関連の処理は
 * USE_HAIKU が #define されているときのみ有効という形にした
 * 
 * 132   06/07/26 16:36 Tsujimura543
 * ドリコムブログへ投稿する処理を修正
 * 
 * 131   06/05/31 15:04 Tsujimura543
 * 代理投稿時に必要に応じて <br /> を付加する処理を入れた
 * 
 * 130   06/05/30 13:21 Tsujimura543
 * autoMode 有効時の動作を修正 (必要に応じて<pre>～</pre>でbodyを
 * 囲むようにした)
 * 
 * 129   06/03/15 21:58 Tsujimura543
 * livedoor Blog のエンドポイント URL を ATOMURL_LIVEDOOR_200507 に固定
 * 
 * 128   06/03/09 19:28 Tsujimura543
 * マイプロフィール関連の処理を完全に削除
 * 
 * 127   06/03/09 19:20 Tsujimura543
 * cocousagi.c 自体は変更なし (xmlRPC.dll の変更のみ)
 * (1) 2006年3月1日の「ウェブリブログ」リニューアルに対応
 * (2) 2006年3月6日の「ヤプログ!」リニューアルに対応
 * (3) エコログの新しい login シーケンスに対応 (いつから変わったのかは不明)
 * 
 * 126   06/02/28 14:17 Tsujimura543
 * MSN Spaces に対応
 * 
 * 125   06/01/27 20:34 Tsujimura543
 * livedoor Blog の再構築処理を追加した
 * 
 * 124   06/01/26 14:51 Tsujimura543
 * アメーバブログの Atom API に暫定対応
 * 
 * 123   06/01/25 19:20 Tsujimura543
 * excite Blog のログイン処理、投稿処理を変更 (引数を追加)
 * 
 * 122   06/01/04 18:23 Tsujimura543
 * COLORS 向け投稿処理を fix
 * 
 * 121   05/12/27 20:26 Tsujimura543
 * 投稿失敗時は「投稿に失敗しました。」と表示するようにした
 * 
 * 120   05/12/27 19:21 Tsujimura543
 * COLORS のダイアリーにも投稿できるようにしてみた
 * 
 * 119   05/12/06 17:44 Tsujimura543
 * 代筆時のファイルのやりとりを w/r から w+t/r+b に変更(Windowsの場合)
 * [投稿結果に余分なゴミがつくことがある現象に対する対策]
 * 
 * 118   05/11/28 15:07 Tsujimura543
 * ココログフリーと goo Blog に対応
 * (ココログフリーは動作確認済み、goo Blog はアカウントを持っていないので
 * 動作確認はしていない)
 * 
 * 117   05/09/21 22:37 Tsujimura543
 * RSA復号結果格納領域の解放を free() から freeRSAbuffer() に変更
 * 
 * 116   05/09/21 11:37 Tsujimura543
 * 設定ファイル中のパスワードの暗号化に対応
 * 
 * 115   05/08/17 15:19 Tsujimura543
 * (1) postEntryOnAtomAPI() と editEntryOnAtomAPI() の引数追加に対応
 * (2) エディタ起動時のデフォルトの指定を notepad から notepad.exe にする
 * 
 * 114   05/08/11 14:02 Tsujimura543
 * isPostingOK() の連続投稿調査時の記事タイトルを utf2sjis() する処理で
 * NULL が返ってきたときに落ちてしまう不具合を修正
 * 
 * 113   05/08/10 16:04 Tsujimura543
 * lcc-win32 でもコンパイルできるように、ヘッダファイルのインクルード順序
 * を変更
 * 
 * 112   05/07/20 15:42 Tsujimura543
 * livedoor Blog の新旧エンドポイントURL使い分け関連処理を修正
 * 
 * 111   05/07/20 15:17 Tsujimura543
 * livedoor Blog の新エンドポイントURLで試してみて駄目なら、旧エンドポイン
 * トURLを使うようにしてみた
 * 
 * 110   05/07/19 18:56 Tsujimura543
 * So-net blog に対応
 * 
 * 109   05/07/13 18:43 Tsujimura543
 * アメーバブログの文字コードの変更に対応する作業に漏れがあったので、
 * 引き続き対応作業を実施した
 * 
 * 108   05/07/13 17:34 Tsujimura543
 * アメーバブログの文字コードの変更、RSS の URL の再変更に対応
 * 
 * 107   05/04/27 16:55 Tsujimura543
 * ココログで取得したカテゴリ名の文字化けが回復できない場合でも、
 * 「カテゴリ指定なし」で投稿できるようにした
 * 
 * 106   05/04/21 19:12 Tsujimura543
 * editForRakuten() を追加し、楽天広場では使えない属性を除去するようにした
 * 
 * 105   05/04/21 16:43 Tsujimura543
 * 楽天広場に対応。投稿できることを確認
 * 
 * 104   05/04/20 15:33 Tsujimura543
 * 代筆投稿時は「俳句を詠ませる Blog Pet API」を呼び出すのを抑制するように
 * した
 * 
 * 103   05/04/14 15:45 Tsujimura543
 * FC2BLOG に対応。投稿できることを確認
 * 
 * 102   05/04/05 10:27 Tsujimura543
 * アメーバブログの RSS の URL 変更に伴う修正
 * 
 * 101   05/04/01 21:06 Tsujimura543
 * 2.23 版
 * 
 * 100   05/04/01 21:04 Tsujimura543
 * (1) アメブロのリニューアル後、「ここうさぎウィザード」で指定したカテゴリ
 *     が反映されなくなってしまった不具合を修正
 * (2) ヤプログ! の login 手順変更に伴う xmlRPC.dll の修正の影響が他に及ば
 *     ないことを確認
 * 
 * 99    05/04/01 16:53 Tsujimura543
 * アメーバブログのリニューアルに伴う仕様変更(XML-RPC API の廃止、
 * 管理画面の変更)に対応
 * 
 * 98    05/03/29 15:02 Tsujimura543
 * FC2NETWORK 向け投稿処理での改行の扱いを調整
 * 
 * 97    05/03/29 14:58 Tsujimura543
 * FC2NETWORK 向け投稿処理を修正
 * 
 * 96    05/03/29 14:16 Tsujimura543
 * (1) Windows 98 で(Windows 95でも?)発生している現象(notepad を終了しない
 *     うちにどんどん処理が先に進んでいく)に対処
 * (2) FC2NETWORK内の日記に対応
 * 
 * 95    05/03/25 21:47 Tsujimura543
 * JUGEMの投稿処理を引数でカテゴリ名の指定をできるようにした
 * 
 * 94    05/03/25 20:48 Tsujimura543
 * exciteブログの投稿処理を引数でカテゴリ名の指定をできるようにした
 * 
 * 93    05/03/25 19:50 Tsujimura543
 * ヤプログの投稿処理を引数でカテゴリ名の指定をできるようにした
 * 
 * 92    05/03/25 19:17 Tsujimura543
 * エコログの投稿処理を引数でカテゴリ名の指定をできるようにした
 * 
 * 91    05/03/25 15:06 Tsujimura543
 * ウェブリブログの投稿処理を引数でカテゴリ名(テーマ名)の指定をできるよう
 * にした
 * 
 * 90    05/03/16 16:46 Tsujimura543
 * 指定したカテゴリに正しく投稿されないことがある不具合に対処
 * 
 * 89    05/03/14 19:26 Tsujimura543
 * 代筆機能を追加
 * 
 * 88    05/03/08 20:36 Tsujimura543
 * 「SweetBox Blog」に記述を統一
 * 
 * 87    05/03/08 17:06 Tsujimura543
 * SweetBox Blog に対応
 * 
 * 86    05/03/07 23:23 Tsujimura543
 * NetLaputa と 269g に対応
 * 
 * 85    05/02/21 22:53 Tsujimura543
 * アメーバブログとウェブリブログをアフィリエリト可能ブログとして扱うよう
 * に変更
 * 
 * 84    05/02/21 22:45 Tsujimura543
 * ヤプログとドリコムの記事末尾に埋め込む絵文字をペットの種類に合わせて
 * 変えるようにした
 * 
 * 83    05/02/21 14:31 Tsujimura543
 * アメーバブログでも NewsHandler 互換 XML-RPC API が使えることを確認。
 * 試験的に XML-RPC API を使って投稿する処理を適用してみた。
 * 
 * 82    05/02/21 13:37 Tsujimura543
 * Newshandler でも「連続投稿チェック」機能が働くようにした
 * 
 * 81    05/02/21 13:16 Tsujimura543
 * NewsHandler もいつの間にか MovableType 互換 API をサポートする
 * ようになっていたので、カテゴリ関連の処理を Movable Type 互換 API
 * 相当として扱うようにした
 * 
 * 80    05/02/18 20:53 Tsujimura543
 * 2.00 版
 * 
 * 79    05/02/18 17:43 Tsujimura543
 * 「こうさぎ」から「BlogPet」への移行に伴う修正の第3弾
 *   -C オプションを追加
 * 
 * 78    05/02/18 17:24 Tsujimura543
 * 「こうさぎ」から「BlogPet」への移行に伴う修正の第2弾
 *   投稿するカテゴリを BlogPet の種別に合わせて変えるようにした
 * 
 * 77    05/02/18 16:51 Tsujimura543
 * 「こうさぎ」から「BlogPet」への移行に伴う修正の第1弾
 *  (1) BlogPet の種別を選択・設定可能にした
 *  (2) 投稿記事の内容を BlogPet の種別に合わせて変えるようにした
 *  (3) 投稿記事に powered by cocousagi の文字列を埋め込むようにした
 * 
 * 76    04/11/29 19:10 Tsujimura543
 * 1.50 版
 * 
 * 75    04/11/29 19:03 Tsujimura543
 * マイプロフィール関連関数をコメントアウト
 * 
 * 74    04/11/29 18:44 Tsujimura543
 * Seesaa Blog への投稿(XML-RPC API リクエスト)を https で行なうようにした
 * 
 * 73    04/11/29 18:30 Tsujimura543
 * アマゾンのおすすめ商品関連処理を修正
 * 
 * 72    04/11/29 13:26 Tsujimura543
 * コンソール入力関連関数を分離、xmlRPC.dll へ移管
 * 
 * 71    04/11/29 11:42 Tsujimura543
 * blog 種別選択画面を 80x23 以内におさまるように修正 (blog種別増加に対応)
 * 
 * 70    04/11/26 22:15 Tsujimura543
 * ウェブリブログでは記事の題名が50バイトより大きいと失敗することが
 * 判明。対策を実施 (1.50 RC1 版)
 * 
 * 69    04/11/26 21:47 Tsujimura543
 * 不要になった変数を削除
 * 
 * 68    04/11/26 21:39 Tsujimura543
 * ウェブリブログに投稿できることを確認
 * 
 * 67    04/11/26 13:19 Tsujimura543
 * エコログに投稿できることを確認
 * 
 * 66    04/11/25 19:03 Tsujimura543
 * エコログ対応版 (動作未確認)
 * 
 * 65    04/11/17 19:19 Tsujimura543
 * 1.44版
 * 
 * 64    04/11/11 11:29 Tsujimura543
 * Windows 98 での動作確認終了 (1.43 正式版)
 * 
 * 63    04/11/10 11:03 Tsujimura543
 * Windows 98 環境だと、常に「関連書籍は見つかりませんでした」になってしま
 * う現象に暫定対処(根本的な原因は「ここうさぎウィザード」の方にあると思わ
 * れる)
 * (1.43 RC4 版)
 * 
 * 62    04/11/08 10:25 Tsujimura543
 * </dt>の挿入位置が間違っていたのを修正。
 * (1.43 RC3 版)
 * 
 * 61    04/11/05 17:55 Tsujimura543
 * ドリコムブログも「おすすめ」指定無視対象(アフィリエイト禁止)扱いにした
 * (1.43 RC2 版)
 * 
 * 60    04/11/05 15:33 Tsujimura543
 * (1) ヤプログ、ドリコムブログで記事本文が長いと投稿に失敗することが
 *     判明。対策を組み込む。 
 * (2) exciteブログを「おすすめ」指定無視対象にした
 *     (アフィリエイトが禁止されているため)
 * 
 * 59    04/11/04 18:12 Tsujimura543
 * いったん、fix (1.43 RC1 版)
 * 
 * 58    04/11/02 22:00 Tsujimura543
 * おもちゃも書籍も「おすすめ」が見つからない場合は、「すべての商品」で
 * 検索をかけるようにした
 * 
 * 57    04/11/02 20:47 Tsujimura543
 * アマゾンの「おもちゃ&ホビー」の検索に対応
 * 
 * 56    04/11/02 18:01 Tsujimura543
 * (1) 同一サイトに複数blogを開設している場合のblogID決定処理を修正
 * (2) MovableType API にて取得したカテゴリの数が0のときにアプリケーション
 *     エラーになる不具合に対処
 * 
 * 55    04/11/01 20:09 Tsujimura543
 * 警告レベル4での warning を 0 にする
 * 
 * 54    04/11/01 19:54 Tsujimura543
 * 『「こうさぎ」からのおすすめ』を試験的に実装
 * 
 * 53    04/10/27 15:34 Tsujimura543
 * -V オプションを追加
 * 
 * 52    04/10/27 15:03 Tsujimura543
 * 「こうさぎの機嫌が悪いとき」に余分にメモリ解放しようとしていたバグを
 * 修正
 * 
 * 51    04/10/15 16:26 Tsujimura543
 * アメーバブログの管理画面のバグ改修に伴い、リンク埋め込みを復活させた
 * [一般公開版 1.42]
 * 
 * 50    04/10/15 15:22 Tsujimura543
 * NewsHandler の場合のみ、投稿日時がおかしな値になる現象に対処
 * (サーバ側の不具合であるが、「ここうさぎ」側で暫定対処しておく)
 * 
 * 49    04/10/14 14:21 Tsujimura543
 * 投稿者のIDとblogのオーナーのIDが別IDの場合に対応 (JUGEMの場合)
 * 
 * 48    04/10/13 16:32 Tsujimura543
 * -u, -U オプションを追加
 * 
 * 47    04/10/12 13:48 Tsujimura543
 * title と body の領域サイズを増やし、確保する場所をスタックからヒープに
 * 変更
 * 
 * 46    04/10/08 20:29 Tsujimura543
 * キヌガサ内日記対応
 * 
 * 45    04/09/29 13:37 Tsujimura543
 * 一般公開版 1.41
 *   (カテゴリ選択関連バグFix [xmlRPC.dll のみ修正])
 * 
 * 44    04/09/28 17:40 Tsujimura543
 * マイプロフィールを処理対象外とする [一般公開版 1.40]
 * 
 * 43    04/09/28 16:40 Tsujimura543
 * ドリコムブログ対応
 * 
 * 42    04/09/28 15:22 Tsujimura543
 * アメーバブログ対応
 * 
 * 41    04/09/17 16:10 Tsujimura543
 * エラーメッセージを追加
 * 
 * 40    04/09/13 15:03 Tsujimura543
 * 投稿に成功したかどうか、メッセージを出すようにした (投稿には成功
 * しているがリビルドには失敗している場合もあるため、「たぶん、投稿
 * に成功した」という曖昧なメッセージにしている)
 * 
 * 39    04/09/07 13:44 Tsujimura543
 * 「login に失敗しました。」というエラーメッセージを追加。
 * 
 * 38    04/09/07 13:35 Tsujimura543
 * mixi の日記に対応 (投稿できることを確認済み)
 * 
 * 37    04/09/06 14:22 Tsujimura543
 * "<![CDATA[ "や "]]>" という文字列が俳句中に出現した場合、再度俳句を取得
 * し直すようにした(取得再試行は最大3回まで実行)
 * 
 * 36    04/09/03 15:53 Tsujimura543
 * 一般公開版 1.3.1
 * 
 * 35    04/09/03 15:37 Tsujimura543
 * 一般公開候補版 1.3.1 RC1
 *   マイプロフィールに対応 (実際に投稿できることを確認)
 * 
 * 34    04/09/02 20:12 Tsujimura543
 * キーワードリンクで文字化けが発生した場合は、キーワードリンクなしの
 * 記事を投稿するようにした (文字化け発生原因は現時点では不明)
 * 
 * [     04/08/31 22:34 Tsujimura543      ]
 * [一般公開版 1.2.5 xmlRPC.dll のみの修正]
 *
 * 33    04/08/31 16:37 Tsujimura543
 * 一般公開版 1.2.4
 * 
 * 32    04/08/31 16:36 Tsujimura543
 * 記事中にuserName相当の文字列が存在しない場合、ニックネーム置換処理で
 * 記事本文の先頭にゴミが付いてしまう不具合を修正(化けた状態で「はてな
 * キーワードリンク」APIを呼び出すと化ける範囲が記事全文に及んでしまう)
 * 
 * 31    04/08/31 14:40 Tsujimura543
 * 一般公開準備
 * 
 * 30    04/08/31 14:03 Tsujimura543
 * ニックネーム置換処理修正 (置き換え対象のuserNameが記事中に複数個
 * 存在すると記事本文の先頭の方がおかしくなってしまう不具合に対処)
 * 
 * 29    04/08/30 19:29 Tsujimura543
 * 一般公開版 (1.2.3)
 * (1) 連続投稿制限を外すオプションを追加
 * (2) 「blogユーザ名」を「指定したニックネーム」に置換する機能を追加
 * 
 * 28    04/08/30 18:30 Tsujimura543
 * (1) 1週間に1回しか投稿しないように制限するはすが、60週間に1回しか投稿
 *     しないようになっていたバグを修正
 * (2) getRecentPostTitlesViaRSS() を追加。JUGEM、exciteブログ、ヤプログも
 *     連続投稿制限できるようにしてみた
 * 
 * 27    04/08/27 18:26 Tsujimura543
 * 一般公開版 (1.2.1)
 *   ヤプログに対応 (実際に投稿できることを確認)
 * 
 * 26    04/08/27 11:28 Tsujimura543
 * exciteブログ対応 (実際に投稿できることを確認済み)
 * 
 * 25    04/08/27 9:29 Tsujimura543
 * blog種別が newPostOnly のときの処理を修正
 *   (対話形式での使用時に blog ID の入力をする処理が抜けていた)
 * 
 * 24    04/08/25 16:59 Tsujimura543
 * JUGEM に対応 (XML-RPC API も Atom API も使わず、独自手法にて対応)
 * 
 * 23    04/08/24 16:37 Tsujimura543
 * 一般公開版 (1.1.4)
 * 
 * 22    04/08/24 14:44 Tsujimura543
 * 設定ファイルで unsupported を指定した場合、強制的に「blogユーザ名」、
 * 「blog投稿用パスワード」をクリアするようにした
 * 
 * 21    04/08/24 14:20 Tsujimura543
 * コメント修正、追加
 * 
 * 20    04/08/24 14:16 Tsujimura543
 * Blog種別に unsupported を追加
 * 
 * 19    04/08/24 11:24 Tsujimura543
 * 設定情報を静的に確保するのをやめ、動的に確保するようにした
 * 
 * 18    04/08/24 11:11 Tsujimura543
 * 設定ファイルで keywordLink: on と書いても、キーワードリンクが埋め込ま
 * れない不具合を修正
 * 
 * 17    04/08/20 16:52 Tsujimura543
 * 投稿先 blog が localhost 内に存在する場合に対応
 * 
 * 16    04/08/19 13:46 Tsujimura543
 * 一般公開版 (1.1.3)
 *   Windows 95 系の場合のキー入力処理を改善
 * 
 * 15    04/08/19 10:46 Tsujimura543
 * 一般公開版 (1.1.2) ← 結局、公開せず
 * 
 * 14    04/08/19 9:31 Tsujimura543
 * News-Handler および metaWeblog.newPost のみサポートしている blog
 * (「こうさぎ飼育箱」を含む)に対応
 * 
 * 13    04/08/19 8:52 Tsujimura543
 * blog_info_tbl[] に atomAPI を追加するのを忘れていた (→ 追加済み)
 * 
 * 12    04/08/17 18:50 Tsujimura543
 * コメントの誤字修正
 * 
 * 11    04/08/17 17:03 Tsujimura543
 * 一般公開版 (1.1.1)
 * 
 * 10    04/08/17 14:40 Tsujimura543
 * リファクタリングを実施
 * 
 * 9     04/08/17 12:25 Tsujimura543
 * blogger API, metaWeblog API のみサポートの blog への対応完了(動作は未確認)
 * 
 * 8     04/08/16 19:09 Tsujimura543
 * blogger API のみサポートしている blog、metaWeblog API のみサポートして
 * いる blog への対応を追加
 * 
 * 7     04/08/13 15:06 Tsujimura543
 * Atom API 経由での投稿でも「連続投稿抑止機能」が働くようにした
 * 
 * 6     04/08/13 13:55 Tsujimura543
 * 俳句詠唱の要否、キーワードリンク埋設の要否を対話型モードでも
 * 選択できるようにした
 * 
 * 5     04/08/13 10:56 Tsujimura543
 * (1) Movable Type への投稿動作確認完了
 * (2) 対話型でのパラメータ入力による動作確認完了
 * 
 * 4     04/08/13 9:48 Tsujimura543
 * Seesaa BLOG にて動作確認
 *  (投稿処理に時間がかかるようなので、タイムアウト時間の見直しが必要)
 * 
 * 3     04/08/12 21:18 Tsujimura543
 * ココログ以外にも対応(とりあえず、livedoor Blog にて動作確認成功)
 * 
 * 2     04/07/07 11:37 Tsujimura543
 * 一般公開版 (1.0.1)
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
 *  キーワード抽出
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
    const char  *kana1  = "ァ";
    const char  *kana2  = "ヶ";
    const char  *kana3  = "ー";
    const char  *kanji1 = "亜";
    const char  *p = body;
    int         found    = 0;
    int         kanji    = 0;
    int         yokomoji = 0;
    int         idiom    = 0;

    /*
     *  漢字のみが3文字以上連続する場合、またはカタカナのみが4文字以上連続
     *  する場合、キーワードとみなして抽出する
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
        strcpy( keyword, "ブログ" );

    return ( keyword );
}


#define MAX_TITLE_LEN   512
#define MAX_BODY_LEN    (MAX_CONTENT_SIZE * 16)
#define MAX_POSTID_LEN  MAX_POSTIDLENGTH
#define MAX_HAIKU_LEN   1024
#define MAX_PROMPT_LEN  80

#define MAX_CATS        32  /* 同一blog内カテゴリ最大数 (暫定値)           */
#define MAX_USERS       20  /* 同一blog内最大ユーザ数   (暫定値)           */
#define MAX_BLOGS       10  /* 同一システム内最大設置可能blog数 (ココログ) */
#define RECENT_ENTRIES  15  /* 連続投稿抑止チェックに使う記事の取得数      */


/*
 *  blog ID の取得・設定
 */

void
setBlogID( char *blogID, BLOGKIND blogType )
{
    if ( !(blogID[0]) ) {
        // CBlogoleeDlg::OnExecutePostArticle() 実行時点で blogID は確定済みなので、
        // 以下の処理が実行されることはない(が、コードは残しておく)
        BLOGINF blogInfo[MAX_BLOGS];
        char    prompt[MAX_PROMPT_LEN];
        char    buf[BUFSIZ];
        int     numOfBlogs = MAX_BLOGS;
        int     r, i;

        /* --- 投稿可能な blog 一覧の取得 */
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
            strcpy( (char *)blogID, blogInfo[0].blogID );/* 確定 */
        else if ( r > 1 ) {
            /* ---- 投稿先 blog の選択 */
            if ( isatty( fileno( stdin ) ) ) {
                do {
                    for ( i = 0; i < r; i++ ) {
                        printf( "(%d)\t%s (blogID: %s)\n",
                                i + 1,
                                utf2sjis( blogInfo[i].blogName ),
                                blogInfo[i].blogID );
                    }
                    sprintf( prompt, "どの blog に投稿しますか? (1 - %d): ", r );
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
        const char *body,   /* (I) 記事本文                              */
        int        mode,    /* (I) 埋め込みモード [1: 画像, 2: テキスト] */
        int        numOfRecomended  /* (I) おすすめ商品掲載件数          */
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

    /* 関連記事検索 (bulkfeeds を利用) */
    getKeyword( body, keyword ); /* 記事本文からキーワードを抽出 */
#ifdef  _DEBUG
    if ( isatty( fileno( stderr ) ) )
        fprintf( stderr, "キーワード: %s\n", keyword );
#endif

    /* 関連商品検索 (Amazon Web Services を利用) */
    ap = (AMAZON_LITE *)malloc( sizeof ( AMAZON_LITE ) * numOfAmazon );
    if ( ap ) {
        char    *searchTitle = "";
        int     searchMode   = AMAZON_MODE_TOYS;

        /* まず、「おもちゃ&ホビー」で検索 */
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
            /* ヒット数0なら、改めて「和書」で検索 */
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
            /* ヒット数0なら、今度は「すべての商品」で検索 */
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
            /* ヒット数0なら、最後は「和書-こども向け」のベストセラーを取得 */
            numOfAmazon = numOfRecomended;
            searchMode  = AMAZON_MODE_JBOOKS;
            searchTitle = "こども向け書籍ベストセラー";
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
                         "“%s”関連書籍は見つかりませんでした。\n", keyword);
            else {
                char    buf[BUFSIZ];
                sprintf( buf,
                         "「%s」に関連する書籍は見つかりませんでした。    ",
                         keyword );
                MessageBox( NULL, buf,
                            "Amazon Web サービス", MB_OK|MB_ICONWARNING );
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
                                 "%sおすすめ商品 ("
                                 "<strong>%s</strong>)%s",
                                 mode == 1 ? "<p>" : "<dl><dt>",
                                 searchTitle,
                                 mode == 1 ? "</p>\n<p>" : "</dt>\n" );
                    else
                        sprintf( sim + len,
                                 "<hr />"
                                 "%sおすすめ商品 ("
                                 "<strong>“%s”に関連する%sの一覧</strong>)"
                                 "%s",
                                 mode == 1 ? "<p>" : "<dl><dt>",
                                 keyword,
                                 searchMode == AMAZON_MODE_TOYS
                                    ? "おもちゃ"
                                    :
                                 searchMode == AMAZON_MODE_BLENDED
                                    ? "商品"
                                    : "書籍",
                                 mode == 1 ? "</p>\n<p>" : "</dt>\n" );
                }

                switch ( mode ) {
                case 1:
                    /* 画像埋め込み */
                    sprintf( sim + strlen( sim ),
                             "<a href=\"%s\">"
                             "<img src=\"%s\" alt=\"%s\" border=\"0\" />"
                             "</a>\n",
                             ap[i].url, ap[i].imageURLmedium, pp );
                    break;

                case 2:
                default:
                    /* テキスト埋め込み */
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
                        break;/* 暫定(yaplogは2000文字までしか投稿できない) */
            }

            if ( n > 1 ) {
                switch ( mode ) {
                case 1:
                    /* 画像埋め込み */
                    strcat( sim, "</p>\n" );
                    break;

                case 2:
                default:
                    /* テキスト埋め込み */
                    strcat( sim, "</dl>\n" );
                    break;
                }
            }
        }

        free( ap );
    }

    /* 関連商品検索 (楽天Webサービスを利用) */
    memset( &rrp,  0x00, sizeof (RAKUTEN_API_REQUEST)  );
    strcpy( rrp.keyword, keyword );
    rrp.hits = numOfRakuten;
    rp = itemSearchOnRakutenWebAPIex( &rrp );
    if ( rp ) {
        if ( rp->numOfItems <= 0 ) {
            if ( isatty( fileno( stderr ) ) )
                fprintf( stderr,
                         "“%s”関連商品は見つかりませんでした。\n",
                         keyword );
            else {
                char    buf[BUFSIZ];
                sprintf( buf, "「%s」に関連する商品は見つかりませんでした。    ",
                         keyword );
                MessageBox( NULL, buf,
                            "楽天Webサービス", MB_OK|MB_ICONWARNING );
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
                printf( "\t%s %d円\n", rp->item[i].itemCode,
                        rp->item[i].itemPrice );
                printf( "\t%f\n", rp->item[i].affiliateRate );
                printf( "\t%d / %f\n", rp->item[i].reviewCount,
                        rp->item[i].reviewAverage );
                */

                if ( m == 1 ) {
                    sprintf( sim + len,
                             "<hr />"
                             "%sおすすめ商品 ("
                             "<strong>“%s”に関連する商品の一覧</strong>)"
                             "%s",
                             mode == 1 ? "<p>" : "<dl><dt>",
                             keyword,
                             mode == 1 ? "</p>\n<p>" : "</dt>\n" );
                }

                switch ( mode ) {
                case 1:
                    /* 画像埋め込み */
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
                    /* テキスト埋め込み */
                    sprintf( sim + strlen( sim ),
                             "<dd><a href=\"%s\">%s</a></dd>\n",
                             rp->item[i].affiliateUrl,
                             rp->item[i].itemName );
                    break;
                }

                m++;

                if ( mode == 2 )
                    if ( (n + m) >= 4 )
                        break;/* 暫定(yaplogは2000文字までしか投稿できない) */
            }

            if ( m > 1 ) {
                switch ( mode ) {
                case 1:
                    /* 画像埋め込み */
                    strcat( sim, "</p>\n" );
                    break;

                case 2:
                default:
                    /* テキスト埋め込み */
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
 *  投稿記事加工
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
        /* キーワードリンク埋め込み */
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
                    /* 文字化け検出                       */
                    /*  → キーワードリンク埋め込みを中止 */
                    if ( isatty( fileno( stderr ) ) )
                        fputs( "「はてなキーワードリンク」で文字化け発生し"
                               "ました!!\n"
                               "キーワードリンクの埋め込みを中止します。\n",
                               stderr );
                    else
                        MessageBox( NULL,
                                    "「はてなキーワードリンク」で文字化け発"
                                    "生しました!!    \nキーワードリンクの埋"
                                    "め込みを中止します。\n",
                                    "「はてなキーワードリンク」でエラー",
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
                /* はてなダイアリーキーワード自動リンクAPIが */
                /* 機能していない場合                        */
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
                fprintf( stderr, "結果: %s\n", body );
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
 *  Atom API 系投稿処理
 */

int
postArticleOnAtomAPI(
        const char *blogID,       /* 投稿先 blog ID     */
        BLOGKIND   blogType,      /* blog 種別          */
        const char *title,        /* 投稿記事題名       */
        const char *body,         /* 投稿記事本文       */
        const char *description,  /* 投稿記事概要       */
        const char *catName       /* 投稿対象カテゴリ名 */
     //,char       *endpointURL   /* エンドポイントURL  */
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

    /* categoryId を取得 */
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

    /* 投稿 */
    content = (char *)malloc( (MAX_BODY_LEN * 3) / 2 );
    subject = (char *)malloc( strlen( title ) * 18 + BUFSIZ + 1 );
    strcpy( subject, sjis2utf( title ) );

    if ( blogType == ameblo ) {
        if ( strlen( subject ) >= 48 * 2 ) {
            /* アメーバブログでは、記事のタイトルは 48文字以内 */
            /*     (48文字より長いと投稿に失敗する)            */
            strcpy( subject, 
                    sjis2utf( "今日の日記" ) );
        }
    }
    if ( blogType == vox ) {
        if ( strlen( subject ) >= 80 ) {
            /* vox では、記事のタイトルは 80バイト以内              */
            /*     (80文字より長いとあふれた部分は捨てられてしまう) */
            strcpy( subject, 
                    sjis2utf( "今日の日記" ) );
        }
    }

    if ( description && *description )
        strcpy( summary, sjis2utf(description) );
    else
        strcpy( summary,
                sjis2utf(
                    "この記事は「ブログクライアント BloGolEe」"
                    "による投稿です。" ) );
    strcpy( content, sjis2utf( body ) );

    setTimeoutTime( DEFAULT_HTTP_TIMEOUT * 4 );
    bRet = postEntryOnAtomAPI( NULL, NULL, blogID, 
                               subject,  /* 題名           */
                               summary,  /* 概要           */
                               content,  /* 本文           */
                               &catEx,   /* カテゴリ       */
                               TRUE,     /* 投稿状態       */
                               postID    /* 投稿後の記事ID */
                             );
    setTimeoutTime( DEFAULT_HTTP_TIMEOUT );

    free( subject );
    free( content );

    ret = (bRet == TRUE) ? 1 : 0;

    return ( ret );
}


int
postArticleOnXMLRPC( const char *blogID,        /* 投稿先 blog ID     */
                     BLOGKIND   blogType,       /* blog 種別          */
                     const char *title,         /* 投稿記事題名       */
                     const char *body,          /* 投稿記事本文       */
                     const char *extended,      /* 投稿記事追記       */
                     const char *description,   /* 投稿記事概要       */
                     const char *keyword,       /* 投稿記事キーワード */
                     const char *catName )      /* 投稿対象カテゴリ名 */
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
         // 注意: msnSpaces, webryX は categoryId ではなく「カテゴリ名」を使う
         (blogType != jugemX)      &&
         (blogType != drecomX)     &&
         (blogType != yaplogX)     &&
         (blogType != newPostOnly)    ) {
        /* --指定カテゴリの categoryId を取得 */
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

    /* -- 投稿 */
    if ( blogType == newsHandler ) {
        /* News-Handler の場合、投稿日時を明示しないと、変な投稿日時になっ */
        /* てしまうことがあるため、特別に対策を施す (本来は、サーバの現在  */
        /* 時刻が投稿日時になるはず)                                       */
        time_t      t = time( NULL );
        struct tm   *tm = gmtime( &t ); /* グリニッジ標準時 */
        sprintf( content.dateCreated,
                 "%04d%02d%02d %02d:%02d:%02d",
                 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                 tm->tm_hour, tm->tm_min, tm->tm_sec );
        /* 備考: yyyy-mm-ddThh:mm:ss や yyyy-mm-ddThh:mm:ssZ の形式だと変な */
        /*       投稿日時(1年前とか)になる。 yyyymmdd hh:mm:ss 形式だとうま */
        /*       くいくことが判明。                                         */
        /*       明らかにサーバ側の不具合だと思われるが、いつ修正されるかわ */
        /*       からないので、とりあえず、クライアント側で対処しておく     */
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
                    "この記事は「ブログクライアント BloGolEe」"
                    "による投稿です。" ) );
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
            /* -- カテゴリ設定 */
            content.numOfCategories = 1;
            strcpy( content.categories[0], catName );
            // 今のところ、カテゴリ指定は1個だけ (暫定)
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
            /* -- カテゴリ設定 */
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
         //         /* → blogType == metaWeblog のときは、 */
         //         /*    found == FALSE なので、ここに来る */
         //         /*    ことはあり得ない                  */
         //     /* metaWeblog API はサポートしているが Movable Type 互換 */
         //     /* API はサポートしていない blog の場合                  */
         //     editPostEx( postID, NULL, NULL, &content, 1 );
         // }
         // else {
                /* Movable Type 互換 API サポート blog の場合 */
                retry = 5;
                do {
                    retry--;
                    if ( retry < 0 )
                        break;
                    Sleep( 2500 );
                    ret = publishPost(postID,NULL,NULL);/* Movable Type API */
                        /* 注意: この関数の実行中にタイムアウトが発生した場 */
                        /*       合はカテゴリが反映されていない可能性が高い */
                } while ( ret == FALSE );
         // }
        }
    }
    setTimeoutTime( DEFAULT_HTTP_TIMEOUT );

    ret = (bRet == TRUE) ? 1 : 0;

    return ( ret );
}


/*
 *  記事を blog に投稿する
 */

BOOL
postArticle(
        const ARTICLE_INFO *article,
        const POST_INFO    *postInfo
    )
{
    BOOL    b   = FALSE;
    int     ret = 0;

    /* 準備 */
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

        /* -- 投稿先 blog ID の確定 */
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

        /* 投稿 */
        if ( postInfo->blogType == exciteBlog )
            return ( postArticleOnExcite( postInfo->blogUserName,
                                          postInfo->blogPassword,
                                          article->title, article->body,
                                          article->extended,
                                          postInfo->categoryName ) );
                            /* exciteブログ専用投稿処理 */
        if ( postInfo->blogType == mixi )
            return ( postArticleOnMixi( postInfo->blogUserName,
                                        postInfo->blogPassword,
                                        article->title, article->body ) );
                            /* mixi専用投稿処理 */
        if ( postInfo->blogType == kinugasa )
            return ( postArticleOnKinugasa( postInfo->blogUserName,
                                            postInfo->blogPassword,
                                            article->title, article->body ) );
                            /* キヌガサ専用投稿処理 */
        if ( postInfo->blogType == echoo )
            return ( postArticleOnEchoo( postInfo->blogUserName,
                                         postInfo->blogPassword,
                                         article->title, article->body,
                                         postInfo->categoryName ) );
                            /* エコログ専用投稿処理 */
        if ( postInfo->blogType == fc2network )
            return ( postArticleOnFC2NETWORK( postInfo->blogUserName,
                                              postInfo->blogPassword,
                                              article->title,
                                              article->body ) );
                            /* FC2NETWORK専用投稿処理 */
        if ( postInfo->blogType == rakuten )
            return ( postArticleOnRakuten( postInfo->blogUserName,
                                           postInfo->blogPassword,
                                           article->title, article->body,
                                           postInfo->categoryName ) );
                            /* 楽天広場専用投稿処理 */
        if ( postInfo->blogType == colors )
            return ( postArticleOnColors( postInfo->blogUserName,
                                          postInfo->blogPassword,
                                          article->title, article->body ) );
                            /* COLORS専用投稿処理 */
        if ( postInfo->blogType == openPne )
            return ( postArticleOnOpenPNE( postInfo->blogUserName,
                                           postInfo->blogPassword,
                                           article->title, article->body ) );
                            /* OpenPNE専用投稿処理 */

        if ( postInfo->blogType == tumblr )
            return ( postArticleOnTumblr( postInfo->blogUserName,
                                          postInfo->blogPassword,
                                          postInfo->blogID[0]
                                            ? postInfo->blogID
                                            : postInfo->blogURL,
                                          article->title, article->body ) );
                            /* Tumblr専用投稿処理 */

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
                    /* livedoor Blog のみの特別な処理 */
                    BOOL    yesNo = NO;

                    if ( isatty( fileno( stderr ) ) ) {
                        fputs( "記事を投稿しました。\n", stderr );
                        inputYesNo( &yesNo, "blog を再構築しますか?" );
                    }
                    else {
                        int r = MessageBox( NULL,
                                            "記事を投稿しました。\n"
                                            "blog を再構築しますか?    ",
                                            "livedoor Blog",
                                            MB_YESNO|MB_ICONINFORMATION );
                        if ( r == IDYES )
                            yesNo = YES;
                    }
                    if ( yesNo == YES ) {
                        /* (blog の管理画面経由で)強制的に再構築する */
                        rebuildOnLivedoor( postInfo->blogUserName,
                                           postInfo->blogPassword,
                                           postInfo->blogID );
                    }
                }
                return ( b );
                            /* Atom API 系投稿処理 */
            }
            else
                return ( postArticleOnXMLRPC( postInfo->blogID,
                                              postInfo->blogType,
                                              article->title, article->body,
                                              article->extended,
                                              article->summary,
                                              article->keyword,
                                              postInfo->categoryName ) );
                            /* XML-RPC API 系投稿処理 */
        }
    }

    if ( isatty( fileno( stdout ) ) ) {
        /* 標準出力へ書き出し */
        printf( "題名: %s\n", utf2sjis( article->title ) );
        printf( "本文: %s\n", article->body );
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
 *  ユーティリティ関数群
 */

/* Unicode(UCS-2BE) (%uXXXX or &#XXXXX;) → UTF-8 (xxyyzz) 変換 */
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


/* 管理画面対話系blogでのカテゴリID取得 */
int
getCategoryIDfromStdin(
        int        *categoryID,  /* (I/O) カテゴリID             */
        const char *htmlSrcCode, /* (I) 管理画面htmlソースコード */
        int        minimumID,    /* (I) カテゴリID最小値         */
        const char *beginSelect, /* (I) <select>                 */
        const char *endSelect,   /* (I) </select>                */
        const char *beginOption, /* (I) <option>                 */
        const char *endOption,   /* (I) </option>                */
        int        charSet       /* (I) 文字コード               */
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
        fputs( "\nカテゴリID: \n", stderr );
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

        fprintf( stderr, "[1-%d]: 選択してください: ", numOfCategories );
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
        char       *catID,       /* (O) カテゴリID (文字列)      */
        char       *categoryName,/* (I/O) カテゴリ名             */
        const char *htmlSrcCode, /* (I) 管理画面htmlソースコード */
        const char *beginSelect, /* (I) <select>                 */
        const char *endSelect,   /* (I) </select>                */
        const char *beginOption, /* (I) <option>                 */
        const char *endOption,   /* (I) </option>                */
        int        charSet       /* (I) 文字コード               */
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
        fputs( "\nカテゴリID: \n", stderr );
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

        fprintf( stderr, "[1-%d]: 選択してください: ", numOfCategories );
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
getCategoryID( int        *categoryID,  /* (I/O) カテゴリID             */
               const char *htmlSrcCode, /* (I) 管理画面htmlソースコード */
               int        minimumID,    /* (I) カテゴリID最小値         */
               const char *beginSelect, /* (I) <select>                 */
               const char *endSelect,   /* (I) </select>                */
               const char *beginOption, /* (I) <option>                 */
               const char *endOption,   /* (I) </option>                */
               int        charSet       /* (I) 文字コード               */
             )
{
    int     defaultCatID = *categoryID;
    BOOL    found        = FALSE;

    if ( *categoryID == defaultCatID ) {
        /* カテゴリ指定なし、またはデフォルトカテゴリ指定 */
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
        *categoryID = defaultCatID; /* カテゴリ指定なし */

    return ( *categoryID );
}


int
getCategoryIDwithName(
        int        *categoryID,  /* (I/O) カテゴリID             */
        char       *categoryName,/* (O)   カテゴリ名             */
        const char *htmlSrcCode, /* (I) 管理画面htmlソースコード */
        int        minimumID,    /* (I) カテゴリID最小値         */
        const char *beginSelect, /* (I) <select>                 */
        const char *endSelect,   /* (I) </select>                */
        const char *beginOption, /* (I) <option>                 */
        const char *endOption,   /* (I) </option>                */
        int        charSet       /* (I) 文字コード               */
    )
{
    int     defaultCatID = *categoryID;
    BOOL    found        = FALSE;

    if ( *categoryID == defaultCatID ) {
        /* 未分類 */
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
        char       *catID,          /* (O) カテゴリID (文字列)      */
        const char *htmlSrcCode,    /* (I) 管理画面htmlソースコード */
        const char *beginSelect,    /* (I) <select>                 */
        const char *endSelect,      /* (I) </select>                */
        const char *beginOption,    /* (I) <option>                 */
        const char *endOption,      /* (I) </option>                */
        int        charSet          /* (I) 文字コード               */
    )
{
    char    categoryName[128];

    getCategoryNameFromStdin( catID, categoryName, htmlSrcCode,
                              beginSelect, endSelect,
                              beginOption, endOption,
                              charSet );

    return ( catID );
}


/* カテゴリ名を元にカテゴリIDを取得する */
char    *
getCategoryIDbyName(
        char       *catID,          /* (O) カテゴリID (文字列)      */
        const char *categoryName,   /* (I) カテゴリ名 (Shift_JIS)   */
        const char *htmlSrcCode,    /* (I) 管理画面htmlソースコード */
        const char *beginSelect,    /* (I) <select>                 */
        const char *endSelect,      /* (I) </select>                */
        const char *beginOption,    /* (I) <option>                 */
        const char *endOption,      /* (I) </option>                */
        int        charSet          /* (I) 文字コード               */
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


/* カテゴリ一覧の取得 */
int
getCategoryIDs(
        long         *numOfCategories,  /* (I) 取得するカテゴリの数     */
                                        /* (O) 取得したカテゴリの数     */
        CATLISTINF_t categories,        /* (O) 取得したカテゴリ情報     */
        const char   *htmlSrcCode,      /* (I) 管理画面htmlソースコード */
        const char   *beginSelect,      /* (I) <select>                 */
        const char   *endSelect,        /* (I) </select>                */
        const char   *beginOption,      /* (I) <option>                 */
        const char   *endOption,        /* (I) </option>                */
        int          charSet            /* (I) 文字コード               */
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
