/* 2452839 徐川 计科 */


/* ----------------------------------------------------------------------------------

     本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include <iomanip>
#include<cmath>
#include<Windows.h>
#include <conio.h>
#include "90-01-b1-hanoi.h"
#include "90-01-b1-hanoi_const_value.h"
#include "../include/cmd_console_tools.h"
#include "../include/cmd_hdc_tools.h"
using namespace std;
int cnt=0;
int head[3], pla[3][MAX_LAYER+2];
int slp;

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

void move_pl(char src, char dst, int k = 0);
static void prt(int s[])
{
    for (int i = 0; i < 10; i++) {
        if (!s[i])
            cout << "  ";
        else
            cout << setw(2) << s[i];
    }
    return;
}
static void sho(int T,char src, char dst, int n, int step=-1)
{
    if (T == 1) {
        cout << n << "# " << src << "---->" << dst << endl;
    }
    if (T == 2) {
        cout << "第" << setw(4) << step << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ")" << endl;
    }
    if (T == 3) {
        cout << "第" << setw(4) << step << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ") ";
        cout << " A:";
        prt(pla[0]);
        cout << " B:";
        prt(pla[1]);
        cout << " C:";
        prt(pla[2]);
        cout << endl;
    }
    if (T == 4) {
        cct_gotoxy(MenuItem4_Start_X + Underpan_A_X_OFFSET + (src - 'A') * Underpan_Distance - 1, MenuItem4_Start_Y + Underpan_A_Y_OFFSET - 2 - head[src - 'A']-1);
        cout << "  ";
        cct_gotoxy(MenuItem4_Start_X + Underpan_A_X_OFFSET + (dst - 'A') * Underpan_Distance - 1, MenuItem4_Start_Y + Underpan_A_Y_OFFSET - 2 - head[dst - 'A']);
        cout << setw(2) << pla[dst-'A'][head[dst-'A']];

        cct_gotoxy(MenuItem4_Start_X, MenuItem4_Start_Y);
        cout << "                                                                                                                       ";
        cct_gotoxy(MenuItem4_Start_X, MenuItem4_Start_Y);
        cout << "第" << setw(4) << step << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ") ";
        cout << " A:";
        prt(pla[0]);
        cout << " B:";
        prt(pla[1]);
        cout << " C:";
        prt(pla[2]);
        char ch;
        if (!slp)ch=_getch();
        else Sleep(slp);
    }
    if (T == 8) {
        cct_gotoxy(MenuItem8_Start_X + Underpan_A_X_OFFSET + (src - 'A') * Underpan_Distance - 1, MenuItem8_Start_Y + Underpan_A_Y_OFFSET - 2 - head[src - 'A'] - 1);
        cout << "  ";
        cct_gotoxy(MenuItem8_Start_X + Underpan_A_X_OFFSET + (dst - 'A') * Underpan_Distance - 1, MenuItem8_Start_Y + Underpan_A_Y_OFFSET - 2 - head[dst - 'A']);
        cout << setw(2) << pla[dst - 'A'][head[dst - 'A']];

        cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y);
        cout << "                                                                                                                       ";
        cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y);
        cout << "第" << setw(4) << step << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ") ";
        cout << " A:";
        prt(pla[0]);
        cout << " B:";
        prt(pla[1]);
        cout << " C:";
        prt(pla[2]);
        move_pl(src, dst);
        char ch;
        if (cnt <= 7) {
            if (!slp)ch=_getch();
            else Sleep(slp);
        }
    }
    if (T == 9) {
        cct_gotoxy(MenuItem8_Start_X + Underpan_A_X_OFFSET + (src - 'A') * Underpan_Distance - 1, MenuItem8_Start_Y + Underpan_A_Y_OFFSET - 2 - head[src - 'A'] - 1);
        cout << "  ";
        cct_gotoxy(MenuItem8_Start_X + Underpan_A_X_OFFSET + (dst - 'A') * Underpan_Distance - 1, MenuItem8_Start_Y + Underpan_A_Y_OFFSET - 2 - head[dst - 'A']);
        cout << setw(2) << pla[dst - 'A'][head[dst - 'A']];

        cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y);
        cout << "                                                                                                                       ";
        cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y);
        cout << "第" << setw(4) << step << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ") ";
        cout << " A:";
        prt(pla[0]);
        cout << " B:";
        prt(pla[1]);
        cout << " C:";
        prt(pla[2]);
        move_pl(src, dst,1);
        char ch;
        if (!slp)ch=_getch();
        else Sleep(slp);
    }
    return;
}

static void move_d(char src, char dst)
{
        head[dst - 'A']++;
		pla[dst - 'A'][head[dst - 'A']] = pla[src - 'A'][head[src - 'A']];
		pla[src - 'A'][head[src - 'A']] = 0;
		head[src - 'A']--;
}

static void hanoi(int n, char src, char tmp, char dst,int T)
{
	if (n == 1) {
		cnt++;
        move_d(src, dst);
        sho(T, src, dst, n, cnt);
		return;
	}
	hanoi(n - 1, src, dst, tmp,T);
	cnt++;
	move_d(src, dst);
    sho(T, src, dst, n, cnt);
	hanoi(n - 1, tmp, src, dst,T);
}

static void read(int &num,char &be,char &en)
{
    while (1) {
        cout << "请输入汉诺塔的层数(1-"<< MAX_LAYER <<")" << endl;
        cin >> num;

        if (cin.fail()) {
            cin.clear();
            while (getchar() != '\n');
        }
        else {
            while (getchar() != '\n');
            if (num >= 1 && num <= 10) {
                break;
            }

        }
    }
    while (1) {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> be;

        if (cin.fail()) {
            cin.clear();
            while (getchar() != '\n');
        }
        else {
            while (getchar() != '\n');
            if (be == 'A' || be == 'B' || be == 'C' || be == 'a' || be == 'b' || be == 'c') {
                break;
            }

        }
    }
    while (1) {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> en;

        if (cin.fail()) {
            cin.clear();
            while (getchar() != '\n');
        }
        else {
            while (getchar() != '\n');
            if (be == en || be == en + 'A' - 'a' || be == en - 'A' + 'a')
                cout << "目标柱(" << char(en > 95 ? en - 32 : en) << ")不能与起始柱(" << char(be > 95 ? be - 32 : be) << ")相同" << endl;
            else {
                if (en == 'A' || en == 'B' || en == 'C' || en == 'a' || en == 'b' || en == 'c') {
                    break;
                }
            }
        }
    }
    if (be > 95)be -= 32;
    if (en > 95)en -= 32;
    for (int i = 0; i < num; i++) {
        pla[be - 'A'][i] = num - i;
    }
    head[0] = -1;
    head[1] = -1;
    head[2] = -1;
    head[be - 'A'] = num - 1;
}

static void reset()
{
    cnt = 0;
    memset(pla, 0, sizeof(pla)); 
    memset(head, 0, sizeof(head));

}

static void print_base()
{
    hdc_rectangle(HDC_Start_X,
        HDC_Start_Y,
        23 * HDC_Base_Width,
        HDC_Base_High,
        0,1,1,HDC_COLOR[11]);
    Sleep(HDC_Init_Delay);
    hdc_rectangle(HDC_Start_X,
        HDC_Start_Y,
        23 * HDC_Base_Width,
        HDC_Base_High,
        0, 1, 1, HDC_COLOR[11]);

    hdc_rectangle(HDC_Start_X + 23 * HDC_Base_Width + HDC_Underpan_Distance,
        HDC_Start_Y,
        23 * HDC_Base_Width,
        HDC_Base_High,
        0, 1, 1, HDC_COLOR[11]);
    Sleep(HDC_Init_Delay);
    hdc_rectangle(HDC_Start_X + (23 * HDC_Base_Width + HDC_Underpan_Distance) * 2,
        HDC_Start_Y,
        23 * HDC_Base_Width,
        HDC_Base_High,
        0, 1, 1, HDC_COLOR[11]);
    Sleep(HDC_Init_Delay);
    hdc_rectangle(HDC_Start_X + 11 * HDC_Base_Width,
        HDC_Start_Y - HDC_Base_High * 12,
        HDC_Base_Width,
        HDC_Base_High * 12,
        0, 1, 1, HDC_COLOR[11]);
    Sleep(HDC_Init_Delay);
    hdc_rectangle(HDC_Start_X + 11 * HDC_Base_Width + 23 * HDC_Base_Width + HDC_Underpan_Distance,
        HDC_Start_Y - HDC_Base_High * 12,
        HDC_Base_Width,
        HDC_Base_High * 12,
        0, 1, 1, HDC_COLOR[11]);
    Sleep(HDC_Init_Delay);
    hdc_rectangle(HDC_Start_X + 11 * HDC_Base_Width + (23 * HDC_Base_Width + HDC_Underpan_Distance) * 2,
        HDC_Start_Y - HDC_Base_High * 12,
        HDC_Base_Width,
        HDC_Base_High * 12,
        0, 1, 1, HDC_COLOR[11]);
    Sleep(HDC_Init_Delay);
    
    for (int i = 0; i <= head[0]; i++) {
        hdc_rectangle(HDC_Start_X + (23 - (2 * pla[0][i] + 1)) / 2 * HDC_Base_Width,
            HDC_Start_Y - (1 + i) * HDC_Base_High,
            HDC_Base_Width * (2 * pla[0][i] + 1),
            HDC_Base_High,
            0, 1, 1, HDC_COLOR[pla[0][i]]);
        Sleep(HDC_Init_Delay);
    }
    for (int i = 0; i <= head[1]; i++) {
        hdc_rectangle(HDC_Start_X + (23 - (2 * pla[1][i] + 1)) / 2 * HDC_Base_Width + (23 * HDC_Base_Width + HDC_Underpan_Distance) * 1,
            HDC_Start_Y - (1 + i) * HDC_Base_High,
            HDC_Base_Width * (2 * pla[1][i] + 1),
            HDC_Base_High,
            0, 1, 1, HDC_COLOR[pla[1][i]]);
        Sleep(HDC_Init_Delay);
    }
    for (int i = 0; i <= head[2]; i++) {
        hdc_rectangle(HDC_Start_X + (23 - (2 * pla[2][i] + 1)) / 2 * HDC_Base_Width + (23 * HDC_Base_Width + HDC_Underpan_Distance) * 2,
            HDC_Start_Y - (1 + i) * HDC_Base_High,
            HDC_Base_Width * (2 * pla[2][i] + 1),
            HDC_Base_High,
            0, 1, 1, HDC_COLOR[pla[2][i]]);
        Sleep(HDC_Init_Delay);
    }

    return;
}

void move_pl(char src, char dst,int k)
{
    char ch;
    int v_x = HDC_Step_X * (((int(src - dst)) > 0 )? -1 : 1), v_y = HDC_Step_Y;
    int now_x = HDC_Start_X + (23 - (2 * pla[dst - 'A'][head[dst - 'A']] + 1)) / 2 * HDC_Base_Width + (23 * HDC_Base_Width + HDC_Underpan_Distance) * (src - 'A');
    int now_y = HDC_Start_Y - (1 + head[src-'A'] + 1) * HDC_Base_High;
    while (now_y > HDC_Top_Y) {
        hdc_rectangle(now_x,
            now_y + HDC_Base_High - v_y,
            HDC_Base_Width * (2 * pla[dst - 'A'][head[dst - 'A']] + 1),
            v_y,
            0, 1, 1, HDC_COLOR[0]);
        if (now_y >= HDC_Start_Y - HDC_Base_High * 13) {
            hdc_rectangle(now_x + HDC_Base_Width * (pla[dst - 'A'][head[dst - 'A']]),
                now_y + HDC_Base_High - v_y,
                HDC_Base_Width,
                v_y,
                0, 1, 1, HDC_COLOR[11]);
        }
        now_y -= v_y;
        hdc_rectangle(now_x,
            now_y,
            HDC_Base_Width * (2 * pla[dst - 'A'][head[dst - 'A']] + 1),
            v_y,
            0, 1, 1, HDC_COLOR[pla[dst - 'A'][head[dst - 'A']]]);
        if (!k) {
            if (cnt <= 7) {
                if (!slp)ch=_getch();
                else Sleep(slp);
            }
        }
        else {
            if (!slp)ch=_getch();
            else Sleep(slp);
        }
    }
    for(int i=1;i<= (23 * HDC_Base_Width + HDC_Underpan_Distance)*abs(src-dst)/abs(v_x);i++){
        if (v_x > 0) {
            hdc_rectangle(now_x,
            now_y,
            v_x,
            HDC_Base_High,
                0, 1, 1, HDC_COLOR[0]);
            now_x += v_x;
            hdc_rectangle(now_x+ HDC_Base_Width * (2 * pla[dst - 'A'][head[dst - 'A']]+1)-v_x,
            now_y,
            v_x,
            HDC_Base_High,
                0, 1, 1, HDC_COLOR[pla[dst - 'A'][head[dst - 'A']]]);
        }
        else {
            hdc_rectangle(now_x+ HDC_Base_Width * (2 * pla[dst - 'A'][head[dst - 'A']]+1)+v_x,
            now_y,
            -v_x,
            HDC_Base_High,
                0, 1, 1, HDC_COLOR[0]);
            now_x += v_x;
            hdc_rectangle(now_x,
            now_y,
            -v_x,
            HDC_Base_High,
                0, 1, 1, HDC_COLOR[pla[dst - 'A'][head[dst - 'A']]]);
        }
        if (!k) {
            if (cnt <= 7) {
                if (!slp)ch=_getch();
                else Sleep(slp);
            }
        }
        else {
            if (!slp)ch=_getch();
            else Sleep(slp);
        }
    }
    while (now_y < HDC_Start_Y - (1 + head[dst-'A']) * HDC_Base_High) {
        hdc_rectangle(now_x,
            now_y ,
            HDC_Base_Width * (2 * pla[dst - 'A'][head[dst - 'A']] + 1),
            v_y,
            0, 1, 1, HDC_COLOR[0]);
        if (now_y > HDC_Start_Y - HDC_Base_High * 12) {
            hdc_rectangle(now_x + HDC_Base_Width * (pla[dst - 'A'][head[dst - 'A']]),
                now_y ,
                HDC_Base_Width,
                v_y,
                0, 1, 1, HDC_COLOR[11]);
        }
        now_y += v_y;
        hdc_rectangle(now_x,
            now_y + HDC_Base_High - v_y,
            HDC_Base_Width * (2 * pla[dst - 'A'][head[dst - 'A']] + 1),
            v_y,
            0, 1, 1, HDC_COLOR[pla[dst - 'A'][head[dst - 'A']]]);
        if (!k) {
            if (cnt <= 7) {
                if (!slp)ch=_getch();
                else Sleep(slp);
            }
        }
        else {
            if (!slp)ch=_getch();
            else Sleep(slp);
        }
    }
    return;
}

static void base_row(int con_x, int con_y)
{
    cct_cls();
    cct_gotoxy(con_x + Underpan_A_X_OFFSET - 2, con_y + Underpan_A_Y_OFFSET - 1);
    cout << "=";
    for (int i = 1; i <= Underpan_Distance * 2 + 4; i++)cout << "=";
    cct_gotoxy(con_x + Underpan_A_X_OFFSET, con_y + Underpan_A_Y_OFFSET);
    cout << "A";
    cct_gotoxy(con_x + Underpan_A_X_OFFSET + Underpan_Distance, con_y + Underpan_A_Y_OFFSET);
    cout << "B";
    cct_gotoxy(con_x + Underpan_A_X_OFFSET + Underpan_Distance * 2, con_y + Underpan_A_Y_OFFSET);
    cout << "C";
    cct_gotoxy(con_x, con_y);
    cout << "初始:  ";
    cout << " A:";
    prt(pla[0]);
    cout << " B:";
    prt(pla[1]);
    cout << " C:";
    prt(pla[2]);
    for (int i = 0; i <= head[0]; i++) {
        cct_gotoxy(con_x + Underpan_A_X_OFFSET - 1, con_y + Underpan_A_Y_OFFSET - i - 2);
        cout << setw(2) << pla[0][i];
    }
    for (int i = 0; i <= head[1]; i++) {
        cct_gotoxy(con_x + Underpan_A_X_OFFSET - 1 + Underpan_Distance, con_y + Underpan_A_Y_OFFSET - i - 2);
        cout << setw(2) << pla[1][i];
    }
    for (int i = 0; i <= head[2]; i++) {
        cct_gotoxy(con_x + Underpan_A_X_OFFSET - 1 + Underpan_Distance * 2, con_y + Underpan_A_Y_OFFSET - i - 2);
        cout << setw(2) << pla[2][i];
    }
}

void solve(int x)
{
    reset();
    int num;
    char be, en, mi,ch;
    if (x!=5) {
        read(num, be, en);
        mi = 'A' + 'B' + 'C' - be - en;
    }
    if (x <= 3 && x >= 1) {
        hanoi(num, be, mi, en, x);
        cout << "按回车键继续";
        ch=_getch();
    }
    if (x == 4) {
        cout << "请输入移动速度(0-200：0-按回车单步演示 1-200:延时1-200ms)";
        cin >> slp; 
        base_row(MenuItem4_Start_X, MenuItem4_Start_Y);
        cct_gotoxy(Status_Line_X, Status_Line_Y);
        cout << "从 " << be << " 移动到 " << en << "，共 " << num << " 层，延时设置为 " << slp << "ms" << endl;
        if (!slp)ch=_getch();
        else Sleep(slp);
        hanoi(num, be, mi,en, x);
        cct_gotoxy(Status_Line_X, Status_Line_Y+1);
        cout << "按回车键继续";
        ch=_getch();;
    }
    if (x == 5) {
        head[0] = -1;
        head[1] = -1;
        head[2] = -1;
        cct_cls();
        cct_gotoxy(Status_Line_X, Status_Line_Y);
        //cct_gotoxy(HDC_Start_X, HDC_Start_Y);
        //hdc_set_pencolor(HDC_COLOR[11]);
        print_base();
        cout << "按回车键继续";
        ch=_getch();
    }
    if (x == 6) {
        cct_cls();
        cct_gotoxy(Status_Line_X, Status_Line_Y);
        cout << "从 " << be << " 移动到 " << en << "，共 " << num << " 层" << endl;
        print_base();
        
        cout << endl<<"按回车键继续";
        ch=_getch();
    }
    if (x == 7) {
        cout << "请输入移动速度(0-10：0-按回车单步演示 1-20:延时1-20ms)";
        cin >> slp; 
        cct_cls();
        cct_gotoxy(Status_Line_X, Status_Line_Y);
        cout << "从 " << be << " 移动到 " << en << "，共 " << num << " 层" << endl;
        print_base();
        
        if (num == 1) {
            move_d(be, en);
            move_pl(be, en);
        }
        else {
            move_d(be, mi);
            move_pl(be, mi);
        }
        cout << endl << "按回车键继续";
        ch=_getch();
    }
    if (x == 8) {
        cout << "请输入移动速度(0-200：0-按回车单步演示 1-200:延时1-200ms)";
        cin >> slp; 
        base_row(MenuItem8_Start_X, MenuItem8_Start_Y);
        cct_gotoxy(Status_Line_X, Status_Line_Y);
        cout << "从 " << be << " 移动到 " << en << "，共 " << num << " 层，延时设置为 " << slp << "ms（前7步，后面自动变为0ms）" << endl;
        print_base();

        if (!slp)ch=_getch();
        else Sleep(slp);
        
        hanoi(num, be, mi, en, x);
        cct_gotoxy(Status_Line_X, Status_Line_Y + 1);
        cout << "按回车键继续";
        ch=_getch();
    }
    if (x == 9) {
        cout << "请输入移动速度(0-10：0-按回车单步演示 1-20:延时1-20ms) ";
        cin >> slp; 
        base_row(MenuItem9_Start_X, MenuItem9_Start_Y);
        cct_gotoxy(Status_Line_X, Status_Line_Y);
        cout << "从 " << be << " 移动到 " << en << "，共 " << num << " 层" << endl;
        print_base();
        if (!slp)ch=_getch();
        else Sleep(slp);
        char inf[100];
        while (1) {
            cct_gotoxy(Status_Line_X, Status_Line_Y - 1);
            cout << "                                                                                                               ";
            cct_gotoxy(Status_Line_X, Status_Line_Y - 1);
            cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
            cin >> inf; //_getch();
            if (strlen(inf) == 1 && (inf[0] == 'q' || inf[0] == 'Q')) {
                cct_gotoxy(Status_Line_X, Status_Line_Y);
                cout << "游戏中止!!!!!" << endl;
                break;
            }
            if (inf[0] >= 'a' && inf[0] <= 'z')inf[0] -= 32;
            if (inf[1] >= 'a' && inf[1] <= 'z')inf[1] -= 32;
            if (!(strlen(inf) == 2 && (inf[0] == 'A' || inf[0] == 'B' || inf[0] == 'C') && (inf[1] == 'A' || inf[1] == 'B' || inf[1] == 'C') && (inf[0] != inf[1]))) {
                continue;
            }
            char src = inf[0], dst = inf[1];
            if (head[src - 'A'] < 0) {
                cct_gotoxy(Status_Line_X, Status_Line_Y);
                cout << "源柱为空!" ;
                Sleep(500);
                cct_gotoxy(Status_Line_X, Status_Line_Y);
                cout << "                                " ;
                continue;
            }
            // 替换原有判断，增加下标合法性检查，防止越界访问
            if (
                head[src - 'A'] >= 0 && head[src - 'A'] < MAX_LAYER + 2 &&
                head[dst - 'A'] >= 0 && head[dst - 'A'] < MAX_LAYER + 2 &&
                pla[src - 'A'][head[src - 'A']] > pla[dst - 'A'][head[dst - 'A']]
            ) {
                cct_gotoxy(Status_Line_X, Status_Line_Y);
                cout << "大盘压小盘，非法操作!";
                Sleep(500);
                cct_gotoxy(Status_Line_X, Status_Line_Y);
                cout << "                                " ;
                continue;
            }
            move_d(src, dst);
            cnt++;
            int idx = head[dst - 'A'];
            int val = 0;
            if (idx >= 0 && idx < MAX_LAYER + 2) {
                val = (int)pla[dst - 'A'][idx];
            }
            sho(9, src, dst, val, cnt);
            if (head[en - 'A'] == num - 1) {
                cct_gotoxy(Status_Line_X, Status_Line_Y);
                cout << "游戏结束!!!!!";
                break;
            }
        }
        cct_gotoxy(Status_Line_X, Status_Line_Y + 1);
        cout << "按回车键继续";
        ch=_getch();
    }
}
