#include <iostream>
#include <string>
#include <Windows.h>
#include "DBClient.h"
#include "atmClient.h"
#include "ATM.h"

#define CLEAR system("cls");
using namespace std;


//사용자 로그인
int atmClient::login() {
	cout << "\n\t카드번호를 입력하세요:";
	cin >> account_num;
	cout << "\n\t비밀번호를 입력하세요:";
	cin >> account_pwd;
	dbcon.setClient(account_num, account_pwd);	
	//사용자 입력값으로 DB클래스의 멤버변수를 set한다.
	
	login_check = dbcon.DB_login();
	//set된 DB클래스의 멤버변수값 (카드번호, 비밀번호)를 통해 로그인 시도(mysql쿼리 송신)
	if (login_check == 0) {
		dbcon.getClient(client_name, bank, account_balance);
	//로그인이 성공하면 get함수를 이용해 db객체의 멤버변수를 atm객체의 맴버변수에 복사한다(캡슐화)
		return 0;
	}
	else {
		CLEAR
		cout << "\n\t입력하신 정보와 일치하는 계좌가 없습니다!!";
		Sleep(2000);
		return 1;
	}
}
//사용자 출금
void atmClient::withdraw() {
	CLEAR
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 1.   출금   \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";

	if (login_check == 0) {

		cout << "\n\t안녕하십니까. " << client_name << " 님! \n\n";
		cout << "\n\t" << client_name << " 님 잔액 : " << account_balance << " 원 입니다.\n";
		cout << "\n\t출금할 금액 : "; cin >> amount;
		dbcon.setClient(amount);
		//db객체의 멤버변수에 금액 저장.

		DBClient *dbC;
		dbC = (DBClient *)&dbM; //다운캐스팅
		/*다운 캐스팅은 파생 클래스로 선언된 포인터 변수에 기반 클래스로 선언된 객체의 주소를
		저장하는 것인데 자동 형변환이 되지 않으므로 에러가 발생한다.
		명시적으로 캐스트 연산자를 기술해 강제 형변환을 하는 경우 다운 캐스팅이 가능하다.
		*/
		if (account_balance >= dbcon.getClient()) {
		//잔액>=금액	getMoney 함수는 사용자 입력 금액을 int형으로 반환한다.
			int ch = (dbC->operator-(amount));
		//연산자오버로딩된 dbManager클래스의 출금함수를 통해 기계에서 돈을 빼낸다.
			if (ch == 0) {
				int re = dbcon.withdraw();
				//기계출금이 성공하면 client에서도 출금을 진행한다.
				if (re == 0) {
					CLEAR
					dbcon.checkResult();
					//checkResult함수를 통해 갱신된 사용자 잔액을 db객체의 멤버변수에 저장
					dbcon.getClient(account_balance);
					//get함수를 이용해 db객체에 저장된 잔액 멤버변수를 atm객체로 가져온다.
					cout << "\n\t출금 완료!!\n\t출금 후 " << client_name << " 님 잔액 : " << account_balance << " 원 입니다.\n";
					Sleep(2000);
				}
				else {
					cout << "\n\t출금 실패!! 다시 시도해 주세요.";
					Sleep(2000);
				}
			}
			else {
				cout << "\n\t기계에 잔액이 부족합니다.";
				cout << "\n\tATM 관리자에게 문의해 주세요.";
				Sleep(3000);
			}
		}
		else {
			cout << "\n\t잔액이 부족합니다.";
			Sleep(2000);
		}

	}
	else {
		cout << "\n\t카드번호 혹은 비밀번호가 틀렸습니다.";
		Sleep(2000);		
	}
	cout << "\n\n\n";
}
//사용자 입금
void atmClient::deposit() {
	CLEAR
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 2.   입금   \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	
	if (login_check == 0) {
		dbcon.getClient(client_name, bank, account_balance);

		cout << "\n\t안녕하십니까. " << client_name << " 님! \n\n";
		cout << "\n\t" << client_name << " 님 잔액 : " << account_balance << " 원 입니다.\n";
		cout << "\n\t입금할 금액 : "; cin >> amount;
		dbcon.setClient(amount);
	
		DBClient *dbC;
		dbC = (DBClient *)&dbM; //다운캐스팅
		/*다운 캐스팅은 파생 클래스로 선언된 포인터 변수에 기반 클래스로 선언된 객체의 주소를
		저장하는 것인데 자동 형변환이 되지 않으므로 에러가 발생한다.
		명시적으로 캐스트 연산자를 기술해 강제 형변환을 하는 경우 다운 캐스팅이 가능하다.
		*/
		int ch = (dbC->operator+(amount));
		if (ch == 0) {
			int re = dbcon.deposit();
			if (re == 0) {
				CLEAR
					dbcon.checkResult();
				dbcon.getClient(account_balance);
				cout << "\n\t입금 완료!!\n\t입금 후 " << client_name << " 님 잔액 : " << account_balance << " 원 입니다.\n";
				Sleep(2000);
			}
			else {
				cout << "\n\t입금 실패!! 다시 시도해 주세요.";
				Sleep(2000);
			}
		}
		else {
			cout << "\n\t입금 실패!! 다시 시도해 주세요.";
			Sleep(2000);
		}
	}
	else {
		cout << "\n\t계좌번호 혹은 비밀번호가 틀렸습니다.";
		Sleep(2000);
	}
}
//사용자 계좌이체
void atmClient::transfer() {
	CLEAR
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 3. 계좌이체 \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	DBClient dbcon_receive;
	char r_num[20], r_bank[20];
	char choice;


	if (login_check == 0) {
		dbcon.getClient(client_name, bank, account_balance);

		cout << "\n\t안녕하십니까. " << client_name << " 님!";
		cout <<"\n\t"<< client_name << " 님 잔액 : " << account_balance << " 원 입니다.\n\n";
		cout << "/////////////////////////////////////////////////////////\n";
		cout << "/국민은행\t신한은행\t기업은행\t우리은행/\n";
		cout << "/////////////////////////////////////////////////////////\n";

		cout << "\n\t보낼사람 은행 : ";		cin >> r_bank;
		cout << "\n\t보낼사람 계좌번호 : "; cin >> r_num;
		dbcon_receive.setRecipient(r_num, r_bank);
		int ch = dbcon_receive.DB_rpt_login();
		//수신자는 은행과 계좌번호를 통해 로그인을 진행한다.

		if (ch == 0) {
			dbcon_receive.getRecipient(recipient_name);
			//로그인이 성공하면 db객체의 멤버변수에 저장된 수신자 정보를 atm객체에 복사한다.
			cout << "\n\t보낼 돈 : "; cin >> amount;
			dbcon.setClient(amount);
			/*계좌이체시 금액을 정적멤버변수에 저장한다.
			정적멤버변수는 DBClient 클래스의 모든 인스턴스에 의해 공유되기 때문에
			송신자와 수신자 간에 이체금액을 같은 변수를 이용해 공유할 수 있다.*/

			if (account_balance >= dbcon.getClient() && !strcmp(bank, r_bank)) {
				//잔액>=이체금액 && 은행이 같은경우
				//strcmp함수는 기술된 두 문자열 인자가 일치할 경우 0을 반환한다.
				//이때 0은 거짓을 의미하기때문에 !를 붙여 true로 바꾸어 준다.
				CLEAR
				cout << "\n\t" << r_bank << " " << recipient_name << " 님 에게 " << dbcon.getClient() << "원 을 보냅니다.";
				cout << "\n\t정말 이체 하시겠습니까? (y/otherKey) : "; cin >> choice;
				if (choice == 'y' || choice == 'Y') {	//이체 여부를 다시 한번 확인 y(Y)입력일 경우 yes, 다른 키 입력일 경우 no				
					int r = dbcon_receive.deposit(); //수신자에게 입금(금액은 정적멤버변수 money사용)
					int w = dbcon.withdraw(); //이체하는사람에게서 출금(금액은 정적멤버변수 money사용)
					if (r == 0 && w == 0) {
						dbcon.checkResult();
						dbcon.getClient(account_balance);
						CLEAR
						cout << "\n\t계좌이체가 성공적으로 이루어졌습니다.";
						cout << "\n\t이체 후 " << client_name << "님 계좌번호 [" << account_num << "] 잔액 : " << account_balance << " 원 입니다.\n";
						Sleep(2000);
					}
					else {
						cout << "\n\t전산 오류!! 다시 시도해 주십시오!!";
						Sleep(2000);
					}
				}
				else {
					cout << "\n\t이체를 취소하셨습니다.";
					Sleep(2000);
				}
			}
			else if (account_balance >= (dbcon.getClient() + fee) && strcmp(bank, r_bank)) {
				//잔액>=이체금액 && 은행이 다른경우
				CLEAR
				cout << "\n\t" << r_bank << " " << recipient_name << " 님 에게 " << dbcon.getClient() << "원 을 보냅니다.\n";
				cout << "\n\t타행 이체는 수수료 700원이 추가됩니다.";
				cout << "\n\t정말 이체 하시겠습니까? (y/otherKey) : "; cin >> choice;

				if (choice == 'y' || choice == 'Y') {	//이체 여부를 다시 한번 확인 y(Y)입력일 경우 yes, 다른 키 입력일 경우 no				
					int c = dbcon.charge(fee);//매니저에게 700원 입금
					int r = dbcon_receive.deposit(); //수신자에게 입금(금액은 정적멤버변수 money사용)
					dbcon.setClient((dbcon.getClient() + fee));//정적멤버변수 money 갱신
					int w = dbcon.withdraw(); //이체하는사람에게서 출금(금액은 갱신된 정적멤버변수 money사용)
					if (c == 0 && r == 0 && w == 0) {
						dbcon.checkResult();
						dbcon.getClient(account_balance);
						CLEAR
						cout << "\n\t계좌이체가 성공적으로 이루어졌습니다.";
						cout << "\n\t이체 후 " << client_name << "님 계좌번호 [" << account_num << "] 잔액 : " << account_balance << " 원 입니다.\n";
						Sleep(2000);
					}
					else {
						CLEAR
						cout << "\n\t전산 오류!! 다시 시도해 주십시오!!";
						Sleep(2000);
					}
				}
				else {
					CLEAR
					cout << "\n\t이체를 취소하셨습니다.";
					Sleep(2000);
				}
			}
			else if (strcmp(bank, r_bank)) {
				CLEAR
				cout << "\n\t타행 이체시 수수료를 포함한 잔액이 부족합니다.";
				Sleep(2000);
			}
			else {
				CLEAR
				cout << "\n\t잔액이 부족합니다.";
				Sleep(2000);
			}
		}
		else {
			CLEAR
			cout << "\n\t존재하지 않는 계좌입니다.";
			Sleep(2000);
		}
	}
}

//회원잔액
void atmClient::checkAccount() {
	CLEAR
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 4. 조회거래 \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	
	//정보출력
	cout <<"\n\t"<< bank << " " << client_name << "님 계좌번호 : " << account_num<<"\n";
	cout<< "\n\t잔액 : " << account_balance << " 원 입니다.";

	Sleep(2000);
}

