#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "Main.h"
#include "DxLib.h"
#include "../episode/Prologue/PrologueEvent.h"
#include "../episode/Kingdom/Kingdom_Event.h"
#include "time.h"
#include "../janken/JankenBattle.h"
#include "../map/FieldMap.h"


// prototype
void sceneTitle(float delta_time);
//-------------------------------------------------------------------------------------
using namespace::std;

// シーン選択
typedef enum {
	SCENE_ID_PLAY,
	SCENE_ID_CONFIG,
	SCENE_ID_QUITGAME,
	SCENE_ID_TITLE,
	SCENE_ID_WORLDMAP,
	SCENE_ID_BATTLE,
	SCENE_ID_EP5_STORY,

	SCENE_MAX
}SCENE_IDS;

SCENE_IDS CHAPTER_ID;

int g_scene_id = SCENE_ID_TITLE;


// メニュー選択定数(SelectMenu)
typedef enum {
	GAMESTART,
	CONFIG,
	QUITGAME,
	BACK,

	MAX   // メニュー項目の数-> 4  
};

static int selectedItemNum;


// メニューで選択中項目と選択済み項目の定義
enum {
	ONSELECT,
	NOWSELECTED
};
static int currentMenuState;


// 選択した手とそれを結果で表示する定数（ScenePlay）
enum {
	SELECTED_HAND,
	SELECTED_HAND_DISPLAY,

};


typedef struct {
	int x, y;       // 座標格納用変数
	char name[128]; // 項目名格納用変数
} MenuElement_t;

MenuElement_t selectItems[] = {
	{80,110,"ゲーム開始"},
	{100,260,"コンフィグ"},
	{100,410,"ゲーム終了"},
	{100,560,"もどる"}
};

const tnl::Vector3 CursorPosTBL[MAX] = {
	{70,150, 0},
	{90, 300, 0},
	{90, 450, 0},
	{90, 600, 0}

};
int firstCursorPos = GAMESTART;
const tnl::Vector3 cursorPos = CursorPosTBL[firstCursorPos];


//タイトル
//-------------------------------------------------------------------------------------------------

string TITLE_LOGO_STR = "魔拳勇者";
tnl::Vector3 TITLE_LOGO_POS = { 460, 120, 0 };
string TITLE_MENU_STR = "start space";
tnl::Vector3 TITLE_MENU_POS = { 450, 450, 0 };

int itemSize = sizeof(selectItems) / sizeof(selectItems[0]);
int itemHeightOffset = 100;
int titleBGM,worldMapBGM, selectButtonSE, determineButtonSE;
int Ep1_BGM, Ep2_BGM, Ep3_BGM, Ep4_BGM, Ep5_BGM, Ep6_BGM;
int mouseX, mouseY;
int titleBG_hdl, menuBG_hdl,prologueEvent_BGhdl,kingdomEvent_BGhdl;
int titleLOGO_hdl;

bool isTitleScene = true;
bool isShowMenu = false;
//bool isOnSliderEvent = false;

int anim_ctrl_frame;
float anim_time_count;
int inputNameHdl;
//-----------------------------------------------------------------------------------------------------
 // メニュー

int menuPointer = GAMESTART;

int selectHand = SELECTED_HAND;


//------------------------------------------------------------------------------------------------------------

void gameStart() {
	srand(time(0));

	SetWindowSizeChangeEnableFlag(TRUE, TRUE);
	ChangeWindowMode(true);          // 確定
	SetDrawScreen(DX_SCREEN_BACK);   // 確定
	// 画面最大サイズ設定
	SetWindowText("魔拳勇者");


	titleBGM = LoadSoundMem("SoundItem/TitleBGM/RPG_Battle_demo_bpm184.mp3");
	worldMapBGM = LoadSoundMem("SoundItem/TitleBGM/WorldMap_BGM.mp3");

	Ep1_BGM = LoadSoundMem("SoundItem/TitleBGM/EP1_BattleBGM.mp3");
	Ep2_BGM = LoadSoundMem("SoundItem/TitleBGM/EP2_BattleBGM.mp3");
	Ep3_BGM = LoadSoundMem("SoundItem/TitleBGM/EP3_BattleBGM.mp3");
	Ep4_BGM = LoadSoundMem("SoundItem/TitleBGM/EP4_BattleBGM.mp3");
	Ep5_BGM = LoadSoundMem("SoundItem/TitleBGM/EP5_BattleBGM.mp3");
	Ep6_BGM = LoadSoundMem("SoundItem/TitleBGM/EP6_BattleBGM.mp3");

	selectButtonSE = LoadSoundMem("SoundItem/SE/selectButton.mp3");
	determineButtonSE = LoadSoundMem("SoundItem/SE/determineButton.mp3");

	titleBG_hdl = LoadGraph("graphics/タイトル画面.png");
	titleLOGO_hdl = LoadGraph("graphics/タイトルロゴ.png");
	menuBG_hdl = LoadGraph("graphics/メニュー画面.png");
	prologueEvent_BGhdl = LoadGraph("graphics/Prologue_BG.jpg");
	kingdomEvent_BGhdl = LoadGraph("graphics/Kingdom_BG.jpg");


	LoadGraphics();
	LoadMapImage();
	LoadSliderHandle();
	LoadPlayerFacesAndOthers();
	LoadEnemyImage();
	LoadClickSE_M();
	LoadFuncButtons();
	LoadFuncButtons_Kingdom();
	BattleBG_Handle();


	inputNameHdl = MakeKeyInput(30, FALSE, FALSE, FALSE);
}



