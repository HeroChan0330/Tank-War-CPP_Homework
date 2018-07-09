#pragma once
#include "Object.h"

Object::Object(int x, int y, UINT width, UINT height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


Object::~Object() {

}

//adapted from js code
//src:https://blog.csdn.net/gg_18826075157/article/details/72858590
//core
/*
// Åö×²¼ì²â£¨Á½ÐÐ´úÂë¸ã¶¨£©
if(
Math.abs(red.x - blue.x) < red.width/2 + blue.width/2 //ºáÏòÅÐ¶Ï
&&
Math.abs(red.y - blue.y) < red.height/2 + blue.height/2 //×ÝÏòÅÐ¶Ï
){
console.log("·¢ÉúÅö×²");
}
*/
bool Object::collisionDetect(Object*a,Object*b) {
	if (abs(a->x - b->x) < a->width / 2 + b->width / 2 //ºáÏòÅÐ¶Ï
		&&
		abs(a->y - b->y) <a->height / 2 + b->height / 2 //×ÝÏòÅÐ¶Ï
		) {
		return true;
	}
	return false;
}

int Object::getX() {
	return x;
}
int Object:: getY() {
	return y;
}
bool Object::outOfField() {
	if (x + width/2<0 || x-width/2>MAP_WIDTH || y + height/2<0 || y-height/2>MAP_HEIGHT) {
		return true;
	}
	return false;
}
bool Object::outOfField2() {
	if (x-width/2 <0 || x+width>MAP_WIDTH || y-height/2 <0 || y+height/2>MAP_HEIGHT) {
		return true;
	}
	return false;
}