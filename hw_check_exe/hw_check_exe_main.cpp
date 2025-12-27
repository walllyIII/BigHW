/* 2452839 徐川 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include"hw_check_exe.h"
#include"../include_mariadb_x86/mysql/mysql.h"
#include"../include/exe_running.h"
using namespace std;

#define main_debug 0

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
	
	msg << "Usage: hw_check_exe_demo --必选项 | --可选项(出现次序不限)" << endl;
	msg << endl;
	msg << "必选项：指定操作" << endl;
	msg << "	--checkname : 需要检查的项目名(配置文件的组名)" << endl;
	msg << endl;
	msg << "必选项[--checkname]的可选参数：" << endl;
	msg << "	--checkcfg_only : 仅打印配置文件检查结果" << endl;
	msg << endl;
	msg << "可选项：指定操作(任选0~n个)" << endl;
	msg << "	--help : 打印帮助信息" << endl;
	msg << "	--debug : 设置Debug等级(可设等级 : warn / info / debug / trace，后项均包含前项，例：info必然包含warn信息)" << endl;
	msg << "		fatal : 致命错误(不能设置，已打开)" << endl;
	msg << "		error : 程序异常错误(不能设置，已打开)" << endl;
	msg << "		warn : 提示潜在问题，但不影响程序运行(默认项)" << endl;
	msg << "		info : 记录程序运行状态信息" << endl;
	msg << "		debug : 打印程序调试过程中的详细信息(打开后会影响程序执行速度，仅建议Debug时使用)" << endl;
	msg << "		trace: 比debug更详细的调试信息(打开后会影响程序执行速度，仅建议Debug时使用)" << endl;
	msg << "	--cfgfile : 指定配置文件" << endl;
	msg << endl;
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

static void trans_cfg_info(config_file_tools list, const string checkname, ST_HW_CHECK_EXE_CFG& info)
{
	vector<string> all, item_gname, item_fname, item_args;
	bool item_gname_flag = 1, item_fname_flag = 1, item_args_flag = 1;
	list.get_all_item(checkname, all);
	for (size_t i = 0; i < all.size(); i++) {		string tmp = all[i];		tmp = split_string_with_c(all[i],'=');		all[i] = remove_space_in_line(tmp,"all");	}
	for (size_t i = 0; i < all.size(); i++) {
		if (remove_space_in_line(all[i],"all") == "include")continue;
		if(remove_space_in_line(all[i], "all")=="exe_style"){
			string tmp;
			list.item_get_string(checkname, "exe_style",tmp);
			tmp=remove_space_in_line(tmp, "all");
			info.exe_style = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="name_list"){
			string tmp;
			list.item_get_string(checkname, "name_list", tmp);
			tmp=remove_space_in_line(tmp, "all");
			if (tmp[tmp.size() - 1] == '\\')tmp = tmp.substr(0, tmp.size() - 1);
			info.name_list = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="single_exe_dirname"){
			string tmp;
			list.item_get_string(checkname, "single_exe_dirname", tmp);
			tmp = remove_space_in_line(tmp, "all");
			if (tmp[tmp.size() - 1] == '\\')tmp = tmp.substr(0, tmp.size() - 1);
			info.single_exe_dirname = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="multi_exe_main_dirname"){
			string tmp;
			list.item_get_string(checkname, "multi_exe_main_dirname", tmp);
			tmp = remove_space_in_line(tmp, "all");
			if (tmp[tmp.size() - 1] == '\\')tmp = tmp.substr(0, tmp.size() - 1);
			info.multi_exe_main_dirname = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="multi_exe_sub_dirname"){
			string tmp;
			list.item_get_string(checkname, "multi_exe_sub_dirname", tmp);
			tmp = remove_space_in_line(tmp, "all");
			if (tmp[tmp.size() - 1] == '\\')tmp = tmp.substr(0, tmp.size() - 1);
			info.multi_exe_sub_dirname = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="stu_exe_name"){
			string tmp;
			list.item_get_string(checkname, "stu_exe_name", tmp);
			tmp = remove_space_in_line(tmp, "all");
			if (tmp[tmp.size() - 1] == '\\')tmp = tmp.substr(0, tmp.size() - 1);
			info.stu_exe_name = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="demo_exe_name"){
			string tmp;
			list.item_get_string(checkname, "demo_exe_name", tmp);
			tmp = remove_space_in_line(tmp, "all");
			if (tmp[tmp.size() - 1] == '\\')tmp = tmp.substr(0, tmp.size() - 1);
			info.demo_exe_name = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="cmd_style"){
			string tmp;
			list.item_get_string(checkname, "cmd_style", tmp);
			tmp = remove_space_in_line(tmp, "all");
			info.cmd_style = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="pipe_get_input_data_exe_name"){
			string tmp;
			list.item_get_string(checkname, "pipe_get_input_data_exe_name", tmp);
			tmp = remove_space_in_line(tmp, "all");
			if (tmp[tmp.size() - 1] == '\\')tmp = tmp.substr(0, tmp.size() - 1);
			info.pipe_get_input_data_exe_name = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="pipe_data_file"){
			string tmp;
			list.item_get_string(checkname, "pipe_data_file", tmp);
			tmp = remove_space_in_line(tmp, "all");
			if (tmp[tmp.size() - 1] == '\\')tmp = tmp.substr(0, tmp.size() - 1);
			info.pipe_data_file = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="redirection_data_dirname"){
			string tmp;
			list.item_get_string(checkname, "redirection_data_dirname", tmp);
			tmp = remove_space_in_line(tmp, "all");
			if (tmp[tmp.size() - 1] == '\\')tmp = tmp.substr(0, tmp.size() - 1);
			info.redirection_data_dirname = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="timeout"){
			int tmp;
			list.item_get_int(checkname, "timeout", tmp);
			info.timeout = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="max_output_len"){
			int tmp;
			list.item_get_int(checkname, "max_output_len", tmp);
			info.max_output_len = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="tc_trim"){
			string tmp;
			list.item_get_string(checkname, "tc_trim", tmp);
			tmp = remove_space_in_line(tmp, "all");
			info.tc_trim = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="tc_lineskip"){
			int tmp;
			list.item_get_int(checkname, "tc_lineskip", tmp);
			info.tc_lineskip = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="tc_lineoffset"){
			int tmp;
			list.item_get_int(checkname, "tc_lineoffset", tmp);
			info.tc_lineoffset = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="tc_ignoreblank"){
			int tmp;
			list.item_get_int(checkname, "tc_ignoreblank", tmp);
			info.tc_ignoreblank = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="tc_not_ignore_linefeed"){
			int tmp;
			list.item_get_int(checkname, "tc_not_ignore_linefeed", tmp);
			info.tc_not_ignore_linefeed = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="tc_maxdiff"){
			int tmp;
			list.item_get_int(checkname, "tc_maxdiff", tmp);
			info.tc_maxdiff = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="tc_maxline"){
			int tmp;
			list.item_get_int(checkname, "tc_maxline", tmp);
			info.tc_maxline = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="tc_display"){
			string tmp;
			list.item_get_string(checkname, "tc_display", tmp);
			tmp = remove_space_in_line(tmp, "all");
			info.tc_display = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="items_num"){
			int tmp;
			list.item_get_int(checkname, "items_num", tmp);
			info.items_num = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="items_begin"){
			int tmp;
			list.item_get_int(checkname, "items_begin", tmp);
			info.items_begin = tmp;
		}
		if(remove_space_in_line(all[i], "all")=="items_end"){
			int tmp;
			list.item_get_int(checkname, "items_end", tmp);
			info.items_end = tmp;
		}
		if(remove_space_in_line(all[i], "all").substr(0,10) == "item_gname"  && item_gname_flag) {
			item_gname_flag = 0;
			string tmp = "item_gname";
			bool flag=1;
			for (int j = 1; j <= info.items_num; j++) {
				string cur = tmp + '_' + to_string(j),val;
				if (list.item_get_null(checkname, cur) == 0) {
					flag = 0;
					continue;
				}
				list.item_get_string(checkname, cur, val);
				val = remove_space_in_line(val, "all");
				remove_bracket_in_line(val);
				val = remove_space_in_line(val, "all");
				item_gname.push_back('['+val+']');
			}
			info.is_gnames = flag;
			info.item_gnames = item_gname;
		}
		if(remove_space_in_line(all[i], "all").substr(0, 10) == "item_fname" && item_fname_flag){
			item_fname_flag = 0;
			string tmp = "item_fname";
			bool flag = 1;
			for (int j = 1; j <= info.items_num; j++) {
				string cur = tmp + '_'+to_string(j), val;
				if (list.item_get_null(checkname, cur) == 0) {
					flag = 0;
					continue;
				}
				list.item_get_string(checkname, cur, val);
				val = remove_space_in_line(val, "all");
				remove_bracket_in_line(val);
				val = remove_space_in_line(val, "all");
				item_fname.push_back(val);
			}
			info.is_fnames = flag;
			info.item_fnames = item_fname;
		}
		if(remove_space_in_line(all[i], "all").substr(0, 9) == "item_args" && item_args_flag){
			item_args_flag = 0;
			string tmp = "item_args";
			bool flag = 1;
			for (int j = 1; j <= info.items_num; j++) {
				string cur = tmp + '_' + to_string(j),val;
				if (list.item_get_null(checkname, cur) == 0) {
					flag = 0;
					continue;
				}
				list.item_get_raw(checkname, cur, val);
				val = remove_space_in_line(val, "all");
				remove_bracket_in_line(val);
				val = remove_space_in_line(val, "all");
				item_args.push_back(val);
			}
			info.is_args = flag;
			info.item_args = item_args;
		}
	}
}

static void proceed_cfg_info(config_file_tools list, ST_HW_CHECK_EXE_CFG& info,const string checkname, const string debug_level,const bool is_checkcfg_only)
{
	if (is_checkcfg_only) {

	}
	if (debug_level != "") {

	}
	vector<string> include;
	string head = checkname;
	while (list.item_get_null(head,"include")) {
		string tmp;
		list.item_get_raw(head, "include",tmp);
		if (tmp == "")break;
		head = tmp;
		include.push_back(head);
	}
	for (size_t i = 0; i < include.size(); i++) {
		string cur = include[i];
		cur = remove_space_in_line(cur, "all");
		trans_cfg_info(list, cur,info);
	}
	trans_cfg_info(list, checkname, info);
}

static bool check_name_list(const vector<string> name_list)
{
	for (size_t i = 0; i < name_list.size(); i++) {
		string tmp = name_list[i],cno,stu_no;
		tmp += '-';
		cno = split_string_with_c(tmp, '-');
		stu_no=split_string_with_c(tmp, '-');
		if ((cno.size() != 8 && cno.size() != 13) || stu_no.size() != 7)
			return 0;
	}
	return 1;
}

static string find_s_incfg(ST_HW_CHECK_EXE_CFG info,string tar)
{
	if (tar == "exe_style")return info.exe_style==""?"<EMPTY>": info.exe_style;
	if (tar == "name_list")return info.name_list == "" ? "<EMPTY>" : info.name_list;
	if (tar == "single_exe_dirname")return (info.single_exe_dirname == "" ? "<EMPTY>" : info.single_exe_dirname )+'\\';
	if (tar == "multi_exe_main_dirname")return (info.multi_exe_main_dirname == "" ? "<EMPTY>" : info.multi_exe_main_dirname)+ '\\';
	if (tar == "multi_exe_sub_dirname")return (info.multi_exe_sub_dirname == "" ? "<EMPTY>" : info.multi_exe_sub_dirname )+ '\\';
	if (tar == "stu_exe_name")return (info.stu_exe_name == "" ? "<EMPTY>" : info.stu_exe_name);
	if (tar == "demo_exe_name")return (info.demo_exe_name == "" ? "<EMPTY>" : info.demo_exe_name);
	if (tar == "cmd_style")return (info.cmd_style == "" ? "<EMPTY>" : info.cmd_style);
	if (tar == "pipe_get_input_data_exe_name")return (info.pipe_get_input_data_exe_name == "" ? "<EMPTY>" : info.pipe_get_input_data_exe_name);
	if (tar == "pipe_data_file")return (info.pipe_data_file == "" ? "<EMPTY>" : info.pipe_data_file);
	if (tar == "redirection_data_dirname")return (info.redirection_data_dirname == "" ? "<EMPTY>" : info.redirection_data_dirname )+ '\\';
	if (tar == "timeout")return to_string(info.timeout);
	if (tar == "max_output_len")return to_string(info.max_output_len);
	if (tar == "tc_trim")return info.tc_trim;
	if (tar == "tc_lineskip")return to_string(info.tc_lineskip);
	if (tar == "tc_lineoffset")return to_string(info.tc_lineoffset);
	if (tar == "tc_ignoreblank")return to_string(info.tc_ignoreblank);
	if (tar == "tc_not_ignore_linefeed")return to_string(info.tc_not_ignore_linefeed);
	if (tar == "tc_maxdiff")return to_string(info.tc_maxdiff);
	if (tar == "tc_maxline")return to_string(info.tc_maxline);
	if (tar == "tc_display")return info.tc_display;
	if (tar == "items_num")return to_string(info.items_num);
	if (tar == "items_begin")return to_string(info.items_begin);
	if (tar == "items_end")return to_string(info.items_end);
	return "";
}

static void checkcfg_only(const string check_name, config_file_tools cfg, ST_HW_CHECK_EXE_CFG cfg_info, const vector<string> name_list)
{
	ostringstream oss;
	vector<string> list;
	bool is_correct = 1;
	int max_len = 0;
	ifstream file;
	cout << endl;
	cout << "====================================================================================================" << endl;
	cout << '[' + check_name + ']' << "配置信息如下：" << endl;
	cout << "====================================================================================================" << endl;
	if ((cfg_info.exe_style == "single" || cfg_info.exe_style == "multi") && cfg_info.name_list == "database") {
		string list[6] = { "db_host","db_port","db_name","db_username","db_curr_term","db_cno_list" };
		int max_len = 0;
		for (int i = 0; i < 6; i++) {
			max_len = max_len < (int)list[i].size() ? list[i].size() : max_len;
		}
		cout << "[数据库]：" << endl;
		//vector<string> da;
		//cfg.get_all_item("[数据库]",da);
		//for (size_t i = 0; i < da.size(); i++) {
		//	cout << da[i] << endl;
		//}
		for (int i = 0; i < 6; i++) {
			string tmp;
			if (i == 0) {
				unsigned int ip;
				cfg.item_get_ipaddr("[数据库]", list[i], ip);
				/*				cout << ip % 256 << endl;
								ip /= 256;
								cout << ip % 256 << endl;
								ip /= 256;
								cout << ip % 256 << endl;
								ip /= 256;
								cout << ip % 256 << endl;
								ip /= 256;*/
				tmp = ip_u_to_str(ip);
			}
			else if (i == 1) {
				int port;
				cfg.item_get_int("[数据库]", list[i], port);
				tmp = to_string(port);
			}
			else
				cfg.item_get_raw("[数据库]", list[i], tmp);
			tmp = remove_space_in_line(tmp, "all");
			if (tmp == "") {
				tmp = "<EMPTY>";
				is_correct = 0;
				oss << "[数据库]" << list[i] << "不存在" << endl;
			}
			cout << "  " << setw(max_len) << left << list[i] << " = " << tmp << endl;
		}
		cout << endl;
	}
	cout << '[' + check_name + "]：" << endl;
	list.push_back("exe_style");
	if (cfg_info.exe_style == "single") {
		list.push_back("name_list");
		list.push_back("single_exe_dirname");
		list.push_back("stu_exe_name");
	}
	if (cfg_info.exe_style == "multi") {
		list.push_back("name_list");
		list.push_back("multi_exe_main_dirname");
		list.push_back("multi_exe_sub_dirname");
		list.push_back("stu_exe_name");
	}
	list.push_back("demo_exe_name");
	list.push_back("cmd_style");
	list.push_back("max_output_len");
	list.push_back("timeout");
	if (cfg_info.cmd_style == "pipe") {
		list.push_back("pipe_get_input_data_exe_name");
		list.push_back("pipe_data_file");
	}
	if (cfg_info.cmd_style == "redirection") {
		list.push_back("redirection_data_dirname");
	}
	list.push_back("/n");
	list.push_back("tc_trim");
	list.push_back("tc_lineskip");
	list.push_back("tc_lineoffset");
	list.push_back("tc_ignoreblank");
	list.push_back("tc_not_ignore_linefeed");
	list.push_back("tc_maxdiff");
	list.push_back("tc_maxline");
	list.push_back("tc_display");
	list.push_back("/n");
	list.push_back("items_num");
	list.push_back("items_begin");
	list.push_back("items_end");
	for (size_t i = 0; i < list.size(); i++) {
		max_len = max_len < (int)list[i].size() ? list[i].size() : max_len;
	}
	for (size_t i = 0; i < list.size(); i++) {
		if (list[i] == "/n") {
			cout << endl;
			continue;
		}
		string tmp = find_s_incfg(cfg_info, list[i]);
		cout << "  " << setw(max_len) << left << list[i] << " = " << tmp << endl;
	}
	if (cfg_info.cmd_style == "pipe" || cfg_info.cmd_style == "redirection" || cfg_info.cmd_style == "main_with_arguments") {
		vector<string>* p;
		if (cfg_info.cmd_style == "pipe")
			p = &cfg_info.item_gnames;
		else if (cfg_info.cmd_style == "redirection")
			p = &cfg_info.item_fnames;
		else
			p = &cfg_info.item_args;
		for (int i = 0; i < cfg_info.items_num; i++) {
			cout << "  " << setw(max_len) << left << "item_name_" + to_string(i + 1) << " = " << (*p)[i] << endl;
		}
	}
	cout << "====================================================================================================" << endl;
	cout << endl;
	if ((cfg_info.item_gnames.size() > 0 && !cfg_info.is_gnames)) {
		oss << "item_gnames不连续" << endl;
		is_correct = 0;
	}
	if ((cfg_info.item_fnames.size() > 0 && !cfg_info.is_fnames)) {
		oss << "item_fnames不连续" << endl;
		is_correct = 0;
	}
	if ((cfg_info.item_args.size() > 0 && !cfg_info.is_args)) {
		oss << "item_args不连续" << endl;
		is_correct = 0;
	}
	if (cfg_info.cmd_style == "pipe" && cfg_info.item_gnames.size() == 0) {
		oss << "item_gnames不存在" << endl;
		is_correct = 0;
	}
	if (cfg_info.cmd_style == "redirection" && cfg_info.item_fnames.size() == 0) {
		oss << "item_fnames不存在" << endl;
		is_correct = 0;
	}
	if (cfg_info.cmd_style == "main_with_arguments" && cfg_info.item_args.size() == 0) {
		oss << "item_args不存在" << endl;
		is_correct = 0;
	}
	file.open(cfg_info.demo_exe_name);
	if (file.fail()) {
		oss << "demo_exe_name文件" << cfg_info.demo_exe_name << "不存在" << endl;
		is_correct = 0;
	}
	if (cfg_info.name_list != "database") {
		file.open(cfg_info.name_list);
		if (file.fail()) {
			oss << "name_list文件" << cfg_info.name_list << "不存在" << endl;
			is_correct = 0;
		}
	}
	for (size_t i = 0; i < name_list.size(); i++) {
		if (cfg_info.exe_style == "single") {
			string tmp, stu_info;
			tmp = name_list[i];
			stu_info = split_string_with_c(tmp, '-');
			stu_info += '-' + split_string_with_c(tmp, '-');
			tmp = cfg_info.single_exe_dirname + '\\' + stu_info + '-' + cfg_info.stu_exe_name;
			file.open(tmp);
			if (file.fail()) {
				oss << "文件" << tmp << "不存在" << endl;
				is_correct = 0;
			}
		}
		else if (cfg_info.exe_style == "multi") {
			string tmp, stu_info;
			tmp = name_list[i];
			stu_info = split_string_with_c(tmp, '-');
			stu_info += '-' + split_string_with_c(tmp, '-');
			tmp = cfg_info.multi_exe_main_dirname + '\\' + stu_info + '\\' + cfg_info.multi_exe_sub_dirname + '\\' + cfg_info.stu_exe_name;
			file.open(tmp);
			if (file.fail()) {
				oss << "文件" << tmp << "不存在" << endl;
				is_correct = 0;
			}
		}
		else
			break;
	}
	if (cfg_info.cmd_style == "pipe") {
		file.open(cfg_info.pipe_get_input_data_exe_name);
		if (file.fail()) {
			oss << "pipe_get_input_data_exe_name文件" << cfg_info.pipe_get_input_data_exe_name << "不存在" << endl;
			is_correct = 0;
		}
		file.open(cfg_info.pipe_data_file);
		if (file.fail()) {
			oss << "pipe_data_file文件" << cfg_info.pipe_data_file << "不存在" << endl;
			is_correct = 0;
		}
	}
	if (cfg_info.cmd_style == "redirection") {
		for (size_t i = 0; i < cfg_info.item_fnames.size(); i++) {
			string tmp = cfg_info.redirection_data_dirname;
			tmp += '\\' + cfg_info.item_fnames[i];
			file.open(tmp);
			if (file.fail()) {
				oss << "文件" << tmp << "不存在" << endl;
				is_correct = 0;
			}
		}
	}
	if (!is_correct) {
		cout << endl << "[--严重错误--] 配置文件存在下列的错误：" << endl;
		cout << oss.str() << endl;
	}
	file.close();
}

