#include <time.h>
#include <string>
#include <random>
#include "../dxlib_ext/dxlib_ext.h"
#include "time.h"
#include "JankenBattle.h"
#include "../map/FieldMap.h"
#include "../game/Main.h"
#include "DxLib.h"
#include <time.h>
#include "../episode/Prologue/PrologueEvent.h"
#include "../episode/Kingdom/Kingdom_Event.h"



class ResetException {};

void ResetFunction()
{
	throw ResetException();
}



// prototype
void InitMoveSlider();
void GetScoreOfSliderEvent();
void ReturnToMap();
void GameOverMenu();
void SceneChange();
void InitHP();
void Draw_BattleSceneBG();
void LoadSliderHandle();
void DrawBossEnemy(int x, int y, float exRate, float angle, int handle, bool translucency);
void InitBGM_phase();

//extern


bool showSymbols;

std::string GetGuString();
std::string GetChokiString();
std::string GetPaString();


// バトル中かバトル終了かを定義
enum {
	SLIDEREVENT,
	STILL_BATTLING,
	SHOWRESULT,
	ENDBATTLE,
	ONMAP,
	TITLE
};

// 戦闘画面の背景設定
enum {
	BG_CONTINENT,
	BG_FOREST,
	BG_VILLAGE,
	BG_CITY,
	BG_THEOCRACY,
	BG_KINGDOM,

};
int BG_Img = BG_CONTINENT;

// スライダーイベントの成績評価
enum {
	SLIDEREVE_PERFECT,
	SLIDEREVE_GREAT,
	SLIDEREVE_GOOD,
	SLIDEREVE_BAD,
	SLIDEREVE_MAX
};

// じゃんけんの結果を定義する定数
enum {
	RESULT_TYPE_WIN,
	RESULT_TYPE_LOSE,
	RESULT_TYPE_DRAW,
	RESULT_TYPE_MAX
};

// 手の種類を定義する定数
enum {
	HAND_TYPE_STONE,
	HAND_TYPE_SCISSORS,
	HAND_TYPE_PAPER,
	HAND_TYPE_MAX
};

enum {
	MENU_RETRY,
	MENU_RETURNMAP,
	MENU_BACKTITLE,
	MENU_MAX
};

const tnl::Vector3 GUCHOKIPA_HANDPOS_TBL[HAND_TYPE_MAX] = {
	{445, 550, 0},
	{610, 550, 0},
	{775, 550, 0}
};



const tnl::Vector3 RESULT_PLAYER_HAND_POS = { 300, 400, 0 };
const tnl::Vector3 RESULT_ENEMY_HAND_POS = { 900, 400, 0 };

const std::string resultMess_Str[RESULT_TYPE_MAX] = { "You Win", "You Lose", "  Draw  " };
const tnl::Vector3 RESULT_MESS_StrPos = { 600, 450, 0 };

const std::string startNextTurn_Str = "Alt to Next";
const tnl::Vector3 START_NEXTTURN_StrPos = { 500, 500, 0 };

const std::string predictable_Str = "Predictable Enemy's Hand";

std::string pressEnter_Str = "Press Enter";


std::string drawEnemyHandRandRate_StrArr[3];

int gu, choki, pa;
// Perfect 70%,20%,10%  // Great 50%,30%,20% // Good 40%,40%,20% // Bad 33%, 34%, 33%

int forestBG_hdl, villageBG_hdl, cityBG_hdl, theocracyBG_hdl, kingdomBG_hdl, continentBG_hdl;

int images[11];

int forestEnemy_Default;
int villageEnemy_Default, villageEnemy_OneHitD;
int cityEnemy_Default, cityEnemy_OneHitD, cityEnemy_TwoHitD;
int theocraEnemy_Default, theocraEnemy_OneHitD, theocraEnemy_TwoHitD, theocraEnemy_ThreeHitD;
int kingdomEnemy_Default, kingdomEnemy_OneHitD, kingdomEnemy_TwoHitD,
kingdomEnemy_ThreeHitD, kingdomEnemy_FourHitD;

int preparing_EnemyImg;

int V_EnemyHdlResult, C_EnemyHdlResult, T_EnemyHdlResult, K_EnemyHdlResult;


int currentBattleState = SLIDEREVENT;
int sliderEventScore = SLIDEREVE_PERFECT;
int menuSelect;
int g_gpc_cursor_hdl = 0;
int g_gpc_hand_hdls[HAND_TYPE_MAX];

