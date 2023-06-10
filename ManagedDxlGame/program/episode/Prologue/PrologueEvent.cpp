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

	// ���̓��[�h��`��
	DrawKeyInputModeString(640, 480);

	// ���͓r���̕������`��
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

		"�E�E�E�E�E�E�E�E�E",

		"�E�E�E�E�E�E�E�E�E",

			"�E�E�E�E�E�E�E�E�E",

			"����͐[������ɂ��Ă��邩�̂悤�Ȋ��o�������B",

			"��E�E�E���E�E�E�E�܁I",

			"�̂𓮂������Ƃ��A�������l���邱�Ƃ��������Ȃ���ȏ�Ԃ̒��A����琺���������ė���B",

			"�u�䂤���Ⴓ�܁I�I�I�v",

			"�I�H�I�H�I�H",

			"�܂�ŋC�����悭�����Ă���������}�΂����̂悤�ɁA���̍b�������͉���@���N�������B",

			"�u���E�E�E�E�v",

			"�u���I�H����ƋN���Ă��������܂����ˁA�E�җl�I�v",


			"�݂��ɂޓ�����ŉ������Ȃ���A�������Ƒ̂��N�����B",

			"�u�E�E�E�����́H�v",


			"�����c�����邽�ߎ��͂����n�����A�������܍����Ɋׂ�B",

			"�����͔��Â���Ԃ������B�_��̃��C�g(�H)������Ȃ��Èł��Ƃ炵�Ă���B",

			"������m�F����Ƃ�͂蓯���悤�ɈÂ��������A������������ꏊ�͖ڂ̑O�̔��ɑ�����{��\n�̂悤���Ƃ������Ƃ��h�����ĕ��������B",

			"(�E�E�E����H�E�E�Q�ڂ��Ă�̂��H)",

			"�s�v�c�Ȃ��Ƃɖڂ��o�܂��O�܂ł̂��Ƃ��v���o���Ȃ��B�����ɂ��ꎞ�I�Ȃ��̂Ȃ̂��A\n����Ƃ��L���������Ă��܂����̂��A���ꂷ�画�f�o���Ȃ������B",

			"�������^��Ɏv�����̂͂��ꂾ���ł͂Ȃ��B",

			"������𔭂��Ă����ڂ̑O�̏����ɖڂ�������B",

			"���b�ώ@���Ă݂����A�ǂ��������Ă�����͉��̑S���m��Ȃ��l���������B",

			"(���ɕςȉ����݂����̂��ڂ��Ă邵�A�ς�������𒅂Ă���B�E�E�R�X�v�����H)",

			"(����R�X�v���C���[�ƈÈłœ�l����Ƃ��ǂ�ȏ󋵂���)",

			"�������čl���Ă��Ă��d�����Ȃ��A���ڐu���������������낤�B",

			"�u�E�E�E�E�E�E���́[�A���݂܂���B�����͂ǂ��ł����H�v",

			"�����u���Ə����͖ڂ���炵�A�����Ȑ��ŕԓ������B",

			"�u�E�E�E�E���E�v",

			"�u�́H�v",

			"�u�E�җl�A�˔@������̐��E�ւ��Ăт��Ă��܂����������l�ѐ\���グ��Ƌ��ɁA��ɂ��`��\n���邱�Ƃ��������܂��v",

			"���̖ڂ�^���������߁A��ċz�����Ă���Ăь����J���B",

			"�u���Ȃ��͎��ɂ܂����v",

			"�E�E�E�E�E�́H",

			"�u��������邨�C�����͂悭������܂����A���������Ă��������v",

			"�u���Ȃ��͎��񂾁A�����đh�����̂ł��A�l�̍��y�V�����X�鍑�z���~���E�҂Ƃ��āv",

			"-----------------------------------",

			"�u����ȃS�~������悤�ȖڂŌ��߂Ȃ��ł��������A���͐^���Ȃ̂ł��I�v",

			"���H��������Ȋ炵�Ă�̂��H���S�ɖ��ӎ��������B",

			"�u�E�җl�I���Ȃ��l�͐l�̎q�̑�\�Ƃ��ėE�҂ɑI�΂ꂽ�̂ł��B�����đI�΂ꂽ�҂͂��̐Ӗ���S�����A\n�l�X�Ɉ��J�ƒ������؂��Ȃ��Ă͂Ȃ�܂���v",

			"�u���ꂩ�炠�Ȃ��l�͏C���̓���i�ނ��ƂɂȂ�ł��傤�B�ł������S�z�ɂ͋y�т܂���I�v",

			"(�E�E�R�������Ă���悤�ɂ͌����Ȃ����Ǔ��e�����܂�ɔn���n�������B�V��̍��\���A��������\n�s�v�c�����Ȃ̂��E�E�E�H)",

			"�u���Ȃ��l���I�΂ꂽ���Ƃɂ͂͂�����Ƃ������R������̂ł��I�����ӎu���h�������A�����Ȗʎ����A\n�C�����������R���邻�̍��E�E�E�v",

			"�u�{���ł���Έ�x���񂾍��͏򉻂����܂ŁB�n��ɖ߂邱�Ƃ͋�����܂���v",

			"�u�������A���̐_�X�Ƃ̘b�������̌��ʁA�������̐���t���ō���͓����݂��邱�Ƃƒv���܂����v",

			"�u����H�v",

			"�u�͂��I�E�җl�̍����Ăђn��ɖ߂����Ƃ͐_�X�̝|�ŋւ����Ă��܂��A���v",

			"�u�E�җl�������ς�ł���������ӂ݂āA����͓���Ƃ��ĕʐ��E�ւ̓]�����F�߂�ꂽ�̂ł��v",

			"�u���܂��ẮA�E�җl�ɂ͐��񂻂̐����^�������ȐS���т��ʂ��A���́y�V�����X�鍑�z�𐳂�������\n�������҂ƂȂ��Ă������������v���܂��I�v",

			"���������Ă���̂������ς蕪����Ȃ��������A�����ŉ��͂����̉\���ɋC���t���B\n",

			"(�h�b�L�����H�I)",

			"����������Ă����̕�����Ȃ��b���͗]���������������B",

			"�ЂƂ��т��̍l���ɒH�蒅���ƁA����܂ŕ����Ă����ْ��ƕs�������������a�炢�����Ƃ�������B",

			"�i����ł����ɂǂ���������񂾁H�U���H���H�j",

			"�܂��U���Ƃ������͂Ȃ����낤�B�����ł���΂��̂悤�Ȓ��ԂɈӖ��͂Ȃ��B",

			"�ł���Ζ����H",

			"�E�E�E",

			"�������ł���Ζڂ��o�߂���S�ĖY��悤�B����Ȃ̂����̍����j���B",

			"�ЂƂ܂����𓾂邽�߁A�K���ɕԓ����Ă݂邱�Ƃɂ����B",

		   "�u���[���ƁE�E�E�E���̘b���ĉ��ɉ��������b�g�Ƃ����Ă������肷���ł����H�v",

			"�u���H�v",

			"�ӊO�Ȕ����������̂��A�ڂ̑O�̏��_(��)�̓L���g���Ƃ����\��Ōł܂�B",

			"�u���H�����Ă�����ėv����Ɏ����̐g���댯�ɎN���ĒN���Ɛ킦���Ă��Ƃł���ˁH�v",

			"�u��A�E�җl�H���A����͐l�ނɂƂ��ĂƂĂ��h���̂���g���Ȃ̂ł���H�I�I�΂ꂵ���̂�����������\n������----�v",

		   "�u���Ɖ��̉������̗E�҂��Ă̂ɑI�΂ꂽ��ł����H�����Ō����̂��Ȃ�ł����ǉ����ē��Ɏ�蕿\n�Ƃ��Ȃ����E�E�v",

		   "�b���Ղ��ď����s���������̂��A���_(��)����͐���܂ł̏Ί炪�����Ă����B",

			"�u�E�E�E�\���󂲂����܂��񂪁A����������`�����鎞�Ԃ͂������܂���B�E�җl�ɂ͈ꍏ�������n��֖߂�A\n�l�X�ɋ~���̎�������L�ׂė~�����̂ł��v",

			"(���܂ő����񂾂낤����E�E�E�E)",

		   "�u����͐V���Ȃ�`���̎n�܂�ƂȂ�ł��傤�A�E�җl�ɏ��_�̏j��������񂱂Ƃ��E�E�E�v",

		   "�u����A�b�͏I����Ă�-----�v",



		   //	"------------------------------------------------------------�Ó]--------------------------------------------------------------",

				"--------------------------------------------------------",

				"------------------------------------------",

				"----------------------------",

				   "�u�������������I�I�H�v",

				   "�u���A������ˁH�v",

				   "�ˑR�^���ÂɂȂ����Ǝv�����獡�x�͐���Ƃ͈Ⴄ�i�F���f���o���ꂽ�B",

				   "�ǂ����A�������̏��_(��)�����������ɓ]�ڂ������悤���E�E�E���āA�]�ځH�H�I�I",

				   "�j���˂��Ă݂����A���ʂɒɂ��B�܂�������Ȃ��Ƃ������������Ƃ͎v�������Ȃ������B",

				   "�i�E�E�E�E�E�E�j",

				   "�]�ڂ̍ہA���炭��u�������̑̂͂��̐����瑶�݂������Ă����B",

				   "��u�̏o�������������ߊm�؂͂Ȃ����A���炭����͖{���������B����������������Ă��M����҂�\n���Ȃ����낤�B����܂ł̎����Ɠ����悤�ɁB",

				   "�����A�{���łȂ���΂��̏󋵂��ǂ���������Ƃ����̂��B",

				   "�E�E�E�~�������߂�悤�ɕӂ�����n���A��l�̏����Ɩڂ��������B",

				   "�u�E�E�E�����l�����̂Ƃ��������ǎ��Ԃ��Ȃ��́A���������b���n�߂��v",

				   "(����E�E�E�H�f�W�����H)",

				   "���ŋߓ����悤�Ȃ��Ƃ��������悤�ȋC������̂����A�C�̂������H",

				   "�����͐錾�ʂ�A������̐��_��ԂȂǒm���Ƃł������΂���ɏ���ɘb���n�߂��B",

				   "�u�E�҂Ƃ��Đ��܂�ς�����Ƃ����̂͂��������Ă��ˁH�v",

				   "�u���A�E�E�E�E�܂��ꉞ�E�E�E�E�Ă��N�́H�v",

					"�u�������̂��Ƃ͌��B�����肱���ɗ���O�ɏ��_�l���牽���M�t�g��������Ȃ������H�v",

					"�u�M�t�g�H�v",

					"�u���̐l�Ԃ��܂Ƃ��ɖ����Ɛ킦��킯�Ȃ�����Ȃ��A�z��Ɛ키���߂ɂ͗͂��v���B�ǂ�����\n��̂悤�Ȃ��̂����܂�ĂȂ��H�v",

					"��������ꉴ�͎��g�̑̂��T�b�ƌ��n���B",

					"�u���A�E�E����H�v",

					"�E��̍b�ɐԂ���͂̂悤�Ȃ��̂������яオ���Ă���B",

				   "�u���A�����������ꂻ��I�������ˁE�E�E�키�̂�I����Łv",

				  "��͂��������r�[�A�����̃e���V���������炩�ɕ^�ς����B������Ă���Ȃɐ������̂Ȃ̂��E�E�E�H",

				 "�u����͒ʏ́y�����z�B���̍���𔭓����邱�Ƃɂ���Đ_���Ȃ�͂��s�g���邱�Ƃ��o����́v",

				"�u��̓I�Ɍ����ƁA���Ȃ��͂��ꂩ��G�Ɛ키�Ƃ��A�y�W�����P���z�ƌĂ΂��V�����s��Ȃ��Ă͂Ȃ�Ȃ��v",

				 "�u�y�W�����P���z�ɏ����Ƃ��ł���Α���Ƀ_���[�W��^������B���R������΂��̋t�ˁv",

				 "�u�V���̉񐔂͑���̃��x���ɂ���ĈقȂ邯�ǁA�v����ɑS�Ăɏ��Ă΂����̂�B�ȒP�ł���H�v",

				 "����ᛂɏ�錾�������������A���͊����Ă�����C�ɂ��Ȃ��悤�ɂ���B",

				 "����Ȃ��Ƃ��E�E�E�E�E�E",

				"�y�W�����P���z",

				"���������Ƃ��Ȃ��P�ꂾ�����B",

				"�������s�v�c�Ȃ��Ƃɉ��̂����͂����m���Ă���B",

				"�V���͏��߂ɂR�̑����̓��P��I�Ԃ��Ƃ���n�܂�A��������g�̎�Ŏ��̉�����B",

				"�����Ă���𑊎�̑I�񂾑����ƏՓ˂����A���s�����߂�̂��B",

				"�P�������A����ł��Ĕ��ɉ����[���B",

			   "(���̍��̖��^�����̎�ɁE�E�E)",

			   "�C���t���΂�����܂ŏ��_��n���ɂ��Ă��������͂������Ȃ��Ȃ��Ă����B",

			   "�]�ڂ����ۂɂ��̐g�Ŗ�����Ă��炩�A���̏󋵂ɉ��͏���������ݎn�߂Ă���̂�������Ȃ��B",

			   "���g�̓K���\�͂ɋ������A�ӂƉE�������Ƃ��ꂪ�͂��ɐk���Ă��邱�Ƃ����������B",

			   "���̐k���͈ӎ����Ă����䂪�ł����A�~�܂낤�Ƃ͂��Ă���Ȃ������B",

			   "�u�E�E�E�����܂��������Ă���݂��������ǁA���̐��E�͕�����Ȃ������A����͊o���Ƃ��āv",

				"�u�E�E�E�����v",

				"�u�E�E�E���Ⴀ�Ō�ɊȒP�ɂ��̍��̌������������ˁv",

				"���𑁂��ď�����킟�A�Ɣ�������͘b�𑱂���B",

				"�u�����H���̍��͌��݁A�X�e�B���A�V�G�[���A�n�[�s�A�A�Z�O�A�A�����čő�̓G�A���W�[�i�ɂ���Ďx�z����\n�Ă���B�܂��A�������茾���Ƃ������|���Ă����΂��Ȃ��̎g���͂����ŉʂ�������v",

				"�u������̖ړI�́H�v",

				"�u�E�E�E�����H�ł��������l�Ԃ��x�z����̂ɗ��R�Ȃ�ėv��Ȃ��񂶂�Ȃ�������H��̓͂��͈͂ɒ��x����\n�̓y�����������玩���̏��L���ɂ����A��������ȂƂ����v",

				"�����������G�E�E�E�Ƃ͎v�����������̘b�͑�̑z�������B��������Ƃ���q�o�f�Q�[���ł����������̂͂������B",

				"�����Ă݂���Ə����͖����������̂悤�ɔ��΂݁A�܂�ł��̘b�͏I���Ƃł������悤�ɘb���ς����B",

				 "�u�悵�I���Ⴀ��芸�������܂ł������ɂ��Ă��d���Ȃ����A�ړ����Ȃ���b���܂��傤�E�E�E���A\n���������Ύ��ȏЉ�܂���������v",

				  "�u���̓t�B�i�A���Ȃ��́H�v",


   "���O����",


	"�u #name�A�����Ȃ����O�ˁv",


	"�u�����ǁ[���v",


	"�u���ꂶ����߂āA�s���܂��傤���E�E�E���̍����~���Ɂv",

