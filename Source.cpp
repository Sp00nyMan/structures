#include <stdio.h>
#include<Windows.h>
#include "Header.h"

int countOfGoods = 5;

/*������� ����� �� ���������� ��������� ����������� �����*/

//������� ����� �� ���������� ���������� (�* - ��, ��� ���������� � � *�* - ���������� � ���� ������ � ��� ������ �������������, �� �������� ����� � - *� ������������� �� ����� �)

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	listSTR *list;
	list = (listSTR*)malloc((countOfGoods + 1) * sizeof(listSTR));
	
	printf("��������� ���������?(ENTER - ��)\n");
	rewind(stdin);
	char arg = getchar();
	if (arg == '\n')
		list = RandomGeneration(list);
	else
		countOfGoods = 0;

	while (true)
	{
		system("CLS");
		menu(list);//����� ���� ��������
		list = whatToDo(list); 
	}
	system("pause");
}