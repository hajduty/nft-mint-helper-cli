#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <tlhelp32.h>
#include <fstream>
#include <sysinfoapi.h>
#include <ctime>

namespace mains {
	int tabs = 20;
	int opt = 1;
	std::string url;
	int posY, posX;
	int y, x;
	bool xFail, yFail, urlFail = false;
	int h, m, s;
	void color(int code);
	std::string time_o;
}