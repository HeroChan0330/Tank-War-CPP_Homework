#pragma once

#include "Object.h"
#include "Tank.h"
#include "Resourse.h"

class Supply:public Object {
protected:
	IMAGE*img;
public:
	Supply(int x, int y, int width, int height,IMAGE*img);
	void move(int x, int y);
	virtual ~Supply();
	virtual void get(Tank*tank)=0;
	virtual void draw(Graphics g)=0;
};

class Supply1 :public Supply {
public:
	Supply1(int x, int y);
	~Supply1();
	void get(Tank*tank);
	void draw(Graphics g);
};