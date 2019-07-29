#ifndef  CALC_DATA_M
#define  CALC_DATA_M

#include <mysql.h>

class DBManager{
private://클래스 내부에서는 접근가능 / 클래스 외부에서는 접근 불가(캡슐화)

	char machine_num[20] = "506";
	char manager_id[20];
	char manager_pwd[20];
	char manager_balance[100];

protected://파생클래스에서 접근가능하도록 protected로 선언
	MYSQL * connection = NULL, conn;
	MYSQL_RES   *sql_result;
	MYSQL_ROW   sql_row;
	/*DB 연동시 쿼리를 보내기 위한 중요한 변수들이다.
	DBManager의 파생클래스인 DBClient에서도 이 변수들을 사용할 수 있도록 protected로 선언하였다.*/

public:
	DBManager();
	~DBManager();
	/*생성자, 소멸자는 파생클래스에 상속되지는 않지만 파생객체가 생성될 때 기반클래스의 생성자, 소멸자
	까지 연속적으로 자동 호출된다.
	이 경우 DB에 connect 하는 부분을 생성자에 기술하고 disconnect 하는 부분을 소멸자에 기술하였다.
	따라서 기반클래스인 DBManager와 파생클래스 DBClient 모두 DB에 쿼리문을 보내는 함수에서 따로
	connection과 disconnect 하는 부분을 기술할 필요가 없다.*/

	void setManager(char *manager_id, char *manager_pwd); //사용자입력값을 멤버변수에 저장(계좌번호,

	void getManager(char *machine_num, char *manager_balance)const;//db의 사용자 정보를 다른 클래스에 전달 const예약어로 멤버변수값을 변경하지 못하도록 하였다.
	void getManager(char *manager_balance)const;//getResult:입,출금 이후의 갱신된 값을 atmManager에 전달, (오버로딩)

	int DB_login();		//매니저 로그인
	int checkResult(); //입출금후 갱신된 결과값을 다시 select하여 멤버변수에 저장.

	int operator-(int amount);//출금
	int operator+(int amount);//입금
	/*기본 자료형에서는 + , -, *등 의 연산이 가능했지만 사용자정의 자료형에서는 이러한 연산이 불가능하다.
		하지만 클래스는 연산자 오버로딩을 통해 이러한 연산을 가능하게 할 수 있다.
		이미 기본 자료형에 사용되던 연산자를 다시 정의하는 것이기 때문에
		연산자 오버로딩 이라고 부른다.*/

	virtual int checkClient();//회원수 출력 기반클래스 에서 가상함수로 선언
	/*바인딩은 함수 호출을 해당 함수의 정의와 결합해 둔 것이다.
	일반적으로 컴파일 시점에 호출할 멤버함수가 결정되고 실행시에는 컴파일 시점에 바인딩 되어 결정된 함수를
	실행만 한다.
	이처럼 컴파일 할 때 미리 호출될 함수의 결정을 하는것을 정적/이른 바인딩 이라고 한다.
	컴파일 시점에는 선언된 포인터 변수의 자료형에 대한 정보만 있고 실행 시점에 변수값이 저장되기 때문에
	정적 바인딩 에서는 포인터 변수의 자료형이 호출될 함수를 결정하게 되는 것이다.
	
	포인터 변수의 자료형이 아니라 객체 클래스형에 따라 호출될 멤버함수가 결정되도록 하고 싶다면
	동적/늦은 바인딩 을 이용할 수 있다.
	이는 호출할 함수가 컴파일 할 때 결정되지 않고 프로그램이 실행되는 동안 결정된다.
	
	동적 바인딩을 하고자 하는 함수에 기반클래스로 가서 함수 원형정의 앞에 virtual을 붙이면 가상함수가 되고
	이는 파생클래스에 상속된다.*/
};

#endif // ! CALC_DATA_H
