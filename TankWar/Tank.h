#pragma once

class Bullet;
class Spark;


#include "Object.h"
#include "Vector2.h"
#include "Configure.h"
#include "Bullet.h"
#include "Camp.h"
#include "Resourse.h"
#include "Manager.h"
#include "Spark.h"
#include "MP3.h"


typedef void(*DieCallBack)(Tank*);//̹�������Ļص�����


class Tank :public Object {
protected:
	Vector2 position;
	Vector2 direction;
	IMAGE*img;
	IMAGE*backup;
	char*name;
	int blood;//Ѫ�� <=0����
	uint32_t bloodVolume;//Ѫ�������ֵ
	uint32_t atk;
	double attackCDTime[5];//���ֹ�������ȴ���������(��λΪs)
	double attackCDPeriod[5];//���ֹ�������ȴ������(��λΪs)
	Camp camp; //��Ӫ
public:
	friend class Manager;
	friend class RobotManager;
	uint32_t bloodBarColor;
	DieCallBack dieCallBack;//��dieCallBack�ص�����Ҫ��this����������������ڴ�����
	Tank(int x, int y, UINT width, UINT height,IMAGE*src,char*name);
	~Tank();
	char*getName();
	void loop(uint32_t timeStamp);//ÿ��ѭ�����ڵ���1��,���ڸ���״̬
	void turn(double dir); //dirȷ���˶��ķ���+�� -˳ ��ת������ת�ı���
	void go(double dir); //dirȷ���˶��ķ���ǰ�󣩺��˶��ı���
	virtual void draw(Graphics g);
	virtual void move(int x, int y);
	virtual bool hited(Bullet*bullet);//����true��ʾ����
	virtual Spark*boom();
	void setBloodVolume(uint32_t volume);//����Ѫ������ ͬʱ��ʼ��Ѫ��
	uint32_t getBlood();
	void setBlood(uint32_t blood);//����Ѫ��
	uint8_t getCdProgress(int n); //���ؼ���n����ȴ���� 0~100
	virtual Bullet*attack();//��������
};
