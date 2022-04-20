#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>.dat
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
const char FileOutTxt[] = "list_student.txt";
const char FileOutDat[] = "student.dat";


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
	" IN DANH SACH\n",
	" SAP XEP\n",
	" TIM KIEM\n",
	" THONG KE\n",
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
	" SAP XEP NOI BOT\n",
	" SAP XEP NHANH\n",
	" THOAT"
};

const char* menu_sort_option[] = {
	" MA SINH VIEN\n",
	" HO VA TEN\n",
	" NGAY SINH\n",
	" DIEM TB TICH LUY\n",
	" THOAT"
};

const char *menu_search[] = {
	" TIM KIEM TUAN TU\n",
	" TIM KIEM NHI PHAN\n",
	" EXIT"
};

const char *menu_search_option[] = {
	" MA LOP\n",
	" MA SINH VIEN\n",
	" HO VA TEN\n",
	" NGAY SINH\n",
	" DIEM TB TICH LUY\n",
	" THOAT"
};

void Nocursortype() //ẩn con chỏ chuột
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void Cursortype() //hiện con chỏ chuột
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

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

// -----------------------thêm sinh viên-----------------------
void AddStudent(Student &st) {
	system("color B3");
	int check, k;
	char ch;
	kebang(50, 5, 70);
	for (int i = 0; i < 5; i++) {
		gotoxy(52, 10 + 2 * i);
		printf("%s", menu_add_student[i]); printf("\n");
	}

	textcolor(12); fflush(stdin); gotoxy(90, 10); gets_s(st.ClassCode);
again:
	gotoxy(90, 12); printf("\t\t\t"); fflush(stdin); gotoxy(90, 12); fflush(stdin); gets_s(st.StudentCode);
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
	if (check == 0 || k != 5) goto again1;

again12:
	gotoxy(90, 18); printf("\t\t\t");
	gotoxy(90, 18); cin >> st.AverageScore;
	if (st.AverageScore < 0 || st.AverageScore > 10) {
		gotoxy(150, 10);
		textcolor(3);
		printf("Diem trung binh khong hop le %.f", st.AverageScore);
		ch = _getch();
		if (ch == 13 || ch == 27) {
			fflush(stdout);
		}

		goto again12;
	}
	gotoxy(150, 10); textcolor(3);
	printf(" %s da duoc luu\n", st.FullName);
	textcolor(3);
}

//--------------ghi file nhị phân ----------------
void WriteFile(Student st) {
	ofstream write(FileOutDat, ios::app | ios::binary);

	write.write(reinterpret_cast<char*>(&st), sizeof(Student));
	write.close();
}

//---------------------dọc file nhị phân-------------------------
void ReadFile(vector<Student> &st)
{
	Student ste, stv;
	ifstream read(FileOutDat, ios::in | ios::binary);

	while (read.read(reinterpret_cast<char *>(&ste), sizeof(Student)))
	{
		st.push_back(ste);
	}
	read.close();
}

//------------------------in danh sach sinh vien-------------------------------------
void PrintListStudent(vector<Student> st) {
	textcolor(3);
	gotoxy(90, 7); textcolor(28);
	cout << "--------DANH  SACH CO " << st.size() << " SINH VIEN--------"; gotoxy(78, 9); textcolor(29);
	for (int j = 1; j < 86; j++) printf("%c", 205); printf("\n"); gotoxy(77, 9); printf("%c", 201); gotoxy(163, 9); printf("%c", 187);
	gotoxy(77, 10); textcolor(3);
	printf(" %5s | %10s | %15s | %20s | %12s | %7s \n", " STT", " Ma lop", "Ma sinh vien", "Ho va ten", "Ngay sinh", "Diem TB");
	for (int i = 0; i < st.size(); i++)
	{
		gotoxy(78, 11 + 2 * i); textcolor(29);
		for (int j = 1; j < 86; j++) printf("%c", 205); gotoxy(77, 10 + 2 * i); printf("%c", 186); gotoxy(163, 10 + 2 * i); printf("%c", 186);
		gotoxy(77, 11 + 2 * i); printf("%c", 204); gotoxy(163, 11 + 2 * i); printf("%c", 185);
		gotoxy(78, 12 + 2 * i); textcolor(3);
		printf("%5.03d |%10s  |%15s  | %20s | %12s |%7.2f  \n", (i + 1), _strupr(st[i].ClassCode), st[i].StudentCode, st[i].FullName, st[i].DateOfBirth, st[i].AverageScore);
	}
	gotoxy(78, 11 + 2 * st.size()); textcolor(29);
	for (int j = 1; j < 87; j++) printf("%c", 205); printf("\n"); gotoxy(77, 11 + 2 * st.size()); printf("%c", 200); gotoxy(163, 11 + 2 * st.size()); printf("%c", 188);
	gotoxy(77, 10 + 2 * st.size()); printf("%c", 186); gotoxy(163, 10 + 2 * st.size()); printf("%c", 186);
	textcolor(3);
}

