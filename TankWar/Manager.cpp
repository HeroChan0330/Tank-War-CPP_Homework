#pragma once
#include "Manager.h"

Manager::Manager(Tank*me, DieCallBack dieCallBack) {
	this->me = me;
	this->dieCallBack = dieCallBack;
}
Manager::~Manager() {
	std::list<Bullet*>::iterator bIter = bullets.begin();
	std::list<Tank*>::iterator tIter = tanks.begin();
	std::list<Spark*>::iterator sIter = sparks.begin();
	for (; bIter != bullets.end(); bIter++) {
		Bullet*bullet = (Bullet*)(*bIter);
		delete bullet;
	}
	for (; tIter != tanks.end(); tIter++) {
		Tank*tank = (Tank*)(*tIter);
		delete tank;
	}
	for (; sIter != sparks.end(); sIter++) {
		Spark*spark = (Spark*)(*sIter);
		delete spark;
	}
}

void Manager::addBullet(Bullet*bullet) {
	bullets.push_front(bullet);
}
void Manager::addTank(Tank*tank) {
	tank->dieCallBack = dieCallBack;
	tanks.push_front(tank);
}
void Manager::addSupply(Supply*supply) {
	supplys.push_front(supply);
}

void Manager::addSpark(Spark*spark) {
	sparks.push_front(spark);
}
Spark* Manager::createSpark(Bullet*bullet, Tank*tank,int period) {
	/*
	int x = -bullet->velocity.getX()*10;
	int y = -bullet->velocity.getY()*10;
	if (abs(x) > abs(tank->width/2)) {
		double scale = abs(tank->width/2) / abs(x);
		x *= scale;
		y *= scale;
	}
	if (abs(y) > abs(tank->height/2)) {
		double scale = abs(tank->height/2) / abs(y);
		x *= scale;
		y *= scale;
	}
	*/
	//����㷨����������
	double radius = 20;
	double angle = PI+bullet->velocity.getAngle();
	double x = radius*cos(angle), y = radius*sin(angle);
	return new Spark(tank->x + x, tank->y + y, period);
}
bool Manager::checkBump(Tank*tank) {
	list<Tank*>::iterator iter = tanks.begin();
	while (iter!=tanks.end()) {
		if (tank != (*iter)&&Object::collisionDetect(tank,*iter)) {
			return true;
		}
		iter++;
	}
	return false;
}

