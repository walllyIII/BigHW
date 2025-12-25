/* 2452839 徐川 计科 */
#include"../include/txt_compare.h"
#include"../include/proceed_line.h"
#include"../include/cmd_console_tools.h"

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<vector>
using namespace std;

static string CF_CRLF_equal(const string& str)
{
	string result = str, str_end;
	if (str.size() >= 2) {
		if (str[str.size() - 1] == '\n' && str[str.size() - 2] == '\r')
			return str.substr(0, str.size() - 2) + '\n';
		else
			return str.substr(0, str.size());
	}
	else {
		return str;
	}
}

static string string_remove_special_char(const string& str)
{
	string result = str;
	for (int i = 0; i < (int)str.size(); i++) {
		if ((int)result[i] == 13 || (int)result[i] == 11 || (int)result[i] == 10 || (int)result[i] == 8 || (int)result[i] == 7)
			result[i] = 'X';
	}
	return result;
}

txt_compare::txt_compare(string filename1, string filename2, string trim_type, string display_type, int line_skip, int line_offset, int line_max_diffnum, int line_max_linenum, bool ignore_blank, bool CR_CRLF_not_equal, bool debug)
{
	this->filename1 = filename1;
	this->filename2 = filename2;
	this->trim_type = trim_type;
	this->display_type = display_type;
	this->line_skip = line_skip;
	this->line_offset = line_offset;
	this->line_max_diffnum = line_max_diffnum;
	this->line_max_linenum = line_max_linenum;
	this->ignore_blank = ignore_blank;
	this->CR_CRLF_not_equal = CR_CRLF_not_equal;
	this->debug = debug;
	ifstream file1, file2;
	int skip1, skip2;
	file1.open(filename1, ios::in | ios::binary);
	if (file1.fail()) {
		cerr << "无法打开文件：" << filename1 << endl;
		return;
	}
	file2.open(filename2, ios::in | ios::binary);
	if (file2.fail()) {
		cerr << "无法打开文件：" << filename2 << endl;
		return;
	}
	string tmp;
	if (line_offset >= 0) {
		skip1 = line_skip;
		skip2 = line_skip + line_offset;
	}
	else {
		skip1 = line_skip - line_offset;
		skip2 = line_skip;
	}
	while (getline(file1, tmp, '\n')) {
		tmp += '\n';
		tmp = remove_space_in_line(tmp, this->trim_type);
		if (this->CR_CRLF_not_equal == false) {
			tmp = CF_CRLF_equal(tmp);
		}
		if (ignore_blank && remove_endline(tmp).empty()) {
			continue;
		}
		skip1--;
		if (skip1 < 0) {
			vline1.push_back(tmp);
			line_maxlen = max(line_maxlen, (int)tmp.size());
		}
	}
	while (getline(file2, tmp, '\n')) {
		tmp += '\n';
		tmp = remove_space_in_line(tmp, this->trim_type);

		if (this->CR_CRLF_not_equal == false) {
			tmp = CF_CRLF_equal(tmp);
		}
		if (ignore_blank && remove_endline(tmp).empty()) {
			continue;
		}
		skip2--;
		if (skip2 < 0) {
			vline2.push_back(tmp);
			line_maxlen = max(line_maxlen, (int)tmp.size());
		}
	}
	file1.close();
	file2.close();
}

