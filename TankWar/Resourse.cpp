#include "Resourse.h"


IMAGE cover[2];
IMAGE pauseCover;
IMAGE gameoverCover;
IMAGE thanosImg;

IMAGE bgImg;
IMAGE bulletImg[BULLETYPESUM];
IMAGE tankImgs[TANKTYPESUM];
IMAGE supplyImg[SUPPLYTYPESUM];
IMAGE sparkImg;

void loadResourse() {
	for (int i = 0; i < TANKTYPESUM; i++) {
		char fileName[20] = { 0 };
		sprintf_s(fileName, "Img\\Tank%d.bmp", i);
		loadimage(&tankImgs[i], fileName);
	}
	for (int i = 0; i < BULLETYPESUM; i++) {
		char fileName[20] = { 0 };
		sprintf_s(fileName, "Img\\Bullet%d.bmp", i);
		loadimage(&bulletImg[i], fileName);
	}
	for (int i = 0; i < SUPPLYTYPESUM; i++) {
		char fileName[20] = { 0 };
		sprintf_s(fileName, "Img\\Supply%d.bmp", i);
		loadimage(&supplyImg[i], fileName);
	}

	loadimage(&cover[0], "Img\\Cover0.jpg");
	loadimage(&cover[1], "Img\\Cover1.jpg");
	loadimage(&pauseCover, "Img\\Pause.bmp");
	loadimage(&gameoverCover, "Img\\GameOver.bmp");
	loadimage(&thanosImg, "Img\\Thanos.jpg");

	loadimage(&bgImg, "Img\\BattleGround.jpg");
	loadimage(&sparkImg, "Img\\Spark.bmp");

}