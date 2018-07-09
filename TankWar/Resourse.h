#ifndef _RESOURSE_H_
#define _RESOURSE_H_
#include <graphics.h>
#include <stdio.h>

#define TANKTYPESUM 8
#define BULLETYPESUM 3
#define SUPPLYTYPESUM 1

extern IMAGE cover[2];
extern IMAGE pauseCover;
extern IMAGE gameoverCover;
extern IMAGE thanosImg;

extern IMAGE bgImg;
extern IMAGE bulletImg[BULLETYPESUM];
extern IMAGE tankImgs[TANKTYPESUM];
extern IMAGE supplyImg[SUPPLYTYPESUM];
extern IMAGE sparkImg;

void loadResourse();

#endif