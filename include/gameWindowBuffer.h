#pragma once
#include <iostream>
#include <Windows.h>

class GameWindowBuffer
{
public:
	int w = 0;
	int h = 0;
	unsigned char* memory = 0;
	void ResetWindowBuffer(HWND hwnd, BITMAPINFO* bitmapInfo);
	void ClearWindow();
};