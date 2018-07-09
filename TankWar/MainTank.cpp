#pragma once
#include "MainTank.h"

MainTank::MainTank(int x, int y, UINT width, UINT height, IMAGE*src, char*name) :Tank(x, y, width, height,src,name) {
	atk = 2 * DEFAULT_ATK;
	this->camp = CAMP_B; //主战坦克设置为CAMP_B
}

Bullet* MainTank::attack() {
	if (attackCDTime[0] < attackCDPeriod[0]) return NULL;
	attackCDTime[0] = 0;//reset
	double angle = direction.getAngle();
	/*
	double bx = (x + width / 2) + width / 2 * cos(angle);
	double by = (y + height / 2) + height / 2 * sin(angle);
	Bullet*res = new Bullet(bx, by, 22, 16, &bulletImg, angle);
	*/
	Bullet*res = new Bullet1(50 * cos(angle) + x, 50 * sin(angle) + y, angle, this, this->camp);
	MP3::play("Audio\\Shoot0.mp3");
	return res;
}
Bullet* MainTank::attack2() {
	if (attackCDTime[1] < attackCDPeriod[1]) return NULL;
	attackCDTime[1] = 0;//reset
	double angle = direction.getAngle();
	/*
	double bx = (x + width / 2) + width / 2 * cos(angle);
	double by = (y + height / 2) + height / 2 * sin(angle);
	Bullet*res = new Bullet(bx, by, 22, 16, &bulletImg, angle);
	*/
	Bullet*res = new Bullet2(50 * cos(angle) + x, 50 * sin(angle) + y, angle, this, this->camp);
	MP3::play("Audio\\Shoot1.mp3");
	return res;
}

Bullet* MainTank::attack3() {
	if (attackCDTime[2] < attackCDPeriod[2]) return NULL;
	attackCDTime[2] = 0;//reset
	double angle = direction.getAngle();
	/*
	double bx = (x + width / 2) + width / 2 * cos(angle);
	double by = (y + height / 2) + height / 2 * sin(angle);
	Bullet*res = new Bullet(bx, by, 22, 16, &bulletImg, angle);
	*/
	Bullet*res = new Bullet3(50 * cos(angle) + x, 50 * sin(angle) + y, angle, this, this->camp);
	MP3::play("Audio\\Shoot2.mp3");
	return res;
}


