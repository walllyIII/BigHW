/* 2452839 徐川 计科 */
#include <conio.h>  
#include <math.h>
using namespace std;

#include "../include/cmd_hdc_tools.h"

void hdc_draw_Mathematical_curve_2452839()
{
    hdc_cls();

    const int CENTER_X = 300;
    const int CENTER_Y = 300;
    const double A = 60.0;        // x 方向基准尺度
    const double B = 40.0;        // y 方向基准尺度
    const double C = 80.0;        // z 方向控制项（影响腰部形状）
    const double Z_HALF = 120.0;  // z 轴显示范围为 [-Z_HALF, Z_HALF]
    const int SLICES = 18;        // 沿 z 方向的剖面数
    const int SEGMENTS = 48;      // 每个剖面的角度细分（可看作周向分辨率）
    const double SCALE = 1.0;     // 最终投影缩放（可调）
    const double DEPTH_FACTOR = 0.35; // 用于将 z 深度影响到屏幕 y 的系数（模拟简单透视/倾斜）
    const double PI = acos(-1.0);

    double yaw = 0.0; // 绕竖直轴的旋转角（按 a/d 修改）
    char ch;

    while (1)
    {
        hdc_cls();
        cct_showstr(2, 1, "<单叶双曲面 线框演示>", 7, 0);
        cct_showstr(2, 2, "[按 a/d 旋转, c 退出]", 7, 0);

        int prev_x[SEGMENTS + 1];
        int prev_y[SEGMENTS + 1];
        bool has_prev_row = false;
        for (int si = 0; si <= SLICES; ++si)
        {
            double t = (double)si / (double)SLICES;
            double z = -Z_HALF + t * (2.0 * Z_HALF);
            double r_factor = sqrt(1.0 + (z * z) / (C * C));
            int last_sx = 0, last_sy = 0;
            int first_sx = 0, first_sy = 0;
            for (int seg = 0; seg <= SEGMENTS; ++seg)
            {
                double theta = (double)seg / (double)SEGMENTS * 2.0 * PI;
                double x = A * r_factor * cos(theta);
                double y = B * r_factor * sin(theta);
                double xr = x * cos(yaw) + z * sin(yaw);
                double zr = -x * sin(yaw) + z * cos(yaw);
                int sx = CENTER_X + (int)(SCALE * xr);
                int sy = CENTER_Y - (int)(SCALE * (y + zr * DEPTH_FACTOR));
                if (seg > 0)
                    hdc_line(last_sx, last_sy, sx, sy, 1);
                else
                {
                    first_sx = sx;
                    first_sy = sy;
                }
                last_sx = sx;
                last_sy = sy;
                if (has_prev_row)
                {
                    hdc_line(prev_x[seg], prev_y[seg], sx, sy, 1);
                }
                prev_x[seg] = sx;
                prev_y[seg] = sy;
            }
            hdc_line(last_sx, last_sy, first_sx, first_sy, 1);
            has_prev_row = true;
        }
        int loop = 1;
        while (loop)
        {
            ch = _getch();
            switch (ch)
            {
            case 'a':
                yaw += 0.08; 
                loop = 0;
                break;
            case 'd':
                yaw -= 0.08; 
                loop = 0;
                break;
            case 'c':
                return;      
            default:
                continue;
            }
        }
    }
}