
#include "stdafx.h"//подключение библиотек
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include <windows.h>

using namespace std;
using namespace System;
using namespace System::IO;

#define ENTER 13// обозначение кнопок
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79

int menu(int);//указание шаблонов используемых функций
void progulshik(struct z*);
void dolznik(struct z*);
void matanaliz(struct z*);
void alfalist(struct z*);
void vstavka(struct z*, char*);
void diagram(struct z*);
void pohozhie(struct z*);


struct z {//шаблон структуры для исходных данных
char name[14];//ФИО студента
char inst[6];//институт
char predmet[11];//предмет
int dolgi;//кол-во долгов
int propuski;//кол-во пропусков
char data[11];//дата пересдачи
};
struct sp{//шаблон, глобальное описание структуры двустроннего списка 
 char name[14];
 int propuski;
 struct sp* sled;
 struct sp* pred;
} *spisok;
int main(array<System::String ^> ^args)
{
int i,n;
int NC;
char dan[7][74]={
	"Какой студент имеет больше пропусков?                                    ",
	"У какого студента определённое количество долгов?                        ",
	"Сколько студентов пересдаёт введённый прдмет?                            ",
	"Есть ли студенты с разных институтов и одинаковым количеством пропусков? ",
	"Алфавитный список студентов                                              ",
	"Диаграмма: соотношение пропусков занятий                                 ",
	"Выход                                                                    "
};//задание списка вопросов - пунктов меню
char BlankLine[ ]="                                                                           ";
FILE* file = fopen("spisok.dat","r");
struct z *students;
 setlocale(LC_CTYPE,"Russian");//поддержка русского языка
 Console::CursorVisible::set(false);//отключаем выдимость курсора
 Console::BufferHeight=Console::WindowHeight;//установка размера буфера по высоте
 Console::BufferWidth=Console::WindowWidth;//установка размера буфера по ширине
 if((file=fopen("spisok.dat","r"))==NULL)//попытка открыть файл
	 {
	 printf("\nФайл spisok.dat не открыт !");//при неудачном открытии выводим соообщение “Файл не открыт!”
	 getch(); exit(1);
	 }
fscanf(file,"%d",&NC);
students=(struct z*)malloc(NC*sizeof(struct z));//выделяем память

for(i=0;i<NC;i++)//считываем данные из списка
	fscanf(file,"%s%s%s%d%d%s",students[i].name,
	students[i].inst, students[i].predmet, &students[i].dolgi,&students[i].propuski,
	students[i].data);

for(i=0;i<NC;i++)//выводим данные из списка на экран
	printf("\n\t%-20s %-10s %-10s %5d %8d %-7s",
	students[i].name,
	students[i].inst, students[i].predmet, students[i].dolgi,students[i].propuski,
	students[i].data);
getch();
while(1)//в цикле создаем область для вопросов и окрашиваем еѐ в цвета
	{
	Console::ForegroundColor=ConsoleColor::Gray;//устанавливаем для букв цвет и подсветку для выбранного вопроса
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();
	Console::ForegroundColor=ConsoleColor::DarkCyan;
	Console::BackgroundColor=ConsoleColor::White;
	Console::CursorLeft=10; //первая точка, откуда будем закрашивать область меню
	Console::CursorTop=4;
	printf(BlankLine);
	for(i=0;i<7;i++) //размещение вопросов
		{
		Console::CursorLeft=10;
		Console::CursorTop=i+5;
		printf(" %s ",dan[i]);
		}
	Console::CursorLeft=10;//последняя точка,где будет заканчиваться выделенная область под меню
	Console::CursorTop=12;
	printf(BlankLine);
	n=menu(7);//выбор вопроса в меню
	switch(n) {
		case 1: progulshik(students); break;
		case 2: dolznik(students); break;
		case 3: matanaliz(students); break;
		case 4: pohozhie(students); break;
		case 5: alfalist(students); break;
		case 6: diagram(students); break;
		case 7: exit(0);
	}
	} // конец while(1)
	return 0;
	} // конец main()
