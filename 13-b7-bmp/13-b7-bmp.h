/* 2452839 徐川 计科 */
#pragma once

//不允许加入任何头文件，特别是<Windows.h>/<Wingdi.h>，查到就是0分甚至是倒扣-20 ！！！

//关于BMP的微软官方文档：
// https://learn.microsoft.com/zh-cn/windows/win32/api/wingdi/ns-wingdi-bitmap

//自行查阅相关资料，了解下面这几个预编译命令的作用，看能否给你的作业带来方便！！！
//#pragma pack(show) //以警告信息的形式显示当前字节对齐的值
//#pragma pack(push) //将当前字节对齐值压入编译器栈的栈顶
//#pragma pack(push, 4) //将当前字节对齐值压入编译器栈的栈顶，然后再将4设置当前值
//#pragma pack(pop)  //将编译器栈栈顶的字节对齐值弹出并设置为当前值
//#pragma pack() //不带参数是恢复默认值

//允许定义其它需要的结构体（类）、常量、常变量等
#pragma pack(push, 1)
struct BitmapFileHeader {
    unsigned short bfType;        // must be 'BM' = 0x4D42
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;     // start of pixel data
};

struct BitmapInfoHeader {
    unsigned int biSize;        // = 40
    int  biWidth;
    int  biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;    // 1,4,8,24,32
    unsigned int biCompression; // must be 0 for uncompressed BMP
    unsigned int biSizeImage;
    int  biXPelsPerMeter;
    int  biYPelsPerMeter;
    unsigned int biClrUsed;     // palette size
    unsigned int biClrImportant;
};
#pragma pack(pop)
struct RGBQuad {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char reserved; // alpha or 0
};

class bitmap {
private:
	BitmapFileHeader file_header;
	BitmapInfoHeader info_header;
	RGBQuad* color_palette;
	unsigned char* pixel_data;
    const bool is_debug;
    /* 自行添加你需要的数据成员及成员函数，不限制数量 */

public:
    /* 公有部分不允许添加任何内容 */
    bitmap(const char* const filename, const bool is_debug);
    ~bitmap();
    int show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror,
        void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const;
};
