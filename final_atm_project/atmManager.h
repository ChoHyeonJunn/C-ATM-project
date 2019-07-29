#include "ATM.h"
#include"DBManager.h"

class atmManager : public ATM {
private:
	DBManager dbM;
	DBManager *dbManager;

	char machine_num[20];		//기계 고유번호
	char manager_id[20];		//매니저 아이디
	char manager_pwd[20];		//매니저 비밀번호
	char manager_balance[100];	//매니저 잔액

public:
	int login();		//로그인
	void withdraw();	//출금
	void deposit();		//입금
	void checkAccount();//기계잔액확인
	/*추상클래스 ATM 의 완전가상함수들을 오버라이딩*/


	void checkClient(); //회원목록
};