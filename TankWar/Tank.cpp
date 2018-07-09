#pragma once
#include "Tank.h"

Tank::Tank(int x, int y, UINT width, UINT height, IMAGE*src,char*name) :Object(x, y, width, height) {
	this->direction = Vector2::fromAngle(0, TANK_SPEED);
	this->position = Vector2(x, y);
	this->name = name;
	this->img = new IMAGE(*src);
	this->backup = new IMAGE(*src);
	this->blood = DEFAULT_TANK_BLOOD_VOLUME;
	this->bloodVolume = DEFAULT_TANK_BLOOD_VOLUME;
	this->dieCallBack = NULL;
	this->atk = DEFAULT_ATK;
	this->camp = CAMP_A;//NPC camp设置为CAMP_A
	memset(attackCDTime, 0, 4 * 5);
	//{ 5, 25, 40, 80, 160 };
	attackCDPeriod[0] = 0.2;
	attackCDPeriod[1] = 2;
	attackCDPeriod[2] = 5;
	attackCDPeriod[3] = 10;
	attackCDPeriod[4] = 20;

	bloodBarColor = RGB(255, 0, 0);
}
Tank::~Tank() {
	delete img;
	delete backup;
}
char*Tank::getName() {
	return name;
}
void Tank::loop(uint32_t timeStamp) {
	for (int i = 0; i < 5; i++) {
		attackCDTime[i] = (attackCDTime[i] < attackCDPeriod[i]) ? attackCDTime[i] + LOOP_PERIOD : attackCDPeriod[i];
	}
}

void Tank::turn(double dir) { //dir确认运动的方向（+逆 -顺 旋转）和旋转的倍速
	double anglePlus = dir*TANK_ANGLE_SPEED*LOOP_PERIOD;
	direction.spin(-anglePlus);
	double angle=-direction.getAngle();
	/*
	double resizedHeight = (int)ceil(abs((double)height * cos(angle)) + abs((double)width * sin(angle)));
	double resizedWidth = (int)ceil(abs((double)height * sin(angle)) + abs((double)width * cos(angle)));

	//IMAGE*newImg = new IMAGE(resizedWidth, resizedHeight);
	IMAGE*newImg = new IMAGE(width, height);
	rotateimage(newImg, backup, angle,0x00,false);
	delete img;
	*/
	IMAGE*newImg = Graphics::rotateImage(backup, angle);
	delete img;
	img = newImg;
}
void Tank::go(double dir) { //dir确认运动的方向（前后）和运动的倍速
	Vector2 displacement = direction*dir*LOOP_PERIOD;
	if ((x-width/2<0 && displacement.getX()<0)||(x+width/2>MAP_WIDTH&&displacement.getX()>0)||
		(y-height/2<0 && displacement.getY()<0) || (y + height/2>MAP_HEIGHT&&displacement.getY()>0)) {
		
	}
	else {
		position = position + displacement;
		x = position.getX();
		y = position.getY();
	}
}
void Tank::draw(Graphics g) {
	uint32_t w = img->getwidth(), h = img->getheight();
	g.draw(img, x-w/2, y-h/2, w, h);

	#if SHOW_BORDER
		g.drawRect2(x - width / 2, y - height / 2, width, height);
	#endif
	g.setFillColor(RED);
	uint32_t bw = (blood*BLOOD_BAR_WIDTH) / bloodVolume;
	g.fillRect2(x - BLOOD_BAR_WIDTH / 2, y - BLOOD_BAR_POS_Y, bw, BLOOD_BAR_HEIGHT);
	g.drawRect2(x - BLOOD_BAR_WIDTH / 2, y - BLOOD_BAR_POS_Y, BLOOD_BAR_WIDTH, BLOOD_BAR_HEIGHT);

	g.drawText(x - BLOOD_BAR_WIDTH / 2, y - TANK_NAME_POS_Y, name);
}
void Tank::move(int x, int y) {
	this->x = x;
	this->y = y;
	this->position = Vector2(x, y);
}

bool Tank::hited(Bullet*bullet) {
	MP3::play("Audio\\Hited.mp3");
	blood -= bullet->atk;
	if (blood <= 0) {
		blood = 0;
		return true;
	}
	return false;
}
Spark* Tank::boom() {
	MP3::play("Audio\\Boom.mp3");
	Spark*spark = new Spark(x, y, 30);
	if (dieCallBack != NULL) dieCallBack(this);
	return spark;
}

void Tank::setBloodVolume(uint32_t volume) {
	bloodVolume = volume;
	blood = volume;
}

uint32_t Tank::getBlood() {
	return blood;
}
void Tank::setBlood(uint32_t blood) {
	this->blood = blood;
	if (this->blood > bloodVolume) this->blood = bloodVolume;
	else if (this->blood < 0) this->blood = 0;
}

Bullet* Tank::attack() {
	//MessageBox(NULL, "ROB ATTACK1", "ROB ATTACK1", 0);
	if (attackCDTime[0] < attackCDPeriod[0]) return NULL;
	attackCDTime[0] = 0;//reset
	//MessageBox(NULL, "ROB ATTACK2", "ROB ATTACK2", 0);
	double angle = direction.getAngle();
	/*
	double bx = (x + width / 2) + width / 2 * cos(angle);
	double by = (y + height / 2) + height / 2 * sin(angle);
	Bullet*res = new Bullet(bx, by, 22, 16, &bulletImg, angle);
	*/
	Bullet*res = new Bullet1(50 * cos(angle) + x, 50 * sin(angle) + y, angle, this,this->camp);
	MP3::play("Audio\\Shoot0.mp3");
	//MessageBox(NULL, "ROB ATTACK3", "ROB ATTACK3", 0);
	return res;
}
uint8_t Tank::getCdProgress(int n) {
	return attackCDTime[n] * 100 / attackCDPeriod[n];
}