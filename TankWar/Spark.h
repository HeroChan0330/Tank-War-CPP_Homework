#pragma once

#include "MyGraphics.h"
#include "Resourse.h"
#include "Configure.h"
#include <math.h>

class Spark {
private:
	int x, y, width, height;
	int period,t;
	IMAGE*img;
public:
	Spark(int x,int y,int period);//period为火花存活周期 决定其scale
	virtual ~Spark();
	bool loop(uint32_t timeStamp);//如果消亡则返回true
	void draw(Graphics g);

};