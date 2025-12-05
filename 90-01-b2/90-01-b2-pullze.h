/* 2452839 Ðì´¨ ¼Æ¿Æ */
#pragma once
#include<iostream>
#include"../include/cmd_console_tools.h"
using namespace std;
void solve(char ch);
void read(int& x);
void ending();
void showpenal();
void gene(int ma[][20], int r); 

bool chei(char s[], int r);
bool check(int ma[][20], int che[][20], int r);
void get_lr(int line[][20], int row[][20], int r, int ma[][20]);

void show_N(int ma[][20], int r);
void show_A(int ma[][20], int che[][20], int line[][20], int row[][20], int r, int x, int y, int z, int f = 0);

void draw_p(int x, int y, int color, int type);
void show_N_P(int ma[][20], int r);
void show_A_P(int ma[][20], int che[][20], int line[][20], int row[][20], int r, int x, int y, int z, int f=0);

bool tranXY(int& x, int& y, int Aax, int Aay, int r);

