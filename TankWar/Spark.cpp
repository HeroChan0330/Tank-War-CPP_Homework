#include "Spark.h"

Spark::Spark(int x, int y,int period) {
	this->x = x;
	this->y = y;
	this->period = period;
	width = 0;
	height = 0;
	t = 0;
	img = new IMAGE(sparkImg);
}
Spark::~Spark() {
	delete img;
}
bool Spark::loop(uint32_t timeStamp) {
	t++;
	if (t > period) {
		return true;
	}
	return false;
}
void Spark::draw(Graphics g) {
	double scale = t;
	//scale=sqrt(x)
	double nWidth = scale * 2;
	double nHeight = scale *2;
	g.draw(img, x - nWidth / 2, y - nHeight / 2, nWidth, nHeight);
}