"���̃V�[����"
};


//�V�����X(Schluss)���I���
//�X�e�B��(Stein) �� ��
//�V�G�[��(Schere)�� ��
//�n�[�s�A(Papier) �� �� 
//�Z�O�A(Seguace) = �z���@�C�^���A��
//���W�[�i(Regina) = ���� �C�^���A��


int scenePhase = 0;     // 0�����_�A1���t�B�i

void ShowPrologueTextLog(float delta_time) {


	isTitleScene = false;

	if (isBlackScreen == false && currentMessLine < 68) {
		DrawRotaGraph(620, 125, 0.7f, 0.0f, prologueEvent_BGhdl, true);
	}


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && inputCharName == false && isStillTalking == true) {

		if (prologueTextLog[currentMessLine] == "���O����") {
			prologueTextLog[currentMessLine] = "���O����͂��Ă�������";
			inputCharName = true;
		}

		if (inputCharName == false) {
			if (prologueTextLog[currentMessLine] == "���̃V�[����") {
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

		// ���_�V�[��----------------------------------------------------------------------------------------------------------------------------------
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
			//�@�t�B�i�V�[��------------------------------------------------------------------------------------------------------------------------------
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
	offensive_f1 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/�h������.png");
	normal_1 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/�m�[�}��.png");
	normal_2 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/�m�[�}��2.png");
	surprise1 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/����.png");
	smile_1 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/�Ί�1.png");
	smile_2 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/�Ί�2.png");
	smile_3 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/�Ί�3.png");
	mad1 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/�{��1.png");
	mad2 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/�{��2.png");
	speechless_1 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/����.png");
	speechless_2 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/����2.png");
	speechless_3 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/����3.png");
	suspect1 = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�\���/�^��.png");
	playerWholeBody = LoadGraph("graphics/�L�����N�^�[�f��/��l��/�����G2.png");


	goddessWholeBody_normal = LoadGraph("graphics/�L�����N�^�[�f��/���_/�m�[�}��.png");
	goddessWholeBody_smile = LoadGraph("graphics/�L�����N�^�[�f��/���_/�Ί�.png");
	goddessWholeBody_serious = LoadGraph("graphics/�L�����N�^�[�f��/���_/�^��.png");
	goddessWholeBody_secret = LoadGraph("graphics/�L�����N�^�[�f��/���_/��.png");

	girl_normal = LoadGraph("graphics/�L�����N�^�[�f��/����/girl_normal.png");
	girl_serious = LoadGraph("graphics/�L�����N�^�[�f��/����/girl_serious.png");
	girl_smile = LoadGraph("graphics/�L�����N�^�[�f��/����/girl_smile.png");
	girl_mad1 = LoadGraph("graphics/�L�����N�^�[�f��/����/girl_mad1.png");
	girl_mad2 = LoadGraph("graphics/�L�����N�^�[�f��/����/girl_mad2.png");
	girl_secret = LoadGraph("graphics/�L�����N�^�[�f��/����/girl_secret.png");

	BGHdl_FinaScene = LoadGraph("graphics/��.jpg");
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
			// TITLE�{�^��
			if (btnInfos.x >= TITLE_BTNFUNC_POS.x && btnInfos.x <= TITLE_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= TITLE_BTNFUNC_POS.y && btnInfos.y <= TITLE_BTNFUNC_POS.y + btnInfos.height) {
				g_scene_id = 3;  // SCENE_ID_TITLE
			}
			// LOAD�{�^��
			if (btnInfos.x >= LOAD_BTNFUNC_POS.x && btnInfos.x <= LOAD_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= LOAD_BTNFUNC_POS.y && btnInfos.y <= LOAD_BTNFUNC_POS.y + btnInfos.height) {

			}
			// SAVE�{�^��
			if (btnInfos.x >= SAVE_BTNFUNC_POS.x && btnInfos.x <= SAVE_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= SAVE_BTNFUNC_POS.y && btnInfos.y <= SAVE_BTNFUNC_POS.y + btnInfos.height) {

			}
			// AUTO�{�^��
			if (btnInfos.x >= AUTO_BTNFUNC_POS.x && btnInfos.x <= AUTO_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= AUTO_BTNFUNC_POS.y && btnInfos.y <= AUTO_BTNFUNC_POS.y + btnInfos.height) {
				autoText = !autoText;
			}
			// SKIP�{�^��
			if (btnInfos.x >= SKIP_BTNFUNC_POS.x && btnInfos.x <= SKIP_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= SKIP_BTNFUNC_POS.y && btnInfos.y <= SKIP_BTNFUNC_POS.y + btnInfos.height) {
				isShowSymbols = true;
				g_scene_id = 4;
			}
			// LOG�{�^��
			if (btnInfos.x >= LOG_BTNFUNC_POS.x && btnInfos.x <= LOG_BTNFUNC_POS.x + btnInfos.width
				&& btnInfos.y >= LOG_BTNFUNC_POS.y && btnInfos.y <= LOG_BTNFUNC_POS.y + btnInfos.height) {

			}
			// CONFIG�{�^��
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