#include "ATM.h"
#include "DBClient.h"

class atmClient : public ATM {
private:
	char client_name[20];//������̸�
	char account_num[20];//���¹�ȣ
	char account_pwd[10];//��й�ȣ
	char bank[20];		 //�����
	int account_balance; //�ܾ�
	
	const int fee = 700; //Ÿ�� ��ü�� ������
	char recipient_name[20];//������ü�� ������ �̸�
	DBClient dbcon;
	DBManager dbM;

public:
	int login();		//�α���
	void withdraw();	//���
	void deposit();		//�Ա�
	void checkAccount();//�ܾ�Ȯ��
	/*�߻�Ŭ���� ATM �� ���������Լ����� �������̵�*/

	void transfer();	//������ü
};