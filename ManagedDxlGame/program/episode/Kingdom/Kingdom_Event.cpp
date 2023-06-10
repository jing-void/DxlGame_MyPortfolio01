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
void AddClickFuncOnBtns_Kingdom(const FuncBtnsInfo& btnInfos_Kingdom);
void DrawRegina(int regina);

extern int episodeNum;
int currentMess_Line = 0;
int titleFuncBtn, skipFuncBtn, saveFuncBtn, logFuncBtn, loadFuncBtn, configFuncBtn, autoFuncBtn;
int add_TextNum = 2;
int str_Count = 0;
int clickX_axi, clickY_axi;
bool hitEnd;
bool startFinalBattle;
bool isReginaTalkTurn_alpha;

float btnSize;

std::string receiveKingdomText[90];

std::string kingdomBattleTextLog[90] = {


	"ついにここまで来た。",

	 "最後の戦いを前にして思いを馳せる。",

	"思い返せば決して楽な道ではなかった。",

	"目が覚めたら訳のわからないところにいて、突然「あなたは死にました」とか言われるし。\nその上勇者とかいう荷が重すぎる役目を背負わされるし。",

	"正直自分を抱きしめてやりたいほど、俺はよくやってると思う。",

		"(・・・はぁ)",

	"今の状況について流石に慣れはしたが、結局のところ理解は全くしていない。未だに意味不明だ。",

	"あれからどれくらい経ったのだろう。",

	"一月前のような気もするし、下手をすればもう半年くらい経過しているのかもしれない。",

	"とにかく俺はこの世界で生き延びることに只々必死だった。",

	"今迄だって別にこの国を救うために戦っていたわけではなく、単に身に降りかかる火の粉を払って\nきただけで、ここに辿り着いたのも成り行きだと思っている。",

	"(異世界転生って言ったら何というかもっとこう・・・・充実しているイメージがあったんだけどな)",

	"例えば俺には旅を共にする仲間がいない。ゲームだと最初は一人ぼっちだが、物語が進んでいくにつれて\n大抵は仲間が増えていく。俺にはそんな仲間がいないのだ。",

	"他には異能力も捨てがたい。女神から異能の力は授かっているものの、実際に戦いを経験して感じたのは\nもっと実践に向いた能力があったのではないか、ということ。",

	"『魔拳』は運に依拠している部分が大きい。自分が有利になるためにある程度の運を捻じ曲げることは出来るが、\nそれは絶対ではない。時には失敗もするし、不利な状況に陥ったことも何度かあった。",

	"故にこの能力については色々疑念を抱いているのだが、もしかすると他にまだ俺が知らない何かがあるのだろうか？",
	
	"・・・・いや、いくら考えたところで答えなど出て来ない。",

	"(これはあくまでも現実なんだ)",

	"折角異世界に来たというのに、今のところ楽しいことが一つもない。これは何かのバグか？",

	"「ふふ」",

	"そうして物思いにふけっていると、ふいに笑い声のようなものが聞こえた。",
	
	"俺は辺りを見渡し、やがて視界の端に一つの人影のようなものを確認する。",

	"「・・・よくぞここまで来た、我が思想に害をなそうとする下賤な人の子よ」",

	"？",

	"そう言いながら人影はこちらに向かって歩みを始める。",

	"コツコツコツ、と妙に規則正しいその足音はどこか薄気味悪い。",

	"また敵か・・・。",

	"もう毎度お馴染みのことではあるが、嫌なものはそれが例え何回目だろうと絶対に嫌なのである。",

	"やがて人影は眼前で歩みを止め-----------俺は言葉を失った。",

	"・・・・・・・美しい。",

	"腰まで伸びた長い髪、透き通るような大きな瞳、蜜のように甘い声。",
	
	"あっという間に俺は目の前の悪魔(？)から目を離すことが出来なくなっていた。",
	
	"もはやどう表現するのが正解なのか不明なほどの魅力を、俺は目の前の敵に感じてしまっていたのだ。",

	"しかしこれほどのオーラ、恐らく話に聞いていた『レジーナ』という最終目標で間違いないだろう。",

	"「あんたが『レジーナ』・・・だな？」",

	"「如何にも、我こそがこの帝国を支配する、レジーナその人である」",

	"「そうか・・・・随分余裕そうだな」",

	"別に自慢ではないが、一応俺も伊達に勇者をやってきたわけではない。数々の戦場を乗り越えその敵を屠ってきた。\nそれを知らないはずがないと思うのだが・・・",
	
    "するとレジーナは心の底から不思議そうに首をかしげ、答える。",
	
	"「逆に何を焦る必要があるのだ？まさか貴様は私を追い詰めたつもりにでもなっているのか？」",

		"「・・・・・・はぁー」",

		"心底呆れた、という感情が彼女のため息に乗って伝わってくる。明らかになめられているようだったが、\n俺はそれを不快に感じなかった。",	
		
		"レジーナの言葉や仕草、更にはその冷徹な表情まで、あらゆる点に於いてその立ち振る舞いはまさしく\n王そのものだ。",

		"俺はそんな彼女に驚くほど夢中になっていた。それはもう怒りを覚えることすら忘れる程にだ。",

		"「問おう、貴様には今２つの選択肢がある」",

		"指を２本立て、それをこちら側へと向ける。",

		"「一つは我に忠誠を誓い、我の配下となるか」",

		"「一つは我に殺され、塵芥の如くここで朽ちて逝くか」",

		"「当然働きによっては褒美もくれてやるし、貴様には特別な席を用意してやってもいいと思っている。\nどうだ、もはや選ぶまでもなかろう？」",

		"・・・なるほど、悪い提案ではないと思った。",

		"今までこの理不尽な世界で散々自分の身を危険に晒して戦ってきた。",

		"勇者だとか言って持て囃され、今や俺が戦うのも勇者なんだから当然だと多くの人が思っている。",

		"しかし俺は元々はただの平凡な人間だ。ここまで来て確かに強くはなったが、心まで変化したわけではない。",

		"別に俺は人々の役に立ちたいとか、国を守りたいといったような立派な志など最初から持ち合わせては\nいなかったのだ。",

		"「・・・そうだな、選ぶまでもない」",

		"「であろう？ならば早速----」",

		"「断る」",

		"「契約の儀を・・・何？」",

		"「悪いがその申し出は断る」",

		"「・・・聞き間違いか？貴様、我の申し出を断る、そう言ったのか？」",

		"頷いてみせると、脱力したように天を見上げ、レジーナは再度深く息を吐いた。",

		"「・・・理解できん、貴様はそこまでの馬鹿だったのか？」",

		"「まぁ・・・馬鹿ってのは否定しないけどな。ただ、俺はあんたのその王者たる風格に惚れたんだ。\nだから俺もあんたの様に自由に生きたいと思った、それだけだ」",

		"「ほざけ・・・分かっているのか？今貴様がしようとしているのは自殺と何も変わらぬ、愚かな選択よ」",

		"「違うな、俺が選んだのは屈服でも降参でもない『第３の選択』だ」",

		"「第３の選択？」",

		"今迄勇者勇者と散々こき使われ続けて来てやったんだ、後はせいぜい俺のやりたいようにやらせてもらおう。",

		"「----俺がお前を支配してやる」",

		"「は？」",

		"まるで鳩が豆鉄砲を食ったような顔で彼女は静止した。",

		"「要は人々にとっての脅威を取り除いてやればいい。それだったら『支配』でも問題ない。そもそも\n『殺せ』と明確に依頼されたわけじゃないしな」",

		"「ふ、・・・ははっ！」",

		"初めて彼女が俺に笑顔を見せた。その笑顔が俺の支配欲に更に火を付ける。",

		"「・・・もうよい」",

		"先程までの笑顔が幻だったかのように彼女の表情が変わり、場の空気が変わった。瞬時に体制を整え\n右手を構える。",

		"「ならばやってみろ、矮小なる人間風情が！！」",

	"バトル開始",
};

