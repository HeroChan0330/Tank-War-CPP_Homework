#include <iostream>
#include <Windows.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>

#include "MP3.h"
#include "Configure.h"
#include "KeyboardManager.h"
#include "MyGraphics.h"
#include "Resourse.h"
#include "Tank.h"
#include "MainTank.h"
#include "RobotManager.h"
#include "Supply.h"


using namespace std;

HWND conHwnd; //控制台的句柄 用于判断窗口失焦时暂停游戏
IMAGE mapBuffer(MAP_WIDTH,MAP_HEIGHT);//整个地图的buffer DC双缓冲绘图，减少闪烁
IMAGE outputBuffer(SCREEN_WIDTH, SCREEN_HEIGHT); //输出到屏幕的buffer DC双缓冲绘图，减少闪烁
HDC outputBufferHDC;

int viewOffsetX = 0;//保证控制的坦克位于视觉中央，对地图绘制偏移X
int viewOffsetY = 0;//保证控制的坦克位于视觉中央，对地图绘制偏移Y

bool gameoverSignal = false; //游戏结束标志

#define SHOWCOVER 1 //是否显示开场动画
#define SHOWFPS 1 //是否右上角显示帧率
uint32_t lastRecordTime = 0;
uint32_t fpsAutoPlus = 0;
uint32_t fpsRecord = 0;

MainTank*me;
uint32_t score = 0;//击杀数

void showFPSInit();
void showFPS(Graphics g);
void viewFollow(Tank*tank);
void showCover();
void consoleInit();
bool checkWindowFocus();
void pause();
void gameOver();
void tankDieCallback(Tank*tank);
void showScore(Graphics g);
void callThanos(Manager&manager);
void start();

int main(int args, char*argv[]) {
	loadResourse();

	//窗口初始化
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	consoleInit();
	showCover();
	showFPSInit();
	double angle = 0;
	while (true) {
		start();
	}

	return 0;
}


void showFPSInit() {
#if SHOWFPS
	lastRecordTime = clock();
#endif
}

void showFPS(Graphics g) {
#if SHOWFPS
	if (clock() - lastRecordTime > 1000) {
		fpsRecord = fpsAutoPlus;
		fpsAutoPlus = 0;
		lastRecordTime = clock();
	}
	fpsAutoPlus++;
	char fpsStr[7] = { 0 };
	sprintf_s(fpsStr, "FPS:%2d", fpsRecord);
	g.drawText(SCREEN_WIDTH - 45, 0, fpsStr);
	//RECT rect = { SCREEN_WIDTH-45, 0, SCREEN_WIDTH, 18};
	//drawtext(fpsStr, &rect, 0);
#endif
}

void viewFollow(Tank*tank) { //使视野跟随坦克
	viewOffsetX = tank->getX() - SCREEN_WIDTH / 2;
	viewOffsetY = tank->getY() - SCREEN_HEIGHT / 2;
	if (viewOffsetX < 0) viewOffsetX = 0;
	else if (viewOffsetX>MAP_WIDTH - SCREEN_WIDTH) viewOffsetX = MAP_WIDTH - SCREEN_WIDTH;
	if (viewOffsetY < 0) viewOffsetY = 0;
	else if (viewOffsetY>MAP_HEIGHT - SCREEN_HEIGHT) viewOffsetY = MAP_HEIGHT - SCREEN_HEIGHT;
}

void showCover() {
#if SHOWCOVER
	uint32_t alias=MP3::play("Audio\\Cover.mp3");
	for (int i = -255; i < 0; i += 16) {
		IMAGE*img = new IMAGE(cover[0]);
		Graphics::lighten(img, i);
		putimage(0, 0, img);
		delete img;
		Sleep(50);
	}
	Sleep(1000);
	for (int i = 0; i >-256; i -= 16) {
		IMAGE*img = new IMAGE(cover[0]);
		Graphics::lighten(img, i);
		putimage(0, 0, img);
		delete img;
		Sleep(50);
	}
	cleardevice();
	Sleep(800);
	for (int i = -255; i < 0; i+=16) {
		IMAGE*img = new IMAGE(cover[1]);
		Graphics::lighten(img, i);
		putimage(0, 0, img);
		delete img;
		Sleep(50);
	}
	while (!GetAsyncKeyState(VK_RETURN));//按回车键继续
	for (int i = 0; i >-256; i -= 16) {
		IMAGE*img = new IMAGE(cover[1]);
		Graphics::lighten(img, i);
		putimage(0, 0, img);
		delete img;
		Sleep(50);
	}
	cleardevice();
	MP3::dispose(alias);
#endif
}

