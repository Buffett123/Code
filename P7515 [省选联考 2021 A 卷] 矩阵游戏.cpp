#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int rd(){
	int res = 0, fl = 1; char c = getchar();
    while(!isdigit(c)){if(c == '-') fl = -1; c = getchar();}
    while(isdigit(c)){res = (res << 3) + (res << 1) + c - '0'; c = getchar();}
    return res * fl;
}
const int maxn = 310;
int n, m, a[maxn], b[maxn], sum[maxn], Max(0x3f3f3f3f), Min(0);
int main(){
	n = rd(); m = rd();
	if(m != 2) return 0;
	for(int i(2); i <= n; ++i) b[i] = rd(), sum[i] = sum[i - 2] + b[i];
	for(int i(2); i <= n; i += 2) Max = min(Max, sum[i] - sum[i - 1]);
	for(int i(1); i <= n; i += 2) Min = max(Min, sum[i - 1] - sum[i]);
	if(Min > Max) printf("NO\n");
	else{
		puts("YES\n");
		a[1] = Min;
		for(int i(2); i <= n; ++i) a[i] = b[i] - a[i - 1];
		for(int i(1); i <= n; ++i) printf("%d\n", a[i]);
	}
	return 0;
}