//static bool isDirectoryExists(const std::string& folderPath) {
//	struct stat info;
//	if (stat(folderPath.c_str(), &info) != 0) {
//		return false;
//	}
//	return (info.st_mode & S_IFDIR) != 0;
//}
//
//static void proceed_name_list(ST_HW_CHECK_EXE_CFG info,vector<string>& list)
//{
//	if (info.exe_style == "none")return;
//	vector<string>done_list;
//	for (size_t i = 0; i < list.size(); i++) {
//		if (info.exe_style == "single")continue;
//		string tmp, stu_cno, stu_no, stu_name, dir, exe;
//		tmp = list[i] + '-';
//		stu_cno = split_string_with_c(tmp, '-');
//		stu_no = split_string_with_c(tmp, '-');
//		stu_name = split_string_with_c(tmp, '-');
//		dir = info.multi_exe_main_dirname + '\\' + stu_no + '-' + stu_cno + '\\' /*+ info.multi_exe_sub_dirname*/;
//		exe = info.stu_exe_name;
//		if (is_directory_empty_win(dir)) {
//			done_list.push_back(list[i]);
//		}
//	}
//	list = done_list;
//}

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

	string db_host, db_port, db_name, db_username, db_passwd, db_currterm, db_cno_list;
	cfg.item_get_raw("[数据库]", "db_host", db_host);
	cfg.item_get_raw("[数据库]", "db_port", db_port);
	cfg.item_get_raw("[数据库]", "db_name", db_name);
	cfg.item_get_raw("[数据库]", "db_username", db_username);
	cfg.item_get_raw("[数据库]", "db_passwd", db_passwd);
	cfg.item_get_raw("[数据库]", "db_currterm", db_currterm);
	cfg.item_get_raw("[数据库]", "db_cno_list", db_cno_list);

	db_host=remove_space_in_line(db_host, "all");
	db_port=remove_space_in_line(db_port, "all");
	db_name=remove_space_in_line(db_name, "all");
	db_username=remove_space_in_line(db_username, "all");
	db_passwd=remove_space_in_line(db_passwd, "all");
	db_currterm=remove_space_in_line(db_currterm, "all");
	db_cno_list=remove_space_in_line(db_cno_list, "all");
	
	ST_HW_CHECK_EXE_CFG cfg_info;
	proceed_cfg_info(cfg, cfg_info, '['+check_name+']', debug_level, is_checkcfg_only);

