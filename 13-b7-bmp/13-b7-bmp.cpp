/* 2452839 徐川 计科 */
#include <iostream>
#include <iomanip>  //用于debug信息打印时的格式
#include <fstream>
//不再允许加入任何头文件，特别是<Windows.h>/<Wingdi.h>，查到就是0分甚至是倒扣-20 ！！！
using namespace std;

#include "13-b7-bmp.h"

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：is_debug，用于查看调试信息，不需要实现（或者按自己的方式实现，对debug的输出不做要求）
            其余内容按需补充
***************************************************************************/
bitmap::bitmap(const char* const filename, const bool is_debug) : file_header{}, info_header{}, color_palette(nullptr), pixel_data(nullptr), is_debug(is_debug)
{
	std::ifstream bmp_file;
	bmp_file.open(filename, std::ios::in | std::ios::binary);
	if (!bmp_file.is_open()) {
		cerr << "无法打开文件：" << filename << endl;
		return ;
	}
	bmp_file.seekg(0, std::ios::beg);
	bmp_file.read((char*)&file_header, sizeof(BitmapFileHeader));
	if (file_header.bfType != 0x4D42) {
		cerr << "不是有效的BMP文件：" << filename << endl;
		bmp_file.close();
		return ;
	}
	bmp_file.seekg(sizeof(BitmapFileHeader), std::ios::beg);
	bmp_file.read((char*)&info_header, sizeof(BitmapInfoHeader));
	if (info_header.biBitCount < 1 || info_header.biBitCount>32) {
		cerr << "不支持的BMP位数：" << info_header.biBitCount << endl;
		bmp_file.close();
		return ;
	}
	if (info_header.biCompression != 0) {
		cerr << "不支持压缩的BMP文件：" << filename << endl;
		bmp_file.close();
		return ;
	}
	if (info_header.biBitCount <= 8) {
		int palette_size = (info_header.biClrUsed == 0) ? (1 << info_header.biBitCount) : info_header.biClrUsed;
		color_palette = new(nothrow) RGBQuad[palette_size];
		bmp_file.seekg(sizeof(BitmapFileHeader) + info_header.biSize, std::ios::beg);
		bmp_file.read((char*)color_palette, sizeof(RGBQuad) * palette_size);
	} else {
		color_palette = nullptr; //24位及以上不需要调色板
	}
	//计算每行像素数据的字节数（考虑4字节对齐）
	int data_size = file_header.bfSize - file_header.bfOffBits;
	pixel_data = new(nothrow) unsigned char[data_size];
	bmp_file.seekg(file_header.bfOffBits, std::ios::beg);
	bmp_file.read((char*)pixel_data, data_size);
	bmp_file.close();
	//按需增加内容
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：按需补充
***************************************************************************/
bitmap::~bitmap()
{
	delete[] color_palette;
	delete[] pixel_data;
}

int bitmap::show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror,
	void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const
{
	if (pixel_data == nullptr) {
		cerr << "像素数据为空，无法显示图像。" << endl;
		return -1;
	}
	int width = info_header.biWidth;
	int height = info_header.biHeight;
	int row_size = ((info_header.biBitCount * width + 31) / 32) * 4; //每行字节数（4字节对齐）
	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			int pixel_index = row * row_size + (col * info_header.biBitCount) / 8;
			unsigned char red = 0, green = 0, blue = 0;
			if (info_header.biBitCount == 32) {
				blue = pixel_data[pixel_index];
				green = pixel_data[pixel_index + 1];
				red = pixel_data[pixel_index + 2];
			}
			else if (info_header.biBitCount == 24) {
				blue = pixel_data[pixel_index];
				green = pixel_data[pixel_index + 1];
				red = pixel_data[pixel_index + 2];
			} else if (info_header.biBitCount == 8) {
				unsigned char palette_index = pixel_data[pixel_index];
				blue = color_palette[palette_index].blue;
				green = color_palette[palette_index].green;
				red = color_palette[palette_index].red;
			}
			else if (info_header.biBitCount == 4) {
				unsigned char byte = pixel_data[pixel_index];
				unsigned char palette_index;
				if (col % 2 == 0) {
					palette_index = (byte >> 4) & 0x0F; //高4位
				} else {
					palette_index = byte & 0x0F; //低4位
				}
				blue = color_palette[palette_index].blue;
				green = color_palette[palette_index].green;
				red = color_palette[palette_index].red;
			}else if(info_header.biBitCount == 1){
				unsigned char byte = pixel_data[pixel_index];
				unsigned char palette_index = (byte >> (7 - (col % 8))) & 0x01; //对应位
				blue = color_palette[palette_index].blue;
				green = color_palette[palette_index].green;
				red = color_palette[palette_index].red;
			}
			int x = col;
			int y = row;
			if (angle == 90) {
				int temp = x;
				x = y;
				y = width - 1 - temp;
			}
			else if (angle == 180) {
				x = width - 1 - x;
				y = height - 1 - y;
			}
			else if (angle == 270) {
				int temp = x;
				x = height - 1 - y;
				y = temp;
			}
			int draw_x = top_left_x + (is_mirror ? (width - 1 - x) : x);
			int draw_y = top_left_y + (height - 1 - y);
			draw_point(draw_x, draw_y, red, green, blue);
		}
	}
	return 0;
}

