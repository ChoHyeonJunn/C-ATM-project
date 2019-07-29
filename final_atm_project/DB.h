#ifndef  CALC_DATA_D
#define  CALC_DATA_D

#include <mysql.h>

class DB {
protected:
	MYSQL * connection = NULL, conn;
	MYSQL_RES   *sql_result;
	MYSQL_ROW   sql_row;
	DB();
	~DB();

public:
	virtual int DB_login() = 0;
	virtual int checkResult() = 0;
};
#endif
