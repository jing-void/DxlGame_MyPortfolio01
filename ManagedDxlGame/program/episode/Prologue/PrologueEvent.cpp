#include <string>
#include <time.h>
#include <iostream>
#include <regex>
#include "../dxlib_ext/dxlib_ext.h"
#include "DxLib.h"
#include "PrologueEvent.h"
#include "../../../program/game/Main.h"
#include "../map/FieldMap.h"

struct FuncBtnsInfo {
	int handle;
	float x;
	float y;
	int width;
	int height;
	float normalSize;
	float zoomSize;
};

std::vector<FuncBtnsInfo> btnInfos;


struct PlayerFaceChange {
	int handle;
	int x;
	int y;
};


// prototype
void SetPlayersName();
void ZoomBtnsOnMouseOver(const FuncBtnsInfo&);
void AddClickFuncOnBtns(const FuncBtnsInfo& btnInfos);
void DrawFuncBtns();
void DrawPlayersFace(int expression);
void DrawWholePlayer();
void DrawGoddess(int goddessFace);
void DrawGirl(int girlFace);


//---------------------------------------------------------------
int currentMessLine = 0;
int pointerArrow = LoadGraph("graphics/pointArrow.png");
float timeCount = 0;
float autoTimer = 0.0f;

std::string drawMess;
bool isStillTalking = true;
bool input_done = false;
bool inputCharName = false;
bool hitEndText = false;
bool autoText = false;
bool onAutoSwitch = false;
bool isBlackScreen = true;
bool isPlayerTalkTurn_alpha;
bool isGoddessTalkTurn_alpha;
bool isGirlTalkTurn_alpha;
bool showPlayer = false, showGoddess = false, showGirl = false;

char name[256];

int x, y;
int clickX_axis, clickY_axis;

int playerFace_Hdls[13];
int offensive_f1, normal_1, normal_2, surprise1,
smile_1, smile_2, smile_3, mad1, mad2, speechless_1, speechless_2,
speechless_3, suspect1, playerWholeBody;

int goddessWholeBody_normal, goddessWholeBody_smile, goddessWholeBody_serious, goddessWholeBody_secret;
int girl_normal, girl_smile, girl_serious, girl_mad1, girl_mad2, girl_secret;
int BGHdl_FinaScene;

tnl::Vector3 TITLE_BTNFUNC_POS = { 125, 700, 0 };
tnl::Vector3 LOAD_BTNFUNC_POS = { 295, 700, 0 };
tnl::Vector3 SAVE_BTNFUNC_POS = { 465, 700, 0 };
tnl::Vector3 AUTO_BTNFUNC_POS = { 635, 700, 0 };
tnl::Vector3 SKIP_BTNFUNC_POS = { 805, 700, 0 };
tnl::Vector3 LOG_BTNFUNC_POS = { 975, 700, 0 };
tnl::Vector3 CONFIG_BTNFUNC_POS = { 1145, 700, 0 };


std::string* PLAYE_NAME;

std::string inputPlayerName;

std::string receiveText[140];
int strCount = 0;
int addTexNum = 2;

void SetPlayersName() {


	SetDrawBright(200, 200, 200);

	SetActiveKeyInput(inputNameHdl);

	// 入力モードを描画
	DrawKeyInputModeString(640, 480);

	// 入力途中の文字列を描画
	DrawKeyInputString(0, 0, inputNameHdl);

	char buff[256];
	GetKeyInputString(buff, inputNameHdl);
	inputPlayerName = buff;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		inputCharName = false;
	}

	PLAYE_NAME = &inputPlayerName;

	DrawStringEx(100, 300, -1, "%s", inputPlayerName.c_str());
}