txt_compare::txt_compare(istringstream iss1, istringstream iss2, string trim_type, string display_type, int line_skip, int line_offset, int line_max_diffnum, int line_max_linenum, bool ignore_blank, bool CR_CRLF_not_equal, bool debug)
{
	this->filename1 = "iss1";
	this->filename2 = "iss2";
	this->trim_type = trim_type;
	this->display_type = display_type;
	this->line_skip = line_skip;
	this->line_offset = line_offset;
	this->line_max_diffnum = line_max_diffnum;
	this->line_max_linenum = line_max_linenum;
	this->ignore_blank = ignore_blank;
	this->CR_CRLF_not_equal = CR_CRLF_not_equal;
	this->debug = debug;
	int skip1, skip2;
	string tmp;
	if (line_offset >= 0) {
		skip1 = line_skip;
		skip2 = line_skip + line_offset;
	}
	else {
		skip1 = line_skip - line_offset;
		skip2 = line_skip;
	}
	while (getline(iss1, tmp, '\n')) {
		tmp += '\n';
		tmp = remove_space_in_line(tmp, this->trim_type);
		if (this->CR_CRLF_not_equal == false) {
			tmp = CF_CRLF_equal(tmp);
		}
		if (ignore_blank && remove_endline(tmp).empty()) {
			continue;
		}
		skip1--;
		if (skip1 < 0) {
			vline1.push_back(tmp);
			line_maxlen = max(line_maxlen, (int)tmp.size());
		}
	}
	while (getline(iss2, tmp, '\n')) {
		tmp += '\n';
		tmp = remove_space_in_line(tmp, this->trim_type);

		if (this->CR_CRLF_not_equal == false) {
			tmp = CF_CRLF_equal(tmp);
		}
		if (ignore_blank && remove_endline(tmp).empty()) {
			continue;
		}
		skip2--;
		if (skip2 < 0) {
			vline2.push_back(tmp);
			line_maxlen = max(line_maxlen, (int)tmp.size());
		}
	}
}

txt_compare::~txt_compare()
{
	output_info.clear();
}

static void output_(const string str1, const string str2, const int line1, const int line2, vector<Spair>& out, bool line1_state, bool line2_state, bool type)
{
	string tmp;
	string end_line1 = "<CR>\n", end_line2 = "<EMPTY><CR>\n", end_line3 = "<EOF>\n";
	int cnt = 0, maxlen = 0;

	while (str1[cnt] == str2[cnt] && cnt < (int)str1.size() && cnt < (int)str2.size())cnt++;
	if (cnt == str1.size())
		tmp = "第[" + to_string(line1) + " / " + to_string(line2) + "]行 - " + "文件2的尾部有多余字符：\n";
	else if (cnt == str2.size())
		tmp = "第[" + to_string(line1) + " / " + to_string(line2) + "]行 - " + "文件1的尾部有多余字符：\n";
	else
		tmp = "第[" + to_string(line1) + " / " + to_string(line2) + "]行 - 第[" + to_string(cnt) + "]个字符开始有差异：\n";
	out.push_back(Spair{ 0,tmp });
	if(type){
		tmp = line1_state ? end_line3 : (str1.empty() ? "<EMPTY><CR>" : str1);
		maxlen = maxlen < (int)tmp.size() ? tmp.size() : maxlen;
		tmp = line2_state ? end_line3 : (str2.empty() ? "<EMPTY><CR>" : str2);
		maxlen = maxlen < (int)tmp.size() ? tmp.size() : maxlen;
		maxlen = ((maxlen / 10) + 1) * 10;
		tmp = "        ";
		for (int i = 0; i < maxlen; i++)tmp += "-";
		tmp += '\n';
		tmp += "        ";
		for (int i = 0; i < maxlen; i++) {
			if(i%10==0)tmp += to_string(i/10);
			else tmp += " ";
		}
		tmp += '\n';
		tmp += "        ";
		for (int i = 0; i < maxlen; i++) {
			tmp += to_string(i%10);
		}
		tmp += '\n';
		tmp += "        ";
		for (int i = 0; i < maxlen; i++)tmp += "-";
		out.push_back(Spair{ 0,tmp + "\n" });
		tmp = "";
	}
	tmp = "文件1 : ";
	bool che = 1;
	for (int i = 0; i < (int)str1.size(); i++) {
		if (str1[i] == '\n')continue;
		if (i>=(int)str2.size() || str1[i] != str2[i]) {
			if (che) {
				che = 0;
				out.push_back(Spair{ 0,tmp });
				tmp = "";
			}
			tmp += str1[i];
		}
		else {
			if (!che) {
				che = 1;
				out.push_back(Spair{ 1,tmp });
				tmp = "";
			}
			tmp += str1[i];
		}
	}
	if (line1_state) {
		out.push_back(Spair{ 0,end_line3 });
	}
	else if(str1.empty()){
			out.push_back(Spair{ 0,end_line2 });
	}else {
		if (che) {
			tmp += end_line1;
			out.push_back(Spair{ 0,tmp });
		}
		else {
			out.push_back(Spair{ 1,tmp });
			out.push_back(Spair{ 0,end_line1 });
		}
	}
	tmp = "文件2 : ";
	che = 1;
	for (int i = 0; i < (int)str2.size(); i++) {
		if (str2[i] == '\n')continue;
		if (i>=(int)str1.size() || str2[i] != str1[i]) {
			if (che) {
				che = 0;
				out.push_back(Spair{ 0,tmp });
				tmp = "";
			}
			tmp += str2[i];
		}
		else {
			if (!che) {
				che = 1;
				out.push_back(Spair{ 1,tmp });
				tmp = "";
			}
			tmp += str2[i];
		}
	}
	if (line2_state) {
		out.push_back(Spair{ 0,end_line3 });
	}
	else if (str2.empty()) {
		out.push_back(Spair{ 0,end_line2 });
	}
	else {
		if (che) {
			tmp += end_line1;
			out.push_back(Spair{ 0,tmp });
		}
		else {
			out.push_back(Spair{ 1,tmp });
			out.push_back(Spair{ 0,end_line1 });
		}
	}
	if (type) {
		tmp = "文件1(HEX) : \n";
		if (line1_state)
			tmp += end_line3;
		else
			tmp += string_to_hex(str1);
		tmp += "文件2(HEX) : \n";
		if (line2_state)
			tmp += end_line3;
		else
			tmp += string_to_hex(str2);
		out.push_back(Spair{ 0,tmp });
	}
}

