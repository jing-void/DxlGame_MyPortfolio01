#pragma once

void ShowMap();
void FlashSymbolAndMap(float deltaTime);
void LoadMapImage();
void ZoomImageOnMouseOver(int imgHandle, int x, int y, int width, int height, float normalScale, float zoomScale);
void ShowStartGameOrNotMenu();
void BattleBG_Handle();
void LoadClickSE_M();


extern bool isShowSymbols;
extern int episodeNum;
extern int currentBattleState;