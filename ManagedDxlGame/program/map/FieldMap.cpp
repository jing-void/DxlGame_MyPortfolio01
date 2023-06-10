#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "DxLib.h"
#include "../game/Main.h"
#include "../janken/JankenBattle.h"
#include "FieldMap.h"

#include <time.h>
#include "../episode/Prologue/PrologueEvent.h"
#include "../episode/Kingdom/Kingdom_Event.h"
#include "time.h"


// prototype
void PlayClickSE();


typedef struct {
	int x, y;       // 座標格納用変数
	char name[128]; // 項目名格納用変数
} MenuElement_t;

MenuElement_t pauseMenus[] = {
	{300,150,"ゲーム画面にもどる"},
	{300,300,"タイトルにもどる"},
	{300,450,"ゲーム終了"},
};

static int pause_scene_id;

enum {
	PAUSE_BACK,
	PAUSE_TITLE,
	PAUSE_QUITGAME
};

struct ImageInfo {
	int handle;
	float x;
	float y;
	int width;
	int height;
	float normalScale;
	float zoomScale;
};

struct ButtonInfo {
	int handle;
	float x;
	float y;
	int width;
	int height;
	float normalScale;
	float zoomScale;
};

// prototype
void ZoomImageOnMouseOver(const ImageInfo&);
void ShowStartGameOrNotMenu(const ImageInfo& imageInfo);
void ZoomButtonOnMouseOver(const ButtonInfo& buttonInfo);
void ClickStartBtnOrBackBtn(const ButtonInfo& buttonInfo);

int clickX, clickY;
int worldMapImage;
int kingdomSymbol, forestSymbol, villageSymbol, citySymbol, theocracySymbol, continentSymbol;
int episodeTitle_PosX = 395, episodeTitle_PosY = 175;  // エピソードタイトルの座標
int alpha = 255;
int playerHP, enemyHP;

int currentSelectMenu = 1;
int menuCount = 3;
int clickSE;

const char* episode = "";

float buttonExRate;
bool fadeIn = true;
bool showMenu = false;
bool isPauseScreen = false;
bool onSelectEps = false;
bool isShowSymbols = true;

tnl::Vector3 FOREST_SYMBOL_POS = { 357, 95, 0 };
tnl::Vector3 VILLAGE_SYMBOL_POS = { 787, 265, 0 };
tnl::Vector3 CITY_SYMBOL_POS = { 950, 580, 0 };
tnl::Vector3 THEOCRACY_SYMBOL_POS = { 455, 680, 0 };
tnl::Vector3 KINGDOM_SYMBOL_POS = { 484, 285, 0 };
tnl::Vector3 CONTINENT_SYMBOL_POS = { 235, 400, 0 };

tnl::Vector3 STARTBUTOON_POS = { 440, 425, 0 };
tnl::Vector3 BACKBUTTON_POS = { 820, 425, 0 };

std::vector<ImageInfo> imageInfos;
std::vector<ButtonInfo> buttonInfos;

void LoadMapImage() {
	worldMapImage = LoadGraph("graphics/NewMap.png");

	imageInfos = {

	{ LoadGraph("graphics/symbols/Kingdom.png"), KINGDOM_SYMBOL_POS.x, KINGDOM_SYMBOL_POS.y, 30,30,0.06f,0.1f},
	{ LoadGraph("graphics/symbols/Forest.png"),FOREST_SYMBOL_POS.x, FOREST_SYMBOL_POS.y,30,30,0.06f,0.1f},
	{ LoadGraph("graphics/symbols/Village.png"),VILLAGE_SYMBOL_POS.x, VILLAGE_SYMBOL_POS.y, 30,30,0.06f,0.1f},
	{ LoadGraph("graphics/symbols/City.png"),CITY_SYMBOL_POS.x, CITY_SYMBOL_POS.y,30,30,0.06f,0.1f},
	{ LoadGraph("graphics/symbols/Theocracy.png"),THEOCRACY_SYMBOL_POS.x, THEOCRACY_SYMBOL_POS.y,30,30,0.06f,0.1f},
	{ LoadGraph("graphics/symbols/Continent.png"),CONTINENT_SYMBOL_POS.x, CONTINENT_SYMBOL_POS.y,30,30,0.06f,0.1f},
	};

	buttonInfos = {

	{ LoadGraph("graphics/startButton.png"),STARTBUTOON_POS.x,STARTBUTOON_POS.y, 140,40,0.25f, 0.28f},
	{ LoadGraph("graphics/backButton.png"),BACKBUTTON_POS.x,BACKBUTTON_POS.y,140,40,0.25f,0.28f}

	};
}


