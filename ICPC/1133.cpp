#include <iostream>
#include <math.h>

using namespace std;

int N,M,L;

int B[10],H[10],P[10],T[10];

int flow[11]; //B�̕��ɏ]������ B,F,A�Ɉˑ��A����ȍ~FA�͎g���Ȃ�
double ht[11]; //t�b��́A��؂�ꂽ�����̍���h

void Fill(int l,int r,int in,double &water)
{
	if(water == 0) return ; //�����Ȃ�
	if(l != r){
		int ci = l,ch = 0; //�����̃C���f�b�N�X�ƍ���
		for(int i = l; i < r; i++){
			if(ch < H[i]){
				ci = i; ch = H[i];
			}
		}
		if(ci >= in){
			Fill(l,ci,in,water);
			Fill(ci+1,r,in,water);
		} else {
			Fill(ci+1,r,in,water);
			Fill(l,ci,in,water);
		}
	}

	int s = ((r == N) ? 100 : B[r]) - ((l == 0) ? 0 : B[l - 1]); //��ʐ�
	double h = ht[l]; //����
	//if(h >= 50.0) return ; //����ȍ~�ǉ��͕s�\
	double max_h = min<double>((r == N) ? 50 * 30 : H[r],(l == 0) ? 50 * 30 : H[l - 1]);

	////�ǉ�����鍂��
	double add_h = (water > s * (max_h - h)) ? (max_h - h) : (water / (double)s);
	water -= add_h * s; //�������炵
	for(int i = l; i <= r; i++) ht[i] += add_h; //���ʂ��グ��

}

void solve()
{
	cin >> N;
	flow[0] = 0;
	for(int i = 0; i < N; i++){
		cin >> B[i] >> H[i];
		H[i] *= 30;
		flow[i+1] = 0;
	}

	int F[10],A[10];
	cin >> M;
	for(int i = 0; i < M; i++){
		cin >> F[i] >> A[i];
		for(int j = 0; j <= N; j++){
			if(j == N || F[i] < B[j]){
				flow[j] += A[i];
				break;
			}
		}
	}

	cin >> L;
	for(int i = 0; i < L; i++)
		cin >> P[i] >> T[i];
	
	for(int i = 0; i < L; i++){
		for(int j = 0; j <= N; j++){
			ht[j] = 0.0; // �����N���A
		}

		//�����̏ォ�琅����
		for(int j = 0; j <= N; j++){
			if(flow[j] == 0) continue; //�����Ȃ�
			double water = flow[j]*T[i];
			Fill(0,N,j,water);
		}

		int p = 0;
		while(p < N && P[i] > B[p]) p++;
		//�Ō��30�Ŋ����č��������Ƃɖ߂�
		cout << ht[p] / 30.0 << endl;
	}

}

int main()
{
	int D;
	cin >> D;
	for(int i = 0; i < D; i++)
	{
		solve();
	}

	return 0;
}