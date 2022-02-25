#include <bits/stdc++.h>
#define inf 0x3fffffff
#define Inf 1061109567
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
void MainTain(int Rt) {
    sze[Rt] = sze[ls[Rt]] + sze[rs[Rt]] + cnt[Rt];
}
void Split(int Rt, int& L, int& R, int x)
{
    // printf("Split %u %u\n", Rt, x);
    if (!Rt)
    {
        L = R = 0;
        return;
    }
    register int Another;
    if (val[Rt] < x)
    {
        L = Rt;
        Split(rs[L], Another, R, x);
        rs[L] = Another;
        MainTain(L)/*, MainTain(R)*/;
        return;
    }
    R = Rt;
    Split(ls[R], L, Another, x);
    ls[R] = Another;
    /*MainTain(L), */MainTain(R);
    return;
}
int Merge(int L, int R)
{
    // printf("Merge %u %u\n", L, R);
    if ((!L) || (!R)) return L + R;
    if (rnd[L] > rnd[R])
    {
        rs[L] = Merge(rs[L], R);
        MainTain(L);
        return L;
    }
    ls[R] = Merge(L, ls[R]);
    MainTain(R);
    return R;
}
void Insert(int x)
{
    register int L(0), R(0), TmpL(0), TmpR(0);
    Split(Rot, L, R, x);
    Split(R, TmpL, TmpR, x + 1);
    if (TmpL) {
        ++cnt[TmpL];
        ++sze[TmpL];
    }
    else {
        TmpL = ++tot, cnt[tot] = sze[tot] = 1, val[tot] = x, rnd[tot] = rand() * rand();
    }
    R = Merge(TmpL, TmpR);
    Rot = Merge(L, R);
    return;
}
void Del(int x) {
    int L = 0, R = 0, TmpL(0), TmpR(0);
    Split(Rot, L, R, x);
    Split(R, TmpL, TmpR, x + 1);
    if (cnt[TmpL] > 1) --sze[TmpL], --cnt[TmpL], R = Merge(TmpL, TmpR);
    else R = TmpR;
    Rot = Merge(L, R);
    // printf("Deled %u NowRot %u Size %u Val %u\n", x, Rot, sze[Rot], val[Rot]);
    return;
}
int res;
int GetRnk(int Rt, int x) {
    // printf("Now %u Val %u Find %u Size %u LR %u RS %u\n", Rt, val[Rt], x, sze[Rt], ls[Rt], rs[Rt]);
    if (sze[Rt] == cnt[Rt]) {
        if (val[Rt] >= x)
            return 0;
        return sze[Rt];
    }
    if (val[Rt] >= x)
        return GetRnk(ls[Rt], x);
    if (val[Rt] < x)
        return GetRnk(rs[Rt], x) + sze[ls[Rt]] + cnt[Rt];
}
int GetVal(int Rt, int x) {
    // printf("GV Now %u  Val %u Get %u LS %u RS %u Size %u Cnt %u\n", Rt, val[Rt], x, ls[Rt], rs[Rt], sze[Rt], cnt[Rt]);
    if ((x > sze[ls[Rt]]) && (x <= sze[ls[Rt]] + cnt[Rt]))
        return val[Rt];
    if (x <= sze[ls[Rt]])
        return GetVal(ls[Rt], x);
    if (x > sze[ls[Rt]] + cnt[Rt])
        return GetVal(rs[Rt], x - sze[ls[Rt]] - cnt[Rt]);
}
int main()
{
    // freopen("P3369_6.in", "r", stdin);
    // freopen("P3369.out", "w", stdout);
    // printf("YOU IDOIT\n");
    srand(20041022);
    n = rd();
    val[0] = inf, val[1] = Inf, cnt[1] = sze[1] = 0;
    rnd[1] = rand() * rand();
    MainTain(Rot);
    while (n--)
    {
        op = rd();
        x = rd();
        if (op == 1)
            Insert(x);
        if (op == 2)
            Del(x);
        if (op == 3)
            printf("%d\n", 1 + GetRnk(Rot, x));
        if (op == 4)
            printf("%d\n", GetVal(Rot, x));
        if (op == 5)
            printf("%d\n", GetVal(Rot, GetRnk(Rot, x)));
        if (op == 6)
            printf("%d\n", GetVal(Rot, 1 + GetRnk(Rot, x + 1)));
    }
    // system("pause");
    return 0;
}
