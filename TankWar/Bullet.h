#pragma once

class Tank;
class Manager;

#include "Object.h"
#include "Tank.h"
#include "Camp.h"
#include "Manager.h"
#include "Vector2.h"
#include "MyGraphics.h"
#include "Configure.h"



class Bullet :public Object {
protected:
	int atk;//������ 
	Vector2 velocity;
	Vector2 position;
	IMAGE *img;
	Tank*from;
	Camp camp;
public:
	friend class Tank;
	friend class MainTank;
	friend class Manager;
	Bullet(int x, int y, UINT width, UINT height, IMAGE*src, Tank*from, double angleRad,Camp camp, double velocity = BULLET_SPEED, int atk = DEFAULT_ATK);
	~Bullet();
	virtual void draw(Graphics g);
	void move(int x, int y);

	virtual bool loop(uint32_t timeStamp);//����true��ʾ������Manager���л���

	virtual bool hit(Tank*obj);
	
};

class Bullet1 :public Bullet {
private:
	int life;
public:
	Bullet1(int x, int y, double angleRad, Tank*from, Camp camp);
	bool loop(uint32_t timeStamp);
	~Bullet1();
};

class Bullet2 :public Bullet {
public:
	Bullet2(int x, int y, double angleRad, Tank*from, Camp camp);
	~Bullet2();
};

class Bullet3 :public Bullet {
public:
	Bullet3(int x, int y, double angleRad, Tank*from, Camp camp);
	~Bullet3();
};
