//Powered by LT_lrsoft->GuangDong Unversity of finance
#include "pch.h"
#include "func.h"
char bank_name[] = "LT's bank";
SInfo *bankInfo = NULL;
void load_info() {
	bankInfo=ReadInfo();
	if (bankInfo == NULL) {
		PData admin;
		printf("请输入管理员账户：");
		scanf("%s",admin.name);
		printf("\n请输入管理员密码：");
		scanf("%s",admin.pwd);
		printf("\n请输入管理员id：");
		scanf("%s", admin.id_card);
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
void Menu_Info(SInfo *head) {
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
	else {
		printf("查询失败！请检查是否个人信息输入有误！\n");
	}
	
}
void Menu_NewCard(SInfo *head) {
	char id[19], pwd[7];
	printf("\n输入id卡号：");
	scanf("%s", id);
	printf("\n输入账户密码：");
	scanf("%s", pwd);
	int temp = CreateCard(head,pwd,id);
}
void Menu_DrawMoney(SInfo *head) {
	int card; char pwd[7]; long double money = 0;
	printf("\n输入卡号：");
	scanf("%d", &card);
	printf("\n输入账户密码：");
	scanf("%s", pwd);
	printf("\n取款金额：");
	scanf("%lf", &money);
	int temp = DrawMoney(head,card,pwd,money);
}
void Menu_DepositMoney(SInfo *head) {
	int card=0; long double money;
	printf("\n输入银行卡号：");
	scanf("%d", &card);
	printf("\n输入存款金额：");
	scanf("%lf", &money);
	int temp = AccountDeposit(head,card,money);
}
void Menu_CreateAccount(SInfo *head) {
	char id[19],name[7], pwd[7];
	printf("请输入身份证Id、姓名与密码(小于等于6位)，按空格键分隔：");
	scanf("%s %s %s",id,name,pwd);
	head = CreateAccount(head,name,pwd,id);
}
void Menu_AccountCancellation(SInfo *head) {
	char id[19], name[7], pwd[7];
	printf("请输入身份证Id、姓名与密码(小于等于6位)，按空格键分隔：");
	scanf("%s %s %s", id, name, pwd);
	int temp = AccountCancellation(head,name,pwd,id);
}
void Menu_CardCancellation(SInfo *head) {
	char name[7], pwd[7]; int card;
	printf("请输入姓名、密码与卡号，按空格键分隔：");
	scanf("%s %s %d",name,pwd,&card);
	int temp = CardCancellation(head,name,card,pwd);
}
void Main_Admin(SInfo *head) {
	char name[7], pwd[7], id[19];
	printf("请输入管理员用户名、密码以及Id号，按空格分隔：");
	scanf("%s %s %s",name,pwd,id);
	if (strcmp(head->data.name,name)==0&& strcmp(head->data.pwd, pwd) == 0&& strcmp(head->data.id_card, id) == 0) {
		ShowAllInfo(head);
	}
	else {
		printf("认证失败！操作被拒绝！\n");
	}
}
void menu() {
	int input;
	while (1) {
		input = 0;
		printf("\n----------------------------------------\n");
		printf("|    欢迎使用%s的自助操作系统   |\n", bank_name);
		printf("|1.转账                          2.取款|\n");
		printf("|3.存款                      4.账户信息|\n");
		printf("|5.开户                          6.开卡|\n");
		printf("|7.销户                          8.销卡|\n");
		printf("|9.数据查看                     10.退出|\n");
		printf("----------------------------------------\n");
		printf("输入数字编号以进行操作：");
		scanf("%d", &input);
		switch (input) {
		case 1:
			Menu_Transfer(bankInfo); break;
		case 2:
			Menu_DrawMoney(bankInfo); break;
		case 3:
			Menu_DepositMoney(bankInfo); break;
		case 4:
			Menu_Info(bankInfo); break;
		case 5:
			Menu_CreateAccount(bankInfo); break;
		case 6:
			Menu_NewCard(bankInfo); break;
		case 7:
			Menu_AccountCancellation(bankInfo); break;
		case 8:
			Menu_CardCancellation(bankInfo); break;
		case 9:
			Main_Admin(bankInfo); break;
		case 10:
			SaveInfo(bankInfo); exit(0); break;
		default:
			system("cls"); break;

		}
	}
	
}
int main()
{
	load_info();
	menu();
	return 0;
}

