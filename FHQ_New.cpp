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
const int maxn = 1000010;
int n, op, x;
int tot, cnt[maxn], sze[maxn], ls[maxn], rs[maxn], rnd[maxn], val[maxn];
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
        return;
    }
    R = Rt;
    Split(ls[Rt], L, ls[Rt], x);
    return;
}
int Merge(int L, int R)
{
    int Ne;
    if (rnd[L] > rnd[R])
    {
        Ne = L;
        // ls[Ne] = ls[L];
        rs[Ne] = Merge(rs[Ne], R);
        return Ne;
    }
    Ne = R;
    // rs[Ne] = rs[R];
    ls[Ne] = Merge(L, ls[Ne]);
    return Ne;
}
void Insert(int Rt, int x)
{
    if (val[Rt] == inf)
    {
        val[Rt] = x;
        cnt[Rt] = sze[Rt] = 1;
        return;
    }
    if (val[Rt] == x)
    {
        cnt[Rt]++;
        MainTain(Rt);
        return;
    }
    if (val[Rt] < x)
    {
        if (!rs[Rt])
        {
            rs[Rt] = ++tot;
            rnd[tot] = rand() * rand();
        }
        Insert(rs[Rt], x);
        MainTain(Rt);
        return;
    }
    if (!ls[Rt])
    {
        ls[Rt] = ++tot;
        rnd[tot] = rand() * rand();
    }
    Insert(ls[Rt], x);
    MainTain(Rt);
    return;
}
void del(int Rt, int x)
{
    if (val[Rt] == inf)
    {
        cnt[Rt] = 1;
        val[Rt] = x;
        MainTain(Rt);
        return;
    }
    if (ls[Rt] = 0)
    {
        ls[Rt] = ++tot;
    }
    del(ls[Rt], x);
    MainTain(Rt);
    return;
}
void Del(int Rt, int x)
{
    int L = 0, R = 0;
    Split(Rt, L, R, x);
    del(R, x);
    Rt = Merge(L, R);
    return;
}
int res;
int GetNxt(int Rt, int x)
{
    if (val[Rt] < x)
    {
        if (rs[Rt])
            return GetNxt(rs[Rt], x);
    }
    if (val[Rt] >= x)
    {
        res = val[Rt];
        if (ls[Rt])
            return GetNxt(ls[Rt], x);
    }
    return res;
}
int GetPre(int Rt, int x)
{
    if (val[Rt] < x)
    {
        res = val[Rt];
        if (rs[Rt])
            return GetPre(rs[Rt], x);
    }
    if (val[Rt] >= x)
    {
        if (ls[Rt])
            return GetPre(ls[Rt], x);
    }
    return res;
}
int GetRnk(int Rt, int x)
{
    if (val[Rt] == x)
        return sze[ls[Rt]];
    if (val[Rt] > x)
        return GetRnk(ls[Rt], x);
    if (val[Rt] < x)
        return GetRnk(rs[Rt], x) + sze[ls[Rt]] + cnt[Rt];
}
int GetVal(int Rt, int x)
{
    if (x > sze[ls[Rt]] && x <= sze[ls[Rt]] + cnt[Rt])
        return val[Rt];
    if (x <= sze[ls[Rt]])
        return GetVal(ls[Rt], x);
    if (x > sze[ls[Rt]] + cnt[Rt])
        return GetVal(rs[Rt], x - sze[ls[Rt]] - cnt[Rt]);
}
int main()
{
    printf("YOU IDOIT\n");
    n = rd();
    for (register int i = 0; i <= maxn; ++i)
        val[i] = inf;
    int Rot = 1;
    val[1] = -Inf;
    rnd[1] = rand() * rand();
    MainTain(Rot);
    while (n--)
    {
        op = rd();
        x = rd();
        if (op == 1)
            Insert(Rot, x);
        if (op == 2)
            Del(Rot, x);
        if (op == 3)
            printf("%d\n", GetRnk(Rot, x));
        if (op == 4)
            printf("%d\n", GetVal(Rot, x));
        if (op == 5)
            printf("%d\n", GetPre(Rot, x));
        if (op == 6)
            printf("%d\n", GetNxt(Rot, x));
    }
    return 0;
}