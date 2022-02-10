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
int n, a[2010][2010], b[2010][2010];
int main(){
	while(cin >> n){
		for(int i(1); i <= n; ++i){
			for(int j(1); j <= n; ++j){
				cin >> a[i][j];
			}
		}
		printf("After:\n");
		for(int i(1); i <= n; ++i) for(int j(1); j <= n; ++j) b[i][j] = 0;
		for(int k(1); k <= n; ++k){
			for(int i(1); i <= n; ++i){
				for(int j(1); j <= n; ++j) b[i][j] += a[i][k] * a[k][j];
			}
		}
		for(int i(1); i <= n; ++i){for(int j(1); j <= n; ++j) printf("%d ", b[i][j]); printf("\n");}
		
	}
	return 0;
}

