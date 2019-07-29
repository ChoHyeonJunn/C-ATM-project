#include <iostream>
#include <my_global.h>
#include <mysql.h>
#include "DB.h"

using namespace std;
#pragma comment(lib,"libmySQL.lib")
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "c++db"
#define CHOP(x) x[strlen(x) - 1] = ' '

DB::DB() {
	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&conn, MYSQL_INIT_COMMAND, "SET NAMES euckr");
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	if (connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
	}
}
DB::~DB() {
	try {
		mysql_free_result(sql_result);
		mysql_close(connection);
	}
	catch (exception e) {
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));

	}
}