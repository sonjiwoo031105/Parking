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
		system("mode con cols=76 lines=30 | title 대 형 마 트 주 차 관 리 프 로 그 램");

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
		gotoxy(x - 2, y); //-2한 이유는 >를 출력하기 위해
		cout << ">       주 차 하 기 ";
		gotoxy(x, y + 1);
		cout << "      출 차 하 기 ";
		gotoxy(x, y + 2);
		cout << "차 량 위 치 검 색 하 기 ";
		gotoxy(x, y + 3);
		cout << "         종 료 ";
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

	int ParkingIn(MYSQL* conn) {
		system("cls");
		string carNum, carName, carTel, carFloor, carPark, answer;

		gotoxy(22, 14);
		cout << "차량번호를 입력하세요: ";
		cin >> carNum;

		if (carNum.length() == 8 || carNum.length() == 9) {
			string query = "select * from car where carNum='" + carNum + "'";
			int qstate = mysql_query(conn, query.c_str());
			if (!qstate) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				if (row == 0) { //주차되어 있지 않은 차이면
					system("cls");
					gotoxy(0, 4);
					ShowParkingCurrent();
					gotoxy(26, 13);
					cout << "주차할 곳을 입력하세요." << endl;
					gotoxy(21, 14);
					cout << "층수와 위치(스페이스바로 구분): ";
					cin >> carFloor >> carPark;
					string sql = "select * from car where carFloor='" + carFloor + "' and carPark='" + carPark + "'";
					int qstate = mysql_query(conn, sql.c_str());
					if (!qstate) {
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						if (row != 0) {
							system("cls");
							gotoxy(23, 14);
							cout << "이미 주차되어 있는 곳입니다." << endl;
							gotoxy(38, 28);
							cout << "뒤로 가려면 스페이스바를 누르세요...";
						}
						else if (carFloor == "B2" || carFloor == "B1" || carFloor == "1" || carFloor == "2") {
							if (stoi(carPark) > 0 && stoi(carPark) <= 20) {
								system("cls");
								gotoxy(26, 13);
								cout << "이름을 입력하세요: ";
								cin >> carName;

								gotoxy(23, 14);
								cout << "연락처를 입력하세요: ";
								cin >> carTel;

								if (carTel.length() == 11) {
									system("cls");
									gotoxy(26, 12);
									cout << "차량번호: " + carNum + "번" << endl;
									gotoxy(26, 13);
									cout << "이름: " + carName + "님" << endl;
									gotoxy(26, 14);
									cout << "연락처: " + carTel << endl;
									gotoxy(26, 15);
									cout << "주차 위치: " + carFloor + "층 " << carPark + "번" << endl;
									gotoxy(22, 16);
									cout << "주차하시겠습니까?(예/아니요): ";
									cin >> answer;

									if (answer == "예" || answer == "네") {
										string query = "insert into car(carNum,userName,userTel,carFloor,carPark) values ('" + carNum + "', '" + carName + "' , '" + carTel + "' , '" + carFloor + "','" + carPark + "') ";
										int qstate = 0;
										qstate = mysql_query(conn, query.c_str());
										if (qstate != 0) {
											cout << "디비문제" << mysql_errno(conn) << endl;
										}
										else
										{
											system("cls");
											gotoxy(27, 14);
											cout << "주차 완료되었습니다." << endl;
											gotoxy(38, 28);
											cout << "뒤로 가려면 스페이스바를 누르세요...";
										}
									}
									else if (answer == "아니요" || answer == "아니오") {
										gotoxy(38, 28);
										cout << "뒤로 가려면 스페이스바를 누르세요...";
									}
								}
								else {
									system("cls");
									gotoxy(22, 14);
									cout << "제대로 된 연락처를 입력하세요.";
									gotoxy(38, 28);
									cout << "뒤로 가려면 스페이스바를 누르세요...";
								}
							}
							else {
								system("cls");
								gotoxy(21, 14);
								cout << "제대로 된 주차공간을 입력하세요." << endl;
								gotoxy(38, 28);
								cout << "뒤로 가려면 스페이스바를 누르세요...";
							}
						}
						else {
							system("cls");
							gotoxy(24, 14);
							cout << "제대로 된 층을 입력하세요." << endl;
							gotoxy(38, 28);
							cout << "뒤로 가려면 스페이스바를 누르세요...";
						}
					}
					else {
						system("cls");
						cout << "디비 에러" << mysql_errno(conn) << endl;
					}
				}
				else {
					system("cls");
					gotoxy(22, 14);
					cout << "이미 주차되어 있는 차량입니다." << endl;
					gotoxy(38, 28);
					cout << "뒤로 가려면 스페이스바를 누르세요...";
				}
			}
			else {
				system("cls");
				cout << "디비 에러" << mysql_errno(conn) << endl;
			}
		}
		else {
			system("cls");
			gotoxy(22, 14);
			cout << "제대로 된 차량번호를 입력하세요." << endl;
			gotoxy(38, 28);
			cout << "뒤로 가려면 스페이스바를 누르세요...";
		}

		goBack();
		return 0;
	}

	int ParkingOut(MYSQL* conn) {
		system("cls"); //화면 모두 지우고 시작
		string carNum, name, tel, answer;

		gotoxy(19, 14);
		cout << "출차할 차량번호를 입력하세요: ";
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
				cout << "주차되어 있지 않은 차량입니다." << endl;
				gotoxy(38, 28);
				cout << "뒤로 가려면 스페이스바를 누르세요...";
			}
			else {
				system("cls");
				gotoxy(22, 13);
				cout << "이름을 입력하세요: ";
				cin >> name;

				gotoxy(22, 14);
				cout << "연락처를 입력하세요: ";
				cin >> tel;

				gotoxy(22, 15);
				cout << "출차하시겠습니까?(예/아니요): ";
				cin >> answer;
				if (answer == "예" || answer == "네") {
					string sql = "select userName,userTel from car where carNum='" + carNum + "'";
					int qstate = mysql_query(conn, sql.c_str());
					if (!qstate) {
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						if (row[0] == name && row[1] == tel) {
							string query = "delete from car where carNum='" + carNum + "'";
							int state = mysql_query(conn, query.c_str());
							if (state != 0) {
								cout << "디비문제" << mysql_errno(conn) << endl;
							}
							else {
								system("cls");
								gotoxy(28, 14);
								cout << "출차 완료되었습니다." << endl;
								gotoxy(38, 28);
								cout << "뒤로 가려면 스페이스바를 누르세요...";
							}
						}
						else {
							system("cls");
							gotoxy(23, 14);
							cout << "이름 또는 전화번호가 틀립니다.";
							gotoxy(38, 28);
							cout << "뒤로 가려면 스페이스바를 누르세요...";
						}
					}
					else {
						cout << "디비 에러" << mysql_errno(conn) << endl;
					}
				}
				else if (answer == "아니요" || answer == "아니오") {
					gotoxy(38, 28);
					cout << "뒤로 가려면 스페이스바를 누르세요...";
				}
			}
		}
		else {
			cout << "디비 에러" << mysql_errno(conn) << endl;
		}

		goBack();
		return 0;
	}

	int SearchCar(MYSQL* conn) {
		system("cls"); //화면 모두 지우고 시작
		string carNum;

		gotoxy(22, 14);
		cout << "차량번호를 입력하세요: ";
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
				cout << "주차되어 있지 않은 차량입니다." << endl;
				gotoxy(38, 28);
				cout << "뒤로 가려면 스페이스바를 누르세요...";
			}
			else {
				gotoxy(22, 13);
				cout << row[6] << "에 주차되었으며," << endl;
				gotoxy(17, 14);
				cout << "차량번호 " << carNum << "번의 위치는 " << row[4] << "층 " << row[5] << "번입니다." << endl;
				gotoxy(38, 28);
				cout << "뒤로 가려면 스페이스바를 누르세요...";
			}
		}
		else {
			cout << "디비 에러" << mysql_errno(conn) << endl;
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
			pk.ParkingIn(conn); //주차하기
		}
		else if (menuCode == 1) {
			pk.ParkingOut(conn);//출차하기
		}
		else if (menuCode == 2) {
			pk.SearchCar(conn);
		}
		else if (menuCode == 3) {
			return 0; //종료
		}
		system("cls");
	}
	return 0;
}