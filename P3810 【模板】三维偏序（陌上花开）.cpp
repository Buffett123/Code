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
#define mod 998244353
#define inf 0x3fffffff
#define pi pair<int,int>
#define mp(a,b) make_pair(a, b)
#define fi first
#define se second
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

const int maxn = 100010;
int n, maxval;
int f[maxn],ans[maxn];
struct Triple{
	int id, a, b, c;
}tp[maxn];
bool cmpa(Triple x, Triple y){
	return x.a == y.a ? (x.b == y.b ? x.c < y.c : x.b < y.b) : x.a < y.a;
}
bool cmpb(Triple x, Triple y){
	return x.b == y.b ? (x.a == y.a ? x.c < y.c : x.a < y.a) : x.b < y.b;
}
int Bit[maxn];
void add(int x){
	for(int i=x;i<=maxval;i+=(i&(-i))) Bit[i] ++;
}
int query(int x){
	int res = 0;
	for(int i=x;i>=1;i-=(i&(-i))) res += Bit[i];
	return res;
}
void inadd(int x){
	for(int i=x;i<=maxval;i+=(i&(-i))) Bit[i]--;
}
void dealit(int L, int R){
	printf("%d %d\n", L, R);
	if(L >= R) return;
	int M = (L + R) >> 1;
	dealit(L, M); dealit(M + 1, R);
	sort(tp + L, tp + M + 1, cmpb);
	sort(tp + M + 1, tp + R + 1, cmpb);
	int c1=L, c2=M+1;
//	clear();
	while(c1 <= M && c2 <= R){
		printf("c1=%d c2=%d\n", c1, c2);
		while(c1 <= M && tp[c1].b <= tp[c2].b){
			add(tp[c1].c);
			c1++;
		}
		while(c2 <= R && tp[c1].b > tp[c2].b){
			ans[tp[c2].id] += query(tp[c2].c);
			c2++;
		}
		
	} 
	while(c2 <= R){
		ans[tp[c2].id] += query(tp[c2].c);
		c2++;
	}
	printf("Over while\n");
	for(int i=L; i<c1; ++i){
		inadd(tp[i].c);
	}
	for(int i=1;i<=n;++i) printf("ans[%d]=%d ", i, ans[i]); printf("\n");
	return ;
}
int main(){
	n=rd(); maxval=rd();
	for(int i=1;i<=n;++i){
		tp[i].a=rd(); tp[i].b=rd(); tp[i].c=rd(); tp[i].id=i;
	}
	sort(tp+1, tp+1+n, cmpa);
	dealit(1, n);
	for(int i=1;i<=n;++i) f[ans[i]]++;
	for(int i=0;i<n;++i) printf("%d\n", f[i]);
	printf("\n");
	return 0;
}


