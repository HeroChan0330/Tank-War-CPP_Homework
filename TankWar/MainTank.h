#pragma once

class Bullet;
class Spark;


#include "Object.h"
#include "Vector2.h"
#include "Configure.h"
#include "Bullet.h"
#include "Resourse.h"
#include "Manager.h"
#include "Spark.h"
#include "MP3.h"

#include "Tank.h"

class MainTank :public Tank { //Ö÷Õ½Ì¹¿Ë
private:

public:
	friend class Manager;
	friend class RobotManager;
	MainTank(int x, int y, UINT width, UINT height, IMAGE*src, char*name);
	Bullet*attack();
	Bullet*attack2();
	Bullet*attack3();

};
