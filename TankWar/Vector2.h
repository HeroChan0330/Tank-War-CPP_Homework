#pragma once


#include "Object.h"
#include <math.h>

class Vector2 { //二维向量
protected:
	double x, y;
public:
	Vector2();
	Vector2(double x, double y);
	static Vector2 fromAngle(double angleRad, double length = 1);//默认为单位向量

	Vector2 operator + (const Vector2&b) const;
	Vector2 operator - (const Vector2&b) const;
	double Vector2::operator*(const Vector2&b);
	Vector2 operator*(const double mult) const;
	void spin(const double angleRad);
	double getX();
	double getY();
	double length();
	double getAngle();//获取弧度
	static double angleOfVectors(Vector2 a, Vector2 b); //获取2个向量直接的angle，范围[-PI,PI](正/负号代表a/b领先)
};
