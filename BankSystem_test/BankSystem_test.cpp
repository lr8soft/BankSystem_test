// BankSystem_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "basic_func.h"
void test_func() {
	PData lt,testdata;
	lt.cardnum[0] = 2333;
	lt.money[0] = 2333333;
	strcpy(lt.name, "lrsoft");
	strcpy(lt.pwd, "aaaaaa");
	SInfo *info = NULL;
	info = AddToList(info,testdata);
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
}
int main()
{
	test_func();
	system("pause");
	return 0;
}

