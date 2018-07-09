#pragma once
#include <stdint.h>
#include "MyGraphics.h"
#include "Vector2.h"
#include "Configure.h"
class Object {
protected:
	bool visible;
	int width, height;
	int x, y;//x yΪObj���ĵ�����
public:
	Object(int x, int y, UINT width, UINT height);
	virtual ~Object();
	virtual void draw(Graphics g) = 0;
	virtual void move(int x, int y)=0;
	static bool collisionDetect(Object*a, Object*b);//2��obj�ĽӴ����
	int getX();
	int getY();
	bool outOfField();//ȫ�������˶���ս����
	bool outOfField2();//obj�߽��˶���ս����
};
