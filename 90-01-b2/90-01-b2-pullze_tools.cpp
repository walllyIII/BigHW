/* 2452839 徐川 计科 */
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#include<iostream>
#include<cstring>
#include"90-01-b2-pullze.h"
#include <iomanip>
using namespace std;

static void matrix_N(int ma[][20],int che[][20],int r,int z)
{
    cout << "+-+"; for (int i = 1; i <= r; i++) { cout << "--"; if (i % 5 == 0)cout << "-+"; }cout << endl;
    cout << "| |"; for (int i = 1; i <= r; i++) { cout << " " << (char)('a' + i - 1); if (i % 5 == 0) cout << " |"; } cout << endl;
    cout << "+-+"; for (int i = 1; i <= r; i++) { cout << "--"; if (i % 5 == 0)cout << "-+"; } cout << endl;
    for (int i = 1; i <= r; i++) {
        cout << "|" << (char)('A' + i - 1) << "|";
		for (int j = 1; j <= r; j++) { 
            if (che[i - 1][j - 1]) {
                if (z) {
					if (ma[i - 1][j - 1]) {
						cout << ' ';
						cct_setcolor(COLOR_WHITE, COLOR_BLUE);
						cout << 'O';
						cct_setcolor();
					}
					else {
						cout << ' ';
						cct_setcolor(COLOR_WHITE, COLOR_BLUE);
						cout << 'X';
						cct_setcolor();
					}
                }
                else {
                    cout << ' ';
                    cct_setcolor(COLOR_WHITE, COLOR_BLUE);
                    cout << 'O';
                    cct_setcolor();
                }
                cct_setcolor();
            }
            else {
				if (ma[i - 1][j - 1] && z)
					cout << " O";
				else
					cout << "  ";
            }
			if (j % 5 == 0)
                cout << " |";
        }
        if (i % 5 == 0) {
            cout << endl; 
            cout <<"+-+"; for (int j = 1; j <= r; j++) { cout << "--"; if (j % 5 == 0)cout << "-+"; }
        }
        cout << endl;
    }
    return;
}

static void matrix_A(int ma[][20], int che[][20], int line[][20], int row[][20], int r, int z)
{
    for (int i = 1; i <= row[19][0]; i++) { cout << "--"; }
    cout << "---+"; for (int i = 1; i <= r; i++) { cout << "--"; if (i % 5 == 0)cout << "-+"; } cout << endl;
    

    for (int i = 1; i <= line[19][0]; i++) {
        cout << "   ";
        for (int i = 1; i <= row[19][0]; i++) { cout << "  "; }
        cout << "|";
        for (int j = 1; j <= r; j++) { if (line[j - 1][i])cout <<right<< setw(2) << line[j - 1][i]; else cout << "  "; if (j % 5 == 0)cout << " |"; }
        cout << endl;
    }
    for (int i = 1; i <= row[19][0] + 1; i++) { cout << "--"; }cout << "-+"; for (int i = 1; i <= r; i++) { cout << "--"; if (i % 5 == 0)cout << "-+"; }cout << endl;
    for (int i = 1; i <= row[19][0] + 1; i++) { cout << "  "; }cout << " |"; for (int i = 1; i <= r; i++) { cout << " " << (char)('a' + i - 1); if (i % 5 == 0) cout << " |"; } cout << endl;
    for (int i = 1; i <= 2 * row[19][0] + 1; i++) { cout << "-"; }cout << "+-+"; for (int i = 1; i <= r; i++) { cout << "--"; if (i % 5 == 0)cout << "-+"; } cout << endl;
    for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= row[19][0]; j++) {
			if (row[i - 1][j]) {
				cout << setw(2) << row[i - 1][j];
			}
			else {
				cout << "  ";
			}
		}
        cout << " |" << (char)('A' + i - 1) << "|";
        for (int j = 1; j <= r; j++) {
            
            if (che[i - 1][j - 1]) {
                if (z) {
                    if (ma[i - 1][j - 1]) {
                        cout << ' ';
                        cct_setcolor(COLOR_WHITE, COLOR_BLUE);
                        cout << 'O';
                        cct_setcolor();
                    }
                    else {
                        cout << ' ';
                        cct_setcolor(COLOR_WHITE, COLOR_BLUE);
                        cout << 'X';
                        cct_setcolor();
                    }
                }
                else {
                    cout << ' ';
                    cct_setcolor(COLOR_WHITE, COLOR_BLUE);
                    cout << 'O';
                    cct_setcolor();
                }
                cct_setcolor();
            }
            else {
                if (ma[i - 1][j - 1] && z)
                    cout << " O";
                else
                    cout << "  ";
            }
            if (j % 5 == 0)
                cout << " |";
        }
        if (i % 5 == 0) {
            cout << endl;
            for (int i = 1; i <= 2 * row[19][0] + 1; i++) { cout << "-"; }
            cout << "+-+"; for (int j = 1; j <= r; j++) { cout << "--"; if (j % 5 == 0)cout << "-+"; }
        }
        cout << endl;
    }
    return;
}