int menu(int n)//n=7
{
	char dan[7][74]={
		"Какой студент имеет больше пропусков?                                    ",
		"У какого студента определённое количество долгов?                        ",
		"Сколько студентов пересдаёт введённый прдмет?                            ",
		"Есть ли студенты с разных институтов и одинаковым количеством пропусков? ",
		"Алфавитный список студентов                                              ",
		"Диаграмма: соотношение пропусков занятий                                 ",
		"Выход                                                                    "
	};
	int y1=3,y2=n-1;//устанавливаем выделение для строчки
	char c=1;
	while (c!=ESC)//при нажатии кнопки ESC, меню закроется
	{
	switch(c) {
	case DOWN: y2=y1; y1++; break;//программирование кнопки DOWN,которая позволяет перемещаться вниз по меню
	case UP: y2=y1; y1--; break;//программирование кнопки UP,которая позволяет перемещаться вверх по меню
	case HOME: y2 = y1; y1 = 0; break;//программирование кнопки HOME,которая позволяет выбрать первый вопрос
    case END: y2 = y1, y1 = n-1; break;//программирование кнопки END,которая позволяет перемещаться выбрать последний вопрос
	case ENTER: return y1+1;//программирование кнопки ENTER,которая позволяет выбрать вопрос
	}
	if(y1>n-1)//условие,когда срабатывает кнопка DOWN
		{y2=n-1;y1=0;}
	if(y1<0)//условие,когда срабатывает кнопка UP
		{y2=0;y1=n-1;}
	Console::ForegroundColor=ConsoleColor::DarkMagenta;//привыборе вопроса, буквы окрашиваются в фиолетовый цвет
	Console::BackgroundColor=ConsoleColor::DarkGreen; //привыборе вопроса, план за буквами подсвечивается зелёным
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::DarkCyan;
	Console::BackgroundColor=ConsoleColor::White;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch();
	}// конец while(c!=ESC)
	exit(0);
}
void progulshik(struct z* students)//функция для поиска студента с наибольшим количеством пропусков
{
	int NC;
	FILE* file = fopen("spisok.dat","r");
	if((file=fopen("spisok.dat","r"))==NULL)
	{
		printf("\nФайл spisok.dat не открыт !");
		getch(); exit(1);
	}
	fscanf(file,"%d",&NC);
	int i=0; struct z ploho;
	strcpy(ploho.name,students[0].name);//в переменную структуры записываем нулевой элемент
	ploho.propuski=students[0].propuski;
	for(i=1;i<NC;i++)
		if (students[i].propuski>ploho.propuski)//условие поиска максимального количества пропусков
		{
			strcpy(ploho.name,students[i].name);
			ploho.propuski=students[i].propuski;
		}
	Console::ForegroundColor=ConsoleColor::DarkCyan;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::CursorLeft=10;//задаем область, где будет выведено макс.количество пропусков
	Console::CursorTop=15;
	printf("Максимальное количество пропусков %d ",ploho.propuski);// Вывод максимального количества пропусков
	printf("имеет студент %s",ploho.name);//Вывод фамилии
	getch();
	}
