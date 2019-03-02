#pragma once

struct listSTR
{
	int index;
	char *name;
	float price;
	int count;
	int percent;
}; //���������� ������� �������� listSTR
extern int countOfGoods; //���������� ����������, ���������� ���������� ������� �� ������


void menu(listSTR *); //������� ����
listSTR* whatToDo(listSTR *); //�������� �� �������� ����

/*������� ������*/
void search(listSTR*);//������� ������ ���� ��� ������

void searchNames(listSTR*); //����� �� �������������
int* searchByName(listSTR *, char* name); //������� ��������� �������� ���� ������� � ����������� �������������
void searchThatName(listSTR *);
void searchByParts(listSTR *list);
bool IsStartWith(char *start, char *name); //�������� �� ����������� ������ �����

void searchPrice(listSTR*); //�� �����
void searchThatPrice(listSTR*);
int* searchByPrice(listSTR *, float price); //������� ��������� �������� ���� ������� � ����������� �����
void searchPriceMoreThen(listSTR *);
void searchPriceLessThen(listSTR *);

void searchCount(listSTR*);//�� ���-��
void searchThatCount(listSTR*);
int* searchByCount(listSTR *, int count); //������� ��������� �������� ���� ������� � ����������� �����������
void searchCountMoreThen(listSTR *);
void searchCountLessThen(listSTR *);

void searchPercent(listSTR*);//�� �������� ��������
void searchThatPercent(listSTR*);
void searchPercentMoreThen(listSTR *);
void searchPercentLessThen(listSTR *);

int* searchOnStruct(listSTR *, int whatToSearchType, void *WhatToLook); //������� ������ ���� ������

/*������� ��������������*/
void delElementOfStruct(listSTR* ,int position); //������� �������� ��������� �� ������� ���������
void structEdit(listSTR *); //������� �������������� ��������� 

/*������� ����������*/
void structSort(listSTR *); //������� ������ ���� ���������� ���������
void sortByNames(listSTR *); //���������� �� ������������� � ���������� �������
void sortByPrice(listSTR *,int start, int end); //���������� �� ����� �� �����������
void sortByCount(listSTR *, int start, int end);
void sortByPercent(listSTR *, int start, int end);

/*������� �����-������*/
listSTR* structInput(listSTR *); //������� ����� ��������� � ������ ��������
void structOutput(listSTR *); //������� ������ ���������
void StructOneOutput(listSTR *list, int index);//����� ����� ���������, ��������������� ������� index
listSTR *RandomGeneration(listSTR*);

/*��������������� �������*/
long double inputpositive();
char *stringInput();//������� ����� ������
long double anyinput();
void revers(char* string, int start, int end);
char* strCPY(char* buffer, char* source);
int fileLen(FILE *);

void wordToUpperCase(char*word);//������� ���������� ���� ���� � ����� � �������� ��������
void upperCaseOutput(char*word);//������� ������ ����� � ������� ����� �����������
int searchPosByIndex(listSTR *list, int index);
