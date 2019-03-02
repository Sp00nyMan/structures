#include <stdio.h>
#include <Windows.h>
#include "Header.h"

/*Основные функции*/
void menu(listSTR *list)
{
	structOutput(list);//Вывод массива структур
	printf("\n\n\n");
	printf("Выберите дальнейшую операцию над списком товаров:\n");
	printf("1. Добавить товары на склад\n");
	printf("2. Изменить данные\n");
	printf("3. Отсортировать список\n");
	printf("4. Поиск товара\n");
	printf("0. Выйти из программы\n");
}
listSTR* whatToDo(listSTR *list)
{
	int ENTER = anyinput();
	rewind(stdin);
	switch (ENTER)
	{
	case 1:
		list = structInput(list);
		break;
	case 2:
		structEdit(list);
		break;
	case 3:
		structSort(list);
		break;
	case 4:
		search(list);
		break;
	case 0:
		exit(1);
	default:
		system("CLS");
		printf("Нет такого действия\n");
		system("pause");
		break;
	}
	return list;
}

/*Функции поиска*/
void search(listSTR *list)
{
	system("CLS");
	printf("Выберите критерии поиска:\n");
	printf("Найти все товары, *ВЫБЕРИТЕ* которых:\n");
	printf("1. Наименование\n");
	printf("2. Цена\n");
	printf("3. Количество\n");
	printf("4. Процент надбавки\n");
	int arg = anyinput();
	switch (arg)
	{
	case 1:
		searchNames(list);
		break;
	case 2:
		searchPrice(list);
		break;
	case 3:
		searchCount(list);
		break;
	case 4:
		searchPercent(list);
		break;
	default:
		printf("Такого варианта нет\n");
		search(list);
		return;
	}
}

void searchNames(listSTR*list)
{
	system("CLS");
	printf("Найти все товары, *Наименование* которых *ВЫБЕРИТЕ* :\n");
	printf("1. Полностью совпадает с\n");
	printf("2. Частично совпадает с\n");
	//printf("3. Содержит\n");
	//printf("4. Заканчивается на\n");
	int arg = anyinput();
	switch (arg)
	{
		case 1:
			searchThatName(list);
			break;
		case 2:
			searchByParts(list);
			break;
		default:
			printf("Выбрана неверная операция\n");
			system("pause");
			searchNames(list);
			break;
	}
}
int* searchByName(listSTR *list, char *name)
{
	int *goods;
	int* buf;
	while (!(goods = (int *)malloc(2 * sizeof(int))))
		free(goods);
	goods[0] = 0;
	bool flag = false;
	for (int i = 0; i < countOfGoods; i++)
		if (!strcmp(list[i].name, name))
		{
			flag = true;
			goods[goods[0] + 1] = list[i].index;
			goods[0]++;

			buf = (int*)realloc(goods, (goods[0] + 2) * sizeof(int));
			if (!buf)
				return NULL;
			goods = buf;
		}
	if (flag)
		return goods;
	else
	{
		free(goods);
		return NULL;
	}
}
void searchThatName(listSTR *list)
{
	system("CLS");
	printf("Найти все товары, Наименование которых Полностью совпадает с *ВВЕДИТЕ*\n");
	char* name = stringInput();
	wordToUpperCase(name);
	system("CLS");
	int *goods = searchByName(list, name);
	if (!goods)
	{
		printf("Нет товаров, Наименование которых Полностью совпадает с ");
		upperCaseOutput(name);
		printf("\n");
		system("pause");
		return;
	}
	printf("Все товары, Наименование которых Полностью совпадает с ");
	upperCaseOutput(name);
	printf(":\n");
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 1; i <= goods[0]; i++)
		StructOneOutput(list, goods[i]);
	system("pause");
	free(goods);
	free(name);
}
void searchByParts(listSTR *list)
{
	printf("Введите параметры для частичного поиска\n('я*TAB*' - товары начинающиеся на 'я'; 'я*ТАВ*о' - товары, начинающиеся на 'я' и заканчивающиеся на 'о')\n");
	char *parametrs = stringInput();
	char *start = NULL;
	bool IsStart;
	if (parametrs[0] != '\t')
	{
		int startSize = 1;
		start = (char*)calloc(startSize, sizeof(char));
		while (parametrs[startSize - 1] != '\t')
		{
			start[startSize - 1] = parametrs[startSize - 1];
			start = (char*)realloc(start, ++startSize);
			start[startSize - 1] = '\0';
		}
	}
	char *end = NULL;
	if (parametrs[strlen(parametrs) - 1] != '\t')
	{
		int endSize = 1;
		int parametrSize = strlen(parametrs) - 1;
		end = (char*)calloc(endSize, sizeof(char));

		while (parametrs[parametrSize] != '\t' && parametrSize != 0)
		{
			end[endSize - 1] = parametrs[parametrSize--];
			end = (char*)realloc(end, ++endSize);
			end[endSize - 1] = '\0';
		}
		revers(end, 0, endSize - 2);
	}
	bool IsEnd;
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < countOfGoods; i++)
	{
		if (parametrs[0] != '\t')
			IsStart = IsStartWith(start, list[i].name);
		else
			IsStart = true;
		if (parametrs[strlen(parametrs) - 1] != '\t')
		{
			char *temp = (char*)calloc(sizeof(list[i].name),sizeof(char));
			temp = strCPY(temp,list[i].name);
			revers(temp, 0, strlen(temp) - 1);
			IsEnd = IsStartWith(end, temp);
		}
		else 
			IsEnd = true;
		if (IsStart && IsEnd)
			StructOneOutput(list, list[i].index);
	}
	system("pause");
}