std::string prologueTextLog[140] = {

		"・・・・・・・・・",

		"・・・・・・・・・",

			"・・・・・・・・・",

			"それは深い眠りについているかのような感覚だった。",

			"ゆ・・・し・・・・ま！",

			"体を動かすことも、何かを考えることさえ億劫なそんな状態の中、何やら声が聴こえて来る。",

			"「ゆうしゃさま！！！」",

			"！？！？！？",

			"まるで気持ちよく眠っていた自分を嘲笑うかのように、その甲高い声は俺を叩き起こした。",

			"「う・・・・」",

			"「あ！？やっと起きてくださいましたね、勇者様！」",


			"鈍く痛む頭を手で押さえながら、ゆっくりと体を起こす。",

			"「・・・ここは？」",


			"現状を把握するため周囲を見渡すが、すぐさま混乱に陥る。",

			"そこは薄暗い空間だった。棒状のライト(？)が頼りなく暗闇を照らしている。",

			"後方を確認するとやはり同じように暗かったが、今自分がいる場所は目の前の扉に続く一本道\nのようだということが辛うじて分かった。",

			"(・・・あれ？・・寝ぼけてるのか？)",

			"不思議なことに目を覚ます前までのことを思い出せない。混乱による一時的なものなのか、\nそれとも記憶を失ってしまったのか、それすら判断出来なかった。",

			"しかも疑問に思ったのはそれだけではない。",

			"先程声を発していた目の前の女性に目を向ける。",

			"数秒観察してみたが、どうあがいてもそれは俺の全く知らない人物だった。",

			"(頭に変な王冠みたいのを載せてるし、変わった服を着ている。・・コスプレか？)",

			"(いやコスプレイヤーと暗闇で二人きりとかどんな状況だよ)",

			"こうして考えていても仕方がない、直接訊いた方が早いだろう。",

			"「・・・・・・あのー、すみません。ここはどこですか？」",

			"そう訊くと女性は目を逸らし、小さな声で返答した。",

			"「・・・・冥界」",

			"「は？」",

			"「勇者様、突如こちらの世界へお呼びしてしまった非礼をお詫び申し上げると共に、先にお伝え\nすることがございます」",

			"俺の目を真っ直ぐ見つめ、一呼吸おいてから再び口を開く。",

			"「あなたは死にました」",

			"・・・・・は？",

			"「混乱されるお気持ちはよく分かりますが、落ち着いてください」",

			"「あなたは死んだ、そして蘇ったのです、人の国【シュルス帝国】を救う勇者として」",

			"-----------------------------------",

			"「そんなゴミを見るような目で見つめないでください、私は真剣なのです！」",

			"何？俺今そんな顔してるのか？完全に無意識だった。",

			"「勇者様！あなた様は人の子の代表として勇者に選ばれたのです。そして選ばれた者はその責務を全うし、\n人々に安寧と秩序を齎さなくてはなりません」",

			"「これからあなた様は修羅の道を進むことになるでしょう。ですがご心配には及びません！」",

			"(・・嘘を言っているようには見えないけど内容があまりに馬鹿馬鹿しい。新手の詐欺か、もしくは\n不思議ちゃんなのか・・・？)",

			"「あなた様が選ばれたことにははっきりとした理由があるのです！強い意志を宿した瞳、精悍な面持ち、\n気高く美しく燃えるその魂・・・」",

			"「本来であれば一度死んだ魂は浄化されるまで。地上に戻ることは許されません」",

			"「しかし、他の神々との話し合いの結果、いくつかの制約付きで今回は特例を設けることと致しました」",

			"「特例？」",

			"「はい！勇者様の魂を再び地上に戻すことは神々の掟で禁じられています、が」",

			"「勇者様が今迄積んできた徳から鑑みて、今回は特例として別世界への転生が認められたのです」",

			"「つきましては、勇者様には是非その清く真っ直ぐな心を貫き通し、今の【シュルス帝国】を正しい道に\n導く先駆者となっていただきたく思います！」",

			"何を言っているのかさっぱり分からなかったが、ここで俺はある一つの可能性に気が付く。\n",

			"(ドッキリか？！)",

			"今聞かされている訳の分からない話よりは余程現実性が高い。",

			"ひとたびその考えに辿り着くと、先程まで抱えていた緊張と不安が少しだけ和らいだことを感じる。",

			"（いやでも他にどう説明するんだ？誘拐？夢？）",

			"まず誘拐という線はないだろう。そうであればこのような茶番に意味はない。",

			"であれば夢か？",

			"・・・",

			"もし夢であれば目が覚めたら全て忘れよう。こんなのただの黒歴史だ。",

			"ひとまず情報を得るため、適当に返答してみることにした。",

		   "「えーっと・・・・その話って俺に何かメリットとかってあったりするんですか？」",

			"「え？」",

			"意外な反応だったのか、目の前の女神(笑)はキョトンとした表情で固まる。",

			"「え？だってそれって要するに自分の身を危険に晒して誰かと戦えってことですよね？」",

			"「ゆ、勇者様？こ、これは人類にとってとても栄光のある使命なのですよ？！選ばれしものだけが得られる\n至高の----」",

		   "「あと何故俺がその勇者ってのに選ばれたんですか？自分で言うのもなんですけど俺って特に取り柄\nとかないし・・」",

		   "話を遮られて少し不満だったのか、女神(笑)からは先程までの笑顔が消えていた。",

			"「・・・申し訳ございませんが、今それをお伝えする時間はございません。勇者様には一刻も早く地上へ戻り、\n人々に救いの手を差し伸べて欲しいのです」",

			"(いつまで続くんだろうこれ・・・・)",

		   "「これは新たなる伝説の始まりとなるでしょう、勇者様に女神の祝福があらんことを・・・」",

		   "「いや、話は終わってな-----」",



		   //	"------------------------------------------------------------暗転--------------------------------------------------------------",

				"--------------------------------------------------------",

				"------------------------------------------",

				"----------------------------",

				   "「うおぉぉっっ！！？」",

				   "「あ、来たわね？」",

				   "突然真っ暗になったと思ったら今度は先程とは違う景色が映し出された。",

				   "どうやら、さっきの女神(笑)が俺をここに転移させたようだ・・・って、転移？？！！",

				   "頬をつねってみたが、普通に痛い。まさかそんなことをする日が来るとは思いもよらなかった。",

				   "（・・・・・・）",

				   "転移の際、恐らく一瞬だけ俺の体はこの世から存在を消していた。",

				   "一瞬の出来事だったため確証はないが、恐らくあれは本物だった。しかしそれを言っても信じる者は\nいないだろう。先程までの自分と同じように。",

				   "ただ、本物でなければこの状況をどう説明しろというのか。",

				   "・・・救いを求めるように辺りを見渡し、一人の少女と目が合った。",

				   "「・・・何か考え中のとこ悪いけど時間がないの、さっそく話を始めるわ」",

				   "(あれ・・・？デジャヴ？)",

				   "つい最近同じようなことがあったような気がするのだが、気のせいか？",

				   "少女は宣言通り、こちらの精神状態など知らんとでも言わんばかりに勝手に話を始めた。",

				   "「勇者として生まれ変わったというのはもう聞いてるわね？」",

				   "「あ、・・・・まあ一応・・・・てか君は？」",

					"「あたしのことは後よ。それよりここに来る前に女神様から何かギフトを授からなかった？」",

					"「ギフト？」",

					"「只の人間がまともに魔女と戦えるわけないじゃない、奴らと戦うためには力が要るわ。どこかに\n印のようなものが刻まれてない？」",

					"そう言われ俺は自身の体をサッと見渡す。",

					"「あ、・・これ？」",

					"右手の甲に赤い紋章のようなものが浮かび上がっている。",

				   "「あ、そうそうそれそれ！分かるわね・・・戦うのよ！それで」",

				  "紋章を見せた途端、少女のテンションが明らかに豹変した。これってそんなに凄いものなのか・・・？",

				 "「それは通称【魔拳】。その刻印を発動することによって神聖なる力を行使することが出来るの」",

				"「具体的に言うと、あなたはこれから敵と戦うとき、【ジャンケン】と呼ばれる儀式を行わなくてはならない」",

				 "「【ジャンケン】に勝つことができれば相手にダメージを与えられる。当然負ければその逆ね」",

				 "「儀式の回数は相手のレベルによって異なるけど、要するに全てに勝てばいいのよ。簡単でしょ？」",

				 "少し癪に障る言い方だったが、俺は敢えてそれを気にしないようにする。",

				 "そんなことより・・・・・・",

				"【ジャンケン】",

				"聞いたことがない単語だった。",

				"しかし不思議なことに何故か俺はそれを知っている。",

				"儀式は初めに３つの属性の内１つを選ぶことから始まり、それを自身の手で実体化する。",

				"そしてそれを相手の選んだ属性と衝突させ、勝敗を決めるのだ。",

				"単純だが、それでいて非常に奥が深い。",

			   "(この国の命運がこの手に・・・)",

			   "気が付けばつい先程まで女神を馬鹿にしていた自分はもういなくなっていた。",

			   "転移を実際にその身で味わってからか、今の状況に俺は少しずつ馴染み始めているのかもしれない。",

			   "自身の適応能力に驚愕しつつ、ふと右手を見るとそれが僅かに震えていることが分かった。",

			   "その震えは意識しても制御ができず、止まろうとはしてくれなかった。",

			   "「・・・多分まだ混乱しているみたいだけど、この世界は紛れもない現実、それは覚えといて」",

				"「・・・了解」",

				"「・・・じゃあ最後に簡単にこの国の現状を説明するわね」",

				"理解早くて助かるわぁ、と皮肉少女は話を続ける。",

				"「いい？この国は現在、スティン、シエーレ、ハーピア、セグア、そして最大の敵、レジーナによって支配され\nている。まあ、ざっくり言うとそいつらを倒してくれればあなたの使命はそこで果たされるわ」",

				"「そいつらの目的は？」",

				"「・・・さぁ？でも魔女が人間を支配するのに理由なんて要らないんじゃないかしら？手の届く範囲に丁度いい\n領土があったから自分の所有物にした、多分そんなところよ」",

				"何か説明が雑・・・とは思ったが少女の話は大体想像がつく。やったことあるＲＰＧゲームでもそういうのはあった。",

				"頷いてみせると少女は満足したかのように微笑み、まるでこの話は終わりとでも言うように話題を変えた。",

				 "「よし！じゃあ取り敢えずいつまでもここにいても仕方ないし、移動しながら話しましょう・・・あ、\nそういえば自己紹介がまだだったわ」",

				  "「私はフィナ、あなたは？」",


   "名前入力",


	"「 #name、悪くない名前ね」",


	"「そりゃどーも」",


	"「それじゃ改めて、行きましょうか・・・この国を救いに」",

"次のシーンへ"
};


