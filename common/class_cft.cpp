/* 2452839 徐川 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include<cstring>

/* 添加自己需要的头文件，注意限制 */
#include "../include/class_cft.h"
using namespace std;

static string proceed_line(string raw_line)
{
	/* 按需完成，对读入的每行内容进行预处理，例如去掉注释、去掉行尾的换行符等 */
	string ret=raw_line;
	for (int i = 0; i < (int)raw_line.size(); i++) {
		if(raw_line[i]=='#'||raw_line[i]==';' || (raw_line[i]=='/' && raw_line[i+1]=='/')) {
			ret = raw_line.substr(0,i);
			break;
		}
	}
	int x = 0, y = ret.size();
	while (x < y && (ret[x] == ' ' || ret[x] == '\t')) x++;
	while (y > x && (ret[y - 1] == ' ' || ret[y - 1] == '\t' || ret[y - 1] == '\n' || ret[y - 1] == '\r')) y--;
	ret = ret.substr(x, y - x);
	return ret;
}

static bool compare_string(const string& s1, const string& s2, const bool is_case_sensitive)
{
	/* 按需完成，比较两个字符串是否相等，考虑大小写敏感与否 */
	if (is_case_sensitive) {
		return s1 == s2;
	}
	else {
		if (s1.size() != s2.size()) return false;
		for (int i = 0; i < (int)s1.size(); i++) {
			if (tolower(s1[i]) != tolower(s2[i])) return false;
		}
		return true;
	}
}

static void insert_to_vector_if_not_exist(vector< SPAIR >& vec,const SPAIR& val)
{
	/* 按需完成，将val插入到vec中，如果vec中已存在相同组名的项，则将val的项合并到已有项中 */
	for (vector<SPAIR>::iterator one_pair = vec.begin(); one_pair != vec.end(); ++one_pair) {
		if (one_pair->first == val.first) {
			one_pair->second.insert(one_pair->second.end(), val.second.begin(), val.second.end());
			return;
		}
	}
	vec.push_back(val);
}

