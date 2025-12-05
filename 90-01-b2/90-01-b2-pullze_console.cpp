/* 2452839 徐川 计科 */
#include<iostream>
#include<cstdio>
#include<iomanip>
#include"90-01-b2-pullze.h"
using namespace std;
void show_N(int ma[][20],int r)
{
	cct_cls();
	int x, y;
	cct_setfontsize("新宋体", 36);
	cct_setconsoleborder(7 + r * 2, 12 + r, 7 + r * 2, 12 + r);
	cct_gotoxy(0, 0);
	cout << endl<<"   ";
	for (int i = 1; i <= r; i++) {
		cout << " " << (char)('a' + i - 1);
	}
	cout << endl << "  ";
	cct_getxy(x, y);cct_showstr(x, y, "╔", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y);cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, r); 
	cct_getxy(x, y);cct_showstr(x, y, "╗", COLOR_WHITE, COLOR_BLACK); cout << endl;
	for (int i = 1; i <= r; i++) {
		cct_setcolor();
		cout << (char)('A' + i - 1) << " ";
		cct_getxy(x, y);cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
		for (int j = 1; j <= r; j++) {
			if (ma[i - 1][j - 1]) {
				cct_getxy(x, y);cct_showstr(x, y, "○", COLOR_HBLUE, COLOR_BLACK);
			}
			else {
				cct_getxy(x, y);cct_showstr(x, y, "  ", COLOR_WHITE, COLOR_BLACK);
			}
		}
		cct_getxy(x, y);cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
		cout << endl;
	}
	cct_setcolor();
	cout << "  ";
	cct_getxy(x, y);cct_showstr(x, y, "╚", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y);cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, r);
	cct_getxy(x, y);cct_showstr(x, y, "╝", COLOR_WHITE, COLOR_BLACK); cout << endl;
	cct_setcolor();
	ending();
	return;
}

void show_A(int ma[][20], int che[][20],int line[][20], int row[][20], int r,int x,int y,int z,int f)
{
	cct_gotoxy(x, y);
	cct_getxy(x, y);cct_showstr(x, y, " ", COLOR_BLACK, COLOR_WHITE,6+row[19][0]*2);
	cct_getxy(x, y);cct_showstr(x, y, "╔", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y);cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, r);
	cct_getxy(x, y);cct_showstr(x, y, "╗", COLOR_WHITE, COLOR_BLACK); cout << endl;
	for (int i = 1; i <= line[19][0]; i++) {
		cct_getxy(x, y);cct_showstr(x, y, " ", COLOR_BLACK, COLOR_WHITE, 6 + row[19][0] * 2);
		cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
		for (int j = 1; j <= r; j++) {
			cct_setcolor(COLOR_WHITE, COLOR_BLACK);
			if (line[j - 1][i])cout <<right<<setw(2)<< line[j - 1][i]; else cout << "  ";
			cct_setcolor();
		}
		cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
		cout << endl;
	}
	cct_getxy(x, y); cct_showstr(x, y, " ", COLOR_BLACK, COLOR_WHITE, 6 + row[19][0] * 2);
	cct_getxy(x, y); cct_showstr(x, y, "╠", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, r);
	cct_getxy(x, y); cct_showstr(x, y, "╣", COLOR_WHITE, COLOR_BLACK); cout << endl;

	cct_getxy(x, y); cct_showstr(x, y, " ", COLOR_BLACK, COLOR_WHITE, 6 + row[19][0] * 2);
	cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
	for (int i = 1; i <= r; i++) {
		cct_setcolor(COLOR_WHITE, COLOR_BLACK);
		cout << " " << (char)('a' + i - 1);
		cct_setcolor();
	}
	cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK); cout << endl ;

	cct_getxy(x, y);cct_showstr(x, y, "╔", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y);cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, row[19][0]);
	cct_getxy(x, y);cct_showstr(x, y, "╦", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y);cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "╬", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK,r);
	cct_getxy(x, y); cct_showstr(x, y, "╣", COLOR_WHITE, COLOR_BLACK); cout << endl;
	for (int i = 1; i <= r; i++) {
		cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
		for (int j = 1; j <= row[19][0]; j++) {
			cct_setcolor(COLOR_WHITE, COLOR_BLACK);
			if (row[i - 1][j]) {
				cout << left<<setw(2)<<row[i - 1][j];
			}
			else {
				cout << "  ";
			}
			cct_setcolor();
		}
		cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
		cct_setcolor(COLOR_WHITE, COLOR_BLACK);
		cout<< " " << (char)('A' + i - 1) ;
		cct_setcolor();
		cct_getxy(x, y);cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
		for (int j = 1; j <= r; j++) {
			if (che[i - 1][j - 1]!=0)
			{
				if (z) {
					if (ma[i - 1][j - 1]) {
						if (che[i - 1][j - 1] == 1) {
							cct_getxy(x, y); cct_showstr(x, y, "○", COLOR_HBLUE, COLOR_BLACK);
						}
						else {
							cct_getxy(x, y); cct_showstr(x, y, "×", COLOR_HBLUE, COLOR_BLACK);
						}
					}
					else {
						if (che[i - 1][j - 1] == 1) {
							cct_getxy(x, y); cct_showstr(x, y, "○", COLOR_HRED, COLOR_BLACK);
						}
						else {
							cct_getxy(x, y); cct_showstr(x, y, "×", COLOR_HRED, COLOR_BLACK);
						}
					}
				}
				else {
					if (che[i - 1][j - 1] == 1) {
						cct_getxy(x, y); cct_showstr(x, y, "○", COLOR_HBLUE, COLOR_BLACK);
					}
					else {
						cct_getxy(x, y); cct_showstr(x, y, "×", COLOR_HRED, COLOR_BLACK);
					}
				}
			}
			else {
				if (ma[i - 1][j - 1] && z) {
					if (f) {
						cct_getxy(x, y); cct_showstr(x, y, "○", COLOR_HWHITE, COLOR_BLACK);
					}
					else {
						cct_getxy(x, y); cct_showstr(x, y, "○", COLOR_HBLUE, COLOR_BLACK);
					}
					 
				}
				else {
					cct_getxy(x, y); cct_showstr(x, y, "  ", COLOR_WHITE, COLOR_BLACK);
				}
			}
			
		}
		cct_getxy(x, y);cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
		cout << endl;
	}
	cct_setcolor();
	cct_getxy(x, y); cct_showstr(x, y, "╚", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, row[19][0]);
	cct_getxy(x, y); cct_showstr(x, y, "╩", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "╩", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, r);
	cct_getxy(x, y); cct_showstr(x, y, "╝", COLOR_WHITE, COLOR_BLACK); cout << endl;
	return;
	return;
}

