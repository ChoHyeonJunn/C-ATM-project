#pragma once
#include "DBManager.h"
#include "atmManager.h"
#include "atmClient.h"
class Start {
private:
	int menu;
public:
	//ATM 초기 메뉴화면
	void menuStart();	
	//관리자를 위한 메뉴화면
	void menuManager(atmManager manager);
};