#ifndef _CONFIGURE_H_
#define _CONFIGURE_H_

#define SHOW_BORDER 0 //��ʾ�ӵ���̹�˵ı߿�

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

#define LOOP_PERIOD 0.02 //ÿ��ѭ�������� fps=1/LOOP_PERIOD=33 HZ ֡���ȶ�ȡ����CPU����

#define TANK_SPEED 200 //ÿ���˶�������
#define TANK_ANGLE_SPEED PI*4/5 //ÿ��ת��Ļ���
#define BULLET_SPEED 600 //ÿ���˶�������

#define DEFAULT_TANK_BLOOD_VOLUME 100
#define DEFAULT_ATK 5

#define BLOOD_BAR_POS_Y 70
#define BLOOD_BAR_WIDTH 100
#define BLOOD_BAR_HEIGHT 15

#define BLOOD_WARNING_EFFECT 1 //��Ѫ����Ч�����أ���ռ��һ���ļ�����Դ
#define BLOOD_WARNING_LIMIT 30 //��Ѫ����

#define TANK_NAME_POS_Y 90

#define MAX_TANK_SUM 30 //Battleground��������̹������

#define ROBOT_ATACK_ANGLE PI/3 //�����˿�ʼ���������ĽǶȷ�Χ/2  ����2�����ܴ���PI
#define ROBOT_ATACK_RADIUS 500 //�����˿�ʼ���ٹ����İ뾶
#define ROBOT_ATTACK_RADIUS_MIN 150 //�����˸��ٹ�������С�뾶
#define ROBOT_ATTACK_TRACK_SPEED 0.7 //���ٹ������ٶ�
#define ROBOT_ATTACK_RATE 0.005 //��������Ҫ���µĹ�������
#define ROBOT_AUTO_SHOWUP_RATE 0.003 //������̹���Զ����ɸ���

#define SUPPLY_AUTO_SHOWUP_RATE 0.001 //�����Զ����ɸ���
#endif