bool IsStartWith(char *start, char *name)
{
	wordToUpperCase(start);
	int sizeOfStart = strlen(start);
	bool flag = false;
	for (int j = 0; j < sizeOfStart && j < strlen(name); j++)
		if (name[j] == start[j])
				flag = true;
			else
			{
				flag = false;
				break;
			}
	if (flag)
		return true;
	else
		return false;
}

void searchPrice(listSTR*list)
{
	system("CLS");
	printf("Найти все товары, *Цена* которых *ВЫБЕРИТЕ*:\n");
	printf("1. Полностью совпадает с\n");//
	printf("2. Больше, чем\n");//
	printf("3. Меньше, чем\n");//
	int arg = anyinput();
	switch (arg)
	{
	case 1:
		searchThatPrice(list);
		break;
	case 2:
		searchPriceMoreThen(list);
		break;
	case 3:
		searchPriceLessThen(list);
		break;
	default:
		printf("Нет такого варианта ответа\n");
		system("pause");
		searchPrice(list);
		break;
	}
}
int* searchByPrice(listSTR *list, float price)
{
	int *goods;
	int* buf;
	while (!(goods = (int *)malloc(2 * sizeof(int))))
		free(goods);
	goods[0] = 0;
	bool flag = false;
	for (int i = 0; i < countOfGoods; i++)
		if (list[i].price == price)
		{
			flag = true;
			goods[goods[0] + 1] = list[i].index;
			goods[0]++;
			buf = (int*)realloc(goods, (goods[0] + 2) * sizeof(int));
			if (!buf)
				return NULL;
			//free(goods);
			goods = buf;
		}
	if (flag)
		return goods;
	else
	{
		free(goods);
		return NULL;
	}
}
void searchThatPrice(listSTR* list)
{
	system("CLS");
	printf("Найти все товары, Цена которых Полностью совпадает с *ВВЕДИТЕ*\n");
	float price = inputpositive();
	system("CLS");
	int *goods = searchByPrice(list, price);
	if (!goods)
	{
		printf("Нет товаров, Цена которых Полностью совпадает с %.2f\n", price);
		system("pause");
		return;
	}
	printf("Все товары, Цена которых Полностью совпадает с %.2f:\n", price);
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 1; i <= goods[0]; i++)
		StructOneOutput(list, goods[i]);
	system("pause");
	free(goods);
}
void searchPriceMoreThen(listSTR *list)
{
	system("CLS");
	printf("Найти все товары, Цена которых Больше, чем *ВВЕДИТЕ*\n");
	float price = inputpositive();
	system("CLS");
	printf("Все товары, Цена которых Больше, чем %.2f:\n", price);
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < countOfGoods; i++)
		if (list[i].price > price)
			StructOneOutput(list, list[i].index);
	system("pause");
}
void searchPriceLessThen(listSTR *list)
{
	system("CLS");
	printf("Найти все товары, Цена которых Меньше, чем *ВВЕДИТЕ*\n");
	float price = inputpositive();
	system("CLS");
	printf("Все товары, Цена которых Меньше, чем %.2f:\n", price);
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < countOfGoods; i++)
		if (list[i].price < price)
			StructOneOutput(list, list[i].index);
	system("pause");
}

