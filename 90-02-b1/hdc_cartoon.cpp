/*  2452839  Ðì´¨  ¼Æ¿Æ  */
#include <iostream>
#include<conio.h>
#include <Windows.h>
#include <math.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

static void DRAW_background(const int base_x, const int base_y)
{
    const int x = base_x - 350;
    const int y = base_y - 400 + 17;
    hdc_rectangle(x, y, 700, 766, 0, true, 1, RGB(255, 255, 255));
}

void hdc_draw_cartoon_2452839(const int base_x, const int base_y)
{
    hdc_cls();

    const int WIN_WIDTH = 800;
    const int WIN_HEIGHT = 800;
    const int SIZE_WIDTH = 700;
    const int SIZE_HEIGHT = 766;
    const int OFFSET_X = 400;
    const int OFFSET_Y = 400;

    const int MyColor_OUTLINE = RGB(0, 0, 0);
    const int MyColor_YELLOW = RGB(255, 235, 0);
    const int MyColor_SPOT_GREEN = RGB(126, 170, 38);
    const int MyColor_WHITE = RGB(255, 255, 255);
    const int MyColor_BLUE_IRIS = RGB(141, 193, 229);
    const int MyColor_BLACK = RGB(0, 0, 0);
    const int MyColor_BROWN = RGB(183, 107, 16);
    const int MyColor_RED = RGB(220, 30, 30);
    const int MyColor_SHOE = RGB(40, 40, 40);
    const int MyColor_BG = RGB(255, 255, 255);
    const int MyColor_YELLOW_SHADOW = RGB(235, 215, 0);
    const int MyColor_YELLOW_LIGHT = RGB(255, 245, 120);
    const int MyColor_SOCK_WHITE = RGB(240, 240, 240);
    const int MyColor_BROWN_DARK = RGB(153, 87, 0);

    const int x0 = base_x - OFFSET_X + (WIN_WIDTH - SIZE_WIDTH) / 2;
    const int y0 = base_y - OFFSET_Y + (WIN_HEIGHT - SIZE_HEIGHT) / 2;

    const int body_w = 340;
    const int body_h = 380;
    const int body_x = x0 + (SIZE_WIDTH - body_w) / 2; 
    const int body_y = y0 + 40;                       

    DRAW_background(base_x, base_y);

    hdc_rectangle(body_x, body_y, body_w, body_h, 0, true, 1, MyColor_YELLOW);
    hdc_line(body_x, body_y , body_x + body_w, body_y , 3, MyColor_OUTLINE);
	hdc_sector(body_x + 20 + 12, body_y - 6, 18,90,270, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 12, body_y - 6, 18, 110, 255, 3, MyColor_OUTLINE);
	hdc_sector(body_x + 20 + 56 + 12, body_y + 0, 18, 90, 270, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 56 + 12, body_y + 0, 18, 90, 270, 3, MyColor_OUTLINE);
	hdc_sector(body_x + 20 + 112 + 12, body_y - 6, 12, 90, 270, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 112 + 12, body_y - 6, 12, 110, 255, 3, MyColor_OUTLINE);
	hdc_sector(body_x + 20 + 168 + 12, body_y + 0, 15, 90, 270, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 168 + 12, body_y + 0, 15, 90, 270, 3, MyColor_OUTLINE);
	hdc_sector(body_x + 20 + 224 + 12, body_y - 6, 18, 90, 270, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 224 + 12, body_y - 6, 18, 110, 255, 3, MyColor_OUTLINE);
	hdc_sector(body_x + 20 + 280 + 12, body_y + 0, 12, 90, 270, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 280 + 12, body_y + 0, 12, 90, 270, 3, MyColor_OUTLINE);
    // ×ó²à²¨ÀË
    hdc_line(body_x, body_y, body_x, body_y + body_h, 3, MyColor_OUTLINE);
    hdc_sector(body_x , body_y + 65, 18, 0, 180, true, 3, MyColor_BG);
    hdc_arc(body_x , body_y + 65, 18, 10, 170, 3, MyColor_OUTLINE);
    hdc_sector(body_x , body_y + 110, 12, 0, 180, true, 3, MyColor_BG);
    hdc_arc(body_x, body_y + 110, 12, 10, 170, 3, MyColor_OUTLINE);
    hdc_sector(body_x, body_y + 155, 9, 0, 180, true, 3, MyColor_BG);
    hdc_arc(body_x, body_y + 155, 9, 10, 170, 3, MyColor_OUTLINE);
    hdc_sector(body_x, body_y + 200, 20, 0, 180, true, 3, MyColor_BG);
    hdc_arc(body_x, body_y + 200, 20, 10, 170, 3, MyColor_OUTLINE);
    hdc_sector(body_x , body_y + 245, 12, 0, 180, true, 3, MyColor_BG);
    hdc_arc(body_x, body_y + 245, 12, 10, 170, 3, MyColor_OUTLINE);
    hdc_sector(body_x, body_y + 290, 9, 0, 180, true, 3, MyColor_BG);
    hdc_arc(body_x, body_y + 290, 9, 10, 170, 3, MyColor_OUTLINE);
	hdc_sector(body_x, body_y + 335, 12, 0, 180, true, 3, MyColor_BG);
	hdc_arc(body_x, body_y + 335, 12, 10, 170, 3, MyColor_OUTLINE);
    // ÓÒ²à²¨ÀË
    hdc_line(body_x+body_w, body_y, body_x+body_w, body_y + body_h, 3, MyColor_OUTLINE);
    hdc_sector(body_x + body_w, body_y + 65, 12, 180, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + body_w, body_y + 65, 12, 190, 350, 3, MyColor_OUTLINE);
    hdc_sector(body_x + body_w, body_y + 110, 9, 180, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + body_w, body_y + 110, 9, 190, 350, 3, MyColor_OUTLINE);
    hdc_sector(body_x + body_w, body_y + 155, 18, 180, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + body_w, body_y + 155, 18, 190, 350, 3, MyColor_OUTLINE);
    hdc_sector(body_x + body_w, body_y + 200, 9, 180, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + body_w, body_y + 200, 9, 190, 350, 3, MyColor_OUTLINE);
    hdc_sector(body_x + body_w, body_y + 245, 12, 180, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + body_w, body_y + 245, 12, 190, 350, 3, MyColor_OUTLINE);
    hdc_sector(body_x + body_w, body_y + 290, 18, 180, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + body_w, body_y + 290, 18, 190, 350, 3, MyColor_OUTLINE);
    hdc_sector(body_x + body_w, body_y + 335, 12, 180, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + body_w, body_y + 335, 12, 190, 350, 3, MyColor_OUTLINE);
    // µ×²¿²¨ÀË
    hdc_line(body_x, body_y+body_h, body_x + body_w, body_y+body_h, 3, MyColor_OUTLINE);
    hdc_sector(body_x + 20 + 12, body_y+body_h , 12, 0, 90, true, 3, MyColor_BG);
    hdc_sector(body_x + 20 + 12, body_y + body_h, 12, 360-90, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 12, body_y+body_h, 12, 0, 90, 3, MyColor_OUTLINE);
	hdc_arc(body_x + 20 + 12, body_y + body_h, 12, 270, 360, 3, MyColor_OUTLINE);
    hdc_sector(body_x + 20 + 56 + 12, body_y+body_h + 3, 15, 0, 90, true, 3, MyColor_BG);
	hdc_sector(body_x + 20 + 56 + 12, body_y + body_h + 3, 15, 360 - 90, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 56 + 12, body_y+body_h + 3, 15, 0, 70, 3, MyColor_OUTLINE);
	hdc_arc(body_x + 20 + 56 + 12, body_y + body_h + 3, 15, 290, 360, 3, MyColor_OUTLINE);
    hdc_sector(body_x + 20 + 112 + 12, body_y+body_h+3, 12, 0, 90, true, 3, MyColor_BG);
	hdc_sector(body_x + 20 + 112 + 12, body_y + body_h+3, 12, 360 - 90, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 112 + 12, body_y+body_h +3, 12, 0, 70, 3, MyColor_OUTLINE);
	hdc_arc(body_x + 20 + 112 + 12, body_y + body_h +3, 12, 290, 360, 3, MyColor_OUTLINE);
    hdc_sector(body_x + 20 + 168 + 12, body_y+body_h + 3, 15, 0, 70, true, 3, MyColor_BG);
	hdc_sector(body_x + 20 + 168 + 12, body_y + body_h + +3, 15, 360 - 70, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 168 + 12, body_y+body_h + 3, 15, 0, 90, 3, MyColor_OUTLINE);
	hdc_arc(body_x + 20 + 168 + 12, body_y + body_h + 3, 15, 270, 360, 3, MyColor_OUTLINE);
    hdc_sector(body_x + 20 + 224 + 12, body_y+body_h +6, 18, 0, 90, true, 3, MyColor_BG);
	hdc_sector(body_x + 20 + 224 + 12, body_y + body_h +6, 18, 360 - 90, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 224 + 12, body_y+body_h +6, 18, 0, 70, 3, MyColor_OUTLINE);
	hdc_arc(body_x + 20 + 224 + 12, body_y + body_h +6, 18, 290, 360, 3, MyColor_OUTLINE);
    hdc_sector(body_x + 20 + 280 + 12, body_y+body_h + 3, 12, 0, 90, true, 3, MyColor_BG);
	hdc_sector(body_x + 20 + 280 + 12, body_y + body_h + 3, 12, 360 - 90, 360, true, 3, MyColor_BG);
    hdc_arc(body_x + 20 + 280 + 12, body_y+body_h + 3, 12, 0, 90, 3, MyColor_OUTLINE);
	hdc_arc(body_x + 20 + 280 + 12, body_y + body_h + 3, 12, 290, 360, 3, MyColor_OUTLINE);
    // ÂÌÉ«°ßµã
    hdc_ellipse(body_x + 60,  body_y + 80,  26, 18, 25, true, 2, MyColor_SPOT_GREEN);
    hdc_ellipse(body_x + 60, body_y + 80, 26, 18, 25, false, 2, MyColor_OUTLINE);
    hdc_ellipse(body_x + 260, body_y + 60,  18, 12, 15, true, 2, MyColor_SPOT_GREEN);
    hdc_ellipse(body_x + 260, body_y + 60, 18, 12, 15, false, 2, MyColor_OUTLINE);
    hdc_ellipse(body_x + 280, body_y + 190, 34, 24, 350, true, 2, MyColor_SPOT_GREEN);
	hdc_ellipse(body_x + 280, body_y + 190, 34, 24, 350, false, 2, MyColor_OUTLINE);
    hdc_ellipse(body_x + 50, body_y + 250, 30, 20, 290, true, 2, MyColor_SPOT_GREEN);
	hdc_ellipse(body_x + 50, body_y + 250, 30, 20, 290, false, 2, MyColor_OUTLINE);
    hdc_ellipse(body_x + 270, body_y + 300, 26, 18, 90, true, 2, MyColor_SPOT_GREEN);
	hdc_ellipse(body_x + 270, body_y + 300, 26, 18,90, false, 2, MyColor_OUTLINE);
    // ÑÛ¾¦
    const int eye_r = 60;
    const int eye_y = body_y + 140;
    const int eye_lx = body_x + 110;             
    const int eye_rx = body_x + 230;             
    // ÑÛ°×
    hdc_circle(eye_lx, eye_y, eye_r, true, 2, MyColor_WHITE);
    hdc_circle(eye_lx, eye_y, eye_r, false, 2, MyColor_OUTLINE);
    hdc_circle(eye_rx, eye_y, eye_r, true, 2, MyColor_WHITE);
	hdc_circle(eye_rx, eye_y, eye_r, false, 2, MyColor_OUTLINE);
    // ºçÄ¤
    hdc_circle(eye_lx, eye_y, 26, true, 2, MyColor_BLUE_IRIS);
    hdc_circle(eye_lx, eye_y, 26, false, 2, MyColor_OUTLINE);
    hdc_circle(eye_rx, eye_y, 26, true, 2, MyColor_BLUE_IRIS);
	hdc_circle(eye_rx, eye_y, 26, false, 2, MyColor_OUTLINE);
    // Í«¿×
    hdc_circle(eye_lx, eye_y, 10, true, 2, MyColor_BLACK);
    hdc_circle(eye_rx, eye_y, 10, true, 2, MyColor_BLACK);
    // ¸ß¹â
    hdc_circle(eye_lx - 6, eye_y - 6, 4, true, 2, MyColor_WHITE);
    hdc_circle(eye_rx - 6, eye_y - 6, 4, true, 2, MyColor_WHITE);
    // ÑÛ½ÞÃ«
    hdc_line(eye_lx - 16, eye_y - eye_r, eye_lx - 16, eye_y - eye_r - 18, 5, MyColor_OUTLINE);
    hdc_line(eye_lx + 0,  eye_y - eye_r, eye_lx + 0,  eye_y - eye_r - 18, 5, MyColor_OUTLINE);
    hdc_line(eye_lx + 16, eye_y - eye_r, eye_lx + 16, eye_y - eye_r - 18, 5, MyColor_OUTLINE);

    hdc_line(eye_rx - 16, eye_y - eye_r, eye_rx - 16, eye_y - eye_r - 18, 5, MyColor_OUTLINE);
    hdc_line(eye_rx + 0,  eye_y - eye_r, eye_rx + 0,  eye_y - eye_r - 18, 5, MyColor_OUTLINE);
    hdc_line(eye_rx + 16, eye_y - eye_r, eye_rx + 16, eye_y - eye_r - 18, 5, MyColor_OUTLINE);
    // ±Ç×Ó
    const int nose_x = body_x + body_w / 2+6;
    const int nose_y = body_y + 170;
    
    hdc_ellipse(nose_x, nose_y + 14, 26, 18, 90, true, 3, MyColor_YELLOW);
    hdc_ellipse(nose_x, nose_y + 14, 26,18,90,false , 3,MyColor_OUTLINE);
    hdc_circle(nose_x-20, nose_y+35, 18, true, 2, MyColor_YELLOW);

    // ±Ç×Ó¸ß¹â
    hdc_circle(nose_x - 4, nose_y - 3, 4, true, 1, MyColor_YELLOW_LIGHT);
    // ×ì
    const int smile_cx = body_x + body_w / 2;
    const int smile_cy = body_y +220;
    hdc_arc(smile_cx,smile_cy-240,260,155,205,4,MyColor_OUTLINE);
    // ×ì½ÇÐ¡µã
	hdc_arc(smile_cx - 120, smile_cy-10, 10, 100, 170, 4, MyColor_OUTLINE);
    hdc_arc(smile_cx + 120, smile_cy-10, 10, 190, 260, 4, MyColor_OUTLINE);

    hdc_arc(smile_cx - 120, smile_cy - 20, 25, 0, 60, 4, MyColor_OUTLINE);
    hdc_arc(smile_cx - 120, smile_cy - 20, 25, 200, 360, 4, MyColor_OUTLINE);
    hdc_circle(smile_cx - 130, smile_cy - 30, 3, true, 2, MyColor_OUTLINE);
    hdc_circle(smile_cx - 130, smile_cy - 20, 3, true, 2, MyColor_OUTLINE);
    hdc_circle(smile_cx - 120, smile_cy - 30, 3, true, 2, MyColor_OUTLINE);
    hdc_arc(smile_cx + 120, smile_cy - 20, 25, 0, 130, 4, MyColor_OUTLINE);
    hdc_arc(smile_cx + 120, smile_cy - 20, 25, 300, 360, 4, MyColor_OUTLINE);
    hdc_circle(smile_cx + 130, smile_cy - 30, 3, true, 2, MyColor_OUTLINE);
    hdc_circle(smile_cx + 130, smile_cy - 20, 3, true, 2, MyColor_OUTLINE);
    hdc_circle(smile_cx + 120, smile_cy - 30, 3, true, 2, MyColor_OUTLINE);
    // ÑÀ³Ý
    hdc_rectangle(smile_cx - 40, smile_cy +20, 36, 30, 0, true, 3, MyColor_WHITE);
    hdc_rectangle(smile_cx - 40, smile_cy + 20, 36, 30, 0, false, 3, MyColor_OUTLINE);
    hdc_rectangle(smile_cx - 40 + 40, smile_cy +20, 36, 30, 0, true, 3, MyColor_WHITE);
	hdc_rectangle(smile_cx - 40 + 40, smile_cy + 20, 36, 30, 0, false, 3, MyColor_OUTLINE);
    // ³ÄÉÀºÍ¿ã×Ó
    const int shirt_x = body_x + 60;
    const int shirt_y = body_y + body_h - 120;
    hdc_rectangle(body_x, body_y + body_h - 80, body_w, 40, 0, true, 3, MyColor_BG);
    hdc_rectangle(body_x, body_y + body_h - 80, body_w, 40, 0, false, 3, MyColor_OUTLINE);
    hdc_rectangle(body_x , body_y + body_h - 40, body_w, 50, 0, true, 3, MyColor_BROWN);
	hdc_rectangle(body_x, body_y + body_h - 40, body_w, 50, 0, false, 3, MyColor_OUTLINE);
    hdc_rectangle(smile_cx - 12, body_y + body_h - 75, 24, 40, 0, true, 3, MyColor_RED);
	hdc_rectangle(smile_cx - 12, body_y + body_h - 75, 24, 40, 0, false, 3, MyColor_OUTLINE);
    hdc_triangle(smile_cx - 12, body_y + body_h - 35, smile_cx + 12, body_y + body_h - 35, smile_cx , body_y + body_h-20 , true, 3, MyColor_RED);
    hdc_triangle(smile_cx - 12, body_y + body_h - 35, smile_cx + 12, body_y + body_h - 35, smile_cx, body_y + body_h - 20, false, 3, MyColor_OUTLINE);
    hdc_circle(smile_cx, body_y + body_h -75, 15, true, 3, MyColor_RED);
    hdc_circle(smile_cx, body_y + body_h -75, 15, false, 3, MyColor_OUTLINE);
	hdc_line(smile_cx - 20, body_y + body_h-80, smile_cx - 40, body_y + body_h -60, 3, MyColor_OUTLINE);
    hdc_line(smile_cx - 80, body_y + body_h-80, smile_cx - 40, body_y + body_h -60, 3, MyColor_OUTLINE);
	hdc_line(smile_cx + 20, body_y + body_h - 80, smile_cx + 40, body_y + body_h - 60, 3, MyColor_OUTLINE);
	hdc_line(smile_cx + 80, body_y + body_h - 80, smile_cx + 40, body_y + body_h - 60, 3, MyColor_OUTLINE);
    hdc_rectangle(smile_cx - 18 - 35, body_y + body_h - 30, 35, 6, 0, true, 3, MyColor_BLACK);
    hdc_rectangle(smile_cx - 90 - 35, body_y + body_h - 30, 35, 6, 0, true, 3, MyColor_BLACK);
    hdc_rectangle(smile_cx + 18 , body_y + body_h - 30, 35, 6, 0, true, 3, MyColor_BLACK);
    hdc_rectangle(smile_cx + 90 , body_y + body_h - 30, 35, 6, 0, true, 3, MyColor_BLACK);
    // ÊÖ±ÛÓëÊÖ
    // ×óÊÖ
    hdc_line(smile_cx - body_w / 2, body_y + body_h - 80, smile_cx - body_w / 2 - 20, body_y + body_h - 60, 4, MyColor_OUTLINE);
    hdc_line(smile_cx - body_w / 2 - 30, body_y + body_h - 80, smile_cx - body_w / 2 - 20, body_y + body_h - 60, 4, MyColor_OUTLINE);
    hdc_line(smile_cx - body_w / 2 - 30, body_y + body_h - 80, smile_cx - body_w / 2, body_y + body_h - 100, 4, MyColor_OUTLINE);
    hdc_rectangle(smile_cx - body_w / 2 - 20, body_y + body_h - 60, 50, 10, 120, true, 3, MyColor_YELLOW);
    hdc_rectangle(smile_cx - body_w / 2 - 20, body_y + body_h - 60, 50, 10, 120, false, 3, MyColor_OUTLINE);
    hdc_circle(smile_cx - body_w / 2 - 40, body_y + body_h -20, 12, true, 2, MyColor_YELLOW);
	hdc_circle(smile_cx - body_w / 2 - 40, body_y + body_h - 20, 12, false, 2, MyColor_OUTLINE);
    // ÓÒÊÖ
    hdc_line(smile_cx + body_w / 2, body_y + body_h - 80, smile_cx + body_w / 2 + 20, body_y + body_h - 60, 4, MyColor_OUTLINE);
    hdc_line(smile_cx + body_w / 2 + 30, body_y + body_h - 80, smile_cx + body_w / 2 + 20, body_y + body_h - 60, 4, MyColor_OUTLINE);
    hdc_line(smile_cx + body_w / 2 + 30, body_y + body_h - 80, smile_cx + body_w / 2-15, body_y + body_h - 100, 4, MyColor_OUTLINE);
    hdc_rectangle(smile_cx + body_w / 2 + 20+5, body_y + body_h - 60-5, 50, 10, 50, true, 3, MyColor_YELLOW);
    hdc_rectangle(smile_cx + body_w / 2 + 20+5, body_y + body_h - 60-5, 50, 10, 50, false, 3, MyColor_OUTLINE);
    hdc_circle(smile_cx + body_w / 2 + 50, body_y + body_h - 20, 12, true, 2, MyColor_YELLOW);
    hdc_circle(smile_cx + body_w / 2 + 50, body_y + body_h - 20, 12, false, 2, MyColor_OUTLINE);
    // ÍÈÓëÐ¬×Ó
    hdc_rectangle(smile_cx - 25 - 50, body_y + body_h+10, 50, 10, 0, true, 3, MyColor_BROWN);
    hdc_rectangle(smile_cx - 25 - 50, body_y + body_h+10, 50, 10, 0, false, 3, MyColor_OUTLINE);
	hdc_rectangle(smile_cx + 25, body_y + body_h+10, 50, 10, 0, true, 3, MyColor_BROWN);
	hdc_rectangle(smile_cx + 25, body_y + body_h+10, 50, 10, 0, false, 3, MyColor_OUTLINE);
    hdc_rectangle(smile_cx - 25 - 15 - 14, body_y + body_h + 20, 14, 60, 0, true, 3, MyColor_YELLOW);
	hdc_rectangle(smile_cx - 25 - 15 - 14, body_y + body_h + 20, 14, 60, 0, false, 3, MyColor_OUTLINE);
	hdc_rectangle(smile_cx + 25 + 15, body_y + body_h + 20, 14, 60, 0, true, 3, MyColor_YELLOW);
	hdc_rectangle(smile_cx + 25 + 15, body_y + body_h + 20, 14, 60, 0, false, 3, MyColor_OUTLINE);
    hdc_rectangle(smile_cx - 25 - 15 - 14, body_y + body_h + 50, 14, 30, 0, true, 3, MyColor_WHITE);
    hdc_rectangle(smile_cx - 25 - 15 - 14, body_y + body_h + 50, 14, 30, 0, false, 3, MyColor_OUTLINE);
    hdc_rectangle(smile_cx + 25 + 15, body_y + body_h + 50, 14, 30, 0, true, 3, MyColor_WHITE);
    hdc_rectangle(smile_cx + 25 + 15, body_y + body_h + 50, 14, 30, 0, false, 3, MyColor_OUTLINE);
    hdc_rectangle(smile_cx - 25 - 15 - 14, body_y + body_h + 60, 14, 20, 0, true, 3, MyColor_WHITE);
    hdc_rectangle(smile_cx - 25 - 15 - 14, body_y + body_h + 60, 14, 20, 0, false, 3, MyColor_OUTLINE);
    hdc_rectangle(smile_cx + 25 + 15, body_y + body_h + 60, 14, 20, 0, true, 3, MyColor_WHITE);
    hdc_rectangle(smile_cx + 25 + 15, body_y + body_h + 60, 14, 20, 0, false, 3, MyColor_OUTLINE);
    
    hdc_rectangle(smile_cx - 35 - 100, body_y + body_h + 80, 100, 20, 0, true, 3, MyColor_BLACK);
	hdc_sector(smile_cx - 110, body_y + body_h + 80 , 25, 0, 90, true, 3, MyColor_BLACK);
    hdc_sector(smile_cx - 110, body_y + body_h + 80, 25, 270, 360, true, 3, MyColor_BLACK);
	hdc_rectangle(smile_cx - 35 - 100, body_y + body_h + 80, 100, 20, 0, false, 3, MyColor_OUTLINE);
	hdc_rectangle(smile_cx + 35, body_y + body_h + 80, 100, 20, 0, true, 3, MyColor_BLACK);
    hdc_sector(smile_cx + 110, body_y + body_h + 80, 25, 0, 90, true, 3, MyColor_BLACK);
    hdc_sector(smile_cx + 110, body_y + body_h + 80, 25, 270, 360, true, 3, MyColor_BLACK);
	hdc_rectangle(smile_cx + 35, body_y + body_h + 80, 100, 20, 0, false, 3, MyColor_OUTLINE);
    // º£ÃàÏ¸½Ú
    hdc_circle(body_x + 170,  body_y + 10, 3, true, 1, MyColor_YELLOW_SHADOW);
    hdc_circle(body_x + 230, body_y + 210,  3, true, 1, MyColor_YELLOW_SHADOW);
    hdc_circle(body_x + 300, body_y + 160, 4, true, 1, MyColor_YELLOW_SHADOW);
    hdc_circle(body_x + 240, body_y + 240, 3, true, 1, MyColor_YELLOW_SHADOW);
    hdc_circle(body_x + 210, body_y + 270, 3, true, 1, MyColor_YELLOW_SHADOW);
    // ÑÛÖÜÇáÎ¢ÒõÓ°
    hdc_circle(eye_lx - 60, eye_y, 3, true, 1, MyColor_YELLOW_SHADOW);
    hdc_circle(eye_lx + 60, eye_y + 8, 3, true, 1, MyColor_YELLOW_SHADOW);
    hdc_circle(eye_rx - 60, eye_y + 8, 3, true, 1, MyColor_YELLOW_SHADOW);
    hdc_circle(eye_rx + 60, eye_y, 3, true, 1, MyColor_YELLOW_SHADOW);
}