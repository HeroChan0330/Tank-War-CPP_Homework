#include "KeyboardManager.h"

KeyBoardManager::KeyBoardManager() {

}


void KeyBoardManager::listen(uint8_t keyCode) {
	put(keyCode, false);
}

bool KeyBoardManager::unlisten(uint8_t keyCode) {
	remove(keyCode);
	return true;
}

bool KeyBoardManager::press(uint8_t keyCode) {
	put(keyCode, true);
	return true;
}
bool KeyBoardManager::release(uint8_t keyCode) {
	put(keyCode, false);
	return true;
}
bool KeyBoardManager::isPressed(uint8_t keyCode) {
	return get(keyCode);
}

void KeyBoardManager::checkKey(BSTNode<uint8_t, bool>*x) {
	if (x != NULL) {
		if (GetAsyncKeyState(x->key)) {
			x->value = true;
		}
		else {
			x->value = false;
		}
		checkKey(x->left);
		checkKey(x->right);
	}
}

void KeyBoardManager::loop() {
	checkKey(root);
}