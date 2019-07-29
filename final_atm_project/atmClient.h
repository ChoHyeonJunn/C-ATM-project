#include "ATM.h"
#include "DBClient.h"

class atmClient : public ATM {
private:
	char client_name[20];//사용자이름
	char account_num[20];//계좌번호
	char account_pwd[10];//비밀번호
	char bank[20];		 //은행명
	int account_balance; //잔액
	
	const int fee = 700; //타행 이체시 수수료
	char recipient_name[20];//계좌이체시 수신자 이름
	DBClient dbcon;
	DBManager dbM;

public:
	int login();		//로그인
	void withdraw();	//출금
	void deposit();		//입금
	void checkAccount();//잔액확인
	/*추상클래스 ATM 의 완전가상함수들을 오버라이딩*/

	void transfer();	//계좌이체
};