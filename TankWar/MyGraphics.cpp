#include "MyGraphics.h"

Graphics::Graphics(IMAGE*src) {
	this->src = src;
	hdc = GetImageHDC(src);
	fgColor = BLACK;
	fillColor = WHITE;
	HPEN hPen = CreatePen(PS_SOLID, 1, fgColor);
	HGDIOBJ old=SelectObject(hdc, hPen);
	DeleteObject(old);
	setFont("微软雅黑", 20);

}

Graphics::~Graphics() {
	//src = NULL;
	ReleaseDC(NULL, hdc);
}


void Graphics::clear(uint32_t color) {

}
void Graphics::draw(IMAGE*img, uint32_t transparentColor) {
	draw(img, 0, 0, img->getwidth(), img->getheight(), transparentColor);
}

void Graphics::draw(IMAGE*img, UINT x, UINT y, uint32_t transparentColor) {
	draw(img, x, y, img->getwidth(), img->getheight(), transparentColor);
}

void Graphics::draw(IMAGE*img, UINT x, UINT y, UINT width, UINT height, uint32_t transparentColor) {
	HDC targetHDC=GetImageHDC(src);
	HDC srcHDC = GetImageHDC(img);
	
	TransparentBlt(targetHDC, x, y, width, height, srcHDC, 0, 0, img->getwidth(), img->getheight(), transparentColor);

	//BitBlt(targetHDC, x, y, width, height, srcHDC, 0, 0, SRCCOPY);
	//StretchBlt(targetHDC, x, y, width, height, srcHDC, 0, 0, src->getwidth(), src->getheight(), SRCCOPY);
}

void Graphics::filterDraw(IMAGE*img, DWORD mode) {
	filterDraw(img, 0, 0, img->getwidth(), img->getheight(), mode);
}
void Graphics::filterDraw(IMAGE*img, UINT x, UINT y, UINT width, UINT height,DWORD mode) {
	HDC targetHDC = GetImageHDC(src);
	HDC srcHDC = GetImageHDC(img);
	StretchBlt(targetHDC, x, y, width, height, srcHDC, 0, 0, img->getwidth(), img->getheight(), mode);
}

void Graphics::setColor(uint32_t color) {
	fgColor = color;
	HPEN hPen = CreatePen(PS_SOLID, 1, fgColor);
	HGDIOBJ old = SelectObject(hdc, hPen);
	DeleteObject(old);
}
void Graphics::setFillColor(uint32_t color) {
	fillColor = color;
}
void Graphics::setFont(char*name, uint32_t height) {
	HFONT hFont = CreateFont(height,                                          //   nHeight     
							0,                                                   //   nWidth     
							0,                                                   //   nEscapement   
							0,                                                   //   nOrientation     
							FW_NORMAL,                                   //   nWeight     
							FALSE,                                           //   bItalic     
							FALSE,                                           //   bUnderline     
							0,                                                   //   cStrikeOut     
							ANSI_CHARSET,                             //   nCharSet     
							OUT_DEFAULT_PRECIS,                 //   nOutPrecision     
							CLIP_DEFAULT_PRECIS,               //   nClipPrecision     
							DEFAULT_QUALITY,                       //   nQuality     
							DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily       
							name);
	HGDIOBJ old = SelectObject(hdc, hFont);
	DeleteObject(old);
}

void Graphics::drawLine(UINT x1, UINT y1, UINT x2, UINT y2) {
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

void Graphics::drawRect(UINT x1, UINT y1, UINT x2, UINT y2) {
	HBRUSH hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	HGDIOBJ old = SelectObject(hdc, hbr);
	DeleteObject(old);
	Rectangle(hdc, x1, y1, x2, y2);
}

void Graphics::drawRect2(UINT x1, UINT y1, UINT width, UINT height) {
	this->drawRect(x1, y1, x1 + width, y1 + height);
}

void Graphics::drawEllipse(UINT x1, UINT y1, UINT x2, UINT y2) {
	HBRUSH hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	HGDIOBJ old = SelectObject(hdc, hbr);
	DeleteObject(old);

	Ellipse(hdc, x1, y1, x2, y2);
}

void Graphics::drawText(UINT x, UINT y,char*str) {
	SetTextColor(hdc, fgColor);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, x, y, str, lstrlen(str));
}

void Graphics::fillRect(UINT x1, UINT y1, UINT x2, UINT y2) {
	RECT rect = { x1, y1, x2, y2 };
	HBRUSH hBrush = CreateSolidBrush(fillColor);
	FillRect(hdc, &rect, hBrush);
	DeleteObject(hBrush);
}

