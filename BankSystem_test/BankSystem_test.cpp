// BankSystem_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include "func.h"
char bank_name[] = "LT's bank";
SInfo *bankInfo = NULL;
void load_info() {
	bankInfo=ReadInfo();
	if (bankInfo == NULL) {
		PData admin;
		printf("请输入管理员账户以及密码，用英文逗号分隔：");
		scanf("%s",admin.name);
		scanf("%s",admin.pwd);
		strcpy(admin.id_card,"Administrator");
		admin.cardnum[0] = -88888888;
		admin.money[0] = -88888888;
		bankInfo = AddToList(bankInfo,admin);
		SaveInfo(bankInfo);
	}
}
void Menu_Transfer(SInfo *head) {
	int card0, card1;
	long double money;
	char pwd[7];
	printf("\n输入要转账的银行卡号：");
	scanf("%d",&card0);
	printf("\n输入接受钱款的卡号：");
	scanf("%d",&card1);
	printf("\n输入转账金额：");
	scanf("%lf",&money);
	printf("\n输入账户密码：");
	scanf("%s",pwd);
	int info = MoneyTransfer(head,pwd,card0,card1,money);
}
void Menu_info(SInfo *head) {
	int card_num = 0,i;
	char id[19], pwd[7];
	printf("\n输入id卡号：");
	scanf("%s",id);
	printf("\n输入账户密码：");
	scanf("%s",pwd);
	SInfo *temp = SearchById(head,id);
	if (temp!=NULL) {
		if (strcmp(temp->data.pwd, pwd) == 0) {
			printf("\n%s先生/女士，注册身份id:%s\n",temp->data.name,temp->data.id_card);
			for (i = 0; i < 3;i++) {
				card_num++;
			}
			printf("有%d张银行卡:",card_num);
			for (i = 0; i < card_num;i++) {
				printf("\n卡号%d: 所有存款:%lf",temp->data.cardnum[i],temp->data.money[i]);
			}
		}
		
	}
	
}
void Menu_newcard(SInfo *head) {
	char id[19], pwd[7];
	printf("\n输入id卡号：");
	scanf("%s", id);
	printf("\n输入账户密码：");
	scanf("%s", pwd);
	int temp = CreateCard(head,pwd,id);
}
void Menu_drawmoney(SInfo *head) {
	int card; char pwd[7]; long double money = 0;
	printf("\n输入卡号：");
	scanf("%d", &card);
	printf("\n输入账户密码：");
	scanf("%s", pwd);
	printf("\n取款金额：");
	scanf("%lf", &money);
	int temp = DrawMoney(head,card,pwd,money);
}
void Menu_depositmoney(SInfo *head) {
	int card=0; long double money;
	printf("\n输入银行卡号：");
	scanf("%d", &card);
	printf("\n输入存款金额：");
	scanf("%lf", &money);
	int temp = AccountDeposit(head,card,money);
}
void menu() {
	int input=0;
menu_ui:
	printf("\n----------------------------------------\n");
	printf("|    欢迎使用%s的自助操作系统   |\n",bank_name);
	printf("|1.转账                          2.取款|\n");
	printf("|3.存款                      4.账户信息|\n");
	printf("|5.开户                          6.开卡|\n");
	printf("|7.销户                          8.销卡|\n");
	printf("|9.后台管理                     10.退出|\n");
	printf("----------------------------------------\n");
	printf("输入数字编号以进行操作：");
	scanf("%d",&input);
	switch (input) {
		case 1:
			Menu_Transfer(bankInfo); goto menu_ui; break;
		case 2:
			Menu_drawmoney(bankInfo); goto menu_ui; break;
		case 3:
			Menu_depositmoney(bankInfo); goto menu_ui; break;
		case 4:
			Menu_info(bankInfo); goto menu_ui; break;
		case 6:
			Menu_newcard(bankInfo); goto menu_ui; break;
		case 10:
			SaveInfo(bankInfo); exit(0); break;
		default:
			system("cls"); goto menu_ui; break;

	}
}
int main()
{
	load_info();
	menu();
	return 0;
}