void LoadFuncButtons_Kingdom() {
	btnInfos_Kingdom = {

	{LoadGraph("graphics/TextButtons/TitleFuncBtn.png"),125,700,70,30,0.115f,0.14f},
	{LoadGraph("graphics/TextButtons/loadFuncBtn.png"),295,700,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/saveFuncBtn.png"),465,700,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/autoFuncBtn.png"),635,700,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/SkipFuncBtn.png"),805,700,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/logFuncBtn.png"),975,700,70,30,0.115f,0.15f},
	{LoadGraph("graphics/TextButtons/configFuncBtn.png"),1145,700,70,30,0.115f,0.15f},
	};
}

void ShowKingdomEventTextLog() {

	DrawRotaGraph(620, 125, 0.7f, 0.0f, kingdomEvent_BGhdl, true);



	for (int i = 0; i < 90; ++i) {
		receiveKingdomText[i] = kingdomBattleTextLog[i];
	}
	if (currentMess_Line < 90) {
		receiveKingdomText[currentMess_Line] = kingdomBattleTextLog[currentMess_Line].substr(0, str_Count);
	}

	if (kingdomBattleTextLog[currentMess_Line].length() > str_Count) {
		str_Count += add_TextNum;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && (kingdomBattleTextLog[currentMess_Line].length() <= str_Count)) {
		currentMess_Line++;
		str_Count = 0;
	}

	if (kingdomBattleTextLog[currentMess_Line] == "バトル開始") {
		receiveKingdomText[currentMess_Line] = "";
		currentBattleState = 0;
		episodeNum = 5;
		g_scene_id = 5;
		currentMess_Line = 0;
	}



	// プレイヤートークターン
	if (currentMess_Line == 5 || currentMess_Line == 11 || currentMess_Line == 17 || currentMess_Line == 23
		|| currentMess_Line == 34 || currentMess_Line == 36 || currentMess_Line == 54 || currentMess_Line == 56
		|| currentMess_Line == 58 || currentMess_Line == 62 || currentMess_Line == 64 || currentMess_Line == 67	|| currentMess_Line == 70) {

		isPlayerTalkTurn_alpha = true;
	}
	else {
		isPlayerTalkTurn_alpha = false;
	}


	if (currentMess_Line >= 19 && currentMess_Line <= 34) {
		DrawRegina(kingdomEnemy_secret);
	}

	

	// レジーナトークターン

	if (currentMess_Line >= 35 && currentMess_Line <= 39) {
		DrawRegina(kingdomEnemy_OneHitD);
	}
	if (currentMess_Line >= 40 && currentMess_Line <= 43) {
		DrawRegina(kingdomEnemy_Default);
	}
	if (currentMess_Line >= 44 && currentMess_Line <= 54) {
		DrawRegina(kingdomEnemy_OneHitD);
	}
	if (currentMess_Line >= 55 && currentMess_Line <= 56) {
		DrawRegina(kingdomEnemy_smile);
	}
	if (currentMess_Line >= 57 && currentMess_Line <= 58) {
		DrawRegina(kingdomEnemy_Default);
	}
	if (currentMess_Line >= 59 && currentMess_Line <= 70) {
		DrawRegina(kingdomEnemy_OneHitD);
	}
	if (currentMess_Line >= 71 && currentMess_Line <= 72) {
		DrawRegina(kingdomEnemy_TwoHitD);
	}
	if (currentMess_Line >= 73 && currentMess_Line <= 74) {
		DrawRegina(kingdomEnemy_OneHitD);
	}
	if (currentMess_Line >= 75) {
		DrawRegina(kingdomEnemy_FourHitD);
	}


	if (currentMess_Line == 35 || currentMess_Line == 39 || currentMess_Line == 40
		|| currentMess_Line == 44 || currentMess_Line == 46 || currentMess_Line == 47
		|| currentMess_Line == 48 || currentMess_Line == 55 || currentMess_Line == 57
		|| currentMess_Line == 59 || currentMess_Line == 61 || currentMess_Line == 63
		|| currentMess_Line == 65 || currentMess_Line == 67 || currentMess_Line == 71
		|| currentMess_Line == 73 || currentMess_Line == 75) {

		isReginaTalkTurn_alpha = true;
	}
	else {
		isReginaTalkTurn_alpha = false;
	}



	DrawWholePlayer();
	
	SetDrawBright(255, 255, 255);

	SetFontSize(20);
	DrawBox(0, 500, 1280, 800, GetColor(20, 20, 20), true);



	SetFontSize(20);
	DrawStringEx(90, 550, -1, "%s", receiveKingdomText[currentMess_Line].c_str());

	SetFontSize(35);
	DrawString(1070, 620, "Enter", -1);




	for (const auto& BTNFUNC_INFO_Kingdom : btnInfos_Kingdom) {
		ZoomBtnsOnMouseOver_Kingdom(BTNFUNC_INFO_Kingdom);
		AddClickFuncOnBtns_Kingdom(BTNFUNC_INFO_Kingdom);
	}
}