void matanaliz(struct z* students)//функция для подсчёта студентов по введенному предмету
{
	int NC;
	FILE* file = fopen("spisok.dat","r");
	if((file=fopen("spisok.dat","r"))==NULL)
	{
		printf("\nФайл spisok.dat не открыт !");
		getch(); exit(1);
	}
	fscanf(file,"%d",&NC);
	int i, k=0;
	char s[80];
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::ForegroundColor=ConsoleColor::White;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	Console::CursorVisible::set(true);//включаем курсор
	printf("Введите предмет:   ");
	Console::CursorLeft=10;
	Console::CursorTop=16;
	SetConsoleCP(1251);//для считывания русских символов
	gets(s);//вписываем нужный текст
	SetConsoleCP(866);//кодировка консоли, чтобы могли выводить русские символы
	for( i=0;i<NC;i++){
		if (strcmp(students[i].predmet, s)==0){
			k++;}}
	Console::CursorLeft=10;
	Console::CursorTop=17;
	printf("Предмет %s пересдаёт %d человек",s,k);
	getch();
}
void dolznik(struct z* students)//список студентов со введённым количеством долгов
{
	int NC;
	FILE* file = fopen("spisok.dat","r");
	if((file=fopen("spisok.dat","r"))==NULL)
	{
		printf("\nФайл spisok.dat не открыт !");
		getch(); exit(1);
	}
	fscanf(file,"%d",&NC);
	int i,k, flag=0;
	Console::ForegroundColor=ConsoleColor::Red;
	Console::BackgroundColor=ConsoleColor::White;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	Console::CursorVisible::set(true);
	printf("Введите количество долгов:   ");
	Console::CursorLeft=10;
	Console::CursorTop=16;
	scanf("%d",&k);
	if(k<10){
		Console::CursorLeft=11;
		Console::CursorTop=16;
		printf("                               ");}
	else{
		Console::CursorLeft=12;
		Console::CursorTop=16;
		printf("                              ");}
	Console::CursorLeft=10;
	Console::CursorTop=17;
	for(i=0;i<NC;i++){
		if (students[i].dolgi==k){
			Console::CursorLeft=10;
			printf("%-20s| %-10s",students[i].name,students[i].inst);
			flag=1;
			Console::CursorTop+=1;
			Console::CursorVisible::set(false);
		}
	}
	if(flag==0)//выводим уведомление, если нет студентов с таким количеством долгов
		printf("Нет студента с таким количеством пропусков!");
	getch();
}
void pohozhie(struct z* students)//студенты с разных институтов и одинаковым количеством пропусков
{
	int NC;
	FILE* file = fopen("spisok.dat","r");
	if((file=fopen("spisok.dat","r"))==NULL)
	{
		printf("\nФайл spisok.dat не открыт !");
		getch(); exit(1);
	}
	fscanf(file,"%d",&NC);
	int i,k,flag=0;
	for(i=0;i<NC;i++){
		for(k=1;k<NC;k++){
			if ((students[i].propuski==students[k].propuski) && (strcmp(students[i].inst,students[k].inst)!=0)){
				//условие для нахождения студентов с разных институтов и одинаковым количеством пропусков
				Console::BackgroundColor=ConsoleColor::White;
				Console::ForegroundColor=ConsoleColor::DarkGreen;
				Console::CursorLeft=10;
				Console::CursorTop=15;
				printf("Студенты %s и %s имеют одинаковое количество пропущенных часов: %ld ",students[i].name,
				students[k].name,students[k].propuski);
				Console::CursorLeft=10;
				Console::CursorTop=16;
				printf("и учатся в разных институтах: %s и %s",students[i].inst,students[k].inst);
				flag=1;
				break;
			}
		}
		if(flag==1)
			break;
	}
	if(flag!=1){//Выводим уведомление, если совпадений не обнаружено
		Console::BackgroundColor=ConsoleColor::Blue;
		Console::ForegroundColor=ConsoleColor::Gray;
		Console::CursorLeft=10;
		Console::CursorTop=15;
		printf("Совпадений нет!");
	}
	getch();
}
void alfalist(struct z* students)//формирование алфавитного списка
{
	int NC;
	FILE* file = fopen("spisok.dat","r");
	if((file=fopen("spisok.dat","r"))==NULL)
	{
		printf("\nФайл spisok.dat не открыт !");
		getch(); exit(1);
	}
	fscanf(file,"%d",&NC);
	int i,x;
	struct sp* nt,*z;
	x = 3;
	Console::ForegroundColor = ConsoleColor::DarkGreen;
	Console::BackgroundColor = ConsoleColor::Gray;
	Console::Clear();
	printf("\n Алфавитный список покупателей");
	printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	if (!spisok)
	for (i = 0; i < NC; i++)
	vstavka(students, students[i].name);
	for (nt = spisok; nt != 0; nt = nt->sled)
	{
	Console::CursorLeft = 0;
	Console::CursorTop = x + 1;
	printf(" %-20s %d", nt->name, nt->propuski);//вывод прямого списка
	x += 1;
	}
	x = 3;
	Console::CursorLeft = 40;
	Console::CursorTop = 1;
	printf("Обратный алфавитный список");
	for (nt = spisok; nt != 0; z = nt, nt = nt->sled);
	for (nt = z, i = 0; nt != 0; i++, nt = nt->pred)
	{
	Console::CursorLeft = 40;
	Console::CursorTop = x + 1;
	printf(" %-20s %d", nt->name, nt->propuski);//вывод обратного списка
	x += 1;
	}
	getch();
}
void vstavka(struct z* students, char* name)//вставка в алфавитный список
{
	int NC;
	FILE* file = fopen("spisok.dat","r");
	if((file=fopen("spisok.dat","r"))==NULL)
	{
		printf("\nФайл spisok.dat не открыт !");
		getch(); exit(1);
	}
	fscanf(file,"%d",&NC);
	int i;
	struct sp* nov, * nt, * z = 0;
	for (nt = spisok; nt != 0 && strcmp(nt->name, name) < 0; z = nt, nt = nt->sled);
	if (nt && strcmp(nt->name, name) == 0) return;
	nov = (struct sp*)malloc(sizeof(struct sp));
	strcpy(nov->name, name);
	nov->sled = nt;
	nov->pred = z;
	nov->propuski = 0;
	for (i = 0; i < NC; i++)
	if (strcmp(students[i].name, name) == 0)
	nov->propuski += students[i].propuski;
	if (!z) spisok = nov;
	if (z) z->sled = nov;
	if (nt) nt->pred = nov;
	return;
}
void diagram(struct z* students)// Диаграмма, показывающая соотношение пропусков у студентов
{
	int NC;
	FILE* file = fopen("spisok.dat","r");
	if((file=fopen("spisok.dat","r"))==NULL)
	{
		printf("\nФайл spisok.dat не открыт !");
		getch(); exit(1);
	}
	fscanf(file,"%d",&NC);
	struct sp *nt;//перемеенная для работы со списком
	int len, i, NColor;//i-для номера строки
	long sum = 0;//число-100%
	char str1[20];//имя
	char str2[20];//процент
	System::ConsoleColor Color;//Задаѐт константы, которые определяют основной цвет и цвет фона консоли
	Console::ForegroundColor = ConsoleColor::Black;
	Console::BackgroundColor = ConsoleColor::White;
	Console::Clear();
	for (i = 0; i < NC; i++)
		sum = sum + students[i].propuski;
	if (!spisok)
		for (i = 0; i < NC; i++)
			vstavka(students, students[i].name);
	Color=ConsoleColor::Black;
	NColor = 0;
	for (nt = spisok, i = 0; nt != 0; nt = nt->sled, i++)
	{
		sprintf(str1,"%s", nt->name);
		sprintf(str2, "%3.f%%", (nt->propuski * 100./ sum));
		Console::ForegroundColor = ConsoleColor::DarkCyan;
		Console::BackgroundColor = ConsoleColor::White;
		Console::CursorLeft = 5;
		Console::CursorTop = i + 1;
		printf(str1);
		Console::CursorLeft = 20;
		printf("%s", str2);
		Console::BackgroundColor = ++Color; NColor++;
		Console::CursorLeft = 30;
		for (len = 0; len < nt->propuski * 100 / sum; len++) printf(" ");
			if (NColor == 14)//выделяем на диаграмму 14 цветов
				{
					Color = ConsoleColor::Black;
					NColor = 0;
				}
	}
	getch();
	return ;
}