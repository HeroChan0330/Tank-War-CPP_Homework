#ifndef _MYGRAPHICS_H_
#define _MYGRAPHICS_H_

#include <graphics.h>
#include <stdint.h>
#include <Windows.h>
#include <wingdi.h>
#include <math.h>
#include <WinUser.h>
#include <iostream>

#pragma comment( lib, "msimg32.lib" )

class Graphics {
private:
	IMAGE*src;
	uint32_t fgColor;
	uint32_t fillColor;
	HDC hdc;
public:
	Graphics(IMAGE*src);
	~Graphics();

	//实现绘制透明贴图
	void setColor(uint32_t color);
	void setFillColor(uint32_t color);
	void setFont(char*name, uint32_t height);

	void clear(uint32_t color);

	void draw(IMAGE*img, UINT x, UINT y, UINT width, UINT height, uint32_t transparentColor = 0x00);
	void draw(IMAGE*img, UINT x, UINT y, uint32_t transparentColor = 0x00);
	void draw(IMAGE*img, uint32_t transparentColor = 0x00);

	void filterDraw(IMAGE*img, UINT x, UINT y, UINT width, UINT height, DWORD mode = MERGEPAINT);
	void filterDraw(IMAGE*img, DWORD mode = MERGEPAINT);

	void drawLine(UINT x1, UINT y1, UINT x2, UINT y2);
	void drawRect(UINT x1, UINT y1, UINT x2, UINT y2);
	void drawRect2(UINT x1, UINT y1, UINT width, UINT height);
	void drawEllipse(UINT x1, UINT y1, UINT x2, UINT y2);
	void drawText(UINT x, UINT y,char*str);

	void fillRect(UINT x1, UINT y1, UINT x2, UINT y2);
	void fillRect2(UINT x1, UINT y1, UINT width, UINT height);
	void fillEllipse(UINT x1, UINT y1, UINT x2, UINT y2);

	
	HDC getDC();

	static IMAGE* cloneImage(IMAGE*src);
	static IMAGE* rotateImage(IMAGE*img, double angle);

	static void lighten(IMAGE*img,int del);//调整图像亮度
	static void fastBlur(IMAGE*img, int radius);//快速模糊
	static void fakeGaussianBlur(IMAGE*img, int radius);//做几次快速模糊平滑模拟高斯模糊 因为高斯模糊开支略大
	static void RGBOffset(IMAGE*img, int ro, int go, int bo); //RGB色彩调节
};



#endif