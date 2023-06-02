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


std::string prologueTextLog[130] = {

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

		"�����͔��Â���Ԃ������B",

		"�_��̃��C�g(�H)������Ȃ��Èł��Ƃ炵�Ă���B",

		"������m�F����Ƃ�͂蓯���悤�ɈÂ��������A������������ꏊ�͖ڂ̑O�̔��ɑ�����{��\n�̂悤���Ƃ������Ƃ��h�����ĕ��������B",

		"(�E�E�E����H�E�E�Q�ڂ��Ă�̂��H)",

		"�s�v�c�Ȃ��Ƃɖڂ��o�܂��O�܂ł̂��Ƃ��v���o���Ȃ��B�����ɂ��ꎞ�I�Ȃ��̂Ȃ̂��A\n����Ƃ��L���������Ă��܂����̂��A���ꂷ�画�f�o���Ȃ������B",

		"�������^��Ɏv�����̂͂��ꂾ���ł͂Ȃ��B",

		"������琺�𔭂��Ă���ڂ̑O�̏����B",

		"��x������Ɋ�������ޏ��̗l�q���f���Ă݂邪�A����͉��̑S���m��Ȃ��l���������B",

		"(���ɕςȉ����݂����̂��ڂ��Ă邵�A�ς�������𒅂Ă���B�E�E�R�X�v�����H)",

		"(����R�X�v���C���[�ƈÈłœ�l����Ƃ��ǂ�ȏ󋵂���)",

		"�l���Ă��Ă��d���Ȃ��A�l������̂�����u���������������낤�B",

		"�u�E�E�E�E�E�E���́[�A���݂܂���B�����͂ǂ��ł����H�v",

		"�����u���Ə����͖ڂ���炵�A�����Ȑ��ŕԓ������B",

		"�u�E�E�E�E���E�v",

		"�u�́H�v",

		"�u�E�җl�A�P�������ɐ\���グ�܂��v",

		"�u���Ȃ��͎��ɂ܂����v",

		"�E�E�E�E�E�́H",

	   "�u��������邨�C�����͂悭������܂����A���������Ă��������I�v",
	   "�u���Ȃ��͎��񂾁A�����đh�����̂ł��A�l�̍��y�V�����X�鍑�z���~���E�҂Ƃ��āv",

	   "-----------------------------------",

	   "�u����ȃS�~������悤�ȖڂŌ��߂Ȃ��ł��������A���͐^���Ȃ̂ł��I�v",

	   //"�I���� No1.�ɂ�݂���@No.2.�}�΂���@No3.���w�𗧂Ă�


			  "�u�ł�����E�E�E�E�����I�����Ƃɂ����I�v",

			  "�u�E�җl�I���Ȃ��l�͐l�̎q�̑�\�Ƃ��ėE�҂ɑI�΂ꂽ�̂ł��B�����đI�΂ꂽ���̂͂��̐Ӗ���S�����A\n�l�X�Ɉ��J�ƒ������؂��Ȃ��Ă͂Ȃ�܂���v",

			"�u���ꂩ�炠�Ȃ��l�͏C���̓���i�ނ��ƂɂȂ�ł��傤�B�ł������S�z�ɂ͋y�т܂���I�v",

			"(�E�E�R�������Ă���悤�ɂ͌����Ȃ����Ǔ��e�����܂�ɔn���n�������B�V��̍��\���A��������\n�s�v�c�����Ȃ̂��E�E�E�H)",

			"�u���Ȃ��l���I�΂ꂽ���Ƃɂ͂͂�����Ƃ������R������̂ł��I�����ӎu���h�������A�����Ȗʎ����A\n�C�����������R���邻�̍��E�E�E�v",

			"�u�{���ł���Έ�x���񂾍��͏򉻂����܂ŁB�n��ɖ߂邱�Ƃ͋�����܂���v",

			"�u�������A���̐_�X�Ƃ̘b�������̌��ʁA�������̐���t���ō���͓����݂��邱�Ƃƒv���܂����v",

			"�u����H�v",

			"�u�͂��I�E�җl�̍����Ăђn��ɖ߂����Ƃ͐_�X�̝|�ŋւ����Ă��܂��A���v",

			"�u�E�җl�������ς�ł���������ӂ݂āA����͓���Ƃ��ĕʐ��E�ւ̓]�����F�߂�ꂽ�̂ł��v",

			"�u���܂��ẮA�E�җl�ɂ͐��񂻂̐����^�������ȐS���т��ʂ��A���́y�V�����X�鍑�z�𐳂�������\n�������҂ƂȂ��Ă������������v���܂��I�v",

			"�E�E�E�����܂Ő^�ʖڂɘb���Ă�����������ǉ������Ă���̂��悭������Ȃ������B",

			"�Ƃ͌�����^��Ɏv�������Ƃ����������߁A��芸����������Ԃ��Ă݂邱�Ƃɂ����B",

		   "�u���̘b���ĉ��ɉ��̃����b�g�������ł����H�v",

			"�u���H�v",

			"�ӊO�Ȕ����������̂��A�ڂ̑O�̏��_(��)�̓L���g���Ƃ����\��Ōł܂�B",

			"�u���H�����Ă�����ėv����Ɏ����̐g���댯�ɎN���Đ킦���Ă��Ƃł���ˁH���������l�����Ȃ���v",

			"�u��A�E�җl�H���A����͐l�ނɂƂ��ĂƂĂ��h���̂���g���Ȃ̂ł���H�I�I�΂ꂵ���̂�����������\n������----�v",

		   "�u���ƁA���̗E�҂��Ă̂ɑI�΂��悤�Ȑ����Ȑl�Ԃ���Ȃ��ł��扴�B�l�̈����Ƃ����ʂɌ������A\n���������Đl�Ⴂ����Ȃ��ł����H�v",

		   "�u�E�E�E�E�E�E�E����ł͗E�җl�A���Ȃ���n��֑���Ԃ��܂��v",

		   "�u����H������́H�v",

		   "�u����͐V���Ȃ�`���̎n�܂�ƂȂ�ł��傤�A���_�̏j��������񂱂Ƃ��E�E�E�v",

		   "�u����A�b�͏I����Ă�-----�v",



		   //	"------------------------------------------------------------�Ó]--------------------------------------------------------------",

				   "�u�������������I�I�H�v",

				   "�u���A������ˁH�v",

				   "�ˑR�^���ÂɂȂ����Ǝv�����獡�x�͐���Ƃ͈Ⴄ�i�F���f���o���ꂽ�B",

				   "�ǂ����A�������̏��_(��)�����������ɓ]�ڂ������悤���E�E�E���āA�]�ځH�H�I�I�R����H�I�I",

				   "(��ׂ���C�Ɍ�������ттė������E�E�E)",

				   "�]�ڂ̍ہA���炭��u�������̑̂͂��̐���������Ă����B",

				   "�{���Ɉ�u�̏o�������������ߊm���Ȃ��Ƃ͌����Ȃ����A����͖{���������B",

				   "���������{���łȂ���΂��̏󋵂��ǂ���������Ƃ����̂��B",

				   "�E�E�E���Ƃ������M��ɐs���������������������P���B�b���͖���Ȃ��Ȃ邩������Ȃ��B",

				   "(���ꂪ�{���̐_�Ƃ��Ă����)",


				   "�u�E�E�E�����l�����̂Ƃ��������ǎ��Ԃ��Ȃ��́A���������b���n�߂��v",

				   "���̂������֊��������ƁA�����ɏ����ȏ������Ȃ�ł����B",

				   "�l�q���炵�Ė��炩�ɉ��ɘb�������Ă���悤���B",

				   "�u�E�҂Ƃ��Đ��܂�ς�����Ƃ����̂͂��������Ă��ˁH�v",

				   "�u���A����ꉞ�E�E�E�Ă��N�́H�v",


					"�u�������̂��Ƃ͌��B���炭���Ȃ��͏��_�l����M�t�g���������Ă���Ǝv���񂾂��ǁE�E�E�v",

					"�u�M�t�g�H�v",

					"�u���̐l�Ԃ��܂Ƃ��ɖ����Ɛ킦��킯�Ȃ�����Ȃ��A�ǂ����Ɉ�̂悤�Ȃ��̂����܂�ĂȂ��H�v",

					"��������ꉴ�͎��g�̑̂��T�b�ƌ��n���B",

					"�u���A���ꂩ�I�v",

					"�E��̍b�ɐԂ���͂̂悤�Ȃ��̂������яオ���Ă���B",

				   "�u���A�����������ꂻ��I�������ˁA�키�̂�I����Łv",

				  "��͂�������Ə����̃e���V���������炩�ɕς��A�����H���C���ɂȂ����B�����͉����������ڂ�\n���܂��Ďq�ǂ��炵���B",

				  "�u���h�Ɏv���Ȃ�����ˁI���ꂪ�~�����Ċ���Ȃ��l�Ȃ�Đ����؂�Ȃ��قǂ���񂾂���I�v",

				  "�u�E�E�E�E�v",

				 "�u���ق�A����͒ʏ́y�����z�B���̍���𔭓����邱�Ƃɂ���Đ_���Ȃ�͂��s�g���邱�Ƃ��o����́v",

				"�u��̓I�Ɍ����ƁA���Ȃ��͂��ꂩ��G�Ɛ키�Ƃ��A�y�W�����P���z�ƌĂ΂��V�����s��Ȃ��Ă͂Ȃ�Ȃ��v",

				 "�u�y�W�����P���z�ɏ����Ƃ��ł���Α���Ƀ_���[�W��^������B���R������΂��̋t�ˁv",

				 "�u�V���̉񐔂͑���̃��x���ɂ���ĈقȂ邯�ǁA�v����ɑS�Ăɏ��Ă΂����̂�B�ȒP�ł���H�v",

				 "�Ȃ񂩌����������傢���傢ᛂɏ��񂾂�ȁE�E�E�ʂɂ�������",

				 "����Ȃ��Ƃ��E�E�E�E�E�E",

				"�y�W�����P���z",

				"�Ȃ����낤�A���߂ĕ������P��̂͂��Ȃ̂ɁA���̂����͂����m���Ă���B",

				"�m���A�V���͏��߂ɂR�̑����̓��P��I�Ԃ��Ƃ���n�܂�A��������g�̎�Ŏ��̉�����B",

				"�����Ă���𑊎�̑I�񂾑����ƏՓ˂����A���s�����߂�̂��B",

				"�P�������A����ł��Ĕ��ɉ����[���B",

			   "(���̍��̖��^�͂��̎�Ɋ|�����Ă���̂��E�E�E)",

			   "��������܂ŏ��_��n���ɂ��Ă��������͂��Ȃ��B",

			   "�����߂Ă��邻�̉E��͋͂��ɐk���Ă���A���͂��̐k���𐧌䂷�邱�Ƃ��o���Ȃ�����",

				"�ӂƋC���t���ƁA�����͉��b�ȕ\��𕂂��ׂ���������Ă����B",

			   "�u�E�E�E�����܂��������Ă���݂��������ǁA���̐��E�͕�����Ȃ������A����͊o���Ƃ��āv",

				"�u�E�E�E�����v",

				"�u�悵�I���ꂶ�Ⴀ�Ō�ɊȒP�ɂ��̍��̌������������ˁv",

				"���𑁂��ď�����킟�A�ƌ����Ȃ��班���͘b�𑱂���B",

				"�u�����H���̍��͌��݁A�X�e�B���A�V�G�[���A�n�[�s�A�A�Z�O�A�A�����čő�̓G�A���W�[�i�ɂ���Ďx�z����Ă���B\n�܂��A�������茾���Ƃ������|���Ă����΃~�b�V�����R���v���[�g�A���Ȃ��̎g���͂����ŉʂ��������Ăˁv",

				"�u������̖ړI�́H�v",

				"�u�E�E�E�����H�ł��������l�Ԃ��x�z����̂ɗ��R�Ȃ�ėv��Ȃ��񂶂�Ȃ�������H�H�������萇�����Ƃ�����\n����̂Ɠ����悤�ɁA��̓͂��͈͂ɒ��x�����̓y�����������玩���̏��L���ɂ����A�݂����ȁH�v",

				"�����G�E�E�E�Ƃ͎v��������͕̂��������B��������Ƃ���q�o�f�Q�[���ł����������̂��������C���[�W�͏o����B",

				"�����Ă݂���Ə����͖����������̂悤�ɔ��΂݁A���̘b�͏I���ƌ����΂���ɘb���ς����B"

				 "�u�悵�I���Ⴀ��芸�����E�E�E���ƁA���������Ύ��ȏЉ�܂���������ˁv",

				  "�u���̓t�B�i�A���Ȃ��́H�v",


   "���O����",

	
	"�u #name�A�����Ȃ����O�ˁv",
					  

	"�u�����ǁ[���v",


	"�u���ꂶ��E�E�E���܂ł������ɂ��Ă��d���Ȃ����A���낻��s���܂��傤���A���̍����~���ɁE�E�E�v",

"���̃V�[����"
};
   

//�V�����X(Schluss)���I���
//�X�e�B��(Stein) �� ��
//�V�G�[��(Schere)�� ��
//�n�[�s�A(Papier) �� �� 
//�Z�O�A(Seguace) = �z���@�C�^���A��
//���W�[�i(Regina) = ���� �C�^���A��



void ShowPrologueTextLog(float delta_time) {


	isTitleScene = false;

	DrawRotaGraph(620, 125, 0.7f, 0.0f, prologueEvent_BGhdl, true);


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && inputCharName == false && isStillTalking == true) {
		/*currentMessLine++;
		currentMessLine %= 130;*/
		

		if (prologueTextLog[currentMessLine] == "�I����No.1"
			&& tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			prologueTextLog[currentMessLine] = "1.�ɂ�݂���   2.��ł�������   3.���w�𗧂Ă�";
		}
		if (prologueTextLog[currentMessLine] == "�I����No.5"
			&& tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			prologueTextLog[currentMessLine] = "�n�j";
		}
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