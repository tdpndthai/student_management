#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <conio.h>
#include<stdio.h>
#include<unistd.h.>
#include <windows.h>
#include <stdlib.h>
#include <Tchar.h>
using namespace std;


struct Student {
	char ClassCode[10]; //mã lớp học
	char StudentCode[10]; //mã sinh viên
	char FullName[50];
	char DateOfBirth[50]; //ngày sinh
	char dayStr[10] = "", monthStr[10] = "", yearStr[10] = ""; //ngày tháng dạng string
	int day, month, year;
	float AverageScore; //điểm trung bình
};

const char* menu[] = {
	" THEM MOI HO SO\n",
	" IN DANH SACH SINH VIEN\n",
	" SAP XEP SINH VIEN\n",
	" TIM KIEM SINH VIEN\n",
	" THONG KE THEO LOP\n",
	" THOAT"
};

const char* menu_add_student[] = {
	" MA LOP						 \n",
	" MA SINH VIEN					 \n",
	" HO VA TEN			             \n",
	" NGAY SINH			             \n",
	" DIEM TRUNG BINH TICH LUY       \n",
};

const char* menu_sort[] = {
	" SAP XEP CHON\n",
	" SAP XEP CHEN\n",
	" SAP XEP NOI BOI\n",
	" SAP XEP NHANH\n",
	" EXIT"
};

const char *menu_search[] = {
	" TIM KIEM TUAN TU\n",
	" TIM KIEM NHI PHAN\n",
	" EXIT"
};

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD menu = { x, y };
	SetConsoleCursorPosition(h, menu);
}

void textcolor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0; wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void kebang(int m, int n, int t) {
	for (int i = 0; i <= n; i++) {
		gotoxy(m, 9); printf("%c", 201);
		gotoxy(m + t - 1, 9); printf("%c", 187);
		gotoxy(m + 1, 9 + 2 * i); for (int j = 0; j < t - 2; j++) printf("%c", 205);
		for (int k = 0; k < n; k++) {
			gotoxy(m, 11 + 2 * k); printf("%c", 204);
			gotoxy(m + t - 1, 11 + 2 * k); printf("%c", 185);
			gotoxy(m, 10 + 2 * k); printf("%c", 186);
			gotoxy(m + t - 1, 10 + 2 * k); printf("%c", 186);
		}	gotoxy(m, 9 + 2 * n); printf("%c", 200);
		gotoxy(m + t - 1, 9 + 2 * n); printf("%c", 188);
	}
}

// -----------------------them sinh vien-----------------------
void AddStudent(Student &st) {
	system("color F1");
	int check, k;
	char ch;
	kebang(50, 5, 70);
	for (int i = 0; i < 5; i++) {
		gotoxy(52, 10 + 2 * i);
		printf("%s", menu_add_student[i]); printf("\n");
	}

	textcolor(12); fflush(stdin); gotoxy(90, 10); gets_s(st.ClassCode);
again:
	gotoxy(90, 12); printf("\t\t\t"); fflush(stdin); gotoxy(90, 12); fflush(stdin); gets_s(st.StudentCode);	/*if (strlen(st.StudentCode) != 8)	goto again;*/
	gotoxy(90, 14); fflush(stdin);	gets_s(st.FullName);

again1:
	gotoxy(90, 16); printf("\t\t\t");
	fflush(stdin);
	gotoxy(90, 16);
	fflush(stdin);
	gets_s(st.DateOfBirth);
	//---------kiem tra ngay sinh-------------------
	for (int i = strlen(st.DateOfBirth) - 1; i >= 0; i--) {
		if (st.DateOfBirth[i] == 47) {
			k = i;
			break;
		}
	}
	strncpy(st.dayStr, st.DateOfBirth + 0, 2);
	strncpy(st.monthStr, st.DateOfBirth + 3, 2);
	strncpy(st.yearStr, st.DateOfBirth + 6, 4);
	st.day = atoi(st.dayStr);
	st.month = atoi(st.monthStr);
	st.year = atoi(st.yearStr);
	if (st.year >= 1) {
		if ((st.month == 1 || st.month == 3 || st.month == 5 || st.month == 7 || st.month == 8 || st.month == 10 || st.month == 12) && (st.day >= 1 && st.day <= 31))check = 1;
		else if ((st.month == 4 || st.month == 6 || st.month == 9 || st.month == 11) && (st.day >= 1 && st.day <= 30))check = 1;
		else if (st.month == 2 && (st.day >= 1 && st.day <= 28))check = 1;
		else if (st.year % 400 == 0 || (st.year % 4 == 0 && st.year % 100 != 0) && (st.month == 2 && (st.day >= 1 && st.day <= 29)))check = 1;
		else check = 0;
	}
	if (check == 0) goto again1;

again12:
	gotoxy(90, 18); printf("\t\t\t");
	gotoxy(90, 18); cin >> st.AverageScore;
	if (st.AverageScore < 0 || st.AverageScore>10) goto again12;
	//chuanhoachuoi(st.HoTen);
	gotoxy(90, 10); textcolor(3);
	printf(" %s da luu\n", st.FullName);
	textcolor(1);
}

