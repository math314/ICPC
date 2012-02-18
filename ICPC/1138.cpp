#include <iostream>
#include <limits.h>
#include <queue>

using namespace std;

int n,m,p,a,b;

#define FOR(i,n) for(int i = 0; i < n; i++)

typedef struct{
	int x,y,z;
} LOAD;

typedef struct{
	double cost[256];
	bool used;
}CITY;

int ticket[8];
LOAD load[465];
CITY city[30+1]; //city[0]��dummy

double get_min(double a,double b){return (a>b)?b:a;}

void search()
{
	queue<int> city_nums;
	

	for(city_nums.push(a); !city_nums.empty(); city_nums.pop()){
		int pipot = city_nums.front();
		if(pipot == b)
			continue; //�����̌o�H�͏I���

		city[pipot].used = true; //�����͂����K�ꂽ���ƂɂȂ�
		for(int j = 0; j < p; j++){
			if((load[j].x != pipot && load[j].y != pipot)) continue; //�����g�������A�ʂ�Ȃ�
			int next = (load[j].x != pipot) ? load[j].x : load[j].y; //����city
			if(city[next].used) continue; //���̒��͂��łɖK�ꂽ
			city_nums.push(next); //���ɖK��钬
			//�R�X�g�v�Z
			for(int i = 0; i < (1 << n); i++){
				if(city[pipot].cost[i] == INT_MAX) continue; //���̃`�P�b�g�\���͂Ȃ�
				FOR(k,n){
					if(i & (1 << k)) continue; //k�Ԗڂ͎g���Ă��܂�
					int new_tickets = i | (1 << k); //�V�����t���O
					city[next].cost[new_tickets] = 
						get_min(city[next].cost[new_tickets],city[pipot].cost[i] + load[j].z / (double)ticket[k]); //�R�X�g�v�Z
				}
			}
		}
	}
}

void solve()
{
	FOR(i,n)
		cin >> ticket[i];
	FOR(i,p)
		cin >> load[i].x >>load[i].y>>load[i].z;

	int flagNum = (1 << n);

	for(int i = 1; i <= m; i++){
		city[i].used = false;
		FOR(j,flagNum)
			city[i].cost[j] = INT_MAX;
	}

	//�g�p�`�P�b�g�Ȃ����Acost0�ɐݒ�
	city[a].cost[0] = 0;
	search();

	double ans = (double)INT_MAX;
	FOR(i,flagNum)
		ans = get_min(ans,city[b].cost[i]);
	if(ans == (double)INT_MAX) cout << "Impossible" << endl;
	else cout << ans << endl;

}

int main()
{
	while(cin>>n>>m>>p>>a>>b,(n||m||p||a||b)){
		solve();
	}

	return 0;
}