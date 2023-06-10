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


	"���ɂ����܂ŗ����B",

	 "�Ō�̐킢��O�ɂ��Ďv����y����B",

	"�v���Ԃ��Ό����Ċy�ȓ��ł͂Ȃ������B",

	"�ڂ��o�߂����̂킩��Ȃ��Ƃ���ɂ��āA�ˑR�u���Ȃ��͎��ɂ܂����v�Ƃ������邵�B\n���̏�E�҂Ƃ������ׂ��d�������ڂ�w���킳��邵�B",

	"����������������߂Ă�肽���قǁA���͂悭����Ă�Ǝv���B",

		"(�E�E�E�͂�)",

	"���̏󋵂ɂ��ė��΂Ɋ���͂������A���ǂ̂Ƃ��뗝���͑S�����Ă��Ȃ��B�����ɈӖ��s�����B",

	"���ꂩ��ǂꂭ�炢�o�����̂��낤�B",

	"�ꌎ�O�̂悤�ȋC�����邵�A���������΂������N���炢�o�߂��Ă���̂�������Ȃ��B",

	"�Ƃɂ������͂��̐��E�Ő������т邱�Ƃɑ��X�K���������B",

	"���������ĕʂɂ��̍����~�����߂ɐ���Ă����킯�ł͂Ȃ��A�P�ɐg�ɍ~�肩����΂̕��𕥂���\n���������ŁA�����ɒH�蒅�����̂�����s�����Ǝv���Ă���B",

	"(�ِ��E�]�����Č������牽�Ƃ����������Ƃ����E�E�E�E�[�����Ă���C���[�W���������񂾂��ǂ�)",

	"�Ⴆ�Ή��ɂ͗������ɂ��钇�Ԃ����Ȃ��B�Q�[�����ƍŏ��͈�l�ڂ��������A���ꂪ�i��ł����ɂ��\n���͒��Ԃ������Ă����B���ɂ͂���Ȓ��Ԃ����Ȃ��̂��B",

	"���ɂ͈ٔ\�͂��̂Ă������B���_����ٔ\�̗͎͂������Ă�����̂́A���ۂɐ킢���o�����Ċ������̂�\n�����Ǝ��H�Ɍ������\�͂��������̂ł͂Ȃ����A�Ƃ������ƁB",

	"�w�����x�͉^�Ɉˋ����Ă��镔�����傫���B�������L���ɂȂ邽�߂ɂ�����x�̉^��P���Ȃ��邱�Ƃ͏o���邪�A\n����͐�΂ł͂Ȃ��B���ɂ͎��s�����邵�A�s���ȏ󋵂Ɋׂ������Ƃ����x���������B",

	"�̂ɂ��̔\�͂ɂ��Ă͐F�X�^�O������Ă���̂����A����������Ƒ��ɂ܂������m��Ȃ�����������̂��낤���H",
	
	"�E�E�E�E����A������l�����Ƃ���œ����ȂǏo�ė��Ȃ��B",

	"(����͂����܂ł������Ȃ�)",

	"�܊p�ِ��E�ɗ����Ƃ����̂ɁA���̂Ƃ���y�������Ƃ�����Ȃ��B����͉����̃o�O���H",

	"�u�ӂӁv",

	"�������ĕ��v���ɂӂ����Ă���ƁA�ӂ��ɏ΂����̂悤�Ȃ��̂����������B",
	
	"���͕ӂ�����n���A�₪�Ď��E�̒[�Ɉ�̐l�e�̂悤�Ȃ��̂��m�F����B",

	"�u�E�E�E�悭�������܂ŗ����A�䂪�v�z�ɊQ���Ȃ����Ƃ��鉺�˂Ȑl�̎q��v",

	"�H",

	"���������Ȃ���l�e�͂�����Ɍ������ĕ��݂��n�߂�B",

	"�R�c�R�c�R�c�A�Ɩ��ɋK�����������̑����͂ǂ������C�������B",

	"�܂��G���E�E�E�B",

	"�������x������݂̂��Ƃł͂��邪�A���Ȃ��̂͂��ꂪ�Ⴆ����ڂ��낤�Ɛ�΂Ɍ��Ȃ̂ł���B",

	"�₪�Đl�e�͊�O�ŕ��݂��~��-----------���͌��t���������B",

	"�E�E�E�E�E�E�E�������B",

	"���܂ŐL�т��������A�����ʂ�悤�ȑ傫�ȓ��A���̂悤�ɊÂ����B",
	
	"�����Ƃ����Ԃɉ��͖ڂ̑O�̈���(�H)����ڂ𗣂����Ƃ��o���Ȃ��Ȃ��Ă����B",
	
	"���͂�ǂ��\������̂������Ȃ̂��s���Ȃقǂ̖��͂��A���͖ڂ̑O�̓G�Ɋ����Ă��܂��Ă����̂��B",

	"����������قǂ̃I�[���A���炭�b�ɕ����Ă����w���W�[�i�x�Ƃ����ŏI�ڕW�ŊԈႢ�Ȃ����낤�B",

	"�u���񂽂��w���W�[�i�x�E�E�E���ȁH�v",

	"�u�@���ɂ��A�䂱�������̒鍑���x�z����A���W�[�i���̐l�ł���v",

	"�u�������E�E�E�E�����]�T�������ȁv",

	"�ʂɎ����ł͂Ȃ����A�ꉞ�����ɒB�ɗE�҂�����Ă����킯�ł͂Ȃ��B���X�̐������z�����̓G��j���Ă����B\n�����m��Ȃ��͂����Ȃ��Ǝv���̂����E�E�E",
	
    "����ƃ��W�[�i�͐S�̒ꂩ��s�v�c�����Ɏ���������A������B",
	
	"�u�t�ɉ����ł�K�v������̂��H�܂����M�l�͎���ǂ��l�߂�����ɂł��Ȃ��Ă���̂��H�v",

		"�u�E�E�E�E�E�E�͂��[�v",

		"�S����ꂽ�A�Ƃ�������ޏ��̂��ߑ��ɏ���ē`����Ă���B���炩�ɂȂ߂��Ă���悤���������A\n���͂����s���Ɋ����Ȃ������B",	
		
		"���W�[�i�̌��t��d���A�X�ɂ͂��̗�O�ȕ\��܂ŁA������_�ɉ����Ă��̗����U�镑���͂܂�����\n�����̂��̂��B",

		"���͂���Ȕޏ��ɋ����قǖ����ɂȂ��Ă����B����͂����{����o���邱�Ƃ���Y�����ɂ��B",

		"�u�₨���A�M�l�ɂ͍��Q�̑I����������v",

		"�w���Q�{���āA����������瑤�ւƌ�����B",

		"�u��͉�ɒ����𐾂��A��̔z���ƂȂ邩�v",

		"�u��͉�ɎE����A�o�H�̔@�������ŋ����Đ������v",

		"�u���R�����ɂ���Ă͖J��������Ă�邵�A�M�l�ɂ͓��ʂȐȂ�p�ӂ��Ă���Ă������Ǝv���Ă���B\n�ǂ����A���͂�I�Ԃ܂ł��Ȃ��낤�H�v",

		"�E�E�E�Ȃ�قǁA������Ăł͂Ȃ��Ǝv�����B",

		"���܂ł��̗��s�s�Ȑ��E�ŎU�X�����̐g���댯�ɎN���Đ���Ă����B",

		"�E�҂��Ƃ������Ď��Ě�����A���≴���키�̂��E�҂Ȃ񂾂��瓖�R���Ƒ����̐l���v���Ă���B",

		"���������͌��X�͂����̕��}�Ȑl�Ԃ��B�����܂ŗ��Ċm���ɋ����͂Ȃ������A�S�܂ŕω������킯�ł͂Ȃ��B",

		"�ʂɉ��͐l�X�̖��ɗ��������Ƃ��A������肽���Ƃ������悤�ȗ��h�Ȏu�ȂǍŏ����玝�����킹�Ă�\n���Ȃ������̂��B",

		"�u�E�E�E�������ȁA�I�Ԃ܂ł��Ȃ��v",

		"�u�ł��낤�H�Ȃ�Α���----�v",

		"�u�f��v",

		"�u�_��̋V���E�E�E���H�v",

		"�u���������̐\���o�͒f��v",

		"�u�E�E�E�����ԈႢ���H�M�l�A��̐\���o��f��A�����������̂��H�v",

		"�����Ă݂���ƁA�E�͂����悤�ɓV�����グ�A���W�[�i�͍ēx�[������f�����B",

		"�u�E�E�E�����ł���A�M�l�͂����܂ł̔n���������̂��H�v",

		"�u�܂��E�E�E�n�����Ă͔̂ے肵�Ȃ����ǂȁB�����A���͂��񂽂̂��̉��҂��镗�i�ɍ��ꂽ�񂾁B\n�����牴�����񂽂̗l�Ɏ��R�ɐ��������Ǝv�����A���ꂾ�����v",

		"�u�ق����E�E�E�������Ă���̂��H���M�l�����悤�Ƃ��Ă���͎̂��E�Ɖ����ς��ʁA�����ȑI����v",

		"�u�Ⴄ�ȁA�����I�񂾂̂͋����ł��~�Q�ł��Ȃ��w��R�̑I���x���v",

		"�u��R�̑I���H�v",

		"�����E�җE�҂ƎU�X�����g��ꑱ���ė��Ă�����񂾁A��͂����������̂�肽���悤�ɂ�点�Ă��炨���B",

		"�u----�������O���x�z���Ă��v",

		"�u�́H�v",

		"�܂�Ŕ������S�C��H�����悤�Ȋ�Ŕޏ��͐Î~�����B",

		"�u�v�͐l�X�ɂƂ��Ă̋��Ђ���菜���Ă��΂����B���ꂾ������w�x�z�x�ł����Ȃ��B��������\n�w�E���x�Ɩ��m�Ɉ˗����ꂽ�킯����Ȃ����ȁv",

		"�u�ӁA�E�E�E�͂͂��I�v",

		"���߂Ĕޏ������ɏΊ���������B���̏Ί炪���̎x�z�~�ɍX�ɉ΂�t����B",

		"�u�E�E�E�����悢�v",

		"����܂ł̏Ί炪�����������̂悤�ɔޏ��̕\��ς��A��̋�C���ς�����B�u���ɑ̐��𐮂�\n�E����\����B",

		"�u�Ȃ�΂���Ă݂�A�⏬�Ȃ�l�ԕ���I�I�v",

	"�o�g���J�n",
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

	if (kingdomBattleTextLog[currentMess_Line] == "�o�g���J�n") {
		receiveKingdomText[currentMess_Line] = "";
		currentBattleState = 0;
		episodeNum = 5;
		g_scene_id = 5;
		currentMess_Line = 0;
	}



	// �v���C���[�g�[�N�^�[��
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

	

	// ���W�[�i�g�[�N�^�[��

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
			// TITLE�{�^��
			if (btnInfos_Kingdom.x >= TITLE_BTNFUNC_POS.x && btnInfos_Kingdom.x <= TITLE_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= TITLE_BTNFUNC_POS.y && btnInfos_Kingdom.y <= TITLE_BTNFUNC_POS.y + btnInfos_Kingdom.height) {
				g_scene_id = 3;  // SCENE_ID_TITLE
			}
			// LOAD�{�^��
			if (btnInfos_Kingdom.x >= LOAD_BTNFUNC_POS.x && btnInfos_Kingdom.x <= LOAD_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= LOAD_BTNFUNC_POS.y && btnInfos_Kingdom.y <= LOAD_BTNFUNC_POS.y + btnInfos_Kingdom.height) {

			}
			// SAVE�{�^��
			if (btnInfos_Kingdom.x >= SAVE_BTNFUNC_POS.x && btnInfos_Kingdom.x <= SAVE_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= SAVE_BTNFUNC_POS.y && btnInfos_Kingdom.y <= SAVE_BTNFUNC_POS.y + btnInfos_Kingdom.height) {

			}
			// AUTO�{�^��
			if (btnInfos_Kingdom.x >= AUTO_BTNFUNC_POS.x && btnInfos_Kingdom.x <= AUTO_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= AUTO_BTNFUNC_POS.y && btnInfos_Kingdom.y <= AUTO_BTNFUNC_POS.y + btnInfos_Kingdom.height) {
				currentMess_Line++;
				//autoText = !autoText;
			}
			// SKIP�{�^��
			if (btnInfos_Kingdom.x >= SKIP_BTNFUNC_POS.x && btnInfos_Kingdom.x <= SKIP_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= SKIP_BTNFUNC_POS.y && btnInfos_Kingdom.y <= SKIP_BTNFUNC_POS.y + btnInfos_Kingdom.height) {
				isShowSymbols = true;
				currentBattleState = 0;
				episodeNum = 5;
				g_scene_id = 5;
				currentMess_Line = 0;
			}
			// LOG�{�^��
			if (btnInfos_Kingdom.x >= LOG_BTNFUNC_POS.x && btnInfos_Kingdom.x <= LOG_BTNFUNC_POS.x + btnInfos_Kingdom.width
				&& btnInfos_Kingdom.y >= LOG_BTNFUNC_POS.y && btnInfos_Kingdom.y <= LOG_BTNFUNC_POS.y + btnInfos_Kingdom.height) {

			}
			// CONFIG�{�^��
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