void draw_p(int x, int y, int color, int type)
{
	if (type == 1) {
		cct_showstr(x, y, "╔═╗", color, COLOR_BLACK);
		cct_showstr(x, y+1, "║○║", color, COLOR_BLACK);
		cct_showstr(x, y+2, "╚═╝", color, COLOR_BLACK);
		cct_gotoxy(x+6, y);
	}
	if (type == -1) {
		cct_showstr(x, y, "╔═╗", color, COLOR_BLACK);
		cct_showstr(x, y+1, "║×║", color, COLOR_BLACK);
		cct_showstr(x, y+2, "╚═╝", color, COLOR_BLACK);
		cct_gotoxy(x+6, y);
	}
	if (type == 0) {
		cct_showstr(x, y, "      ", color, COLOR_BLACK);
		cct_showstr(x, y+1, "      ", color, COLOR_BLACK);
		cct_showstr(x, y+2, "      ", color, COLOR_BLACK);
		cct_gotoxy(x+6, y);
	}
}

void show_N_P(int ma[][20], int r)
{
	int x, y,m=16;
	if (r == 5)m = 24; if (r == 10)m = 16; if (r == 15)m = 10;
	cct_setfontsize("新宋体", m);
	cct_setconsoleborder(18 + r * 8, 50 + r*6, 18 + r * 8, 50 + r*6);
	cct_gotoxy(0, 0);
	cout << endl << "   ";
	for (int i = 1; i <= r; i++) {
		cout << "   " << (char)('a' + i - 1)<<"    ";
	}
	cout << endl << "  ";
	cct_getxy(x, y); cct_showstr(x, y, "╔", COLOR_WHITE, COLOR_BLACK);
	for (int j = 1; j <= r; j++) {
		cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, 3);
		if (j == r)break;
		cct_getxy(x, y); cct_showstr(x, y, "╦", COLOR_WHITE, COLOR_BLACK);
	}
	cct_getxy(x, y); cct_showstr(x, y, "╗", COLOR_WHITE, COLOR_BLACK); cout << endl;
	for (int i = 1; i <= r; i++) {
		for (int k = 1; k <= 3; k++) {
			cct_setcolor();
			if (k == 2)cout << (char)('A' + i - 1) << " ";
			else cout << "  ";
			cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
			for (int j = 1; j <= r; j++) {
				if (k == 1) {
					if (ma[i - 1][j - 1]) {
						cct_getxy(x, y); draw_p(x, y, COLOR_HBLUE, 1);
					}
					else {
						cct_getxy(x, y); draw_p(x, y, COLOR_WHITE, 0);
					}
				}
				else {
					cct_gotoxy(x + 8, y);
				}
				cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
			}
			cout << endl;
		}
		if (i == r)break;
		cct_setcolor();
		cout << "  ";
		cct_getxy(x, y); cct_showstr(x, y, "╠", COLOR_WHITE, COLOR_BLACK);
		for (int j = 1; j <= r; j++) {
			cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, 3);
			if (j == r)break;
			cct_getxy(x, y); cct_showstr(x, y, "╬", COLOR_WHITE, COLOR_BLACK);
		}
		cct_getxy(x, y); cct_showstr(x, y, "╣", COLOR_WHITE, COLOR_BLACK); cout << endl;
	}
	cct_setcolor();
	cout << "  ";
	cct_getxy(x, y); cct_showstr(x, y, "╚", COLOR_WHITE, COLOR_BLACK);
	for (int j = 1; j <= r; j++) {
		cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, 3);
		if (j == r)break;
		cct_getxy(x, y); cct_showstr(x, y, "╩", COLOR_WHITE, COLOR_BLACK);
	}
	cct_getxy(x, y); cct_showstr(x, y, "╝", COLOR_WHITE, COLOR_BLACK); 
	cct_setcolor();
	cout << endl;
	ending();
	return;
}

