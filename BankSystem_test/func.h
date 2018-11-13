#pragma once
#include "basic_func.h"
#include <time.h>
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
			printf("�ӿ���%dת��%lfԪ������%d�ɹ���\n",cardS,money,cardR);
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
int AccountDeposit(SInfo *head,int card,long double money) {
	int temp = Deposit(head,card,money);
	switch (temp)
	{
		case -1:
			printf("���ʧ�ܣ��˺Ų����ڣ�\n"); break;
		case 1:
			printf("�ɹ��򿨺�%d����%lfԪ��\n", card, money); break;
		default:
			printf("δ֪ԭ���´��ʧ�ܣ�\n"); break;
	}
	return temp;
}
int AccountDrawMoney(SInfo *head,int card,char pwd[],long double money) {
	int temp = DrawMoney(head,card,pwd,money);
	switch (temp)
	{
		case 0:
			printf("���㣬ȡ��ʧ�ܣ�\n"); break;
		case 1:
			printf("ȡ��ɹ�����ȡ�����Ǯ��\n"); break;
		default:
			printf("���Ż����������\n"); break;
	}
	return temp;
}
SInfo *CreateAccount(SInfo *head, char name[], char pwd[], char id_card[]) {
	SInfo *temp = SearchById(head, id_card), *htemp;
	PData info;
	if (temp != NULL) {
		printf("�����id���Ѿ�ע�����˻���ע��ʧ�ܣ�\n");
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
		printf("δ֪ԭ����ע��ʧ�ܣ�\n");
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
		printf("�����ɹ�������Ϊ&d",card_num);
		return 1;
	}else {
		printf("�Ѵ�������ſ��ķݶ����ʧ�ܣ�\n");
		return -1;
	}
}