// bo dau cach trong
char *XuliTen(char name[50])
{
	char ten[50], temp[10], ten1[50];
	strcpy(ten, name);
	int i = 0;
	int n = strlen(ten) - 1;
	while (ten[n] != ' ')
	{
		temp[i] = ten[n];
		i++;
		n--;
	}
	temp[i] = '\0';
	ten[n] = '\0';
	strcpy(ten1, _strrev(temp));
	strcat(ten1, " ");
	strcat(ten1, ten);
	return ten1;
}

// bo dau / o ngay sinh
char *XuliNgaySinh(char ngay[20])
{
	char temp[30], date[20], *m[20];
	strcpy(date, ngay);
	char *p;
	int i = 0;
	p = strtok(date, "/");
	while (p != NULL)
	{
		m[i] = p;
		i++;
		p = strtok(NULL, "/");
	}
	strcpy(temp, m[i - 1]);
	for (int j = i - 2; j >= 0; j--)
	{
		strcat(temp, "/");
		strcat(temp, m[j]);
	}
	return temp;
}


void strdelete(char *s, int vt, int sl) // xoa ki tu o vi tri vt, s1 la vt xet cuoi
{
	int n = strlen(s), i;
	for (i = vt; i <= n - sl; ++i)
		s[i] = s[i + sl];
}

//-------------------------------------------------------------------------------------------------------
void chuanhoachuoi(char a[])
{
	int i;
	while (a[strlen(a) - 1] == ' ') // xoa khoang trang o cuoi
		a[strlen(a) - 1] = 0;
	while (a[0] == ' ') // xoa khoang trang o dau
		strdelete(a, 0, 1);
	for (i = 0; i < strlen(a); ++i)
		if ((a[i] >= 65) && (a[i] <= 90)) // kiem tra co phai la ky tu hoa
			a[i] += 32;					  // chuyen tat ca ve ky tu thuong
	i = 0;
	while (i < strlen(a)) // xoa hai khoang trang lien tiep
		if ((a[i] == ' ') && (a[i + 1] == ' '))
			strdelete(a, i, 1);
		else
			++i;
	for (i = 0; i < strlen(a); i++)
		if (a[i] == ' ')
			a[i + 1] -= 32; // chuyen chu cai sau khoang trang thanh chu hoa
	a[0] = toupper(a[0]);	// chuyen chu cai dau tien thanh chu hoa
}

//-------------ghi ra file text ---------
void WriteFileText (vector<Student> st)
{
	FILE *f1;
	int i = 1;

	f1 = fopen(FileOutTxt, "wt");
	fprintf(f1, "          -----------DANH SACH SINH VIEN-------------\n");
	fprintf(f1, "---------------------------------------------------------------------------------------------\n");

	fprintf(f1, "| stt  |     MALOP  |        MAst  |           HOTEN         |     NGAYSINH    |   DIEMTB   |\n");
	for (int i = 0; i < st.size(); i++)
	{
		chuanhoachuoi(st[i].FullName);
		fprintf(f1, "---------------------------------------------------------------------------------------------\n");
		fprintf(f1, "|%5.03d | %10s | %12s | %23s | %15s | %10.2f |\n", (i + 1), _strupr(st[i].ClassCode), st[i].StudentCode, st[i].FullName, st[i].DateOfBirth, st[i].AverageScore);
	}
	fprintf(f1, "---------------------------------------------------------------------------------------------\n");
	fclose(f1);
}

