#ifndef _KEYBOARDMANAGER_H_
#define _KEYBOARDMANAGER_H_

#include <windows.h>
#include <stdint.h>
#include "BST.cpp"

//Interesting part
//extends the Binary Search Tree
class KeyBoardManager :protected BST<uint8_t, bool> {
private:
	void checkKey(BSTNode<uint8_t, bool>*x);
public:
	KeyBoardManager();
	void listen(uint8_t keyCode);
	bool unlisten(uint8_t keyCode);

	bool press(uint8_t keyCode);
	bool release(uint8_t keyCode);//如果未按下，返回false，否则true
	bool isPressed(uint8_t keyCode);//如果已经按下，返回true,否则false
	void loop();//msg loop
};


#endif