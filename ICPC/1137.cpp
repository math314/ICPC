#include <iostream>
#include <complex>

using namespace std;

typedef complex<int> P;

int n;

int m;
P base[9];
int sm[50];
P s[50][9];

P rotate_p = P(0,1);

bool cmp(int i)
{
	if(m != sm[i]) return false; //‚»‚à‚»‚àÜ‚ê‚é‰ñ”‚ªˆÙ‚È‚é

	for(int j = 0; j < 4; j++){
		int k;
		for(k = 0; k < m-1; k++){
			if(base[k] != s[i][k]) break;
		}
		if(k == m-1) return true;
		for(k = 0; k < m-1; k++){
			if(base[k] != s[i][m-2-k]) break;
		}
		if(k == m-1) return true;
		for(int k=0; k<m-1;k++) s[i][k] *= rotate_p; //90“x‰ñ“]
	}

	return false;
}

void solve()
{
	int x,y;
	cin >> m;
	P buf[10];
	for(int i=0;i<m;i++){
		cin >> buf[i].real() >> buf[i].imag();
	}
	for(int i=0;i<m-1;i++){
		base[i] = buf[i+1]-buf[i];
	}

	for(int j =0;j<n;j++){
		cin >> sm[j];
		for(int i=0;i<sm[j];i++){
			cin >> buf[i].real() >> buf[i].imag();
		}
		for(int i=0;i<sm[j]-1;i++){
			s[j][i] = buf[i+1]-buf[i];
		}
	}

	for(int i = 0; i < n; i++){
		if(cmp(i)) cout << i + 1 << endl;
	}

	cout << "+++++" << endl;
}

int main()
{
	while(cin >> n,n)
		solve();

	return 0;
}