//シュルス(Schluss)＝終わり
//スティン(Stein) ＝ 石
//シエーレ(Schere)＝ 鋏
//ハーピア(Papier) ＝ 紙 
//セグア(Seguace) = 配下　イタリア語
//レジーナ(Regina) = 女王 イタリア語


int scenePhase = 0;     // 0が女神、1がフィナ

void ShowPrologueTextLog(float delta_time) {


	isTitleScene = false;

	if (isBlackScreen == false && currentMessLine < 68) {
		DrawRotaGraph(620, 125, 0.7f, 0.0f, prologueEvent_BGhdl, true);
	}


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && inputCharName == false && isStillTalking == true) {

		if (prologueTextLog[currentMessLine] == "名前入力") {
			prologueTextLog[currentMessLine] = "名前を入力してください";
			inputCharName = true;
		}

		if (inputCharName == false) {
			if (prologueTextLog[currentMessLine] == "次のシーンへ") {
				SetFontSize(35);
				DrawFormatString(350, 400, -1, "%s", "Enter");
				hitEndText = true;
				isStillTalking = false;
			}
		}
		autoTimer = 0.0f;
	}


	if (inputCharName == false && isStillTalking == false && hitEndText == true) {
		ClearDrawScreen();

		FlashSymbolAndMap(1);
	}
	else {

		// 女神シーン----------------------------------------------------------------------------------------------------------------------------------
		SetFontSize(20);

		switch (scenePhase)
		{
		case 0:
			if (showPlayer == true && currentMessLine < 68) {
				DrawWholePlayer();
			}

			if (showGoddess == true && currentMessLine < 20) {

				DrawGoddess(goddessWholeBody_secret);
			}

			if (showGoddess == true && currentMessLine >= 20) {
				if (currentMessLine == 20 || currentMessLine == 21 || currentMessLine == 22 || currentMessLine == 23 ||
					currentMessLine == 24 || currentMessLine == 25 || currentMessLine == 26 || currentMessLine == 27 || currentMessLine == 32 ||
					currentMessLine == 38 || currentMessLine == 39 || currentMessLine == 41 || currentMessLine == 43 || currentMessLine == 58 ||
					currentMessLine == 59 || currentMessLine == 60 || currentMessLine == 66 || currentMessLine == 67) {
					DrawGoddess(goddessWholeBody_normal);
				}
				if (currentMessLine == 28 || currentMessLine == 29 || currentMessLine == 30 || currentMessLine == 31 || currentMessLine == 35 ||
					currentMessLine == 36 || currentMessLine == 42 || currentMessLine == 46 || currentMessLine == 47 || currentMessLine == 48 ||
					currentMessLine == 49 || currentMessLine == 50 || currentMessLine == 51 || currentMessLine == 52 || currentMessLine == 53 ||
					currentMessLine == 54 || currentMessLine == 55 || currentMessLine == 56 || currentMessLine == 57 || currentMessLine == 61 ||
					currentMessLine == 62 || currentMessLine == 63 || currentMessLine == 64 || currentMessLine == 65) {
					DrawGoddess(goddessWholeBody_serious);
				}
				if (currentMessLine == 33 || currentMessLine == 34 || currentMessLine == 37 || currentMessLine == 40 ||
					currentMessLine == 44 || currentMessLine == 45) {
					DrawGoddess(goddessWholeBody_smile);
				}
			}
			
			if (currentMessLine >= 71) {
				scenePhase = 1;
			}
			break;
			//　フィナシーン------------------------------------------------------------------------------------------------------------------------------
		case 1:
			DrawRotaGraph(500, 50, 1.0f, 0.0f, BGHdl_FinaScene, true);

			if (currentMessLine > 71 && currentMessLine < 127) {
				DrawWholePlayer();
			}

			if (currentMessLine > 71 && currentMessLine <= 80)	DrawGirl(girl_secret);

			if (currentMessLine == 81 || currentMessLine == 82 || currentMessLine == 83 ||
				currentMessLine == 84 || currentMessLine == 87 || currentMessLine == 88 || currentMessLine == 97 ||
				currentMessLine == 113 || currentMessLine == 114 || currentMessLine == 115) {
				DrawGirl(girl_normal);
			}
			if (currentMessLine == 85 || currentMessLine == 86 || currentMessLine == 95 || currentMessLine == 96 ||
				currentMessLine == 112 || currentMessLine == 113) {
				DrawGirl(girl_serious);
			}
			if (currentMessLine == 93 || currentMessLine == 94 || currentMessLine == 98 || currentMessLine == 99 ||
				currentMessLine == 100 || currentMessLine == 101 || currentMessLine == 102 ||
				currentMessLine == 103 || currentMessLine == 104 || currentMessLine == 105 ||
				currentMessLine == 105 || currentMessLine == 106 || currentMessLine == 107 ||
				currentMessLine == 108 || currentMessLine == 109 || currentMessLine == 110 ||
				currentMessLine == 111 || currentMessLine == 121 || currentMessLine == 122 ||
				currentMessLine == 123 || currentMessLine == 124 || currentMessLine == 125 ||
				currentMessLine == 126) {
				DrawGirl(girl_smile);
			}
			if (currentMessLine == 89 || currentMessLine == 90 || currentMessLine == 91 ||
				currentMessLine == 92) {
				DrawGirl(girl_mad2);
			}
			if (currentMessLine == 116 || currentMessLine == 117 || currentMessLine == 118 ||
				currentMessLine == 119 || currentMessLine == 120) {
				DrawGirl(girl_mad1);
			}

			break;
		}


		SetDrawBright(255, 255, 255);

		DrawBox(0, 500, 1280, 800, GetColor(20, 20, 20), true);
		for (int i = 0; i < 140; ++i) {
			receiveText[i] = prologueTextLog[i];
		}
		if (currentMessLine < 140) {
			receiveText[currentMessLine] = prologueTextLog[currentMessLine].substr(0, strCount);
		}

		if (prologueTextLog[currentMessLine].length() > strCount) {
			strCount += addTexNum;
		}
		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && (prologueTextLog[currentMessLine].length() <= strCount)) {
			currentMessLine++;
			strCount = 0;
		}

		SetFontSize(20);
		DrawStringEx(90, 550, -1, "%s", receiveText[currentMessLine].c_str());

		DrawFuncBtns();

		for (const auto& BTNFUNC_INFO : btnInfos) {
			ZoomBtnsOnMouseOver(BTNFUNC_INFO);
			AddClickFuncOnBtns(BTNFUNC_INFO);
		}
	}

	if (currentMessLine < 9) {
		isBlackScreen = true;
		showPlayer = false;
		showGoddess = false;
	}
	else {
		isBlackScreen = false;
		showPlayer = true;
		showGoddess = true;
	}

	if (currentMessLine == 9 || currentMessLine == 12 || currentMessLine == 16 || currentMessLine == 21 || currentMessLine == 22 ||
		currentMessLine == 24 || currentMessLine == 27 || currentMessLine == 31 || currentMessLine == 34 || currentMessLine == 36 ||
		currentMessLine == 39 || currentMessLine == 43 || currentMessLine == 48 || currentMessLine == 51 || currentMessLine == 54 ||
		currentMessLine == 57 || currentMessLine == 60 || currentMessLine == 62 || currentMessLine == 65 || currentMessLine == 67 ||
		currentMessLine == 71 || currentMessLine == 76 || currentMessLine == 82 || currentMessLine == 86 || currentMessLine == 88 ||
		currentMessLine == 91 || currentMessLine == 107 || currentMessLine == 113 || currentMessLine == 117 || currentMessLine == 125) {

		isPlayerTalkTurn_alpha = true;
	}
	else {
		isPlayerTalkTurn_alpha = false;
	}

	if (currentMessLine == 10 || currentMessLine == 26 || currentMessLine == 28 || currentMessLine == 30 || currentMessLine == 32 ||
		currentMessLine == 33 || currentMessLine == 35 || currentMessLine == 37 || currentMessLine == 38 || currentMessLine == 40 ||
		currentMessLine == 41 || currentMessLine == 42 || currentMessLine == 44 || currentMessLine == 45 || currentMessLine == 46 ||
		currentMessLine == 58 || currentMessLine == 61 || currentMessLine == 64 || currentMessLine == 66) {

		isGoddessTalkTurn_alpha = true;
	}
	else {
		isGoddessTalkTurn_alpha = false;
	}

	if (currentMessLine == 81 || currentMessLine == 85 || currentMessLine == 87 ||
		currentMessLine == 89 || currentMessLine == 93 || currentMessLine == 95 ||
		currentMessLine == 96 || currentMessLine == 97 || currentMessLine == 98 ||
		currentMessLine == 112 || currentMessLine == 114 || currentMessLine == 116 ||
		currentMessLine == 118 || currentMessLine == 121 || currentMessLine == 122 ||
		currentMessLine == 124 || currentMessLine == 126) {

		isGirlTalkTurn_alpha = true;
	}
	else {
		isGirlTalkTurn_alpha = false;
	}


	if (inputCharName == true) {
		SetPlayersName();

		SetFontSize(30);
		DrawString(1070, 640, "Space", -1);
	}
	else {
		SetDrawBright(255, 255, 255);
	}
	if (inputCharName == false && isStillTalking == true && hitEndText == false) {
		SetFontSize(30);
		DrawString(1070, 620, "Enter", -1);
	}
}