//--------------ghi file nhi phan ----------------
void WriteFile(Student st) {
	ofstream write("student.dat", ios::app | ios::binary);

	write.write(reinterpret_cast<char*>(&st), sizeof(Student));
	write.close();
}

//------------------------in danh sach sinh vien-------------------------------------
void PrintListStudent(vector<Student> st) {
	textcolor(1);
	gotoxy(90, 7); textcolor(28);
	cout << "--------DANH  SACH CO " << st.size() << " SINH VIEN--------"; gotoxy(78, 9); textcolor(29);
	for (int j = 1; j < 86; j++) printf("%c", 205); printf("\n"); gotoxy(77, 9); printf("%c", 201); gotoxy(163, 9); printf("%c", 187);
	gotoxy(77, 10); textcolor(1);
	printf(" %5s | %10s | %15s | %20s | %12s | %7s \n", " STT", " Ma lop", "Ma sinh vien", "Ho va ten", "Ngay sinh", "Diem TB");
	for (int i = 0; i < st.size(); i++)
	{
		//chuanhoachuoi(st[i].HoTen);
		gotoxy(78, 11 + 2 * i); textcolor(29);
		for (int j = 1; j < 86; j++) printf("%c", 205); gotoxy(77, 10 + 2 * i); printf("%c", 186); gotoxy(163, 10 + 2 * i); printf("%c", 186);
		gotoxy(77, 11 + 2 * i); printf("%c", 204); gotoxy(163, 11 + 2 * i); printf("%c", 185);
		gotoxy(78, 12 + 2 * i); textcolor(1);
		printf("%5.03d |%10s  |%15s  | %20s | %12s |%7.2f  \n", (i + 1), _strupr(st[i].ClassCode), st[i].StudentCode, st[i].FullName, st[i].DateOfBirth, st[i].AverageScore);
	}
	gotoxy(78, 11 + 2 * st.size()); textcolor(29);
	for (int j = 1; j < 87; j++) printf("%c", 205); printf("\n"); gotoxy(77, 11 + 2 * st.size()); printf("%c", 200); gotoxy(163, 11 + 2 * st.size()); printf("%c", 188);
	gotoxy(77, 10 + 2 * st.size()); printf("%c", 186); gotoxy(163, 10 + 2 * st.size()); printf("%c", 186);
	textcolor(1);
}