void show_A_P(int ma[][20], int che[][20], int line[][20], int row[][20], int r, int x, int y, int z, int f)
{
	cct_gotoxy(x, y);
	
	cct_showstr(x, y, " ", COLOR_BLACK, COLOR_WHITE, 6 + row[19][0] * 2);
	cct_getxy(x, y); cct_showstr(x, y, "╔", COLOR_WHITE, COLOR_BLACK);
	for (int i = 1; i <= r; i++) {
		cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, 3);
		if (i == r)break;
		cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK);
	}
	cct_getxy(x, y); cct_showstr(x, y, "╗", COLOR_WHITE, COLOR_BLACK); cout << endl;

	for (int i = 1; i <= line[19][0]; i++) {
		cct_getxy(x, y); cct_showstr(x, y, " ", COLOR_BLACK, COLOR_WHITE, 6 + row[19][0] * 2);
		cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
		for (int j = 1; j <= r; j++) {
			cct_setcolor(COLOR_WHITE, COLOR_BLACK);
			cout << "  ";
			if (line[j - 1][i])cout << left << setw(2) << line[j - 1][i]; else cout << "  ";
			cout << "  ";
			if (j == r)break;
			cout << "  ";
			cct_setcolor();
		}
		cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
		cout << endl;
	}

	cct_getxy(x, y); cct_showstr(x, y, " ", COLOR_BLACK, COLOR_WHITE, 6 + row[19][0] * 2);

	cct_getxy(x, y); cct_showstr(x, y, "╠", COLOR_WHITE, COLOR_BLACK);
	for (int i = 1; i <= r; i++) {
		cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, 3);
		if (i == r)break;
		cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK);
	}
	cct_getxy(x, y); cct_showstr(x, y, "╣", COLOR_WHITE, COLOR_BLACK); cout << endl;

	cct_getxy(x, y); cct_showstr(x, y, " ", COLOR_BLACK, COLOR_WHITE, 6 + row[19][0] * 2);
	cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
	for (int i = 1; i <= r; i++) {
		cct_setcolor(COLOR_WHITE, COLOR_BLACK);
		cout << "  " << (char)('a' + i - 1)<<"   ";
		if (i == r)break;
		cout << "  ";
		cct_setcolor();
	}
	cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK); cout << endl;

	cct_getxy(x, y); cct_showstr(x, y, "╔", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, row[19][0]);
	cct_getxy(x, y); cct_showstr(x, y, "╦", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "╬", COLOR_WHITE, COLOR_BLACK);

	for (int j = 1; j <= r; j++) {
		cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, 3);
		if (j == r)break;
		cct_getxy(x, y); cct_showstr(x, y, "╦", COLOR_WHITE, COLOR_BLACK);
	}
	cct_getxy(x, y); cct_showstr(x, y, "╣", COLOR_WHITE, COLOR_BLACK); cout << endl;

	for (int i = 1; i <= r; i++) {
		for (int k = 1; k <= 3; k++) {
			cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
			if (k == 2) {
				for (int j = 1; j <= row[19][0]; j++) {
					cct_setcolor(COLOR_WHITE, COLOR_BLACK);
					if (row[i - 1][j]) {
						cout << left << setw(2) << row[i - 1][j];
					}
					else {
						cout << "  ";
					}
					cct_setcolor();
				}
			}
			else {
				for (int j = 1; j <= row[19][0]; j++)
					cout << "  ";
			}
			cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
			cct_setcolor(COLOR_WHITE, COLOR_BLACK);
			if (k == 2)cout << " " << (char)('A' + i - 1);
			else cout << "  ";
			cct_setcolor();
			cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
			for (int j = 1; j <= r; j++) {
				if (k == 1) {
					if (che[i - 1][j - 1] != 0)
					{
						if (z) {
							if (ma[i - 1][j - 1]) {
								if (che[i - 1][j - 1] == 1) {
									cct_getxy(x, y); draw_p(x, y, COLOR_HBLUE, 1);//cct_showstr(x, y, "○", COLOR_HBLUE, COLOR_BLACK);
								}
								else {
									cct_getxy(x, y); draw_p(x, y, COLOR_HBLUE, -1);//cct_showstr(x, y, "×", COLOR_HBLUE, COLOR_BLACK);
								}
							}
							else {
								if (che[i - 1][j - 1] == 1) {
									cct_getxy(x, y); draw_p(x, y, COLOR_HRED, 1);//cct_showstr(x, y, "○", COLOR_HRED, COLOR_BLACK);
								}
								else {
									cct_getxy(x, y); draw_p(x, y, COLOR_HRED, -1);//cct_showstr(x, y, "×", COLOR_HRED, COLOR_BLACK);
								}
							}
						}
						else {
							if (che[i - 1][j - 1] == 1) {
								cct_getxy(x, y); draw_p(x, y, COLOR_HBLUE, 1);//cct_showstr(x, y, "○", COLOR_HBLUE, COLOR_BLACK);
							}
							else {
								cct_getxy(x, y); draw_p(x, y, COLOR_HRED, -1);//cct_showstr(x, y, "×", COLOR_HRED, COLOR_BLACK);
							}
						}
					}
					else {
						if (ma[i - 1][j - 1] && z) {
							if (f) {
								cct_getxy(x, y); draw_p(x, y, COLOR_HWHITE, 1);//cct_showstr(x, y, "○", COLOR_HWHITE, COLOR_BLACK);
							}
							else {
								cct_getxy(x, y); draw_p(x, y, COLOR_HBLUE, 1);//cct_showstr(x, y, "○", COLOR_HBLUE, COLOR_BLACK);
							}

						}
						else {
							cct_getxy(x, y); draw_p(x, y, COLOR_WHITE, 0);//cct_showstr(x, y, "  ", COLOR_WHITE, COLOR_BLACK);
						}
					}

				}
				else {
					cct_gotoxy(x + 8, y);
				}
				cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
			}
			//cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
			cout << endl;
			
		}
		if (i == r)break;
			cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
			cct_getxy(x, y); cct_showstr(x, y, "  ", COLOR_WHITE, COLOR_BLACK, row[19][0]);
			cct_getxy(x, y); cct_showstr(x, y, "║", COLOR_WHITE, COLOR_BLACK);
			cct_getxy(x, y); cct_showstr(x, y, "  ", COLOR_WHITE, COLOR_BLACK);
			cct_getxy(x, y); cct_showstr(x, y, "╠", COLOR_WHITE, COLOR_BLACK);
			for (int j = 1; j <= r; j++) {
				cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, 3);
				if (j == r)break;
				cct_getxy(x, y); cct_showstr(x, y, "╬", COLOR_WHITE, COLOR_BLACK);
			}
			cct_getxy(x, y); cct_showstr(x, y, "╣", COLOR_WHITE, COLOR_BLACK);
			cout << endl;
	}
	cct_setcolor();
	cct_getxy(x, y); cct_showstr(x, y, "╚", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, row[19][0]);
	cct_getxy(x, y); cct_showstr(x, y, "╩", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK);
	cct_getxy(x, y); cct_showstr(x, y, "╩", COLOR_WHITE, COLOR_BLACK);
	for (int j = 1; j <= r; j++) {
		cct_getxy(x, y); cct_showstr(x, y, "═", COLOR_WHITE, COLOR_BLACK, 3);
		if (j == r)break;
		cct_getxy(x, y); cct_showstr(x, y, "╩", COLOR_WHITE, COLOR_BLACK);
	}
	cct_getxy(x, y); cct_showstr(x, y, "╝", COLOR_WHITE, COLOR_BLACK);
	cct_setcolor();
	cout << endl;
	return;
}