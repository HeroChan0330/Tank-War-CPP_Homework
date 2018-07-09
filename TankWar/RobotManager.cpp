#include "RobotManager.h"

double u_random() {
	return (double)(rand() % 100000) / 100000.0;
}

#define RANDOMNAMESUM 21
char*randomName[] = { "Python", "PHP", "JAVA", "CSS", "JAVAScript", "JQuery",
"NodeJs", "Vue", "TypeScript", "SQL", "VB", ".Net", "GoLang", "Swift",
"HTML", "C#", "Perl", "C", "Objective-C", "Pascal", "Shell" };

RobotManager::RobotManager(Tank*me,DieCallBack dieCallBack) :Manager(me,dieCallBack) {
	srand(time(NULL));
}

RobotManager::~RobotManager() {

}
void RobotManager::autoAction(Tank*tank) {
	
	Vector2 dis(me->x - tank->x, me->y - tank->y);
	double angle = Vector2::angleOfVectors(dis, tank->direction);
	if (dis.length() <= ROBOT_ATACK_RADIUS&&abs(angle)<ROBOT_ATACK_ANGLE) { //发动自动攻击
		if (angle>PI / 24) {
			tank->turn(-1);
		}
		else if (angle < -PI / 24) {
			tank->turn(1);
		}
		else if (u_random() < ROBOT_ATTACK_RATE) {
				Bullet*bullet = tank->attack();
				if (bullet != NULL) addBullet(bullet);
		}
		if (dis.length()>ROBOT_ATTACK_RADIUS_MIN) {
			tank->go(ROBOT_ATTACK_TRACK_SPEED);
		}
	}
	else {
		int random = rand() % 100;
		if (random>60) {
			tank->go(1);
			if (checkBump(tank)) tank->go(-1);
		}
		else if (random < 20) {
			tank->go(-1);
			if (checkBump(tank)) tank->go(1);
		}
		else if (random >= 20 && random < 30) {
			tank->turn(-1);
		}
		else if (random >= 30 && random <= 60) {
			tank->turn(1);
		}
	}
	
}

Tank* RobotManager::autoCreateTank() {
	if (tanks.size() >= MAX_TANK_SUM) return NULL;
	Tank*npc;
	for (int i = 0; i < 10; i++) {//尝试10次，如果屏幕上坦克太多，尝试都会失败，就不增加坦克
		int type = rand() % TANKTYPESUM;
		char*name = randomName[rand() % RANDOMNAMESUM];
		//try { //我以为这里会出现内存问题，不过应该不会
			npc = new Tank(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, tankImgs[type].getwidth(), tankImgs[type].getheight(), &tankImgs[type], name);
			if (checkBump(npc)) {
				delete npc;
			}
			else {
				npc->direction = Vector2::fromAngle(u_random()*PI, TANK_SPEED);
				addTank(npc);
				return npc;
			}
		//}
		//catch (bad_alloc exception) {
		//	cout << "Memory error" << endl;
		//	Sleep(1000);
		//}
	}
}
Supply*RobotManager::autoCreateSupply() {
	Supply1*supply = new Supply1(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);
	addSupply(supply);
	return supply;
}
void RobotManager::loop(uint32_t timeStamp) {
	if (u_random() < ROBOT_AUTO_SHOWUP_RATE) {
		autoCreateTank();
	}
	if (u_random() < SUPPLY_AUTO_SHOWUP_RATE) {
		autoCreateSupply();
	}
	
	std::list<Tank*>::iterator iter = tanks.begin();
	while (iter != tanks.end()) {
		if ((*iter) != me) {
			autoAction(*iter);
		}
		iter++;
	}
	Manager::loop(timeStamp);

}