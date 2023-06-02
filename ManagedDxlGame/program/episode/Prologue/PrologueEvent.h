#pragma once
void ShowPrologueTextLog(float delta_time);
void LoadFuncButtons();
void DrawFuncBtns();
void LoadPlayerFacesAndOthers();
void AutoFunction();


extern int titleFuncBtn, skipFuncBtn, saveFuncBtn, logFuncBtn, loadFuncBtn, configFuncBtn, autoFuncBtn;
extern int inputNameHdl;
extern int offensive_f1, normal_1, normal_2, suprise1,
smile_1, smile_2, smile_3, mad1,mad2, speechless_1, speechless_2,
speechless_3, suspect1;

extern bool autoText;