#if main_debug
	string s1 = "1,2,3,",s2="1 2 3 ",s3="1\t2\t3\t",t;
	while ((t = split_string_with_c(s1, ',')) != "") {
		cout << t << endl;
	}
	while ((t = split_string_with_c(s2, ' ')) != "") {
		cout << t << endl;
	}
	while ((t = split_string_with_c(s3, ' ')) != "") {
		cout << t << endl;
	}
	while ((t = split_string_with_c(s3, '\t')) != "") {
		cout << t << endl;
	}
#endif

	vector<string>name_list;
	if (!is_checkcfg_only) {
		MYSQL* mysql;
		MYSQL_RES* result;
		MYSQL_ROW  row;

		/* 初始化 mysql 变量，失败返回NULL */
		if ((mysql = mysql_init(NULL)) == NULL) {
			cerr << "mysql_init failed" << endl;
			return -1;
		}

		/* 连接数据库，失败返回NULL
			1、mysqld没运行
			2、没有指定名称的数据库存在 */
		if (mysql_real_connect(mysql, db_host.c_str()/*+':'+db_port).c_str()*/, db_username.c_str(), db_passwd.c_str(), db_name.c_str(), 0, NULL, 0) == NULL) {
			cerr << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}

		/* 设置字符集，否则读出的字符乱码 */
		mysql_set_character_set(mysql, "gbk");

		if (cfg_info.name_list == "database") {
			string db_cno_list_tmp=db_cno_list+',';
			while (1) {
				string cno_head = split_string_with_c(db_cno_list_tmp,',');
				if (cno_head == "")
					break;
				string search_info = "select stu_cno, stu_no, stu_name from view_student_for_oop  where stu_cno = \"" + cno_head + "\" and stu_cno_is_del = '0' ";
				if (mysql_query(mysql, search_info.c_str())) {
					cerr << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
					return -1;
				}

				/* 将查询结果存储起来，出现错误则返回NULL
					注意：查询结果为NULL，不会返回NULL */
				if ((result = mysql_store_result(mysql)) == NULL) {
					cerr << "mysql_store_result failed" << endl;
					return -1;
				}

				/* 打印当前查询到的记录的数量 */
				if(!is_checkcfg_only)
					cout << "select return " << (int)mysql_num_rows(result) << " records" << endl;

				/* 循环读取所有满足条件的记录
					2、row的排列顺序与select返回的列顺序相同，本例：
						row[0] <=> stu_sex
						row[1] <=> stu_no
						row[2] <=> stu_name
						row[3] <=> NULL */
				while ((row = mysql_fetch_row(result)) != NULL) {
					string stu_info;
					stu_info = row[0];
					stu_info += '-';
					stu_info += row[1];
					stu_info += '-';
					stu_info += row[2];
					name_list.push_back(stu_info);
				}

				/* 释放result，否则会丢失内存 */
				mysql_free_result(result);
			}
		}
		else {
			ifstream name_list_file;
			name_list_file.open(cfg_info.name_list,ios::in|ios::binary);
			if (name_list_file.fail()) {
				cerr << "无法打开文件：" << cfg_info.name_list << endl;
				return -1;
			}
			string line;
			while (getline(name_list_file, line)) {
				string stu_info[3];
				line = remove_space_in_line(line,"all");
				line = remove_comment_in_line(line,"#");
				line = remove_space_in_line(line, "all");
				if (line == "")continue;
				for (size_t i = 0; i < line.size(); i++)
					if (line[i] == '\t')line[i] = ' ';
				line += ' ';
				stu_info[0] = split_string_with_c(line,' ');
				stu_info[1] = split_string_with_c(line,' ');
				stu_info[2] = split_string_with_c(line,' ');
				if (stu_info[0] == "" || stu_info[1] == "" || stu_info[2] == "") {
					cerr << "文件：" << cfg_info.name_list << "名单列表有误" << endl;
					return -1;
				}
				name_list.push_back(stu_info[0] + '-' + stu_info[1] + '-' + stu_info[2]);
			}
			name_list_file.close();
		}
		if(!is_checkcfg_only)
			cout << "总计拉取名单学生" << name_list.size() << "人" << endl;
		//getchar();
		if (!check_name_list(name_list)) {
			cerr << "学生名单有误！" << endl;
			return -1;
		}
	}
	
	//proceed_name_list(cfg_info,name_list);

	if (is_checkcfg_only) {
		checkcfg_only(check_name,cfg,cfg_info,name_list);
		return 0;
	}
	ofstream ofile;
	string ofname;
	ostringstream ofi;

	time_t now = time(0);
	string now_time,time_b,time_e;
	msg.str("");
	msg.clear();
	ofi << "exe_style" << '\t' << cfg_info.exe_style << endl;
	ofi << "cmd_style" << '\t' << cfg_info.cmd_style << endl;
	ofi << "name_list" << '\t' << cfg_info.name_list << endl;
	ofi << "stu_exe_name" << '\t' << cfg_info.stu_exe_name << endl;
	ofi << "statrt_time" << '\t' << ctime(&now) << endl;
	ofi << "序号\t课号\t学号\t姓名\t正确运行\t定时器创建失败\t管道方式打开失败\t启动定时器失败\t超时\t超过输出上限\t死循环\tTC通过总数\t";
	for (int i = cfg_info.items_begin-1; i < cfg_info.items_end; i++) {
		if (cfg_info.cmd_style == "normal")
			break;
		else if (cfg_info.cmd_style == "pipe") {
			ofi << cfg_info.item_gnames[i] << '\t';
		}
		else if (cfg_info.cmd_style == "redirection") {
			ofi << cfg_info.item_fnames[i] << '\t';
		}
		else {
			ofi << cfg_info.item_args[i] << '\t';
		}
	}
	ofi << endl;
	size_t pos;
	pos = cfg_info.demo_exe_name.find_last_of('\\');
	string demo_exe= cfg_info.demo_exe_name.substr(pos+1, cfg_info.demo_exe_name.size()-pos-1);
	vector<string> ans;
	if (1) {
		int ok = 0,
			create_timer_id_failed = 0,		//创建定时器ID失败
			popen_faliled = 0,				//管道方式打开可执行文件失败
			start_timer_failed = 0,			//启动定时器失败
			timeout = 0,					//超时
			max_output = 0,					//达到设定的输出上限（死循环输出，反正肯定不对了）
			killed_by_callback = 0,			//死循环（超时且fgetc阻塞）
			opc = 0;						//tc
		time_b = ctime(&now);
		time_b = time_b.substr(0, time_b.size() - 1);
		if (cfg_info.cmd_style == "normal") {
			st_CheckExec demo={cfg_info.demo_exe_name,demo_exe,cfg_info.max_output_len,cfg_info.timeout};
			demo.running();
			ans.push_back(demo.msg.str());
			if (demo.get_errno() == CheckExec_Errno::ok)	ok++;
			if (demo.get_errno() == CheckExec_Errno::create_timer_id_failed)	create_timer_id_failed++;
			if (demo.get_errno() == CheckExec_Errno::popen_faliled)	popen_faliled++;
			if (demo.get_errno() == CheckExec_Errno::start_timer_failed)	start_timer_failed++;
			if (demo.get_errno() == CheckExec_Errno::timeout)	timeout++;
			if (demo.get_errno() == CheckExec_Errno::max_output)	max_output++;
			if (demo.get_errno() == CheckExec_Errno::killed_by_callback)	killed_by_callback++;
		}
		else if (cfg_info.cmd_style == "pipe") {
			for (int i = cfg_info.items_begin - 1; i < cfg_info.items_end; i++) {
				st_CheckExec demo = {	cfg_info.pipe_get_input_data_exe_name+' '+
										cfg_info.pipe_data_file+' '+
										cfg_info.item_gnames[i]+" | "+
										cfg_info.demo_exe_name,
										demo_exe,cfg_info.max_output_len,cfg_info.timeout};
				demo.running();
				ans.push_back(demo.msg.str());
				if (demo.get_errno() == CheckExec_Errno::ok)	ok++;
				if (demo.get_errno() == CheckExec_Errno::create_timer_id_failed)	create_timer_id_failed++;
				if (demo.get_errno() == CheckExec_Errno::popen_faliled)	popen_faliled++;
				if (demo.get_errno() == CheckExec_Errno::start_timer_failed)	start_timer_failed++;
				if (demo.get_errno() == CheckExec_Errno::timeout)	timeout++;
				if (demo.get_errno() == CheckExec_Errno::max_output)	max_output++;
				if (demo.get_errno() == CheckExec_Errno::killed_by_callback)	killed_by_callback++;
			}
		}
		else if (cfg_info.cmd_style == "redirection") {
			for (int i = cfg_info.items_begin - 1; i < cfg_info.items_end; i++) {
				st_CheckExec demo = { cfg_info.demo_exe_name + " < " +
										cfg_info.redirection_data_dirname + '\\' +
										cfg_info.item_fnames[i],
										demo_exe,cfg_info.max_output_len,cfg_info.timeout };
				demo.running();
				ans.push_back(demo.msg.str());
				if (demo.get_errno() == CheckExec_Errno::ok)	ok++;
				if (demo.get_errno() == CheckExec_Errno::create_timer_id_failed)	create_timer_id_failed++;
				if (demo.get_errno() == CheckExec_Errno::popen_faliled)	popen_faliled++;
				if (demo.get_errno() == CheckExec_Errno::start_timer_failed)	start_timer_failed++;
				if (demo.get_errno() == CheckExec_Errno::timeout)	timeout++;
				if (demo.get_errno() == CheckExec_Errno::max_output)	max_output++;
				if (demo.get_errno() == CheckExec_Errno::killed_by_callback)	killed_by_callback++;
			}
		}
		else {
			for (int i = cfg_info.items_begin - 1; i < cfg_info.items_end; i++) {
				st_CheckExec demo = { cfg_info.demo_exe_name + " " +
										cfg_info.item_args[i],
										demo_exe,cfg_info.max_output_len,cfg_info.timeout };
				demo.running();
				ans.push_back(demo.msg.str());
				if (demo.get_errno() == CheckExec_Errno::ok)	ok++;
				if (demo.get_errno() == CheckExec_Errno::create_timer_id_failed)	create_timer_id_failed++;
				if (demo.get_errno() == CheckExec_Errno::popen_faliled)	popen_faliled++;
				if (demo.get_errno() == CheckExec_Errno::start_timer_failed)	start_timer_failed++;
				if (demo.get_errno() == CheckExec_Errno::timeout)	timeout++;
				if (demo.get_errno() == CheckExec_Errno::max_output)	max_output++;
				if (demo.get_errno() == CheckExec_Errno::killed_by_callback)	killed_by_callback++;
			}
		}
		time_e = ctime(&now);
		time_e = time_e.substr(0, time_e.size() - 1);
		msg << time_b << "参考答案生成情况" << endl;
		msg << "======================================================================" << endl;
		msg << "参考exe文件：" << cfg_info.demo_exe_name << endl;
		msg << "测试运行情况：";
		if (ok)msg << "正确运行=" << ok;
		if (create_timer_id_failed)msg << "定时器创建失败=" << create_timer_id_failed;
		if (popen_faliled)msg << "管道方式打开失败=" << popen_faliled;
		if (start_timer_failed)msg << "启动定时器失败=" << start_timer_failed;
		if (timeout)msg << "超时=" << timeout;
		if (max_output)msg << "超过输出上限=" << max_output;
		if (killed_by_callback)msg << "死循环=" << killed_by_callback;
		msg << endl << "时间：" << time_b << "-" << time_e << endl;
		msg << "======================================================================" << endl;
		cout << msg.str();
		msg.str(""); msg.clear();
	}
	
	if (cfg_info.exe_style != "none") {
		for (size_t i = 0; i < name_list.size(); i++) {
			time_b = ctime(&now);
			time_b = time_b.substr(0, time_b.size() - 1);
			int ok = 0,
				create_timer_id_failed = 0,		//创建定时器ID失败
				popen_faliled = 0,				//管道方式打开可执行文件失败
				start_timer_failed = 0,			//启动定时器失败
				timeout = 0,					//超时
				max_output = 0,					//达到设定的输出上限（死循环输出，反正肯定不对了）
				killed_by_callback = 0,			//死循环（超时且fgetc阻塞）
				opc = 0;						//tc
			vector<string>st;
			int ml = cfg_info.max_output_len, t = cfg_info.timeout;
			string tmp, stu_cno, stu_no, stu_name, full, exe;
			tmp = name_list[i] + '-';
			stu_cno = split_string_with_c(tmp, '-');
			stu_no = split_string_with_c(tmp, '-');
			stu_name = split_string_with_c(tmp, '-');
			if (cfg_info.exe_style == "single") {
				full = cfg_info.single_exe_dirname + '\\' + stu_no + '-' + stu_cno + '-' + cfg_info.stu_exe_name;
				exe = stu_cno + '-' + stu_no + '-' + cfg_info.stu_exe_name;
			}
			else {
				full= cfg_info.multi_exe_main_dirname + '\\' + stu_no + '-' + stu_cno + '\\' + cfg_info.multi_exe_sub_dirname + '\\' + cfg_info.stu_exe_name;
				exe = cfg_info.stu_exe_name;
			}

			if (1) {
				ifstream tmp;
				tmp.open(full);
				if (!tmp.good()) {
					msg << time_b << "学生答案生成情况" << endl;
					msg << "======================================================================" << endl;
					msg << "序号：" << i + 1 << "学号：" << stu_no << " / 姓名：" << stu_name << " / 课号： " << stu_cno << endl;
					msg << "exe不存在" << endl;
					time_e = ctime(&now);
					time_e = time_e.substr(0, time_e.size() - 1);
					msg << "时间：" << time_b << "-" << time_e << endl;
					msg << "======================================================================" << endl;
					cout << msg.str();
					msg.str(""); msg.clear();
					ofi << i + 1 << '\t' << "=text(\"" + stu_cno + "\", \"#\")" << '\t' << stu_no << '\t' << stu_name << '\t' << '/' << '\t'
						<< '/' << '\t' << '/' << '\t' << '/' << '\t'
						<< '/' << '\t' << '/' << '\t' << '/' << '\t' << 0 << '\t';
					for (size_t k = cfg_info.items_begin; k <= cfg_info.items_end; k++)
						ofi << 0 << '\t';
					ofi << endl;
					continue;
				}
				tmp.close();
			}

			if (cfg_info.cmd_style == "normal") {
				st_CheckExec stu = { full,exe,ml,t };
				stu.running();
				st.push_back(stu.msg.str());
				if (stu.get_errno() == CheckExec_Errno::ok)	ok++;
				if (stu.get_errno() == CheckExec_Errno::create_timer_id_failed)	create_timer_id_failed++;
				if (stu.get_errno() == CheckExec_Errno::popen_faliled)	popen_faliled++;
				if (stu.get_errno() == CheckExec_Errno::start_timer_failed)	start_timer_failed++;
				if (stu.get_errno() == CheckExec_Errno::timeout)	timeout++;
				if (stu.get_errno() == CheckExec_Errno::max_output)	max_output++;
				if (stu.get_errno() == CheckExec_Errno::killed_by_callback)	killed_by_callback++;
			}
			else if (cfg_info.cmd_style == "pipe") {
				for (int j = cfg_info.items_begin - 1; j < cfg_info.items_end; j++) {
					st_CheckExec stu = { cfg_info.pipe_get_input_data_exe_name + ' ' +
											cfg_info.pipe_data_file + ' ' +
											cfg_info.item_gnames[j] + " | " +
											full,
											exe,ml,t };
					stu.running();
					st.push_back(stu.msg.str());
					if (stu.get_errno() == CheckExec_Errno::ok)	ok++;
					if (stu.get_errno() == CheckExec_Errno::create_timer_id_failed)	create_timer_id_failed++;
					if (stu.get_errno() == CheckExec_Errno::popen_faliled)	popen_faliled++;
					if (stu.get_errno() == CheckExec_Errno::start_timer_failed)	start_timer_failed++;
					if (stu.get_errno() == CheckExec_Errno::timeout)	timeout++;
					if (stu.get_errno() == CheckExec_Errno::max_output)	max_output++;
					if (stu.get_errno() == CheckExec_Errno::killed_by_callback)	killed_by_callback++;
				}
			}
			else if (cfg_info.cmd_style == "redirection") {
				for (int j = cfg_info.items_begin - 1; j < cfg_info.items_end; j++) {
					st_CheckExec stu = {	full + " < " +
											cfg_info.redirection_data_dirname + '\\' +
											cfg_info.item_fnames[j],
											exe,ml,t };
					stu.running();
					st.push_back(stu.msg.str());
					if (stu.get_errno() == CheckExec_Errno::ok)	ok++;
					if (stu.get_errno() == CheckExec_Errno::create_timer_id_failed)	create_timer_id_failed++;
					if (stu.get_errno() == CheckExec_Errno::popen_faliled)	popen_faliled++;
					if (stu.get_errno() == CheckExec_Errno::start_timer_failed)	start_timer_failed++;
					if (stu.get_errno() == CheckExec_Errno::timeout)	timeout++;
					if (stu.get_errno() == CheckExec_Errno::max_output)	max_output++;
					if (stu.get_errno() == CheckExec_Errno::killed_by_callback)	killed_by_callback++;
				}
			}
			else {
				for (int i = cfg_info.items_begin - 1; i < cfg_info.items_end; i++) {
					st_CheckExec stu = { full + " " +
											cfg_info.item_args[i],
											exe,ml,t };
					stu.running();
					st.push_back(stu.msg.str());
					if (stu.get_errno() == CheckExec_Errno::ok)	ok++;
					if (stu.get_errno() == CheckExec_Errno::create_timer_id_failed)	create_timer_id_failed++;
					if (stu.get_errno() == CheckExec_Errno::popen_faliled)	popen_faliled++;
					if (stu.get_errno() == CheckExec_Errno::start_timer_failed)	start_timer_failed++;
					if (stu.get_errno() == CheckExec_Errno::timeout)	timeout++;
					if (stu.get_errno() == CheckExec_Errno::max_output)	max_output++;
					if (stu.get_errno() == CheckExec_Errno::killed_by_callback)	killed_by_callback++;
				}
			}
			//st_CheckExec stu = { tmp,stu_info + '-' + cfg_info.stu_exe_name,cfg_info.max_output_len,cfg_info.timeout };
			vector<bool>res;
			
			msg << time_b << "学生答案生成情况" << endl;
			msg << "======================================================================" << endl;
			msg << "序号：" << i + 1 << "学号：" << stu_no << " / 姓名：" << stu_name << " / 课号： " << stu_cno << endl;
			msg << "测试运行情况：";
			if (ok)msg << "正确运行=" << ok;
			if (create_timer_id_failed)msg << "定时器创建失败=" << create_timer_id_failed;
			if (popen_faliled)msg << "管道方式打开失败=" << popen_faliled;
			if (start_timer_failed)msg << "启动定时器失败=" << start_timer_failed;
			if (timeout)msg << "超时=" << timeout;
			if (max_output)msg << "超过输出上限=" << max_output;
			if (killed_by_callback)msg << "死循环=" << killed_by_callback;
			msg << endl;
			for (int j = cfg_info.items_begin; j <= cfg_info.items_end; j++) {
				int k = j - cfg_info.items_begin;
				istringstream s1(st[k]), s2(ans[k]);
				txt_compare tc = { s1,s2,cfg_info.tc_trim,cfg_info.tc_display,cfg_info.tc_lineskip,
									cfg_info.tc_lineoffset,cfg_info.tc_maxdiff,cfg_info.tc_maxline
									,cfg_info.tc_ignoreblank,cfg_info.tc_not_ignore_linefeed ,0};
				if (!tc.compare()) {
					opc++;
					res.push_back(1);
				}
				else {
					res.push_back(0);
				}
					
			}
			msg << "逐项正确性：";
			for (size_t k = 0; k < res.size(); k++)msg << res[k];
			msg << endl << "tc正确项数：" << opc << endl;
			time_e = ctime(&now);
			time_e = time_e.substr(0, time_e.size() - 1);
			msg << "时间：" << time_b << "-" << time_e << endl;
			msg << "======================================================================" << endl;
			cout << msg.str();
			msg.str(""); msg.clear();
			ofi << i + 1 << '\t' << "=text(\"" + stu_cno +"\", \"#\")" << '\t' << stu_no << '\t' << stu_name << '\t' << ok << '\t'
				<< create_timer_id_failed << '\t' << popen_faliled << '\t' << start_timer_failed << '\t' 
				<< timeout << '\t' << max_output << '\t' << killed_by_callback << '\t' << opc << '\t';
			for (size_t k = 0; k < res.size(); k++)
				ofi << res[k] << '\t';
			ofi << endl;
		}
		tm tm_now = *localtime(&now);
		char time_buf[32];
		strftime(time_buf, sizeof(time_buf), "%Y-%m-%d-%H-%M-%S", &tm_now);
		now_time=time_buf;
		ofname = "check-result-2452839-" + now_time + '-' + cfg_info.exe_style + '-'
			+ cfg_info.cmd_style + (cfg_info.name_list == "database" ? "database" : "txt") + '-' + cfg_info.stu_exe_name + ".xls";
		ofile.open(ofname,ios::out);
		ofile << ofi.str();
		if (ofile.fail()) {
			cerr << "文件" << ofname << "生成失败" << endl;
			return -1;
		}
		else {
			now_time = ctime(&now);
			now_time = now_time.substr(0, now_time.size() - 1);
			cout << now_time << " 检查结果文件[" << ofname << "]已生成." << endl;
		}
		ofile.close();
	}
	return 0;
}