void LoadPlayerFacesAndOthers() {
	offensive_f1 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/ドン引き.png");
	normal_1 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/ノーマル.png");
	normal_2 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/ノーマル2.png");
	surprise1 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/驚き.png");
	smile_1 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/笑顔1.png");
	smile_2 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/笑顔2.png");
	smile_3 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/笑顔3.png");
	mad1 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/怒り1.png");
	mad2 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/怒り2.png");
	speechless_1 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/呆れ.png");
	speechless_2 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/呆れ2.png");
	speechless_3 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/呆れ3.png");
	suspect1 = LoadGraph("graphics/キャラクター素材/主人公/表情差分/疑問.png");
	playerWholeBody = LoadGraph("graphics/キャラクター素材/主人公/立ち絵2.png");


	goddessWholeBody_normal = LoadGraph("graphics/キャラクター素材/女神/ノーマル.png");
	goddessWholeBody_smile = LoadGraph("graphics/キャラクター素材/女神/笑顔.png");
	goddessWholeBody_serious = LoadGraph("graphics/キャラクター素材/女神/真剣.png");
	goddessWholeBody_secret = LoadGraph("graphics/キャラクター素材/女神/謎.png");

	girl_normal = LoadGraph("graphics/キャラクター素材/少女/girl_normal.png");
	girl_serious = LoadGraph("graphics/キャラクター素材/少女/girl_serious.png");
	girl_smile = LoadGraph("graphics/キャラクター素材/少女/girl_smile.png");
	girl_mad1 = LoadGraph("graphics/キャラクター素材/少女/girl_mad1.png");
	girl_mad2 = LoadGraph("graphics/キャラクター素材/少女/girl_mad2.png");
	girl_secret = LoadGraph("graphics/キャラクター素材/少女/girl_secret.png");

	BGHdl_FinaScene = LoadGraph("graphics/夜.jpg");
}

