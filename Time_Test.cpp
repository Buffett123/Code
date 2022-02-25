#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int rd(){
	int res = 0, fl = 1; char c = getchar();
    while(!isdigit(c)){if(c == '-') fl = -1; c = getchar();}
    while(isdigit(c)){res = (res << 3) + (res << 1) + c - '0'; c = getchar();}
    return res * fl;
}
const int maxn = 1000010;
int main(){
	double st = clock();
	for(register int i = 1; i <= 3750000000; ++i);
	double ed = clock();
	printf("%lf\n", ed - st); 
	return 0;
}



