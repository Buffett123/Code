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
int f1 = -777, f2 = 123;
int main(){
	cout << f1 << " " << f2 << endl;
	for(int i = 3; i <= 3000000000; ++i){
		swap(f1, f2);
		f2 += f1;
//		printf("%d %d\n", f1, f2);
		if(f1 == -777 && f2 == 123) {
			printf("%d f1=%d f2=%d\n", i, f1, f2);
		}
	}
	return 0;
}



