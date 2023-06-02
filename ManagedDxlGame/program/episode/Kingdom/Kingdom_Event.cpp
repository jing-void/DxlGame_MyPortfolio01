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
	//"���ɂ����܂ŗ����B",
	// "�Ō�̐킢��O�ɂ��Ďv����y����B",
	//"�v���Ԃ��Ό����Ċy�ȓ��ł͂Ȃ�����",
	//"�ڂ��o�߂����̂킩��Ȃ��Ƃ���ɂ��āA�ˑR�u���Ȃ��͎��ɂ܂����v�Ƃ������邵",
	//"���܂��ɗE�҂Ƃ������ׂ��d�������ڂ�w���킳��邵",

	//	"�E�E�E�͂�",

	//"���̏󋵁A����͂������̗̂����͑S�����Ă��Ȃ��B�����ɈӖ��s���ł���B",


	//"���ꂩ��ǂꂭ�炢�o�����̂��낤",
	//"�ꌎ�O�̂悤�ȋC�����邵�A���������΂������N���炢�o�߂��Ă���̂�������Ȃ�",
	//"�Ƃɂ������͂��̐��E�Ő������т邱�Ƃɑ��X�K��������",
	//"���������ĕʂɂ��̍����~�����߂ɐ���Ă����킯�ł͂Ȃ�",
	//"���͒P�ɐg�ɍ~�肩����΂̕��𕥂��Ă��������ŁA�����ɒH�蒅�����̂�����s�����Ǝv���Ă���",


	//"�u�ӂӁv",

	//"���̎��A���E�̒[�Ɉ�̐l�e�̂悤�Ȃ��̂𑨂���",

	//"�u�E�E�E�悭�������܂ŗ����A�䂪�v�z�ɊQ���Ȃ����Ƃ��鉺�˂Ȑl�̎q��v",

	//"�H",

	//"���������Ȃ���l�e�͂�����Ɍ������ĕ��݂��n�߂�",
	//"�R�c�R�c�R�c�A�Ɩ��ɋK�����������̑����͂ǂ������C����������",

	//"�܂��G���E�E�E",

	//"�����̂��Ƃł͂��邪�A���Ȃ��̂͂��ꂪ�Ⴆ����ڂ��낤�Ɛ�΂Ɍ��Ȃ̂ł���",
	//"�₪�Đl�e�͊�O�ŕ��݂��~��-----------���͌��t��������",

	//"�E�E�E�E�E�E�E������",

	//"���܂ŐL�т��������A�����ʂ�悤�ȑ傫�ȓ��A���̂悤�ɊÂ����B",
	//"�������A���ɕt���Ă���c�m�ƁA�w�ォ��L�тĂ���K�����������ꂪ�l�Ԃł͂Ȃ��Ƃ������Ƃ��͂�����ƕ�����Ă���",
	//"��������Ȃ��Ƃ͂ǂ��ł��悢�B",
	//"�ڂ̑O�̈���(�H)�͐�������̂��悤���Ȃ��قǔ������A�����h�X�g���C�N�ł���",
	//"�w�e�p�[��x�Ƃ������t�����ł͎��܂肫��Ȃ��A���͂�ǂ��\������̂������Ȃ̂��s���Ȃقǂ̖��͂�������̂�",

	//"�u�ӂ�A�m���Ă����v",

	//"�������������������ɖڂ̑O�̈���(�H)�͓�����",
	//"����������قǂ̃I�[���A�b�ɕ����Ă����w���W�[�i�x�Ƃ����ŏI�ڕW�ŊԈႢ�Ȃ�������",


	//
	//"1.���܂����w���W�[�i�x���ȁH",
	//"2.�����]�T��������",
	//"3.�E�E�E�D���ł�",
	//

	//// �I��1
	//	"�u�@���ɂ��A�䂱�������̒鍑���x�z����A���W�[�i���̐l�ł���v",
	//// �I���Q
	//	"�u�t�ɉ����ł�K�v������̂��H�܂����M�l�͎���ǂ��l�߂�����ɂł��Ȃ��Ă���̂��H�v",
	//// �I���R
	//	"�u�E�E�E�E�E�v",




	//	"�u�E�E�E�₨���A�M�l�ɂ͂Q�̑I����������B�v",
	//	"�u��͉�ɒ����𐾂��A��̔z���ƂȂ邩�B�v",
	//	"�u��͉�ɎE����A�o�H�̔@�������ŋ����Đ������B�v",

	//	"�u�ǂ����A�ȒP���낤�H�v",
	//	"�u���R�����ɂ���Ă͖J��������Ă��A�M�l�ɂ͓��ʂɊ����Ƃ��Ă̐Ȃ�p�ӂ��Ă���Ă������B���͂�I�Ԃ܂ł��Ȃ��낤�H�v",

	//	"�E�E�Ȃ�قǁA������Ăł͂Ȃ��A���B",
	//	"���܂ł��̗��s�s�Ȑ��E�ŎU�X�����̐g���댯�ɂ��炵�Đ���Ă���",
	//	"�E�҂Ȃ񂾂��炻��͓��R���ƍl���Ă���l�Ԃ��������邪�A����͈Ⴄ",
	//	"���͂����̕��}�Ȑl�ԂȂ̂��A���X�E�҂Ȃ�Ă���ȗ��h�Ȃ��̂Ȃ񂩂���Ȃ�",
	//	"�N�ł���������{���̉���F�߂ė~�����A�����v���Ă���",


		"�u�E�E�E�������ȁA�I�Ԃ܂ł��Ȃ��v",

		"�u�ł��낤�H�Ȃ�Α���----�v",

		"�u�f��v",

		"�u�_��̋V���E�E�E���H�v",

		"�u���������̐\���o�͒f��A�����ŋ����ʂĂ�̂͂��O�̕����v",

		"�u�E�E�E�����ł���ȁA�����܂ŋM�l�͔n���������̂��H�v",

		"�u�܂��������ȁA�n�����Ă͔̂ے肵�Ȃ��B�����ȁA���͒N���̎w�}���󂯂�̂������Ȃ񂾁v",

		"�u���͉��̐��������悤�ɐ�����A�̂ɂ��O�̔z���ɂ͂Ȃ�Ȃ��v",

		"�u�������A����͂��܂Ȃ������ȁB�Ȃ�΁E�E�E���ˁv",
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
			kingdomBattleTextLog[currentMess_Line] == "�u�������A����͂��܂Ȃ������ȁB�Ȃ�΁E�E�E���ˁv") {
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



// �X�L�b�v�{�^��������灨 �@isShowSymbols = true;�@�@��ǉ�
