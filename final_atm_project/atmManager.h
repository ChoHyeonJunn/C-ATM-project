#include "ATM.h"
#include"DBManager.h"

class atmManager : public ATM {
private:
	DBManager dbM;
	DBManager *dbManager;

	char machine_num[20];		//��� ������ȣ
	char manager_id[20];		//�Ŵ��� ���̵�
	char manager_pwd[20];		//�Ŵ��� ��й�ȣ
	char manager_balance[100];	//�Ŵ��� �ܾ�

public:
	int login();		//�α���
	void withdraw();	//���
	void deposit();		//�Ա�
	void checkAccount();//����ܾ�Ȯ��
	/*�߻�Ŭ���� ATM �� ���������Լ����� �������̵�*/


	void checkClient(); //ȸ�����
};