void searchCount(listSTR*list)
{
	system("CLS");
	printf("Найти все товары, *Количество* которых *ВЫБЕРИТЕ*:\n");
	printf("1. Полностью совпадает с\n");//
	printf("2. Больше, чем\n");//
	printf("3. Меньше, чем\n");//
	int arg = anyinput();
	switch (arg)
	{
	case 1:
		searchThatCount(list);
		break;
	case 2:
		searchCountMoreThen(list);
		break;
	case 3:
		searchCountLessThen(list);
		break;
	default:
		printf("Нет такого варианта ответа\n");
		system("pause");
		searchCount(list);
		break;
	}
}
int* searchByCount(listSTR *list, int count)
{
	int *goods;
	int* buf;
	while (!(goods = (int *)malloc(2 * sizeof(int))))
		free(goods);
	goods[0] = 0;
	bool flag = false;
	for (int i = 0; i < countOfGoods; i++)
		if (list[i].count == count)
		{
			flag = true;
			goods[goods[0] + 1] = list[i].index;
			goods[0]++;

			buf = (int*)realloc(goods, (goods[0] + 2) * sizeof(int));
			if (!buf)
				return NULL;
			//free(goods);
			goods = buf;
		}
	if (flag)
		return goods;
	else
	{
		free(goods);
		return NULL;
	}
}

void searchThatCount(listSTR *list)
{
	system("CLS");
	printf("Найти все товары, Количество которых Полностью совпадает с *ВВЕДИТЕ*\n");
	int count = inputpositive();
	system("CLS");
	int *goods = searchByCount(list, count);
	if (!goods)
	{
		printf("Нет товаров, Количество которых Полностью совпадает с %d\n", count);
		system("pause");
		return;
	}
	printf("Все товары, Количество которых Полностью совпадает с %d:\n", count);
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 1; i <= goods[0]; i++)
		StructOneOutput(list, goods[i]);
	system("pause");
	free(goods);
}
void searchCountMoreThen(listSTR *list)
{
	system("CLS");
	printf("Найти все товары, Количество которых Больше, чем *ВВЕДИТЕ*\n");
	int count = inputpositive();
	system("CLS");
	printf("Все товары, Количество которых Больше, чем %d:\n", count);
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < countOfGoods; i++)
		if (list[i].count > count)
			StructOneOutput(list, list[i].index);
	system("pause");
}
void searchCountLessThen(listSTR *list)
{
	system("CLS");
	printf("Найти все товары, Количество которых Меньше, чем *ВВЕДИТЕ*\n");
	int count = inputpositive();
	system("CLS");
	printf("Все товары, Количество которых Меньше, чем %d:\n", count);
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < countOfGoods; i++)
		if (list[i].count < count)
			StructOneOutput(list, list[i].index);
	system("pause");
}

void searchPercent(listSTR*list)
{
	printf("Найти все товары, *Процент надбавки* которых *ВЫБЕРИТЕ*:\n");
	printf("1. Полностью совпадает с\n");
	printf("2. Больше, чем\n");
	printf("3. Меньше, чем\n");
	int arg = anyinput();

	switch (arg)
	{
	case 1:
		searchThatPercent(list);
		break;
	case 2:
		searchPercentMoreThen(list);
		break;
	case 3:
		searchPercentLessThen(list);
		break;
	default:
		printf("Нет такого варианта ответа\n");
		system("pause");
		searchPercent(list);
		break;
	}
}
void searchThatPercent(listSTR *list)
{
	system("CLS");
	printf("Найти все товары, Процент надбавки которых Полностью совпадает с *ВВЕДИТЕ*\n");
	int percent = inputpositive();
	system("CLS");
	printf("Все товары, Процент надбавки которых Полностью совпадает с %d:\n", percent);
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < countOfGoods; i++)
		if (list[i].percent == percent)
			StructOneOutput(list, list[i].index);
	system("pause");
}
void searchPercentMoreThen(listSTR *list)
{
	system("CLS");
	printf("Найти все товары, Процент надбавки которых Больше, чем *ВВЕДИТЕ*\n");
	int percent = inputpositive();
	system("CLS");
	printf("Все товары, Количество которых Больше, чем %d:\n", percent);
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < countOfGoods; i++)
		if (list[i].percent > percent)
			StructOneOutput(list, list[i].index);
	system("pause");
}
void searchPercentLessThen(listSTR *list)
{
	system("CLS");
	printf("Найти все товары, Процент надбавки которых Меньше, чем *ВВЕДИТЕ*\n");
	int percent = inputpositive();
	system("CLS");
	printf("Все товары, Процент надбавки которых Меньше, чем %d:\n", percent);
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < countOfGoods; i++)
		if (list[i].percent < percent)
			StructOneOutput(list, list[i].index);
	system("pause");
}

