/*
集合幂级数乘法、乘法逆元、ln、exp、左复合多项式
*/
#include<stdio.h>
#include<string.h>
#include<vector>
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int word;
typedef unsigned short hword;
typedef unsigned char byte;
#define mx 20
#define mx_ 19
#define FOR(size) for(word i=0;i<(size);++i)
#define fftfor(size)								\
	for(word floor=1;floor<(size);floor<<=1)		\
		for(word head=0;head<(size);head+=floor<<1)	\
			for(word i=0;i<floor;++i)
const word mod=998244353;
inline word qpow(word a,word b){
	word ans=1;
	for(;b;b>>=1){
		if(b&1) ans=1ull*ans*a%mod;
		a=1ull*a*a%mod;
	}
	return ans;
}
word popcnt[1<<mx];
std::vector<word> pos[mx+1];
#define lowbit(x) ((x)&-(x))
struct READ{
	char c;
	inline READ(){
		pos[popcnt[0]=0].push_back(0);
		for(int i=1;i<(1u<<mx);++i)
			pos[popcnt[i]=popcnt[i-lowbit(i)]+1].push_back(i);
		c=getchar();}
	template<typename type>
	inline READ& operator >>(type& num){
		while('0'>c||c>'9') c=getchar();
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
}cin;
#define _or(num) (((num)[head|i|floor]+=(num)[head|i])%=mod)
#define or_(num) (((num)[head|i|floor]+=mod-(num)[head|i])%=mod)
#define _and(num) (((num)[head|i]+=(num)[head|i|floor])%=mod)
#define and_(num) (((num)[head|i]+=mod-(num)[head|i|floor])%=mod)
#define _xor(num)(	\
		num1=(num)[head|i],	\
		num2=(num)[head|i|floor],	\
		(num)[head|i]=(num1+mod-num2)%mod,	\
		(num)[head|i|floor]=(num1+num2)%mod)
#define xor_(num)(	\
		num1=(num)[head|i],	\
		num2=(num)[head|i|floor],	\
		(num)[head|i]=(num1+num2)%mod,	\
		(num)[head|i|floor]=(num2+mod-num1)%mod)
word in[1<<mx],eax[1<<mx],ebx[1<<mx],eex[1<<mx];
word ecx[mx][1<<mx],edx[mx][1<<mx];

inline void _1(const word n){//ebx<-1/eax
	ebx[0]=qpow(eax[0],mod-2);
	for(word k=1;k<n;++k){
		for(const auto &i:pos[k])
			ecx[k][i]=1ull*(mod-ebx[0])*eax[i]%mod;
		fftfor(1u<<n) _or(ecx[k]);
		FOR(1u<<n) edx[k][i]=1ull*ebx[0]*ecx[k][i]%mod;
	}
	for(word k=1;k<n;++k){
		memcpy(eex,edx[k],4u<<n);
		fftfor(1u<<n) or_(eex);
		for(const auto &i:pos[k]) ebx[i]=eex[i];
		for(word j=1;j+k<=n;++j)
			FOR(1u<<n) edx[j+k][i]=(1ull*ecx[j][i]*edx[k][i]+edx[k+j][i])%mod;
	}
	if(n){
		ull get=0;
		for(word i=1;i<(1u<<n);++i) get+=1ull*eax[i]*ebx[((1u<<n)-1)^i]%mod;
		ebx[(1u<<n)-1]=get%mod*(mod-ebx[0])%mod;
	}
}
inline void exp(const word n){//ebx=exp(eax)
	if(ebx[0]=1,n==0) return;
	edx[0][0]=1;
	for(word k=1;k<n;++k)
		memset(edx[k],0,4u<<(n-1));
	for(int m=0;m<n;++m){
		const word size=1u<<m;
		for(word k=1;k<m;++k)
			memset(ecx[k],0,4u<<m);
		FOR(size) ecx[popcnt[i]][i]=eax[size|i];
		for(word k=1;k<m;++k)
			fftfor(size) _or(ecx[k]);
		if(m){
			const word size=1u<<(m-1);
			FOR(size) edx[popcnt[i]+1][size|i]=ebx[size|i];
			for(word k=1;k<=m;++k){
				fftfor(size) _or(edx[k]+size);
				FOR(size) (edx[k][size|i]+=edx[k][i])%=mod;
			}
		}
		for(int k=m-1;k>0;--k){
			FOR(size){
				ull get=0;
				for(int j=1;j<k;++j)
					get+=1ull*ecx[j][i]*edx[k-j][i]%mod;
				ecx[k][i]=(get+ecx[k][i]+1ull*ecx[0][0]*edx[k][i])%mod;
			}
			fftfor(size) or_(ecx[k]);
		}
		ull get=0;
		FOR(1u<<m) get+=1ull*eax[1u<<m|i]*ebx[((1u<<m)-1)^i]%mod;
		ecx[m][(1u<<m)-1]=get%mod;
		FOR(size) ebx[size|i]=ecx[popcnt[i]][i];
	}
}