//----------------sắp xếp chọn--------------------
void SelectionSort(vector<Student> st, int Opt) {
	int min;
	char temp1[30], temp2[30];
	for (int i = 0; i < st.size() - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < st.size(); j++)
		{
			switch (Opt)
			{
			case 1:
			{
				if (strcmp(st[min].StudentCode, st[j].StudentCode) > 0)
					min = j;
			}
			break;
			case 2:
			{
				strcpy(temp1, XuliTen(st[min].FullName));
				strcpy(temp2, XuliTen(st[j].FullName));
				if (strcmp(temp1, temp2) > 0)
					min = j;
			}
			break;
			case 3:
			{
				strcpy(temp1, XuliNgaySinh(st[min].DateOfBirth));
				strcpy(temp2, XuliNgaySinh(st[j].DateOfBirth));
				if (strcmp(temp1, temp2) > 0)
					min = j;
			}
			break;
			case 4:
			{
				if (st[min].AverageScore < st[j].AverageScore)
					min = j;
			}
			break;
			}
		}
		swap(st[i], st[min]);
	}
	PrintListStudent(st);
	_getch();
	WriteFileText(st);
}

//----------------------sắp xếp chèn-------------
void InsertionSort(vector<Student> st, int Opt) {
	Student temp;
	char temp1[50], temp2[50];
	for (int i = 1; i < st.size(); i++)
	{
		temp = st[i];
		int j = i - 1;
		switch (Opt)
		{
		case 1:
		{
			while ((j >= 0) && (strcmp(temp.StudentCode, st[j].StudentCode) < 0))
			{
				st[j + 1] = st[j];
				j = j - 1;
			}
		}
		break;
		case 2:
		{
			strcpy(temp1, XuliTen(temp.FullName));
			while (j >= 0)
			{
				strcpy(temp2, XuliTen(st[j].FullName));
				if (strcmp(temp1, temp2) < 0)
				{
					st[j + 1] = st[j];
					j = j - 1;
				}
				else
				{
					break;
				}
			}
		}
		break;
		case 3:
		{
			strcpy(temp1, XuliNgaySinh(temp.DateOfBirth));
			while (j >= 0)
			{
				strcpy(temp2, XuliNgaySinh(st[j].DateOfBirth));
				if (strcmp(temp1, temp2) < 0)
				{
					st[j + 1] = st[j];
					j = j - 1;
				}
				else
				{
					break;
				}
			}
		}
		break;
		case 4:
		{
			while ((j >= 0) && (temp.AverageScore > st[j].AverageScore))
			{
				st[j + 1] = st[j];
				j = j - 1;
			}
		}
		break;
		}
		st[j + 1] = temp;
	}
	PrintListStudent(st);
	_getch();
	WriteFileText(st);
}

//----------------------sắp xếp nổi bọt-------------
void BubbleSort(vector<Student> st, int Opt) {
	char temp1[50], temp2[50];
	for (int i = 0; i < st.size() - 1; i++)
	{
		for (int j = st.size() - 1; j > i; j--)
		{
			switch (Opt)
			{
			case 1:
			{
				if (strcmp(st[j].StudentCode, st[j - 1].StudentCode) < 0)
					swap(st[j], st[j - 1]);
			}
			break;
			case 2:
			{
				strcpy(temp1, XuliTen(st[j].FullName));
				strcpy(temp2, XuliTen(st[j - 1].FullName));
				if (strcmp(temp1, temp2) < 0)
					swap(st[j], st[j - 1]);
			}
			break;
			case 3:
			{
				strcpy(temp1, XuliNgaySinh(st[j].DateOfBirth));
				strcpy(temp2, XuliNgaySinh(st[j - 1].DateOfBirth));
				if (strcmp(temp1, temp2) < 0)
					swap(st[j], st[j - 1]);
			}
			break;
			case 4:
			{
				if (st[j].AverageScore > st[j - 1].AverageScore)
					swap(st[j], st[j - 1]);
			}
			break;
			}
		}
	}
	PrintListStudent(st);
	_getch();
	WriteFileText(st);
}

