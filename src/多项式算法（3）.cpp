/*
多项式多点求值与快速插值
*/
#include<stdio.h>
#include<string.h>
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int word;
typedef unsigned char byte;
const word mod=998244353,nimod=29;
constexpr ull pow(word a,word b){
	word ans=1;
	for(;b;b>>=1){
		if(b&1) ans=1ull*ans*a%mod;
		a=1ull*a*a%mod;
	}
	return ans;
}
#define mx 19
#define mx_ 18
word root[1<<mx],inv[1<<mx],realid[1<<(mx+1)];
word ni[nimod];
struct READ{
	char c;
	inline READ(){//NTT 预处理
		const ull num1=pow(3,(mod-1)>>mx);
		const ull num2=pow(num1,mod-2);
		root[1<<mx_]=inv[1<<mx_]=ni[1]=1;
		ni[2]=pow(2,mod-2),realid[1]=0;
		for(word floor=1,i=2;floor<=mx;++floor){
			ni[(1u<<floor)%nimod]=1ull*ni[(1u<<(floor-1))%nimod]*ni[2]%mod;
			for(;i<1u<<(floor+1);++i)
				realid[i]=(i&1)<<(floor-1)|realid[i>>1];
		}
		for(word i=(1<<mx_)+1;i<1<<mx;++i){
			root[i]=num1*root[i-1]%mod;
			inv[i]=num2*inv[i-1]%mod;
		}
		for(word i=(1<<mx_)-1;i;--i)
			root[i]=root[i<<1],inv[i]=inv[i<<1];
		c=getchar();}
	template<typename type>
	inline READ& operator >>(type& num){//读入
		while('0'>c||c>'9') c=getchar();
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
}cin;
#define nttfor(size)	\
	for(word floor=1;floor<(size);floor<<=1)	\
		for(word head=0;head<(size);head+=floor<<1)	\
			for(word i=0;i<floor;++i)//FFT 循环
#define ntt(num,root)	[&](){							\
	word num1=num[head|i],num2=num[head|i|floor];		\
    num1+=(num2=1ull*num2*root[i|floor]%mod);   		\
	num[head|i]=num1>=mod? num1-mod:num1;	    		\
	num1-=num2,num1+=mod-num2;                  		\
	num[head|i|floor]=num1>=mod? num1-mod:num1;}()
#define id(size,i) realid[(i)|(size)]//二进制翻转的下标
#define FOR(size) for(word i=0;i<(size);++i)
word y[1<<mx],eax[1<<mx],ebx[1<<mx],ecx[1<<mx],edx[1<<mx];
struct poly{
	word *num,last;
	inline poly(){}
	inline poly(word *NUM,word end){
		num=NUM,last=end;}
};
//输入结果多项式的大小及表达式，将其放入 ecx 与edx 中
#define inconv(size,f,g) FOR((size)>>1){	\
		word head=id(size,i);				\
		ecx[head]=(f),edx[head]=(g);		\
		head=id(size,size>>1|i);			\
		ecx[head]=edx[head]=0;				\
	}
//对 ecx与 edx 作 ntt 并输出结果
#define outconv(size,f_times_g)								\
	nttfor(size) ntt(ecx,root),ntt(edx,root);				\
	FOR(size) f_times_g[id(size,i)]=1ull*ecx[i]*edx[i]%mod;	\
	nttfor(size) ntt(f_times_g,inv);