inline void ln(const word n){//in=ln(eax),ebx=1/eax
	if(in[0]=0,n==0) return;
	_1(n-1);
	for(word k=1;k<n;++k)
		memset(edx[k],0,4u<<(n-1));
	FOR(1u<<(n-1)) edx[popcnt[i]][i]=ebx[i];
	for(word k=1;k<n-1;++k)
		fftfor(1u<<(n-1)) _or(edx[k]);
	for(int m=0;m<n;++m){
		const word size=1u<<m;
		for(word k=1;k<m;++k)
			memset(ecx[k],0,4u<<m);
		FOR(size) ecx[popcnt[i]][i]=eax[size|i];
		for(word k=1;k<m;++k)
			fftfor(size) _or(ecx[k]);
		for(int k=m-1;k>0;--k){
			FOR(size){
				ull get=0;
				for(int j=1;j<k;++j)
					get+=1ull*ecx[j][i]*edx[k-j][i]%mod;
				ecx[k][i]=(get+1ull*ecx[k][i]*edx[0][0]+1ull*ecx[0][0]*edx[k][i])%mod;
			}
			fftfor(size) or_(ecx[k]);
		}
		ull get=0;
		FOR(1u<<m) get+=1ull*eax[1u<<m|i]*ebx[((1u<<m)-1)^i]%mod;
		ecx[m][(1u<<m)-1]=get%mod;
		FOR(size) in[size|i]=ecx[popcnt[i]][i];
	}
}
word *efx[mx+1];
int main(){//计算多项式复合形式幂级数
	word n;
	cin>>n;
	FOR(1u<<n) cin>>eax[i];
	FOR(n+1) cin>>in[i];
	efx[0]=ebx;
	for(word i=1;i<=n;++i)
		efx[i]=efx[i-1]+(1u<<(n-i));
	for(word k=0;k<=n;++k){
		for(int i=n;i>=0;--i)
			efx[k][0]=(1ull*efx[k][0]*eax[0]+in[i])%mod;
		for(word i=0;i<=n;++i)
			in[i]=(1ull+i)*in[i+1]%mod;
	}
	for(word m=0;m<n;++m){
		for(word k=0;k<=m;++k)
			memset(ecx[k],0,4u<<m);
		const word size=1u<<m;
		FOR(size) ecx[popcnt[i]][i]=eax[size|i];
		for(word k=0;k<=m;++k)
			fftfor(size) _or(ecx[k]);
		for(word k=n-m;k;){
			for(word i=0;i<=m;++i)
				memset(edx[i],0,4u<<m);
			FOR(size) edx[popcnt[i]][i]=efx[k][i];
			for(word j=0;j<=m;++j)
				fftfor(size) _or(edx[j]);
			for(int j=m;j>=0;--j){
				FOR(size){
					ull get=0;
					for(int l=0;l<=j;++l)
						get+=1ull*ecx[l][i]*edx[j-l][i]%mod;
					edx[j][i]=get%mod;
				}
				fftfor(size) or_(edx[j]);
			}
			--k;
			FOR(size) efx[k][size|i]=edx[popcnt[i]][i];
		}
	}
	FOR(1u<<n) printf("%u ",ebx[i]);
	return 0;
}