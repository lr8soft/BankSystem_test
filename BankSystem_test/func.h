#pragma once
#include "basic_func.h"
int MoneyTransfer(SInfo *head,char pwd[],int cardS,int cardR,long double money) {
	int i,tempS,tempR;
	SInfo *accountS, *accountR;
	accountS = SearchByNum(head,cardS);
	accountR = SearchByNum(head,cardR);
	if (accountS == NULL || accountR == NULL) {
		printf("无法找到该卡号，转账失败！\n");
		return -1;
	}
	for (i = 0; i < 3;i++) {
		if (accountS->data.cardnum[i]==cardS) {
			tempS = i;
		}
		if (accountR->data.cardnum[i] == cardR) {
			tempR = i;
		}
	}
	if (strcmp(accountS->data.pwd,pwd)==0) {//pwd correct
		if (accountS->data.money[tempS]-money>=0) {
			accountS->data.money[tempS] -= money;
			accountR->data.money[tempR] += money;
			printf("从%d转账%lf元到%d成功！\n",cardS,money,cardR);
			return 1;
		}else {
			printf("%d卡内余额不足,转账失败！\n",cardS);
			return 0;
		}
	}else {
		printf("密码错误！转账失败！\n");
		return 0;
	}
}
int CardCancellation(SInfo *head,char name[],int card,char pwd[]) {
	int input,num,i;
	SInfo *account;
	account = SearchByNum(head, card);
	if (account== NULL) {
		printf("无法找到该卡号，操作失败！\n");
		return -1;
	}
	for (i = 0; i < 3;i++) {
		if (account->data.cardnum[i]==card) {
			num = i;
		}
	}
	if (strcmp(account->data.name,name)==0&&strcmp(account->data.pwd, pwd) == 0) {
		printf("确认注销卡号%d吗？该操作为不可逆操作！ 输入1以确认删除:\n",card);
		scanf("%d",&input);
		if (input==1) {
			account->data.cardnum[num] = 0;
			account->data.money[num] = 0.0;
			printf("操作成功\n");
			return 1;
		}
		else {
			printf("操作已取消\n");
			return 0;
		}
	}
	else {
		printf("个人信息有误!\n");
		return 0;
	}
}
int AccountCancellation(SInfo *head,char name[],char pwd[],int card) {
	int i, num,input;
	SInfo *account;
	account = SearchByNum(head, card);
	if (account == NULL) {
		printf("无法找到该卡号，操作失败！\n");
		return -1;
	}
	for (i = 0; i < 3; i++) {
		if (account->data.cardnum[i] == card) {
			num = i;
		}
	}
	if (strcmp(account->data.name, name) == 0 && strcmp(account->data.pwd, pwd) == 0) {
		printf("确认注销该账号吗？所有信息将会删除，该操作为不可逆操作！ 输入1以确认删除:\n", card);
		scanf("%d", &input);
		if (input == 1) {
			DeleteAccount(head,card);
			printf("操作成功，信息已删除\n");
			return 1;
		}
		else {
			printf("操作已取消\n");
			return 0;
		}
	}
	else {
		printf("个人信息有误！\n");
		return 0;
	}
}