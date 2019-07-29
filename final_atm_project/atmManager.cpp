#include <iostream>
#include "DBManager.h"
#include "DBClient.h"
#include "atmManager.h"
#include "ATM.h"

#define CLEAR system("cls");

using namespace std;

//������ �α���
int atmManager::login() {
	cout << "\n/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t ATM MANAGER \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "\n\t������ ���̵� �Է��ϼ���:"; cin >> manager_id;
	cout << "\n\t��й�ȣ�� �Է��ϼ���:"; cin >> manager_pwd;
	//���̵�� ��й�ȣ�� manager��ü�� ��������� ����
	dbM.setManager(manager_id, manager_pwd); //manager��ü�� ��������� dbM��ü�� ����Լ��� ����.
	login_check = dbM.DB_login();

	if (login_check == 0) {
		dbM.getManager(machine_num, manager_balance);
		return 0;
	}
	else {
		CLEAR
		cout << "\n\t������ ���̵� Ȥ�� ��й�ȣ�� Ʋ�Ƚ��ϴ�!!\n\n\n";
		Sleep(2000);
		return 1;
	}
}
//ATM ��� ���
void atmManager::withdraw() {	
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 1.   ���   \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "\n\t�ȳ��Ͻʴϱ�. " << manager_id << " ��! \n\n";
	cout <<"\n\t"<< machine_num << "�� ��� �ܾ� : " << manager_balance << " �� �Դϴ�.\n";
	cout << "\n\t����� �ݾ� : "; cin >> amount;
	if (atoi(manager_balance) >= amount) {
		int ch = dbM - amount;//������ �����ε��� ����� ����� -��ȣ�� �� �� �ִ�.
		if (ch == 0) {
			dbM.checkResult();
			dbM.getManager(manager_balance);
			cout << "\n\t��� �� " << machine_num << "�� ��� �ܾ� : " << manager_balance << " �� �Դϴ�.\n";
			Sleep(2000);
		}
		else {
			cout << "\n\t���� ����!!";
			Sleep(2000);
		}
		cout << "\n\n\n\n\n";
	}
	else {
		cout << "\n\t��迡 �ܾ��� �����մϴ�.";
		Sleep(2000);
	}
	return;
}
//ATM ��� �Ա�
void atmManager::deposit() {
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 2.   �Ա�   \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "\n\t�ȳ��Ͻʴϱ�. " << manager_id << " ��! \n\n";
	cout <<"\n\t"<< machine_num << "�� ��� �ܾ� : " << manager_balance << " �� �Դϴ�.\n";
	cout << "\n\t�Ա��� �ݾ� : "; cin >> amount;
	int ch = dbM + amount;//������ �����ε��� ����� �Ա��� +��ȣ�� �� �� �ִ�.
	if (ch == 0) {
		dbM.checkResult();
		dbM.getManager(manager_balance);
		cout << "\n\t�Ա� �� " << machine_num << "�� ��� �ܾ� : " << manager_balance << " �� �Դϴ�.\n";
		Sleep(2000);
	}
	else {
		cout << "\n\t���� ����!!";
		Sleep(2000);
	}
	cout << "\n\n\n\n\n";
	return;
}
//ATM �ܾ� Ȯ��
void atmManager::checkAccount() {
	CLEAR
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 4. ��ȸ�ŷ� \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";

	//�������
	cout << "\n\t" << manager_id << " [" << machine_num << "�� ����ܾ� : " << manager_balance << " �� ]\n";
	Sleep(2000);
}
//ȸ�� ��
void atmManager::checkClient() {
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 3. ȸ����ȸ \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "\n\t�ȳ��Ͻʴϱ�. " << manager_id << " ��! \n\n";
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t ���� ȸ������ \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";

	cout << "\n\t���� �� ȸ�� �� [" << dbM.checkClient() << "] ��.\n\n";
	dbManager = new DBClient; //�� ĳ���� (���Ŭ������ ������ ������ �Ļ�Ŭ������ �ν��Ͻ��� ����Ŵ)                        

	dbManager->checkClient(); //�����ͺ����� Prn()�Լ��� �����ϸ�...  
							  /*checkClient()�Լ��� ��� Ŭ������ ���� virtual�� �ٿ� �����Լ��� �������
							  ������ ���� ���ε��� �Ǿ� ȣ��Ǵ� �Լ��� ���Ŭ������ �Լ��� �ƴ϶�
							  �Ļ�Ŭ���� DBClient�� �Լ��� �ȴ�.*/

	Sleep(7000);
}
