#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <mysql.h>
#pragma comment(lib, "libmySQL.lib")
using namespace std;

#define UP 72
#define DOWN 80
#define SUBMIT 4

class DBconnection {
private:
	MYSQL* conn;

public:
	MYSQL* DBconn() {
		conn = mysql_init(0);
		mysql_options(conn, MYSQL_SET_CHARSET_NAME, "euckr");
		mysql_options(conn, MYSQL_INIT_COMMAND, "SET NAMES euckr");
		conn = mysql_real_connect(conn, "localhost", "root", "111111", "parking", 3307, NULL, 0);
		return conn;
	}

	void init() {
		system("mode con cols=76 lines=30 | title �� �� �� Ʈ �� �� �� �� �� �� �� ��");

		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO ConsoleCursor;
		ConsoleCursor.bVisible = 0;
		ConsoleCursor.dwSize = 1;
		SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
	}
};

class Parking :public DBconnection {
private:
	MYSQL_ROW row;
	MYSQL_RES* res;
public:
	void gotoxy(int x, int y) {
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos;
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition(consoleHandle, pos);
	}

	int menuDraw() {
		int x = 26;
		int y = 12;
		gotoxy(x - 2, y); //-2�� ������ >�� ����ϱ� ����
		cout << ">       �� �� �� �� ";
		gotoxy(x, y + 1);
		cout << "      �� �� �� �� ";
		gotoxy(x, y + 2);
		cout << "�� �� �� ġ �� �� �� �� ";
		gotoxy(x, y + 3);
		cout << "         �� �� ";
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

	int ParkingIn(MYSQL* conn) {
		system("cls");
		string carNum, carName, carTel, carFloor, carPark, answer;

		gotoxy(22, 14);
		cout << "������ȣ�� �Է��ϼ���: ";
		cin >> carNum;

		if (carNum.length() == 8 || carNum.length() == 9) {
			string query = "select * from car where carNum='" + carNum + "'";
			int qstate = mysql_query(conn, query.c_str());
			if (!qstate) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				if (row == 0) { //�����Ǿ� ���� ���� ���̸�
					system("cls");
					gotoxy(0, 4);
					ShowParkingCurrent();
					gotoxy(26, 13);
					cout << "������ ���� �Է��ϼ���." << endl;
					gotoxy(21, 14);
					cout << "������ ��ġ(�����̽��ٷ� ����): ";
					cin >> carFloor >> carPark;
					string sql = "select * from car where carFloor='" + carFloor + "' and carPark='" + carPark + "'";
					int qstate = mysql_query(conn, sql.c_str());
					if (!qstate) {
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						if (row != 0) {
							system("cls");
							gotoxy(23, 14);
							cout << "�̹� �����Ǿ� �ִ� ���Դϴ�." << endl;
							gotoxy(38, 28);
							cout << "�ڷ� ������ �����̽��ٸ� ��������...";
						}
						else if (carFloor == "B2" || carFloor == "B1" || carFloor == "1" || carFloor == "2") {
							if (stoi(carPark) > 0 && stoi(carPark) <= 20) {
								system("cls");
								gotoxy(26, 13);
								cout << "�̸��� �Է��ϼ���: ";
								cin >> carName;

								gotoxy(23, 14);
								cout << "����ó�� �Է��ϼ���: ";
								cin >> carTel;

								if (carTel.length() == 11) {
									system("cls");
									gotoxy(26, 12);
									cout << "������ȣ: " + carNum + "��" << endl;
									gotoxy(26, 13);
									cout << "�̸�: " + carName + "��" << endl;
									gotoxy(26, 14);
									cout << "����ó: " + carTel << endl;
									gotoxy(26, 15);
									cout << "���� ��ġ: " + carFloor + "�� " << carPark + "��" << endl;
									gotoxy(22, 16);
									cout << "�����Ͻðڽ��ϱ�?(��/�ƴϿ�): ";
									cin >> answer;

									if (answer == "��" || answer == "��") {
										string query = "insert into car(carNum,userName,userTel,carFloor,carPark) values ('" + carNum + "', '" + carName + "' , '" + carTel + "' , '" + carFloor + "','" + carPark + "') ";
										int qstate = 0;
										qstate = mysql_query(conn, query.c_str());
										if (qstate != 0) {
											cout << "�����" << mysql_errno(conn) << endl;
										}
										else
										{
											system("cls");
											gotoxy(27, 14);
											cout << "���� �Ϸ�Ǿ����ϴ�." << endl;
											gotoxy(38, 28);
											cout << "�ڷ� ������ �����̽��ٸ� ��������...";
										}
									}
									else if (answer == "�ƴϿ�" || answer == "�ƴϿ�") {
										gotoxy(38, 28);
										cout << "�ڷ� ������ �����̽��ٸ� ��������...";
									}
								}
								else {
									system("cls");
									gotoxy(22, 14);
									cout << "����� �� ����ó�� �Է��ϼ���.";
									gotoxy(38, 28);
									cout << "�ڷ� ������ �����̽��ٸ� ��������...";
								}
							}
							else {
								system("cls");
								gotoxy(21, 14);
								cout << "����� �� ���������� �Է��ϼ���." << endl;
								gotoxy(38, 28);
								cout << "�ڷ� ������ �����̽��ٸ� ��������...";
							}
						}
						else {
							system("cls");
							gotoxy(24, 14);
							cout << "����� �� ���� �Է��ϼ���." << endl;
							gotoxy(38, 28);
							cout << "�ڷ� ������ �����̽��ٸ� ��������...";
						}
					}
					else {
						system("cls");
						cout << "��� ����" << mysql_errno(conn) << endl;
					}
				}
				else {
					system("cls");
					gotoxy(22, 14);
					cout << "�̹� �����Ǿ� �ִ� �����Դϴ�." << endl;
					gotoxy(38, 28);
					cout << "�ڷ� ������ �����̽��ٸ� ��������...";
				}
			}
			else {
				system("cls");
				cout << "��� ����" << mysql_errno(conn) << endl;
			}
		}
		else {
			system("cls");
			gotoxy(22, 14);
			cout << "����� �� ������ȣ�� �Է��ϼ���." << endl;
			gotoxy(38, 28);
			cout << "�ڷ� ������ �����̽��ٸ� ��������...";
		}

		goBack();
		return 0;
	}

