#include <iostream>
#include <string>
#include <Windows.h>
#include "DBClient.h"
#include "atmClient.h"
#include "ATM.h"

#define CLEAR system("cls");
using namespace std;


//����� �α���
int atmClient::login() {
	cout << "\n\tī���ȣ�� �Է��ϼ���:";
	cin >> account_num;
	cout << "\n\t��й�ȣ�� �Է��ϼ���:";
	cin >> account_pwd;
	dbcon.setClient(account_num, account_pwd);	
	//����� �Է°����� DBŬ������ ��������� set�Ѵ�.
	
	login_check = dbcon.DB_login();
	//set�� DBŬ������ ��������� (ī���ȣ, ��й�ȣ)�� ���� �α��� �õ�(mysql���� �۽�)
	if (login_check == 0) {
		dbcon.getClient(client_name, bank, account_balance);
	//�α����� �����ϸ� get�Լ��� �̿��� db��ü�� ��������� atm��ü�� �ɹ������� �����Ѵ�(ĸ��ȭ)
		return 0;
	}
	else {
		CLEAR
		cout << "\n\t�Է��Ͻ� ������ ��ġ�ϴ� ���°� �����ϴ�!!";
		Sleep(2000);
		return 1;
	}
}
//����� ���
void atmClient::withdraw() {
	CLEAR
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 1.   ���   \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";

	if (login_check == 0) {

		cout << "\n\t�ȳ��Ͻʴϱ�. " << client_name << " ��! \n\n";
		cout << "\n\t" << client_name << " �� �ܾ� : " << account_balance << " �� �Դϴ�.\n";
		cout << "\n\t����� �ݾ� : "; cin >> amount;
		dbcon.setClient(amount);
		//db��ü�� ��������� �ݾ� ����.

		DBClient *dbC;
		dbC = (DBClient *)&dbM; //�ٿ�ĳ����
		/*�ٿ� ĳ������ �Ļ� Ŭ������ ����� ������ ������ ��� Ŭ������ ����� ��ü�� �ּҸ�
		�����ϴ� ���ε� �ڵ� ����ȯ�� ���� �����Ƿ� ������ �߻��Ѵ�.
		��������� ĳ��Ʈ �����ڸ� ����� ���� ����ȯ�� �ϴ� ��� �ٿ� ĳ������ �����ϴ�.
		*/
		if (account_balance >= dbcon.getClient()) {
		//�ܾ�>=�ݾ�	getMoney �Լ��� ����� �Է� �ݾ��� int������ ��ȯ�Ѵ�.
			int ch = (dbC->operator-(amount));
		//�����ڿ����ε��� dbManagerŬ������ ����Լ��� ���� ��迡�� ���� ������.
			if (ch == 0) {
				int re = dbcon.withdraw();
				//�������� �����ϸ� client������ ����� �����Ѵ�.
				if (re == 0) {
					CLEAR
					dbcon.checkResult();
					//checkResult�Լ��� ���� ���ŵ� ����� �ܾ��� db��ü�� ��������� ����
					dbcon.getClient(account_balance);
					//get�Լ��� �̿��� db��ü�� ����� �ܾ� ��������� atm��ü�� �����´�.
					cout << "\n\t��� �Ϸ�!!\n\t��� �� " << client_name << " �� �ܾ� : " << account_balance << " �� �Դϴ�.\n";
					Sleep(2000);
				}
				else {
					cout << "\n\t��� ����!! �ٽ� �õ��� �ּ���.";
					Sleep(2000);
				}
			}
			else {
				cout << "\n\t��迡 �ܾ��� �����մϴ�.";
				cout << "\n\tATM �����ڿ��� ������ �ּ���.";
				Sleep(3000);
			}
		}
		else {
			cout << "\n\t�ܾ��� �����մϴ�.";
			Sleep(2000);
		}

	}
	else {
		cout << "\n\tī���ȣ Ȥ�� ��й�ȣ�� Ʋ�Ƚ��ϴ�.";
		Sleep(2000);		
	}
	cout << "\n\n\n";
}
//����� �Ա�
void atmClient::deposit() {
	CLEAR
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 2.   �Ա�   \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	
	if (login_check == 0) {
		dbcon.getClient(client_name, bank, account_balance);

		cout << "\n\t�ȳ��Ͻʴϱ�. " << client_name << " ��! \n\n";
		cout << "\n\t" << client_name << " �� �ܾ� : " << account_balance << " �� �Դϴ�.\n";
		cout << "\n\t�Ա��� �ݾ� : "; cin >> amount;
		dbcon.setClient(amount);
	
		DBClient *dbC;
		dbC = (DBClient *)&dbM; //�ٿ�ĳ����
		/*�ٿ� ĳ������ �Ļ� Ŭ������ ����� ������ ������ ��� Ŭ������ ����� ��ü�� �ּҸ�
		�����ϴ� ���ε� �ڵ� ����ȯ�� ���� �����Ƿ� ������ �߻��Ѵ�.
		��������� ĳ��Ʈ �����ڸ� ����� ���� ����ȯ�� �ϴ� ��� �ٿ� ĳ������ �����ϴ�.
		*/
		int ch = (dbC->operator+(amount));
		if (ch == 0) {
			int re = dbcon.deposit();
			if (re == 0) {
				CLEAR
					dbcon.checkResult();
				dbcon.getClient(account_balance);
				cout << "\n\t�Ա� �Ϸ�!!\n\t�Ա� �� " << client_name << " �� �ܾ� : " << account_balance << " �� �Դϴ�.\n";
				Sleep(2000);
			}
			else {
				cout << "\n\t�Ա� ����!! �ٽ� �õ��� �ּ���.";
				Sleep(2000);
			}
		}
		else {
			cout << "\n\t�Ա� ����!! �ٽ� �õ��� �ּ���.";
			Sleep(2000);
		}
	}
	else {
		cout << "\n\t���¹�ȣ Ȥ�� ��й�ȣ�� Ʋ�Ƚ��ϴ�.";
		Sleep(2000);
	}
}
//����� ������ü
void atmClient::transfer() {
	CLEAR
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 3. ������ü \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	DBClient dbcon_receive;
	char r_num[20], r_bank[20];
	char choice;


	if (login_check == 0) {
		dbcon.getClient(client_name, bank, account_balance);

		cout << "\n\t�ȳ��Ͻʴϱ�. " << client_name << " ��!";
		cout <<"\n\t"<< client_name << " �� �ܾ� : " << account_balance << " �� �Դϴ�.\n\n";
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/��������\t��������\t�������\t�츮����/\n";
		cout << "/////////////////////////////////////////////////////////\n";

		cout << "\n\t������� ���� : ";		cin >> r_bank;
		cout << "\n\t������� ���¹�ȣ : "; cin >> r_num;
		dbcon_receive.setRecipient(r_num, r_bank);
		int ch = dbcon_receive.DB_rpt_login();
		//�����ڴ� ����� ���¹�ȣ�� ���� �α����� �����Ѵ�.

		if (ch == 0) {
			dbcon_receive.getRecipient(recipient_name);
			//�α����� �����ϸ� db��ü�� ��������� ����� ������ ������ atm��ü�� �����Ѵ�.
			cout << "\n\t���� �� : "; cin >> amount;
			dbcon.setClient(amount);
			/*������ü�� �ݾ��� ������������� �����Ѵ�.
			������������� DBClient Ŭ������ ��� �ν��Ͻ��� ���� �����Ǳ� ������
			�۽��ڿ� ������ ���� ��ü�ݾ��� ���� ������ �̿��� ������ �� �ִ�.*/

			if (account_balance >= dbcon.getClient() && !strcmp(bank, r_bank)) {
				//�ܾ�>=��ü�ݾ� && ������ �������
				//strcmp�Լ��� ����� �� ���ڿ� ���ڰ� ��ġ�� ��� 0�� ��ȯ�Ѵ�.
				//�̶� 0�� ������ �ǹ��ϱ⶧���� !�� �ٿ� true�� �ٲپ� �ش�.
				CLEAR
				cout << "\n\t" << r_bank << " " << recipient_name << " �� ���� " << dbcon.getClient() << "�� �� �����ϴ�.";
				cout << "\n\t���� ��ü �Ͻðڽ��ϱ�? (y/otherKey) : "; cin >> choice;
				if (choice == 'y' || choice == 'Y') {	//��ü ���θ� �ٽ� �ѹ� Ȯ�� y(Y)�Է��� ��� yes, �ٸ� Ű �Է��� ��� no				
					int r = dbcon_receive.deposit(); //�����ڿ��� �Ա�(�ݾ��� ����������� money���)
					int w = dbcon.withdraw(); //��ü�ϴ»�����Լ� ���(�ݾ��� ����������� money���)
					if (r == 0 && w == 0) {
						dbcon.checkResult();
						dbcon.getClient(account_balance);
						CLEAR
						cout << "\n\t������ü�� ���������� �̷�������ϴ�.";
						cout << "\n\t��ü �� " << client_name << "�� ���¹�ȣ [" << account_num << "] �ܾ� : " << account_balance << " �� �Դϴ�.\n";
						Sleep(2000);
					}
					else {
						cout << "\n\t���� ����!! �ٽ� �õ��� �ֽʽÿ�!!";
						Sleep(2000);
					}
				}
				else {
					cout << "\n\t��ü�� ����ϼ̽��ϴ�.";
					Sleep(2000);
				}
			}
			else if (account_balance >= (dbcon.getClient() + fee) && strcmp(bank, r_bank)) {
				//�ܾ�>=��ü�ݾ� && ������ �ٸ����
				CLEAR
				cout << "\n\t" << r_bank << " " << recipient_name << " �� ���� " << dbcon.getClient() << "�� �� �����ϴ�.\n";
				cout << "\n\tŸ�� ��ü�� ������ 700���� �߰��˴ϴ�.";
				cout << "\n\t���� ��ü �Ͻðڽ��ϱ�? (y/otherKey) : "; cin >> choice;

				if (choice == 'y' || choice == 'Y') {	//��ü ���θ� �ٽ� �ѹ� Ȯ�� y(Y)�Է��� ��� yes, �ٸ� Ű �Է��� ��� no				
					int c = dbcon.charge(fee);//�Ŵ������� 700�� �Ա�
					int r = dbcon_receive.deposit(); //�����ڿ��� �Ա�(�ݾ��� ����������� money���)
					dbcon.setClient((dbcon.getClient() + fee));//����������� money ����
					int w = dbcon.withdraw(); //��ü�ϴ»�����Լ� ���(�ݾ��� ���ŵ� ����������� money���)
					if (c == 0 && r == 0 && w == 0) {
						dbcon.checkResult();
						dbcon.getClient(account_balance);
						CLEAR
						cout << "\n\t������ü�� ���������� �̷�������ϴ�.";
						cout << "\n\t��ü �� " << client_name << "�� ���¹�ȣ [" << account_num << "] �ܾ� : " << account_balance << " �� �Դϴ�.\n";
						Sleep(2000);
					}
					else {
						CLEAR
						cout << "\n\t���� ����!! �ٽ� �õ��� �ֽʽÿ�!!";
						Sleep(2000);
					}
				}
				else {
					CLEAR
					cout << "\n\t��ü�� ����ϼ̽��ϴ�.";
					Sleep(2000);
				}
			}
			else if (strcmp(bank, r_bank)) {
				CLEAR
				cout << "\n\tŸ�� ��ü�� �����Ḧ ������ �ܾ��� �����մϴ�.";
				Sleep(2000);
			}
			else {
				CLEAR
				cout << "\n\t�ܾ��� �����մϴ�.";
				Sleep(2000);
			}
		}
		else {
			CLEAR
			cout << "\n\t�������� �ʴ� �����Դϴ�.";
			Sleep(2000);
		}
	}
}

//ȸ���ܾ�
void atmClient::checkAccount() {
	CLEAR
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 4. ��ȸ�ŷ� \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	
	//�������
	cout <<"\n\t"<< bank << " " << client_name << "�� ���¹�ȣ : " << account_num<<"\n";
	cout<< "\n\t�ܾ� : " << account_balance << " �� �Դϴ�.";

	Sleep(2000);
}

