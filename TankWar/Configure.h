#ifndef _CONFIGURE_H_
#define _CONFIGURE_H_

#define SHOW_BORDER 0 //显示子弹和坦克的边框

#define VK_A 65
#define VK_S 83
#define VK_D 68
#define VK_Q 81
#define VK_W 87
#define VK_E 69



#define PI 3.14159

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

#define MAP_WIDTH 3000
#define MAP_HEIGHT 2500

#define PREVIEW_MAP_WIDTH 150
#define PREVIEW_MAP_HEIGHT 125

#define LOOP_PERIOD 0.02 //每个循环的周期 fps=1/LOOP_PERIOD=33 HZ 帧率稳定取决于CPU性能

#define TANK_SPEED 200 //每秒运动的像素
#define TANK_ANGLE_SPEED PI*4/5 //每秒转弯的弧度
#define BULLET_SPEED 600 //每秒运动的像素

#define DEFAULT_TANK_BLOOD_VOLUME 100
#define DEFAULT_ATK 5

#define BLOOD_BAR_POS_Y 70
#define BLOOD_BAR_WIDTH 100
#define BLOOD_BAR_HEIGHT 15

#define BLOOD_WARNING_EFFECT 1 //残血警告效果开关，会占用一定的计算资源
#define BLOOD_WARNING_LIMIT 30 //残血警告

#define TANK_NAME_POS_Y 90

#define MAX_TANK_SUM 30 //Battleground上面的最大坦克数量

#define ROBOT_ATACK_ANGLE PI/3 //机器人开始发动攻击的角度范围/2  乘以2倍不能大于PI
#define ROBOT_ATACK_RADIUS 500 //机器人开始跟踪攻击的半径
#define ROBOT_ATTACK_RADIUS_MIN 150 //机器人跟踪攻击的最小半径
#define ROBOT_ATTACK_TRACK_SPEED 0.7 //跟踪攻击的速度
#define ROBOT_ATTACK_RATE 0.005 //满足上述要求下的攻击概率
#define ROBOT_AUTO_SHOWUP_RATE 0.003 //机器人坦克自动生成概率

#define SUPPLY_AUTO_SHOWUP_RATE 0.001 //补给自动生成概率
#endif