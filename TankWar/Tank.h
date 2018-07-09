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


typedef void(*DieCallBack)(Tank*);//坦克死亡的回调函数


class Tank :public Object {
protected:
	Vector2 position;
	Vector2 direction;
	IMAGE*img;
	IMAGE*backup;
	char*name;
	int blood;//血量 <=0死亡
	uint32_t bloodVolume;//血量的最大值
	uint32_t atk;
	double attackCDTime[5];//各种攻击的冷却已完成周期(单位为s)
	double attackCDPeriod[5];//各种攻击的冷却总周期(单位为s)
	Camp camp; //阵营
public:
	friend class Manager;
	friend class RobotManager;
	uint32_t bloodBarColor;
	DieCallBack dieCallBack;//在dieCallBack回调不需要对this进行析构，会产生内存问题
	Tank(int x, int y, UINT width, UINT height,IMAGE*src,char*name);
	~Tank();
	char*getName();
	void loop(uint32_t timeStamp);//每个循环周期调用1次,用于更新状态
	void turn(double dir); //dir确认运动的方向（+逆 -顺 旋转）和旋转的倍速
	void go(double dir); //dir确认运动的方向（前后）和运动的倍速
	virtual void draw(Graphics g);
	virtual void move(int x, int y);
	virtual bool hited(Bullet*bullet);//返回true表示死亡
	virtual Spark*boom();
	void setBloodVolume(uint32_t volume);//设置血量上限 同时初始化血量
	uint32_t getBlood();
	void setBlood(uint32_t blood);//设置血量
	uint8_t getCdProgress(int n); //返回技能n的冷却进度 0~100
	virtual Bullet*attack();//基础攻击
};
