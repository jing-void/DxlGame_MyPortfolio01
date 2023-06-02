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

char name[256];

int x, y;
int clickX_axis, clickY_axis;

int playerFace_Hdls[13];
int offensive_f1, normal_1, normal_2, surprise1,
smile_1, smile_2, smile_3, mad1, mad2, speechless_1, speechless_2,
speechless_3, suspect1, playerWholeBody;

int goddessWholeBody_normal, goddessWholeBody_smile, goddessWholeBody_serious, goddessWholeBody_secret;

tnl::Vector3 TITLE_BTNFUNC_POS = { 125, 700, 0 };
tnl::Vector3 LOAD_BTNFUNC_POS = { 295, 700, 0 };
tnl::Vector3 SAVE_BTNFUNC_POS = { 465, 700, 0 };
tnl::Vector3 AUTO_BTNFUNC_POS = { 635, 700, 0 };
tnl::Vector3 SKIP_BTNFUNC_POS = { 805, 700, 0 };
tnl::Vector3 LOG_BTNFUNC_POS = { 975, 700, 0 };
tnl::Vector3 CONFIG_BTNFUNC_POS = { 1145, 700, 0 };


std::string* PLAYE_NAME;

std::string inputPlayerName;

std::string receiveText[130];
int strCount = 0;
int addTexNum = 1;

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


