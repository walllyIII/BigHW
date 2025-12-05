/* 2452839 徐川 计科 */
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#include<iostream>
#include"90-01-b2-pullze.h"
#include "../include/simple_menu.h"

using namespace std;
int main()
{
	const char menu[][80] = {
		" A.内部数组，原样输出",
		" B.内部数组，生成提示行列并输出",
		" C.内部数组，游戏版",
		" --------------------------------------------------------",
		" D.n*n的框架(无分隔线)，原样输出",
		" E.n*n的框架(无分隔线)，含提示行列",
		" F.n*n的框架(无分隔线)，显示初始状态，鼠标移动可显示坐标",
		" G.cmd图形界面完整版(无分隔线)",
		" --------------------------------------------------------",
		" H.n*n的框架(有分隔线)，原样输出",
		" I.n*n的框架(有分隔线)，含提示行列",
		" J.n*n的框架(有分隔线)，显示初始状态，鼠标移动可显示坐标",
		" K.cmd图形界面完整版(有分隔线)",
		" --------------------------------------------------------",
		" Q.退出",
		""
	};
	const char* x2 = "ABCDEFGHIJKQabcdefghijkq";

    srand((unsigned int)time(NULL));
    while (1) {
        char ch;
		cct_setconsoleborder(120, 50, 120, 200);
		cct_setfontsize("新宋体", 16, 0);
        cct_gotoxy(0, 0);
        ch=simple_menu(menu,x2);
        if (ch >= 'a' && ch <= 'z')ch -= 32;
        if (ch == 'Q' || ch == 'q')
            return 0;
        solve(ch);
    }
}