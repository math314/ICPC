#include <iostream>

using namespace std;

int money,year;

int Fu(double p,int t){
	int ret = money;
	for(int i=0;i<year; i++)
		ret = (int)(ret * ( 1 + p)) - t;
	return ret;
}
int Ta(double p, int t)
{
	int z = money;
	int r =0;
	for(int i=0;i<year;i++)
	{
		r += (int)(z*p);
		z-= t;
	}

	return z+r;

}

int solve()
{
	int n;
	cin >> money >> year >> n;
	int rets[100];
	for(int i= 0; i <n; i++){
		int fukuri;
		double p;
		int t;
		cin >> fukuri >> p >> t;
		rets[i] = (fukuri)?Fu(p,t):Ta(p,t);
	}
	int ret = 0;
	for(int i=0;i<n;i++)
		if(ret <rets[i]) ret = rets[i];

	return ret;
}

int main()
{
	int m;
	cin >> m;
	for(int i=0;i<m;i++)
		cout << solve() << endl;

	return 0;
}