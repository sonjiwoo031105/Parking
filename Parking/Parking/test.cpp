#include <iostream> 
using namespace std; 
class Human { 
private: 
int age;
char name[10];
char hobby[20];
public:
	Human(int _age, char * _name, char * _hobby) : age(_age) { 
		strcpy(name, _name);
		strcpy(hobby, _hobby);
	} 
	void getup() { cout << "���!" << endl; } 
	void sleep() { cout << "��ħ!" << endl; } 
	void eat() { cout << "�Ļ�!" << endl; } 
	void study() { cout << "����!" << endl; } 
	void showInfo() { 
		cout << "�̸�: " << name << endl; cout << "����: " << age << endl; cout << "���: " << hobby << endl; 
	} 
}; 
class Student : public Human { 
private: 
char school[30]; 
public: 
	Student(int _age, char * _name, char * _hobby, char * _school) : Human(_age, _name, _hobby) { 
		strcpy(school, _school); 
	} 
	  void schoolInfo() { showInfo(); cout << "�Ҽ� �б�: " << school << endl; } 
}; 
int main() { 
	Student stu(18, "��ö��", "���α׷���", "�ڹٰ���б�"); 
	stu.schoolInfo(); stu.getup(); stu.eat(); stu.study(); stu.sleep(); 
	return 0; 
}

