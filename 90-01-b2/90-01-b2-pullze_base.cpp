/* 2452839 徐川 计科 */
#include<cstdio>
#include<iostream>
#include"90-01-b2-pullze.h"
using namespace std;

void read(int& x)
{
    while (1) {
        cout << "请输入区域大小(5/10/15) ：";
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            while (getchar() != '\n');
        }
        else {
            if ((x == 5) || (x == 10) || (x == 15)) {
                break;
            }
            else {
                cin.clear();
                while (getchar() != '\n');
            }

        }
    }
    return;
}

void gene(int ma[][20], int r)
{
    for (int i = 1; i <= (int)((r * r) / 2) + 1; i++) {
        int x, y;
        do {
            x = rand() % r, y = rand() % r;
        } while (ma[x][y] == 1);
        ma[x][y] = 1;
    }
}

void ending()
{
    char s[50];
    int x, y;
    while (getchar() != '\n');
    cout << endl;
    cct_getxy(x, y);
    while (1) {
        cct_gotoxy(x, y);
        cout << "本小题结束，请输入End继续...";
        fgets(s, sizeof(s), stdin);
        if (strlen(s) == 4 && s[0] == 'E' && s[1] == 'n' && s[2] == 'd')
            break;
        else
            cout << "输入错误，请重新输入";
    }
    return;
}

void get_lr(int line[][20], int row[][20], int r, int ma[][20])
{
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            if ((ma[j][i] == 1 && j == 0) || (ma[j][i] == 1 && ma[j - 1][i] == 0)) {
                line[i][0]++;
                line[i][line[i][0]] = 1;
            }
            if (j == 0)continue;
            if (ma[j][i] == 1 && ma[j - 1][i] == 1) {
                line[i][line[i][0]]++;
            }
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            if ((ma[i][j] == 1 && j == 0) || (ma[i][j] == 1 && ma[i][j - 1] == 0)) {
                row[i][0]++;
                row[i][row[i][0]] = 1;
            }
            if (j == 0)continue;
            if (ma[i][j] == 1 && ma[i][j - 1] == 1) {
                row[i][row[i][0]]++;
            }
        }
    }
    for (int i = 0; i < r; i++) {
        line[19][0] = line[19][0] < line[i][0] ? line[i][0] : line[19][0];
    }
    for (int i = 0; i < r; i++) {
        for (int j = line[i][0]; j >= 1; j--) {
            line[i][j + line[19][0] - line[i][0]] = line[i][j];
        }
        for (int j = 1; j <= line[19][0] - line[i][0]; j++) {
            line[i][j] = 0;
        }
    }
    /*for (int i = 0; i < r; i++) {
        for (int j = 1; j < line[i][0] / 2; j++) {
            swap(line[i][j], line[i][line[i][0] - j + 1]);
        }
    }*/
    for (int i = 0; i < r; i++) {
        row[19][0] = row[19][0] < row[i][0] ? row[i][0] : row[19][0];
    }
    for (int i = 0; i < r; i++) {
        for (int j = row[i][0]; j >= 1; j--) {
            row[i][j + row[19][0] - row[i][0]] = row[i][j];
        }
        for (int j = 1; j <= row[19][0] - row[i][0]; j++) {
            row[i][j] = 0;
        }
    }
}

void showpenal()
{
    cout << "命令形式：Aa=等价于图形游戏中鼠标左键选择Aa位(区分大小写)" << endl;
    cout << "             不需要支持图形界面的右键打叉，再次输入Aa相当于清除" << endl;
    cout << "          X/x=退出(新行仅有X/x，不分大小写)" << endl;
    cout << "          Y/y=提交(新行仅有Y/y，不分大小写)" << endl;
    cout << "          Z/z=作弊(新行仅有Z/z，不分大小写)" << endl;
    cout << "          Ctrl+c 强制退出" << endl;
    cout << "请输入 :";
    return;
}

bool chei(char s[], int r)
{
    if (strlen(s) == 3 && s[0] >= 'A' && s[0] <= 'A' + r - 1 && s[1] >= 'a' && s[1] <= 'a' + r - 1)
        return 1;
    if (strlen(s) == 2 && (s[0] == 'X' || s[0] == 'x' || s[0] == 'Y' || s[0] == 'y' || s[0] == 'Z' || s[0] == 'z'))
        return 1;
    return 0;
}

bool check(int ma[][20], int che[][20], int r)
{
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            if (ma[i][j] != (che[i][j] == -1 ? 0 : che[i][j]))
                return 0;
        }
    }
    return 1;
}