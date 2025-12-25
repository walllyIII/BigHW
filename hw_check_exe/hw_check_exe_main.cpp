/* 2452839 徐川 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include"hw_check_exe.h"
#include"../include_mariadb_x86/mysql/mysql.h"
#include"../include/exe_running.h"
using namespace std;

enum OPT_ARGS {
	OPT_ARGS_HELP = 0,
	OPT_ARGS_DEBUG,
	OPT_ARGS_CHECKNAME,
	OPT_ARGS_CHECKCFG_ONLY,
	OPT_ARGS_CFGFILE
};

struct ST_HW_CHECK_EXE_CFG {
	char exe_style='n';						//'n'==none,'s'==single,'m'==multi
	bool namelist=0;						//0==databse,1=file
	string single_exe_dirname;			//指定 single 方式下存放所有学生 exe 的目录名
	string multi_exe_main_dirname;		//指定根目录(例:D:\25261-term\allfile)
	string multi_exe_sub_dirname;		//指定学生目录下的 exe 文件目录(例:vs-exec)
	string stu_exe_name;				//指定学生 exe 文件名(例:3-b3-2.cpp.vs.x86.debug.exe)
	string demo_exe_name;				//指定参考程序的全路径文件名
	char cmd_style='n';						//'n'==none,'p'==pipe,'r'==redirection,'m'==main_with_arguments
	string pipe_get_input_data_exe_name;//指定 get_input_data.exe 的全路径文件名
	string pipe_data_file;				//指定 get_input_data.exe 所用的数据文件的全路径文件名
	string redirection_data_dirname;	//指定重定向方式输入的数据文件所在的目录
	int timeout=0;						//设定超时时间
	int max_output_len=0;					//设置最大输出长度
	string tc_trim;						//即 txt_compare 作业参数--trim
	int tc_lineskip = 0;				//即 txt_compare 作业的参数--lineskip 
	int tc_lineoffset = 0;				//即 txt_compare 作业的参数--lineoffset 
	bool tc_ignoreblank = 0;			//即 txt_compare 作业的参数--ignore_blank 
	bool tc_not_ignore_linefeed;		//即 txt_compare 作业的参数--not_ignore_linefeed 
	int tc_maxdiff = 0;					//即 txt_compare 作业的参数--max_diff 
	int tc_maxline = 0;					//即 txt_compare 作业的参数--max_line 
	string tc_display = "none";			//即 txt_compare 作业的参数--display none / normal / detailed
	int items_num=1;						// 指定测试项的总数(取值[1..1024]) 
	int items_begin=1;					// 指定测试的起始项数([1..items_num]) 
	int items_end=1;						//指定测试的结束项数([items_begin..items_num])
	vector < string > item_gnames;				//如果是 pipe 方式,则指定 pipe_data_file 中的 n 个组名
	vector < string > item_fnames;				//如果是 redirection 方式,则为 redirection_data_dirname 下的文件名
	vector < string > item_args;					//如果是 main_with_arguments 方式,则指定 n 个命令行参数
};

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* const full_procname,ostringstream& msg)
{
	const int offset_len = 7;
	const char *procname = strrchr(full_procname, '\\');
	if (procname == NULL)
		procname = full_procname;

	/* 本程序的特殊示例 */
	msg << "e.g.  :" << endl;
	msg << setw(offset_len) << ' ' << procname << " --checkname 3-b3                 : 按配置文件[3-b3]组的设定检查exe的运行结果" << endl;
	msg << setw(offset_len) << ' ' << procname << " --checkname 3-b3 --checkcfg_only : 检查配置文件[3-b3]组的设定是否正确" << endl;
	msg << setw(offset_len) << ' ' << procname << " --checkname 3-b3 --debug trace   : 按配置文件[3-b3]组的设定检查exe的运行结果，打印所有调试信息" << endl;
	msg << endl;
}

static void remove_bracket_in_line(string& line)
{
	line = remove_space_in_line(line, "all");
	if (line[0] == '[' && line[line.size() - 1] == ']')
		line = line.substr(1, line.size() - 2);
	line=remove_space_in_line(line, "all");
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int main(int argc, char** argv)
{
	const string loglevel_define[] = { "warn", "info", "debug", "trace", ""};

	args_analyse_tools args[] = {
		args_analyse_tools("--help",		   ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--debug",		   ST_EXTARGS_TYPE::str_with_set_default, 1, 0, loglevel_define),
		args_analyse_tools("--checkname",	   ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--checkcfg_only", ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--cfgfile",	   ST_EXTARGS_TYPE::str, 1, string("hw_check_exe.cfg")),
		args_analyse_tools()  //最后一个，用于结束
	};
	if (argc <= 1) {
		ostringstream msg;
		usage(argv[0], msg);
		cout << msg.str() << endl;
		return -1;
	}

	ostringstream msg;
	int cur_argc;

	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		return -1;
	}

	const bool is_help = args[OPT_ARGS_HELP].existed(); //后面多出要用，先取值出来，提高效率
	const bool is_debug = args[OPT_ARGS_DEBUG].existed(); //后面多出要用，先取值出来，提高效率
	const string debug_level = args[OPT_ARGS_DEBUG].get_string();
	const string check_name = args[OPT_ARGS_CHECKNAME].get_string();
	const bool is_checkcfg_only = args[OPT_ARGS_CHECKCFG_ONLY].existed();
	const string cfg_file = args[OPT_ARGS_CFGFILE].get_string();

	if (is_help || is_debug) {
		args_analyse_print(args);
		usage(argv[0], msg);
		if (is_help)
			return -1;
	}

	if (args[OPT_ARGS_CHECKNAME].existed() == 0) {
		if (!is_debug) { //如果debug打印过了就不再打印
			args_analyse_print(args);
			usage(argv[0], msg);
		}
		cout << "必须带" << args[OPT_ARGS_CHECKNAME].get_name() << "参数." << endl << endl;
		return -1;
	}

	config_file_tools cfg(cfg_file);

	if (cfg.is_read_succeeded() == 0) {
		cout << "配置文件[" << args[OPT_ARGS_CFGFILE].get_string() << "]读取不成功" << endl;
		return -1;
	}

	string db_host, db_port, db_name, db_username, db_passwd, db_currterm;
	cfg.item_get_raw("[数据库]", "db_host", db_host);
	cfg.item_get_raw("[数据库]", "db_port", db_port);
	cfg.item_get_raw("[数据库]", "db_name", db_name);
	cfg.item_get_raw("[数据库]", "db_username", db_username);
	cfg.item_get_raw("[数据库]", "db_passwd", db_passwd);
	cfg.item_get_raw("[数据库]", "db_currterm", db_currterm);

	remove_space_in_line(db_host, "all");
	remove_space_in_line(db_port, "all");
	remove_space_in_line(db_name, "all");
	remove_space_in_line(db_username, "all");
	remove_space_in_line(db_passwd, "all");
	remove_space_in_line(db_currterm, "all");

	if (is_checkcfg_only) {

	}

	

	return 0;
}

