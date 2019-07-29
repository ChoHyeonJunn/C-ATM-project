#ifndef  CALC_DATA_H
#define  CALC_DATA_H

#include <mysql.h>
#include "DBManager.h"

class DBClient : public DBManager {
private:
	static int money;
	/*���� �������
	�Ϲ� ��������� Ŭ������ �ν��Ͻ��� ������ ������ �޸� ������ ���������� �Ҵ������
	���� ��������� �ν��Ͻ��� ������� ���α׷��� ���۰� ���ÿ� �����ȴ�.*/
	/*
	Ư¡
	���� ��������� Ŭ������ ��� �ν��Ͻ��� ���� ������
	���� ��������� �ڷᰡ ����Ǿ� ���� �����Ǵ� ������ ���������� ���������� �ش� Ŭ����������
	�����ؾ� �Ѵٴ� ������ ���������� ���̰� �ִ�.

	�� ��� ������ü �� �ݾ��� ��,������ ��ü�� ���� �����Ǿ�� �ϹǷ� static�� ����Ͽ���.
	���� ĸ��ȭ�� ���� ���������ڸ� private ���� �����Ͽ���, �ݾ��� atmŬ�����κ��� �Է¹ް�
	�����ϱ� ���� ����������� get, set �� �����Ͽ���.*/

	char client_name[20];//������̸�
	char account_num[20];//���¹�ȣ
	char account_pwd[10];//��й�ȣ
	char bank[20];		 //�����
	char account_balance[100];//�ܾ�
	/*privateŬ���� ���ο����� ���ٰ��� / Ŭ���� �ܺο����� ���� �Ұ�(ĸ��ȭ)
	ATM���� ������� ������ ����Ǹ� �ȵǴ� �߿��� �����̱� ������ Ŭ���� �ܺο���
	�������� ���ϵ��� ���������ڸ� private�� �����Ͽ� ĸ��ȭ�� �����Ͽ���.
	*/

	
	
public:
	void setClient(char *account_num, char *account_pwd); //������Է°��� ��������� ����(���¹�ȣ, ��й�ȣ)
	void setRecipient(char *r_num, char *r_bank);//������Է°�(����������)�� ��������� ����(�̸�, �����)	

	void getClient(char *client_name, char *bank, int &account_balance)const;//db�� ����� ������ �ٸ� Ŭ������ ����
	void getClient(int &account_balance)const;//����� �� ���ŵ� ���� �ٸ� Ŭ������ ����(�����ε�)
	void getRecipient(char *r_name)const;//db�� ������ ������ �ٸ� Ŭ������ ����

	static void setClient(int new_money);//������������� �����ϱ� ���� ��������Լ�
	static int getClient();//������������� �ٸ� Ŭ������ �����ϱ� ���� ��������Լ�
	/*getXxx �Լ��� DB���� ������ ���� private��������� ����� ���� ATM��ü���� �����ϰ� 
	�ϱ� ���� �Լ��̴�. 
	*/

	int DB_login();		//Ŭ���̾�Ʈ �α���
	int DB_rpt_login();//������ü�� ������ üũ

	int checkResult(); //������� ���ŵ� ������� �ٽ� select�Ͽ� ��������� ����.

	int withdraw();//���(�Ű����� ���� ������������� ���� ����ϱ� ������ �����ڿ����ε��� ������� �ʾҴ�.)
	int deposit();//�Ա�(")

	int charge(int charge);//Ÿ����ü�� ������ ����
	int checkClient();//���Ŭ������ �Լ� �������̵�, ȸ����� ���
};

#endif // ! CALC_DATA_H
