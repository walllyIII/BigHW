/* 2452839 徐川 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include<cmath>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */

static bool che_ip(string s, u_int& ret)
{
	int len = (int)s.length();
	int sum = 0;
	int dot_count = 0;
	bool flag = 0;
	for (int i = 0; i <= len; i++) {
		if (s[i] == '.' || s[i] == 0) {
			if (flag == 0)
				return 0;
			flag = 0;
			if (sum < 0 || sum>255)
				return 0;
			ret = (ret << 8) + sum;
			sum = 0;
			if (s[i] == '.')dot_count++;
			continue;
		}
		if (s[i] < '0' || s[i]>'9')
			return 0;
		else
			flag = 1;
		sum = sum * 10 + (s[i] - '0');
	}
	if (dot_count != 3)
		return 0;
	return 1;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	args_existed = 0;
	this->args_name = "";
	this->extargs_type = ST_EXTARGS_TYPE::null;
	this->extargs_num = 0;
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	args_existed = 0;
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;
	this->extargs_bool_default = def;
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	args_existed = 0;
	extargs_int_value = def;
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;
	this->extargs_int_default = def;
	this->extargs_int_min = _min;
	this->extargs_int_max = _max;
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	args_existed = 0;
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;
	this->extargs_int_default = extargs_int_value = set[def_of_set_pos];
	int n = 0;
	while (set[n]!= INVALID_INT_VALUE_OF_SET){n++;}
	this->extargs_int_set = new int[n+1];
	for (int i = 0; i <= n; i++) {
		this->extargs_int_set[i] = set[i];
	}
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	args_existed = 0;
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;
	this->extargs_string_default = extargs_string_value = def;
	if (che_ip(def, this->extargs_ipaddr_default))
		extargs_ipaddr_value = this->extargs_ipaddr_default;
	else
		extargs_ipaddr_default = extargs_ipaddr_value = 0;
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	args_existed = 0;
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;
	this->extargs_string_default = extargs_string_value =set[def_of_set_pos];
	int n = 0;
	while (set[n] != "") { n++; }
	this->extargs_string_set = new string[n+1];
	for (int i = 0; i <= n; i++) {
		this->extargs_string_set[i] = set[i];
	}
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_default、double_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const double	def, const double _min, const double _max)
{
	args_existed = 0;
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;
	this->extargs_double_default = extargs_double_value =def;
	this->extargs_double_min = _min;
	this->extargs_double_max = _max;
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_set_default、double_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const double* const set)
{
	args_existed = 0;
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;
	this->extargs_double_default = extargs_double_value = set[def_of_set_pos];
	int n = 0;
	while (abs(set[n]-INVALID_DOUBLE_VALUE_OF_SET) >DOUBLE_DELTA ) { n++; }
	this->extargs_double_set = new double[n+1];
	for (int i = 0; i <= n; i++) {
		this->extargs_double_set[i] = set[i];
	}
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
	if(this->args_name== "int_with_set_default" || this->args_name== "int_with_set_error"){
		delete[] this->extargs_int_set;
	}
	if (this->args_name == "str_with_set_default" || this->args_name == "str_with_set_error") {
		delete[] this->extargs_string_set;
	}
	if(this->args_name== "double_with_set_default" || this->args_name== "double_with_set_error"){
		delete[] this->extargs_double_set;
	}
	return;
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const double args_analyse_tools::get_double() const
{
	return this->extargs_double_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	u_int val = extargs_ipaddr_value;
	string a="", b="", c="", d="";
	a = to_string(val & 0xff);
	val >>= 8;
	b = to_string(val & 0xff);
	val >>= 8;
	c = to_string(val & 0xff);
	val >>= 8;
	d = to_string(val & 0xff);
	return d+"."+c+"."+b+"."+a;
}

static string ip_u_to_str(u_int ipaddr)
{
	string a = "", b = "", c = "", d = "";
	a = to_string(ipaddr & 0xff);
	ipaddr >>= 8;
	b = to_string(ipaddr & 0xff);
	ipaddr >>= 8;
	c = to_string(ipaddr & 0xff);
	ipaddr >>= 8;
	d = to_string(ipaddr & 0xff);
	return d + "." + c + "." + b + "." + a;
}

static int args_check(const char* const str, args_analyse_tools* const args)
{
	string s = str;
	args_analyse_tools* cur_arg = args;
	int i = 0;
	while (cur_arg[i].get_name()!="") {
		if(s==cur_arg[i].get_name()){
			return i;
		}
		i++;
	}
	return -1;
}

static bool is_in_int_set(const int val, const int* const set)
{
	int i = 0;
	while (set[i]!= INVALID_INT_VALUE_OF_SET)
	{
		if(val== set[i]){
			return true;
		}
		i++;
	}
	return false;
}

static bool is_in_int_set(const double val, const double* const set)
{
	int i = 0;
	while(set[i]!= INVALID_DOUBLE_VALUE_OF_SET)
	{
		if (abs(val - set[i]) < DOUBLE_DELTA) {
			return true;
		}
		i++;
	}
	return false;
}

static bool is_in_int_set(const string val, const string* const set)
{
	int i = 0;
	while(set[i]!= "")
	{
		if (val == set[i]) {
			return true;
		}
		i++;
	}
	return false;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			0  ：无后续参数
			1  ：有后续参数
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int i;
	for(i=1;i<argc;i++){
		int pos = args_check(argv[i], args);
		if (pos < 0) {
			if(follow_up_args)
				continue;
			else {
				cout << "参数["<<argv[i]<<"]格式非法(不是--开头的有效内容)." << endl;
				return -1;

			}
		}
		if (args[pos].args_existed == 1) {
			cout << "参数[" << args[pos].args_name << "]重复." << endl;
			return -1;
		}
		args[pos].args_existed = 1;
		if(args[pos].extargs_num == 1) {
			if (args[pos].extargs_type== ST_EXTARGS_TYPE::int_with_default) {
				int temp = stoi(argv[i + 1]);
				if(temp>=args[pos].extargs_int_min && temp<=args[pos].extargs_int_max)
					args[pos].extargs_int_value = temp;
				else
					args[pos].extargs_int_value = args[pos].extargs_int_default;
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
				int temp = stoi(argv[i + 1]);
				if (temp >= args[pos].extargs_int_min && temp <= args[pos].extargs_int_max)
					args[pos].extargs_int_value = temp;
				else {
					cout << "参数[" << args[pos].args_name << "]的附加参数值(" << temp << ")非法. (类型:int, 范围" << ("[" + to_string(args[pos].extargs_int_min) + ".." + to_string(args[pos].extargs_int_max) + "]") << ")" << endl;
					return -1;
				}
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::int_with_set_default) {
				int temp = stoi(argv[i + 1]);
				if (is_in_int_set(temp,args[pos].extargs_int_set)) 
					args[pos].extargs_int_value = temp;
				else 
					args[pos].extargs_int_value = args[pos].extargs_int_default;
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
				int temp = stoi(argv[i + 1]);
				if (is_in_int_set(temp, args[pos].extargs_int_set)) 
					args[pos].extargs_int_value = temp;
				else {
					string s="[";
					for (int j = 0; args[pos].extargs_int_set[j] != INVALID_INT_VALUE_OF_SET; j++) {
						if (j != 0)
							s += "/";
						s += to_string(args[pos].extargs_int_set[j]);
					}
					s += "])";
					cout << "参数[" << args[pos].args_name << "]的附加参数值(" << temp << ")非法. (类型:int, 可取值" << s << endl;
					return -1;
				}
					
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::double_with_default) {
				double temp = stod(argv[i + 1]);
				if (temp >= args[pos].extargs_double_min && temp <= args[pos].extargs_double_max)
					args[pos].extargs_double_value = temp;
				else
					args[pos].extargs_double_value = args[pos].extargs_double_default;
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::double_with_error) {
				double temp = stod(argv[i + 1]);
				if (temp >= args[pos].extargs_double_min && temp <= args[pos].extargs_double_max)
					args[pos].extargs_double_value = temp;
				else {
					cout << "参数[" << args[pos].args_name << "]的附加参数值(" << temp << ")非法. (类型:double, 范围" << "[" <<args[pos].extargs_double_min<< ".." <<args[pos].extargs_double_max << "]" << ")" << endl;
					return -1;
				}
					
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::double_with_set_default) {
				double temp = stod(argv[i + 1]);
				if (is_in_int_set(temp, args[pos].extargs_double_set))
					args[pos].extargs_double_value = temp;
				else
					args[pos].extargs_double_value = args[pos].extargs_double_default;
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
				double temp = stod(argv[i + 1]);
				if (is_in_int_set(temp, args[pos].extargs_double_set))
					args[pos].extargs_double_value = temp;
				else{
					cout << "参数[" << args[pos].args_name << "]的附加参数值(" << temp << ")非法. (类型:double, 可取值[";
					for (int j = 0; abs(args[pos].extargs_double_set[j] -INVALID_DOUBLE_VALUE_OF_SET)>DOUBLE_DELTA; j++) {
						if (j != 0)
							cout << "/";
						cout << args[pos].extargs_double_set[j];
					}
					cout << "])" << endl;
					return -1;
				}
					
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::str) {
				args[pos].extargs_string_value = string(argv[i + 1]);
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::str_with_set_default) {
				string temp = string(argv[i + 1]);
				if (is_in_int_set(temp, args[pos].extargs_string_set))
					args[pos].extargs_string_value = temp;
				else
					args[pos].extargs_string_value = args[pos].extargs_string_default;
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
				string temp = string(argv[i + 1]);
				if (is_in_int_set(temp, args[pos].extargs_string_set))
					args[pos].extargs_string_value = temp;
				else {
					string s = "[";
					for (int j = 0; args[pos].extargs_string_set[j]!=""; j++) {
						if (j != 0)
							s += "/";
						s += args[pos].extargs_string_set[j];
					}
					s += "])";
					cout << "参数[" << args[pos].args_name << "]的附加参数值(" << temp << ")非法. (类型:string, 可取值" << s << endl;;
					return -1;
				}
					
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
				u_int temp;
				if(che_ip((string)argv[i + 1], temp))
					args[pos].extargs_ipaddr_value = temp;
				else
					args[pos].extargs_ipaddr_value = args[pos].extargs_ipaddr_default;
			}
			else if (args[pos].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
				u_int temp;
				if (che_ip((string)argv[i + 1], temp))
					args[pos].extargs_ipaddr_value = temp;
				else {
					cout << "参数[" << args[pos].args_name << "]的附加参数值(" << argv[i+1]<<")非法. (类型:IP地址)" << endl;
					return -1;
				}
					
			}
			i++;
		}
		else {
			args[pos].extargs_int_value = args[pos].extargs_int_default;
			args[pos].extargs_double_value = args[pos].extargs_double_default;
			args[pos].extargs_string_value = args[pos].extargs_string_default;
			args[pos].extargs_ipaddr_value = args[pos].extargs_ipaddr_default;
		}
	}
	return i-1;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{
	int i = 0;
	int w1 = 4, w2 = 4, w3 = 7, w4 = 6, w5 = 5, w6 = 9;
	ostringstream oss;
	while (args[i].get_name() != "") {
		w1 = max(w1, (int)args[i].get_name().length());
		if(args[i].extargs_type== ST_EXTARGS_TYPE::boolean){
			w2 = max(w2, (int)sizeof("Bool"));
			w3 = max(w3, (int)sizeof("false"));
			if (args[i].existed())w5 = max(w5, (int)sizeof("0/1"));
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::int_with_default){
			w2 = max(w2, (int)sizeof("IntWithDefault"));
			w3 = max(w3, (int)to_string(args[i].extargs_int_default).length());
			if (args[i].existed())w5 = max(w5, (int)to_string(args[i].extargs_int_value).length());
			w6 = max(w6, (int)("["+to_string(args[i].extargs_int_min) + ".." + to_string(args[i].extargs_int_max) + "]").length());
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::int_with_error){
			w2 = max(w2, (int)sizeof("IntWithError"));
			w3 = max(w3, (int)sizeof("/"));
			if (args[i].existed())w5 = max(w5, (int)to_string(args[i].extargs_int_value).length());
			w6 = max(w6, (int)("["+to_string(args[i].extargs_int_min) + ".." + to_string(args[i].extargs_int_max)+"]").length());
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::int_with_set_default){
			w2 = max(w2, (int)sizeof("IntWithSETDefault"));
			w3 = max(w3, (int)to_string(args[i].extargs_int_default).length());
			if (args[i].existed())w5 = max(w5, (int)to_string(args[i].extargs_int_value).length());
			string s = "";
			for(int j=0; args[i].extargs_int_set[j]!= INVALID_INT_VALUE_OF_SET; j++){
				if(j!=0)
					s += "/";
				s += to_string(args[i].extargs_int_set[j]);
			}
			w6 = max(w6, (int)s.length());
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::int_with_set_error){
			w2 = max(w2, (int)sizeof("IntWithSETError"));
			w3 = max(w3, (int)sizeof("/"));
			if (args[i].existed())w5 = max(w5, (int)to_string(args[i].extargs_int_value).length());
			string s = "";
			for (int j = 0; args[i].extargs_int_set[j] != INVALID_INT_VALUE_OF_SET; j++) {
				if(j!=0)
					s += "/";
				s += to_string(args[i].extargs_int_set[j]);
			}
			w6 = max(w6, (int)s.length());
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::double_with_default){
			oss.str("");
			w2 = max(w2, (int)sizeof("DoubleWithDefault"));
			w3 = max(w3, (int)sizeof("/"));
			if (args[i].existed()) {
				oss << fixed << setprecision(6) << args[i].extargs_double_value;
				w5 = max(w5, (int)oss.str().length());
			}
			oss.str("");
			oss << "[" << fixed << setprecision(6) << args[i].extargs_double_min << ".." << fixed << setprecision(6) << args[i].extargs_double_max << "]";
			w6 = max(w6, (int)oss.str().length());
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::double_with_error){
			oss.str("");
			w2 = max(w2, (int)sizeof("DoubleWithError"));
			w3 = max(w3, (int)to_string(args[i].extargs_double_default).length());
			if (args[i].existed()) {
				oss << fixed << setprecision(6) << args[i].extargs_double_value;
				w5 = max(w5, (int)oss.str().length());
			}
			oss.str("");
			oss << "[" << fixed << setprecision(6) << args[i].extargs_double_min << ".." << fixed << setprecision(6) << args[i].extargs_double_max << "]";
			w6 = max(w6, (int)oss.str().length());
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::double_with_set_default){
			oss.str("");
			w2 = max(w2, (int)sizeof("DoubleWithSETDefault"));
			w3 = max(w3, (int)to_string(args[i].extargs_double_default).length());
			if (args[i].existed()) {
				oss << fixed << setprecision(6) << args[i].extargs_double_value;
				w5 = max(w5, (int)oss.str().length());
			}
			oss.str("");
			for(int j=0; abs(args[i].extargs_double_set[j] - INVALID_DOUBLE_VALUE_OF_SET)>= DOUBLE_DELTA; j++){
				if(j!=0)
					oss << "/";
				oss<< fixed << setprecision(6)<<args[i].extargs_double_set[j];
			}
			w6 = max(w6, (int)oss.str().length());
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::double_with_set_error){
			oss.str("");
			w2 = max(w2, (int)sizeof("DoubleWithSETError"));
			w3 = max(w3, (int)sizeof("/"));
			if (args[i].existed()) {
				oss << fixed << setprecision(6) << args[i].extargs_double_value;
				w5 = max(w5, (int)oss.str().length());
			}
			oss.str("");
			for (int j = 0; abs(args[i].extargs_double_set[j] - INVALID_DOUBLE_VALUE_OF_SET) >= DOUBLE_DELTA; j++) {
				if (j != 0)
					oss << "/";
				oss << fixed << setprecision(6) << args[i].extargs_double_set[j];
			}
			w6 = max(w6, (int)oss.str().length());
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::str){
			w2 = max(w2, (int)sizeof("String"));
			w3 = max(w3, (int)args[i].extargs_string_default.length());
			if (args[i].existed())w5 = max(w5, (int)args[i].extargs_string_value.length());
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::str_with_set_default){
			w2 = max(w2, (int)sizeof("StringWithSETDefault"));
			w3 = max(w3, (int)args[i].extargs_string_default.length());
			if (args[i].existed())w5 = max(w5, (int)(args[i].extargs_string_value.length()));
			string s = "";
			for(int j=0; args[i].extargs_string_set[j] != ""; j++) {
				if(j!=0)
					s += "/";
				s += args[i].extargs_string_set[j];
			}
			w6 = max(w6, (int)s.length());
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::str_with_set_error){
			w2 = max(w2, (int)sizeof("StringWithSETError"));
			w3 = max(w3, (int)args[i].extargs_string_default.length());
			if (args[i].existed())w5 = max(w5, (int)args[i].extargs_string_value.length());
			string s = "";
			for (int j = 0; args[i].extargs_string_set[j] != ""; j++) {
				if(j!=0)
					s += "/";
				s += args[i].extargs_string_set[j];
			}
			w6 = max(w6, (int)s.length());

		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::ipaddr_with_default){
			w2 = max(w2, (int)sizeof("IPAddrWithDefault"));
			w3 = max(w3, (int)ip_u_to_str(args[i].extargs_ipaddr_default).length());
			if (args[i].existed())w5 = max(w5, (int)args[i].get_str_ipaddr().length());
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::ipaddr_with_error){
			w2 = max(w2, (int)sizeof("IPAddrWithError"));
			w3 = max(w3, (int)ip_u_to_str(args[i].extargs_ipaddr_default).length());
			if(args[i].existed())w5 = max(w5, (int)args[i].get_str_ipaddr().length());
		}
		i++;
	}
	//打印表头
	w1+=2; w3++; w4++; w5++; w6++;
	cout << setw(w1 + w2 + w3 + w4 + w5 + w6) << setfill('=') << "=" << setfill(' ') << endl;
	cout << left << setw(w1) << " name" 
		<< left << setw(w2) << "type" 
		<< left << setw(w3) << "default" 
		<< left << setw(w4) << "exists" 
		<< left << setw(w5) << "value" 
		<< left  << "range/set" << endl;
	cout << setw(w1 + w2 + w3 + w4 + w5 + w6) << setfill('=') << '=' << setfill(' ') << endl;
	//打印各参数信息
	i = 0;
	while (args[i].get_name() != "") {
		cout << left << setw(w1) << " "+args[i].get_name()  ;
		if(args[i].extargs_type== ST_EXTARGS_TYPE::boolean){
			cout << left << setw(w2) << "Bool"  
				<< left << setw(w3) << (args[i].extargs_bool_default ? "true" : "false")  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? "true": "/")  
				<< left  << "/" << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::int_with_default){
			cout << left << setw(w2) << "IntWithDefault"  
				<< left << setw(w3) << to_string(args[i].extargs_int_default)  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? to_string(args[i].extargs_int_value):"/")  
				<< left  << "[" + to_string(args[i].extargs_int_min) + ".." + to_string(args[i].extargs_int_max) + "]" << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::int_with_error){
			cout << left << setw(w2) << "IntWithError"  
				<< left << setw(w3) << "/"  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? to_string(args[i].extargs_int_value) : "/")  
				<< left  << "[" + to_string(args[i].extargs_int_min) + ".." + to_string(args[i].extargs_int_max) + "]" << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::int_with_set_default){
			string s = "";
			for(int j=0; args[i].extargs_int_set[j] != INVALID_INT_VALUE_OF_SET; j++){
				if(j!=0)
					s += "/";
				s += to_string(args[i].extargs_int_set[j]);
			}
			cout << left << setw(w2) << "IntSETWithDefault"  
				<< left << setw(w3) << to_string(args[i].extargs_int_default)  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? to_string(args[i].extargs_int_value) : "/")  
				<< left  << s << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::int_with_set_error){
			string s = "";
			for (int j = 0; args[i].extargs_int_set[j] != INVALID_INT_VALUE_OF_SET; j++) {
				if(j!=0)
					s += "/";
				s += to_string(args[i].extargs_int_set[j]);
			}
			cout << left << setw(w2) << "IntSETWithError"  
				<< left << setw(w3) << "/"  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? to_string(args[i].extargs_int_value) : "/")  
				<< left  << s << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::double_with_default){
			cout << left << setw(w2) << "DoubleWithDefault"  
				<< left << setw(w3) << to_string(args[i].extargs_double_default)  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? to_string(args[i].extargs_double_value) : "/")  
				<< left  << "[" + to_string(args[i].extargs_double_min) + ".." + to_string(args[i].extargs_double_max) + "]" << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::double_with_error){
			cout << left << setw(w2) << "DoubleWithError"  
				<< left << setw(w3) << "/"  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? to_string(args[i].extargs_double_value) : "/")  
				<< left  << "[" + to_string(args[i].extargs_double_min) + ".." + to_string(args[i].extargs_double_max) + "]" << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::double_with_set_default){
			string s = "";
			for(int j=0; abs(args[i].extargs_double_set[j] - INVALID_DOUBLE_VALUE_OF_SET) >= DOUBLE_DELTA; j++){
				if(j!=0)
					s += "/";
				s += to_string(args[i].extargs_double_set[j]);
			}
			cout << left << setw(w2) << "DoubleSETWithDefault"  
				<< left << setw(w3) << to_string(args[i].extargs_double_default)  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? to_string(args[i].extargs_double_value) : "/")  
				<< left  << s << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::double_with_set_error){
			string s = "";
			for (int j = 0; abs(args[i].extargs_double_set[j] - INVALID_DOUBLE_VALUE_OF_SET) >= DOUBLE_DELTA; j++) {
				if(j!=0)
					s += "/";
				s += to_string(args[i].extargs_double_set[j]);
			}
			cout << left << setw(w2) << "DoubleSETWithError"  
				<< left << setw(w3) << "/"  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? to_string(args[i].extargs_double_value) : "/")  
				<< left  << s << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::str){
			cout << left << setw(w2) << "String"  
				<< left << setw(w3) << (args[i].extargs_string_default=="" ? "/" : args[i].extargs_string_default)  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? args[i].extargs_string_value : "/")  
				<< left  << "/" << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::str_with_set_default){
			string s = "";
			for(int j=0; args[i].extargs_string_set[j] != ""; j++){
				if(j!=0)
					s += "/";
				s += args[i].extargs_string_set[j];
			}
			cout << left << setw(w2) << "StringSETWithDefault"  
				<< left << setw(w3) << args[i].extargs_string_default  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? args[i].extargs_string_value : "/")  
				<< left  << s << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::str_with_set_error){
			string s = "";
			for (int j = 0; args[i].extargs_string_set[j] != ""; j++) {
				if(j!=0)
					s += "/";
				s += args[i].extargs_string_set[j];
			}
			cout << left << setw(w2) << "StringSETWithError"  
				<< left << setw(w3) << "/"  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? args[i].extargs_string_value : "/")  
				<< left  << s << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::ipaddr_with_default){
			cout << left << setw(w2) << "IPAddrWithDefault"  
				<< left << setw(w3) <<ip_u_to_str(args[i].extargs_ipaddr_default)
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? args[i].get_str_ipaddr() : "/")  
				<< left  << "/" << endl;
		}
		if(args[i].extargs_type== ST_EXTARGS_TYPE::ipaddr_with_error){
			cout << left << setw(w2) << "IPAddrWithError"  
				<< left << setw(w3) << "/"  
				<< left << setw(w4) << (args[i].existed() ? "1" : "0")  
				<< left << setw(w5) << (args[i].existed() ? args[i].get_str_ipaddr() : "/")  
				<< left  << "/" << endl;
		}
		i++;
	}
	cout << setw(w1 + w2 + w3 + w4 + w5 + w6) << setfill('=') << '=' << setfill(' ') << endl << endl;
	return 0; //此句根据需要修改
}

#endif // !ENABLE_LIB_COMMON_TOOLS
