#define SOCKET int // �̰� ���־�� �Ѵٰ� �ϴ����
#include<stdio.h>
#include<string.h>
#include<mysql.h> // MySQL�� �����ϱ� ���� �� �ʿ��� �ش� ����

// Database�� �����ϱ� ���� �⺻���� ����
#define HOST "localhost" // ������ host �ּ�
#define USER "root" // ����� �̸�
#define PASS "111111" // �н�����
#define NAME "parking" // ������ �����ͺ��̽� �̸�

int main(void) {

	char* query = "select * from parking"; // ������ ����
	int len;

	MYSQL* conn_ptr; // MySQL���� ������ ���
	MYSQL_RES* res; // ������ ���� ����� �޴� ����
	MYSQL_ROW row; // ������ ���� ���� ������ ���� ����ִ� ����

	conn_ptr = mysql_init(NULL); // �ʱ�ȭ
	if (!conn_ptr) {
		printf("mysql_init ����\n");
	}

	// MySQL�� ����
	conn_ptr = mysql_real_connect(conn_ptr, "localhost", "root", "111111", "parking", 3307,(char*) NULL, 0);

	if (conn_ptr) {
		printf("���� ����\n");
	}
	else {
		printf("���� ����\n");
	}

	// ���� ����
	// mysql_query() ���� �� ��ȯ���� 0�̾�� ����
	len = mysql_query(conn_ptr, query);

	res = mysql_store_result(conn_ptr); // ������ ��� ���� MYSQL_RES ������ ����

	// ���� ��� �� ���
	while ((row = mysql_fetch_row(res)) != NULL) { // �� ROW �� ��� �´�
		printf("%s %s %s %s\n", row[0], row[1], row[2]); // ��� �� ���
	}

	// �Ҵ� �� �޸� ����
	mysql_free_result(res);
	mysql_close(conn_ptr);

	return 0;
}