/* 给出各种自定义函数的实现（已给出的内容不全） */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::config_file_tools(const char* const _cfgname, const enum BREAK_CTYPE _ctype) : is_read_succeed(false)
{
	ifstream fin;
	this->cfgname = string(_cfgname);
	this->item_separate_character_type = _ctype;
	fin.open(this->cfgname.c_str(), ios::in);
	if (!fin.is_open()) {
		/* 文件打开失败的处理 */
		cerr << "配置文件[" << this->cfgname << "]打开失败!" << endl;
		return;
	}
	vector< SPAIR > lines;
	SPAIR tmp;
	string line;
	bool simple= false;
	int cnt = 0;
	while (getline(fin, line)) {
		cnt++;
		if (line.size() > MAX_LINE) {
			cerr << "非法格式的配置文件，第[" << cnt << "]行超过最大长度 1024." << endl;
			fin.close();
			is_read_succeed = false;
			return;
		}
		line = proceed_line(line);
		if (line.empty()) continue;
		if ((line[0] != '[' || line[line.size() - 1] != ']')) {
			if (!simple) {
				simple = true;
				tmp.first = SIMPLE_GNAME;
			}
			tmp.second.push_back(line);
		}
		else {
			if (!simple) simple = true;
			if (!tmp.first.empty() || !tmp.second.empty()) {
				insert_to_vector_if_not_exist(lines,tmp);
				tmp.second.clear();
			}
			line=line.substr(1, line.size() - 2);
			line = proceed_line(line);
			if (line.empty()) {
				tmp.first = SIMPLE_GNAME;
			}
			else {
				tmp.first = '[' + line + ']';
			}
		}
	}
	if (!tmp.first.empty() || !tmp.second.empty()) {
		insert_to_vector_if_not_exist(lines, tmp);
		tmp.second.clear();
	}
	fin.close();
	if (lines.empty()) {
		cerr << "配置文件全部是注释语句或空行." << endl;
		is_read_succeed = false;
		return;
	}
	this->cfg_list = lines;
	/* 读取文件内容并存储到自定义结构中，按需完成 */
	is_read_succeed = true;
	/* 按需完成 */
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::config_file_tools(const string& _cfgname, const enum BREAK_CTYPE _ctype):config_file_tools(_cfgname.c_str(), _ctype){}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::~config_file_tools()
{
	/* 按需完成 */
}


/***************************************************************************
  函数名称：
  功    能：判断读配置文件是否成功
  输入参数：
  返 回 值：true - 成功，已读入所有的组/项
		   false - 失败，文件某行超长/文件全部是注释语句
  说    明：
***************************************************************************/
bool config_file_tools::is_read_succeeded() const
{
	/* 按需完成，根据需要改变return的值 */
	return is_read_succeed;
}

/***************************************************************************
  函数名称：
  功    能：返回配置文件中的所有组
  输入参数：vector <string>& ret : vector 中每项为一个组名
  返 回 值：读到的组的数量（简单配置文件的组数量为1，组名为"）
  说    明：
***************************************************************************/
int config_file_tools::get_all_group(vector <string>& ret)
{
	/* 按需完成，根据需要改变return的值 */
	ret.clear();
	for (vector<SPAIR>::const_iterator one_pair = this->cfg_list.begin(); one_pair != this->cfg_list.end(); ++one_pair){
		ret.push_back(one_pair->first);
	}
	return ret.size();
}

/***************************************************************************
  函数名称：
  功    能：查找指定组的所有项并返回项的原始内容
  输入参数：const char* const group_name：组名
		   vector <string>& ret：vector 中每项为一个项的原始内容
		   const bool is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：项的数量，0表示空
  说    明：
***************************************************************************/
int config_file_tools::get_all_item(const char* const group_name, vector <string>& ret, const bool is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	ret.clear();
	for (int i = 0; i < (int)this->cfg_list.size(); i++) {
		if (compare_string(this->cfg_list[i].first, group_name, is_case_sensitive)) {
			ret = this->cfg_list[i].second;
			return ret.size();
		}
	}
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::get_all_item(const string& group_name, vector <string>& ret, const bool is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	return this->get_all_item(group_name.c_str(), ret, is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的原始内容（=后的所有字符，string方式）
  输入参数：const char* const group_name
		   const char* const item_name
		   string &ret
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_raw(const char* const group_name, const char* const item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	for (vector<SPAIR>::iterator one_pair = this->cfg_list.begin(); one_pair != this->cfg_list.end(); ++one_pair) {
		if (compare_string(one_pair->first, group_name, group_is_case_sensitive)) {
			for (vector<string>::iterator one_item_it = one_pair->second.begin(); one_item_it != one_pair->second.end(); ++one_item_it){
				string& one_item = *one_item_it;
				size_t pos;
				if (this->item_separate_character_type == BREAK_CTYPE::Equal) {
					pos = one_item.find_first_of('=');
				}
				else if (this->item_separate_character_type == BREAK_CTYPE::Space) {
					pos = one_item.find_first_of(" \t");
				}
				else {
					// 未知分隔符类型
					continue;
				}
				if (pos == string::npos) continue; //未找到分隔符，无法匹配项目名
				string item_name_in_cfg = one_item.substr(0, pos);
				item_name_in_cfg = proceed_line(item_name_in_cfg);
				if (compare_string(item_name_in_cfg, item_name, item_is_case_sensitive)) {
					// 找到匹配的项名
					ret = one_item.substr(pos + 1);
					return 1;
				}
			}
		}
	}
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_raw(const string& group_name, const string& item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_raw(group_name.c_str(), item_name.c_str(), ret, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：1 - 该项的项名存在
		   0 - 该项的项名不存在
  说    明：
***************************************************************************/
int config_file_tools::item_get_null(const char* const group_name, const char* const item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	for (vector<SPAIR>::iterator one_pair = this->cfg_list.begin(); one_pair != this->cfg_list.end(); ++one_pair) {
		if (compare_string(one_pair->first, group_name, group_is_case_sensitive)) {
			for (vector<string>::iterator one_item_it = one_pair->second.begin(); one_item_it != one_pair->second.end(); ++one_item_it) {
				string& one_item = *one_item_it;
				size_t pos;
				if (this->item_separate_character_type == BREAK_CTYPE::Equal) {
					pos = one_item.find_first_of('=');
				}
				else if (this->item_separate_character_type == BREAK_CTYPE::Space) {
					pos = one_item.find_first_of(" \t");
				}
				else {
					// 未知分隔符类型
					continue;
				}
				if (pos == string::npos) continue; //未找到分隔符，无法匹配项目名
				string item_name_in_cfg = one_item.substr(0, pos);
				item_name_in_cfg = proceed_line(item_name_in_cfg);
				if (compare_string(item_name_in_cfg, item_name, item_is_case_sensitive)) {
					// 找到匹配的项名
					return 1;
				}
			}
		}
	}
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_null(const string& group_name, const string& item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_null(group_name.c_str(), item_name.c_str(), group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   char& value                                ：读到的char的值（返回1时可信，返回0则不可信）
		   const char* const choice_set = nullptr     ：合法的char的集合（例如："YyNn"表示合法输入为Y/N且不分大小写，该参数有默认值nullptr，表示全部字符，即不检查）
		   const char def_value = DEFAULT_CHAR_VALUE  ：读不到/读到非法的情况下的默认值，该参数有默认值DEFAULT_CHAR_VALUE，分两种情况
															当值是   DEFAULT_CHAR_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_CHAR_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：1 - 取到正确值
			   未取到值/未取到正确值，设置了缺省值（包括设为缺省值）
		   0 - 未取到（只有为未指定默认值的情况下才会返回0）
  说    明：
***************************************************************************/
int config_file_tools::item_get_char(const char* const group_name, const char* const item_name, char& value,
						const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	std::istringstream iss;
	/* 先取原始内容 */
	string raw_content;
	int ret = this->item_get_raw(group_name, item_name, raw_content, group_is_case_sensitive, item_is_case_sensitive);
	char temp_char;
	if (ret == 0) {
		/* 未取到值 */
		if (def_value != DEFAULT_CHAR_VALUE) {
			value = def_value;
			return 1;
		}
		else {
			return 0;
		}
	}
	/* 取到了原始内容，进行转换 */
	iss.str(raw_content);
	iss >> temp_char;
	if (iss.fail() || !iss.eof()) {
		/* 转换失败 */
		if (def_value != DEFAULT_CHAR_VALUE) {
			value = def_value;
			return 1;
		}
		else {
			return 0;
		}
	}
	value = temp_char;
	return 1;
	/* 按需完成，根据需要改变return的值 */
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_char(const string& group_name, const string& item_name, char& value,
						const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_char(group_name.c_str(), item_name.c_str(), value, choice_set, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为int型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   int& value                                 ：读到的int的值（返回1时可信，返回0则不可信）
		   const int min_value = INT_MIN              : 期望数据范围的下限，默认为INT_MIN
		   const int max_value = INT_MAX              : 期望数据范围的上限，默认为INT_MAX
		   const int def_value = DEFAULT_INT_VALUE    ：读不到/读到非法的情况下的默认值，该参数有默认值 DEFAULT_INT_VALUE，分两种情况
															当值是   DEFAULT_INT_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_INT_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_int(const char* const group_name, const char* const item_name, int& value,
						const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	std::istringstream iss;
	/* 先取原始内容 */
	string raw_content;
	int ret = this->item_get_raw(group_name, item_name, raw_content, group_is_case_sensitive, item_is_case_sensitive);
	int temp_int;
	if (ret == 0) {
		/* 未取到值 */
		if (def_value != DEFAULT_INT_VALUE) {
			value = def_value;
			return 1;
		}
		else {
			return 0;
		}
	}
	/* 取到了原始内容，进行转换 */
	iss.str(raw_content);
	iss >> temp_int;
	if (iss.fail() || !iss.eof() || temp_int < min_value || temp_int > max_value) {
		/* 转换失败或不在范围内 */
		if (def_value != DEFAULT_INT_VALUE) {
			value = def_value;
			return 1;
		}
		else {
			return 0;
		}
	}
	value = temp_int;
	return 1;
	/* 按需完成，根据需要改变return的值 */
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_int(const string& group_name, const string& item_name, int& value,
						const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_int(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为double型
  输入参数：const char* const group_name                  ：组名
		   const char* const item_name                   ：项名
		   double& value                                 ：读到的int的值（返回1时可信，返回0则不可信）
		   const double min_value = __DBL_MIN__          : 期望数据范围的下限，默认为INT_MIN
		   const double max_value = __DBL_MAX__          : 期望数据范围的上限，默认为INT_MAX
		   const double def_value = DEFAULT_DOUBLE_VALUE ：读不到/读到非法的情况下的默认值，该参数有默认值DEFAULT_DOUBLE_VALUE，分两种情况
																当值是   DEFAULT_DOUBLE_VALUE 时，返回0（值不可信）
																当值不是 DEFAULT_DOUBLE_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false     : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false      : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_double(const char* const group_name, const char* const item_name, double& value,
						const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	std::istringstream iss;
	/* 先取原始内容 */
	string raw_content;
	int ret = this->item_get_raw(group_name, item_name, raw_content, group_is_case_sensitive, item_is_case_sensitive);
	double temp_double;
	if (ret == 0) {
		/* 未取到值 */
		if (def_value != DEFAULT_DOUBLE_VALUE) {
			value = def_value;
			return 1;
		}
		else {
			return 0;
		}
	}
	/* 取到了原始内容，进行转换 */
	iss.str(raw_content);
	iss >> temp_double;
	if (iss.fail() || !iss.eof() || temp_double < min_value || temp_double > max_value) {
		/* 转换失败或不在范围内 */
		if (def_value != DEFAULT_DOUBLE_VALUE) {
			value = def_value;
			return 1;
		}
		else {
			return 0;
		}
	}
	value = temp_double;
	return 1;
	/* 按需完成，根据需要改变return的值 */
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_double(const string& group_name, const string& item_name, double& value,
						const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_double(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char * / char []型
  输入参数：const char* const group_name                  ：组名
		   const char* const item_name                   ：项名
		   char *const value                             ：读到的C方式的字符串（返回1时可信，返回0则不可信）
		   const int str_maxlen                          ：指定要读的最大长度（含尾零）
																如果<1则返回空串(不是DEFAULT_CSTRING_VALUE，虽然现在两者相同，但要考虑default值可能会改)
																如果>MAX_STRLEN 则上限为MAX_STRLEN
		   const char* const def_str                     ：读不到情况下的默认值，该参数有默认值DEFAULT_CSTRING_VALUE，分两种情况
																当值是   DEFAULT_CSTRING_VALUE 时，返回0（值不可信）
																当值不是 DEFAULT_CSTRING_VALUE 时，令value=def_value并返回1（注意，不是直接=）
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：1、为简化，未对\"等做转义处理，均按普通字符
		   2、含尾零的最大长度为str_maxlen，调用时要保证有足够空间
		   3、如果 str_maxlen 超过了系统预设的上限 MAX_STRLEN，则按 MAX_STRLEN 取
***************************************************************************/
int config_file_tools::item_get_cstring(const char* const group_name, const char* const item_name, char* const value,
						const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	std::istringstream iss;
	/* 先取原始内容 */
	string raw_content;
	int ret = this->item_get_raw(group_name, item_name, raw_content, group_is_case_sensitive, item_is_case_sensitive);
	if (str_maxlen < 1) {
		/* 指定长度小于1，返回空串 */
		value[0] = '\0';
		return 1;
	}
	int effective_maxlen = (str_maxlen > MAX_STRLEN) ? MAX_STRLEN : str_maxlen;
	if (ret == 0) {
		/* 未取到值 */
		if (def_value != DEFAULT_CSTRING_VALUE) {
			/* 设定了默认值 */
			strncpy(value, def_value, effective_maxlen - 1);
			value[effective_maxlen - 1] = '\0'; // 确保尾零
			return 1;
		}
		else {
			/* 未设定默认值 */
			return 0;
		}
	}
	/* 取到了原始内容，进行转换 */
	iss.str(raw_content);
	char temp_str[MAX_STRLEN];
	iss >> temp_str;
	if (iss.fail() || !iss.eof()) {
		/* 转换失败 */
		if (def_value != DEFAULT_CSTRING_VALUE) {
			/* 设定了默认值 */
			strncpy(value, def_value, effective_maxlen - 1);
			value[effective_maxlen - 1] = '\0'; // 确保尾零
			return 1;
		}
		else {
			/* 未设定默认值 */
			return 0;
		}
	}
	strncpy(value, temp_str, effective_maxlen - 1);
	value[effective_maxlen - 1] = '\0'; // 确保尾零
	return 1;
	/* 按需完成，根据需要改变return的值 */
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_cstring(const string& group_name, const string& item_name, char* const value,
						const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)

{
	/* 本函数已实现 */
	return item_get_cstring(group_name.c_str(), item_name.c_str(), value, str_maxlen, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为 string 型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   string &value                              ：读到的string方式的字符串（返回1时可信，返回0则不可信）
		   const string &def_value                    ：读不到情况下的默认值，该参数有默认值DEFAULT_STRING_VALUE，分两种情况
															当值是   DEFAULT_STRING_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_STRING_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：为简化，未对\"等做转义处理，均按普通字符
***************************************************************************/
int config_file_tools::item_get_string(const char* const group_name, const char* const item_name, string& value,
						const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	std::istringstream iss;
	/* 先取原始内容 */
	string raw_content;
	int ret = this->item_get_raw(group_name, item_name, raw_content, group_is_case_sensitive, item_is_case_sensitive);
	if (ret == 0) {
		/* 未取到值 */
		if (def_value != DEFAULT_STRING_VALUE) {
			value = def_value;
			return 1;
		}
		else {
			return 0;
		}
	}
	/* 取到了原始内容，进行转换 */
	string temp_str;
	iss.str(raw_content);
	iss >> temp_str;
	if (iss.fail() || !iss.eof()) {
		/* 转换失败 */
		if (def_value != DEFAULT_STRING_VALUE) {
			value = def_value;
			return 1;
		}
		else {
			return 0;
		}
	}
	value = temp_str;
	return 1;
	/* 按需完成，根据需要改变return的值 */
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_string(const string& group_name, const string& item_name, string& value,
						const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_string(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为 IPv4 地址的32bit整型（主机序）
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   unsigned int &value                        ：读到的IP地址，32位整型方式（返回1时可信，返回0则不可信）
		   const unsigned int &def_value              ：读不到情况下的默认值，该参数有默认值DEFAULT_IPADDR_VALUE，分两种情况
															当值是   DEFAULT_IPADDR_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_IPADDR_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_ipaddr(const char* const group_name, const char* const item_name, unsigned int& value,
						const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	std::istringstream iss;
	/* 先取原始内容 */
	string raw_content;
	int ret = this->item_get_raw(group_name, item_name, raw_content, group_is_case_sensitive, item_is_case_sensitive);
	unsigned int temp_ipaddr;
	if (ret == 0) {
		/* 未取到值 */
		if (def_value != DEFAULT_IPADDR_VALUE) {
			value = def_value;
			return 1;
		}
		else {
			return 0;
		}
	}
	/* 取到了原始内容，进行转换 */
	iss.str(raw_content);
	unsigned int byte1, byte2, byte3, byte4;
	char dot1, dot2, dot3;
	iss >> byte1 >> dot1 >> byte2 >> dot2 >> byte3 >> dot3 >> byte4;
	if (iss.fail() || !iss.eof() || dot1 != '.' || dot2 != '.' || dot3 != '.' ||
		byte1 > 255 || byte2 > 255 || byte3 > 255 || byte4 > 255) {
		/* 转换失败 */
		if (def_value != DEFAULT_IPADDR_VALUE) {
			value = def_value;
			return 1;
		}
		else {
			return 0;
		}
	}
	temp_ipaddr = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
	value = temp_ipaddr;
	return 1;
	/* 按需完成，根据需要改变return的值 */
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_ipaddr(const string& group_name, const string& item_name, unsigned int& value,
						const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_ipaddr(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}
