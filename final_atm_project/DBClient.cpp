#include <iostream>
#include <my_global.h>
#include <mysql.h>
#include "DBClient.h"

using namespace std;
#pragma comment(lib,"libmySQL.lib")
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "c++db"
#define CHOP(x) x[strlen(x) - 1] = ' '

/*정적 멤버변수는 클래스 밖에서 별도로 초기화 해야 한다.*/
int DBClient::money = 0;

void DBClient::setClient(char *account_num, char *account_pwd) {
	sprintf(this->account_num, "%s", account_num);
	sprintf(this->account_pwd, "%s", account_pwd);
	/*this포인터는 멤버함수 내에서 호출 객체의 주소를 저장하는 포인터다. 컴파일러에 의해 제공되어
	궂이 선언하지 않아도 되지만 함수의 매개변수와 멤버변수명이 동일해 이를 구분해야 할 때에는 사용한다.
	이 경우 DBClient클래스의 dbcon 객체에 atmClient클래스의 clnt 객체의 멤버변수를 전달하는 함수인데,
	전달하려는 멤버변수와 전달받는 멤버변수의 이름이 같으므로 전달받는 멤버변수가
	dbcon 객체의 멤버변수임을 표시하기 위해 this 포인터를 사용하였다.
	*/
}
void DBClient::setClient(int new_money) {
	money = new_money;
}

void DBClient::getClient(char *client_name, char *bank, int &account_balance)const {
	sprintf(client_name, "%s", this->client_name);
	sprintf(bank, "%s", this->bank);
	account_balance= atoi(this->account_balance);
	//this 포인터 사용
}
void DBClient::getClient(int &account_balance)const {
	account_balance = atoi(this->account_balance);
	//this 포인터 사용

}
int DBClient::getClient() {
	return money;
}

void DBClient::setRecipient(char *r_num, char *r_bank) {
	sprintf(account_num, "%s", r_num);
	sprintf(bank, "%s", r_bank);
	//멤버변수와 매개변수의 이름이 같지 않아 this포인터를 궂이 사용하지 않았다.
}
void DBClient::getRecipient(char *r_name)const {
	sprintf(r_name, "%s", client_name);
	//멤버변수와 매개변수의 이름이 같지 않아 this포인터를 궂이 사용하지 않았다.
}

//사용자 로그인
int DBClient::DB_login() {
	int query_stat;
	char query[255];
	bool check_id = false;	

	sprintf(query, "SELECT * FROM atmClient WHERE account_num = '%s' AND account_pwd = '%s'",
		account_num, account_pwd);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		if (strcmp(account_num, sql_row[1]) == 0) {
			sprintf(client_name, "%s", sql_row[0]);
			sprintf(account_num, "%s", sql_row[1]);
			sprintf(bank, "%s", sql_row[3]);
			sprintf(account_balance, "%s", sql_row[4]);
			check_id = true;
		}
		return 0;
	}
	if (check_id == false) {
		return 1;
	}
}
//출금
int DBClient::withdraw() {
	int query_stat;
	char query[255];	

	sprintf(query, "UPDATE atmClient SET account_balance = account_balance - %d WHERE account_num='%s'",
		money, account_num);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}
	else {
		return 0;
	}
}
//입금
int DBClient::deposit() {
	int query_stat;
	char query[255];

	sprintf(query, "UPDATE atmClient SET account_balance = account_balance + %d WHERE account_num='%s'",
		money, account_num);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}
	else {
		return 0;
	}
}
//수수료
int DBClient::charge(int charge) {
	int query_stat;
	char query[255];

	sprintf(query, "UPDATE atmManager SET manager_balance = manager_balance + '%d' WHERE manager_id = 'manager'",
		charge);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}
	else {
		return 0;
	}
}
//수신자 로그인
int DBClient::DB_rpt_login() {
	int query_stat;
	char query[255];
	bool check_id = false;

	sprintf(query, "SELECT * FROM atmClient WHERE account_num = '%s' AND bank = '%s'",
		account_num, bank);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		if (strcmp(account_num, sql_row[1]) == 0) {
			sprintf(client_name, "%s", sql_row[0]);
			sprintf(account_num, "%s", sql_row[1]);
			sprintf(bank, "%s", sql_row[3]);
			check_id = true;
		}
		return 0;
	}
	if (check_id == false) {
		return 1;
	}
}
//회원목록 출력
int DBClient::checkClient() {
	int query_stat;
	int i = 0;
	char query[255];

	query_stat = mysql_query(connection, "select c.bank, c.client_name, c.account_num from atmManager as m join atmClient as c where c.machine_use = m.machine_num");
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
	}

	sql_result = mysql_store_result(connection);
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		printf("***\t%s, %s 계좌번호[%s]\n\n", sql_row[0], sql_row[1], sql_row[2]);
		i++;
	}

	return 0;
}
//업무 후 결과값 확인
int DBClient::checkResult() {
	int query_stat;
	char query[255];
	bool check_id = false;

	sprintf(query, "SELECT account_balance FROM atmClient WHERE account_num = '%s' AND account_pwd = '%s'",
		account_num, account_pwd);
	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		sprintf(account_balance, "%s", sql_row[0]);
	}
	return 0;
}


