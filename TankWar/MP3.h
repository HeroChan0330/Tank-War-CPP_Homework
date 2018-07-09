#pragma once

/*
refer:https://blog.csdn.net/u014559880/article/details/50751941
*/

#include <iostream>
#include <stdint.h>
#include <Windows.h>
#include <time.h>
#include <list>
using namespace std;

typedef  int(__stdcall* w32mci)(const char*, char*, int, int);
typedef int(__stdcall *  w32mcierror)(int, char*, int);
class Mci {
private:
	HINSTANCE hins;
	w32mci wmci;
	w32mcierror wmcierror;
public:
	Mci();
	~Mci();
	char buf[256];
	bool send(std::string command);//error  return false 
};

enum PlayType {
	PLAYTYPE_SINGLE,PLAYTYPE_LOOP
};

struct MP3His {
	uint32_t stopTime;
	uint32_t length;
	int alias;
	PlayType playType;
};
class MP3 {
private:
	static Mci mci;
	static uint32_t index;
	static list<MP3His*>toBeDispose;
public:

	//自动处理
	static void loop();
	static void dispose(int alias);
	static uint32_t play(char* path, PlayType playType=PLAYTYPE_SINGLE);
};
