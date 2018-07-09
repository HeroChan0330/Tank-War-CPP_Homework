#include "MP3.h"

Mci MP3::mci;
uint32_t MP3::index = 0;
list<MP3His*>MP3::toBeDispose;

Mci::Mci() {
	HINSTANCE hins = LoadLibraryA("winmm.dll");
	wmci = (w32mci)GetProcAddress(hins, "mciSendStringA");
	wmcierror = (w32mcierror)GetProcAddress(hins, "mciGetErrorStringA");
}
Mci::~Mci() {
	FreeLibrary(hins);
}

bool Mci::send(std::string command) {
	int errcode = wmci(command.c_str(), buf, 254, 0);
	if (errcode) {
		wmcierror(errcode, buf, 254);
		return false;
	}
	return true;
}


//自动处理回收
void MP3::loop() {
	list<MP3His*>::iterator iter = toBeDispose.begin();
	while (iter != toBeDispose.end()) {
		MP3His* his = (MP3His*)(*iter);
		if (clock() > his->stopTime) {
			if (his->playType == PLAYTYPE_SINGLE) {
				dispose(his->alias);
				delete his;
				iter = toBeDispose.erase(iter);
			}
			else if (his->playType == PLAYTYPE_LOOP) {
				his->stopTime += his->length;
				char cmd[80] = { 0 };
				sprintf_s(cmd, "play tank_mp3_%d from 0 to %d", his->alias, his->length);
				mci.send(cmd);
				iter++;
			}
		}
		else {
			iter++;
		}
	}
}
void MP3::dispose(int alias) {
	char cmd[80] = { 0 };
	sprintf_s(cmd, "stop tank_mp3_%d", alias);
	mci.send(cmd);
	sprintf_s(cmd, "close tank_mp3_%d", alias);
	mci.send(cmd);
	//cout << "alial_" << alias << " dispose" << endl;
}
uint32_t MP3::play(char* path, PlayType playType) {

	char cmd[80] = { 0 };
	index++;
	sprintf_s(cmd, "open %s alias tank_mp3_%d", path, index);
	mci.send(cmd);
	sprintf_s(cmd, "set tank_mp3_%d time format milliseconds", index);
	mci.send(cmd);
	sprintf_s(cmd, "status tank_mp3_%d length", index);
	mci.send(cmd);
	int length = atoi(mci.buf);
	sprintf_s(cmd, "play tank_mp3_%d from 0 to %d", index, length);
	mci.send(cmd);

	MP3His*his = new MP3His();
	his->alias = index;
	his->stopTime = clock() + length;
	his->playType = playType;
	his->length = length;
	toBeDispose.push_back(his);
	//cout << toBeDispose.size() << endl;
	return index;
}