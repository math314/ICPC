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

typedef struct 
{
	int n,count;
} HANAFUDA;

HANAFUDA GetSituation()
{
	HANAFUDA h;
	vector<int> v = GetIntVector();
	h.n = v[0];
	h.count = v[1];

	return h;
}

bool true_func(int dummy){return true;}

void solve(HANAFUDA h)
{
	vector<int> data(h.n);
	for(int i = 0; i < h.n; i++){
		data[i] = h.n - i;
	}

	for(int i = 0; i < h.count; i++){
		vector<int> inputs = GetIntVector();
		rotate( data.begin(), data.begin() +(inputs[0] - 1), data.begin() + (inputs[0] + inputs[1] - 1) );
	}

	cout << data[0] << endl;
}

void Hanafuda()
{
	HANAFUDA h = GetSituation();
	while(h.n != 0 && h.count != 0){
		solve(h);
		h = GetSituation();
	}
}


int main()
{
	Hanafuda();

	return 0;
}