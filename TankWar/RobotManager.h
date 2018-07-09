#pragma once


#include "Manager.h"

#include <stdlib.h>


class RobotManager :public Manager { //机器人会自动攻击的管理器
private:
	void autoAction(Tank*tank);
	Tank* autoCreateTank();
	Supply*autoCreateSupply();
public:
	RobotManager(Tank*me,DieCallBack dieCallBack);
	virtual ~RobotManager();
	void loop(uint32_t timeStamp);
};