std::string prologueTextLog[130] = {

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

		"そこは薄暗い空間だった。",

		"棒状のライト(？)が頼りなく暗闇を照らしている。",

		"後方を確認するとやはり同じように暗かったが、今自分がいる場所は目の前の扉に続く一本道\nのようだということが辛うじて分かった。",

		"(・・・あれ？・・寝ぼけてるのか？)",

		"不思議なことに目を覚ます前までのことを思い出せない。混乱による一時的なものなのか、\nそれとも記憶を失ってしまったのか、それすら判断出来なかった。",

		"しかも疑問に思ったのはそれだけではない。",

		"先程から声を発している目の前の女性。",

		"一度そちらに顔を向け彼女の様子を伺ってみるが、それは俺の全く知らない人物だった。",

		"(頭に変な王冠みたいのを載せてるし、変わった服を着ている。・・コスプレか？)",

		"(いやコスプレイヤーと暗闇で二人きりとかどんな状況だよ)",

		"考えていても仕方ない、人がいるのだから訊いた方が早いだろう。",

		"「・・・・・・あのー、すみません。ここはどこですか？」",

		"そう訊くと女性は目を逸らし、小さな声で返答した。",

		"「・・・・冥界」",

		"「は？」",

		"「勇者様、単刀直入に申し上げます」",

		"「あなたは死にました」",

		"・・・・・は？",

	   "「混乱されるお気持ちはよく分かりますが、落ち着いてください！」",
	   "「あなたは死んだ、そして蘇ったのです、人の国【シュルス帝国】を救う勇者として」",

	   "-----------------------------------",

	   "「そんなゴミを見るような目で見つめないでください、私は真剣なのです！」",

	   //"選択肢 No1.にらみつける　No.2.嘲笑する　No3.中指を立てる


			  "「ですから・・・・あぁ！もうとにかく！」",

			  "「勇者様！あなた様は人の子の代表として勇者に選ばれたのです。そして選ばれたものはその責務を全うし、\n人々に安寧と秩序を齎さなくてはなりません」",

			"「これからあなた様は修羅の道を進むことになるでしょう。ですがご心配には及びません！」",

			"(・・嘘を言っているようには見えないけど内容があまりに馬鹿馬鹿しい。新手の詐欺か、もしくは\n不思議ちゃんなのか・・・？)",

			"「あなた様が選ばれたことにははっきりとした理由があるのです！強い意志を宿した瞳、精悍な面持ち、\n気高く美しく燃えるその魂・・・」",

			"「本来であれば一度死んだ魂は浄化されるまで。地上に戻ることは許されません」",

			"「しかし、他の神々との話し合いの結果、いくつかの制約付きで今回は特例を設けることと致しました」",

			"「特例？」",

			"「はい！勇者様の魂を再び地上に戻すことは神々の掟で禁じられています、が」",

			"「勇者様が今迄積んできた徳から鑑みて、今回は特例として別世界への転生が認められたのです」",

			"「つきましては、勇者様には是非その清く真っ直ぐな心を貫き通し、今の【シュルス帝国】を正しい道に\n導く先駆者となっていただきたく思います！」",

			"・・・ここまで真面目に話してもらったが結局何言っているのかよく分からなかった。",

			"とは言え一つ疑問に思ったことがあったため、取り敢えずそれをぶつけてみることにした。",

		   "「その話って俺に何のメリットがあるんですか？」",

			"「え？」",

			"意外な反応だったのか、目の前の女神(笑)はキョトンとした表情で固まる。",

			"「え？だってそれって要するに自分の身を危険に晒して戦えってことですよね？しかも他人を守りながら」",

			"「ゆ、勇者様？こ、これは人類にとってとても栄光のある使命なのですよ？！選ばれしものだけが得られる\n至高の----」",

		   "「あと、その勇者ってのに選ばれるような崇高な人間じゃないですよ俺。人の悪口とか普通に言うし、\nもしかして人違いじゃないですか？」",

		   "「・・・・・・・それでは勇者様、あなたを地上へ送り返します」",

		   "「あれ？続けるの？」",

		   "「これは新たなる伝説の始まりとなるでしょう、女神の祝福があらんことを・・・」",

		   "「いや、話は終わってな-----」",



		   //	"------------------------------------------------------------暗転--------------------------------------------------------------",

				   "「うおぉぉっっ！！？」",

				   "「あ、来たわね？」",

				   "突然真っ暗になったと思ったら今度は先程とは違う景色が映し出された。",

				   "どうやら、さっきの女神(笑)が俺をここに転移させたようだ・・・って、転移？？！！嘘だろ？！！",

				   "(やべぇ一気に現実味を帯びて来たぞ・・・)",

				   "転移の際、恐らく一瞬だけ俺の体はこの世から消えていた。",

				   "本当に一瞬の出来事だったため確かなことは言えないが、あれは本物だった。",

				   "そもそも本物でなければこの状況をどう説明するというのか。",

				   "・・・何というか筆舌に尽くしがたい興奮が俺を襲う。暫くは眠れなくなるかもしれない。",

				   "(あれが本当の神業ってやつだな)",


				   "「・・・何か考え中のとこ悪いけど時間がないの、さっそく話を始めるわ」",

				   "声のした方へ顔を向けると、そこに小さな少女が佇んでいた。",

				   "様子からして明らかに俺に話しかけているようだ。",

				   "「勇者として生まれ変わったというのはもう聞いてるわね？」",

				   "「あ、うん一応・・・てか君は？」",


					"「あたしのことは後よ。恐らくあなたは女神様からギフトを授かっていると思うんだけど・・・」",

					"「ギフト？」",

					"「只の人間がまともに魔女と戦えるわけないじゃない、どこかに印のようなものが刻まれてない？」",

					"そう言われ俺は自身の体をサッと見渡す。",

					"「あ、これか！」",

					"右手の甲に赤い紋章のようなものが浮かび上がっている。",

				   "「あ、そうそうそれそれ！分かるわね、戦うのよ！それで」",

				  "紋章を見せると少女のテンションが明らかに変わり、少し食い気味になった。そこは何だか見た目に\n相まって子どもらしい。",

				  "「光栄に思いなさいよね！それが欲しくて堪らない人なんて数え切れないほどいるんだから！」",

				  "「・・・・」",

				 "「こほん、それは通称【魔拳】。その刻印を発動することによって神聖なる力を行使することが出来るの」",

				"「具体的に言うと、あなたはこれから敵と戦うとき、【ジャンケン】と呼ばれる儀式を行わなくてはならない」",

				 "「【ジャンケン】に勝つことができれば相手にダメージを与えられる。当然負ければその逆ね」",

				 "「儀式の回数は相手のレベルによって異なるけど、要するに全てに勝てばいいのよ。簡単でしょ？」",

				 "なんか言い方がちょいちょい癪に障るんだよな・・・別にいいけど",

				 "そんなことより・・・・・・",

				"【ジャンケン】",

				"なぜだろう、初めて聞いた単語のはずなのに、何故か俺はそれを知っている。",

				"確か、儀式は初めに３つの属性の内１つを選ぶことから始まり、それを自身の手で実体化する。",

				"そしてそれを相手の選んだ属性と衝突させ、勝敗を決めるのだ。",

				"単純だが、それでいて非常に奥が深い。",

			   "(この国の命運はこの手に掛かっているのか・・・)",

			   "もう先程まで女神を馬鹿にしていた自分はいない。",

			   "今見つめているその右手は僅かに震えており、俺はその震えを制御することが出来なかった",

				"ふと気が付くと、少女は怪訝な表情を浮かべこちらを見ていた。",

			   "「・・・多分まだ混乱しているみたいだけど、この世界は紛れもない現実、それは覚えといて」",

				"「・・・了解」",

				"「よし！それじゃあ最後に簡単にこの国の現状を説明するわね」",

				"理解早くて助かるわぁ、と言いながら少女は話を続ける。",

				"「いい？この国は現在、スティン、シエーレ、ハーピア、セグア、そして最大の敵、レジーナによって支配されている。\nまあ、ざっくり言うとそいつらを倒してくれればミッションコンプリート、あなたの使命はそこで果たされるってね」",

				"「そいつらの目的は？」",

				"「・・・さぁ？でも魔女が人間を支配するのに理由なんて要らないんじゃないかしら？食事したり睡眠をとったり\nするのと同じように、手の届く範囲に丁度いい領土があったから自分の所有物にした、みたいな？」",

				"何か雑・・・とは思ったが大体は分かった。やったことあるＲＰＧゲームでもそういうのあったしイメージは出来る。",

				"頷いてみせると少女は満足したかのように微笑み、この話は終わりと言わんばかりに話題を変えた。"

				 "「よし！じゃあ取り敢えず・・・っと、そういえば自己紹介がまだだったわね」",

				  "「私はフィナ、あなたは？」",


   "名前入力",

	
	"「 #name、悪くない名前ね」",
					  

	"「そりゃどーも」",


	"「それじゃ・・・いつまでもここにいても仕方ないし、そろそろ行きましょうか、この国を救いに・・・」",

"次のシーンへ"
};
   

