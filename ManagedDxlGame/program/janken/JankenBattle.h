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
extern int kingdomEnemy_secret;
extern int kingdomEnemy_smile;
extern int kingdomEnemy_Default;
extern int kingdomEnemy_OneHitD;
extern int kingdomEnemy_TwoHitD;
extern int kingdomEnemy_ThreeHitD;
extern int kingdomEnemy_FourHitD;


extern float anim_time_count;


extern std::string pressEnter_Str;
