#pragma once

class Supply;
#include <list>
#include "Bullet.h"
#include "Tank.h"
#include "Spark.h"
#include "Supply.h"

typedef void(*DieCallBack)(Tank*);//̹�������Ļص�����
class Manager { //�����ӵ����˶������У���ʧ ̹�˵ı�����
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
	bool checkBump(Tank*tank);//���tanks�ڴ�tank��Ķ����Ƿ��н���(��ײ�������򷵻�true
	void draw(Graphics g);
	IMAGE* getPreviewMap();

	void killHalf(); //��һ����ָ���������һ���̹��
};