#pragma once
#include "DBManager.h"
#include "atmManager.h"
#include "atmClient.h"
class Start {
private:
	int menu;
public:
	//ATM �ʱ� �޴�ȭ��
	void menuStart();	
	//�����ڸ� ���� �޴�ȭ��
	void menuManager(atmManager manager);
};