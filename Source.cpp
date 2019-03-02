#include <stdio.h>
#include<Windows.h>
#include "Header.h"

int countOfGoods = 5;

/*Сделать поиск по частичному совпаднию центральной части*/

//СДелать поиск по частичному совпадению (П* - всё, что начинается с П *п* - начинается с чего угодно и чем угодно заканчивается, но содержит букву п - *п заканчивается на букву п)

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	listSTR *list;
	list = (listSTR*)malloc((countOfGoods + 1) * sizeof(listSTR));
	
	printf("Случайная генерация?(ENTER - да)\n");
	rewind(stdin);
	char arg = getchar();
	if (arg == '\n')
		list = RandomGeneration(list);
	else
		countOfGoods = 0;

	while (true)
	{
		system("CLS");
		menu(list);//Вывод меню действий
		list = whatToDo(list); 
	}
	system("pause");
}