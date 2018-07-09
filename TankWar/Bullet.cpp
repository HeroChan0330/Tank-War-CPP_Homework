#pragma once

#include "Bullet.h"


Bullet::Bullet(int x, int y, UINT width, UINT height, IMAGE*src, Tank*from, double angleRad, Camp camp, double velocity, int atk) :Object(x, y, width, height) {
	this->velocity = Vector2::fromAngle(angleRad, velocity);
	this->position = Vector2(x, y);
	
	double resizedHeight = (int)ceil(abs((double)height * cos(angleRad)) + abs((double)width * sin(angleRad)));
	double resizedWidth = (int)ceil(abs((double)height * sin(angleRad)) + abs((double)width * cos(angleRad)));

	this->width = (UINT)resizedWidth;
	this->height = (UINT)resizedHeight;
	this->from = from;
	this->camp = camp;

	img =Graphics::rotateImage(src,-angleRad);
	//rotateimage(img, src, angleRad);
	this->atk = atk;
}
Bullet::~Bullet() {
	delete img;
}
void Bullet::draw(Graphics g) {
	int w = img->getwidth(), h = img->getheight();
	g.draw(img, x-w/2, y-h/2, w, h);
	#if SHOW_BORDER
		g.drawRect2(x - width / 2, y - height / 2, width, height);
	#endif
}
void Bullet::move(int x, int y) {
	this->x = x;
	this->y = y;
	this->position = Vector2(x, y);
}

bool Bullet::loop(uint32_t timeStamp) {
	position = position + velocity*LOOP_PERIOD;
	x = position.getX();
	y = position.getY();
	if (this->outOfField()) {
		return true;
	}
	return false;
}

bool Bullet::hit(Tank*obj) {
	
	return false;
}



//派生类定义

Bullet1::Bullet1(int x, int y, double angleRad, Tank*from, Camp camp) :Bullet(x, y, 22, 16, &bulletImg[0], from, angleRad, camp, 800, 5) {
	life = 0;
}

Bullet1::~Bullet1() {

}
bool Bullet1::loop(uint32_t timeStamp) {
	life++;
	if (life > 30) return true;//生命周期为30 超过后回收
	return Bullet::loop(timeStamp);
}

Bullet2::Bullet2(int x, int y, double angleRad, Tank*from, Camp camp) :Bullet(x, y, 50, 8, &bulletImg[1], from, angleRad, camp, 800, 30) {
	//atk = 30;
}
Bullet2::~Bullet2() {

}

Bullet3::Bullet3(int x, int y, double angleRad, Tank*from, Camp camp) :Bullet(x, y, 61, 37, &bulletImg[2], from, angleRad, camp, 400, 50) {
	//atk = 50;
}
Bullet3::~Bullet3() {

}