void ZoomBtnsOnMouseOver_Kingdom(const FuncBtnsInfo& btnInfos_Kingdom) {
	int hoveredX, hoveredY;
	float scaleSize;

	GetMousePoint(&hoveredX, &hoveredY);

	if (hoveredX >= btnInfos_Kingdom.x && hoveredX <= btnInfos_Kingdom.x + btnInfos_Kingdom.width &&
		hoveredY >= btnInfos_Kingdom.y && hoveredY <= btnInfos_Kingdom.y + btnInfos_Kingdom.height) {
		btnSize = btnInfos_Kingdom.zoomSize;
	}
	else {
		btnSize = btnInfos_Kingdom.normalSize;
	}

	DrawRotaGraph(btnInfos_Kingdom.x, btnInfos_Kingdom.y, btnSize, 0.0f, btnInfos_Kingdom.handle, false);
}

void AddClickFuncOnBtns_Kingdom(const FuncBtnsInfo& btnInfos_Kingdom) {
	GetMousePoint(&clickX_axi, &clickY_axi);

	if (GetMouseInput() && MOUSE_INPUT_LEFT) {

		if (clickX_axi >= btnInfos_Kingdom.x && clickX_axi <= btnInfos_Kingdom.x + btnInfos_Kingdom.width && 
			clickY_axi >= btnInfos_Kingdom.y && clickY_axi <= btnInfos_Kingdom.y + btnInfos_Kingdom.height) {
			// TITLEボタン
			if (btnInfos_Kingdom.x >= TITLE_BTNFUNC_POS.x && btnInfos_Kingdom.x <= TITLE_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= TITLE_BTNFUNC_POS.y && btnInfos_Kingdom.y <= TITLE_BTNFUNC_POS.y + btnInfos_Kingdom.height) {
				g_scene_id = 3;  // SCENE_ID_TITLE
			}
			// LOADボタン
			if (btnInfos_Kingdom.x >= LOAD_BTNFUNC_POS.x && btnInfos_Kingdom.x <= LOAD_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= LOAD_BTNFUNC_POS.y && btnInfos_Kingdom.y <= LOAD_BTNFUNC_POS.y + btnInfos_Kingdom.height) {

			}
			// SAVEボタン
			if (btnInfos_Kingdom.x >= SAVE_BTNFUNC_POS.x && btnInfos_Kingdom.x <= SAVE_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= SAVE_BTNFUNC_POS.y && btnInfos_Kingdom.y <= SAVE_BTNFUNC_POS.y + btnInfos_Kingdom.height) {

			}
			// AUTOボタン
			if (btnInfos_Kingdom.x >= AUTO_BTNFUNC_POS.x && btnInfos_Kingdom.x <= AUTO_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= AUTO_BTNFUNC_POS.y && btnInfos_Kingdom.y <= AUTO_BTNFUNC_POS.y + btnInfos_Kingdom.height) {
				currentMess_Line++;
				//autoText = !autoText;
			}
			// SKIPボタン
			if (btnInfos_Kingdom.x >= SKIP_BTNFUNC_POS.x && btnInfos_Kingdom.x <= SKIP_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= SKIP_BTNFUNC_POS.y && btnInfos_Kingdom.y <= SKIP_BTNFUNC_POS.y + btnInfos_Kingdom.height) {
				isShowSymbols = true;
				currentBattleState = 0;
				episodeNum = 5;
				g_scene_id = 5;
				currentMess_Line = 0;
			}
			// LOGボタン
			if (btnInfos_Kingdom.x >= LOG_BTNFUNC_POS.x && btnInfos_Kingdom.x <= LOG_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= LOG_BTNFUNC_POS.y && btnInfos_Kingdom.y <= LOG_BTNFUNC_POS.y + btnInfos_Kingdom.height) {

			}
			// CONFIGボタン
			if (btnInfos_Kingdom.x >= CONFIG_BTNFUNC_POS.x && btnInfos_Kingdom.x <= CONFIG_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= CONFIG_BTNFUNC_POS.y && btnInfos_Kingdom.y <= CONFIG_BTNFUNC_POS.y + btnInfos_Kingdom.height) {

			}
		}
	}
}


void DrawRegina(int regina) {
	if (isReginaTalkTurn_alpha == true) {
		SetDrawBright(255, 255, 255);
	}
	else {
		SetDrawBright(160, 160, 160);
	}

	DrawRotaGraph(1050, 435, 0.8f, 0.0f, regina, true);
}