int enemySelectedHand = HAND_TYPE_STONE;
int currentSelectPlayerHand = HAND_TYPE_STONE;
int jankenResult = RESULT_TYPE_DRAW;
tnl::Vector3 PLAYER_CURSOR_Pos = GUCHOKIPA_HANDPOS_TBL[currentSelectPlayerHand];

int episodeNum;


bool isMovingSlide = false, isShowStartTex = true, battleStartTex = true,
isShowEnterTex = false, haveShowNextTurnTex = true, isPlayerWin = false,
isShowGameOverMenu = false, isUsedFirstEnter = false, isSliderEventStopped = false,
firstTimeOnSpace = true, isShowSlider = true, isFirstRound_Slider = true,
isRetryGame = false;

int ep1BGM_phase = 0, ep2BGM_phase = 0, ep3BGM_phase = 0, ep4BGM_phase = 0, ep5BGM_phase = 0, ep6BGM_phase = 0;

void JankenBattle() {

	if (currentBattleState == SLIDEREVENT || currentBattleState == STILL_BATTLING || currentBattleState == SHOWRESULT) {
		if (episodeNum == 1) {
			switch (ep1BGM_phase)
			{
			case 0:
				PlaySoundMem(Ep1_BGM, DX_PLAYTYPE_LOOP);
				ep1BGM_phase = 1;
				break;
			case 1:
				break;
			}
		}
		if (episodeNum == 2) {
			switch (ep2BGM_phase)
			{
			case 0:
				PlaySoundMem(Ep2_BGM, DX_PLAYTYPE_LOOP);
				ep2BGM_phase = 1;
				break;
			case 1:
				break;
			}
		}
		if (episodeNum == 3) {
			switch (ep3BGM_phase)
			{
			case 0:
				PlaySoundMem(Ep3_BGM, DX_PLAYTYPE_LOOP);
				ep3BGM_phase = 1;
				break;
			case 1:
				break;
			}
		}
		if (episodeNum == 4) {
			switch (ep4BGM_phase)
			{
			case 0:
				PlaySoundMem(Ep4_BGM, DX_PLAYTYPE_LOOP);
				ep4BGM_phase = 1;
				break;
			case 1:
				break;
			}
		}
		if (episodeNum == 5) {
			switch (ep5BGM_phase)
			{
			case 0:
				PlaySoundMem(Ep5_BGM, DX_PLAYTYPE_LOOP);
				ep5BGM_phase = 1;
				break;
			case 1:
				break;
			}
		}
		if (episodeNum == 6) {
			switch (ep6BGM_phase)
			{
			case 0:
				PlaySoundMem(Ep6_BGM, DX_PLAYTYPE_LOOP);
				ep6BGM_phase = 1;
				break;
			case 1:
				break;
			}
		}
	}


	if (currentBattleState == ONMAP) {
		isShowSymbols = true;
		if (showMenu && onSelectEps) {
			isShowSymbols = false;
		}		
		ReturnToMap();
	}
	else if (currentBattleState == TITLE) {
		sceneTitle();
	}


	if (currentBattleState == SLIDEREVENT) {
		Draw_BattleSceneBG();

		if (isFirstRound_Slider == true) {
			// 戦闘開始時最初の1回だけ実行
			if (isShowStartTex == true && battleStartTex == true) {
				std::string battleStart = "Battle Start!";
				std::string pressSpace = "Press Space";


				isMovingSlide = false;
				SetFontSize(90);
				DrawFormatString(360, 250, -1, "%s", battleStart.c_str());
				if (isRetryGame != true) {
					SetFontSize(55);
					DrawFormatString(460, 400, -1, "%s", pressSpace.c_str());
				}
			}

			if (isRetryGame == true) {
				firstTimeOnSpace = false;
				std::string pressBack = "Press Back";
				SetFontSize(55);
				DrawFormatString(460, 400, -1, "%s", pressBack.c_str());
			}

			// スペースを押すとEnter が表示される
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && firstTimeOnSpace == true ||
				tnl::Input::IsKeyDownTrigger(eKeys::KB_BACK) && isRetryGame == true) {
				isShowStartTex = false;
				battleStartTex = false;
				isShowEnterTex = true;
				isRetryGame = false;
				PlaySoundMem(determineButtonSE, DX_PLAYTYPE_BACK);

			}

			// 1回目のスライダー起動
			if (isShowStartTex == false && battleStartTex == false && isFirstRound_Slider == true) {
				isShowSlider = true;
				isMovingSlide = true;
				firstTimeOnSpace = false;
			}
			// スライダー停止処理
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && isMovingSlide == true) {
				isShowEnterTex = false;
				isSliderEventStopped = true;
				PlaySoundMem(determineButtonSE, DX_PLAYTYPE_BACK);
			}
		}
		// 2回目以降のスライダー
		if (isFirstRound_Slider == false) {

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				isMovingSlide = true;// エンターキーが押されたらループを制御するフラグを切り替える
				isShowEnterTex = false;
				isSliderEventStopped = true;
				isShowSlider = true;
				PlaySoundMem(determineButtonSE, DX_PLAYTYPE_BACK);
			}
		}

		if (isSliderEventStopped == true) {
			// スライダーイベントの成績表示 ＆ 相手の出す手札の確率設定
			GetScoreOfSliderEvent();
			SetFontSize(55);
			DrawString(460, 400, "Press Shift", -1);
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LSHIFT) ||
				tnl::Input::IsKeyDownTrigger(eKeys::KB_RSHIFT)) {
				currentBattleState = STILL_BATTLING;
			}
		}
	}


	//------------------------------------------------------------------------------------------------------

	if (currentBattleState == STILL_BATTLING) {
		Draw_BattleSceneBG();


		if (isSliderEventStopped != true) {
			//ぐーちょきぱーの画像を表示ー＞そこに計算した各手の確率を表示
			SetFontSize(55);

			switch (sliderEventScore) {

			case SLIDEREVE_PERFECT:
				DrawString(460, 280, "PERFECT!", GetColor(255, 165, 0));
				break;
			case SLIDEREVE_GREAT:
				DrawString(490, 280, "GREAT!", GetColor(0, 240, 0));
				break;
			case SLIDEREVE_GOOD:
				DrawString(540, 280, "GOOD", GetColor(245, 245, 245));
				break;
			case SLIDEREVE_BAD:
				DrawString(570, 280, "BAD", GetColor(10, 10, 10));
				break;
			}
		}


		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
			currentSelectPlayerHand--;
			if (currentSelectPlayerHand < 0) currentSelectPlayerHand = HAND_TYPE_PAPER;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
			currentSelectPlayerHand++;
			if (currentSelectPlayerHand >= HAND_TYPE_MAX) currentSelectPlayerHand = HAND_TYPE_STONE;
		}
		PLAYER_CURSOR_Pos = GUCHOKIPA_HANDPOS_TBL[currentSelectPlayerHand];


		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			// CPU が手を選択
			enemySelectedHand = rand() % HAND_TYPE_MAX;

			// じゃんけんの勝敗判定
			if (currentSelectPlayerHand == HAND_TYPE_STONE) {
				if (enemySelectedHand == HAND_TYPE_SCISSORS) {
					jankenResult = RESULT_TYPE_WIN;
					enemyHP--;
				}
				if (enemySelectedHand == HAND_TYPE_PAPER) {
					jankenResult = RESULT_TYPE_LOSE;
					playerHP--;
				}
				if (enemySelectedHand == HAND_TYPE_STONE) {
					jankenResult = RESULT_TYPE_DRAW;
				}
			}
			if (currentSelectPlayerHand == HAND_TYPE_SCISSORS) {
				if (enemySelectedHand == HAND_TYPE_PAPER) {
					jankenResult = RESULT_TYPE_WIN;
					enemyHP--;
				}
				if (enemySelectedHand == HAND_TYPE_STONE) {
					jankenResult = RESULT_TYPE_LOSE;
					playerHP--;
				}
				if (enemySelectedHand == HAND_TYPE_SCISSORS) {
					jankenResult = RESULT_TYPE_DRAW;
				}
			}
			if (currentSelectPlayerHand == HAND_TYPE_PAPER) {
				if (enemySelectedHand == HAND_TYPE_STONE) {
					jankenResult = RESULT_TYPE_WIN;
					enemyHP--;
				}
				if (enemySelectedHand == HAND_TYPE_SCISSORS) {
					jankenResult = RESULT_TYPE_LOSE;
					playerHP--;
				}
				if (enemySelectedHand == HAND_TYPE_PAPER) {
					jankenResult = RESULT_TYPE_DRAW;
				}
			}

			isShowSlider = false;

			// 次のフレームからは結果表示シーケンス
			currentBattleState = SHOWRESULT;
		}

		// カーソル表示
		DrawRotaGraphF(PLAYER_CURSOR_Pos.x + 25, PLAYER_CURSOR_Pos.y + 165, 0.25f, 0, g_gpc_cursor_hdl, true);
		// ぐーちょきぱーの画像表示
		for (int i = 0; i < HAND_TYPE_MAX; ++i) {
			DrawRotaGraphF(GUCHOKIPA_HANDPOS_TBL[i].x, GUCHOKIPA_HANDPOS_TBL[i].y + 55, 0.5f, 0, g_gpc_hand_hdls[i], true);
		}


		if (isSliderEventStopped == true) {
			if (episodeNum == 1) {
				DrawBossEnemy(600, 240, 0.95f, 0.0f, forestEnemy_Default, true);
			}
			else if (episodeNum == 2) {
				switch (enemyHP) {
				case 2:
					V_EnemyHdlResult = villageEnemy_Default;
					break;
				case 1:
					V_EnemyHdlResult = villageEnemy_OneHitD;
					break;
				}
				DrawBossEnemy(600, 220, 0.95f, 0.0f, V_EnemyHdlResult, true);

			}
			else if (episodeNum == 3) {
				switch (enemyHP) {
				case 3:
					C_EnemyHdlResult = cityEnemy_Default;
					break;
				case 2:
					C_EnemyHdlResult = cityEnemy_OneHitD;
					break;
				case 1:
					C_EnemyHdlResult = cityEnemy_TwoHitD;
					break;
				}
				DrawBossEnemy(600, 240, 0.95f, 0.0f, C_EnemyHdlResult, true);

			}
			else if (episodeNum == 4) {
				switch (enemyHP) {
				case 4:
					T_EnemyHdlResult = theocraEnemy_Default;
					break;
				case 3:
					T_EnemyHdlResult = theocraEnemy_OneHitD;
					break;
				case 2:
					T_EnemyHdlResult = theocraEnemy_TwoHitD;
					break;
				case 1:
					T_EnemyHdlResult = theocraEnemy_ThreeHitD;
					break;
				}
				DrawBossEnemy(600, 230, 0.95f, 0.0f, T_EnemyHdlResult, true);

			}
			else if (episodeNum == 5) {
				switch (enemyHP) {
				case 5:
					K_EnemyHdlResult = kingdomEnemy_Default;
					break;
				case 4:
					K_EnemyHdlResult = kingdomEnemy_OneHitD;
					break;
				case 3:
					K_EnemyHdlResult = kingdomEnemy_TwoHitD;
					break;
				case 2:
					K_EnemyHdlResult = kingdomEnemy_ThreeHitD;
					break;
				case 1:
					K_EnemyHdlResult = kingdomEnemy_FourHitD;
					break;
				}
				DrawBossEnemy(600, 240, 0.95f, 0.0f, K_EnemyHdlResult, true);
			}
			else if (episodeNum == 6) {
				DrawBossEnemy(600, 240, 0.25f, 0.0f, preparing_EnemyImg, true);
			}
			isShowSlider = false;
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);

		DrawBox(0, 480, 1300, 685, 0, true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 手札画面
		SetFontSize(30);
		DrawFormatString(425, 450, 0xFFFF0000, predictable_Str.c_str(), true);
		SetFontSize(50);
		// 手札の確率String
		DrawFormatString(GUCHOKIPA_HANDPOS_TBL[0].x - 10, GUCHOKIPA_HANDPOS_TBL[0].y - 65, 0xFFFACD, GetGuString().c_str());
		DrawFormatString(GUCHOKIPA_HANDPOS_TBL[1].x - 10, GUCHOKIPA_HANDPOS_TBL[1].y - 65, 0xFFFACD, GetChokiString().c_str());
		DrawFormatString(GUCHOKIPA_HANDPOS_TBL[2].x - 10, GUCHOKIPA_HANDPOS_TBL[2].y - 65, 0xFFFACD, GetPaString().c_str());

		SetFontSize(30);
		DrawFormatString(50, 688, 0xFF800080, "PlayerHP:%d", playerHP);
		DrawFormatString(900, 20, 0xFF800080, "EnemyHP:%d", enemyHP);
	}


	//----------------------------------------------------------------------------------------------------

		// バトル終了後の処理
	else if (currentBattleState == SHOWRESULT) {
		Draw_BattleSceneBG();


		if (isSliderEventStopped == true) {
			if (episodeNum == 1) {
				DrawBossEnemy(600, 240, 0.95f, 0.0f, forestEnemy_Default, true);
			}
			else if (episodeNum == 2) {
				switch (enemyHP) {
				case 2:
					V_EnemyHdlResult = villageEnemy_Default;
					break;
				case 1:
					V_EnemyHdlResult = villageEnemy_OneHitD;
					break;
				}
				DrawBossEnemy(600, 220, 0.95f, 0.0f, V_EnemyHdlResult, true);

			}
			else if (episodeNum == 3) {
				switch (enemyHP) {
				case 3:
					C_EnemyHdlResult = cityEnemy_Default;
					break;
				case 2:
					C_EnemyHdlResult = cityEnemy_OneHitD;
					break;
				case 1:
					C_EnemyHdlResult = cityEnemy_TwoHitD;
					break;
				}
				DrawBossEnemy(600, 240, 0.95f, 0.0f, C_EnemyHdlResult, true);

			}
			else if (episodeNum == 4) {
				switch (enemyHP) {
				case 4:
					T_EnemyHdlResult = theocraEnemy_Default;
					break;
				case 3:
					T_EnemyHdlResult = theocraEnemy_OneHitD;
					break;
				case 2:
					T_EnemyHdlResult = theocraEnemy_TwoHitD;
					break;
				case 1:
					T_EnemyHdlResult = theocraEnemy_ThreeHitD;
					break;
				}
				DrawBossEnemy(600, 230, 0.95f, 0.0f, T_EnemyHdlResult, true);

			}
			else if (episodeNum == 5) {
				switch (enemyHP) {
				case 5:
					K_EnemyHdlResult = kingdomEnemy_Default;
					break;
				case 4:
					K_EnemyHdlResult = kingdomEnemy_OneHitD;
					break;
				case 3:
					K_EnemyHdlResult = kingdomEnemy_TwoHitD;
					break;
				case 2:
					K_EnemyHdlResult = kingdomEnemy_ThreeHitD;
					break;
				case 1:
					K_EnemyHdlResult = kingdomEnemy_FourHitD;
					break;
				}
				DrawBossEnemy(600, 240, 0.95f, 0.0f, K_EnemyHdlResult, true);
			}
			else if (episodeNum == 6) {
				DrawBossEnemy(600, 240, 0.25f, 0.0f, preparing_EnemyImg, true);
			}
		}

		DrawRotaGraphF(RESULT_ENEMY_HAND_POS.x + 55, RESULT_ENEMY_HAND_POS.y - 15, 0.5f, 0, g_gpc_hand_hdls[enemySelectedHand], true);
		DrawRotaGraphF(RESULT_PLAYER_HAND_POS.x - 30, RESULT_PLAYER_HAND_POS.y - 15, 0.5f, 0, g_gpc_hand_hdls[currentSelectPlayerHand], true);

		SetFontSize(30);
		DrawStringEx(RESULT_ENEMY_HAND_POS.x + 45, RESULT_ENEMY_HAND_POS.y + 50, -1, "ENEMY");
		DrawStringEx(RESULT_PLAYER_HAND_POS.x - 50, RESULT_PLAYER_HAND_POS.y + 50, -1, "PLAYER");

		if (haveShowNextTurnTex) {
			SetFontSize(70);
			DrawStringEx(490, 400, -1, resultMess_Str[jankenResult].c_str());
		}


		SetFontSize(DEFAULT_FONT_SIZE);


		if (playerHP != 0 && enemyHP != 0) {
			haveShowNextTurnTex = true;

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LALT) || tnl::Input::IsKeyDownTrigger(eKeys::KB_RALT)) {
				isShowEnterTex = true;
				isSliderEventStopped = false;

				haveShowNextTurnTex = false;
				isFirstRound_Slider = false;
				currentBattleState = SLIDEREVENT;

			}
		}
		if (playerHP != 0 && enemyHP == 0) {
			haveShowNextTurnTex = false;
			isPlayerWin = true;

			SetFontSize(70);
			DrawString(460, 400, "Game Clear", -1, true);
			SetFontSize(55);
			DrawString(530, 490, "Enter", -1, true);
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				isShowSymbols = true;
				isShowEnterTex = false;
				isSliderEventStopped = false;
				isShowStartTex = true;
				battleStartTex = true;
				isFirstRound_Slider = true;
				firstTimeOnSpace = true;

				if (showMenu && onSelectEps) {
					isShowSymbols = false;
				}
				ReturnToMap();

				currentBattleState = ENDBATTLE;
			}
		}
		if (playerHP == 0 && enemyHP != 0) {
			haveShowNextTurnTex = false;
			isPlayerWin = false;

			SetFontSize(70);
			DrawString(480, 400, "Game Over", -1, true);
			DrawString(530, 490, "Enter", -1, true);

			if (!isUsedFirstEnter && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				currentBattleState = ENDBATTLE;

				isUsedFirstEnter = true;
				isShowGameOverMenu = true;
			}
			if (isShowGameOverMenu == true) {
				ClearDrawScreen();

				GameOverMenu();
			}
		}

		if (haveShowNextTurnTex) {
			SetFontSize(50);
			DrawString(START_NEXTTURN_StrPos.x, START_NEXTTURN_StrPos.y, startNextTurn_Str.c_str(), -1);
		}

		SetFontSize(30);
		DrawFormatString(50, 688, 0xFF800080, "PlayerHP:%d", playerHP);
		DrawFormatString(900, 20, 0xFF800080, "EnemyHP:%d", enemyHP);
	}


	if (currentBattleState == ENDBATTLE) {
		if (isPlayerWin == true) {
			ReturnToMap();
		}
		else {
			GameOverMenu();
			SetFontSize(45);
			DrawString(1070, 640, "Space", -1);
		}
	}
}


