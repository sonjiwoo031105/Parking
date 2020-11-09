#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
#define UP 72
#define DOWN 80
#define SUBMIT 4
//메인화면 돌아가기 기능도 구현해 지우야

/*함수들*/
int keyControl();
void init();
int menuDraw();
int ParkingDraw();
void Parking();
void gotoxy(int, int); //(x, y)만큼 커서가 이동하는 함수
int ShowParkingCurrent(); 

int keyControl() {
	char temp;
	while (1) {
		if (_kbhit()) {
			temp = _getch();
			if (temp == -32) {
				temp = _getch();
				switch (temp) {
				case UP:
					return UP;
					break;
				case DOWN:
					return DOWN;
					break;
				}
			}
			if (temp == ' ') {
				return SUBMIT;
			}
		}
		return 0;
	}
}
void init() {
	system("mode con cols=76 lines=30 | title 대 형 마 트 주 차 관 리 프 로 그 램");
	
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}
int menuDraw() {
	int x = 24;
	int y = 12;
	gotoxy(x-2, y); //-2한 이유는 >를 출력하기 위해
	cout << "> 주 차 하 기 ";
	gotoxy(x, y+1);
	cout << "출 차 하 기 ";
	gotoxy(x, y+2);
	cout << "차 량 위 치 검 색 하 기 ";
	gotoxy(x, y+3);
	cout << "종 료 ";
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 12) { //y는 12~14까지만 이동
				gotoxy(x - 2, y); // x-2하는 이유는 >를 두 칸 이전에 출력하기 위해서
				cout << " "; //원래 위치를 지우고
				gotoxy(x - 2, --y); //새로 이동한 위치로 이동하여
				cout << ">"; //다시 그리기
			}
			break;
		}
		case DOWN: {
			if (y < 15) { //최대 15
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << ">"; 
			}
			break;
		}
		case SUBMIT: {
			return y - 12; //y 시작 위치가 12였으므로 y-12를 하면 0,1,2 세 숫자를 받을 수 있다.
		}
		}
	}
	return 0;
}
int ParkingDraw() {
	system("cls"); //화면 모두 지우고 시작
	int x = 24;
	int y = 12;
	string carNum, carName, carTel, carPark, answer;
	string s1, s2;
	
	
	gotoxy(x , y); 
	cout << "차량번호를 입력하세요: ";
	cin >> carNum;

	gotoxy(x, y + 1);
	cout << "이름을 입력하세요: ";
	cin >> carName;

	gotoxy(x, y + 2);
	cout << "연락처를 입력하세요: ";
	cin >> carTel;

	gotoxy(x, y + 3);
	cout << "종 료 ";
	while (1) {
		int n = keyControl();
		switch (n) {
		case SUBMIT: {
			return y - 12; //y 시작 위치가 12였으므로 y-12를 하면 0,1,2 세 숫자를 받을 수 있다.
		}
		}
	}
	return 0;
}

void Parking() {
	system("cls"); //화면 모두 지우고 시작
	string carNum, carName, carTel, carPark, answer;
	string s1, s2;
	cout << "차량번호를 입력하세요: ";
	cin >> carNum;
	cout << "이름을 입력하세요: ";
	cin >> carName;
	cout << "연락처를 입력하세요: ";
	cin >> carTel;
	ShowParkingCurrent();
	cout << "주차할 곳을 입력해주세요." << endl;
	cout << "층수와 위치(스페이스바로 구분) : ";
	cin >> s1 >> s2;
	system("cls");

	cout << "차량번호: " + carNum + "번" << endl;
	cout << "이름: " + carName + "님" << endl;
	cout << "연락처: " + carTel << endl;
	cout << "주차 위치: " +  s1 + "층 " << s2 + "번" << endl;
	cout << "주차하시겠습니까?(y/n): ";
	cin >> answer;
	


	while (1) {
		if (keyControl() == SUBMIT)
			break;
	}
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}


int ShowParkingCurrent() {
	cout << "[2층]---------------" << endl;
	cout << "[01][02][03][04][05]" << endl;
	cout << "[06][07][08][09][10]" << endl;
	cout << "[11][12][13][14][15]" << endl;
	cout << "[16][17][18][19][20]" << endl;
	cout << "[1층]---------------" << endl;
	cout << "[01][02][03][04][05]" << endl;
	cout << "[06][07][08][09][10]" << endl;
	cout << "[11][12][13][14][15]" << endl;
	cout << "[16][17][18][19][20]" << endl;
	cout << "[B1층]---------------" << endl;
	cout << "[01][02][03][04][05]" << endl;
	cout << "[06][07][08][09][10]" << endl;
	cout << "[11][12][13][14][15]" << endl;
	cout << "[16][17][18][19][20]" << endl;
	cout << "[B2층]---------------" << endl;
	cout << "[01][02][03][04][05]" << endl;
	cout << "[06][07][08][09][10]" << endl;
	cout << "[11][12][13][14][15]" << endl;
	cout << "[16][17][18][19][20]" << endl;
	return 0;
}


int main() {
	init();
	while (1) {
		int menuCode = menuDraw();
		if (menuCode == 0) {
			ParkingDraw(); //주차하기
		}
		else if (menuCode == 1) {
			//출차하기
		}
		else if (menuCode == 2) {
			//차량위치검색
		}
		else if (menuCode == 3) {
			return 0; //종료
		}
		system("cls");
	}
	return 0;
}