void gameMain(float delta_time) {

	if (g_scene_id == SCENE_ID_TITLE && isTitleScene == true) {
		sceneTitle();
	}
	if (g_scene_id == SCENE_ID_PLAY) {
		ShowPrologueTextLog(delta_time);
	}
	if (g_scene_id == SCENE_ID_WORLDMAP) {
		FlashSymbolAndMap(delta_time);
	}
	if (g_scene_id == SCENE_ID_BATTLE) {
		JankenBattle();
	}
	if (g_scene_id == SCENE_ID_EP5_STORY) {
		ShowKingdomEventTextLog();
	}

	
	if (isShowEnterTex == true) {
		SetFontSize(60);
		DrawString(450, 400, pressEnter_Str.c_str(), -1);
		MoveSliderPerFrame(delta_time);

	}
	if (isShowStartTex == false && battleStartTex == false) {
		if (isShowSlider == true) {
			delta_time = 0;
			MoveSliderPerFrame(delta_time);
		}
	}	
	
	if(autoText == true) AutoFunction();
}


int titleScene_phase = 0;

void sceneTitle() {

	// タイトルシーンのBGM管理（再生・停止）
	switch (titleScene_phase)
	{
	case 0:
		PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP);
		titleScene_phase = 1;
		break;
	case 1:
		break;
	}

	SetFontSize(70);
	DrawRotaGraph(30, 30, 0.8f, 0, titleBG_hdl, true);

	DrawRotaGraph(625, 170, 2.0f, 0, titleLOGO_hdl,true);

	//DrawStringEx(TITLE_LOGO_POS.x, TITLE_LOGO_POS.y, -1, TITLE_LOGO_STR.c_str());
	DrawStringEx(TITLE_MENU_POS.x, TITLE_MENU_POS.y, -1, TITLE_MENU_STR.c_str());

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		currentMenuState = ONSELECT;
		PlaySoundMem(determineButtonSE, DX_PLAYTYPE_BACK);
		isShowMenu = true;
	}

	if (isShowMenu == true) {
		ClearDrawScreen();

		DrawRotaGraph(300, 325, 1.0f, 0, menuBG_hdl, true);

		// 描画
		for (int i = 0; i < MAX; i++) {
			SetFontSize(60);
			DrawFormatString(selectItems[i].x, selectItems[i].y, GetColor(255, 255, 255), "・ %s", selectItems[i].name);
		}


		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			selectedItemNum = (selectedItemNum + (MAX - 1)) % MAX;
			PlaySoundMem(selectButtonSE, DX_PLAYTYPE_BACK);
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			selectedItemNum = (selectedItemNum + 1) % MAX;
			PlaySoundMem(selectButtonSE, DX_PLAYTYPE_BACK);
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) == 1 || tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) == 1) {
			for (int i = 0; i < MAX; i++) {
				if (i == selectedItemNum) {
					selectItems[i].x = 90;
				}
				else {
					selectItems[i].x = 110;
				}
			}
		}
		SetFontSize(40);
		DrawString(1070, 640, "Enter", -1);

	}

	if (selectedItemNum == 0) selectedItemNum = GAMESTART;
	if (selectedItemNum == 1) selectedItemNum = CONFIG;
	if (selectedItemNum == 2) selectedItemNum = QUITGAME;
	if (selectedItemNum == 3) selectedItemNum = BACK;


	if (CheckHitKey(KEY_INPUT_RETURN) == 1 && isShowMenu) {
		titleScene_phase = 0;
		isShowMenu = false;
		StopSoundMem(titleBGM);

		switch (selectedItemNum) {
		case GAMESTART:
			g_scene_id = SCENE_ID_PLAY;
			break;
		case CONFIG:
			g_scene_id = SCENE_ID_CONFIG;
			break;
		case QUITGAME:
			g_scene_id = SCENE_ID_QUITGAME;
			break;
		case BACK:
			g_scene_id = SCENE_ID_TITLE;
			break;
		}
		PlaySoundMem(determineButtonSE, DX_PLAYTYPE_BACK);
	}
}

//------------------------------------------------------------------------------------------------------------
void gameEnd() {
}