word n;
template<word size>
struct tree{
	tree<(size>>1)> l,r;
	word num[size<<1];
	inline word operator[](const word id)const{
		if(id<=size) return num[size-id];
		return 0;
	}
	inline tree(const word id):l(id<<1),r(id<<1|1){
		inconv(size,l.num[i],r.num[i]);
		ecx[1]=l.num[size>>1];
		edx[1]=r.num[size>>1];
		outconv(size,num);
		word num1=ni[size%nimod],num2;
		FOR(size) num[i]=1ull*num1*num[i]%mod;
		num1=l.num[size>>1];
		num2=r.num[size>>1];
		num[size]=num1=1ull*num1*num2%mod;
		num[0]=(num[0]+mod-num1)%mod;
		memcpy(l.num,ecx,sizeof(l.num));
		memcpy(r.num,edx,sizeof(r.num));
	}
	#define rconv(r,f)	\
		FOR(size) f[id(size,i)]=1ull*ecx[i]*r.num[i]%mod;
	inline void operator ()(const word id,word *const f){
		if(id*size>=n) return void(memset(f,0,size<<2));
		FOR(size) ecx[id(size,i)]=f[i];
		nttfor(size) ntt(ecx,root);
		rconv(r,f);
		rconv(l,ebx);
		nttfor(size) ntt(f,inv),ntt(ebx,inv);
		word num1=ni[size%nimod],num2;
		FOR(size>>1){
			f[i]=1ull*num1*f[size>>1|i]%mod;
			f[size>>1|i]=1ull*num1*ebx[size>>1|i]%mod;
		}
		l(id<<1,f),r(id<<1|1,f+(size>>1));
		inconv(size,f[i],f[size>>1|i]);
		nttfor(size) ntt(ecx,root),ntt(edx,root);
		FOR(size){
			const word head=id(size,i);
			ebx[head]=1ull*ecx[i]*r.num[i]%mod;
			f[head]=1ull*edx[i]*l.num[i]%mod;
		}
		nttfor(size) ntt(f,inv),ntt(ebx,inv);
		if((id+1)*size<=n) FOR(size){
			if((f[i]+=ebx[i])>=mod) f[i]-=mod;
		}else{
			num2=((id+1)*size)-n;
			if(num2>(size>>1)) num2=(size>>1);
			for(word i=0;num2+i<size;++i)
				if((f[i]+=ebx[num2+i])>=mod) f[i]-=mod;
		}
		num1=ni[size%nimod];
		FOR(size) f[i]=1ull*num1*f[i]%mod;
	}
};
template<>
struct tree<1>{
	word num[2];
	inline tree(const word id){
		num[1]=1,num[0]=mod-ebx[id];
		if(num[0]>=mod) num[0]-=mod;
	}
	inline void operator()(const word id,word *const f){
		if(id>=n) f[0]=0;
		else f[0]=pow(f[0],mod-2)*y[id]%mod;
	}
	inline word operator[](const word id)const{
		if(id<=1) return num[1-id];
		return 0;
	}
};
template<word size>
inline void getans(){
	if(size<=n)
		return getans<(size<<1)>();
	tree<size> *t;
	t=new tree<size>(0);//拿出在 ebx 内的点值，维护乘积
	memset(ebx,0,sizeof(ebx));
	ebx[0]=pow((*t)[0],mod-2);//将 ebx 换算为 g_{0,n} 的逆元
	for(word size_=2;size_<=(size<<1);){
		size_<<=1;
		inconv(size_,ebx[i],(*t)[i]);
		outconv(size_,ebx);
		word num1=mod-ni[size_%nimod];
		FOR(size_>>1){
			edx[id(size_,i)]=1ull*num1*ebx[i]%mod;
			edx[id(size_,size_>>1|i)]=0;
		}
		edx[0]=(2ll+edx[0])%mod;
		nttfor(size_) ntt(edx,root);
		FOR(size_) ebx[id(size_,i)]=1ull*ecx[i]*edx[i]%mod;
		nttfor(size_) ntt(ebx,inv);
		memset(ebx+(size_>>1),0,(size_>>1)<<2);
		num1=ni[size_%nimod];
		FOR(size_>>1) ebx[i]=1ull*num1*ebx[i]%mod;
	}
	do{//计算 f*Tg,放入 eax
		inconv(size<<1,(1ull+i)*t->num[size-n+i+1]%mod,ebx[size-i]);
		edx[1]=ebx[0];
		outconv(size<<1,ebx);
		word num1=ni[(size<<1)%nimod];
		FOR(size) eax[i]=1ull*num1*ebx[i|size]%mod;
	}while(0);
	(*t)(0,eax);
	for(word i=0;i<n;++i)
		printf("%u ",eax[i]);
	delete t;
}
template<>
inline void getans<(1u<<mx_)>(){}
int main(){
	cin>>n;
	for(word i=0;i<n;++i)
		cin>>ebx[i]>>y[i];//多项式的系数
	getans<1>();
	return 0;
}