int* searchOnStruct(listSTR *list, int arg, void *whatToLook)
{
	switch (arg)
	{
	case 0:
		return searchByName(list, (char*)whatToLook);
	case 1:
		return searchByPrice(list, *((float*)whatToLook));
	case 2:
		return searchByCount(list, *((int*)whatToLook));
	}
	return nullptr;
}

/*Функции редактирования*/
void delElementOfStruct(listSTR *list, int position)
{
	listSTR temp;

	for (int i = position; i < countOfGoods; i++)
	{
		temp = list[i];
		list[i] = list[i + 1];
		list[i + 1] = temp;
	}
	countOfGoods--;
	listSTR *buf;
	buf = (listSTR*)realloc(list, (countOfGoods + 1) * sizeof(listSTR));
	if (!buf)
		return;
	//free(list);
	list = buf;
}
void structEdit(listSTR *list)
{
	char *name;
	int* goods;
	do {
		printf("Введите название товара, который хотите изменить:\n");
		name = stringInput(); //Ввод названия
		wordToUpperCase(name);
		system("CLS");
		structOutput(list);
		goods = searchOnStruct(list, 0, name); //Поиск структур, содержащих введённое наименование в массиве структур
		system("CLS");
		if (goods == NULL)
			printf("На складе нет товаров с таким названием\n");
		else
			break;
	} while (true);
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------");
	for (int i = 0; i < goods[0]; i++)
		StructOneOutput(list, goods[i + 1]);

	int num;
	if (goods[0] > 1)
	{
		printf("Введите порядковый номер товара, который хотите изменить:\n");
		num = anyinput();
	}
	else
		num = 1;
	system("CLS");

	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------");
	StructOneOutput(list, goods[num]);
	printf("Выберите параметр для изменения\n");
	printf("1. Наименование\n");
	printf("2. Цена\n");
	printf("3. Количество\n");
	printf("4. Процент торговой надбавки\n");
	printf("5. Удалить элемент из структуры\n");//СДЕЛАТЬ
	printf("0. Отмена\n");
	int arg = anyinput();
	system("CLS");

	StructOneOutput(list, goods[num]);
	int pos = searchPosByIndex(list, goods[num]);

	switch (arg)
	{
	case 1:
		list[pos].name = stringInput();
		wordToUpperCase(list[pos].name);
		break;
	case 2:
		list[pos].price = inputpositive();
		break;
	case 3:
		list[pos].count = inputpositive();
		break;
	case 4:
		list[pos].percent = inputpositive();
		break;
	case 5:
		delElementOfStruct(list, pos);
		break;
	case 0:
		return;
	default:
		printf("Выбрана неверная операция\n");
		system("pause");
		return;
	}
}