void consoleInit() {
	conHwnd = GetForegroundWindow();
}

bool checkWindowFocus() {
	if (GetForegroundWindow() != conHwnd) {
		return false;
	}
	return true;
}

void pause() {
	//IMAGE*img = new IMAGE(SCREEN_WIDTH, SCREEN_HEIGHT);
	//g.draw(&outputBuffer, 0, 0);
	//BitBlt(GetImageHDC(img), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetImageHDC(&outputBuffer), viewOffsetX, viewOffsetY, SRCCOPY);
	//getimage(img, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); 
	//Graphics::fakeGaussianBlur(img, 10);
	IMAGE*img = &outputBuffer;
	Graphics::fakeGaussianBlur(img, 10);
	Graphics::lighten(img, -100);
	Graphics g(img);
	g.draw(&pauseCover,(SCREEN_WIDTH-pauseCover.getwidth())/2,(SCREEN_HEIGHT-pauseCover.getheight())/2);
	putimage(0, 0, img);

	while (!checkWindowFocus()) {
		Sleep(200);
	}
	while (!GetAsyncKeyState(VK_RETURN));//按回车键继续
}

void gameOver() {
	//IMAGE*img = new IMAGE(SCREEN_WIDTH, SCREEN_HEIGHT);
	////g.draw(&outputBuffer, 0, 0);
	////BitBlt(GetImageHDC(img), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetImageHDC(&outputBuffer), viewOffsetX, viewOffsetY, SRCCOPY);
	//getimage(img, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//Graphics::fakeGaussianBlur(img, 10);
	IMAGE*img = &outputBuffer;
	Graphics::fakeGaussianBlur(img, 10);
	Graphics::lighten(img, -100);
	Graphics g(img);
	g.draw(&gameoverCover, (SCREEN_WIDTH - gameoverCover.getwidth()) / 2, (SCREEN_HEIGHT - gameoverCover.getheight()) / 2);
	char scoreStr[15] = { 0 };
	sprintf_s(scoreStr, "YOU SCORE:%d",score);
	g.setFont("微软雅黑", 88);
	g.setColor(WHITE);
	g.drawText((SCREEN_WIDTH-520)/2,SCREEN_HEIGHT*2/3,scoreStr);
	putimage(0, 0, img);
	g.setFont("微软雅黑", 20);
	g.setColor(BLACK);
	while (!GetAsyncKeyState(VK_RETURN));//按回车键继续
	gameoverSignal = true;
	
}

void tankDieCallback(Tank*tank) {
	if (tank != me) {
		score++;
	}
	else {
		gameOver();
	}
}

void showScore(Graphics g) {
	char scoreStr[10] = { 0 };
	sprintf_s(scoreStr, "SCORE:%3d", score);
	g.drawText(0, 0, scoreStr);
	//RECT rect = { 0, 0, 72, 18 };
	//drawtext(scoreStr, &rect, 0);
}

