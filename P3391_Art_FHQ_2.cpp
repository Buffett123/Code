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
int Rot(1), tot(1), sze[maxn], ls[maxn], rs[maxn], rnd[maxn], val[maxn], rev[maxn];
void MainTain(int Rt) {
    sze[Rt] = sze[ls[Rt]] + sze[rs[Rt]] + 1;
}
void PushDown(int Rt) { if (rev[Rt]) rev[Rt] = 0, swap(ls[Rt], rs[Rt]), rev[ls[Rt]] ^= 1, rev[rs[Rt]] ^= 1; }
void Split(int Rt, int& L, int& R, int x) {
    if (!Rt) {
        L = R = 0;
        return;
    }
    PushDown(Rt);
    register int Another(0);
    if (sze[ls[Rt]] + 1 < x) {
        L = Rt;
        Split(rs[L], Another, R, x - sze[ls[Rt]] - 1);
        rs[L] = Another;
        MainTain(L);
        return;
    }
    R = Rt;
    Split(ls[R], L, Another, x);
    ls[R] = Another;
    MainTain(R);
    return;
}
int Merge(int L, int R)
{
    if ((!L) || (!R)) return L + R;
    if (rnd[L] > rnd[R]) {
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
void Insert(int x) {
    register int R(0);
    R = ++tot, sze[tot] = 1, val[tot] = x, rnd[tot] = rand() * rand(), rev[tot] = 0;
    Rot = Merge(Rot, R);
}
void Print(int x) {
    printf("Node %u LS %u RS %u Value %u Size %u\n", x, ls[x], rs[x], val[x], sze[x]);
}
void PPRIN(int Rt) {
    PushDown(Rt);
    if (sze[ls[Rt]])PPRIN(ls[Rt]);
    if (val[Rt])printf("%d ", val[Rt]);
    if (sze[rs[Rt]])PPRIN(rs[Rt]);
}
void Reverse(int Rt, int l, int r) {
    if (rev[Rt]) PushDown(Rt);
    int L(0), R(0), TmpL(0), TmpR(0);
    Split(Rt, L, R, l);
    if (rev[R]) PushDown(R);
    Split(R, TmpL, TmpR, r - l + 2);
    rev[TmpL] ^= 1;
    R = Merge(TmpL, TmpR);
    Rot = Merge(L, R);
}
int main()
{
    double st = clock();
    // freopen("P3391_3.in", "r", stdin);
    // freopen("P3391_3.ans", "w", stdout);
    srand(573346);
    n = rd(); m = rd();
    rnd[1] = rand() * rand();
    MainTain(Rot);
    for (ri i = 1; i <= n; ++i) {
        Insert(i);
    }
    int l, r;
    while (m--) {
        l = rd() + 1; r = rd() + 1;
        Reverse(Rot, l, r);
//        PPRIN(Rot);
//        putchar('\n');
    }
    PPRIN(Rot);
    putchar('\n');
    double ed = clock();
    system("pause");
    return 0;
}
