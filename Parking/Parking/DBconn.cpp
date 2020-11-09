#include <iostream>
#include <string>
#include <mysql.h>

#pragma comment(lib, "libmySQL.lib")
using namespace std;

int main() {
    MYSQL mysql;
    mysql_init(&mysql);
    mysql_real_connect(&mysql, "localhost", "root", "111111", "parking", 3307, NULL, 0);
    mysql_close(&mysql);

    return 0;
}