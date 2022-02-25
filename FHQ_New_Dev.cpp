#include <bits/stdc++.h>
#define inf 0x3fffffff
#define Inf 1061109567
#define Mod 1000000007 
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
int n, op, x;
int Rot(1), tot(1), cnt[maxn], sze[maxn], ls[maxn], rs[maxn], rnd[maxn], val[maxn];
int Rand(){
	return rnd[tot] * rnd[tot - 1] + val[tot];
} 
void MainTain(int Rt)
{
    sze[Rt] = sze[ls[Rt]] + sze[rs[Rt]] + cnt[Rt];
}
void Split(int Rt, int &L, int &R, int x)
{
    if (!Rt)
    {
        L = R = 0;
        return;
    }
    if (val[Rt] < x)
    {
        L = Rt;
        Split(rs[Rt], rs[Rt], R, x);
        MainTain(L); 
        return;
    }
    R = Rt;
    Split(ls[Rt], L, ls[Rt], x);
    MainTain(R);
    return;
}
int Merge(int L, int R)
{
    if((!L) || (!R)) return L + R;
    if (rnd[L] > rnd[R])
    {
        rs[L] = Merge(rs[L], R);
        MainTain(L);
        return L;
    }
    ls[R] = Merge(L, ls[R]);
    return R;
}
void Insert(int x)
{
    int L(0), R(0), TmpL(0), TmpR(0);
    Split(Rot, L, R, x);
    Split(R, TmpL, TmpR, x + 1);
    if(!cnt[TmpL]){
    	TmpL = ++tot; 	
		val[tot] = x;
    	rnd[tot] = Rand();
		sze[tot] = cnt[tot] = 1;
	}
	else {
		sze[TmpL]++; cnt[TmpL]++;
	}
	R = Merge(TmpL, TmpR);
	Rot = Merge(L, R);
	return;
}

void Del(int x)
{
    int L(0), R(0), TmpL(0), TmpR(0);
    Split(Rot, L, R, x);
    Split(R, TmpL, TmpR, x + 1);
    if(cnt[TmpL] > 1){
    	cnt[TmpL]--; sze[TmpL]--;
    	R = Merge(TmpL, TmpR);
	}
	else R = TmpR;
	Rot = Merge(L, R);
	return;
}
int GetRnk(int Rt, int x)
{
	if(sze[Rt] = cnt[Rt]){//льепр╤╫з╣Ц 
		if(val[Rt] >= x) return 0;
		return sze[Rt];
	}
    if (val[Rt] >= x)
        return GetRnk(ls[Rt], x);
    if (val[Rt] < x)
        return GetRnk(rs[Rt], x) + sze[ls[Rt]] + cnt[Rt];
}
int GetVal(int Rt, int x)
{
    if (x > sze[ls[Rt]] && (x <= sze[ls[Rt]] + cnt[Rt]))
        return val[Rt];
    if (x <= sze[ls[Rt]])
        return GetVal(ls[Rt], x);
    if (x > sze[ls[Rt]] + cnt[Rt])
        return GetVal(rs[Rt], x - sze[ls[Rt]] - cnt[Rt]);
}
void Print(int Rt){
	if(cnt[Rt] == 0) return;
	printf("Node:%d val=%d cnt=%d sze=%d ls=%d rs=%d\n", Rt, val[Rt], cnt[Rt], sze[Rt], ls[Rt], rs[Rt]);
	Print(ls[Rt]); Print(rs[Rt]);
}
int main()
{
	srand(20041022);
    n = rd();
    val[0] = inf, val[1] = Inf, cnt[1] = sze[1] = 0;
    rnd[1] = rand() * rand();
    MainTain(Rot);
    Print(Rot);
    while (n--)
    {
        op = rd();
        x = rd();
        if (op == 1)
            Insert(x);
        if (op == 2)
            Del(x);
        if (op == 3)
            printf("%d\n", GetRnk(Rot, x) + 1);
        if (op == 4)
            printf("%d\n", GetVal(Rot, x));
        if (op == 5)
            printf("%d\n", GetVal(Rot, GetRnk(Rot, x)));
        if (op == 6)
            printf("%d\n", GetVal(Rot, GetRnk(Rot, x + 1) + 1));
        Print(Rot);
    }
    return 0;
}
