#pragma once
#include <iostream>
#include <Windows.h>

class GameWindowBuffer
{
public:
	int w = 0;
	int h = 0;
	BYTE *memory = nullptr;
	void ResetWindowBuffer(HWND hwnd, BITMAPINFO *bitmapinfo);
	void ClearWindow();
};