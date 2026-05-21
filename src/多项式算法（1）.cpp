/*
普通NTT、形式幂级数乘法逆元、ln、exp、复合和复合逆
*/
#include<stdio.h>
#include<string.h>
#define mx 20 //一维的最大长度
#define mx_ 19 //mx_=mx-1
#define _mx 20 //寄存器总长度
typedef unsigned int word;
word realid[1<<(mx+1)];
#define id(size,i) realid[(i)|(size)]
#define FOR(size) for(word i=0;i<(size);++i)
#define fftfor(size) \
for(word floor=1;floor<(size);floor<<=1) \
for(word head=0;head<(size);head+=floor<<1) \
for(word i=0;i<floor;++i)
const word mod=998244353,nimod=29;
inline word qpow(word a,word b){
    word ans=1;
    for(;b;b>>=1){
        if(b&1) ans=1ull*ans*a%mod;
        a=1ull*a*a%mod;
    }
    return ans;
}
word root[1<<mx],inv[1<<mx],ni[nimod];
struct READ{
    char c;
    inline READ(){
        c=getchar();
        ni[1]=1,ni[2]=qpow(2,mod-2);
        for(word floor=1,i=2;floor<=mx;++floor){
            ni[(1u<<floor)%nimod]=1ull*ni[(1u<<(floor-1))%nimod]*ni[2]%mod;
            for(;i<(1u<<(floor+1));++i)
                realid[i]=(i&1)<<(floor-1)|realid[i>>1];
        }
        const word num1=qpow(3,(mod-1)>>mx);
        const word num2=qpow(num1,mod-2);
        root[1<<mx_]=inv[1<<mx_]=1;
        for(word i=(1<<mx_)+1;i<(1<<mx);++i){
            root[i]=1ull*num1*root[i-1]%mod;
            inv[i]=1ull*num2*inv[i-1]%mod;
        }
        for(word i=(1u<<mx_)-1;i;--i)
            root[i]=root[i<<1],inv[i]=inv[i<<1];
    }
    template<typename type>
    inline READ& operator >>(type& num){
        while('0'>c||c>'9') c=getchar();
        for(num=0;'0'<=c&&c<='9';c=getchar())
            num=num*10+(c-'0');
        return *this;
    }
}cin;
#define ntt(num,root)( \
num1=num[head|i],num2=num[head|i|floor], \
num1+=(num2=1ull*num2*root[i|floor]%mod), \
num[head|i]=num1>=mod? num1-mod:num1, \
num1-=num2,num1+=mod-num2, \
num[head|i|floor]=num1>=mod? num1-mod:num1)
#define ntt2(num,root)( \
num1=num[(head|i)*m|k],num2=num[(head|i|floor)*m|k], \
num1+=(num2=1ull*num2*root[i|floor]%mod), \
num[(head|i)*m|k]=num1>=mod? num1-mod:num1, \
num1-=num2,num1+=mod-num2, \
num[(head|i|floor)*m|k]=num1>=mod? num1-mod:num1)
namespace FFT{
    struct fftreg{
        word ecx[1<<_mx];
        //size 写到前面 截半（可以用 end 控制末端）
        //size 写到后面 不截半
        template<typename type>
        inline void operator()(const word size,const type& f){//一维卷积
            FOR(size>>1){
                ecx[id(size,i)]=f[i];
                ecx[id(size,size>>1|i)]=0;
            }
            word num1,num2;
            fftfor(size) ntt(ecx,root);
        }
        template<typename type>
        inline void operator()(const word n,const word m,const type& f){//二维卷积（双截半）
            memset(ecx,0,(n*m)<<2);
            for(word i=0;i<=(n>>1);++i)
                for(word j=0;j<(m>>1);++j)
                    ecx[id(n,i)*m|id(m,j)]=f[i*(m>>1)|j];
            for(word k=0;k<n;++k){
                word num1,num2,* const num=ecx+m*k;
                fftfor(m) ntt(num,root);
            }
            fftfor(n) for(word k=0;k<m;++k){
                word num1,num2;
                ntt2(ecx,root);
            }
        }
        template<typename type>
        inline void operator()(const type& f,const word n,const word m){//二维卷积（单截半）
            memset(ecx,0,(n*m)<<2);
            for(word i=0;i<n;++i)
                for(word j=0;j<(m>>1);++j)
                    ecx[id(n,i)*m|id(m,j)]=f[i*(m>>1)|j];
            for(word k=0;k<n;++k){
                word num1,num2,* const num=ecx+m*k;
                fftfor(m) ntt(num,root);
            }
            fftfor(n) for(word k=0;k<m;++k){
                word num1,num2;
                ntt2(ecx,root);
            }
        }
    };
    inline void conv(const word size,const fftreg& f,
        const fftreg& g,word* const f_times_g){
        FOR(size) f_times_g[id(size,i)]=1ull*f.ecx[i]*g.ecx[i]%mod;
        word num1,num2;
        fftfor(size) ntt(f_times_g,inv);
        num1=ni[size%nimod];
        FOR(size) f_times_g[i]=1ull*num1*f_times_g[i]%mod;
    }
    inline void conv(const word n,const word m,
        const fftreg& f,const fftreg& g,word* const f_times_g){
        for(word i=0;i<n;++i)
            for(word j=0;j<m;++j)
                f_times_g[id(n,i)*m|id(m,j)]=1ull*f.ecx[i*m|j]*g.ecx[i*m|j]%mod;
        for(word k=0;k<n;++k){
            word num1,num2,* const num=f_times_g+m*k;
            fftfor(m) ntt(num,inv);
        }
        fftfor(n) for(word k=0;k<m;++k){
            word num1,num2;
            ntt2(f_times_g,inv);
        }
        const word num=1ull*ni[n%nimod]*ni[m%nimod]%mod;
        FOR(n*m) f_times_g[i]=1ull*num*f_times_g[i]%mod;
    }
}
using FFT::fftreg;
using FFT::conv;
word in[1<<_mx],eax[1<<_mx],ebx[1<<_mx],eex[1<<_mx];
fftreg ecx,edx;
#define newton(size_) \
word size=2; \
while(size<<=1,(size>>2)<(size_))
inline void _1(const word size_){//ebx<-1/eax
    ebx[0]=qpow(eax[0],mod-2);
    newton(size_){
        ecx(size,eax),edx(size,ebx);
        conv(size,ecx,edx,ebx);
        FOR(size) ebx[i]=(mod-ebx[i])%mod;
        ebx[0]=(2+ebx[0])%mod;
        ecx(size,ebx);
        conv(size,ecx,edx,ebx);
    }
}
word fact[1u<<mx_],rev[1u<<mx_];
inline void ln(const word size){//ebx<-ln(eax)
    _1(size),ecx(size<<1,ebx);
    FOR(size) ebx[i]=(1ull+i)*eax[i+1]%mod;
    edx(size<<1,ebx),conv(size<<1,ecx,edx,ebx);
    for(word i=size-1;i;--i)
        ebx[i]=1ull*rev[i]*fact[i-1]%mod*ebx[i-1]%mod;
    ebx[0]=0;
}
inline void exp_(const word size_){//eax<-exp(in) (ebx 不确定)
    eax[0]=1;
    newton(size_){
        ln(size>>1);
        FOR(size>>1) ebx[i]=(in[i]+mod-ebx[i])%mod;
        ebx[0]=(ebx[0]+1)%mod;
        ecx(size,eax),edx(size,ebx);
        conv(size,ecx,edx,eax);
    }
}
inline void bostan_mori(word m){
    //in 初始为 1*m,eax 初始为 2*m，求解 ebx<-[y^(m-1)]in/eax (mod x^m)
    word n=1;
    for(;m!=1;n<<=1,m>>=1){
        for(word i=0;i<=n;++i)
            for(word j=0;j<m;++j)
                ebx[i*m|j]=j&1? (mod-eax[i*m|j])%mod:eax[i*m|j];
        ecx(n<<1,m<<1,in),edx(n<<1,m<<1,ebx);
        conv(n<<1,m<<1,ecx,edx,eex);
        for(word i=0;i<(n<<1);++i)
            for(word j=0;j<(m>>1);++j)
                in[i*(m>>1)|j]=eex[i*(m<<1)|(j<<1|1)];
        memset(in+(n<<1)*(m>>1),0,m<<1);
        ecx(n<<1,m<<1,eax),conv(n<<1,m<<1,ecx,edx,eex);
        ecx(m<<1,eax+n*m),edx(m<<1,ebx+n*m);
        conv(m<<1,ecx,edx,ebx);
        for(word i=0;i<(n<<1);++i)
            for(word j=0;j<(m>>1);++j)
                eax[i*(m>>1)|j]=eex[i*(m<<1)|(j<<1)];
        for(word j=0;j<(m>>1);++j){
            eax[(n<<1)*(m>>1)|j]=ebx[j<<1];
            (eax[j]+=mod-ebx[j<<1])%=mod;
        }
    }
    _1(n);
    ecx(n<<1,in),edx(n<<1,ebx);
    conv(n<<1,ecx,edx,ebx);
}
inline void comp_inv(const word size){
    //计算 eax 的复合逆（仍放在原 eax），in 与 ebx 均不确定
    const word a1_=qpow(eax[1],mod-2);
    for(word i=0,num=mod-1;i<size;++i){
        eax[size|i]=1ull*num*eax[i]%mod;
        eax[i]=0,num=1ull*a1_*num%mod;
    }
    memset(in,0,size<<2);
    in[0]=eax[0]=1;
    bostan_mori(size);
    for(word k=1;k<size;++k)
        eax[size-1-k]=1ull*(size-1)*rev[k]%mod*fact[k-1]%mod*ebx[k]%mod;
    ln(size);
    const word num=qpow(mod-(size-1),mod-2);
    FOR(size) in[i]=1ull*num*ebx[i]%mod;
    exp_(size);
    for(word i=size;--i;) eax[i]=1ull*a1_*eax[i-1]%mod;
    eax[0]=0;
}
inline void bostan_mori_T(const word m,const word n=1){
    //in 初始为 m*1,eax 初始为 2*m，求解 ebx<-[x^(m-1)]in_R/eax (mod y^m)
    if(m==1){
        _1(n);
        ecx(n<<1,in),edx(n<<1,ebx);
        conv(n<<1,ecx,edx,ebx);
        for(word j=0;j<n;++j) in[j]=ebx[n-1-j];
        return;
    }
    fftreg& efx=*((fftreg*)(new word[(n<<1)*(m<<1)]));
    for(word i=0;i<=n;++i)
        for(word j=0;j<m;++j)
            ebx[i*m|j]=j&1? (mod-eax[i*m|j])%mod:eax[i*m|j];
    ecx(n<<1,m<<1,eax),efx(n<<1,m<<1,ebx);
    conv(n<<1,m<<1,ecx,efx,eex);
    for(word i=0;i<(n<<1);++i)
        for(word j=0;j<(m>>1);++j)
            eax[i*(m>>1)|j]=eex[i*(m<<1)|(j<<1)];
    ecx(m<<1,eax+n*m),edx(m<<1,ebx+n*m);
    conv(m<<1,ecx,edx,ebx);
    for(word j=0;j<(m>>1);++j){
        eax[(n<<1)*(m>>1)|j]=ebx[j<<1];
        (eax[j]+=mod-ebx[j<<1])%=mod;
    }
    bostan_mori_T(m>>1,n<<1);
    for(word i=0;i<(n<<1);++i)
        for(word j=0;j<(m>>1);++j){
            eax[((n<<1)-1-i)*m|(((m>>1)-1-j)<<1)]=in[i*(m>>1)|j];
            eax[((n<<1)-1-i)*m|(((m>>1)-1-j)<<1|1)]=0;
        }
    ecx(eax,n<<1,m<<1);
    conv(n<<1,m<<1,ecx,efx,eex);
    delete (word*)&efx;
    for(word i=0;i<n;++i)
        for(word j=0;j<m;++j)
            in[i*m|j]=eex[((n<<1)-1-i)*(m<<1)|(m-1-j)];
}
inline void comp(const word size){//eax<-eax\circ ebx (in,ebx 不确定)
    FOR(size) in[size-1-i]=eax[i],eax[size|i]=(mod-ebx[i])%mod,eax[i]=0;
    eax[0]=1;
    bostan_mori_T(size);
    FOR(size) eax[i]=in[size-1-i];
}