#include <iostream>
#include <string.h>

using namespace std;


typedef struct{
	int l,r;
}CROSS;

typedef struct {
	bool walk;
	char name[16+1];
}LOAD;

int N,M,L;
LOAD loads[200]; //�����ۑ�

CROSS crosses[1000];


int AddLoad(char *load)
{
	int i;
	for(i = 0; i < L; i++){
		if(strcmp(load,loads[i].name) == 0) return i;
	}
	strcpy(loads[i].name,load); //�ǉ�����
	L++;
	return i;
}

CROSS AddCross(char *cross)
{
	int len = strlen(cross);
	for(int i = 0; i <= len; i++){
		if(cross[i] == '-'){
			CROSS cr;
			cross[i] = '\0';
			cr.l = AddLoad(cross);
			cr.r = AddLoad(cross+i+1);
			return cr;
		}
	}

	CROSS dummy;
	return dummy;
}

int GetLoad(char *load)
{
	for(int i = 0; i < L; i++){
		if(strcmp(load,loads[i].name) == 0) return i;
	}
	return -1;
}

CROSS GetCross(char *cross)
{
	int len = strlen(cross);
	for(int i = 0; i <= len; i++){
		if(cross[i] == '-'){
			CROSS cr;
			cross[i] = '\0';
			cr.l = GetLoad(cross);
			cr.r = GetLoad(cross+i+1);
			return cr;
		}
	}

	CROSS dummy;
	return dummy;
}

typedef enum {NONE,OK,NO = -1} FLAG;
FLAG flag;

void JudgeVaild(int l,int r,bool other)
{
	if(flag != NONE) return ; //�t���O����
	if(loads[l].walk) return ; //���ɕ�����
	if(l == r){ //���ǂ蒅����
		flag = other ? OK : NO;
		return;
	}
	loads[l].walk = true; //������
	for(int i= 0; i < N; i++){
		if(crosses[i].l == l) {
			JudgeVaild(crosses[i].r,r,!other);
			if(flag != NONE) return;
			for(int j = 0; j < N; j++){
				if(i == j || crosses[i].r != crosses[j].r || loads[crosses[j].l].walk) continue;
				JudgeVaild(crosses[j].l,r,other);
				if(flag != NONE) return;
			}
		}
		else if(crosses[i].r == l){
			for(int j = 0; j < N; j++){
				if(i == j || crosses[i].l != crosses[j].l || loads[crosses[j].r].walk) continue;
				JudgeVaild(crosses[j].r,r,other);
				if(flag != NONE) return;
			}
		}
	}
}

bool IsOk(CROSS crs)
{
	if(crs.l == -1 || crs.r == -1) return false;

	for(int j = 0; j < L; j++) loads[j].walk = false; //�����Ă��Ȃ�
	flag = NONE; //�܂��t���O�Ȃ�
	JudgeVaild(crs.l,crs.r,false); //�s���邩�ǂ�������( l --- r )
	return flag == OK;
}

void solve()
{
	L = 0;

	for(int i =0 ; i < N; i++){
		char str[34];
		cin >> str; //������ǂݍ���
		crosses[i] = AddCross(str);
	}

	cout << L << endl; //�����o��

	cin >> M;
	for(int i = 0; i < M; i++){
		char str[34];
		cin >> str; //������ǂݍ���
		CROSS judge = GetCross(str);

		cout << (IsOk(judge) ? "YES" : "NO") << endl;
	}
	
}

int main()
{
	while(cin >> N,N){
		solve();
	}
	return 0;
}