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
	Spark(int x,int y,int period);//periodΪ�𻨴������ ������scale
	virtual ~Spark();
	bool loop(uint32_t timeStamp);//��������򷵻�true
	void draw(Graphics g);

};