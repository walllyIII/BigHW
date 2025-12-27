/* 2452839 徐川 计科 */
#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<climits>
#include<iomanip>
#include <sys/stat.h>
#include"../include/class_aat.h"
#include"../include/class_cft.h"
#include"../include/txt_compare.h"
#include"../include/proceed_line.h"

enum OPT_ARGS {
	OPT_ARGS_HELP = 0,
	OPT_ARGS_DEBUG,
	OPT_ARGS_CHECKNAME,
	OPT_ARGS_CHECKCFG_ONLY,
	OPT_ARGS_CFGFILE
};

struct ST_HW_CHECK_EXE_CFG {
	string exe_style = "multi";			//'n'==none,'s'==single,'m'==multi
	string name_list = "database";		//0==databse,1=file
	string single_exe_dirname;			//指定 single 方式下存放所有学生 exe 的目录名
	string multi_exe_main_dirname;		//指定根目录(例:D:\25261-term\allfile)
	string multi_exe_sub_dirname;		//指定学生目录下的 exe 文件目录(例:vs-exec)
	string stu_exe_name;				//指定学生 exe 文件名(例:3-b3-2.cpp.vs.x86.debug.exe)
	string demo_exe_name;				//指定参考程序的全路径文件名
	string cmd_style = "normal";			//'n'==none,'p'==pipe,'r'==redirection,'m'==main_with_arguments
	string pipe_get_input_data_exe_name;//指定 get_input_data.exe 的全路径文件名
	string pipe_data_file;				//指定 get_input_data.exe 所用的数据文件的全路径文件名
	string redirection_data_dirname;	//指定重定向方式输入的数据文件所在的目录
	int timeout = 1;						//设定超时时间
	int max_output_len = 1024;			//设置最大输出长度
	string tc_trim = "none";				//即 txt_compare 作业参数--trim
	int tc_lineskip = 0;				//即 txt_compare 作业的参数--lineskip 
	int tc_lineoffset = 0;				//即 txt_compare 作业的参数--lineoffset 
	bool tc_ignoreblank = 0;			//即 txt_compare 作业的参数--ignore_blank 
	bool tc_not_ignore_linefeed = 0;		//即 txt_compare 作业的参数--not_ignore_linefeed 
	int tc_maxdiff = 0;					//即 txt_compare 作业的参数--max_diff 
	int tc_maxline = 0;					//即 txt_compare 作业的参数--max_line 
	string tc_display = "none";			//即 txt_compare 作业的参数--display none / normal / detailed
	int items_num = 0;					//指定测试项的总数(取值[1..1024]) 
	int items_begin = 0;					//指定测试的起始项数([1..items_num]) 
	int items_end = 0;					//指定测试的结束项数([items_begin..items_num])
	vector < string > item_gnames;		//如果是 pipe 方式,则指定 pipe_data_file 中的 n 个组名
	vector < string > item_fnames;		//如果是 redirection 方式,则为 redirection_data_dirname 下的文件名
	vector < string > item_args;		//如果是 main_with_arguments 方式,则指定 n 个命令行参数
	bool is_gnames = 0;					//item_gname的编号是否连续
	bool is_fnames = 0;					//item_fname的编号是否连续
	bool is_args = 0;						//item_args 的编号是否连续
};