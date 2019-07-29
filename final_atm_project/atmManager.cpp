#include <iostream>
#include "DBManager.h"
#include "DBClient.h"
#include "atmManager.h"
#include "ATM.h"

#define CLEAR system("cls");

using namespace std;

//관리자 로그인
int atmManager::login() {
	cout << "\n/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t ATM MANAGER \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "\n\t관리자 아이디를 입력하세요:"; cin >> manager_id;
	cout << "\n\t비밀번호를 입력하세요:"; cin >> manager_pwd;
	//아이디와 비밀번호를 manager객체의 멤버변수에 저장
	dbM.setManager(manager_id, manager_pwd); //manager객체의 멤버변수를 dbM객체의 멤버함수에 전달.
	login_check = dbM.DB_login();

	if (login_check == 0) {
		dbM.getManager(machine_num, manager_balance);
		return 0;
	}
	else {
		CLEAR
		cout << "\n\t관리자 아이디 혹은 비밀번호가 틀렸습니다!!\n\n\n";
		Sleep(2000);
		return 1;
	}
}
//ATM 기계 출금
void atmManager::withdraw() {	
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 1.   출금   \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "\n\t안녕하십니까. " << manager_id << " 님! \n\n";
	cout <<"\n\t"<< machine_num << "번 기계 잔액 : " << manager_balance << " 원 입니다.\n";
	cout << "\n\t출금할 금액 : "; cin >> amount;
	if (atoi(manager_balance) >= amount) {
		int ch = dbM - amount;//연산자 오버로딩을 사용해 출금을 -기호로 할 수 있다.
		if (ch == 0) {
			dbM.checkResult();
			dbM.getManager(manager_balance);
			cout << "\n\t출금 후 " << machine_num << "번 기계 잔액 : " << manager_balance << " 원 입니다.\n";
			Sleep(2000);
		}
		else {
			cout << "\n\t전산 오류!!";
			Sleep(2000);
		}
		cout << "\n\n\n\n\n";
	}
	else {
		cout << "\n\t기계에 잔액이 부족합니다.";
		Sleep(2000);
	}
	return;
}
//ATM 기계 입금
void atmManager::deposit() {
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 2.   입금   \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "\n\t안녕하십니까. " << manager_id << " 님! \n\n";
	cout <<"\n\t"<< machine_num << "번 기계 잔액 : " << manager_balance << " 원 입니다.\n";
	cout << "\n\t입금할 금액 : "; cin >> amount;
	int ch = dbM + amount;//연산자 오버로딩을 사용해 입금을 +기호로 할 수 있다.
	if (ch == 0) {
		dbM.checkResult();
		dbM.getManager(manager_balance);
		cout << "\n\t입금 후 " << machine_num << "번 기계 잔액 : " << manager_balance << " 원 입니다.\n";
		Sleep(2000);
	}
	else {
		cout << "\n\t전산 오류!!";
		Sleep(2000);
	}
	cout << "\n\n\n\n\n";
	return;
}
//ATM 잔액 확인
void atmManager::checkAccount() {
	CLEAR
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 4. 조회거래 \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";

	//정보출력
	cout << "\n\t" << manager_id << " [" << machine_num << "번 기계잔액 : " << manager_balance << " 원 ]\n";
	Sleep(2000);
}
//회원 수
void atmManager::checkClient() {
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 3. 회원조회 \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "\n\t안녕하십니까. " << manager_id << " 님! \n\n";
	cout << "/////////////////////////////////////////////////////////\n";
	cout << "/\t\t\t 현재 회원정보 \t\t\t/\n";
	cout << "/////////////////////////////////////////////////////////\n";

	cout << "\n\t현재 총 회원 수 [" << dbM.checkClient() << "] 명.\n\n";
	dbManager = new DBClient; //업 캐스팅 (기반클래스형 포인터 변수로 파생클래스형 인스턴스를 가리킴)                        

	dbManager->checkClient(); //포인터변수로 Prn()함수에 접근하면...  
							  /*checkClient()함수의 기반 클래스로 가서 virtual을 붙여 가상함수로 만들었기
							  때문에 동적 바인딩이 되어 호출되는 함수는 기반클래스의 함수가 아니라
							  파생클래스 DBClient의 함수가 된다.*/

	Sleep(7000);
}
