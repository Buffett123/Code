//灵魂何必无处安放 
#include<bits/stdc++.h>
#define ll long long
#define MOD 998244353
using namespace std;
int rd(){
	int res(0), fl(1);
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
const int maxn = 100010;
struct Edge{
	int to, nxt;
}ed[maxn << 1]; 
struct Node{
	Node *ls, *rs;
	int l, r, sum;
	void Upd(int L, int R, int Tp){
		if(L > r || R < l) return;
		if(L <= l && r <= R){
			sum += Tp * (r - l + 1); return;
		}
		ls->Upd(L, R, Tp); rs->Upd(L, R, Tp);
		sum = ls->sum + rs->sum; return;
	}
	int Qry(int L, int R){
		if(L <= l && r <= R) return sum;
		if(L > r || R < l) return 0;
		return ls->Qry(L, R) + rs->Qry(L, R); 
	}
}Mem[maxn << 1], *pool = Mem, *Rot;
Node* Build(int L, int R){
	Node *u = ++pool;
	u->l = L; u->r = R; u->sum = 0;
	if(L == R){
		u->ls = NULL; u->rs = NULL;
	}
	else{
		int M((L + R) >> 1);
		u->ls = Build(L, M); u->rs = Build(M + 1, R);
	}
	return u;
}
struct St{
	int dep, id;
	bool operator < (const St S) const{
		return dep < S.dep;
	}
}st[maxn][20];
int n, Col[maxn], en, fst[maxn], lne, Lg[maxn], cnt, Fa[maxn], Dfn[maxn], Sze[maxn], Seg[maxn], Dep[maxn], Top[maxn], Son[maxn];
ll Ans; 
vector<int> Plt[maxn];
void add(int u, int v){
	ed[++en].to = v; ed[en].nxt = fst[u]; fst[u] = en;
}
void DFS1(int u, int fa){
	Dep[u] = Dep[fa] + 1;
	Fa[u] = fa;
	for(int e(fst[u]); e; e = ed[e].nxt){
		int v = ed[e].to;
		if(v == fa) continue;
		DFS1(v, u);
		if(Sze[v] > Sze[Son[u]]) Son[u] = v;
		Sze[u] += Sze[v];
	}
	Sze[u]++;
}
void DFS2(int u, int top){
	Top[u] = top; Dfn[u] = ++cnt; st[cnt][0].id = u; st[cnt][0].dep = Dep[u]; Seg[cnt] = u;
	if(Son[u]) DFS2(Son[u], top);
	for(int e(fst[u]); e; e = ed[e].nxt){
		int v = ed[e].to;
		if(v == Fa[u] || v == Son[u]) continue;
		DFS2(v, v);
	}
}
int GetMin(int x, int y){
	int k(y - x + 1);
	return min(st[x][Lg[k]], st[y - (1 << Lg[k]) + 1][Lg[k]]).id;
} 
struct Line{
	int h, l, r, tp;
	bool operator < (const Line L) const{
		return h < L.h;
	}
}Lne[maxn * 40];
int main(){
	Lg[0] = -1;
	for(int i(1); i <= 100000; ++i) Lg[i] = Lg[i >> 1] + 1;
	n = rd(); int u, v;
	for(int i(1); i <= n; ++i){
		Col[i] = rd(); Plt[Col[i]].push_back(i); 
	} 
	for(int i(1); i < n; ++i){
		u = rd(); v = rd();
		add(u, v); add(v, u);
	} //printf("Over cin\n");
	DFS1(1, 0);
	DFS2(1, 1);
	Rot = Build(1, n);
	for(int j(1); j <= 18; ++j){
		for(int i(1); i <= cnt; ++i){
			if(i + (1 << (j - 1)) <= cnt) st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
	for(int i(1); i <= n; ++i){
		if(!Plt[i].size()) continue;
		int sze = Plt[i].size();
		for(int j(0); j < sze; ++j){
			for(int k(j + 1); k < sze; ++k){
				int u = Plt[i][j], v = Plt[i][k];
				if(u > v) swap(u, v);
				int lca = GetMin(Dfn[u], Dfn[v]);
				if(lca != u){
					if(Dfn[u] < Dfn[v]){
						Lne[++lne] = Line{Dfn[v], Dfn[u], Dfn[u] + Sze[u] - 1, 1};
						Lne[++lne] = Line{Dfn[v] + Sze[v] - 1, Dfn[u], Dfn[u] + Sze[u] - 1, -1};
					} 
					else{
						Lne[++lne] = Line{Dfn[u], Dfn[v], Dfn[v] + Sze[v] - 1, 1};
						Lne[++lne] = Line{Dfn[u] + Sze[u] - 1, Dfn[v], Dfn[v] + Sze[v] - 1, -1};
					}
				}
				else if(lca == u){
					// [1  [dfn[u]   [dfn[v], dfn[v] + sze[v] - 1]    dfn[u] + sze[u] - 1]    n]
					// ----          -----------------------------                        ------
					Lne[++lne] = Line{Dfn[v], 1, Dfn[u] - 1, 1};
					Lne[++lne] = Line{Dfn[v] + Sze[v] - 1, Dfn[u] + Sze[u], n, -1};
				}
				else{
					Lne[++lne] = Line{Dfn[u], 1, Dfn[v] - 1, 1};
					Lne[++lne] = Line{Dfn[u] + Sze[u] - 1, Dfn[v] + Sze[v], n, -1};
				}
			}
		}
	}
	sort(Lne + 1, Lne + 1 + lne);
	Rot->Upd(Lne[1].l, Lne[1].r, Lne[1].tp);
	for(int i(2); i <= lne; ++i){
		Rot->Upd(Lne[i].l, Lne[i].r, Lne[i].tp); 
		if(Lne[i].h != Lne[i - 1].h){
			Ans += 1ll * (Lne[i].h - Lne[i - 1].h) * Rot->Qry(1, n);
		}
	}
	Ans = 1ll * n * (n + 1) / 2 - Ans;
	printf("%lld\n", Ans);
	return 0;
}

