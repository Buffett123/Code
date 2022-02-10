#include<bits/stdc++.h>
#define ll long long
#define MOD 998244353
using namespace std;
ll rd(){
	ll res(0), fl(1);
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
ll a, b, s, len, p0, p1, Inv100, Inv2, Ans, g[10000010], Inv[10000010];
ll ksm(ll base, ll p){
	ll res(1);
	for(; p; p >>= 1){
		if(p & 1) (res *= base) %= MOD;
		(base *= base) %= MOD;
	}
	return res;
}
ll work(ll a, ll b, ll x){
	if(x == 0) {
//		printf("work(%lld,%lld,%lld)=%lld\n", a, b, x, (a + b) * Inv2 % MOD);
		return (a + b) * Inv2 % MOD;
	}
//	printf("work(%lld,%lld,%lld)=%lld\n", a, b, x, p1 * Inv100 % MOD * work((a + b) / 2, b, x - 1) + p0 * Inv100 % MOD * work(a, (a + b) / 2, x - 1) % MOD);
	return p1 * Inv100 % MOD * work((a + b) / 2, b, x - 1) % MOD + p0 * Inv100 % MOD * work(a, (a + b) / 2, x - 1) % MOD;
}
void Subtask1(){
	printf("a=%lld b=%lld s=%lld\n", a, b, s);
	printf("%lld\n", work(a, b, s));
}
void Subtask3(){
	Inv[1] = Inv2;
	for(int i(2); i <= s; ++i){
		Inv[i] = (Inv[i - 1] * Inv2) % MOD;
	}
	g[s] = len * Inv[s] % MOD;
	for(int i(s - 1); i >= 0; --i){
		g[i] = (g[i + 1] + len * Inv[i + 1] % MOD * p1 * Inv100 % MOD) % MOD;
	}
	printf("%lld\n", g[1]);
}
int main(){
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	Inv100 = ksm(100ll, MOD - 2);
	Inv2 = ksm(2ll, MOD - 2);
	a = rd(); b = rd(); s = rd(); p0 = rd(); p1 = rd(); len = b - a;
//	if(s <= 20){
//		Subtask1(); return 0;
//	}
	if(p0 == 50){
		Ans = ((a + b) * Inv2) % MOD;
		printf("%lld\n", Ans);
		return 0;
	}
//	if(s <= 10000000){
//		Subtask3(); return 0;
//	}
	Ans = (((Inv2 - ksm(Inv2, s + 1) + MOD) % MOD * (p1 - p0) % MOD * Inv100 % MOD * len % MOD + (a + b) * Inv2 % MOD) % MOD + MOD) % MOD;
//	Ans = ((1 - ksm(Inv2, s)) % MOD * 2 % MOD * (p1 - p0) % MOD * Inv100 % MOD * len % MOD + (a + b) / 2 % MOD) % MOD;
	printf("%lld\n", Ans);
	return 0;
}
/*
1 2 1 50 50
*/
