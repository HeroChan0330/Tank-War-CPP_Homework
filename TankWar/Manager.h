#pragma once

class Supply;
#include <list>
#include "Bullet.h"
#include "Tank.h"
#include "Spark.h"
#include "Supply.h"

typedef void(*DieCallBack)(Tank*);//坦克死亡的回调函数
class Manager { //处理子弹的运动，击中，消失 坦克的被击中
protected:
	std::list<Bullet*>bullets;
	std::list<Tank*> tanks;
	std::list<Spark*>sparks;
	std::list<Supply*>supplys;

	void removeBullet(Bullet*bullet);
	void removeTank(Tank*tank);
	void addSpark(Spark*spark);
	Spark*createSpark(Bullet*bullet, Tank*tank, int period = 5);

	Tank*me;
	DieCallBack dieCallBack;
public:
	Manager(Tank*me, DieCallBack dieCallBack);
	virtual ~Manager();
	void addBullet(Bullet*bullet);
	void addTank(Tank*tank);
	void addSupply(Supply*supply);
	void loop(uint32_t timsStamp);
	bool checkBump(Tank*tank);//检测tanks内处tank外的对象是否有交集(碰撞），有则返回true
	void draw(Graphics g);
	IMAGE* getPreviewMap();

	void killHalf(); //打一个响指，随机消灭一半的坦克
};