typedef struct {
	int x, y;       // 座標格納用変数
	char name[128]; // 項目名格納用変数
} MenuElement_t;

MenuElement_t gameOverMenuItems[] = {
	{80,150,"リトライ"},
	{100,300,"マップにもどる"},
	{100,450,"タイトル画面にもどる"}
};



void GameOverMenu() {
	Draw_BattleSceneBG();

	int determineButtonSE = LoadSoundMem("SoundItem/SE/determineButton.mp3");


	for (int i = 0; i < MENU_MAX; i++) {
		DrawFormatString(gameOverMenuItems[i].x, gameOverMenuItems[i].y, GetColor(255, 255, 255), "・ %s", gameOverMenuItems[i].name);
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		menuSelect = (menuSelect + (MENU_MAX - 1)) % MENU_MAX;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		menuSelect = (menuSelect + 1) % MENU_MAX;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) == 1 || tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) == 1) {
		for (int i = 0; i < MENU_MAX; i++) {
			if (i == menuSelect) {
				gameOverMenuItems[i].x = 90;
			}
			else {
				gameOverMenuItems[i].x = 110;
			}
		}
	}

	if (menuSelect == 0) menuSelect = MENU_RETRY;
	if (menuSelect == 1) menuSelect = MENU_RETURNMAP;
	if (menuSelect == 2) menuSelect = MENU_BACKTITLE;


	if (isUsedFirstEnter && tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {

		switch (menuSelect)
		{
		case MENU_RETRY:
			isShowGameOverMenu = false;
			isShowStartTex = true;
			battleStartTex = true;
			isFirstRound_Slider = true;
			isSliderEventStopped = false;
			isRetryGame = true;
			firstTimeOnSpace = true;

			InitBGM_phase();

			currentBattleState = SLIDEREVENT;
			InitHP();
			JankenBattle();
			break;
		case MENU_RETURNMAP:
			isShowGameOverMenu = false;
			isShowStartTex = true;
			battleStartTex = true;
			isFirstRound_Slider = true;
			isSliderEventStopped = false;
			firstTimeOnSpace = true;

			InitBGM_phase();
			InitHP();

			currentBattleState = ONMAP;

			break;
		case MENU_BACKTITLE:
			isShowGameOverMenu = false;
			isShowStartTex = true;
			battleStartTex = true;
			isFirstRound_Slider = true;
			isSliderEventStopped = false;
			firstTimeOnSpace = true;

			InitBGM_phase();
			InitHP();

			currentBattleState = TITLE;

			break;
		}
		isUsedFirstEnter = false;
		PlaySoundMem(determineButtonSE, DX_PLAYTYPE_BACK);
	}
}

