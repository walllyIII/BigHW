/* 2452839 徐川 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include"hw_check_exe.h"
#include"../include/exe_running.h"
using namespace std;

enum OPT_ARGS {
	OPT_ARGS_HELP = 0,
	OPT_ARGS_DEBUG,
	OPT_ARGS_CHECKNAME,
	OPT_ARGS_CHECKCFG_ONLY,
	OPT_ARGS_CFGFILE
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

	if(is_checkcfg_only)

	return 0;
}