bool tranXY(int& x, int& y,int Aax,int Aay,int r)
{
    int kmx[200] = { 0 };
    int kmy[200] = { 0 };
    for (int i = 0; i <= (r-1)*8; i+=8) {
        kmx[i + 2] = (int)(i / 8)+1; kmx[i + 3] = (int)(i / 8) + 1; kmx[i + 4] = (int)(i / 8) + 1;
        kmx[i + 5] = (int)(i / 8)+1; kmx[i + 6] = (int)(i / 8) + 1; kmx[i + 7] = (int)(i / 8) + 1;
    }
    
    for (int i = 0; i <= (r-1)*4; i+=4) {
        kmy[i + 1] = (int)(i / 4) + 1; kmy[i + 2] = (int)(i / 4) + 1; kmy[i + 3] = (int)(i / 4) + 1;
    }

    if (x < Aax || y < Aay)return 0;
    x = kmx[x - Aax];
    y = kmy[y - Aay];
    return x && y;
}

void solve(char ch)
{
    int r, ma[20][20] = { 0 }, line[20][20] = {0}, row[20][20] = {0},x,y;
    int che[20][20] = { 0 };
    char s[20];
	if (ch == 'A') {
		cct_cls();
        read(r);
        gene(ma,r);
        cout << "初始数组：" << endl;
        cct_getxy(x, y);
        matrix_N(ma, che,r,1);
        ending();
	}
    if (ch == 'B') {
        cct_cls();
        read(r);
        gene(ma, r);
        get_lr(line,row,r,ma);
        cout << "初始数组：" << endl;
        matrix_A(ma, che, line, row, r, 1);
        ending();
    }
    if (ch == 'C') {
        int z=0,c;
        cct_cls();
        read(r);
        gene(ma, r);
        get_lr(line, row, r, ma);
        cout << "初始数组：" << endl;
        matrix_A(ma, che, line, row, r, 0);
        c=getchar();
        while (1) {
            while (1) {
                cout << endl << endl;
				showpenal();
				fgets(s, sizeof(s), stdin);
				if (chei(s, r)) {
					break;
				}
				else {
					cout << "输入错误" << endl;
				}
			}
            if (s[0] == 'X' || s[0] == 'x')
                break;
            if (s[0] == 'Y' || s[0] == 'y') {
                if (check(ma, che,r)) {
                    cout << "提交成功，游戏结束" << endl;
                    break;
                }
                else {
                    cout << "提交错误, 可用作弊模式查看" << endl;
                    continue;
                }
            }
            if (s[0] == 'Z' || s[0] == 'z') {
                cout << "输入Z/z后：" << endl;
                z = (z + 1) % 2;
                matrix_A(ma, che, line, row, r, z);
                continue;
            }
            che[s[0] - 'A'][s[1] - 'a'] = (che[s[0] - 'A'][s[1] - 'a'] + 1) % 2;
            cout << "输入" << s[0] << s[1] << "后：" << endl;
            matrix_A(ma, che, line, row, r, z);

        }
        ending();
    }
    if (ch == 'D') {
        cct_cls();
        read(r);
        gene(ma, r);
        show_N(ma, r);
    }
    if (ch == 'E') {
        cct_cls();
        cct_setcolor();
        cct_setconsoleborder(120, 50, 120, 200);
        read(r);
        cct_cls();
        gene(ma, r);
        get_lr(line, row, r, ma);
        show_A(ma, che,line, row, r,0,1,1);
        cct_setcolor();
        ending();
    }
    if (ch == 'F') {
        cct_cls();
        cct_setcolor();
        read(r);
        gene(ma, r);
        get_lr(line, row, r, ma);
        cct_cls();
        cct_setfontsize("新宋体", 36);
        cct_setconsoleborder(120, 50, 120, 200);
        cout << "测试键盘/鼠标左键/右键，按回车退出" << endl;
        show_A(ma, che,line, row, r,0,1,1);
        int Aax = 6 + 2 * row[19][0], Aay = 4 + line[19][0];
        cct_getxy(x, y);
        cct_enable_mouse();
        while (1) {
            int MX, MY, MAction, keycode1, keycode2,situ;
            situ=cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
            cct_gotoxy(x + row[19][0] + 1, y); cct_setcolor(); cout << "                          ";
            cct_gotoxy(x + row[19][0] + 1, y);
            if (situ) {
               if (keycode1==13 && keycode2==0) {
                    cout << "[读到回车键]";
                    break;
                }
                else {
                    cout << "[读到键码]" << keycode1 << '/' << keycode2;
                }
            }
            else {
				cout << "[";
				if (MAction == MOUSE_LEFT_BUTTON_CLICK)cout << "读到左键";
				if (MAction == MOUSE_RIGHT_BUTTON_CLICK)cout << "读到右键";
				if (MAction != MOUSE_LEFT_BUTTON_CLICK && MAction != MOUSE_RIGHT_BUTTON_CLICK && MAction != MOUSE_NO_ACTION)cout << "当前鼠标";
				cout << "] ";
				if (MX >= Aax && MX <= Aax + r * 2 && MY >= Aay && MY <= Aay + r - 1) {
					cout << (char)('A' + (int)((MY - Aay))) << "行" << (char)('a' + (int)((MX - Aax) / 2)) << "列";
				}
				else {
					cout << "位置非法";
				}
            }
        }
        cct_disable_mouse();
        cct_setcolor();
        ending();
    }
    if (ch == 'G') {
		cct_cls();
		cct_setcolor();
		read(r);
		gene(ma, r);
		get_lr(line, row, r, ma);
		cct_cls();
		cct_setfontsize("新宋体", 36);
		cct_setconsoleborder(150, 1000, 150, 300);
		cout << "左键选〇 / 右键选×, Y / y提交, Z / z作弊, Q / q结束" << endl;
        int z = 0;
		show_A(ma, che, line, row, r, 0, 1, z,1);
		int Aax = 8 + 2 * row[19][0], Aay = 5 + line[19][0];
		cct_getxy(x, y);
		cct_enable_mouse();
		while (1) {
			int MX, MY, MAction, keycode1, keycode2, situ;
			situ = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
			cct_gotoxy(x + row[19][0] + 1, y); cct_setcolor(); cout << "                               ";
			cct_gotoxy(x + row[19][0] + 1, y);
			if (situ) {
                if ((keycode1 == 'Z' && keycode2 == 0) || (keycode1 == 'z' && keycode2 == 0)) {
                    if (!z)cout << "作弊模式开";
                    else cout << "作弊模式关";
                    z = (z + 1) % 2;
                    show_A(ma, che, line, row, r, 0, 1, z,1);
                    continue;
                }
                else if ((keycode1 == 'Y' && keycode2 == 0) || (keycode1 == 'y' && keycode2 == 0)) {
                    cout << "读到提交键" << endl;
                    if (check(ma, che, r)) {
                        cout << "提交成功，游戏结束" << endl;
                        break;
                    }
                    else {
                        cct_gotoxy(x + row[19][0] + 1, y); cct_setcolor();
                        cout << "提交错误, 可用作弊模式查看" << endl;
                        continue;
                    }
                }
                else if ((keycode1 == 'Q' && keycode2 == 0) || (keycode1 == 'q' && keycode2 == 0)) {
                    cout << "[读到Q/q，游戏结束]";
                    break;
                }else
				    cout << "[读到键码]" << keycode1 << '/' << keycode2;
			}
			else {
				cout << "[";
				if (MAction == MOUSE_LEFT_BUTTON_CLICK)cout << "读到左键";
				if (MAction == MOUSE_RIGHT_BUTTON_CLICK)cout << "读到右键";
				if (MAction != MOUSE_LEFT_BUTTON_CLICK && MAction != MOUSE_RIGHT_BUTTON_CLICK && MAction != MOUSE_NO_ACTION)cout << "当前鼠标";
				cout << "] ";
				if (MX >= Aax && MX <= Aax + r * 2 && MY >= Aay && MY <= Aay + r - 1) {
					cout << (char)('A' + (int)((MY - Aay))) << "行" << (char)('a' + (int)((MX - Aax) / 2)) << "列";
					if (MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_RIGHT_BUTTON_CLICK) {
						int nowy = (int)((MX - Aax) / 2), nowx = MY - Aay;
						int mval = MAction == MOUSE_LEFT_BUTTON_CLICK ? 1 : -1;
						if (mval == che[nowx][nowy]) {
							che[nowx][nowy] = 0;
						}
						else {
							che[nowx][nowy] = mval;
						}
						show_A(ma, che, line, row, r, 0, 1, z, 1);
					}
                }
				else {
					cout << "位置非法";
				}
                
				
			}
            
		}
		cct_disable_mouse();
		cct_setcolor();
		ending();
    }
    if (ch == 'H') {
        cct_cls();
        read(r);
        gene(ma, r);
        show_N_P(ma, r);
    }
    if (ch == 'I') {
        cct_cls();
        cct_setcolor();
        cct_setconsoleborder(120, 50, 120, 200);
        read(r);
        cct_cls();
        gene(ma, r);
        get_lr(line, row, r, ma);
        show_A_P(ma, che, line, row, r, 0, 1, 1);
        cct_setcolor();
        ending();
    }
    if (ch == 'J') {
        cct_cls();
        cct_setcolor();
        read(r);
        gene(ma, r);
        get_lr(line, row, r, ma);
        cct_cls();
        int m;
        if (r == 5)m = 24; if (r == 10)m = 16; if (r == 15)m = 10;
        cct_setfontsize("新宋体", m);
        cct_setconsoleborder(28 + r * 8, 60 + r * 6, 28 + r * 8, 60 + r * 6);
        cout << "测试键盘/鼠标左键/右键，按回车退出" << endl;
        show_A_P(ma, che, line, row, r, 0, 1, 1);
        int Aax = 6 + 2 * row[19][0], Aay =4+line[19][0];
        cct_getxy(x, y);
        cct_enable_mouse();
        while (1) {
            int MX, MY, MAction, keycode1, keycode2, situ;
            situ = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
            cct_gotoxy(x + row[19][0] + 1, y+1); cct_setcolor(); cout << "                          ";
            cct_gotoxy(x + row[19][0] + 1, y+1);
            if (situ) {
                if (keycode1 == 13 && keycode2 == 0) {
                    cout << "[读到回车键]";
                    break;
                }
                else {
                    cout << "[读到键码]" << keycode1 << '/' << keycode2;
                }
            }
            else {
                cout << "[";
                if (MAction == MOUSE_LEFT_BUTTON_CLICK)cout << "读到左键";
                if (MAction == MOUSE_RIGHT_BUTTON_CLICK)cout << "读到右键";
                if (MAction != MOUSE_LEFT_BUTTON_CLICK && MAction != MOUSE_RIGHT_BUTTON_CLICK && MAction != MOUSE_NO_ACTION)cout << "当前鼠标";
                cout << "] ";
                //MX = Aax + (MX - Aax) / 6;MY = Aay + (MY - Aay) / 6;
                if (tranXY(MX,MY,Aax,Aay,r)) {
                    MX--; MY--;
                    cout << (char)('A' + MY) << "行" << (char)('a' + MX) << "列";
                }
                else {
                    cout << "位置非法";
                }
            }
        }
        cct_disable_mouse();
        cct_setcolor();
        ending();
    }
    if (ch == 'K') {
        cct_cls();
        cct_setcolor();
        read(r);
        gene(ma, r);
        get_lr(line, row, r, ma);
        cct_cls();
        int m=24;
        if (r == 5)m = 24; if (r == 10)m = 16; if (r == 15)m = 10;
        cct_setfontsize("新宋体", m);
        cct_setconsoleborder(28 + r * 8, 60 + r * 6, 28 + r * 8, 60 + r * 6);
        cout << "左键选〇 / 右键选×, Y / y提交, Z / z作弊, Q / q结束" << endl;
        int z = 0;
        show_A_P(ma, che, line, row, r, 0, 1, z, 1);
        int Aax = 6 + 2 * row[19][0], Aay = 4 + line[19][0];
        cct_getxy(x, y);
        cct_enable_mouse();
        while (1) {
            int MX, MY, MAction, keycode1, keycode2, situ;
            situ = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
            cct_gotoxy(x + row[19][0] + 1, y+1); cct_setcolor(); cout << "                               ";
            cct_gotoxy(x + row[19][0] + 1, y+1);
            if (situ) {
                if ((keycode1 == 'Z' && keycode2 == 0) || (keycode1 == 'z' && keycode2 == 0)) {
                    if (!z)cout << "作弊模式开";
                    else cout << "作弊模式关";
                    z = (z + 1) % 2;
                    show_A_P(ma, che, line, row, r, 0, 1, z, 1);
                    continue;
                }
                else if ((keycode1 == 'Y' && keycode2 == 0) || (keycode1 == 'y' && keycode2 == 0)) {
                    cout << "读到提交键" << endl;
                    if (check(ma, che, r)) {
                        cout << "提交成功，游戏结束" << endl;
                        break;
                    }
                    else {
                        cct_gotoxy(x + row[19][0] + 1, y); cct_setcolor();
                        cout << "提交错误, 可用作弊模式查看" << endl;
                        continue;
                    }
                }
                else if ((keycode1 == 'Q' && keycode2 == 0) || (keycode1 == 'q' && keycode2 == 0)) {
                    cout << "[读到Q/q，游戏结束]";
                    break;
                }
                else
                    cout << "[读到键码]" << keycode1 << '/' << keycode2;
            }
            else {
                cout << "[";
                if (MAction == MOUSE_LEFT_BUTTON_CLICK)cout << "读到左键";
                if (MAction == MOUSE_RIGHT_BUTTON_CLICK)cout << "读到右键";
                if (MAction != MOUSE_LEFT_BUTTON_CLICK && MAction != MOUSE_RIGHT_BUTTON_CLICK && MAction != MOUSE_NO_ACTION)cout << "当前鼠标";
                cout << "] ";
                if (tranXY(MX, MY, Aax, Aay, r)) {
                    MX--; MY--;
                    cout << (char)('A' + MY) << "行" << (char)('a' + MX) << "列";
                    
					if (MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_RIGHT_BUTTON_CLICK) {
						int nowy = MX, nowx = MY;
						int mval = MAction == MOUSE_LEFT_BUTTON_CLICK ? 1 : -1;
						if (mval == che[nowx][nowy]) {
							che[nowx][nowy] = 0;
						}
						else {
							che[nowx][nowy] = mval;
						}
						show_A_P(ma, che, line, row, r, 0, 1, z, 1);
					}
                }
                else {
                    cout << "位置非法";
                }
            }

        }
        cct_disable_mouse();
        cct_setcolor();
        ending();
    }
}