void Graphics::fillRect2(UINT x1, UINT y1, UINT width, UINT height) {
	this->fillRect(x1, y1, x1 + width, y1 + height);
}

void Graphics::fillEllipse(UINT x1, UINT y1, UINT x2, UINT y2) {
	HRGN hrgn=CreateEllipticRgn(x1, y1, x2, y2);
	HBRUSH hBrush = CreateSolidBrush(fillColor);
	FillRgn(hdc, hrgn, hBrush);
	DeleteObject(hrgn);
	DeleteObject(hBrush);
	
}

HDC Graphics::getDC() {
	return hdc;
}

IMAGE* Graphics::cloneImage(IMAGE*src) {
	/*
	IMAGE*res = new IMAGE(src->getwidth(), src->getheight());
	HDC targetHdc=GetImageHDC(res);
	HDC srcHdc = GetImageHDC(src);
	BitBlt(targetHdc, 0, 0, src->getwidth(), src->getheight(), srcHdc, 0, 0, SRCCOPY);
	*/
	return new IMAGE(*src);
}

IMAGE* Graphics::rotateImage(IMAGE*img,double angle) {
	if (img == NULL) return NULL;
	int width = img->getwidth(), height = img->getheight();
	int resizedHeight = (int)ceil(abs((double)height * cos(angle)) + abs((double)width * sin(angle)));
	int resizedWidth = (int)ceil(abs((double)height * sin(angle)) + abs((double)width * cos(angle)));
	int w = max(resizedWidth, resizedHeight);
	
	IMAGE*temp = new IMAGE(w, w);
	IMAGE*res = new IMAGE(w, w);
	//Graphics g(temp);
	//g.draw(img, (w - width) / 2, (w - height) / 2, width, height);
	BitBlt(GetImageHDC(temp), (w - width) / 2, (w - height) / 2, width, height, GetImageHDC(img), 0, 0,SRCCOPY);
	rotateimage(res, temp, angle);
	delete temp;
	return res;

}

void Graphics::lighten(IMAGE*img,int del) {
	DWORD*buffer = GetImageBuffer(img);
	uint8_t*rgbArray = (uint8_t*)buffer;
	uint8_t*ptr = rgbArray;
	int height = img->getheight(), width = img->getwidth();
	for (int j = 0; j <height; j++) {
		for (int i = 0; i <width; i++) {
			for (int channel = 0; channel < 3; channel++) {
				if ((*ptr) + del>255) (*ptr) = 255;
				else if ((*ptr) + del < 0) (*ptr) = 0;
				else (*ptr) += del;
				ptr++;
			}
			ptr++;
		}
	}
}

void Graphics::fastBlur(IMAGE*img,int radius) {
	int height = img->getheight(), width = img->getwidth();
	int stride = width * 4;
	DWORD*buffer = GetImageBuffer(img);
	byte*content = (byte*)buffer;

	for (int y = 0; y<height; y++) {
		for (int x = 0; x<width; x++) {
			for (int c = 0; c<3; c++) {//c为BGR次序
				int cnt = 0;
				int sum = 0;
				for (int j = -radius; j <= radius; j++) {//垂直方向求和
					if (j + y >= 0 && j + y<height) {
						cnt++;
						sum += content[(j + y)*stride + 4 * x + c];
					}
				}
				for (int i = -radius; i <= radius; i++) {//水平方向求和
					if (i + x >= 0 && i + x<width) {
						cnt++;
						sum += content[y*stride + 4 * (x + i) + c];
					}
				}
				content[y*stride + 4 * x + c] = sum / cnt;
			}
		}
	}
}

void Graphics::fakeGaussianBlur(IMAGE*img, int radius) {
	for (int i = 0; i < radius / 5; i++) {
		fastBlur(img, radius);
	}
}

void Graphics::RGBOffset(IMAGE*img,int ro, int go, int bo) {
	int offset[] = { bo, go, ro };
	uint32_t height = img->getheight(), width = img->getwidth(), stride = 4 * width;
	byte*ptr = (byte*)GetImageBuffer(img);
	for (int j = 0; j<height; j++) {
		for (int i = 0; i<width; i++) {
			for (int c = 0; c<3; c++) {
				if ((*ptr) + offset[c]>255) (*ptr) = 255;
				else if ((*ptr) + offset[c]<0) (*ptr) = 0;
				else (*ptr) += offset[c];
				ptr++;
			}
			ptr ++;
		}
		//ptr += stride - width * 3;
	}
}