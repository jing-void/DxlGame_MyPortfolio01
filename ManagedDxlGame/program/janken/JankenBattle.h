#pragma once
void LoadGraphics();
void ReturnToMap();
void JankenBattle();
void SceneChange();
void GameOverMenu();
void LoadSliderHandle();
void MoveSliderPerFrame(float deltaTime);
void LoadEnemyImage();

extern bool isMovingSlide;
extern bool isShowSymbols;
extern bool showMenu;
extern bool onSelectEps;
extern bool isShowStartTex ;
extern bool battleStartTex;
extern bool isShowEnterTex ;
extern bool isShowSlider;
extern bool isPlayerWin;

extern int playerHP, enemyHP;
extern int anim_ctrl_frame;

extern float anim_time_count;


extern std::string pressEnter_Str;
