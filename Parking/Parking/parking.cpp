#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
#define UP 72
#define DOWN 80
#define SUBMIT 4
//����ȭ�� ���ư��� ��ɵ� ������ �����

/*�Լ���*/
int keyControl();
void init();
int menuDraw();
int ParkingDraw();
void Parking();
void gotoxy(int, int); //(x, y)��ŭ Ŀ���� �̵��ϴ� �Լ�
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
	system("mode con cols=76 lines=30 | title �� �� �� Ʈ �� �� �� �� �� �� �� ��");
	
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}
int menuDraw() {
	int x = 24;
	int y = 12;
	gotoxy(x-2, y); //-2�� ������ >�� ����ϱ� ����
	cout << "> �� �� �� �� ";
	gotoxy(x, y+1);
	cout << "�� �� �� �� ";
	gotoxy(x, y+2);
	cout << "�� �� �� ġ �� �� �� �� ";
	gotoxy(x, y+3);
	cout << "�� �� ";
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 12) { //y�� 12~14������ �̵�
				gotoxy(x - 2, y); // x-2�ϴ� ������ >�� �� ĭ ������ ����ϱ� ���ؼ�
				cout << " "; //���� ��ġ�� �����
				gotoxy(x - 2, --y); //���� �̵��� ��ġ�� �̵��Ͽ�
				cout << ">"; //�ٽ� �׸���
			}
			break;
		}
		case DOWN: {
			if (y < 15) { //�ִ� 15
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << ">"; 
			}
			break;
		}
		case SUBMIT: {
			return y - 12; //y ���� ��ġ�� 12�����Ƿ� y-12�� �ϸ� 0,1,2 �� ���ڸ� ���� �� �ִ�.
		}
		}
	}
	return 0;
}
int ParkingDraw() {
	system("cls"); //ȭ�� ��� ����� ����
	int x = 24;
	int y = 12;
	string carNum, carName, carTel, carPark, answer;
	string s1, s2;
	
	
	gotoxy(x , y); 
	cout << "������ȣ�� �Է��ϼ���: ";
	cin >> carNum;

	gotoxy(x, y + 1);
	cout << "�̸��� �Է��ϼ���: ";
	cin >> carName;

	gotoxy(x, y + 2);
	cout << "����ó�� �Է��ϼ���: ";
	cin >> carTel;

	gotoxy(x, y + 3);
	cout << "�� �� ";
	while (1) {
		int n = keyControl();
		switch (n) {
		case SUBMIT: {
			return y - 12; //y ���� ��ġ�� 12�����Ƿ� y-12�� �ϸ� 0,1,2 �� ���ڸ� ���� �� �ִ�.
		}
		}
	}
	return 0;
}

void Parking() {
	system("cls"); //ȭ�� ��� ����� ����
	string carNum, carName, carTel, carPark, answer;
	string s1, s2;
	cout << "������ȣ�� �Է��ϼ���: ";
	cin >> carNum;
	cout << "�̸��� �Է��ϼ���: ";
	cin >> carName;
	cout << "����ó�� �Է��ϼ���: ";
	cin >> carTel;
	ShowParkingCurrent();
	cout << "������ ���� �Է����ּ���." << endl;
	cout << "������ ��ġ(�����̽��ٷ� ����) : ";
	cin >> s1 >> s2;
	system("cls");

	cout << "������ȣ: " + carNum + "��" << endl;
	cout << "�̸�: " + carName + "��" << endl;
	cout << "����ó: " + carTel << endl;
	cout << "���� ��ġ: " +  s1 + "�� " << s2 + "��" << endl;
	cout << "�����Ͻðڽ��ϱ�?(y/n): ";
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
	cout << "[2��]---------------" << endl;
	cout << "[01][02][03][04][05]" << endl;
	cout << "[06][07][08][09][10]" << endl;
	cout << "[11][12][13][14][15]" << endl;
	cout << "[16][17][18][19][20]" << endl;
	cout << "[1��]---------------" << endl;
	cout << "[01][02][03][04][05]" << endl;
	cout << "[06][07][08][09][10]" << endl;
	cout << "[11][12][13][14][15]" << endl;
	cout << "[16][17][18][19][20]" << endl;
	cout << "[B1��]---------------" << endl;
	cout << "[01][02][03][04][05]" << endl;
	cout << "[06][07][08][09][10]" << endl;
	cout << "[11][12][13][14][15]" << endl;
	cout << "[16][17][18][19][20]" << endl;
	cout << "[B2��]---------------" << endl;
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
			ParkingDraw(); //�����ϱ�
		}
		else if (menuCode == 1) {
			//�����ϱ�
		}
		else if (menuCode == 2) {
			//������ġ�˻�
		}
		else if (menuCode == 3) {
			return 0; //����
		}
		system("cls");
	}
	return 0;
}