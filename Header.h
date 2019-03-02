#pragma once

struct listSTR
{
	int index;
	char *name;
	float price;
	int count;
	int percent;
}; //Обьявление массива структур listSTR
extern int countOfGoods; //Глобальная переменная, содержащая количество товаров на складе


void menu(listSTR *); //Главное меню
listSTR* whatToDo(listSTR *); //Действия из главного меню

/*Фенкции поиска*/
void search(listSTR*);//Функция выбора поля для поиска

void searchNames(listSTR*); //поиск по наименованиям
int* searchByName(listSTR *, char* name); //Функция получения индексов всех товаров с необходимым наименованием
void searchThatName(listSTR *);
void searchByParts(listSTR *list);
bool IsStartWith(char *start, char *name); //Проверка на определённое начало слова

void searchPrice(listSTR*); //по ценам
void searchThatPrice(listSTR*);
int* searchByPrice(listSTR *, float price); //Функция получения индексов всех товаров с необходимой ценой
void searchPriceMoreThen(listSTR *);
void searchPriceLessThen(listSTR *);

void searchCount(listSTR*);//по кол-ву
void searchThatCount(listSTR*);
int* searchByCount(listSTR *, int count); //Функция получения индексов всех товаров с необходимым количеством
void searchCountMoreThen(listSTR *);
void searchCountLessThen(listSTR *);

void searchPercent(listSTR*);//по проценту надбавки
void searchThatPercent(listSTR*);
void searchPercentMoreThen(listSTR *);
void searchPercentLessThen(listSTR *);

int* searchOnStruct(listSTR *, int whatToSearchType, void *WhatToLook); //Функция выбора типа поиска

/*Функции редактирования*/
void delElementOfStruct(listSTR* ,int position); //Функция удаления структуры из массива структура
void structEdit(listSTR *); //Функция редактирования структуры 

/*Функции сортировки*/
void structSort(listSTR *); //функция выбора типа сортировки структуры
void sortByNames(listSTR *); //Сортировка по наименованиям в алфавитном порядке
void sortByPrice(listSTR *,int start, int end); //Сортировка по ценам по возрвстанию
void sortByCount(listSTR *, int start, int end);
void sortByPercent(listSTR *, int start, int end);

/*Функции ввода-вывода*/
listSTR* structInput(listSTR *); //Функция ввода структуры в массив структур
void structOutput(listSTR *); //Функция вывода структуры
void StructOneOutput(listSTR *list, int index);//Вывод одной структуры, соответствующей индексу index
listSTR *RandomGeneration(listSTR*);

/*Вспомогательные функции*/
long double inputpositive();
char *stringInput();//Функция ввода строки
long double anyinput();
void revers(char* string, int start, int end);
char* strCPY(char* buffer, char* source);
int fileLen(FILE *);

void wordToUpperCase(char*word);//Функция возведения всех букв в слове к верхнему регистру
void upperCaseOutput(char*word);//Функция вывода слова с большой буквы посимвольно
int searchPosByIndex(listSTR *list, int index);