//シュルス(Schluss)＝終わり
//スティン(Stein) ＝ 石
//シエーレ(Schere)＝ 鋏
//ハーピア(Papier) ＝ 紙 
//セグア(Seguace) = 配下　イタリア語
//レジーナ(Regina) = 女王 イタリア語



void ShowPrologueTextLog(float delta_time) {


	isTitleScene = false;

	DrawRotaGraph(620, 125, 0.7f, 0.0f, prologueEvent_BGhdl, true);


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && inputCharName == false && isStillTalking == true) {
		/*currentMessLine++;
		currentMessLine %= 130;*/
		

		if (prologueTextLog[currentMessLine] == "選択肢No.1"
			&& tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			prologueTextLog[currentMessLine] = "1.にらみつける   2.舌打ちをする   3.中指を立てる";
		}
		if (prologueTextLog[currentMessLine] == "選択肢No.5"
			&& tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			prologueTextLog[currentMessLine] = "ＯＫ";
		}
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
		SetFontSize(20);

		DrawWholePlayer();
		DrawGoddess(goddessWholeBody_secret);

		DrawBox(0, 500, 1280, 800, GetColor(20, 20, 20), true);
		for (int i = 0; i < 130; ++i) {
			receiveText[i] = prologueTextLog[i];
		}
		if (currentMessLine < 130) {
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
}

void DrawPlayersFace(int expression) {

	DrawRotaGraph(40, 620, 1.0f, 0.0f, expression, true);
}

void DrawWholePlayer() {
	DrawRotaGraph(95, 560, 1.0f, 0.0f, playerWholeBody, true);
}

void DrawGoddess(int goddessFace) {
	DrawRotaGraph(1050, 520, 1.0f, 0.0f, goddessFace, true);
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

		if (clickX_axis >= btnInfos.x && clickX_axis <= btnInfos.x + btnInfos.width && clickY_axis >= btnInfos.y && clickY_axis <= btnInfos.y + btnInfos.height) {
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