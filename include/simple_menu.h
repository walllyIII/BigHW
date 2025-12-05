/* 2452839 Ðì´¨ ¼Æ¿Æ */

#pragma once
#include<iostream>
#include<cstdio>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_hdc_tools.h"
using namespace std;

int simple_menu(const char* const menu[], const char* const cod);

template<typename T, std::size_t N, std::size_t M>
int simple_menu(const T(&menu)[N][M], const char* const cod)
{
	char x;
	for (int i = 0; menu[i][0] != 0; i++) {
		cout << menu[i] << endl;
	}
	while (1) {
		x = _getch();
		if (strchr(cod, x)) {
			break;
		}
	}
	cout << x << endl;
	return x;
}

int simple_menu(const char* menu, const char* const cod);