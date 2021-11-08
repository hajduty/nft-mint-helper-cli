#include "main.h"
#include "tabChange.h"
#include "fastDupe.h"
#include "key.h"
#include "time.h"
#include "click.h"

//Changes console output color
auto mains::color(int color) -> void {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//Loads saved values
void loadSave() {
	std::ifstream conf;
	conf.open("tempConf.txt");
	std::string url;
	if (conf.fail()) {
		std::cout << "No previous URL found\n\n";
		mains::urlFail = true;
	}
	else {
		while (conf >> url) {
			std::cout << "URL has been set to " << url << " " << mains::url << "\n\n";
			url = url;
			mains::url = url;
		}
	}
	conf.close();

	std::ifstream x;
	x.open("x.txt");
	int xe;
	if (x.fail()) {
		std::cout << "No previous XCord found\n\n";
		mains::xFail = true;
	}
	else {
		while (x >> xe) {
			std::cout << "XCord has been set to " << xe << "\n\n";
			mains::x = xe;
		}
	}
	x.close();

	std::ifstream y;
	y.open("y.txt");
	int ye;
	if (y.fail()) {
		std::cout << "No previous YCord found\n\n";
		mains::yFail = true;
	}
	else {
		while (y >> ye) {
			std::cout << "YCord has been set to " << ye << "\n\n";
			mains::y = ye;
		}
	}
	y.close();
}

//menu shit
void startAsk() {
	loadSave();
	if (mains::xFail == true || mains::yFail == true) {
		std::cout << "Saving mouse location whenever you press ""K"".\n";
		if (mains::urlFail != true) {
			system(("start msedge.exe " + mains::url).c_str());
		}
		key(mains::x, mains::y);
		system("cls");
	}

	if (mains::urlFail == true) {
		std::cout << "Chrome or Edge?\n1 = Edge\n2 = Chrome\nAnswer: ";
		std::cin >> mains::opt;
		std::cout << "Enter URL: \n";
		std::cin >> mains::url;
		std::cout << "How many tabs ";
		std::cin >> mains::tabs;

		std::ofstream urls;
		urls.open("tempConf.txt");
		urls << mains::url;
		urls.close();
	}
	std::cout << "Mouse position registered to " << mains::x << "," << mains::y << "\n";
	Sleep(50);
}

int main() {
	while (true) {
		//Changes window size and outputs splash message
		int start;
		HWND console = GetConsoleWindow();
		RECT ConsoleRect;
		GetWindowRect(console, &ConsoleRect);
		MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 450, 500, TRUE);

		mains::color(12);
		std::cout << "          __  ________   ____________________\n";
		std::cout << "         /  |/  /  _/ | / /_  __/ ____/ __  /\n";
		std::cout << "        / /|_/ // //  |/ / / / / __/ / /_/ / \n";
		std::cout << "       / /  / // // /|  / / / / /___/ _, _/  \n";
		std::cout << "      /_/  /_/___/_/ |_/ /_/ /_____/_/ |_|   \n\n";

		std::cout << "       FAST SPAM = 1    |    CLICK @ TIME = 2\n";
		mains::color(15);
		std::cout << std::endl << "TYPE: ";
		std::cin >> start;

		Sleep(200);
		system("cls");
		mains::color(12);
		std::cout << "PRESS 'U' TO EXIT WHEN CREATING TABS/CLICKING\n";
		mains::color(15);
		Sleep(1500);

		//If user presses fast spam, skips time stuff.
		if (start == 1) {
			startAsk();
			Sleep(50);
			mains::opt = 1;
			if (mains::opt == 1) {
				//Starts edge and goes to specified url
				system(("start msedge.exe " + mains::url).c_str());
				Sleep(1000);

				//Creates tabs, currently does by simulating keyboard input.
				for (int i = 0; i < mains::tabs; i++) {
					//Exits program if user presses U
					if (GetAsyncKeyState('U')) {
						std::cout << "\nProgram terminated\n";
						system("pause");
						return 0;
					}
					fastDupe();
					Sleep(20);
				}

				Sleep(1000);

				std::cout << "clicking\n" << "tabbing\n";

				//Tab & click loop, tabs & clicks basically.
				for (int i = 0; i < ((mains::tabs * 10) * 3); i++) {
					if (GetAsyncKeyState('U')) {
						//Exits program if user presses U
						std::cout << "\nProgram terminated\n";
						system("pause");
						return 0;
					}

					tabChange();
					Sleep(5);
					click(mains::x, mains::y);
					Sleep(5);
				}
			}
			std::cout << "\n\nExit?\n\n";
			std::string opti;
			std::cin >> opti;
			if (opti == "yes") {
				break;
			}
		}
		else {
			//If user wants to make the program click & change tabs at specific time
			std::string ti = currentTime(); //Gets current time
			std::cout << "Current time is " << ti << std::endl;
			std::cout << "Enter hour: \nExample: ""18""\n\nHour:";
			std::cin >> mains::h;
			std::cout << "Enter minute: \nExample: ""30""\n\nMinute:";
			std::cin >> mains::m;
			std::cout << "Enter second: \nExample: ""00""\n\nSecond:";
			std::cin >> mains::s;

			startAsk(); //gets url & tab numbers
			Sleep(50);
			if (mains::opt == 1) {
				system(("start msedge.exe " + mains::url).c_str());
				Sleep(1000);

				//Duplicates tabs
				for (int i = 0; i < mains::tabs; i++) {
					//Exits if user presses U
					if (GetAsyncKeyState('U')) {
						std::cout << "\nProgram terminated\n";
						system("pause");
						return 0;
					}
					fastDupe(); //Tab dupe
					Sleep(20);
				}

				Sleep(1000);
				getTime(mains::h, mains::m, mains::s); //Waits until time is as user specified

				for (int i = 0; i < ((mains::tabs * 10) * 3); i++) {
					//Exits if user presses U
					if (GetAsyncKeyState('U')) {
						std::cout << "\nProgram terminated\n";
						system("pause");
						return 0;
					}

					tabChange(); //Changes tab
					Sleep(5);
					click(mains::x, mains::y); //Clicks at loc
					Sleep(5);
				}
			}
		}
	}
}