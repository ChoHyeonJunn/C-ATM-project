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
	//���Ŭ���� DBManager�� ������ : db������ �ʱ�ȭ�ϰ� connection�ϴ� ����̴�.
	//�Ļ�Ŭ�������� ��ü ������ ���Ŭ������ �����ڱ��� ȣ��Ǳ� ������ �Ļ�Ŭ�������� dbconnection�κ���
	//������� �ʾƵ� mysql�� ������ ������ �� �ִ�.
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
	//���Ŭ�������� DBManager�� �Ҹ��� : free_result�� ���� �������� �����ϰ� mysql_close()
	//����Ŭ������ ��ü �Ҹ�� ���Ŭ������ �Ҹ��ڱ��� ȣ��Ǳ⶧���� �Ļ�Ŭ�������� �Ʒ��� ����
	//����� ���� ����� �ʿ䰡 ����.
	try {
		mysql_free_result(sql_result);
		mysql_close(connection);
	}
	catch (exception e) {
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
	}//������ ���ܻ�Ȳ�� �߻��� try~catch �� ����� ����ó���� �Ͽ���.
}

void DBManager::setManager(char *manager_id, char *manager_pwd) {
	sprintf(this->manager_id, "%s", manager_id);
	sprintf(this->manager_pwd, "%s", manager_pwd);
	/*this�����ʹ� ����Լ� ������ ȣ�� ��ü�� �ּҸ� �����ϴ� �����ʹ�. �����Ϸ��� ���� �����Ǿ�
	���� �������� �ʾƵ� ������ �Լ��� �Ű������� ����������� ������ �̸� �����ؾ� �� ������ ����Ѵ�.
	�� ��� DBManagerŬ������ dbM ��ü�� atmManagerŬ������ manager ��ü�� ��������� �����ϴ� �Լ��ε�,
	�����Ϸ��� ��������� ���޹޴� ��������� �̸��� �����Ƿ� ���޹޴� ���������
	dbM ��ü�� ����������� ǥ���ϱ� ���� this �����͸� ����Ͽ���.
	*/
}
void DBManager::getManager(char *machine_num, char *manager_balance)const {
	sprintf(machine_num, "%s", this->machine_num);
	sprintf(manager_balance, "%s", this->manager_balance);
	/*this ������ ���
	DBManager��ü�� ��������� atmManager��ü�� �����ϱ� ���� �Լ��ε�, �����Ϸ��� ��������� ���޹޴� ��������� 
	�̸��� �����Ƿ� ���޹޴� ��������� dbM ��ü�� ����������� ǥ���ϱ� ���� this �����͸� ����Ͽ���.
	*/
}
void DBManager::getManager(char *manager_balance)const {
	sprintf(manager_balance, "%s", this->manager_balance);
	//this ������ ���(getManager ����� ����...)

}
//������ �α���
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
//���� �� ����� Ȯ��
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
//���
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
//�Ա�
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
