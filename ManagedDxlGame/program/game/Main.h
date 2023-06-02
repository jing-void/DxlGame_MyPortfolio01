#pragma once
void gameStart();
void gameMain( float delta_time );
void gameEnd();
void sceneTitle();
void ScenePlay();
void ShowConfigMenu();
void QuitGame();
void BackToTitle();
void GameScreen();

extern int g_scene_id ;
extern int selectButtonSE;
extern int determineButtonSE;
extern int prologueEvent_BGhdl;
extern int kingdomEvent_BGhdl;
extern int continentEvent_BGhdl;

extern int Ep1_BGM, Ep2_BGM, Ep3_BGM, Ep4_BGM, Ep5_BGM, Ep6_BGM;
extern int worldMapBGM;
extern bool isTitleScene;