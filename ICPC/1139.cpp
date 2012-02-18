#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//1 <= N <= 100
//1 <= T <= 1000
//1 <= R <= 10
int N,T,R;

#define FOR(i,n) for(int i = 0; i < n; i++)
typedef complex<int> P;

void cin2P(P &p){
	int x,y;
	cin >>x >> y;
	p.real(x);p.imag(y);
} 

typedef struct{
	int t; //時間
	P vp;  //速度
}KEIRO;
typedef struct{
	string name;
	P start; //スタート地点
	int keiro_num;
	KEIRO keiro[1000];
}ROBOT;

ROBOT robot[100];

vector<string> ans;

void solve()
{
	//入力受け取り
	for(int i=0;i<N;i++){
		int dummy;
		cin >> robot[i].name >> dummy;
		cin2P(robot[i].start);
		robot[i].keiro_num = 0;
		do{
			cin >> robot[i].keiro[robot[i].keiro_num].t;
			cin2P(robot[i].keiro[robot[i].keiro_num].vp);
		}while(robot[i].keiro[robot[i].keiro_num++].t != T);

		ans.clear();

		sort(ans.begin(),ans.end());
		for(vector<string>::iterator it = ans.begin(); it != ans.end(); ++it)
		{
			cout << *it;
		}
	}
}

int main()
{
	while(cin>>N>>T>>R,(N||T||R)){
		solve();
	}

	return 0;
}