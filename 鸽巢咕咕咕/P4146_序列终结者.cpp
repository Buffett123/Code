#include<bits/stdc++.h>
#define ri rsgister int
using namespace std;
typedef long long ll;
int rd(){
	int res = 0, fl = 1; char c = getchar();
    while(!isdigit(c)){if(c == '-') fl = -1; c = getchar();}
    while(isdigit(c)){res = (res << 3) + (res << 1) + c - '0'; c = getchar();}
    return res * fl;
}
const int maxn = 500010;
int Rot, n, m, k, l, r, v, tot, ls[maxn], rs[maxn], val[maxn], tag[maxn], rev[maxn], rnd[maxn], cnt[maxn], sze[maxn], mav[maxn];
void MainTain(int Rt){
	sze[Rt] = cnt[Rt] + sze[ls[Rt]] + sze[rs[Rt]];
	mav[Rt] = val[Rt];
	if(ls[Rt]) mav[Rt] = max(mav[Rt], mav[ls[Rt]]);
	if(rs[Rt]) mav[Rt] = max(mav[Rt], mav[rs[Rt]]);
}
void MakeTag(int Rt, int x){
	tag[Rt] += x; mav[Rt] += x; val[Rt] += x;
}
void PushDown(int Rt){
	if(tag[Rt]){
		MakeTag(ls[Rt], tag[Rt]); MakeTag(rs[Rt], tag[Rt]);
		MainTain(Rt);
		tag[Rt] = 0;
	}
	if(rev[Rt]){
		rev[Rt] ^= 1;
		swap(ls[Rt], rs[Rt]);
		rev[ls[Rt]] ^= 1; rev[rs[Rt]] ^= 1;
	}
}
void Split(int Rt, int &L, int &R, int x){
	if(!Rt){
		L = R = 0; return;
	}
	PushDown(Rt);
	int Another(0);
	if(sze[ls[Rt]] + cnt[Rt] < x){
		L = Rt;
		Split(rs[L], Another, R, x - sze[ls[Rt]] - cnt[Rt]);
		rs[L] = Another;
//		Split(rs[L], rs[L], R, x - sze[ls[Rt]] - cnt[Rt]);
		MainTain(L);
		return;
	}
	R = Rt;
	Split(ls[R], L, Another, x);
	ls[R] = Another;
//	Split(ls[R], L, ls[R], x);
	MainTain(R);
	return;
}
int Merge(int L, int R){
	if((!L) || (!R)) return L + R;
	if(rnd[L] > rnd[R]){
		PushDown(L);
		rs[L] = Merge(rs[L], R);
		MainTain(L);
		return L;
	}
	PushDown(R);
	ls[R] = Merge(L, ls[R]);
	MainTain(R);
	return R; 
}
void Insert(int x){
	int Tmp = ++tot;
	val[tot] = 0; rnd[tot] = rand() * rand();
	sze[tot] = cnt[tot] = 1;
	Rot = Merge(Rot, Tmp);
}
void Print(int Rt){
	printf("sze[%d]=%d cnt[%d]=%d val[%d]=%d tag[%d]=%d rev[%d]=%d [mav[%d]=%d] sze[ls]=%d sze[rs]=%d\n", Rt, sze[Rt], Rt, cnt[Rt], Rt, val[Rt], Rt, tag[Rt], Rt, rev[Rt], Rt, mav[Rt], sze[ls[Rt]], sze[rs[Rt]]);
	if(ls[Rt]) Print(ls[Rt]);
	if(rs[Rt]) Print(rs[Rt]);
} 
int main(){
	srand(50214002);
	int L, R, TmpL, TmpR;
	n = rd(); m = rd();
	for(int i = 1; i <= n; ++i) Insert(0);
	
//	Print(Rot); 

	while(m--){
		k = rd(); l = rd(); r = rd();
		if(k == 1){
			v = rd();
			L = 0, R = 0, TmpL = 0, TmpR = 0; 
			Split(Rot, L, R, l); 
			Split(R, TmpL, TmpR, r + 1);
			MakeTag(TmpL, v);
			R = Merge(TmpL, TmpR);
			Rot = Merge(L, R);
			
//			Print(Rot);
			
			continue;
		}
		if(k == 2){
			L = 0, R = 0, TmpL = 0, TmpR = 0;
			Split(Rot, L, R, l);
			Split(R, TmpL, TmpR, r - l + 2);
			rev[TmpL] ^= 1;
			R = Merge(TmpL, TmpR);
			Rot = Merge(L, R);
			
//			Print(Rot);
			
			continue;
		}
		Split(Rot, L, R, l);
		Split(R, TmpL, TmpR, r + 1);
		printf("%d\n", mav[TmpL]);
		R = Merge(TmpL, TmpR);
		Rot = Merge(L, R);
		
//		Print(Rot);
	
	}
	return 0;
}