void InitBGM_phase() {

	ep1BGM_phase = 0;
	ep2BGM_phase = 0;
	ep3BGM_phase = 0;
	ep4BGM_phase = 0;
	ep5BGM_phase = 0;
	ep6BGM_phase = 0;

	StopSoundMem(Ep1_BGM);
	StopSoundMem(Ep2_BGM);
	StopSoundMem(Ep3_BGM);
	StopSoundMem(Ep4_BGM);
	StopSoundMem(Ep5_BGM);
	StopSoundMem(Ep6_BGM);

}

void InitHP() {
	switch (episodeNum)
	{
	case 1: // Forest
		playerHP = 6;
		enemyHP = 1;
		break;
	case 2: // Village
		playerHP = 5;
		enemyHP = 2;
		break;
	case 3: // City
		playerHP = 4;
		enemyHP = 3;
		break;
	case 4: // Theocracy
		playerHP = 3;
		enemyHP = 4;
		break;
	case 5: // Kingdom
		playerHP = 2;
		enemyHP = 5;
		break;
	case 6: // Continent
		playerHP = 1;
		enemyHP = 6;
		break;
	}
}

void ReturnToMap() {
	FlashSymbolAndMap(1);
}


void LoadSliderHandle() {
	const int imgTotalNum = 11;

	for (int i = 0; i < imgTotalNum; ++i) {
		char fileName[40];
		sprintf_s(fileName, "graphics/SliderBar/Bar%d.png", i + 1);
		images[i] = LoadGraph(fileName);
	}
}