void ShowMap() {
	if (onSelectEps) {
		SetDrawBright(128, 128, 128);
	}

	DrawRotaGraph(640, 360, 0.47, 0, worldMapImage, true);
}

int worldMapBGM_phase = 0;

void FlashSymbolAndMap(float deltaTime) {

	switch (worldMapBGM_phase)
	{
	case 0:
		PlaySoundMem(worldMapBGM, DX_PLAYTYPE_LOOP);
		worldMapBGM_phase = 1;
		break;
	case 1:
		break;
	}


	int offset = 0.03;
	int defaultSize = 0.06;

	if (isPauseScreen == true) {
		SetDrawBright(220, 220, 220);

	}
	else if (isPauseScreen == false) {
		SetDrawBright(255, 255, 255);
	}


	ShowMap();


	// 通常描画
	if (fadeIn)
	{
		alpha -= 4;
		if (alpha <= 0)
		{
			alpha = 0;
			fadeIn = false;
		}
	}
	else
	{
		alpha += 4;
		if (alpha >= 255) {
			alpha = 255;
			fadeIn = true;
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);


	// マウスが画像上にある場合に拡大表示
	for (const auto& imageInfo : imageInfos) {
		ZoomImageOnMouseOver(imageInfo);

		if (isShowSymbols) {
			ShowStartGameOrNotMenu(imageInfo);
		}
	}
	// 通常描画に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// はじめる、もどるボタン表示中
	if (showMenu && onSelectEps) {
		buttonExRate = 0.22f;

		// カーソルがボタンに重なっているとき
		for (const auto& buttonInfo : buttonInfos) {
			ZoomButtonOnMouseOver(buttonInfo);
			ClickStartBtnOrBackBtn(buttonInfo);
		}
		SetFontSize(55);
		DrawFormatString(episodeTitle_PosX, episodeTitle_PosY, -1, episode, true);
	}



	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LALT) || tnl::Input::IsKeyDownTrigger(eKeys::KB_RALT)) {
		isPauseScreen = true;
	}
	if (isPauseScreen == true) {
		SetDrawBright(220, 220, 220);

		for (int i = 0; i < menuCount; i++) {
			SetFontSize(40);
			DrawFormatString(pauseMenus[i].x, pauseMenus[i].y, 0, "・%s", pauseMenus[i].name);
		}
		SetFontSize(35);
		DrawFormatString(830, 625, 0, "Space", true);


		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			currentSelectMenu = (currentSelectMenu + (menuCount - 1)) % menuCount;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			currentSelectMenu = (currentSelectMenu + 1) % menuCount;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) == 1 || tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) == 1) {
			for (int i = 0; i < menuCount; i++) {
				if (i == currentSelectMenu) {
					pauseMenus[i].x = 280;
				}
				else {
					pauseMenus[i].x = 300;
				}
			}
		}
		if (currentSelectMenu == 0) pause_scene_id = PAUSE_BACK;
		if (currentSelectMenu == 1) pause_scene_id = PAUSE_TITLE;
		if (currentSelectMenu == 2) pause_scene_id = PAUSE_QUITGAME;


		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
			switch (pause_scene_id)
			{
			case PAUSE_BACK:
				isPauseScreen = false;
				break;
			case PAUSE_TITLE:
				isPauseScreen = false;
				isTitleScene = true;
				g_scene_id = 3; // SCENE_ID_TITLE
				break;
			case PAUSE_QUITGAME:
				DxLib_End();
			}
			worldMapBGM_phase = 0;
			StopSoundMem(worldMapBGM);
		}
	}
	if (isPauseScreen == false && showMenu == false) {
		SetDrawBright(255, 255, 255);
		SetFontSize(28);
		DrawFormatString(815, 625, 0, "Alt:メニューを開く", true);
	}
}