void start() {

	srand(time(NULL));
	//键盘监听
	KeyBoardManager keyboardManager;
	keyboardManager.listen(VK_ESCAPE);
	keyboardManager.listen(VK_LSHIFT);
	keyboardManager.listen(VK_UP);
	keyboardManager.listen(VK_DOWN);
	keyboardManager.listen(VK_LEFT);
	keyboardManager.listen(VK_RIGHT);
	keyboardManager.listen(VK_A);
	keyboardManager.listen(VK_S);
	keyboardManager.listen(VK_D);
	keyboardManager.listen(VK_Q);

	gameoverSignal = false;
	viewOffsetX = 0;//保证控制的坦克位于视觉中央，对地图绘制偏移X
	viewOffsetY = 0;//保证控制的坦克位于视觉中央，对地图绘制偏移Y
	score = 0;

	//人物初始化
	uint8_t myType = rand() % TANKTYPESUM;
	me = new MainTank(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, tankImgs[myType].getwidth(), tankImgs[myType].getheight(), &tankImgs[myType], "C++");
	me->dieCallBack = tankDieCallback;
	RobotManager manager(me, tankDieCallback);
	manager.addTank(me);

	/*
	for (int i = 0; i < 5; i++) {
	Tank*npc=new Tank(500, 500-i*100, tankImgs[i].getwidth(), tankImgs[i].getheight(), &tankImgs[i], "NPC");
	manager.addTank(npc);
	}
	*/
	Graphics g(&mapBuffer);
	Graphics screenGraphics(&outputBuffer);

	outputBufferHDC = GetImageHDC(&outputBuffer);

	double speed = 1;//移动速度
	uint32_t periodStartTime;
	uint32_t startTime = clock();//开始时间
	uint32_t timeStamp;
	uint32_t callThanosChance = 3;

	MP3::play("Audio\\BGM.mp3",PLAYTYPE_LOOP);
	while (true) {
		periodStartTime = clock();
		timeStamp = clock() - startTime;

		keyboardManager.loop();
		//g.clear(0x000000);
		g.draw(&bgImg);

		//键盘输入

		//按下shift加速前进
		if (keyboardManager.isPressed(VK_LSHIFT)) speed = 1.5;
		else speed = 1;

		if (keyboardManager.isPressed(VK_UP)) {
			me->go(speed);
			if (manager.checkBump(me)) me->go(-speed);
		}
		else if (keyboardManager.isPressed(VK_DOWN)) {
			me->go(-speed);
			if (manager.checkBump(me)) me->go(speed);
		}
		if (keyboardManager.isPressed(VK_LEFT)) {
			if (keyboardManager.isPressed(VK_DOWN))
				me->turn(-speed);
			else {
				me->turn(speed);
			}
		}
		else if (keyboardManager.isPressed(VK_RIGHT)) {
			if (keyboardManager.isPressed(VK_DOWN)) {
				me->turn(speed);
			}
			else {
				me->turn(-speed);
			}
		}
		Bullet*bullet = NULL;
		if (keyboardManager.isPressed(VK_D)) {
			bullet = me->attack3();
			if (bullet != NULL) {
				manager.addBullet(bullet);
			}
		}
		if (keyboardManager.isPressed(VK_S)) {
			bullet = me->attack2();
			if (bullet != NULL) {
				manager.addBullet(bullet);
			}
		}
		if (keyboardManager.isPressed(VK_A)) {
			bullet = me->attack();
			if (bullet != NULL) {
				manager.addBullet(bullet);
			}
		}
		if (keyboardManager.isPressed(VK_Q) && callThanosChance>0) {
			callThanos(manager);
			callThanosChance--;
		}

		//视野跟随
		viewFollow(me);
		manager.loop(timeStamp);//事件循环

		if (gameoverSignal) {
			break;
		}
		//暂停控制
		if (!checkWindowFocus() || keyboardManager.isPressed(VK_ESCAPE)) {
			pause();
		}

		manager.draw(g);//绘制管理

		//音乐资源处理
		MP3::loop();

		//输出、周期结束
		BitBlt(outputBufferHDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g.getDC(), viewOffsetX, viewOffsetY, SRCCOPY);
		
		#if BLOOD_WARNING_EFFECT
				if (me->getBlood() < BLOOD_WARNING_LIMIT) { //残血,场景偏红
				//if (true){
					uint32_t rOffset = abs((int)(timeStamp/10) % 200-100)+50;
					Graphics::RGBOffset(&outputBuffer, rOffset, 0, 0);
				}
		#endif

		IMAGE*previewMap = manager.getPreviewMap();
		BitBlt(outputBufferHDC, 0,SCREEN_HEIGHT - PREVIEW_MAP_HEIGHT, PREVIEW_MAP_WIDTH, PREVIEW_MAP_HEIGHT, GetImageHDC(previewMap),0,0,SRCCOPY);
		delete previewMap;

		showFPS(screenGraphics);
		showScore(screenGraphics);
		putimage(0, 0, &outputBuffer);
		//putimage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, &mapBuffer, viewOffsetX, viewOffsetY);
		//putimage(0, SCREEN_HEIGHT - PREVIEW_MAP_HEIGHT, PREVIEW_MAP_WIDTH, PREVIEW_MAP_HEIGHT, previewMap, 0, 0);
		
		

		while (clock() - periodStartTime < 1000 * LOOP_PERIOD) { //稳定帧率
			Sleep(1);
			//稍微的sleep可以让线程休息一下，不让CPU长期处于高负荷
			//当然根据我的经验，windows的中断原理对sleep唤醒有点影响，反正不准确，这里大可以不sleep效果更佳
		}
		//Sleep(LOOP_DELAY);
	}
}

void callThanos(Manager&manager) {
	IMAGE show(SCREEN_WIDTH, SCREEN_HEIGHT);
	StretchBlt(GetImageHDC(&show), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetImageHDC(&thanosImg), 0, 0, thanosImg.getwidth(), thanosImg.getheight(), SRCCOPY);
	putimage(0, 0, &show);
	MP3::play("Audio\\FingerSnap.mp3");
	Sleep(1000);
	manager.killHalf();
	
}
