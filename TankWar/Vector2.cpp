
#include "Vector2.h"

Vector2::Vector2() {
	x = 0;
	y = 0;
}
Vector2::Vector2(double x, double y) {
	this->x = x;
	this->y = y;
}
Vector2 Vector2::fromAngle(double angleRad, double length) {//Ĭ��Ϊ��λ����
	return Vector2(length*cos(angleRad), length*sin(angleRad));
}

Vector2 Vector2::operator + (const Vector2&b) const {
	return Vector2(x + b.x, y + b.y);
}
Vector2 Vector2::operator - (const Vector2&b) const {
	return Vector2(x - b.x, y - b.y);
}
double Vector2::operator*(const Vector2&b) {
	return (x*b.x) + (y*b.y);
}
Vector2 Vector2::operator*(const double mult) const {
	return Vector2(x*mult, y*mult);
}
void Vector2::spin(const double angleRad) {
	/*//�㷨������
	double len = length();
	double angle = atan2(y, x)+angleRad;
	x = len*cos(angle);
	y = len*sin(angle);
	*/
	//������ת��ʽ
	//Refer:https://blog.csdn.net/hjq376247328/article/details/45113563
	double x1, y1;
	x1 = x * cos(angleRad) - y * sin(angleRad);
	y1 = x * sin(angleRad) + y * cos(angleRad);
	x = x1;
	y = y1;
}
double Vector2::getX() {
	return x;
}
double Vector2::getY() {
	return y;
}
double Vector2::length() {
	return sqrt(x*x + y*y);
}
double Vector2::getAngle() {
	return atan2(y, x);
}
double Vector2::angleOfVectors(Vector2 a, Vector2 b) {
	//return acos((a.x*b.x + a.y / b.y) / (a.length()*b.length())); //������ѧ�����ϵ�
	return a.getAngle() - b.getAngle();

}
