#include"../include/proceed_line.h"
using namespace std;

string remove_space_in_line(const string& line, const string& trim_type)
{
	string result = line,str_end;
	if (trim_type == "none") {
		// 不做任何处理
		return result;
	}
	else if (trim_type == "left") {
		// 去除左侧空格和制表符
		int start=0;
		while ((result[start] == '\t' || result[start] == ' ' || result[start] == '\n' || result[start] == '\r') && (start < (int)result.size()))start++;
		if (start != result.size()) {
			result = result.substr(start);
		} else {
			result.clear(); // 全是空格或制表符
		}
	}
	else if (trim_type == "right") {
		// 去除右侧空格和制表符
		int end = result.size() - 1;
		while ((end >= 0) && (result[end] == '\t' || result[end] == ' ' || result[end] == '\n' || result[end] == '\r'))end--;
		if (end >= 0) {
			result = result.substr(0, end + 1);
		} else {
			result.clear(); // 全是空格或制表符
		}
	}
	else if (trim_type == "all") {
		// 去除两侧空格和制表符
		int start = 0;
		int end = result.size() - 1;
		while ((result[start] == '\t' || result[start] == ' ' || result[start] == '\n' || result[start] == '\r') && (start < (int)result.size()))start++;
		while ((end >= 0) && (result[end] == '\t' || result[end] == ' ' || result[end] == '\n' || result[end] == '\r'))end--;
		if (start != result.size() && end>=0 && start<=end) {
			result = result.substr(start, end - start + 1);
		} else {
			result.clear(); // 全是空格或制表符
		}
	}
	return result;
}

string remove_comment_in_line(const string& line, const string& comment_delimiter)
{
	string result = line;
	size_t pos = result.find(comment_delimiter);
	if (pos != string::npos) {
		result = result.substr(0, pos);
	}
	return result;
}

string remove_endline(const string& str)
{
	int i = (int)str.size() - 1;
	while (i >= 0 && (str[i] == '\r' || str[i] == '\n')) {
		i--;
	}
	return str.substr(0, i + 1);
}

bool cmp_str(const string& s1, const string& s2, const bool is_case_sensitive)
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

string string_to_hex(const string& str)
{
	ostringstream oss;
	string tmp = "";
	if (str == "") {
		return "<EMPTY>";
	}
	for (int i = 0; i < (int)str.size();i++) {
		if (str[i] == '\n')continue;
		if (i % 16 == 0) {
			oss << setw(8) << setfill('0') << hex <<right<< i << " : ";
		}
		if (i % 8 == 0 && i % 16 != 0)
			oss << "- ";
		oss << setw(2) <<hex<< (static_cast<unsigned int>(str[i])&0x000000ff) << ' ';
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')){
			tmp += str[i];
		} else {
			tmp += '.';
		}
		if (i % 16 == 15) {
			oss << " " << tmp << endl;
			tmp.clear();
		}
	}
	int k;
	k = (((int)(str.size())/16)+1)*16;
	if ((str.size())%16) {
		int p = 0;
		if (str[str.size() - 1] == '\n')
			p = 1;
		for (int j = str.size()-p; j < k; j++) {
			oss << "   ";
			if (j % 8 == 0 && j % 16 != 0)
				oss << "  ";
		}
		oss << " " << tmp << endl;
	}
	return oss.str();
}