int txt_compare::compare()
{
	int skip1, skip2, width = 80;
	if (line_offset >= 0) {
		skip1 = line_skip;
		skip2 = line_skip + line_offset;
	}
	else {
		skip1 = line_skip - line_offset;
		skip2 = line_skip;
	}
	string tmp;
	width = (line_maxlen / 10 + 1) * 10 + 8 + 2;
	if (this->display_type=="detailed" && width < 80)
		width = 80;
	string cut_line;
	for (int k = 0; k < width; k++)cut_line += "=";
	cut_line += "\n";
	vector<string>::iterator it1 = vline1.begin();
	vector<string>::iterator it2 = vline2.begin();
	int i = 0,diff_cnt=0;
	bool flag = 1;
	bool line1_state = 0, line2_state = 0;
	while (i<(int)vline1.size() || i<(int)vline2.size()) {
		i++;
		string l1, l2;
		if(line1_state)
			l1 = "";
		else
			l1 = *it1;
		if (line2_state)
			l2 = "";
		else
			l2 = *it2;
		if (l1 != l2) {
			if (this->display_type == "none") {
				output_info.push_back(Spair{ 0,"文件不同.\n" });
				diff_cnt++;
				flag = 0;
			}
			else if (this->display_type == "normal") {
				if (flag == 1) {
					output_info.push_back(Spair{ 0,"比较结果输出：\n" });
					output_info.push_back(Spair{ 0,cut_line });
				}
				output_(l1, l2, skip1 + i, skip2 + i, output_info,line1_state,line2_state,0);
				output_info.push_back(Spair{ 0,"\n" });
				diff_cnt++;
				flag = 0;
			}
			else {
				if (flag == 1) {
					output_info.push_back(Spair{ 0,"比较结果输出：\n" });
					output_info.push_back(Spair{ 0,cut_line });
				}
				output_(l1, l2, skip1 + i, skip2 + i, output_info,line1_state,line2_state,1);
				output_info.push_back(Spair{ 0,"\n" });
				diff_cnt++;
				flag = 0;
			}
		}
		if (diff_cnt >= this->line_max_diffnum && this->line_max_diffnum>0) {
			output_info.push_back(Spair{ 0,"差异行数已达上限，停止比较.\n" });
			break;
		}
		if (i >= this->line_max_linenum && this->line_max_linenum > 0) {
			output_info.push_back(Spair{ 0,"比较行数已达上限，停止比较.\n" });
			break;
		}
		if (it1+1 != vline1.end())
			it1++;
		else 
			line1_state = 1;
			
		if (it2+1 != vline2.end())
			it2++;
		else 
			line2_state = 1;
			
	}
	if (flag) {
		if (this->display_type == "none") {
			output_info.push_back(Spair{ 0,"文件相同.\n" });
		}
		else {
			output_info.push_back(Spair{ 0,"比较结果输出：\n" });
			output_info.push_back(Spair{ 0,cut_line });
			output_info.push_back(Spair{ 0,"在指定检查条件下完全一致.\n"+ cut_line});
		}
	}
	else {
		if (this->display_type == "normal") {
			output_info.push_back(Spair{ 0,cut_line+ "在指定检查条件下共"+to_string(diff_cnt) + "行有差异.\n\
阅读提示：\n\
        1、空行用<EMPTY>标出\n\
        2、文件结束用<EOF>标出\n\
        3、两行相同列位置的差异字符用亮色标出\n\
        4、每行中的CR/LF/VT/BS/BEL用X标出(方便看清隐含字符)\n\
        5、每行尾的多余的字符用亮色标出，CR/LF/VT/BS/BEL用亮色X标出(方便看清隐含字符)\n\
        6、每行最后用<CR>标出(方便看清隐含字符)\n\
        7、中文因为编码问题，差异位置可能报在后半个汉字上，但整个汉字都亮色标出\n\
        8、用--display detailed可以得到更详细的信息\n" + cut_line });
		}
		else if(this->display_type == "detailed"){
			output_info.push_back(Spair{ 0,cut_line+ "在指定检查条件下共"+to_string(diff_cnt) + "行有差异.\n\
阅读提示：\n\
        1、空行用<EMPTY>标出\n\
        2、文件结束用<EOF>标出\n\
        3、两行相同列位置的差异字符用亮色标出\n\
        4、每行中的CR/LF/VT/BS/BEL用X标出(方便看清隐含字符)\n\
        5、每行尾的多余的字符用亮色标出，CR/LF/VT/BS/BEL用亮色X标出(方便看清隐含字符)\n\
        6、每行最后用<CR>标出(方便看清隐含字符)\n\
        7、中文因为编码问题，差异位置可能报在后半个汉字上，但整个汉字都亮色标出\n"+ cut_line });
		}
	}
	return diff_cnt;
}