void DrawPlayersFace(int expression) {

	DrawRotaGraph(40, 620, 1.0f, 0.0f, expression, true);
}

void DrawWholePlayer() {
	if (isPlayerTalkTurn_alpha == true) {
		SetDrawBright(255, 255, 255);

	}
	else {
		SetDrawBright(160, 160, 160);
	}
	DrawRotaGraph(110, 560, 1.0f, 0.0f, playerWholeBody, true);
}

void DrawGoddess(int goddessFace) {
	if (isGoddessTalkTurn_alpha == true) {
		SetDrawBright(255, 255, 255);
	}
	else {
		SetDrawBright(160, 160, 160);
	}
	DrawRotaGraph(1050, 520, 1.0f, 0.0f, goddessFace, true);
}

void DrawGirl(int girlFace) {
	if (isGirlTalkTurn_alpha == true) {
		SetDrawBright(255, 255, 255);
	}
	else {
		SetDrawBright(160, 160, 160);
	}
	DrawRotaGraph(1050, 385, 0.9f, 0.0f, girlFace, true);
}

void LoadFuncButtons() {
	btnInfos = {

	{LoadGraph("graphics/TextButtons/TitleFuncBtn.png"),TITLE_BTNFUNC_POS.x,TITLE_BTNFUNC_POS.y,70,30,0.115f,0.14f},
	{LoadGraph("graphics/TextButtons/SkipFuncBtn.png"),SKIP_BTNFUNC_POS.x,SKIP_BTNFUNC_POS.y,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/saveFuncBtn.png"),SAVE_BTNFUNC_POS.x,SAVE_BTNFUNC_POS.y,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/logFuncBtn.png"),LOG_BTNFUNC_POS.x,LOG_BTNFUNC_POS.y,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/loadFuncBtn.png"),LOAD_BTNFUNC_POS.x,LOAD_BTNFUNC_POS.y,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/configFuncBtn.png"),CONFIG_BTNFUNC_POS.x,CONFIG_BTNFUNC_POS.y,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/autoFuncBtn.png"),AUTO_BTNFUNC_POS.x,AUTO_BTNFUNC_POS.y,70,30,0.115f,0.15f}
	};
}

