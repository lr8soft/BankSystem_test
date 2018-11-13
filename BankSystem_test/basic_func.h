#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define MAX_LEN 5
typedef struct {
	int cardnum[3] = {0,0,0};
	long double money[3] = {0.0,0.0,0.0};
	char name[7];
	char pwd[7];
}PData;
typedef struct {
	PData data[MAX_LEN];
	int datalen;
}SearchInfo;
typedef struct Node {
	PData data;
	struct Node *nextInfo;
}SInfo;
void SearchInit(SearchInfo *list) {
	list->datalen = 0;
}
SInfo *AddToList(SInfo *head, PData data) {
	SInfo *temp, *htemp;
	if (!(temp=(SInfo*)malloc(sizeof(SInfo)))) {
		printf("内存申请失败，无法注册新用户！\n");
		return NULL;
	}else {
		temp->data = data;
		temp->nextInfo = NULL;
		if (head==NULL) {
			head = temp;
			return head;
		}
		htemp = head;
		while (htemp->nextInfo!=NULL) {
			htemp = htemp->nextInfo;
		}
		htemp->nextInfo = temp;
		return head;
	}
}
SInfo *SearchByNum(SInfo *head, int cnum) {
	SInfo *htemp;
	int i=0;
	htemp = head;
	while (htemp) {
		for (i = 0; i < 3;i++) {
			if (htemp->data.cardnum[i]==cnum) {
				return htemp;
			}
		}
		htemp = htemp->nextInfo;
	}
	printf("无法找到该用户！请检查卡号是否输入错误！\n");
	return NULL;
}
SearchInfo *SearchByName(SInfo *head,char name[]) {//记得free()
	int len = 0;
	SInfo *htemp;
	SearchInfo sinfo;
	SearchInit(&sinfo);
	htemp = head;
	while (htemp) {
		if (strcmp(htemp->data.name,name)==0) {
			sinfo.data[len] = htemp->data;
			len++;
		}
		htemp = htemp->nextInfo;
	}
	if (len==0) {
		return NULL;
	}
	else {
		return &sinfo;
	}
}
int DeleteAccount(SInfo *head, int cardnum) {
	SInfo *htemp,*node; int i = 0;
	htemp = head;
	node = head;
	while (htemp) {
		for (i = 0; i < 3;i++){
			if (htemp->data.cardnum[i]==cardnum) {
				node->nextInfo = htemp->nextInfo;
				free(htemp);
				return 1;
			}
		}
		node = htemp;
		htemp = htemp->nextInfo;
	}
	return 0;
}
SInfo *SInfoInit(SInfo *head) {
	PData temp;
	temp.cardnum[0] = -8888888;
	temp.money[0] = -88888888.0;
	strcpy(temp.name, "FILLED");
	strcpy(temp.pwd, "ABCDEF");
	head = AddToList(head, temp);
	return head;
}
int InfoLen(SInfo *head) {
	int len = 0;
	SInfo *htemp;
	htemp = head;
	while (htemp) {
		len++;
		htemp = htemp->nextInfo;
	}
	return len;
}
void ShowAllInfo(SInfo *head) {
	SInfo *htemp;
	htemp = head;
	while (htemp) {
		printf("信息:[(%d,%d,%d),%s,%s]",htemp->data.cardnum[0], htemp->data.cardnum[1], htemp->data.cardnum[2], htemp->data.name, htemp->data.pwd);
		printf("￥:[%lf,%lf,%lf]\n",htemp->data.money[0], htemp->data.money[1], htemp->data.money[2]);
		htemp = htemp->nextInfo;
	}
}
int SaveInfo(SInfo *head) {
	FILE *fp; SInfo *htemp; int i = 0;
	int listlen = InfoLen(head);
	htemp = head;
	fp = fopen("info.dat","wb");
	fwrite(&listlen, sizeof(int), 1, fp);
	while (htemp) {
		for (i = 0; i < 3;i++) {
			fwrite(&htemp->data.cardnum[i],sizeof(int),1,fp);
			fwrite(&htemp->data.money[i], sizeof(long double), 1, fp);
		}
		fwrite(htemp->data.name,sizeof(htemp->data.name),1,fp);
		fwrite(htemp->data.pwd, sizeof(htemp->data.pwd), 1, fp);
		htemp = htemp->nextInfo;
	}
	fclose(fp);
	printf("数据已完成写入！\n");
	return 1;
}
SInfo *ReadInfo() {
	FILE *fp; SInfo *htemp=NULL; PData tdata; int i,j;
	int listlen;
	fp = fopen("info.dat","rb");
	if (fp == NULL) return NULL;
	fread(&listlen,sizeof(int),1,fp);
	for (j = 0; j < listlen;j++) {
		for (i = 0; i < 3; i++) {
			fread(&tdata.cardnum[i], sizeof(int), 1, fp);
			fread(&tdata.money[i], sizeof(long double), 1, fp);
		}
		fread(tdata.name, sizeof(tdata.name), 1, fp);
		fread(tdata.pwd, sizeof(tdata.pwd), 1, fp);
		htemp=AddToList(htemp,tdata);
	}
	fclose(fp);
	printf("数据文件已全部写入!\n");
	return htemp;
}