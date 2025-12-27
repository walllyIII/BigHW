/* 2452839 Ðì´¨ ¼Æ¿Æ */
#pragma once
#include <string>
#include<sstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

string remove_space_in_line(const string& line, const string& trim_type);
string remove_comment_in_line(const string& line, const string& comment_delimiter);
bool cmp_str(const string& s1, const string& s2, const bool is_case_sensitive);
string string_to_hex(const string& str);
string remove_endline(const string& str);
string split_string_with_c(string& ori,char tar);
string ip_u_to_str(unsigned int ipaddr);