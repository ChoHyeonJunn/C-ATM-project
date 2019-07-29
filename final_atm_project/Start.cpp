#include<iostream>
#include"Start.h"

#define CLEAR system("cls");
using namespace std;

void Start::menuStart() {
	int menu;	//선택한 메뉴를 담을 변수
	atmClient client;	//사용자 ATM 객체 생성
	while (1) {
		CLEAR
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/\t\t\t   ATM 메뉴  \t\t\t/\n";
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/\t\t\t 1.   출금   \t\t\t/\n";
		cout << "/\t\t\t 2.   입금   \t\t\t/\n";
		cout << "/\t\t\t 3. 계좌이체 \t\t\t/\n";
		cout << "/\t\t\t 4. 조회거래 \t\t\t/\n";
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/\t\t\t 0.   종료   \t\t\t/\n";
		cout << "/\t\t\t999.매니저모드\t\t\t/\n";
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "\n\t원하는 메뉴를 입력하세요:";
		cin >> menu;
		CLEAR
			switch (menu) {
				case 0: exit(0); break;
				case 1:
					if (client.login() == 0) {
						client.withdraw();	//사용자객체의 출금함수 호출
					}		break;
				case 2:
					if (client.login() == 0) {
						client.deposit();	//사용자객체의 입금함수 호출
					}		break;
				case 3:
					if (client.login() == 0) {
						client.transfer();	//사용자객체의 이체함수 호출
					}		break;
				case 4:
					if (client.login() == 0) {
						client.checkAccount();//사용자객체의 잔액확인함수 호출
					}		break;
				case 999: {
					atmManager manager;	//관리자 ATM 객체 생성

					if (manager.login() == 0) {
						menuManager(manager);//관리자용 메뉴로 이동
					}
					break;
				}		
				default: cout << "\n\t잘못된 메뉴 입력!!\n\n";
			}

	}
}
void Start::menuManager(atmManager manager) {//관리자용 메뉴
	int menu;
	while (1) {
		CLEAR
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/\t\t\t ATM MANAGER \t\t\t/\n";
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/\t\t\t 1.   출금   \t\t\t/\n";//withdraw
		cout << "/\t\t\t 2.   입금   \t\t\t/\n";//deposit
		cout << "/\t\t\t 3. 회원조회 \t\t\t/\n";//print client list
		cout << "/\t\t\t 4. 기계잔액 \t\t\t/\n";//print client list
		cout << "/\t\t\t 0.   종료   \t\t\t/\n";//exit(0)
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "\n\t원하는 메뉴를 입력하세요:";
		cin >> menu;
		cout << "\n\n\n\n";
		CLEAR
			switch (menu) {
			case 1: manager.withdraw(); break;		//관리자 출금
			case 2: manager.deposit();	break;		//관리자 입금
			case 3: manager.checkClient();	break;	//회원목록 출력
			case 4: manager.checkAccount();	break;	//기계잔액 확인
			case 0: return; break;
			default:cout << "/////////////////////////////////////////////////////////\n";
				cout << "\n\n\t\t  잘못된 메뉴 입력!!\n\n\n\n";
				cout << "/////////////////////////////////////////////////////////\n";
			}
	}
}