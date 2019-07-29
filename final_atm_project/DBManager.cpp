#include <iostream>
#include <my_global.h>
#include <mysql.h>
#include "DBManager.h"

using namespace std;
#pragma comment(lib,"libmySQL.lib")
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "c++db"
#define CHOP(x) x[strlen(x) - 1] = ' '


DBManager::DBManager() {
	//기반클래스 DBManager의 생성자 : db연결을 초기화하고 connection하는 기능이다.
	//파생클래스에서 객체 생성시 기반클래스의 생성자까지 호출되기 때문에 파생클래스에서 dbconnection부분을
	//기술하지 않아도 mysql에 쿼리를 전송할 수 있다.
	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&conn, MYSQL_INIT_COMMAND, "SET NAMES euckr");
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	if (connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
	}
}
DBManager::~DBManager() {
	//기반클래스에서 DBManager의 소멸자 : free_result를 통해 쿼리값을 해제하고 mysql_close()
	//파행클래스의 객체 소멸시 기반클래스의 소멸자까지 호출되기때문에 파생클래스에서 아래와 같은
	//기능을 따로 기술할 필요가 없다.
	try {
		mysql_free_result(sql_result);
		mysql_close(connection);
	}
	catch (exception e) {
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
	}//디버깅시 예외상황이 발생해 try~catch 를 사용해 예외처리를 하였다.
}

void DBManager::setManager(char *manager_id, char *manager_pwd) {
	sprintf(this->manager_id, "%s", manager_id);
	sprintf(this->manager_pwd, "%s", manager_pwd);
	/*this포인터는 멤버함수 내에서 호출 객체의 주소를 저장하는 포인터다. 컴파일러에 의해 제공되어
	궂이 선언하지 않아도 되지만 함수의 매개변수와 멤버변수명이 동일해 이를 구분해야 할 때에는 사용한다.
	이 경우 DBManager클래스의 dbM 객체에 atmManager클래스의 manager 객체의 멤버변수를 전달하는 함수인데,
	전달하려는 멤버변수와 전달받는 멤버변수의 이름이 같으므로 전달받는 멤버변수가
	dbM 객체의 멤버변수임을 표시하기 위해 this 포인터를 사용하였다.
	*/
}
void DBManager::getManager(char *machine_num, char *manager_balance)const {
	sprintf(machine_num, "%s", this->machine_num);
	sprintf(manager_balance, "%s", this->manager_balance);
	/*this 포인터 사용
	DBManager객체의 멤버변수를 atmManager객체에 전달하기 위한 함수인데, 전달하려는 멤버변수와 전달받는 멤버변수의 
	이름이 같으므로 전달받는 멤버변수가 dbM 객체의 멤버변수임을 표시하기 위해 this 포인터를 사용하였다.
	*/
}
void DBManager::getManager(char *manager_balance)const {
	sprintf(manager_balance, "%s", this->manager_balance);
	//this 포인터 사용(getManager 내용과 동일...)

}
//관리자 로그인
int DBManager::DB_login() {
	int query_stat;
	char query[255];
	bool check_id = false;

	sprintf(query, "SELECT * FROM atmManager WHERE manager_id = '%s' AND manager_pwd = '%s'",
		manager_id, manager_pwd);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
	}

	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		if (strcmp(manager_id, sql_row[1]) == 0) {
			sprintf(machine_num, "%s", sql_row[0]);
			sprintf(manager_balance, "%s", sql_row[3]);
			check_id = true;
		}
		return 0;
	}
	if (check_id == false) {
		return 1;
	}
}
//업무 후 결과값 확인
int DBManager::checkResult() {
	int query_stat;
	char query[255];
	bool check_id = false;

	sprintf(query, "SELECT manager_balance FROM atmManager WHERE manager_id = '%s' AND manager_pwd = '%s'",
		manager_id, manager_pwd);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
	}

	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
			sprintf(manager_balance, "%s", sql_row[0]);
	}
	return 0;
}
//출금
int DBManager::operator-(int amount) {
	int query_stat;
	char query[255];

	sprintf(query, "UPDATE atmManager SET manager_balance = manager_balance - %d WHERE machine_num='%s'",
		amount, machine_num);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0){
		return 1;
	}
	else {
		return 0;
	}
}
//입금
int DBManager::operator+(int amount) {
	int query_stat;
	char query[255];

	sprintf(query, "UPDATE atmManager SET manager_balance = manager_balance + %d WHERE machine_num='%s'",
		amount, machine_num);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0){
		return 1;
	}
	else {
		return 0;
	}
}

int DBManager::checkClient() {
	int query_stat;
	int i = 0;
	int num;
	char query[255];

	query_stat = mysql_query(connection, "SELECT count(*) from atmClient");
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
	}
	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		num = atoi(sql_row[0]);
	}
	
	return num;
}
