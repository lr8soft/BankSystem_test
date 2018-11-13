#pragma once
#include "basic_func.h"
#include <time.h>
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
			printf("从卡号%d转账%lf元到卡号%d成功！\n",cardS,money,cardR);
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
int AccountDeposit(SInfo *head,int card,long double money) {
	int temp = Deposit(head,card,money);
	switch (temp)
	{
		case -1:
			printf("存款失败！账号不存在！\n"); break;
		case 1:
			printf("成功向卡号%d存入%lf元。\n", card, money); break;
		default:
			printf("未知原因导致存款失败！\n"); break;
	}
	return temp;
}
int AccountDrawMoney(SInfo *head,int card,char pwd[],long double money) {
	int temp = DrawMoney(head,card,pwd,money);
	switch (temp)
	{
		case 0:
			printf("余额不足，取款失败！\n"); break;
		case 1:
			printf("取款成功，请取走你的钱款\n"); break;
		default:
			printf("卡号或者密码错误！\n"); break;
	}
	return temp;
}
SInfo *CreateAccount(SInfo *head, char name[], char pwd[], char id_card[]) {
	SInfo *temp = SearchById(head, id_card), *htemp;
	PData info;
	if (temp != NULL) {
		printf("该身份id卡已经注册了账户，注册失败！\n");
		return NULL;
	}
	strcpy(info.id_card, id_card);
	strcpy(info.name, name);
	strcpy(info.pwd, pwd);
	htemp = AddToList(head, info);
	if (htemp != NULL) {
		head = htemp;
		return head;
	}
	else {
		printf("未知原因导致注册失败！\n");
		return head;
	}
}
int CreateCard(SInfo *head,char pwd[],char id_card[]) {
	int card_num,i,remain=0;
getRandCard:
	srand(time(NULL));
	card_num= rand() * 10;
	SInfo *temp = SearchByNum(head,card_num),*htemp;
	htemp = SearchById(head,id_card);
	if (temp != NULL) {
		goto getRandCard;
	}
	for (i = 0; i < 3;i++) {
		if (htemp->data.cardnum[i] == 0) remain++;
	}
	if (remain>0) {
		htemp->data.cardnum[3 - remain] = card_num;
		printf("开卡成功！卡号为&d",card_num);
		return 1;
	}else {
		printf("已达最大三张卡的份额！开卡失败！\n");
		return -1;
	}
}