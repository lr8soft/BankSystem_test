#pragma once
#include "basic_func.h"
int MoneyTransfer(SInfo *head,char pwd[],int cardS,int cardR,long double money) {
	int i,tempS,tempR;
	SInfo *accountS, *accountR;
	accountS = SearchByNum(head,cardS);
	accountR = SearchByNum(head,cardR);
	if (accountS == NULL || accountR == NULL) {
		printf("�޷��ҵ��ÿ��ţ�ת��ʧ�ܣ�\n");
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
			printf("��%dת��%lfԪ��%d�ɹ���\n",cardS,money,cardR);
			return 1;
		}else {
			printf("%d��������,ת��ʧ�ܣ�\n",cardS);
			return 0;
		}
	}else {
		printf("�������ת��ʧ�ܣ�\n");
		return 0;
	}
}
int CardCancellation(SInfo *head,char name[],int card,char pwd[]) {
	int input,num,i;
	SInfo *account;
	account = SearchByNum(head, card);
	if (account== NULL) {
		printf("�޷��ҵ��ÿ��ţ�����ʧ�ܣ�\n");
		return -1;
	}
	for (i = 0; i < 3;i++) {
		if (account->data.cardnum[i]==card) {
			num = i;
		}
	}
	if (strcmp(account->data.name,name)==0&&strcmp(account->data.pwd, pwd) == 0) {
		printf("ȷ��ע������%d�𣿸ò���Ϊ����������� ����1��ȷ��ɾ��:\n",card);
		scanf("%d",&input);
		if (input==1) {
			account->data.cardnum[num] = 0;
			account->data.money[num] = 0.0;
			printf("�����ɹ�\n");
			return 1;
		}
		else {
			printf("������ȡ��\n");
			return 0;
		}
	}
	else {
		printf("������Ϣ����!\n");
		return 0;
	}
}
int AccountCancellation(SInfo *head,char name[],char pwd[],int card) {
	int i, num,input;
	SInfo *account;
	account = SearchByNum(head, card);
	if (account == NULL) {
		printf("�޷��ҵ��ÿ��ţ�����ʧ�ܣ�\n");
		return -1;
	}
	for (i = 0; i < 3; i++) {
		if (account->data.cardnum[i] == card) {
			num = i;
		}
	}
	if (strcmp(account->data.name, name) == 0 && strcmp(account->data.pwd, pwd) == 0) {
		printf("ȷ��ע�����˺���������Ϣ����ɾ�����ò���Ϊ����������� ����1��ȷ��ɾ��:\n", card);
		scanf("%d", &input);
		if (input == 1) {
			DeleteAccount(head,card);
			printf("�����ɹ�����Ϣ��ɾ��\n");
			return 1;
		}
		else {
			printf("������ȡ��\n");
			return 0;
		}
	}
	else {
		printf("������Ϣ����\n");
		return 0;
	}
}