void MoveSliderPerFrame(float deltaTime) {
	const int imgTotalNum = 11;

	anim_time_count += deltaTime;
	if (anim_time_count > 0.1f) {
		anim_ctrl_frame++;
		anim_ctrl_frame %= 11;

		anim_time_count = 0;
	}

	DrawRotaGraph(620, 380, 0.75f, 0, images[anim_ctrl_frame], true);
}

void GetScoreOfSliderEvent() {


	if (images[anim_ctrl_frame] == images[0]) {
		sliderEventScore = SLIDEREVE_PERFECT;
	}
	else if (images[anim_ctrl_frame] == images[1]
		|| images[anim_ctrl_frame] == images[2]
		|| images[anim_ctrl_frame] == images[3]) {
		sliderEventScore = SLIDEREVE_GREAT;
	}
	else if (images[anim_ctrl_frame] == images[4]
		|| images[anim_ctrl_frame] == images[5]
		|| images[anim_ctrl_frame] == images[6]) {
		sliderEventScore = SLIDEREVE_GOOD;
	}
	else {
		sliderEventScore = SLIDEREVE_BAD;
	}

	std::vector<int> randomRateAry_Perfect = { 70,20,10 };
	std::vector<int> randomRateAry_Great = { 50,30,20 };
	std::vector<int> randomRateAry_Good = { 40,40,20 };
	std::vector<int> randomRateAry_Bad = { 34,33,33 };

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> rateDistribution(1, 10);
	int randomValue = rateDistribution(gen);

	// Perfect
	std::shuffle(randomRateAry_Perfect.begin(), randomRateAry_Perfect.end(), gen);

	// Great
	std::shuffle(randomRateAry_Great.begin(), randomRateAry_Great.end(), gen);

	// Good
	std::shuffle(randomRateAry_Good.begin(), randomRateAry_Good.end(), gen);

	// Bad
	std::shuffle(randomRateAry_Bad.begin(), randomRateAry_Bad.end(), gen);

	// スコアによって相手の手札の出る確率をそれぞれ計算
	switch (sliderEventScore) {
		SetFontSize(45);

	case SLIDEREVE_PERFECT:

		gu = randomRateAry_Perfect[0];
		choki = randomRateAry_Perfect[1];
		pa = randomRateAry_Perfect[2];


		DrawString(480, 280, "PERFECT!", GetColor(255, 165, 0));
		break;
	case SLIDEREVE_GREAT:
		gu = randomRateAry_Great[0];
		choki = randomRateAry_Great[1];
		pa = randomRateAry_Great[2];


		DrawString(500, 280, "GREAT!", GetColor(0, 240, 0));
		break;
	case SLIDEREVE_GOOD:
		gu = randomRateAry_Good[0];
		choki = randomRateAry_Good[1];
		pa = randomRateAry_Good[2];


		DrawString(560, 280, "GOOD", GetColor(245, 245, 245));
		break;
	case SLIDEREVE_BAD:
		gu = randomRateAry_Bad[0];
		choki = randomRateAry_Bad[1];
		pa = randomRateAry_Bad[2];

		DrawString(560, 280, "BAD", GetColor(245, 245, 245));
		break;
	}

	for (int i = 0; i < 3; i++) {
		drawEnemyHandRandRate_StrArr[0] = std::to_string(gu);
		drawEnemyHandRandRate_StrArr[1] = std::to_string(choki);
		drawEnemyHandRandRate_StrArr[2] = std::to_string(pa);
	}
}