void Manager::loop(uint32_t timsStamp) {
	std::list<Bullet*>::iterator bIter = bullets.begin();
	while (bIter!=bullets.end()) {
		bool hit = false;
		Bullet*bullet = (Bullet*)(*bIter);
		//bullet->loop(timsStamp);
		
		//�����߽� ɾ��bullet
		if (bullet->loop(timsStamp)) {
			bIter = bullets.erase(bIter);//����Ĳ����᲻���Զ�������
			delete bullet;
			continue;
		}
		//�ѳ�����ӵ��������


		std::list<Tank*>::iterator tIter = tanks.begin();

		while (tIter!=tanks.end()) {
			Tank*tank = (Tank*)(*tIter);
			if (Object::collisionDetect(*bIter, *tIter) && bullet->camp != tank->camp) { //�ر��Ѿ��˺�
				hit = true;
				bullet->hit(tank);

				//����Ч
				Spark*spark = createSpark(bullet, tank);
				addSpark(spark);

				if (tank->hited(bullet)) { //̹�˻���
					addSpark(tank->boom());
					tIter = tanks.erase(tIter);//���������̹��
					delete tank;
				}

				bIter = bullets.erase(bIter);//����Ĳ��������Զ�����
				delete bullet;
				break;
			}
			else {
				tIter++;//�Զ�������һ��
			}
		}
		if (!hit) bIter++;

	}

	//�����Լ�̹���ܼ��ģʽ �ж��Ƿ��м񵽲���Ʒ
	std::list<Supply*>::iterator suIter = supplys.begin();
	while (suIter != supplys.end()) {
		Supply*supply = (Supply*)(*suIter);
		if (Object::collisionDetect(me, supply)) {
			supply->get(me);
			suIter=supplys.erase(suIter);
			MP3::play("Audio\\GetSupply.mp3");
			delete supply;
			break;
		}
		suIter++;
	}


	//����tank��spark��
	std::list<Tank*>::iterator tIter = tanks.begin();
	for (; tIter != tanks.end(); tIter++) {
		Tank*tank = (Tank*)(*tIter);
		tank->loop(timsStamp);
		//����ȫ��̹�˶��ܼ��ģʽ �ж��Ƿ��м񵽲���Ʒ
		//std::list<Supply*>::iterator suIter = supplys.begin();
		//while (suIter != supplys.end()) {
		//	Supply*supply = (Supply*)(*suIter);
		//	if (Object::collisionDetect(tank, supply)) {
		//		supply->get(tank);
		//		suIter=supplys.erase(suIter);
		//		delete supply;
		//		break;
		//	}
		//	suIter++;
		//}
	}
	std::list<Spark*>::iterator sIter = sparks.begin();
	while (sIter != sparks.end()) {
		Spark*spark = (Spark*)(*sIter);
		if (spark->loop(timsStamp)) {
			sIter = sparks.erase(sIter);
			delete spark;
		}
		else {
			sIter++;
		}
	}
}
void Manager::draw(Graphics g) {
	std::list<Bullet*>::iterator bIter = bullets.begin();
	std::list<Tank*>::iterator tIter = tanks.begin();
	std::list<Spark*>::iterator sIter = sparks.begin();
	std::list<Supply*>::iterator suIter = supplys.begin();
	for (; suIter != supplys.end(); suIter++) {
		Supply*supply = (Supply*)(*suIter);
		supply->draw(g);
	}
	for (; tIter != tanks.end(); tIter++) {
		Tank*tank = (Tank*)(*tIter);
		tank->draw(g);
	}
	for (; bIter != bullets.end(); bIter++) {
		Bullet*bullet = (Bullet*)(*bIter);
		bullet->draw(g);
	}
	for (; sIter != sparks.end(); sIter++) {
		Spark*spark = (Spark*)(*sIter);
		spark->draw(g);
	}
}


void Manager::removeBullet(Bullet*bullet) {
	bullets.remove(bullet);
	delete bullet;
}
void Manager::removeTank(Tank*tank) {
	tanks.remove(tank);
	delete tank;
}

IMAGE* Manager::getPreviewMap() {
	IMAGE*map = new IMAGE(PREVIEW_MAP_WIDTH, PREVIEW_MAP_HEIGHT);
	//if (map == NULL) {
	//	MessageBox(NULL, "�ڴ�������", "����", 0);
	//	return NULL;
	//}
	DWORD*buffer = GetImageBuffer(map);
	for (std::list<Tank*>::iterator tIter = tanks.begin(); tIter != tanks.end(); tIter++) {
		Tank*tank = (Tank*)(*tIter);
		uint32_t color = RGB(0, 0, 255);
		if (tank == me) color = RGB(0, 255, 0);
		uint32_t x = tank->x*PREVIEW_MAP_WIDTH / MAP_WIDTH, y = tank->y*PREVIEW_MAP_HEIGHT / MAP_HEIGHT;
		buffer[y*PREVIEW_MAP_WIDTH + x] = color;
	}
	return map;
	//g.draw(map, 0, SCREEN_HEIGHT - PREVIEW_MAP_HEIGHT,WHITE);
}

void Manager::killHalf() { //��һ����ָ���������һ���̹��
	//char str[10] = { 0 };
	//_itoa_s(tanks.size(), str, 10);
	//MessageBox(NULL, str, "��ָ֮ǰ����", 0);
	std::list<Tank*>::iterator tIter = tanks.begin();
	uint32_t size = tanks.size();
	for (int i = 0; i < size / 2; i++) {
		Tank*tank = (Tank*)(*tIter);
		if (tank != me) { //��Ȼ�Լ�����boom
			addSpark(tank->boom());
			tIter=tanks.erase(tIter);
			delete tank;
		}
		tIter++;
	}
	//_itoa_s(tanks.size(), str, 10);
	//MessageBox(NULL, str, "��ָ֮������",0);
}