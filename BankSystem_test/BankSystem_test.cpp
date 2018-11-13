// BankSystem_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include "func.h"
void test_func() {
	PData lt;
	lt.cardnum[0] = 2333;
	lt.money[0] = 623434.0;
	strcpy(lt.name, "lrsoft");
	strcpy(lt.pwd, "aaaaaa");
	strcpy(lt.id_card, "440101000000000000");
	SInfo *info = NULL;
	info=SInfoInit(info);
	info = AddToList(info, lt);
	info = AddToList(info, lt);
	info = AddToList(info, lt);
	ShowAllInfo(info);
	SaveInfo(info);

	SInfo *test = NULL;
	test = ReadInfo();
	ShowAllInfo(test);
	DeleteAccount(test,2333);
	ShowAllInfo(test);

	test=SearchByNum(test,2333);
	MoneyTransfer(info,lt.pwd,2333, -8888888,2000);
	ShowAllInfo(info);
	CardCancellation(info,lt.name,2333,lt.pwd);
	ShowAllInfo(info);
	AccountCancellation(info,lt.name,lt.pwd,2333);
	ShowAllInfo(info);
}
int main()
{
	test_func();
	system("pause");
	return 0;
}