/*Функции сортировки*/
void structSort(listSTR *list)
{
	system("CLS");
	printf("Выберите параметр для сортировки:\n");
	printf("1. Наименование\n");
	printf("2. Цена\n");
	printf("3. Количество\n");
	printf("4. Процент надбавки\n");
	int whatToSort = anyinput();
	switch (whatToSort)
	{
	case 1:
		sortByNames(list);
		break;
	case 2:
		sortByPrice(list, 0, countOfGoods - 1);
		break;
	case 3:
		sortByCount(list, 0, countOfGoods);
		break;
	case 4:
		sortByPercent(list, 0, countOfGoods);
		break;
	default:
		printf("Такого варианта ответа нет\n");
		system("pause");
		structSort(list);
		break;
	}
}
void sortByNames(listSTR *list)
{
	for (int i = 0; i < countOfGoods / 2; i++)
		for (int j = 0; j < countOfGoods - 1; j++)
			if (strcmp(list[j].name, list[j + 1].name) > 0)
			{
				listSTR temp;
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
}
void sortByPrice(listSTR *list, int start, int end)
{
	int s = start, e = end;
	float pivot = list[(e + s) / 2].price;
	while (s <= e)
	{
		for (; list[s].price < pivot; s++);
		for (; list[e].price > pivot; e--);

		if (s < e)
		{
			listSTR temp;
			temp = list[e];
			list[e] = list[s];
			list[s] = temp;
		}
		s++;
		e--;
	}
	if (start < e)
		sortByPrice(list, start, e);
	if (s < end)
		sortByPrice(list, s, end);
}
void sortByCount(listSTR *list, int start, int end)
{
	int s = start, e = end;
	int pivot = list[(e + s) / 2].count;
	while (s <= e)
	{
		for (; list[s].count < pivot; s++);
		for (; list[e].count > pivot; e--);

		if (s < e)
		{
			listSTR temp;
			temp = list[e];
			list[e] = list[s];
			list[s] = temp;
		}
		s++;
		e--;
	}
	if (start < e)
		sortByCount(list, start, e);
	if (s < end)
		sortByCount(list, s, end);
}
void sortByPercent(listSTR *list, int start, int end)
{
	int s = start, e = end;
	int pivot = list[(e + s) / 2].percent;
	while (s <= e)
	{
		for (; list[s].percent < pivot; s++);
		for (; list[e].percent > pivot; e--);

		if (s < e)
		{
			listSTR temp;
			temp = list[e];
			list[e] = list[s];
			list[s] = temp;
		}
		s++;
		e--;
	}
	if (start < e)
		sortByPercent(list, start, e);
	if (s < end)
		sortByPercent(list, s, end);
}

/*Функции ввода-вывода*/
listSTR *RandomGeneration(listSTR *list)
{
	printf("Случайная генерация?(yN)\n");
	rewind(stdin);
	char arg = getchar();
	if (arg == 'y')
	else
		countOfGoods = 0;
	FILE *goods;
	fopen_s(&goods, "Наименования.txt", "r");

	int countOfNamesInFile = fileLen(goods); //Функция поиска количества строк в файле
	char **names;

	bool *flags = (bool *)malloc(countOfNamesInFile * sizeof(bool)); //Массив для избежания повторений
	for (int i = 0; i < countOfNamesInFile; i++)
		flags[i] = true;

	names = (char**)malloc(countOfNamesInFile * sizeof(char*)); //Подгрузка всех наименований из файла в массив строк
	for (int i = 0; i < countOfNamesInFile; i++)
	{
		*(names + i) = (char*)calloc(20, sizeof(char));
		*(names + i) = fgets(*(names + i), 20, goods);
		names[i][strlen(names[i]) - 1] = '\0'; //Убираем \n из строк
	}

	for (int i = 0; i < countOfGoods; i++)
	{
		list[i].index = i;
		int num;
		num = rand() % (countOfNamesInFile - 1);
		if (flags[num])
		{
			flags[num] = false;
			list[i].name = *(names + num);
		}
		else
		{
			i--;
			continue;
		}
		wordToUpperCase(list[i].name); //Приводим слово к верхнему регистру

		do
		{
			list[i].price = rand() % 100;
			list[i].price /= 100;
			list[i].price += rand() % 200;
		} while (list[i].price == 0);

		do
			list[i].count = rand() % 100;
		while (list[i].count == 0);

		do
			list[i].percent = rand() % 30;
		while (list[i].percent < 5);

	}
	rewind(goods);
	fclose(goods);
	return list;
}
listSTR* structInput(listSTR *list)
{
	while (true)
	{
		list[countOfGoods].index = countOfGoods;
		system("CLS");
		structOutput(list);
		printf("Введите наименование товара\n");
		list[countOfGoods].name = stringInput();
		wordToUpperCase(list[countOfGoods].name);
		system("CLS");

		structOutput(list);
		upperCaseOutput(list[countOfGoods].name);
		printf("\n\n");
		printf("Введите цену товара\n");
		list[countOfGoods].price = inputpositive();
		system("CLS");

		structOutput(list);
		upperCaseOutput(list[countOfGoods].name);
		printf("\t\t\t\t\t");
		if (strlen(list[countOfGoods].name) <= 7)
			printf("\t");
		printf("%.2f\n\n", list[countOfGoods].price);
		printf("Введите количество единиц товара\n");
		list[countOfGoods].count = inputpositive();
		system("CLS");

		structOutput(list);
		upperCaseOutput(list[countOfGoods].name);
		printf("\t\t\t\t\t");
		if (strlen(list[countOfGoods].name) <= 7)
			printf("\t");
		printf("%.2f", list[countOfGoods].price);
		printf("\t\t\t");
		printf("%d\n\n", list[countOfGoods].count);
		printf("Введите величину торговой надбавки (в %c)\n", '%');
		list[countOfGoods].percent = inputpositive();
		system("CLS");
		countOfGoods++;

		structOutput(list);
		printf("Для того, чтобы ввести ещё товар нажмите ENTER\n");
		rewind(stdin);
		listSTR *buf;
		buf = (listSTR*)realloc(list, (countOfGoods + 1) * sizeof(listSTR));
		if (!buf)
			return list;
		//free(list);
		list = buf;
		if (getchar() != '\n')
			break;
	}
	system("CLS");
	return list;
}
void structOutput(listSTR *list)
{
	printf("Список товаров на складе:\n\n");
	printf("НАИМЕНОВАНИЕ\t\t\t\t\tЦЕНА\t\t\tКОЛИЧЕСТВО\t\t\tНАДБАВКА\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < countOfGoods; i++)
	{
		upperCaseOutput(list[i].name);
		printf("\t\t\t\t\t");
		if (strlen(list[i].name) < 7)
			printf("\t");
		printf("%.2f", list[i].price);
		printf("\t\t\t");
		printf("%d", list[i].count);
		printf("\t\t\t\t");
		printf("%d", list[i].percent);
		printf("\n");
		printf("------------------------------------------------------------------------------------------------------------------");
		printf("\n");
	}
}
void StructOneOutput(listSTR *list, int index)
{
	int i = searchPosByIndex(list, index);
	upperCaseOutput(list[i].name);
	printf("\t\t\t\t\t");
	if (strlen(list[i].name) <= 7)
		printf("\t");
	printf("%.2f", list[i].price);
	printf("\t\t\t");
	printf("%d", list[i].count);
	printf("\t\t\t\t");
	printf("%d", list[i].percent);
	printf("\n");
	printf("------------------------------------------------------------------------------------------------------------------");
	printf("\n");
}

/*Вспомогательные функции*/
void wordToUpperCase(char* word)
{
	if (!word)
	{
		printf("Ошибка чтения памяти\n");
		system("pause");
		return;
	}
	int size = strlen(word);
	for (int i = 0; i < size; i++)
		if (word[i] <= 'z' && word[i] >= 'a')
			word[i] += 'A' - 'a';
		else
			if (word[i] <= 'я' && word[i] >= 'а')
				word[i] += 'А' - 'а';
}
void upperCaseOutput(char* word)
{
	int wordSize = 0;
	//puts(word);
	//system("pause");
	if (word != NULL)
		wordSize = strlen(word);
	else
		return;
	printf("%c", word[0]);
	if(word[0] >='A' && word[0] <='Z')
		for (int i = 1; i <= wordSize; i++)
			printf("%c", word[i] - 'A' + 'a');
	else
		if (word[0] >= 'А' && word[0] <= 'Я')
			for (int i = 1; i <= wordSize; i++)
				printf("%c", word[i] - 'А' + 'а');
}
int searchPosByIndex(listSTR *list,int index)
{
	for (int i = 0; i < countOfGoods; i++)
		if (list[i].index == index)
			return i;
	return -1;
}
long double anyinput()
{
	long double a;
	bool isEntered = false;
	while (!isEntered)
	{
		rewind(stdin);
		isEntered = scanf_s("%Lf", &a);
	}
	return a;
}
long double inputpositive()
{
	long double a;
	while (true)
	{
		a = anyinput();
		if (a < 0)
		{
			printf("Значение не может быть отрицательным, введите другое\n");
			continue;
		}
		else break;
	}

	return a;
}
char *stringInput()
{
	char *string;
	char* buf;
	int size = 1;
	int symbol;
	string = (char*)calloc(size, sizeof(char));
	if (!string)
		return nullptr;
	rewind(stdin);
	while ((symbol = getchar()) != '\n')
	{
		string[size - 1] = symbol;		
		size++;
		buf = (char*)realloc(string, size);
		if (!buf)
			return NULL;
		//free(string);
		string = buf;
		string[size - 1] = '\0';
	}
	return string;
}
void revers(char* string, int start, int end)
{
	int i = start;
	int j = end;
	int temp;
	for (; j >= i; j--, i++)
	{
		temp = *(string + i);
		*(string + i) = *(string + j);
		*(string + j) = temp;
	}
}
char* strCPY(char* buffer, char* source)
{
	buffer = (char*)calloc(strlen(source) + 1, sizeof(char));
	int i = 0;
	while (source[i - 1] != '\0')
		buffer[i] = source[i++];
	return buffer;
}
int fileLen(FILE *file)
{

	int i = 0;
	char* buffer = (char*)calloc(30, sizeof(char));
	do
	{
		fgets(buffer, 30, file);
		if (buffer)
			i++;
	} while (!feof(file));
	rewind(file);
	return i;
}