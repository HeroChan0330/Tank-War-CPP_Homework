#include "Supply.h"

Supply::Supply(int x, int y, int width, int height, IMAGE*img):Object(x,y,width,height){
	this->img = new IMAGE(*img);	
}
Supply::~Supply() {
	delete img;
}
void Supply::move(int x, int y) {
	this->x = x;
	this->y = y;
}

Supply1::Supply1(int x, int y) : Supply(x, y, 40, 53, &supplyImg[0]) {
	this->img = img;
}
void Supply1::get(Tank*tank) {
	uint32_t blood = tank->getBlood();
	blood += 30;
	tank->setBlood(blood);
}
void Supply1::draw(Graphics g) {
	g.draw(img, x - width / 2, y - width / 2);
}
Supply1::~Supply1() {
}
