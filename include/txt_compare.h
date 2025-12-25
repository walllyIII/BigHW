/* 2452839 Ðì´¨ ¼Æ¿Æ */
#pragma once
#include<string>
#include<sstream>
#include<vector>
using namespace std;

struct Spair {
	bool is_highlight;
	string content;
};

class txt_compare
{
private:
	string filename1;
	string filename2;
	string trim_type;
	string display_type;
	int line_skip;
	int line_offset;
	int line_max_diffnum;
	int line_max_linenum;
	bool ignore_blank;
	bool CR_CRLF_not_equal;
	bool debug;
	vector<Spair> output_info;
	int line_maxlen;
	vector<string>vline1, vline2;
public:
	txt_compare(istringstream iss1,istringstream iss2, string trim_type, string display_type, int line_skip, int line_offset, int line_max_diffnum, int line_max_linenum, bool ignore_blank, bool CR_CRLF_not_equal, bool debug);
	txt_compare(string filename1, string filename2, string trim_type, string display_type, int line_skip, int line_offset, int line_max_diffnum, int line_max_linenum, bool ignore_blank, bool CR_CRLF_not_equal, bool debug);
	~txt_compare();
	int compare();
	void result();
};