std::string GetGuString()
{
	return drawEnemyHandRandRate_StrArr[0];
}

std::string GetChokiString()
{
	return drawEnemyHandRandRate_StrArr[1];
}

std::string GetPaString()
{
	return drawEnemyHandRandRate_StrArr[2];
}



// Perfect 70%,20%,10%    // Great 50%,30%,20%     // Good 40%,40%,20%    // Bad 33%, 34%, 33%

// Main.cppのgameStart()で呼び出し
void LoadGraphics() {

	g_gpc_cursor_hdl = LoadGraph("graphics/cursor.png");
	g_gpc_hand_hdls[HAND_TYPE_STONE] = LoadGraph("graphics/stone.png");
	g_gpc_hand_hdls[HAND_TYPE_SCISSORS] = LoadGraph("graphics/scissors.png");
	g_gpc_hand_hdls[HAND_TYPE_PAPER] = LoadGraph("graphics/paper.png");

}

void BattleBG_Handle() {
	forestBG_hdl = LoadGraph("graphics/BattleScene/Forest.png");
	villageBG_hdl = LoadGraph("graphics/BattleScene/Village.png");
	cityBG_hdl = LoadGraph("graphics/BattleScene/City.png");
	theocracyBG_hdl = LoadGraph("graphics/BattleScene/Theocracy.png");
	kingdomBG_hdl = LoadGraph("graphics/BattleScene/Kingdom.png");
	continentBG_hdl = LoadGraph("graphics/BattleScene/Continent.png");
}


