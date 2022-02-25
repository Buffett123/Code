#include <bits/stdc++.h>
#define inf 0x3fffffff
#define Inf 1061109567
#define ri register int
using namespace std;
typedef long long ll;
int rd()
{
    int res = 0, fl = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            fl = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        res = (res << 3) + (res << 1) + c - '0';
        c = getchar();
    }
    return res * fl;
}
const int maxn = 100010;
int n, m, op, x;
int ROOT(1), tot(1), cnt[maxn], sze[maxn], ls[maxn], rs[maxn], rnd[maxn], val[maxn], rev[maxn];
void MainTain(int Rt) {
    sze[Rt] = sze[ls[Rt]] + sze[rs[Rt]] + cnt[Rt];
}
void PushDown(int Rt){
	if(rev[Rt]){
	 	rev[Rt] ^= 1;
		swap(ls[Rt], rs[Rt]);
		rev[ls[Rt]] ^= 1; rev[rs[Rt]] ^= 1;
	}
//	if(cnt[ls[Rt]]) PushDown(ls[Rt]);
//	if(cnt[rs[Rt]]) PushDown(rs[Rt]);
} 
void Split(int Rt, int& L, int& R, int x)
{
//	printf("Split %d sze= %d on%d\n", val[Rt], sze[Rt], x);
	if (rev[Rt]){
		PushDown(rev[Rt]);
	}
    if (!Rt){
        L = R = 0;
        return;
    }
    register int Another(0);
//    MainTain(Rt);
    if (sze[ls[Rt]] + cnt[Rt] < x)
    {
        L = Rt;
        Split(rs[L], Another, R, x - sze[ls[Rt]] - cnt[Rt]);
        rs[L] = Another;
        MainTain(L);
//	    printf("Split%d sze= %d on%d L=%d R=%d\n", val[Rt], sze[Rt], x, val[L], val[R]);
        return;
    }
    R = Rt;
    Split(ls[R], L, Another, x);
    ls[R] = Another;
    MainTain(R);
//    printf("Split%d sze= %d on%d L=%d R=%d\n", val[Rt], sze[Rt], x, val[L], val[R]);
    return;
}
int Merge(int L, int R)
{
    if ((!L) || (!R)) return L + R;
    if (rnd[L] > rnd[R])
    {
    	if(rev[L]) PushDown(L);
    	if(rev[R]) PushDown(R);
        rs[L] = Merge(rs[L], R);
        MainTain(L);
        return L;
    }
    if(rev[R]) PushDown(R);
    if(rev[L]) PushDown(L);
    ls[R] = Merge(L, ls[R]);
    MainTain(R);
    return R;
}
void Insert(int x)
{
    register int L(0), R(0), TmpL(0), TmpR(0);
    if(rev[ROOT]) PushDown(ROOT);
    Split(ROOT, L, R, x);
    if(rev[R]) PushDown(R);
    Split(R, TmpL, TmpR, x + 1);
    if (TmpL) {
        ++cnt[TmpL];
        ++sze[TmpL];
    }
    else {
        TmpL = ++tot, cnt[tot] = sze[tot] = 1, val[tot] = x, rnd[tot] = rand() * rand();
        val[tot] = x; rev[tot] = 0;
    }
    R = Merge(TmpL, TmpR);
    ROOT = Merge(L, R);
    return;
}

void Print(int Rt){
	if(rev[Rt]){
		PushDown(Rt);
	}
	printf("sze=%d val[%d]=%d->val[%d]=%d\nval[%d]=%d->val[%d]=%d\n", sze[Rt], Rt, val[Rt], ls[Rt], val[ls[Rt]], Rt, val[Rt], rs[Rt], val[rs[Rt]]);
	if(cnt[ls[Rt]])Print(ls[Rt]);
//	printf("%d ", val[Rt]);
	if(cnt[rs[Rt]])Print(rs[Rt]);
}

void PPrin(int Rt){
	if(rev[Rt]){
		PushDown(Rt);
	}
//	printf("sze=%d val[%d]=%d->val[%d]=%d\nval[%d]=%d->val[%d]=%d\n", sze[Rt], Rt, val[Rt], ls[Rt], val[ls[Rt]], Rt, val[Rt], rs[Rt], val[rs[Rt]]);
	if(cnt[ls[Rt]])PPrin(ls[Rt]);
//	printf("%d ", val[Rt]);
	if(cnt[rs[Rt]])PPrin(rs[Rt]);
}
int haveprint;
void PPRIN(int Rt){
	if(rev[Rt]){
		PushDown(Rt);
	}
//	printf("sze=%d val[%d]=%d->val[%d]=%d\nval[%d]=%d->val[%d]=%d\n", sze[Rt], Rt, val[Rt], ls[Rt], val[ls[Rt]], Rt, val[Rt], rs[Rt], val[rs[Rt]]);
	if(cnt[ls[Rt]])PPRIN(ls[Rt]);
	printf("%d ", val[Rt]);
	haveprint++;
//	if(haveprint % 10 == 0) printf("\n");
	if(cnt[rs[Rt]])PPRIN(rs[Rt]);
}
void Reverse(int Rt, int l, int r){

//	printf("reverse %d %d\n", l, r);
	if(rev[Rt]) PushDown(Rt);
	int L(0), R(0), TmpL(0), TmpR(0);
	Split(Rt, L, R, l);

//	printf("NOW COUT L\n"); 
//	PPrin(L); printf("\n");
//	Print(L); printf("\n");
	if(rev[R]) PushDown(R); 
	Split(R, TmpL, TmpR, r - l + 2);
	rev[TmpL] ^= 1;
	
//	PPrin(TmpL); printf("\n");
//	PPrin(TmpR); printf("\n");
//	Print(TmpL); printf("\n");
//	Print(TmpR); printf("\n");
	
	R = Merge(TmpL, TmpR);
	
//	printf("NOW COUT R\n");
//	Print(R);
//	PPrin(R);
//	printf("\n");

	ROOT = Merge(L, R); 
}


int main()
{
	double st = clock();
	freopen("P3391_3.in", "r", stdin);
	freopen("P3391_3.ans", "w", stdout);
    srand(time(NULL));
    n = rd(); m = rd();
    /*val[0] = inf, val[1] = Inf, cnt[1] = sze[1] = 0*/;
    rnd[1] = rand() * rand();
    MainTain(ROOT);
    for(ri i = 1; i <= n; ++i){
    	Insert(i);
	}
//	Print(ROOT);
	int l, r;
	while(m--){
		l = rd(); r = rd();
		Reverse(ROOT, l, r);
//		Print(ROOT);
//		printf("\n");
		PPrin(ROOT);
//		if(rev[ROOT])
//			PushDown(ROOT);
//		for(ri i = 0; i <= tot; ++i){
//			if(val[i] == 3){
//				printf("%d ls[%d]=%d rs[%d]=%d\n", i, i, ls[i], i, rs[i]);
//			}
//		}
	}
	PPRIN(ROOT);
//	printf("haveprint %d\n", haveprint);
	double ed = clock();
//	printf("TM=%lf\n", ed - st);
    return 0;
}