void ZoomImageOnMouseOver(const ImageInfo& imageInfo) {
	int mouseX, mouseY;
	float scale = imageInfo.normalScale;

	// マウスが画像上にある場合に拡大表示
	GetMousePoint(&mouseX, &mouseY);
	if (mouseX >= imageInfo.x && mouseX <= imageInfo.x + imageInfo.width && mouseY >= imageInfo.y && mouseY <= imageInfo.y + imageInfo.height) {
		scale = imageInfo.zoomScale;
	}
	if (isShowSymbols) {
		DrawRotaGraph(imageInfo.x, imageInfo.y, scale, 0.0f, imageInfo.handle, true);
	}
}


void ZoomButtonOnMouseOver(const ButtonInfo& buttonInfo) {
	int mouseX, mouseY;
	float scale = buttonInfo.normalScale;

	// マウスが画像上にある場合に拡大表示
	GetMousePoint(&mouseX, &mouseY);
	if (mouseX >= buttonInfo.x && mouseX <= buttonInfo.x + buttonInfo.width && mouseY >= buttonInfo.y && mouseY <= buttonInfo.y + buttonInfo.height) {
		scale = buttonInfo.zoomScale;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawRotaGraph(buttonInfo.x, buttonInfo.y, scale, 0.0f, buttonInfo.handle, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void ClickStartBtnOrBackBtn(const ButtonInfo& buttonInfo) {
	GetMousePoint(&clickX, &clickY);

	if (GetMouseInput() && MOUSE_INPUT_LEFT)
	{
		// スタートボタン押下
		if (clickX >= buttonInfo.x && clickX <= buttonInfo.x + buttonInfo.width && clickY >= buttonInfo.y && clickY <= buttonInfo.y + buttonInfo.height) {
			// はじめるボタン
			if (buttonInfo.x >= STARTBUTOON_POS.x && buttonInfo.x <= STARTBUTOON_POS.x + buttonInfo.width &&
				buttonInfo.y >= STARTBUTOON_POS.y && buttonInfo.y <= STARTBUTOON_POS.y + buttonInfo.y + buttonInfo.height) {

				worldMapBGM_phase = 0;
				StopSoundMem(worldMapBGM);

				switch (episodeNum)
				{
				case 1: // Forest
					showMenu = false;
					onSelectEps = false;

					playerHP = 6;
					enemyHP = 1;
					g_scene_id = 5;
					break;
				case 2: // Village
					showMenu = false;
					onSelectEps = false;

					playerHP = 5;
					enemyHP = 2;
					g_scene_id = 5;
					break;
				case 3: // City
					showMenu = false;
					onSelectEps = false;

					playerHP = 4;
					enemyHP = 3;
					g_scene_id = 5;
					break;
				case 4: // Theocracy
					showMenu = false;
					onSelectEps = false;

					playerHP = 3;
					enemyHP = 4;
					g_scene_id = 5;
					break;
				case 5: // Kingdom
					showMenu = false;
					onSelectEps = false;

					playerHP = 2;
					enemyHP = 5;
					g_scene_id = 5;
					break;
				case 6: // Continent
					showMenu = false;
					onSelectEps = false;

					playerHP = 1;
					enemyHP = 6;
					g_scene_id = 5;
					break;
				}

				PlayClickSE();

				if (episodeNum != 5) {
					currentBattleState = 0;  //　 SLIDEREVENT (0) 
				}
				else if (episodeNum == 5) {
					g_scene_id = 6;         //    SCENE_ID_EP5_STORY (6)
				}

				SetDrawBright(255, 255, 255);

				// もどるボタン
			}
			else if (buttonInfo.x >= BACKBUTTON_POS.x && buttonInfo.x <= BACKBUTTON_POS.x + buttonInfo.width &&
				buttonInfo.y >= BACKBUTTON_POS.y && buttonInfo.y <= BACKBUTTON_POS.y + buttonInfo.y + buttonInfo.height) {
				PlayClickSE();
				showMenu = false;
				onSelectEps = false;
				isShowSymbols = true;
			}
		}
	}
}


void ShowStartGameOrNotMenu(const ImageInfo& imageInfo) {
	buttonExRate = 0;

	GetMousePoint(&clickX, &clickY);

	if (GetMouseInput() && MOUSE_INPUT_LEFT)
	{
		if (clickX >= imageInfo.x && clickX <= imageInfo.x + imageInfo.width && clickY >= imageInfo.y && clickY <= imageInfo.y + imageInfo.height) {
			PlayClickSE();
			showMenu = true;
			onSelectEps = true;
			isShowSymbols = false;

			// Forest
			if (imageInfo.x >= FOREST_SYMBOL_POS.x && imageInfo.x <= FOREST_SYMBOL_POS.x + imageInfo.width &&
				imageInfo.y >= FOREST_SYMBOL_POS.y && imageInfo.y <= FOREST_SYMBOL_POS.y + imageInfo.y + imageInfo.height) {
				episode = "第１章：森の賢王";
				episodeNum = 1;
				// Village
			}
			else if (imageInfo.x >= VILLAGE_SYMBOL_POS.x && imageInfo.x <= VILLAGE_SYMBOL_POS.x + imageInfo.width &&
				imageInfo.y >= VILLAGE_SYMBOL_POS.y && imageInfo.y <= VILLAGE_SYMBOL_POS.y + imageInfo.y + imageInfo.height) {
				episode = "第２章：人々の希望";
				episodeNum = 2;
			}
			// City
			else if (imageInfo.x >= CITY_SYMBOL_POS.x && imageInfo.x <= CITY_SYMBOL_POS.x + imageInfo.width &&
				imageInfo.y >= CITY_SYMBOL_POS.y && imageInfo.y <= CITY_SYMBOL_POS.y + imageInfo.y + imageInfo.height) {
				episode = "第３章：失われた街並み";
				episodeNum = 3;
			}
			// Theocracy
			else if (imageInfo.x >= THEOCRACY_SYMBOL_POS.x && imageInfo.x <= THEOCRACY_SYMBOL_POS.x + imageInfo.width &&
				imageInfo.y >= THEOCRACY_SYMBOL_POS.y && imageInfo.y <= THEOCRACY_SYMBOL_POS.y + imageInfo.y + imageInfo.height) {
				episode = "第４章：信仰";
				episodeNum = 4;
			}
			// Kingdom
			else if (imageInfo.x >= KINGDOM_SYMBOL_POS.x && imageInfo.x <= KINGDOM_SYMBOL_POS.x + imageInfo.width &&
				imageInfo.y >= KINGDOM_SYMBOL_POS.y && imageInfo.y <= KINGDOM_SYMBOL_POS.y + imageInfo.y + imageInfo.height) {
				episode = "終章：帝国の支配者";
				episodeNum = 5;
			}
			// Continent
			else if (imageInfo.x >= CONTINENT_SYMBOL_POS.x && imageInfo.x <= CONTINENT_SYMBOL_POS.x + imageInfo.width &&
				imageInfo.y >= CONTINENT_SYMBOL_POS.y && imageInfo.y <= CONTINENT_SYMBOL_POS.y + imageInfo.y + imageInfo.height) {
				episode = "番外編：野球拳勇者";
				episodeNum = 6;
			}
		}
	}
}


void LoadClickSE_M() {
	clickSE = LoadSoundMem("SoundItem/SE/clickSE.mp3");
}
void PlayClickSE() {
	PlaySoundMem(clickSE, DX_PLAYTYPE_BACK);
}