//----------------------sắp xếp nhanh-------------
void QuickSort(vector<Student> &st, int Left, int Right, int Opt) {
	int i = Left;
	int j = Right;
	Student key = st[(Left + Right) / 2];
	char cKey[50], temp[50];

	while (i <= j)
	{
		switch (Opt)
		{
		case 1:
		{
			while (strcmp(st[i].StudentCode, key.StudentCode) < 0)
				i++;
			while (strcmp(st[j].StudentCode, key.StudentCode) > 0)
				j--;
		}
		break;
		case 2:
		{
			strcpy(cKey, XuliTen(key.FullName));
			while (1)
			{
				strcpy(temp, XuliTen(st[i].FullName));
				if (strcmp(temp, cKey) < 0)
					i++;
				else
					break;
			}
			while (1)
			{
				strcpy(temp, XuliTen(st[j].FullName));
				if (strcmp(temp, cKey) > 0)
					j--;
				else
					break;
			}
		}
		break;
		case 3:
		{
			strcpy(cKey, XuliNgaySinh(key.DateOfBirth));
			while (1)
			{
				strcpy(temp, XuliNgaySinh(st[i].DateOfBirth));
				if (strcmp(temp, cKey) < 0)
					i++;
				else
					break;
			}
			while (1)
			{
				strcpy(temp, XuliNgaySinh(st[j].DateOfBirth));
				if (strcmp(temp, cKey) > 0)
					j--;
				else
					break;
			}
		}
		break;
		case 4:
		{
			while (st[i].AverageScore > key.AverageScore)
				i++;
			while (st[j].AverageScore < key.AverageScore)
				j--;
		}
		break;
		case 5:
		{
			while (strcmp(st[i].ClassCode, key.ClassCode) < 0)
				i++;
			while (strcmp(st[j].ClassCode, key.ClassCode) > 0)
				j--;
		}
		break;
		}
		if (i <= j)
		{
			swap(st[i], st[j]);
			i++;
			j--;
		}
	}
	if (Left < j)
		QuickSort(st, Left, j, Opt);
	if (i < Right)
		QuickSort(st, i, Right, Opt);
	WriteFileText(st);
}