void txt_compare::result()
{
	Spair tmp1, tmp2;
	vector<Spair>::iterator it1 = output_info.begin(),it2=output_info.begin()+1;
	for (; it2 != output_info.end(); it1++,it2++) {
		tmp1 = *it1; tmp2 = *it2;
		int len1 = tmp1.content.size();
		int len2 = tmp2.content.size();
		if (tmp1.is_highlight == tmp2.is_highlight)continue;
		else {

			if (!((unsigned int)tmp1.content[len1 - 1] <= 127 && (unsigned int)tmp1.content[len1 - 1] >= 0)) {
				if (tmp1.is_highlight) {
					tmp1.content += tmp2.content[0];
					tmp2.content.erase(0, 1);
					*it1 = tmp1;
					*it2 = tmp2;
				}
				else {
					tmp2.content = tmp1.content[len1 - 1] + tmp2.content;
					tmp1.content.erase(len1 - 1, 1);
					*it1 = tmp1;
					*it2 = tmp2;
				}
			}
		}
	}
	it1 = output_info.begin();
	for (; it1 != output_info.end(); it1++) {
		if(it1->is_highlight){
			int bc, fc;
			cct_getcolor(bc, fc);
			cct_setcolor(COLOR_HYELLOW, COLOR_HRED);
			string tmp = it1->content;
			tmp = string_remove_special_char(tmp);
			cout << tmp;
			cct_setcolor(bc, fc);
		} else {
			cout << it1->content;
		}
	}
}