void LoadEnemyImage() {
	forestEnemy_Default = LoadGraph("graphics/キャラクター素材/Forest_Enemy/デフォルト.png");
	villageEnemy_Default = LoadGraph("graphics/キャラクター素材/Village_Enemy/デフォルト.png");
	villageEnemy_OneHitD = LoadGraph("graphics/キャラクター素材/Village_Enemy/oneHit.png");
	cityEnemy_Default = LoadGraph("graphics/キャラクター素材/City_Enemy/デフォルト.png");
	cityEnemy_OneHitD = LoadGraph("graphics/キャラクター素材/City_Enemy/oneHit.png");
	cityEnemy_TwoHitD = LoadGraph("graphics/キャラクター素材/City_Enemy/twoHit.png");
	theocraEnemy_Default = LoadGraph("graphics/キャラクター素材/Theocracy_Enemy/デフォルト.png");
	theocraEnemy_OneHitD = LoadGraph("graphics/キャラクター素材/Theocracy_Enemy/oneHit.png");
	theocraEnemy_TwoHitD = LoadGraph("graphics/キャラクター素材/Theocracy_Enemy/twoHit.png");
	theocraEnemy_ThreeHitD = LoadGraph("graphics/キャラクター素材/Theocracy_Enemy/threeHit.png");
	kingdomEnemy_Default = LoadGraph("graphics/キャラクター素材/Kingdom_Enemy/デフォルト.png");
	kingdomEnemy_OneHitD = LoadGraph("graphics/キャラクター素材/Kingdom_Enemy/oneHit.png");
	kingdomEnemy_TwoHitD = LoadGraph("graphics/キャラクター素材/Kingdom_Enemy/twoHit.png");
	kingdomEnemy_ThreeHitD = LoadGraph("graphics/キャラクター素材/Kingdom_Enemy/threeHit.png");
	kingdomEnemy_FourHitD = LoadGraph("graphics/キャラクター素材/Kingdom_Enemy/fourHit.png");

	preparing_EnemyImg = LoadGraph("graphics/キャラクター素材/Continent_Enemy/4_2.png");
}


void DrawBossEnemy(int x, int y, float exRate, float angle, int handle, bool translucency) {

	DrawRotaGraph(x, y, exRate, angle, handle, translucency);
}

void Draw_BattleSceneBG() {
	if (episodeNum == 1) {
		DrawGraph(0, 0, forestBG_hdl, false);
	}
	else if (episodeNum == 2) {
		DrawRotaGraph(15, 15, 1.0f, 0, villageBG_hdl, false);
	}
	else if (episodeNum == 3) {
		DrawRotaGraph(635, 0, 1.5f, 0, cityBG_hdl, false);
	}
	else if (episodeNum == 4) {
		DrawGraph(-370, 0, theocracyBG_hdl, false);
	}
	else if (episodeNum == 5) {
		DrawRotaGraph(635, 400, 1.5f, 0, kingdomBG_hdl, false);
	}
	else if (episodeNum == 6) {
		DrawRotaGraph(500, 400, 1.0f, 0, continentBG_hdl, false);
	}
}