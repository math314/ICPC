#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <limits.h>

using namespace std;

//1 <= N <= 100
//1 <= T <= 1000
//1 <= R <= 10
int N,T,R;

#define FOR(i,n) for(int i = 0; i < n; i++)
typedef complex<double> P;

void cin2P(P &p){
	int x,y;
	cin >>x >> y;
	p.real(x);p.imag(y);
} 

typedef struct{
	int t; //����
	P vp;  //���x
}KEIRO;
typedef struct{
	string name;
	P start; //�X�^�[�g�n�_
	int  keiro_num; //�o�H��
	KEIRO keiro[1000];
	double tRev; //��M����

	P GetV(double time)
	{
		for(int i = 0; i < keiro_num; i++){
			if(keiro[i].t > time) return keiro[i].vp;
		}
		return keiro[keiro_num-1].vp;
	}
}ROBOT;

ROBOT robot[100];

double Inner(P& a,P &b)
{
	return a.real() * b.real() + a.imag() * b.imag();
}

double Sq(P &a){ return Inner(a,a);}

double min_d(double a,double b){ return a>b?b:a;}

//�J�n�ʒu�v�Z
P calcStart(ROBOT &rob,double start)
{
	P ret = rob.start;
	for(int i=0;i<rob.keiro_num;i++)
	{
		if(start <= ( (i == 0) ? 0 : rob.keiro[i].t)) break;
		//�ړ�����
		double time = min_d(start,rob.keiro[i].t) - ( (i == 0) ? 0 : rob.keiro[i].t);
		ret += rob.keiro[i].vp * time;
	}

	return ret;
}

double GetRevTime(ROBOT &o,ROBOT &r){
	double sTime = o.tRev;

	vector<double> times;
	times.push_back(sTime);
	for(int oti =0;oti<o.keiro_num;oti++) {
		if(o.keiro[oti].t < sTime) continue;
		times.push_back(o.keiro[oti].t);
	}
	for(int rti =0;rti<r.keiro_num;rti++){
		if(r.keiro[rti].t < sTime) continue;
		times.push_back(r.keiro[rti].t);
	}
	// �A������l���폜����
	sort(times.begin(),times.end());
	vector<double>::iterator last_it = unique( times.begin(), times.end() );
	for(vector<double>::iterator it = times.begin(); it != last_it; ++it){
		if(*it < sTime || *it == (double)T) continue; //�܂��J�n�ł��Ȃ� 
		P p = calcStart(r,*it) - calcStart(o,*it); //for�Ɉړ�
		P v = r.GetV(*it) - o.GetV(*it); //���x�̍����擾
		if(v.imag() == 0 && v.real() == 0){
			if(Sq(p) <= R * R) return *it; //����Ԃ�Ԃ�
		} else {
			double A = Sq(v),B = Inner(v,p),C = Sq(p);
			double D = B * B - A * (C - R * R); //���ʎ�
			if( D < 0) continue; //���Ȃ�
			double Drt = sqrt(D);
			//�d�Ȃ�J�n�ƏI�������̎擾
			double start = (-B-Drt)/A + *it;
			double end = (-B+Drt)/A + *it;
			if(*it < start){
				if(*(it+1) < start) continue;
				else return start;
			}
			else if(*it <= end) return *it;
			else continue;
		}
	}

	return INT_MAX; //���Ȃ�
}

class CMin_Robot_Rev_Time
{
public:
	bool operator()(int& r,int& l)
	{
		return robot[r].tRev > robot[l].tRev;
	}
};

void solve()
{
	vector<int> nokori;
	//���͎󂯎��
	for(int i=0;i<N;i++){
		int dummy;
		cin >> robot[i].name >> dummy;
		cin2P(robot[i].start);
		robot[i].keiro_num = 0;
		nokori.push_back(i);
		do{
			cin >> robot[i].keiro[robot[i].keiro_num].t;
			cin2P(robot[i].keiro[robot[i].keiro_num].vp);
			robot[i].tRev = INT_MAX;
		}while(robot[i].keiro[robot[i].keiro_num++].t != T);
	}

	vector<int> revRobots;
	robot[0].tRev = 0;
	revRobots.push_back(0); //0�Ԗڂ��M���������Ă���
	vector<string> ans;

	while(!revRobots.empty()){
		//�ŏ����Ԃ������{�b�g��ID�擾
		int robID = *min_element(revRobots.begin(),revRobots.end(),CMin_Robot_Rev_Time());
		ans.push_back(robot[robID].name);
		revRobots.erase(find(revRobots.begin(),revRobots.end(),robID)); //�c�肩��ID�폜
		nokori.erase(find(nokori.begin(),nokori.end(),robID)); //�c�肩��ID�폜
		for(vector<int>::iterator it = nokori.begin(); it != nokori.end(); ++it){
			double revTime = GetRevTime(robot[robID],robot[*it]);
			if(revTime == INT_MAX) continue;
			double lastRevTime = robot[*it].tRev; 
			robot[*it].tRev = min_d(lastRevTime,revTime);
			if(lastRevTime == INT_MAX && revTime != INT_MAX) revRobots.push_back(*it);
		}
	}

	sort(ans.begin(),ans.end());
	for(vector<string>::iterator it = ans.begin(); it != ans.end(); ++it)
		cout << *it << endl;
}

int main()
{
	while(cin>>N>>T>>R,(N||T||R)){
		solve();
	}

	return 0;
}