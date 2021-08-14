#include<map>
#include<set>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<vector>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<functional>
#define fi first
#define se second
#define il inline
#define ui unsigned
#define Mod 998244353
#define inf 0x3fffffff
#define ri register int
#define pi pair<int,int>
#define mp(a,b) make_pair(a, b)
using namespace std;
typedef long long ll;
int rd(){
	int res = 0, fl = 1;
    char c = getchar();
    while(!isdigit(c)){
        if(c == '-') fl = -1;
        c = getchar();
    }
    while(isdigit(c)){
        res = (res << 3) + (res << 1) + c - '0';
        c = getchar();
    }
    return res * fl;
}
const int maxn = 1000010;
ui n, op, x, Rot, cnt[maxn], val[maxn], ls[maxn], rs[maxn], sze[maxn], rnd[maxn], tot;
void maintain(ui rt){
	sze[rt]=cnt[rt]+sze[ls[rt]]+sze[rs[rt]]; return;
}
ui merge(ui L, ui R){
	ui Ne;
	if(rnd[L]>rnd[R]){
		Ne=L;
		rs[Ne]=R;
		ls[Ne]=merge(ls[Ne], rs[Ne]); 
		maintain(Ne);
		printf("Ne=%d val=%d\n", Ne, val[Ne]);
		return Ne;
	}
	Ne=R;
	ls[Ne]=L;
	rs[Ne]=merge(ls[Ne], rs[Ne]);
	maintain(Ne);
	printf("Ne=%d val=%d\n", Ne, val[Ne]);
	return Ne;
}
void Split(ui rt, ui &L, ui &R, ui x){
	if(!rt){
		L=R=0; return;
	}
	printf("Split %d\n", val[rt]);
	if(val[rt]<x){
		L=rt;
		Split(rs[rt], rs[L], R, x); return;
	}
	R=rt;
	Split(ls[rt], L, ls[R], x); return;
}
void insert(ui &rt, ui K){
	printf("Insert in\n");
	ui L=0, R=0;
	Split(rt, L, R, K);
	printf("Over Split\n");
	ui R0=R;
	while(ls[R0]) R0=ls[R0];
	if(val[R0]) cnt[R0]++; 
	else{
		ui Ne=++tot;
		val[Ne]=K; cnt[Ne]=1; rnd[Ne]=rand();
		printf("Merge in\n");
		R=merge(R, Ne);
	}
	printf("Merge To Rot\n");
	rt = merge(L, R);
	return ;
}
void Del(ui &rt, ui K){
	ui L=0, R=0;
	Split(rt, L, R, K);
	cnt[R]--;
	if(cnt[R]==0){
		R=merge(ls[R], rs[R]);
	}
	rt=merge(L, R);
	
}
ui getrnk(ui rt, ui K){
	ui res=0;
	while(res <= K){
		if(val[ls[rt]]>K){
			rt=ls[rt]; continue;
		}
		if(res + cnt[rt] <= K){res += cnt[rt]; rt = rs[rt]; continue;}
		if(res + cnt[rt] > K) return res + 1;
	}
}
ui getval (ui rt, ui K){
//	while(1){
//		if(K <= sze[ls[rt]]){
//			rt = ls[rt]; continue;
//		}
//		else if(K > sze[ls[rt]]){
//			K -= sze[ls[rt]];
//		}
//		if(cnt[rt]<=K) return val[rt];
//		K-=cnt[rt]; rt=rs[rt];
//	}
	if(sze[ls[rt]] < K && sze[ls[rt]] + cnt[rt] >= K) return val[rt];
	if(sze[ls[rt]] >= K) return getval(ls[rt], K);
	return getval(rs[rt], K-sze[ls[rt]]-cnt[rt]);
}
ui getPre(ui rt, ui K){
//	while(rs[rt]&&val[rt]<K) rt=rs[rt];
//	while(ls[rt]&&val[ls[rt]]>=K) rt=ls[rt];
//	while(rs[rt]) rt=rs[rt];
//	return val[rt];
	if(val[rt]<K){
		if(rs[rt]) return getPre(rs[rt], K);
		return val[rt];
	}
	if(val[rt]>=K){
		return getPre(ls[rt], K);
	}
}
ui getNxt(ui rt, ui K){
	if(val[rt]>K){
		if(ls[rt]) return getNxt(ls[rt], K);
		return val[rt];
	}
	return getNxt(rs[rt], K);
}
void print(ui rt){
	printf("%d:val=%d cnt=%d sze=%d ls=%d rs=%d\n", rt, val[rt], cnt[rt], sze[rt], ls[rt], rs[rt]);
	if(ls[rt]) print(ls[rt]);
	if(rs[rt]) print(rs[rt]);
}
int main(){
	Rot=1; val[Rot]=-inf; sze[Rot]=cnt[Rot]=1; rnd[Rot]=rand();
	n=rd();
	while(n--){
		op=rd(); x=rd();
		if(op==1){
			insert(Rot, x); //continue;
		}
		if(op==2){
			Del(Rot, x); //continue;
		}
		if(op==3){
			printf("%d\n", getrnk(Rot, x));
		}
		if(op==4){
			printf("%d\n", getval(Rot, x));
		}
		if(op==5){
			printf("%d\n", getPre(Rot, x));
		}
		if(op==6){
			printf("%d\n", getNxt(Rot, x));
		}
		printf("Tot=%d\n", tot);
		print(Rot);
	}
	return 0;
}