int main() {
	int Opt = 1; //thứ tự menu
	char ch; //kí tự nhập từ bàn phím
	Student std1;
	Student std2;
	Student std3;
	vector<Student> vector_student;
main_menu:
	do {
		//kebang(0, 6, 27);
		gotoxy(50, 3);
		gotoxy(65, 2); printf("--MENU SINH VIEN--\n\n\n\n\n\n\n\n");
		system("color F1");
		for (int t = 1; t <= 6; t++)
		{
			if (t == Opt) {
				textcolor(27); gotoxy(2, 8 + 2 * t);
				printf("%s", menu[t - 1]); printf("\n"); textcolor(1);
			}
			else
			{
				gotoxy(2, 8 + 2 * t);
				printf("%s\n", menu[t - 1]);
			}
		}
		do {
			ch = _getch();
			if (ch == 224) ch = _getch();
		} while (!(ch == 224 || ch == 13 || ch == 77 || ch == 80 || ch == 72 || ch == 75 || ch == 27));
		if (ch == 80) {
			Opt++;
			if (Opt > 6) Opt = 1;
		}
		if (ch == 72)
		{
			Opt--;
			if (Opt < 1) Opt = 6;
		}
	} while (!(ch == 13 || ch == 77));
menu_child:
	switch (Opt) {
	case 1: {
		do {
			gotoxy(70, 10); printf("\t\t\t"); gotoxy(70, 12); printf("\t\t\t"); gotoxy(70, 14); printf("\t\t\t"); gotoxy(70, 16); printf("\t\t\t"); gotoxy(70, 18); printf("\t\t\t");
			AddStudent(std1);
			vector_student.push_back(std1);
			//WriteFile(std1);

		} while (!(ch == 13 || ch == 27));
	}break;
	case 2: {
		do
		{
			PrintListStudent(vector_student);
			do {
				ch = _getch();
				if (ch == 224) ch = _getch();
			} while (!(ch == 224 || ch == 13 || ch == 77 || ch == 80 || ch == 72 || ch == 75 || ch == 27));
			if (ch == 13 || ch == 27) { system("cls"); goto main_menu; }
		} while (!(ch == 13 || ch == 27));
	}break;
	case 3:
	again3: {
		int kOpt = 1;
		do {
			kebang(30, 5, 20);
			gotoxy(50, 3);
			gotoxy(65, 2);
			printf("--MENU SINH VIEN--\n\n\n\n\n");
			system("color F1");
			for (int t = 1; t <= 5; t++)
			{
				if (t == kOpt)
				{
					textcolor(27);
					gotoxy(32, 8 + 2 * t);
					printf("%s", menu_sort[t - 1]);
					printf("\n");
					textcolor(1);
				}
				else
				{
					gotoxy(32, 8 + 2 * t);
					printf("%s\n", menu_sort[t - 1]);
				}
			}
			do
			{
				ch = _getch();
				if (ch == 224)
					ch = _getch();
			} while (!(ch == 224 || ch == 13 || ch == 77 || ch == 80 || ch == 72 || ch == 75 || ch == 27));
			if (ch == 80)
			{
				kOpt++;
				if (kOpt > 5)
					kOpt = 1;
			}
			if (ch == 72)
			{
				kOpt--;
				if (kOpt < 1)
					kOpt = 5;
			}
			if (ch == 75 || ch == 27)
			{
				system("cls");
				goto main_menu;
			}
		} while (!(ch == 13 || ch == 27));
	}
			break;
	case 4:
	again4: {
		int mOpt = 1;
		do
		{
			kebang(30, 3, 22);
			gotoxy(50, 3);
			gotoxy(65, 2);
			printf("--MENU SINH VIEN--\n\n\n\n\n");
			system("color F1");
			for (int t = 1; t <= 3; t++)
			{
				if (t == mOpt)
				{
					gotoxy(32, 8 + 2 * t);
					textcolor(27);
					printf("%s", menu_search[t - 1]);
					printf("\n");
					textcolor(1);
				}
				else
				{
					gotoxy(32, 8 + 2 * t);
					printf("%s\n", menu_search[t - 1]);
				}
			}
			do
			{
				ch = _getch();
				if (ch == 224)
					ch = _getch();
			} while (!(ch == 224 || ch == 13 || ch == 77 || ch == 80 || ch == 72 || ch == 75 || ch == 27));
			if (ch == 80)
			{
				mOpt++;
				if (mOpt > 3)
					mOpt = 1;
			}
			if (ch == 72)
			{
				mOpt--;
				if (mOpt < 1)
					mOpt = 3;
			}
			if (ch == 75 || ch == 27)
			{
				system("cls");
				goto main_menu;
			}
		} while (!(ch == 13 || ch == 27));
	}break;
	case 5:
		break;
	case 6:
		break;
	}
	return 0;
}