#include "key.h"

int key(int py, int px) {
	while (true) {
		if (GetAsyncKeyState('K')) {
			Beep(200, 60);
			Beep(100, 60);

			POINT point;
			if (GetCursorPos(&point)) {
				px = point.x;
				py = point.y;

				std::ofstream x;
				x.open("x.txt");
				x << point.x;
				x.close();

				std::ofstream y;
				y.open("y.txt");
				y << point.y;
				y.close();
				return py, px;
			}
			break;
		}
	}
}

void click(int x, int y) {
	Sleep(6);
	PostMessage(GetForegroundWindow(), WM_LBUTTONDOWN, MK_RBUTTON, MAKELPARAM(x, y));
	PostMessage(GetForegroundWindow(), WM_LBUTTONUP, MK_RBUTTON, MAKELPARAM(x, y));
	PostMessage(GetForegroundWindow(), WM_LBUTTONDOWN, MK_RBUTTON, MAKELPARAM(x, y));
	PostMessage(GetForegroundWindow(), WM_LBUTTONUP, MK_RBUTTON, MAKELPARAM(x, y));
	PostMessage(GetForegroundWindow(), WM_LBUTTONDOWN, MK_RBUTTON, MAKELPARAM(x, y));
	PostMessage(GetForegroundWindow(), WM_LBUTTONUP, MK_RBUTTON, MAKELPARAM(x, y));
	std::cout << "Clicked";
	Sleep(8);
}