#include <string>
#include <iterator>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

string GetStr()
{
	string str;
	getline(cin,str);
	return str;
}

vector<int> GetIntVector()
{
	string str;
	getline(cin,str);
	istringstream line( str );

	istream_iterator<int> iit(line);
	istream_iterator<int> iit_eof;

	vector<int> ret;

	for(;iit != iit_eof; iit++){
		ret.push_back(*iit);
	}

	return ret;
}

int counter;

void GoNext(vector<string>& lines,int hh,int hw)
{
	counter++;
	lines[hh][hw] = '#';

	if(hw > 0 && lines[hh][hw-1] != '#')
		GoNext(lines,hh,hw-1);

	if(hw < (int)lines[hh].size() - 1 && lines[hh][hw+1] != '#')
		GoNext(lines,hh,hw+1);

	if(hh > 0 && lines[hh-1][hw] != '#')
		GoNext(lines,hh-1,hw);

	if(hh < (int)lines.size() - 1 && lines[hh+1][hw] != '#')
		GoNext(lines,hh+1,hw);
}

void solve(int w,int h)
{
	vector<string> lines;
	for(int i = 0; i < h; i++){
		lines.push_back(GetStr());
	}

	int humanw,humanh = -1;
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			if(lines[i][j] == '@'){
				humanh = i; humanw = j;
				break;
			}
		}
		if(humanh != -1) break;
	}

	counter = 0;

	GoNext(lines,humanh,humanw);

	cout << counter <<endl;
}

void solve1130()
{
	vector<int> v = GetIntVector();
	while(v[0] != 0 && v[1] != 0){
		solve(v[0],v[1]);
		 v = GetIntVector();
	}
}


int main()
{
	solve1130();

	return 0;
}