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

/*���� ��������� Ŭ���� �ۿ��� ������ �ʱ�ȭ �ؾ� �Ѵ�.*/
int DBClient::money = 0;

void DBClient::setClient(char *account_num, char *account_pwd) {
	sprintf(this->account_num, "%s", account_num);
	sprintf(this->account_pwd, "%s", account_pwd);
	/*this�����ʹ� ����Լ� ������ ȣ�� ��ü�� �ּҸ� �����ϴ� �����ʹ�. �����Ϸ��� ���� �����Ǿ�
	���� �������� �ʾƵ� ������ �Լ��� �Ű������� ����������� ������ �̸� �����ؾ� �� ������ ����Ѵ�.
	�� ��� DBClientŬ������ dbcon ��ü�� atmClientŬ������ clnt ��ü�� ��������� �����ϴ� �Լ��ε�,
	�����Ϸ��� ��������� ���޹޴� ��������� �̸��� �����Ƿ� ���޹޴� ���������
	dbcon ��ü�� ����������� ǥ���ϱ� ���� this �����͸� ����Ͽ���.
	*/
}
void DBClient::setClient(int new_money) {
	money = new_money;
}

void DBClient::getClient(char *client_name, char *bank, int &account_balance)const {
	sprintf(client_name, "%s", this->client_name);
	sprintf(bank, "%s", this->bank);
	account_balance= atoi(this->account_balance);
	//this ������ ���
}
void DBClient::getClient(int &account_balance)const {
	account_balance = atoi(this->account_balance);
	//this ������ ���

}
int DBClient::getClient() {
	return money;
}

void DBClient::setRecipient(char *r_num, char *r_bank) {
	sprintf(account_num, "%s", r_num);
	sprintf(bank, "%s", r_bank);
	//��������� �Ű������� �̸��� ���� �ʾ� this�����͸� ���� ������� �ʾҴ�.
}
void DBClient::getRecipient(char *r_name)const {
	sprintf(r_name, "%s", client_name);
	//��������� �Ű������� �̸��� ���� �ʾ� this�����͸� ���� ������� �ʾҴ�.
}

//����� �α���
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
//���
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
//�Ա�
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
//������
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
//������ �α���
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
//ȸ����� ���
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
		printf("***\t%s, %s ���¹�ȣ[%s]\n\n", sql_row[0], sql_row[1], sql_row[2]);
		i++;
	}

	return 0;
}
//���� �� ����� Ȯ��
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