	int ParkingOut(MYSQL* conn) {
		system("cls"); //ȭ�� ��� ����� ����
		string carNum, name, tel, answer;

		gotoxy(19, 14);
		cout << "������ ������ȣ�� �Է��ϼ���: ";
		cin >> carNum;

		string query = "select * from car where carNum='" + carNum + "'";
		const char* c = query.c_str();
		int qstate = mysql_query(conn, c);
		if (!qstate) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			if (row == 0) {
				system("cls");
				gotoxy(22, 14);
				cout << "�����Ǿ� ���� ���� �����Դϴ�." << endl;
				gotoxy(38, 28);
				cout << "�ڷ� ������ �����̽��ٸ� ��������...";
			}
			else {
				system("cls");
				gotoxy(22, 13);
				cout << "�̸��� �Է��ϼ���: ";
				cin >> name;

				gotoxy(22, 14);
				cout << "����ó�� �Է��ϼ���: ";
				cin >> tel;

				gotoxy(22, 15);
				cout << "�����Ͻðڽ��ϱ�?(��/�ƴϿ�): ";
				cin >> answer;
				if (answer == "��" || answer == "��") {
					string sql = "select userName,userTel from car where carNum='" + carNum + "'";
					int qstate = mysql_query(conn, sql.c_str());
					if (!qstate) {
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						if (row[0] == name && row[1] == tel) {
							string query = "delete from car where carNum='" + carNum + "'";
							int state = mysql_query(conn, query.c_str());
							if (state != 0) {
								cout << "�����" << mysql_errno(conn) << endl;
							}
							else {
								system("cls");
								gotoxy(28, 14);
								cout << "���� �Ϸ�Ǿ����ϴ�." << endl;
								gotoxy(38, 28);
								cout << "�ڷ� ������ �����̽��ٸ� ��������...";
							}
						}
						else {
							system("cls");
							gotoxy(23, 14);
							cout << "�̸� �Ǵ� ��ȭ��ȣ�� Ʋ���ϴ�.";
							gotoxy(38, 28);
							cout << "�ڷ� ������ �����̽��ٸ� ��������...";
						}
					}
					else {
						cout << "��� ����" << mysql_errno(conn) << endl;
					}
				}
				else if (answer == "�ƴϿ�" || answer == "�ƴϿ�") {
					gotoxy(38, 28);
					cout << "�ڷ� ������ �����̽��ٸ� ��������...";
				}
			}
		}
		else {
			cout << "��� ����" << mysql_errno(conn) << endl;
		}

		goBack();
		return 0;
	}

	int SearchCar(MYSQL* conn) {
		system("cls"); //ȭ�� ��� ����� ����
		string carNum;

		gotoxy(22, 14);
		cout << "������ȣ�� �Է��ϼ���: ";
		cin >> carNum;

		string query = "select * from car where carNum='" + carNum + "'";
		const char* c = query.c_str();
		int qstate = mysql_query(conn, c);
		if (!qstate) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			system("cls");
			if (row == 0) {
				gotoxy(22, 14);
				cout << "�����Ǿ� ���� ���� �����Դϴ�." << endl;
				gotoxy(38, 28);
				cout << "�ڷ� ������ �����̽��ٸ� ��������...";
			}
			else {
				gotoxy(22, 13);
				cout << row[6] << "�� �����Ǿ�����," << endl;
				gotoxy(17, 14);
				cout << "������ȣ " << carNum << "���� ��ġ�� " << row[4] << "�� " << row[5] << "���Դϴ�." << endl;
				gotoxy(38, 28);
				cout << "�ڷ� ������ �����̽��ٸ� ��������...";
			}
		}
		else {
			cout << "��� ����" << mysql_errno(conn) << endl;
		}
		goBack();
		return 0;
	}

	int goBack() {
		while (1) {
			if (keyControl() == SUBMIT)
				break;
			int n = keyControl();
			switch (n) {
			case SUBMIT: {
				return 0;
			}
			}
		}
		return 0;
	}

};




int main() {
	Parking pk;
	MYSQL* conn = pk.DBconn();
	pk.init();
	
	while (1) {
		int menuCode = pk.menuDraw();
		if (menuCode == 0) {
			pk.ParkingIn(conn); //�����ϱ�
		}
		else if (menuCode == 1) {
			pk.ParkingOut(conn);//�����ϱ�
		}
		else if (menuCode == 2) {
			pk.SearchCar(conn);
		}
		else if (menuCode == 3) {
			return 0; //����
		}
		system("cls");
	}
	return 0;
}