void DrawFuncBtns() {
	DrawRotaGraph(125, 700, 0.12f, 0, titleFuncBtn, true);
	DrawRotaGraph(295, 700, 0.12f, 0, loadFuncBtn, true);
	DrawRotaGraph(465, 700, 0.12f, 0, saveFuncBtn, true);
	DrawRotaGraph(635, 700, 0.12f, 0, autoFuncBtn, true);
	DrawRotaGraph(805, 700, 0.12f, 0, skipFuncBtn, true);
	DrawRotaGraph(975, 700, 0.12f, 0, logFuncBtn, true);
	DrawRotaGraph(1145, 700, 0.12f, 0, configFuncBtn, true);
}


void ZoomBtnsOnMouseOver(const FuncBtnsInfo& btnInfo) {
	int hoveredX, hoveredY;
	float scaleSize;

	GetMousePoint(&hoveredX, &hoveredY);

	if (hoveredX >= btnInfo.x && hoveredX <= btnInfo.x + btnInfo.width && hoveredY >= btnInfo.y && hoveredY <= btnInfo.y + btnInfo.height) {
		scaleSize = btnInfo.zoomSize;
	}
	else {
		scaleSize = btnInfo.normalSize;
	}

	DrawRotaGraph(btnInfo.x, btnInfo.y, scaleSize, 0.0f, btnInfo.handle, false);
}


