#include<iostream>
#include"Start.h"

#define CLEAR system("cls");
using namespace std;

void Start::menuStart() {
	int menu;	//������ �޴��� ���� ����
	atmClient client;	//����� ATM ��ü ����
	while (1) {
		CLEAR
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/\t\t\t   ATM �޴�  \t\t\t/\n";
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/\t\t\t 1.   ���   \t\t\t/\n";
		cout << "/\t\t\t 2.   �Ա�   \t\t\t/\n";
		cout << "/\t\t\t 3. ������ü \t\t\t/\n";
		cout << "/\t\t\t 4. ��ȸ�ŷ� \t\t\t/\n";
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/\t\t\t 0.   ����   \t\t\t/\n";
		cout << "/\t\t\t999.�Ŵ������\t\t\t/\n";
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "\n\t���ϴ� �޴��� �Է��ϼ���:";
		cin >> menu;
		CLEAR
			switch (menu) {
				case 0: exit(0); break;
				case 1:
					if (client.login() == 0) {
						client.withdraw();	//����ڰ�ü�� ����Լ� ȣ��
					}		break;
				case 2:
					if (client.login() == 0) {
						client.deposit();	//����ڰ�ü�� �Ա��Լ� ȣ��
					}		break;
				case 3:
					if (client.login() == 0) {
						client.transfer();	//����ڰ�ü�� ��ü�Լ� ȣ��
					}		break;
				case 4:
					if (client.login() == 0) {
						client.checkAccount();//����ڰ�ü�� �ܾ�Ȯ���Լ� ȣ��
					}		break;
				case 999: {
					atmManager manager;	//������ ATM ��ü ����

					if (manager.login() == 0) {
						menuManager(manager);//�����ڿ� �޴��� �̵�
					}
					break;
				}		
				default: cout << "\n\t�߸��� �޴� �Է�!!\n\n";
			}

	}
}
void Start::menuManager(atmManager manager) {//�����ڿ� �޴�
	int menu;
	while (1) {
		CLEAR
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/\t\t\t ATM MANAGER \t\t\t/\n";
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/\t\t\t 1.   ���   \t\t\t/\n";//withdraw
		cout << "/\t\t\t 2.   �Ա�   \t\t\t/\n";//deposit
		cout << "/\t\t\t 3. ȸ����ȸ \t\t\t/\n";//print client list
		cout << "/\t\t\t 4. ����ܾ� \t\t\t/\n";//print client list
		cout << "/\t\t\t 0.   ����   \t\t\t/\n";//exit(0)
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "\n\t���ϴ� �޴��� �Է��ϼ���:";
		cin >> menu;
		cout << "\n\n\n\n";
		CLEAR
			switch (menu) {
			case 1: manager.withdraw(); break;		//������ ���
			case 2: manager.deposit();	break;		//������ �Ա�
			case 3: manager.checkClient();	break;	//ȸ����� ���
			case 4: manager.checkAccount();	break;	//����ܾ� Ȯ��
			case 0: return; break;
			default:cout << "/////////////////////////////////////////////////////////\n";
				cout << "\n\n\t\t  �߸��� �޴� �Է�!!\n\n\n\n";
				cout << "/////////////////////////////////////////////////////////\n";
			}
	}
}