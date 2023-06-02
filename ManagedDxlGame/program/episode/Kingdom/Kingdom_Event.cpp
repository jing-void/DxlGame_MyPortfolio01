#include <string>
#include <time.h>
#include <iostream>
#include "../dxlib_ext/dxlib_ext.h"
#include "DxLib.h"
#include "../Prologue/PrologueEvent.h"
#include "../../../program/game/Main.h"
#include "../map/FieldMap.h"
#include "../janken/JankenBattle.h"


struct FuncBtnsInfo {
	int handle;
	float x;
	float y;
	int width;
	int height;
	float normalSize;
	float zoomSize;
};


std::vector<FuncBtnsInfo> btnInfos_Kingdom;


// prototype
void ZoomBtnsOnMouseOver_Kingdom(const FuncBtnsInfo& btnInfos_Kingdom);


extern int episodeNum;
int currentMess_Line = 0;
int titleFuncBtn, skipFuncBtn, saveFuncBtn, logFuncBtn, loadFuncBtn, configFuncBtn, autoFuncBtn;

bool hitEnd;

std::string kingdomBattleTextLog[150] = {
	//"ついにここまで来た。",
	// "最後の戦いを前にして思いを馳せる。",
	//"思い返せば決して楽な道ではなかった",
	//"目が覚めたら訳のわからないところにいて、突然「あなたは死にました」とか言われるし",
	//"おまけに勇者とかいう荷が重すぎる役目を背負わされるし",

	//	"・・・はぁ",

	//"今の状況、慣れはしたものの理解は全くしていない。未だに意味不明である。",


	//"あれからどれくらい経ったのだろう",
	//"一月前のような気もするし、下手をすればもう半年くらい経過しているのかもしれない",
	//"とにかく俺はこの世界で生き延びることに只々必死だった",
	//"今迄だって別にこの国を救うために戦っていたわけではない",
	//"俺は単に身に降りかかる火の粉を払ってきただけで、ここに辿り着いたのも成り行きだと思っている",


	//"「ふふ」",

	//"その時、視界の端に一つの人影のようなものを捉えた",

	//"「・・・よくぞここまで来た、我が思想に害をなそうとする下賤な人の子よ」",

	//"？",

	//"そう言いながら人影はこちらに向かって歩みを始める",
	//"コツコツコツ、と妙に規則正しいその足音はどこか薄気味悪かった",

	//"また敵か・・・",

	//"いつものことではあるが、嫌なものはそれが例え何回目だろうと絶対に嫌なのである",
	//"やがて人影は眼前で歩みを止め-----------俺は言葉を失った",

	//"・・・・・・・美しい",

	//"腰まで伸びた長い髪、透き通るような大きな瞳、蜜のように甘い声。",
	//"しかし、頭に付いているツノと、背後から伸びている尻尾だけがそれが人間ではないということをはっきりと物語っていた",
	//"ただそんなことはどうでもよい。",
	//"目の前の悪魔(？)は正直文句のつけようがないほど美しい、正直ドストライクである",
	//"『容姿端麗』という言葉だけでは収まりきらない、もはやどう表現するのが正解なのか不明なほどの魅力を感じるのだ",

	//"「ふん、知っておるわ」",

	//"さも興味が無さそうに目の前の悪魔(？)は答えた",
	//"しかしこれほどのオーラ、話に聞いていた『レジーナ』という最終目標で間違いなさそうだ",


	//
	//"1.おまえが『レジーナ』だな？",
	//"2.随分余裕そうだな",
	//"3.・・・好きです",
	//

	//// 選択1
	//	"「如何にも、我こそがこの帝国を支配する、レジーナその人である」",
	//// 選択２
	//	"「逆に何を焦る必要があるのだ？まさか貴様は私を追い詰めたつもりにでもなっているのか？」",
	//// 選択３
	//	"「・・・・・」",




	//	"「・・・問おう、貴様には２つの選択肢がある。」",
	//	"「一つは我に忠誠を誓い、我の配下となるか。」",
	//	"「一つは我に殺され、塵芥の如くここで朽ちて逝くか。」",

	//	"「どうだ、簡単だろう？」",
	//	"「当然働きによっては褒美もくれてやる、貴様には特別に幹部としての席を用意してやってもいい。もはや選ぶまでもなかろう？」",

	//	"・・なるほど、悪い提案ではない、か。",
	//	"今までこの理不尽な世界で散々自分の身を危険にさらして戦ってきた",
	//	"勇者なんだからそれは当然だと考えている人間が多くいるが、それは違う",
	//	"俺はただの平凡な人間なのだ、元々勇者なんてそんな立派なものなんかじゃない",
	//	"誰でもいいから本当の俺を認めて欲しい、そう思っていた",


		"「・・・そうだな、選ぶまでもない」",

		"「であろう？ならば早速----」",

		"「断る」",

		"「契約の儀を・・・何？」",

		"「悪いがその申し出は断る、ここで朽ち果てるのはお前の方だ」",

		"「・・・理解できんな、そこまで貴様は馬鹿だったのか？」",

		"「まぁそうだな、馬鹿ってのは否定しない。ただな、俺は誰かの指図を受けるのが嫌いなんだ」",

		"「俺は俺の生きたいように生きる、故にお前の配下にはならない」",

		"「そうか、それはすまなかったな。ならば・・・死ね」",
};

void LoadFuncButtons_Kingdom() {
	btnInfos_Kingdom = {

	{LoadGraph("graphics/TextButtons/TitleFuncBtn.png"),125,700,70,30,0.115f,0.14f},
	{LoadGraph("graphics/TextButtons/SkipFuncBtn.png"),295,700,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/saveFuncBtn.png"),465,700,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/logFuncBtn.png"),635,700,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/loadFuncBtn.png"),805,700,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/configFuncBtn.png"),975,700,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/autoFuncBtn.png"),1145,700,70,30,0.115f,0.15f}
	};
}

void ShowKingdomEventTextLog() {

	DrawRotaGraph(620, 125, 0.7f, 0.0f, kingdomEvent_BGhdl, true);


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		currentMess_Line++;
		currentMess_Line %= 110;


		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && 
			kingdomBattleTextLog[currentMess_Line] == "「そうか、それはすまなかったな。ならば・・・死ね」") {
			currentBattleState = 0;
			episodeNum = 5;
			g_scene_id = 5;
			currentMess_Line = 0;
		}
	}


	SetFontSize(20);
	DrawBox(0, 500, 1280, 800, GetColor(20, 20, 20), true);
	DrawFormatString(90, 550, -1, "%s", kingdomBattleTextLog[currentMess_Line].c_str());

	SetFontSize(35);
	DrawString(1070, 620, "Enter", -1);


	for (const auto& BTNFUNC_INFO_Kingdom : btnInfos_Kingdom) {
		ZoomBtnsOnMouseOver_Kingdom(BTNFUNC_INFO_Kingdom);
	}


}

void ZoomBtnsOnMouseOver_Kingdom(const FuncBtnsInfo& btnInfos_Kingdom) {
	DrawRotaGraph(btnInfos_Kingdom.x, btnInfos_Kingdom.y, 0.12f, 0.0f, btnInfos_Kingdom.handle, false);

}



// スキップボタン作ったら→ 　isShowSymbols = true;　　を追加
