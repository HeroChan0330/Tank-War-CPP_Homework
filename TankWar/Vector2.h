#pragma once


#include "Object.h"
#include <math.h>

class Vector2 { //��ά����
protected:
	double x, y;
public:
	Vector2();
	Vector2(double x, double y);
	static Vector2 fromAngle(double angleRad, double length = 1);//Ĭ��Ϊ��λ����

	Vector2 operator + (const Vector2&b) const;
	Vector2 operator - (const Vector2&b) const;
	double Vector2::operator*(const Vector2&b);
	Vector2 operator*(const double mult) const;
	void spin(const double angleRad);
	double getX();
	double getY();
	double length();
	double getAngle();//��ȡ����
	static double angleOfVectors(Vector2 a, Vector2 b); //��ȡ2������ֱ�ӵ�angle����Χ[-PI,PI](��/���Ŵ���a/b����)
};
