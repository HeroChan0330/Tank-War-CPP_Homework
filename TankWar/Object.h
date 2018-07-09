#pragma once
#include <stdint.h>
#include "MyGraphics.h"
#include "Vector2.h"
#include "Configure.h"
class Object {
protected:
	bool visible;
	int width, height;
	int x, y;//x y为Obj中心点坐标
public:
	Object(int x, int y, UINT width, UINT height);
	virtual ~Object();
	virtual void draw(Graphics g) = 0;
	virtual void move(int x, int y)=0;
	static bool collisionDetect(Object*a, Object*b);//2个obj的接触检测
	int getX();
	int getY();
	bool outOfField();//全部画面运动到战场外
	bool outOfField2();//obj边界运动到战场外
};
