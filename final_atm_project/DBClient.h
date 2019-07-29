#ifndef  CALC_DATA_H
#define  CALC_DATA_H

#include <mysql.h>
#include "DBManager.h"

class DBClient : public DBManager {
private:
	static int money;
	/*정적 멤버변수
	일반 멤버변수는 클래스로 인스턴스를 생설할 때마다 메모리 영역을 개별적으로 할당받지만
	정적 멤버변수는 인스턴스와 상관없이 프로그램의 시작과 동시에 생성된다.*/
	/*
	특징
	정적 멤버변수는 클래스의 모든 인스턴스에 의해 공유됨
	정적 멤버변수에 자료가 저장되어 값이 유지되는 원리는 전역변수와 동일하지만 해당 클래스명으로
	접근해야 한다는 점에서 전역변수와 차이가 있다.

	이 경우 계좌이체 시 금액은 송,수신자 객체에 의해 공유되어야 하므로 static을 사용하였다.
	또한 캡슐화를 위해 접근지정자를 private 으로 선언하였고, 금액을 atm클래스로부터 입력받고
	전달하기 위해 정적멤버변수 get, set 을 구현하였다.*/

	char client_name[20];//사용자이름
	char account_num[20];//계좌번호
	char account_pwd[10];//비밀번호
	char bank[20];		 //은행명
	char account_balance[100];//잔액
	/*private클래스 내부에서는 접근가능 / 클래스 외부에서는 접근 불가(캡슐화)
	ATM에서 사용자의 정보는 노출되면 안되는 중요한 정보이기 때문에 클래스 외부에서
	접근하지 못하도록 접근지정자를 private로 선언하여 캡슐화를 구현하였다.
	*/

	
	
public:
	void setClient(char *account_num, char *account_pwd); //사용자입력값을 멤버변수에 저장(계좌번호, 비밀번호)
	void setRecipient(char *r_num, char *r_bank);//사용자입력값(수신자정보)을 멤버변수에 저장(이름, 은행명)	

	void getClient(char *client_name, char *bank, int &account_balance)const;//db의 사용자 정보를 다른 클래스에 전달
	void getClient(int &account_balance)const;//입출금 후 갱신된 값을 다른 클래스에 전달(오버로딩)
	void getRecipient(char *r_name)const;//db의 수신자 정보를 다른 클래스에 전달

	static void setClient(int new_money);//정적멤버변수를 갱신하기 위한 정적멤버함수
	static int getClient();//정적멤버변수를 다른 클래스에 전달하기 위한 정적멤버함수
	/*getXxx 함수는 DB와의 연결을 통해 private멤버변수에 저장된 값을 ATM객체에서 접근하게 
	하기 위한 함수이다. 
	*/

	int DB_login();		//클라이언트 로그인
	int DB_rpt_login();//계좌이체시 수신자 체크

	int checkResult(); //입출금후 갱신된 결과값을 다시 select하여 멤버변수에 저장.

	int withdraw();//출금(매개변수 없이 정적멤버변수를 통해 계산하기 때문에 연산자오버로딩을 사용하지 않았다.)
	int deposit();//입금(")

	int charge(int charge);//타행이체시 수수료 납부
	int checkClient();//기반클래스의 함수 오버라이딩, 회원목록 출력
};

#endif // ! CALC_DATA_H
