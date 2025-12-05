/* 2452839 徐川 计科 */

/* ----------------------------------------------------------------------------------

     本文件功能：
	1、放被 hanoi_main.cpp 调用的菜单函数，要求显示各菜单项，读入正确的选项后返回

     本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、不允许定义静态全局变量（全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
#include<iostream>
#include<cstring>
#include <conio.h>
#include "../include/simple_menu.h"
#include "../include/cmd_console_tools.h"
#include "../include/cmd_hdc_tools.h"
using namespace std;

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

int simple_menu(const char * const menu[], const char * const cod)
{
	char x;
	for(int i=0; menu[i] != NULL; i++) {
		cout << menu[i] << endl;
	}
	while (1) {
		x = _getch();
		if (strchr(cod,x)) {
			break;
		}
	}
	cout << x << endl;
	return x;
}

int simple_menu(const char* const menu, const char* const cod)
{
	char x;
	cout << menu<< endl;
	while (1) {
		x = _getch();
		if (strchr(cod, x)) {
			break;
		}
	}
	cout << x << endl;
	return x;
}