void AddClickFuncOnBtns(const FuncBtnsInfo& btnInfos) {
	GetMousePoint(&clickX_axis, &clickY_axis);

	if (GetMouseInput() && MOUSE_INPUT_LEFT) {

		if (clickX_axis >= btnInfos.x && clickX_axis <= btnInfos.x + btnInfos.width && 
			clickY_axis >= btnInfos.y && clickY_axis <= btnInfos.y + btnInfos.height) {
			// TITLEボタン
			if (btnInfos.x >= TITLE_BTNFUNC_POS.x && btnInfos.x <= TITLE_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= TITLE_BTNFUNC_POS.y && btnInfos.y <= TITLE_BTNFUNC_POS.y + btnInfos.height) {
				g_scene_id = 3;  // SCENE_ID_TITLE
			}
			// LOADボタン
			if (btnInfos.x >= LOAD_BTNFUNC_POS.x && btnInfos.x <= LOAD_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= LOAD_BTNFUNC_POS.y && btnInfos.y <= LOAD_BTNFUNC_POS.y + btnInfos.height) {

			}
			// SAVEボタン
			if (btnInfos.x >= SAVE_BTNFUNC_POS.x && btnInfos.x <= SAVE_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= SAVE_BTNFUNC_POS.y && btnInfos.y <= SAVE_BTNFUNC_POS.y + btnInfos.height) {

			}
			// AUTOボタン
			if (btnInfos.x >= AUTO_BTNFUNC_POS.x && btnInfos.x <= AUTO_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= AUTO_BTNFUNC_POS.y && btnInfos.y <= AUTO_BTNFUNC_POS.y + btnInfos.height) {
				autoText = !autoText;
			}
			// SKIPボタン
			if (btnInfos.x >= SKIP_BTNFUNC_POS.x && btnInfos.x <= SKIP_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= SKIP_BTNFUNC_POS.y && btnInfos.y <= SKIP_BTNFUNC_POS.y + btnInfos.height) {
				isShowSymbols = true;
				g_scene_id = 4;
			}
			// LOGボタン
			if (btnInfos.x >= LOG_BTNFUNC_POS.x && btnInfos.x <= LOG_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= LOG_BTNFUNC_POS.y && btnInfos.y <= LOG_BTNFUNC_POS.y + btnInfos.height) {

			}
			// CONFIGボタン
			if (btnInfos.x >= CONFIG_BTNFUNC_POS.x && btnInfos.x <= CONFIG_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= CONFIG_BTNFUNC_POS.y && btnInfos.y <= CONFIG_BTNFUNC_POS.y + btnInfos.height) {

			}
		}
	}
}

void AutoFunction() {

	if (autoText == false) 	return;

	autoTimer += 0.015;

	if (autoTimer >= 1.5f) {
		currentMessLine++;
		autoTimer = 0.0f;
	}
}