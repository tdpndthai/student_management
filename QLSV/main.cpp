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

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27


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

void DrawBoard(int m, int n, int t) {
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
	DrawBoard(50, 5, 70);
	for (int i = 0; i < 5; i++) {
		gotoxy(52, 10 + 2 * i);
		printf("%s", menu_add_student[i]); printf("\n");
	}

	textcolor(12); fflush(stdin); gotoxy(90, 10); gets_s(st.ClassCode);
again:
	gotoxy(90, 12); printf("\t\t\t"); fflush(stdin); gotoxy(90, 12); fflush(stdin); gets_s(st.StudentCode); if (strlen(st.StudentCode) != 8) goto again; fflush(stdout); //msv = 8
	gotoxy(90, 14); fflush(stdin);	gets_s(st.FullName);

again1:
	gotoxy(90, 16); printf("\t\t\t");
	fflush(stdin);
	gotoxy(90, 16);
	fflush(stdin);
	gets_s(st.DateOfBirth);
	//---------kiem tra ngay sinh format dd/mm/yyyy-------------------
	for (int i = strlen(st.DateOfBirth) - 1; i >= 0; i--) {
		if (st.DateOfBirth[i] == 47) { //gạch / cuối cùng phải nằm vị trí số 5
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
		if (ch == KEY_ENTER || ch == KEY_ESC) {
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
char *NameHandling(char name[50])
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
char *DateHandling(char ngay[20])
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
void HandleRegularString(char a[])
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
void WriteFileText(vector<Student> st)
{
	FILE *f1;
	int i = 1;

	f1 = fopen(FileOutTxt, "wt");
	fprintf(f1, "          -----------DANH SACH SINH VIEN-------------\n");
	fprintf(f1, "---------------------------------------------------------------------------------------------\n");

	fprintf(f1, "| STT  |     MALOP  |        MASV  |           HOTEN         |     NGAYSINH    |   DIEMTB   |\n");
	for (int i = 0; i < st.size(); i++)
	{
		HandleRegularString(st[i].FullName);
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
				strcpy(temp1, NameHandling(st[min].FullName));
				strcpy(temp2, NameHandling(st[j].FullName));
				if (strcmp(temp1, temp2) > 0)
					min = j;
			}
			break;
			case 3:
			{
				strcpy(temp1, DateHandling(st[min].DateOfBirth));
				strcpy(temp2, DateHandling(st[j].DateOfBirth));
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
			strcpy(temp1, NameHandling(temp.FullName));
			while (j >= 0)
			{
				strcpy(temp2, NameHandling(st[j].FullName));
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
			strcpy(temp1, DateHandling(temp.DateOfBirth));
			while (j >= 0)
			{
				strcpy(temp2, DateHandling(st[j].DateOfBirth));
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
				strcpy(temp1, NameHandling(st[j].FullName));
				strcpy(temp2, NameHandling(st[j - 1].FullName));
				if (strcmp(temp1, temp2) < 0)
					swap(st[j], st[j - 1]);
			}
			break;
			case 3:
			{
				strcpy(temp1, DateHandling(st[j].DateOfBirth));
				strcpy(temp2, DateHandling(st[j - 1].DateOfBirth));
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
			strcpy(cKey, NameHandling(key.FullName));
			while (1)
			{
				strcpy(temp, NameHandling(st[i].FullName));
				if (strcmp(temp, cKey) < 0)
					i++;
				else
					break;
			}
			while (1)
			{
				strcpy(temp, NameHandling(st[j].FullName));
				if (strcmp(temp, cKey) > 0)
					j--;
				else
					break;
			}
		}
		break;
		case 3:
		{
			strcpy(cKey, DateHandling(key.DateOfBirth));
			while (1)
			{
				strcpy(temp, DateHandling(st[i].DateOfBirth));
				if (strcmp(temp, cKey) < 0)
					i++;
				else
					break;
			}
			while (1)
			{
				strcpy(temp, DateHandling(st[j].DateOfBirth));
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

//-----------tim kiem tuan tu----------------
void LinearSearch(vector<Student> st, int Opt)
{
	vector<Student> result;
	char cKey[50];
	float mKey;
	DrawBoard(77, 1, 30);
	gotoxy(80, 10);
	textcolor(12);
	fflush(stdin);
	gets_s(cKey);
	textcolor(3);
	HandleRegularString(cKey);
	for (int i = 0; i < st.size(); i++)
	{
		switch (Opt)
		{
		case 1:
		{
			_strupr(cKey);
			if (strcmp(cKey, st[i].ClassCode) == 0)
			{
				result.push_back(st[i]);
			}
		}
		break;
		case 2:
		{
			if (strcmp(cKey, st[i].StudentCode) == 0)
			{
				result.push_back(st[i]);
			}
		}
		break;
		case 3:
		{
			int k;
			char ten[50];
			for (int t = strlen(st[i].FullName) - 1; t >= 0; t--)
			{
				if (st[i].FullName[t] == 32 && st[i].FullName[t + 1] != 32)
				{
					k = t;
					break;
				}
			}
			strncpy(ten, st[i].FullName + k + 1, strlen(st[i].FullName) - k);
			if (strcmp(cKey, ten) == 0)
			{
				result.push_back(st[i]);
			}
			if (strcmp(cKey, st[i].FullName) == 0)
			{
				result.push_back(st[i]);
			}
		}
		break;
		case 4:
		{
			if (strcmp(cKey, st[i].dayStr) == 0 || strcmp(cKey, st[i].monthStr) == 0 || strcmp(cKey, st[i].yearStr) == 0)
				result.push_back(st[i]);
			else if (strcmp(cKey, st[i].DateOfBirth) == 0)
			{
				result.push_back(st[i]);
			}
		}
		break;
		case 5:
		{
			float mKey = atof(cKey);
			if (mKey == st[i].AverageScore)
			{
				result.push_back(st[i]);
			}
		}
		break;
		}
	}
	if (result.empty())
	{
		gotoxy(90, 15);
		textcolor(12);
		printf("--------Khong tim thay ket qua %s!!!-------", cKey);
		gotoxy(90, 16);
		textcolor(28);
		printf("--------Moi ban nhap lai tim kiem: ---------");
		textcolor(3);
	}
	else
	{
		gotoxy(90, 5);
		textcolor(2);
		printf("Ket qua tim kiem %s: ", cKey);
		textcolor(3);
		PrintListStudent(result);
	}
}

//-----------tim kiem nhi phan----------------
int Binary_search(vector<Student> st, int L, int R, char cKey[50], int Opt)
{
	if (L > R)
		return -1;
	else
	{
		char tKey[50];
		int key = (L + R) / 2;
		switch (Opt)
		{
		case 1:
		{
			_strupr(cKey);
			if (strcmp(cKey, st[key].ClassCode) == 0)
				return key;
			else if (strcmp(cKey, st[key].ClassCode) > 0)
				return Binary_search(st, key + 1, R, cKey, Opt);
			else if (strcmp(cKey, st[key].ClassCode) < 0)
				return Binary_search(st, L, key - 1, cKey, Opt);
		}
		break;
		case 2:
		{
			if (strcmp(cKey, st[key].StudentCode) == 0)
				return key;
			else if (strcmp(cKey, st[key].StudentCode) > 0)
				return Binary_search(st, key + 1, R, cKey, Opt);
			else if (strcmp(cKey, st[key].StudentCode) < 0)
				return Binary_search(st, L, key - 1, cKey, Opt);
		}
		break;
		case 3:
		{
			HandleRegularString(cKey);
			if (strstr(cKey, " ") == NULL)
			{
				int k;
				char ten[50];
				for (int t = strlen(st[key].FullName) - 1; t >= 0; t--)
				{
					if (st[key].FullName[t] == 32 && st[key].FullName[t + 1] != 32)
					{
						k = t;
						break;
					}
				}
				strncpy(ten, st[key].FullName + k + 1, strlen(st[key].FullName) - k);

				if (strcmp(cKey, ten) == 0)
					return key;
				else if (strcmp(cKey, ten) > 0)
					return Binary_search(st, key + 1, R, cKey, Opt);
				else if (strcmp(cKey, ten) < 0)
					return Binary_search(st, L, key - 1, cKey, Opt);
			}
			else
			{

				HandleRegularString(cKey);
				char cKey1[50];
				strcpy(tKey, NameHandling(st[key].FullName));
				strcpy(cKey1, NameHandling(cKey));
				if (strcmp(cKey1, tKey) == 0)
					return key;
				else if (strcmp(cKey1, tKey) > 0)
					return Binary_search(st, key + 1, R, cKey, Opt);
				else if (strcmp(cKey1, tKey) < 0)
					return Binary_search(st, L, key - 1, cKey, Opt);
			}
		}
		case 4:
		{
			if (strlen(cKey) < 5)
			{
				if (strcmp(cKey, st[key].yearStr) == 0)
					return key;
				else if (strcmp(cKey, st[key].yearStr) > 0)
					return Binary_search(st, key + 1, R, cKey, Opt);
				else if (strcmp(cKey, st[key].yearStr) < 0)
					return Binary_search(st, L, key - 1, cKey, Opt);
			}
			else
			{

				char cKey1[50];
				strcpy(tKey, DateHandling(st[key].DateOfBirth));
				strcpy(cKey1, DateHandling(cKey));
				if (strcmp(cKey1, tKey) == 0)
					return key;
				else if (strcmp(cKey1, tKey) > 0)
					return Binary_search(st, key + 1, R, cKey, Opt);
				else if (strcmp(cKey1, tKey) < 0)
					return Binary_search(st, L, key - 1, cKey, Opt);
			}
		}
		break;
		case 5:
		{
			float mKey = atof(cKey);
			if (mKey == st[key].AverageScore)
				return key;
			else if (mKey < st[key].AverageScore)
				return Binary_search(st, key + 1, R, cKey, Opt);
			else if (mKey > st[key].AverageScore)
				return Binary_search(st, L, key - 1, cKey, Opt);
		}
		break;
		}
	}
}


//--------------------thong ke sinh vien-----------------------------
void Statistic(vector<Student> st, char x[])
{
again20:
	DrawBoard(35, 1, 25);
	gotoxy(37, 10);
	printf(" Ma Lop  ||  ");
	gotoxy(50, 10);
	printf("\t");
	textcolor(12);
	fflush(stdin);
	gotoxy(51, 10);
	gets_s(x, 10);
	textcolor(3);
	int chon;
	float tong, j, k, l, m, n;
	tong = j = l = m = n = k = 0;
	for (int i = 0; i < st.size(); i++)
	{
		if (_stricmp(st[i].ClassCode, x) == 0)
		{
			tong++;
			if (st[i].AverageScore >= 9)
				j++;
			else if ((st[i].AverageScore < 9) && (st[i].AverageScore >= 8))
				k++;
			else if ((st[i].AverageScore < 8) && (st[i].AverageScore >= 7))
				l++;
			else if ((st[i].AverageScore < 7) && (st[i].AverageScore >= 5))
				m++;
			else
				n++;
		}
	}
	if (tong > 0)
	{
		textcolor(29);
		DrawBoard(77, 4, 72);
		textcolor(3);
		gotoxy(78, 10);
		printf("\t\t    So hoc sinh trong lop %s la:  %.0f hocsinh\t\t    ", _strupr(x), tong);
		gotoxy(78, 12);
		printf("%10s|%11s|%11s|%11s|%11s|%11s\n", " ", "Xuat Sac", "Gioi", "Kha", "Trung Binh", "Yeu");
		gotoxy(78, 13);
		gotoxy(78, 14);
		printf("%10s|%11.2f|%11.2f|%11.2f|%11.2f|%11.2f\n", " ", j, k, l, m, n);
		textcolor(3);
		gotoxy(78, 16);
		printf("%10s|%11.2f|%11.2f|%11.2f|%11.2f|%11.2f\n", "Ti Le(%)", (j / tong) * 100, (k / tong) * 100, (l / tong) * 100, (m / tong) * 100, (n / tong) * 100);
		textcolor(29);
		gotoxy(78, 17);
	}
	else
	{
		textcolor(29);
		gotoxy(78, 10);
		printf("Lop %s khong co sinh vien.", x);
		_getch();
		textcolor(3);
		goto again20;
	}
	_getch();
	textcolor(3);
	system("cls");
}

int main() {
	int Opt = 1; //thứ tự menu
	int optSort = 1; //thứ tự lựa chọn option sort
	int optSortSelection = 1; //thứ tự lựa chọn điều kiện sort: class code,student code
	int optSearch = 1; //thứ tự lựa chọn option search
	char ch; //kí tự nhập từ bàn phím
	Student std1;
	Student std2;
	Student std3;
	vector<Student> vector_student;
	ReadFile(vector_student);
	char x[10];
main_menu:
	textcolor(2);
	gotoxy(65, 25);
	printf("NGUYEN DANH THAI");
	gotoxy(70, 26);
	textcolor(2);
	printf("CNPM15");
	do {
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
		} while (!(ch == 224 || ch == KEY_ENTER || ch == KEY_RIGHT || ch == KEY_DOWN || ch == KEY_UP || ch == KEY_LEFT || ch == KEY_ESC));
		if (ch == KEY_DOWN) {
			Opt++;
			if (Opt > 6) Opt = 1;
		}
		if (ch == KEY_UP)
		{
			Opt--;
			if (Opt < 1) Opt = 6;
		}
	} while (!(ch == KEY_ENTER || ch == KEY_RIGHT));
menu_child:
	switch (Opt) {
	case 1: {// thêm hồ sơ
		do {
			Cursortype();
			gotoxy(70, 10); printf("\t\t\t"); gotoxy(70, 12); printf("\t\t\t"); gotoxy(70, 14); printf("\t\t\t"); gotoxy(70, 16); printf("\t\t\t"); gotoxy(70, 18); printf("\t\t\t");
			AddStudent(std1);
			vector_student.push_back(std1);
			WriteFile(std1);
			system("cls");
			goto main_menu;
		} while (!(ch == KEY_ENTER || ch == KEY_ESC));
	}break;
	case 2: {// in danh sách st
		do
		{
			PrintListStudent(vector_student);
			do {
				ch = _getch();
				if (ch == 224) ch = _getch();
			} while (!(ch == 224 || ch == KEY_ENTER || ch == KEY_RIGHT || ch == KEY_DOWN || ch == KEY_UP || ch == KEY_LEFT || ch == KEY_ESC));
			if (ch == KEY_ENTER || ch == KEY_ESC) {
				system("cls");
				goto main_menu;
			}
		} while (!(ch == KEY_ENTER || ch == KEY_ESC));
	}break;
	case 3://sắp xếp
	sort_function:
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
			} while (!(ch == 224 || ch == KEY_ENTER || ch == KEY_RIGHT || ch == KEY_DOWN || ch == KEY_UP || ch == KEY_LEFT || ch == KEY_ESC));
			if (ch == KEY_DOWN)
			{
				optSort++;
				if (optSort > 5)
					optSort = 1;
			}
			if (ch == KEY_UP)
			{
				optSort--;
				if (optSort < 1)
					optSort = 5;
			}
			if (ch == KEY_LEFT || ch == KEY_ESC)
			{
				system("cls");
				goto main_menu;
			}
		} while (!(ch == KEY_ENTER || ch == KEY_ESC || ch == KEY_RIGHT));

		switch (optSort) //lựa chọn sắp xếp nào,chọn,chèn,nhanh,noi bot
		{
		case 1:
		case 2:
		case 3:
		case 4:
		select_sort_option:
		{
			char ch;
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
				} while (!(ch == 224 || ch == KEY_ENTER || ch == KEY_RIGHT || ch == KEY_DOWN || ch == KEY_UP || ch == KEY_LEFT || ch == KEY_ESC));
				if (ch == KEY_DOWN)
				{
					optSortSelection++;
					if (optSortSelection > 5)
						optSortSelection = 1;
				}
				if (ch == KEY_UP)
				{
					optSortSelection--;
					if (optSortSelection < 1)
						optSortSelection = 5;
				}
				if (ch == KEY_LEFT || ch == KEY_ESC)
				{
					goto sort_function;
				}
			} while (!(ch == KEY_ENTER || ch == KEY_ESC));

			switch (optSortSelection)
			{
			case 1:
				SelectionSort(vector_student, optSortSelection);
				break;
			case 2:
				InsertionSort(vector_student, optSortSelection);
				break;
			case 3:
				BubbleSort(vector_student, optSortSelection);
				break;
			case 4:
			{
				vector<Student> stp(vector_student);
				QuickSort(stp, 0, stp.size() - 1, optSortSelection);
				PrintListStudent(stp);
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
	goto sort_function;
	case 4://tìm kiếm
	search_function: {
		do
		{
			DrawBoard(30, 3, 22);
			gotoxy(50, 3);
			gotoxy(65, 2);
			printf("--MENU SINH VIEN--\n\n\n\n\n");
			system("color B3");
			for (int t = 1; t <= 3; t++)
			{
				if (t == optSearch)
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
			} while (!(ch == 224 || ch == KEY_ENTER || ch == KEY_RIGHT || ch == KEY_DOWN || ch == KEY_UP || ch == KEY_LEFT || ch == KEY_ESC));
			if (ch == KEY_DOWN)
			{
				optSearch++;
				if (optSearch > 3)
					optSearch = 1;
			}
			if (ch == KEY_UP)
			{
				optSearch--;
				if (optSearch < 1)
					optSearch = 3;
			}
			if (ch == KEY_LEFT || ch == KEY_ESC)
			{
				system("cls");
				goto main_menu;
			}
		} while (!(ch == KEY_ENTER || ch == KEY_ESC || ch == KEY_RIGHT));

		switch (optSearch)
		{
		case 1:
		again5:
		{
			char ch;
			int iOpt = 1;
			do
			{
				DrawBoard(54, 6, 20);
				gotoxy(50, 3);
				printf("**************************************************");
				gotoxy(65, 2);
				printf("--MENU SINH VIEN--\n\n\n\n\n");
				system("color B3");
				for (int t = 1; t <= 6; t++)
				{
					if (t == iOpt)
					{
						gotoxy(56, 8 + 2 * t);
						textcolor(26);
						printf("%s", menu_search_option[t - 1]);
						printf("\n");
						textcolor(3);
					}
					else
					{
						gotoxy(56, 8 + 2 * t);
						printf("%s\n", menu_search_option[t - 1]);
					}
				}
				do
				{
					ch = _getch();
					if (ch == 224)
						ch = _getch();
				} while (!(ch == 224 || ch == KEY_ENTER || ch == KEY_RIGHT || ch == KEY_DOWN || ch == KEY_UP || ch == KEY_LEFT || ch == KEY_ESC));
				if (ch == KEY_DOWN)
				{
					iOpt++;
					if (iOpt > 6)
						iOpt = 1;
				}
				if (ch == KEY_UP)
				{
					iOpt--;
					if (iOpt < 1)
						iOpt = 6;
				}
				if (ch == KEY_LEFT || ch == KEY_ESC)
					goto search_function;
			} while (!(ch == KEY_ENTER || ch == KEY_ESC || ch == KEY_RIGHT));
			switch (iOpt)
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			{
				LinearSearch(vector_student, iOpt);
				_getch();
			}
			break;
			case 6:
				goto search_function;
				break;
			default:
				break;
			}
			system("cls");
			DrawBoard(30, 3, 22);
			for (int t = 0; t < 3; t++)
			{
				gotoxy(32, 10 + 2 * t);
				printf("%s", menu_search[t]);
				textcolor(3);
			}
			//DrawBoard(0, 6, 27);
			for (int h = 0; h < 6; h++)
			{
				gotoxy(2, 10 + 2 * h);
				printf("%s", menu[h]);
				textcolor(3);
			}
			goto again5;
		}
		case 2:
		again6:
		{
			char ch;
			int tOpt = 1;
			do
			{
				DrawBoard(54, 6, 20);
				gotoxy(50, 3);
				printf("**************************************************");
				gotoxy(65, 2);
				printf("--MENU SINH VIEN--\n\n\n\n\n");
				system("color B3");
				for (int t = 1; t <= 6; t++)
				{
					if (t == tOpt)
					{
						gotoxy(56, 8 + 2 * t);
						textcolor(26);
						printf("%s", menu_search_option[t - 1]);
						printf("\n");
						textcolor(3);
					}
					else
					{
						gotoxy(56, 8 + 2 * t);
						printf("%s\n", menu_search_option[t - 1]);
					}
				}
				do
				{
					ch = _getch();
					if (ch == 224)
						ch = _getch();
				} while (!(ch == 224 || ch == KEY_ENTER || ch == KEY_RIGHT || ch == KEY_DOWN || ch == KEY_UP || ch == KEY_LEFT || ch == KEY_ESC));
				if (ch == KEY_DOWN)
				{
					tOpt++;
					if (tOpt > 6)
						tOpt = 1;
				}
				if (ch == KEY_UP)
				{
					tOpt--;
					if (tOpt < 1)
						tOpt = 6;
				}
				if (ch == KEY_LEFT || ch == KEY_ESC)
					goto search_function;
			} while (!(ch == KEY_ENTER || ch == KEY_ESC || ch == KEY_RIGHT));
			switch (tOpt)
			{
			case 1:
			{
				QuickSort(vector_student, 0, vector_student.size() - 1, 5);
				vector<Student> result, svp(vector_student);
				char cKey[50];
				DrawBoard(77, 1, 30);
				gotoxy(80, 10);
				textcolor(12);
				fflush(stdin);
				gets_s(cKey);
				textcolor(3);
				int i;
				while (Binary_search(svp, 0, svp.size(), cKey, 1) >= 0)
				{
					i = Binary_search(svp, 0, svp.size(), cKey, 1);
					result.push_back(svp[i]);
					svp.erase(svp.begin() + i);
				}
				if (result.empty())
				{
					gotoxy(90, 15);
					textcolor(12);
					printf("--------Khong tim thay ket qua %s!!!------\n", cKey);
					gotoxy(90, 16);
					textcolor(28);
					printf("-------Moi ban nhap lai tim kiem: --------");
					textcolor(3);
					_getch();
				}
				else
				{
					gotoxy(90, 5);
					textcolor(2);
					printf("Ket qua tim kiem %s: ", cKey);
					textcolor(3);
					PrintListStudent(result);
					_getch();
				}
				system("cls");
				DrawBoard(30, 3, 22);
				for (int t = 0; t < 3; t++)
				{
					gotoxy(32, 10 + 2 * t);
					printf("%s", menu_search[t]);
					textcolor(3);
				}
				//DrawBoard(0, 6, 27);
				for (int h = 0; h < 6; h++)
				{
					gotoxy(2, 10 + 2 * h);
					printf("%s", menu[h]);
					textcolor(3);
				}
				goto again6;
			}
			break;
			case 2:
			case 3:
			case 4:
			case 5:
			{
				QuickSort(vector_student, 0, vector_student.size() - 1, tOpt - 1);
				vector<Student> result, svp(vector_student);
				char cKey[50];
				DrawBoard(77, 1, 30);
				gotoxy(80, 10);
				textcolor(12);
				fflush(stdin);
				gets_s(cKey);
				textcolor(3);
				int i;
				while (Binary_search(svp, 0, svp.size(), cKey, tOpt) >= 0)
				{
					i = Binary_search(svp, 0, svp.size(), cKey, tOpt);
					result.push_back(svp[i]);
					svp.erase(svp.begin() + i);
				}
				if (result.empty())
				{
					gotoxy(90, 15);
					textcolor(12);
					printf("--------Khong tim thay ket qua %s!!!------", cKey);
					gotoxy(90, 16);
					textcolor(28);
					printf("-------Moi ban nhap lai tim kiem: --------");
					textcolor(3);
					_getch();
				}
				else
				{
					gotoxy(90, 5);
					textcolor(2);
					printf("Ket qua tim kiem %s: ", cKey);
					textcolor(3);
					PrintListStudent(result);
					_getch();
					system("cls");
				}
			}
			break;
			case 6:
				goto search_function;
				break;
			default:
				break;
			}
			system("cls");
			DrawBoard(30, 3, 22);
			for (int t = 0; t < 3; t++)
			{
				gotoxy(32, 10 + 2 * t);
				printf("%s", menu_search[t]);
				textcolor(3);
			}
			//DrawBoard(0, 6, 27);
			for (int h = 0; h < 6; h++)
			{
				gotoxy(2, 10 + 2 * h);
				printf("%s", menu[h]);
				textcolor(3);
			}
			goto again6;
		}
		case 3:
			system("cls");
			goto main_menu;
			break;
		}

	}break;
	case 5://thống kê
		do {
			Statistic(vector_student, x);
			goto main_menu;
		} while (!(ch == KEY_ENTER || ch == KEY_ESC));
		break;
	case 6://thoát
		system("cls");
		cout << "\n\n" << endl;
		gotoxy(45, 2);
		cout << "HOC, HOC NUA, HOC MAI!!!!!" << endl;
		textcolor(12);
		cout << "\n\nAn phim bat ki de thoat...";
		_getch();
		break;
	}
	return 0;
}