int main() {
	int Opt = 1; //thứ tự menu
	char ch; //kí tự nhập từ bàn phím
	Student std1;
	Student std2;
	Student std3;
	vector<Student> vector_student;
	ReadFile(vector_student);
main_menu:
	do {
		//kebang(0, 6, 27);
		gotoxy(50, 3);
		gotoxy(65, 2); printf("--MENU SINH VIEN--\n\n\n\n\n\n\n\n");
		system("color B3");
		Nocursortype();
		for (int t = 1; t <= 6; t++)
		{
			if (t == Opt) {
				textcolor(26); gotoxy(2, 8 + 2 * t);
				printf("%s", menu[t - 1]); printf("\n"); textcolor(3);
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
	case 1: {// thêm hồ sơ
		do {
			Cursortype();
			gotoxy(70, 10); printf("\t\t\t"); gotoxy(70, 12); printf("\t\t\t"); gotoxy(70, 14); printf("\t\t\t"); gotoxy(70, 16); printf("\t\t\t"); gotoxy(70, 18); printf("\t\t\t");
			AddStudent(std1);
			vector_student.push_back(std1);
			WriteFile(std1);
			//system("cls");
			goto main_menu;
		} while (!(ch == 13 || ch == 27));
	}break;
	case 2: {// in danh sách st
		do
		{
			PrintListStudent(vector_student);
			do {
				ch = _getch();
				if (ch == 224) ch = _getch();
			} while (!(ch == 224 || ch == 13 || ch == 77 || ch == 80 || ch == 72 || ch == 75 || ch == 27));
			if (ch == 13 || ch == 27) { 
				system("cls"); 
				goto main_menu; 
			}
		} while (!(ch == 13 || ch == 27));
	}break;
	case 3://sắp xếp
	sort_function: 
	{
		int optSort = 1;
		do {
			gotoxy(65, 2);
			printf("--MENU SINH VIEN--\n\n\n\n\n");
			system("color B3");
			for (int t = 1; t <= 5; t++)
			{
				if (t == optSort)
				{
					textcolor(26);
					gotoxy(32, 8 + 2 * t);
					printf("%s", menu_sort[t - 1]);
					printf("\n");
					textcolor(3);
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
				optSort++;
				if (optSort > 5)
					optSort = 1;
			}
			if (ch == 72)
			{
				optSort--;
				if (optSort < 1)
					optSort = 5;
			}
			if (ch == 75 || ch == 27)
			{
				//system("cls");
				goto main_menu;
			}
		} while (!(ch == 13 || ch == 27));

		switch (optSort)
		{
			case 1:
			case 2:
			case 3:
			case 4:
			select_sort_option:
			{
				char ch;
				int optSortSelection = 1;
				do {
					gotoxy(65, 2);
					printf("--MENU SINH VIEN--\n\n\n\n\n");
					system("color B3");
					for (int t = 1; t <= 5; t++)
					{
						if (t == optSortSelection)
						{
							gotoxy(55, 8 + 2 * t);
							textcolor(26);
							printf("%s", menu_sort_option[t - 1]);
							printf("\n");
							textcolor(3);
						}
						else
						{
							gotoxy(55, 8 + 2 * t);
							printf("%s\n", menu_sort_option[t - 1]);
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
						optSortSelection++;
						if (optSortSelection > 5)
							optSortSelection = 1;
					}
					if (ch == 72)
					{
						optSortSelection--;
						if (optSortSelection < 1)
							optSortSelection = 5;
					}
					if (ch == 75 || ch == 27)
					{
						goto sort_function;
					}
				} while (!(ch == 13 || ch == 27));

				switch (optSortSelection)
				{
					case 1:
						SelectionSort(vector_student, optSortSelection);
						break;
					case 2:
						InsertionSort(vector_student, optSortSelection);
						_getch();
						break;
					case 3:
						BubbleSort(vector_student, optSortSelection);
						_getch();
						break;
					case 4:
					{
						vector<Student> stp(vector_student);
						QuickSort(stp, 0, stp.size() - 1, optSortSelection);
						_getch();
					}
					break;
					case 5:
						//system("cls");
						goto sort_function;
						break;
				}
				goto select_sort_option;
				break;
			}
			case 5:
				system("cls");
				goto main_menu;
				break;
		}
	} 
	goto sort_function;
	case 4://tìm kiếm
	again4: {
		int mOpt = 1;
		do
		{
			kebang(30, 3, 22);
			gotoxy(50, 3);
			gotoxy(65, 2);
			printf("--MENU SINH VIEN--\n\n\n\n\n");
			system("color B3");
			for (int t = 1; t <= 3; t++)
			{
				if (t == mOpt)
				{
					gotoxy(32, 8 + 2 * t);
					textcolor(26);
					printf("%s", menu_search[t - 1]);
					printf("\n");
					textcolor(3);
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
	case 5://thống kê
		do {

		} while (!(ch == 13 || ch == 27));
		break;
	case 6://thoát
		system("cls");
		cout << "\n\n"
			<< endl;
		gotoxy(45, 2);
		cout << "HOC, HOC NUA, HOC MAI!!!!!" << endl;
		textcolor(12);
		cout << "\n\nAn phim bat ki de thoat...";
		_getch();
		break;
	}
	return 0;
}