#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

void closeormenu();
void menu();
struct AcountBank* pHead = NULL;
int h = 0;
int keyofacount = 1;



struct AcountBank
{
	int key;
	char nameofperson[80];
	char lastname[80];
	int day, month, year;
	char adress[60];
	double phone;
	float history[10];
	char kod[5];
	float balance;
	struct AcountBank *pNext;
};

struct AcountBank* find(struct AcountBank* pHead, int key)
{
	while (pHead != NULL)
	{
		if (pHead->key == key)
		{
			return pHead;
		}
		pHead = pHead->pNext;
	}

	if (pHead == NULL)
	{
		printf("This account was not found\n");
	}

	return 0;
}

void fordelay(int j)
{
	int i, k;
	for (i = 0; i < j; i++)
		k = i;
}

char *kodsecret()
{
	char kod[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789";
	char *kodsodi = (char *)malloc(5 * sizeof(char));
	int i, j = 0, t = 0;
	i = rand() % 10;
	while (t < 5)
	{
		kodsodi[t] = kod[i];
		i = (rand() % (61 - 1 + 1)) + 1;
		t++;
	}
	kodsodi[t++] = '\0';



	return kodsodi;
}

int key()
{
	return keyofacount++;
}

int keyhistory()
{
	if (h == 9)
	{
		h = 0;
	}
	return h++;
}


struct AcountBank* add(struct AcountBank* phead)
{
	struct AcountBank* pNewNode = (struct AcountBank*)malloc(sizeof(struct AcountBank));
	char *adri;
	int i, j;
	if (pNewNode)
	{
		printf("\nEnter the name:");
		scanf("%s", pNewNode->nameofperson);
		printf("\nEnter the last name:");
		scanf("%s", pNewNode->lastname);
		printf("\nEnter your addras(Street name/Street number/City):");
		scanf("%s", pNewNode->adress);
		printf("\nEnter the date of birth(mm/dd/yyyy):");
		scanf("%d/%d/%d", &pNewNode->day, &pNewNode->month, &pNewNode->year);
		if ((2020 - pNewNode->year) < 16)
		{
			printf("Unable to open account");
			return NULL;
		}
		printf("\nEnter your phone:");
		scanf("%lf", &pNewNode->phone);
		pNewNode->key = key();
		strcpy(pNewNode->kod, kodsecret());
		printf("\nyour kod:%s", pNewNode->kod);
		pNewNode->balance = 0;
		for (j = 0; j < 10; j++)
		{
			pNewNode->history[j] = 0;
		}
		pNewNode->pNext = phead;
	}

	for (i = 0; i <= 6; i++)
	{
		fordelay(100000000);
		printf("\nAccount created successfully!");
	}

	return pNewNode;
}

void updating(struct AcountBank* phead, int key)
{
	struct AcountBank* up = NULL;
	up = find(phead, key);
	int i = 0, choice = 0;
	char code[5];
login_try:
	printf("Enter your code:");
	scanf("%s", &code);

	if (strcmp(code, up->kod) == 0)
	{
	menu_again:
		printf("\n\n\t\t1.Update first name\n\t\t2.Update last name\n\t\t3.Update Date of birth\n\t\t4.Update Address\n\t\t5.Update phone\n\t\t6.Update Kode\n\t\t7.back to menu\n\n\n\n\n\t\t Enter your choice:");
		scanf("%d", &choice);
		system("cls");
		switch (choice)
		{
		case 1:
			printf("\nEnter the name:");
			scanf("%s", &up->nameofperson);
			break;
		case 2:
			printf("\nEnter the last name:");
			scanf("%s", &up->lastname);
			break;
		case 3:
			printf("\nEnter the date of birth(mm/dd/yyyy):");
			scanf("%d/%d/%d", &up->day, &up->month, &up->year);
			break;
		case 4:
			printf("\nEnter your adress:");
			scanf("%s", &up->adress);
			break;
		case 5:
			printf("\nEnter your phone:");
			scanf("%lf", &up->phone);
			break;
		case 6:
			strcpy(up->kod, kodsecret());
			printf("\nyour kod:%s", up->kod);
			break;
		case 7:
			closeormenu();
			break;

		}
		goto menu_again;

	}

	else
	{
		i++;
		if (i == 3)
		{
			exit(0);
		}
		system("cls");
		printf("\n\nWrong password try again!!\a\a\a\n");
	}

	goto login_try;

}

void addmoney(struct AcountBank* phead, int key)
{
	struct AcountBank* pHeadmnoney = NULL;
	pHeadmnoney = find(phead, key);
	char code[5];
	float money;
	int i = 0, choice = 0;
try_connect:
	printf("Enter your code:");
	scanf("%s", &code);
	if (strcmp(code, pHeadmnoney->kod) == 0)
	{
	Pull_screen:
		printf("\n\n\t\t1.Deposit\n\t\t2.withdrawal\n\t\t3.back to menu\n\n\n\n\n\t\t Enter your choice:");
		scanf("%d", &choice);
		system("cls");
		if (choice == 1)
		{
			printf("\nWrite down how much money you want to deposit:");
			scanf("%f", &money);
			pHeadmnoney->balance += money;
			pHeadmnoney->history[keyhistory()] = money;
		}
		else if (choice == 2)
		{
			printf("\nWrite down how much money you want to withdrawal:");
			scanf("%f", &money);
			if (money > pHeadmnoney->balance)
			{
				printf("\nYou can't withdraw money");
				printf("\nYou can to withdraw: %.2f", pHeadmnoney->balance);
			}
			else
			{
				pHeadmnoney->balance -= money;
				pHeadmnoney->history[keyhistory()] = money;
			}
		}
		else if (choice == 3)
		{
			closeormenu();
		}
		goto Pull_screen;
	}

	else
	{
		i++;
		system("cls");
		printf("\n\nWrong password try again!!\a\a\a");
		if (i == 3)
		{
			exit(0);
		}
		goto try_connect;
	}

}

void closeormenu(void)
{
	int main_exit;
	printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
	scanf("%d", &main_exit);
	system("cls");
	if (main_exit == 1)
		menu();
	else
		exit(0);
}

void information(struct AcountBank* phead, int key)
{
	struct AcountBank* pHeadinfo = NULL;
	char code[5];
	pHeadinfo = find(phead, key);
	int i = 0;
try_connect:
	printf("Enter your code:");
	scanf("%s", &code);
	if (strcmp(code, pHeadinfo->kod) == 0)
	{
		printf("%d : %s : %s : %.2f ILS : birthy:%d/%d/%d : adress:%s : kod:%s : phone:%.0lf\n", pHeadinfo->key, pHeadinfo->nameofperson, pHeadinfo->lastname, pHeadinfo->balance, pHeadinfo->day, pHeadinfo->month, pHeadinfo->year, pHeadinfo->adress, pHeadinfo->kod, pHeadinfo->phone);
		printf("History:\n");
		for (i = 0; i < 10; i++)
		{
			printf("%.2f\n", pHeadinfo->history[i]);

		}
	}

	else
	{
		i++;
		system("cls");
		printf("\n\nWrong password try again!!\a\a\a");
		if (i == 3)
		{
			exit(0);
		}
		goto try_connect;
	}

	closeormenu();
}

struct AcountBank* removea(struct AcountBank* currP)
{
	struct AcountBank* ptemp = pHead;
	if (currP == NULL)
		return NULL;

	ptemp = currP->pNext;
	free(currP);
	return ptemp;

}

void Remove(struct AcountBank* phead, int key)
{
	struct AcountBank* ptemp = NULL;
	ptemp = find(phead, key);
	char code[5];
	int noyes;
	int i = 0;
try_connect:
	printf("Enter your code:");
	scanf("%s", &code);
	if (strcmp(code, ptemp->kod) == 0)
	{
		printf("Are you sure you want to delete the account?\n Press 1 if yes\n press 2 if no\n");
		printf("your choice:");
		scanf("%d", &noyes);
		if (noyes == 1)
		{
			removea(ptemp);
			printf("Your account has been deleted\n");
			closeormenu();
		}
		if (noyes == 2)
		{
			system("cls");
			closeormenu();
		}
	}

	else
	{
		i++;
		system("cls");
		printf("\n\nWrong password try again!!\a\a\a");
		if (i == 3)
		{
			exit(0);
		}
		goto try_connect;
	}

	closeormenu();
}

float sumofthebank(struct AcountBank* phead)
{
	float sum = 0;
	while (phead != NULL)
	{
		sum += phead->balance;
		phead = phead->pNext;
	}

	return sum;
}

void listall(struct AcountBank* phead)
{
	while (pHead != NULL)
	{
		printf("%d : %s : %s : %.2f ILS \n", pHead->key, pHead->nameofperson, pHead->lastname, pHead->balance);
		pHead = pHead->pNext;
	}
}

void listalltotxtfile(struct AcountBank* phead)
{
	FILE *f = fopen("Actions.txt", "a+");
	while (pHead != NULL)
	{
		fprintf(f, "%d : %s : %s : %.2f ILS \n", pHead->key, pHead->nameofperson, pHead->lastname, pHead->balance);
		pHead = pHead->pNext;
	}
}

void FindMax(struct AcountBank* phead)
{
	FILE *f = fopen("Actions.txt", "a+");
	struct AcountBank* result = NULL;
	int max = phead->balance;
	result = phead;
	while (phead)
	{
		if (phead->balance > max)
		{
			max = phead->balance;
			result = phead;
		}
		phead = phead->pNext;
	}

	printf("%d : %s : %s : %.2f ILS", result->key, result->nameofperson, result->lastname, result->balance);
	fprintf(f, "max acount money: %d : %s : %s : %.2f ILS", result->key, result->nameofperson, result->lastname, result->balance);
}

void Findold(struct AcountBank* phead)
{
	FILE *f = fopen("Actions.txt", "a+");
	struct AcountBank* result = NULL;
	int age = 2020-phead->year;
	result = phead;
	while (phead)
	{
		if (2020-phead->year > age)
		{
			age = 2020-phead->year;
			result = phead;
		}
		phead = phead->pNext;
	}

	printf("%d : %s : %s : %.2f ILS", result->key, result->nameofperson, result->lastname, result->balance);
	fprintf(f, "the most old acount: %d : %s : %s : %.2f ILS", result->key, result->nameofperson, result->lastname, result->balance);
}

void Findyoung(struct AcountBank* phead)
{
	FILE *f = fopen("Actions.txt", "a+");
	struct AcountBank* result = NULL;
	int age = 2020 - phead->year;
	result = phead;
	while (phead)
	{
		if (2020 - phead->year < age)
		{
			age = 2020 - phead->year;
			result = phead;
		}
		phead = phead->pNext;
	}

	printf("%d : %s : %s : %.2f ILS", result->key, result->nameofperson, result->lastname, result->balance);
	fprintf(f, "the most old yound: %d : %s : %s : %.2f ILS", result->key, result->nameofperson, result->lastname, result->balance);
}

void FindMin(struct AcountBank* phead)
{
	FILE *f = fopen("Actions.txt", "a+");
	struct AcountBank* result = NULL;
	int min = phead->balance;
	result = phead;
	while (phead)
	{
		if (phead->balance < min)
		{
			min = phead->balance;
			result = phead;
		}

		phead = phead->pNext;
	}

	printf("%d : %s : %s : %.2f ILS", result->key, result->nameofperson, result->lastname, result->balance);
	fprintf(f, "min acount money: %d : %s : %s : %.2f ILS", result->key, result->nameofperson, result->lastname, result->balance);

}

void infoonthebank(struct AcountBank* phead)
{
	FILE *f = fopen("Actions.txt", "a+");
	float sumofbank;
	int choice = 0;
	char pass[10], password[10] = "bankben";
	int i = 0;
main_pas:
	printf("\n\n\t\tEnter the password to login:");
	scanf("%s", pass);
	if (strcmp(pass, password) == 0)
	{
		printf("\n\nPassword Match!\nLOADING");
		for (i = 0; i <= 6; i++)
		{
			fordelay(100000000);
			printf(".");
		}
		system("cls");
		goto menuofbank;
	}
	else
	{
		i++;
		system("cls");
		printf("\n\nWrong password try again!!\a\a\a");
		if (i == 3)
		{
			exit(0);
		}
	}
	goto main_pas;

menuofbank:
	printf("\n\n\t\t1.The total amount of money in the bank\n\t\t2.A list of all account numbers\n\t\t3.The account with the highest amount\n\t\t4.The account with the lowest amount\n\t\t5.The oldest customer in the bank\n\t\t6.The youngest customer in the bank\n\t\t7.Print the information into a file\n\t\t9.exit\n\n\n\n\n\t\t Enter your choice:");
	scanf("%d", &choice);
	system("cls");
	switch (choice)
	{
	case 1:
		sumofbank = sumofthebank(phead);
		printf("the sum of bank:%.2f\n", sumofbank);
		fprintf(f, "the sum of bank: %.2f\n", sumofbank);
		goto menuofbank;
		break;
	case 2:
		listall(phead);
		goto menuofbank;
		break;
	case 3:
		FindMax(phead);
		goto menuofbank;
		break;
	case 4:
		FindMin(phead);
		goto menuofbank;
		break;
	case 5:
		Findold(phead);
		goto menuofbank;
		break;
	case 6:
		Findyoung(phead);
		goto menuofbank;
		break;
	case 7:
		listalltotxtfile(phead);
		fclose(f);
		printf("the info in Actions.txt");
		closeormenu();
		break;
	case 8:
		closeormenu();
		break;
	}
}

void menu(void)
{
	int choice = 0, numofbank;
	system("color 70");
	printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
	printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\t\t1.Create new account\n\t\t2.Update bank account\n\t\t3.Make a deposit / withdrawal \n\t\t4.Account information\n\t\t5.Remove Account\n\t\t6.View customer data\n\t\t7.exit\n\n\n\n\n\t\t Enter your choice:");
	scanf("%d", &choice);
	system("cls");
	switch (choice)
	{
	case 1:
		pHead = add(pHead);
		system("cls");
		closeormenu();
		break;
	case 2:
		printf("Enter your Key Acount:");
		scanf("%d", &numofbank);
		updating(pHead, numofbank);
		break;
	case 3:
		printf("Enter your Key Acount:");
		scanf("%d", &numofbank);
		addmoney(pHead, numofbank);
		break;
	case 4:
		printf("Enter your Key Acount:");
		scanf("%d", &numofbank);
		information(pHead, numofbank);
		break;
	case 5:
		printf("Enter your Key Acount:");
		scanf("%d", &numofbank);
		Remove(pHead, numofbank);
		break;
	case 6:
		infoonthebank(pHead);
		break;
	case 7:
		choice = 9;
		break;

	}
}

int main()
{
	char pass[10], password[10] = "bankben";
	int i = 0;
	system("color 70");
main_pas:
	printf("\n\n\t\tEnter the password to login:");
	scanf("%s", pass);
	if (strcmp(pass, password) == 0)
	{
		printf("\n\nPassword Match!\nLOADING");
		for (i = 0; i <= 6; i++)
		{
			fordelay(100000000);
			printf(".");
		}
		system("cls");
		menu();
	}
	else
	{
		i++;
		system("cls");
		printf("\n\nWrong password try again!!\a\a\a");
		if (i == 3)
		{
			exit(0);
		}
	}
	goto main_pas;



	return 0;


}
