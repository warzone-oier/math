/*
任意模数NTT、多项式欧几里得
*/
#include<stdio.h>
#include<string.h>
#include<initializer_list>
#include<vector>
#include<cmath>
using std::sin;
using std::cos;
using std::acos;
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int word;
typedef unsigned short hword;
typedef unsigned char byte;
#define mx 18
#define mx_ 17
word realid[1<<(mx+1)];
#define id(size,i) realid[(i)|(size)]
#define FOR(size) for(word i=0;i<(size);++i)
#define fftfor(size) \
for(word floor=1;floor<(size);floor<<=1) \
for(word head=0;head<(size);head+=floor<<1) \
for(word i=0;i<floor;++i)
const word mod=1e9+7;
inline word qpow(word a,word b){
    word ans=1;
    for(;b;b>>=1){
        if(b&1) ans=1ull*ans*a%mod;
        a=1ull*a*a%mod;
    }
    return ans;
}
struct complex{
    db real,imag;
    inline complex(){}
    inline complex(const complex& p){ real=p.real,imag=p.imag; }
    inline complex(db a,db b=0){ real=a,imag=b; }
    inline complex operator*(const complex& p)const{
        return complex(real*p.real-imag*p.imag,real*p.imag+imag*p.real);
    }
    inline complex operator+(const complex& p)const{
        return complex(real+p.real,imag+p.imag);
    }
    inline complex operator-(const complex& p)const{
        return complex(real-p.real,imag-p.imag);
    }
    inline void operator+=(const complex& p){
        real+=p.real,imag+=p.imag;
    }
    inline void operator-=(const complex& p){
        real-=p.real,imag-=p.imag;
    }
}root[1<<mx],inv[1<<mx];
#define PI acos(-1.0)/(1<<mx_)
struct READ{
    char c;
    inline READ(){
        c=getchar();
        complex num;
        root[1u<<mx_].real=inv[1u<<mx_].real=1;
        for(word floor=1,i=2;floor<=mx;++floor)
            for(;i<(1u<<(floor+1));++i)
                realid[i]=(i&1)<<(floor-1)|realid[i>>1];
        for(word i=1;i<1u<<mx_;++i){
            root[1u<<mx_|i]=complex(cos(i*PI),sin(i*PI));
            inv[1u<<mx_|i]=complex(root[1u<<mx_|i].real,-root[1u<<mx_|i].imag);
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
#define fft(num,root) [&](){ \
complex num1=num[head|i|floor]*root[i|floor]; \
num[head|i|floor]=num[head|i]; \
num[head|i]+=num1; \
num[head|i|floor]-=num1;}()
namespace FFT{
    complex eax[1<<mx],ebx[1<<mx];
#define cover(eax,ecx,edx,size)( \
num1=eax[i]+eax[((size)-i)&~(size)], \
num2=eax[i]-eax[((size)-i)&~(size)], \
ecx[i]=complex(num1.real/2,num2.imag/2), \
edx[i]=complex(num1.imag/2,num2.real/-2))
    struct fftreg{
        complex ecx[1<<mx],edx[1<<mx];
        inline void operator()(const word size,const word* const f,const word end=0){
            complex eax[1<<mx];
            FOR(size>>1){
                eax[id(size,i)]=complex(f[i]>>15,f[i]&0x7fff);
                eax[id(size,size>>1|i)]=0;
            }
            eax[id(size,size>>1)]=complex(end>>15,end&0x7fff);
            fftfor(size) fft(eax,root);
            complex num1,num2;
            FOR(size) cover(eax,ecx,edx,size);
        }
        inline void operator()(const word* const f,const word size){
            complex eax[1<<mx];
            FOR(size) eax[id(size,i)]=complex(f[i]>>15,f[i]&0x7fff);
            fftfor(size) fft(eax,root);
            complex num1,num2;
            FOR(size) cover(eax,ecx,edx,size);
        }
    };
    inline void conv(const word size,const fftreg& f,
        const fftreg& g,word* const f_times_g){
        const complex num1(0,1);
        FOR(size){
            eax[id(size,i)]=f.ecx[i]*g.ecx[i]+f.edx[i]*g.edx[i]*num1;
            ebx[id(size,i)]=f.ecx[i]*g.edx[i]+f.edx[i]*g.ecx[i]*num1;
        }
        fftfor(size) fft(eax,inv),fft(ebx,inv);
        const word head=(1u<<15)%mod;
        FOR(size){
            ull out=(ull)(eax[i].real/size+0.5)%mod;
            out=(ull)(ebx[i].real/size+0.5)%mod+out%mod*head%mod;
            out=(ull)(ebx[i].imag/size+0.5)%mod+out%mod;
            out=(ull)(eax[i].imag/size+0.5)%mod+out%mod*head%mod;
            f_times_g[i]=out%mod;
        }
    }
}
using FFT::fftreg;
using FFT::conv;
word in[1<<mx],eax[1<<mx],ebx[1<<mx];
fftreg ecx,edx;
#define newton(size_) \
word size=2; \
while(size<<=1,(size>>2)<(size_))
inline void _1(const word size_){
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
#define lowbit(x) ((x)&-(x))
struct poly:public std::vector<word>{
    inline poly(){}
    inline poly(const poly&)=default;
    inline poly(const word size):
        std::vector<word>(size){};
    inline poly(std::initializer_list<word> list):
        std::vector<word>(list){}
    inline poly(const poly& f,const poly& g):
        std::vector<word>(f.size()&&g.size()? f.size()+g.size()-1:0){//乘法
        if(f.size()==0) return;
        if(g.size()==0) return;
        if(f.size()==1){
            FOR(g.size()) at(i)=1ull*f[0]*g[i]%mod;
            return;
        }
        if(g.size()==1){
            FOR(f.size()) at(i)=1ull*f[i]*g[0]%mod;
            return;
        }
        int size=f.size()+g.size()-1;
        while(size!=lowbit(size)) size+=lowbit(size);
        memset(eax,0,size<<2);
        memset(ebx,0,size<<2);
        FOR(f.size()) eax[i]=f[i];
        FOR(g.size()) ebx[i]=g[i];
        ecx(eax,size),edx(ebx,size);
        conv(size,ecx,edx,ebx);
        size=f.size()+g.size()-1;
        FOR(size) at(i)=ebx[i];
    }
    inline void operator+=(const poly& f){
        for(word i=0;i<size()&&i<f.size();++i)
            (at(i)+=f[i])%=mod;
        while(size()<f.size()) push_back(f[size()]);
        while(size()&&at(size()-1)==0) pop_back();
    }
    inline void operator-=(const poly& f){
        for(word i=0;i<size()&&i<f.size();++i)
            (at(i)+=mod-f[i])%=mod;
        while(size()<f.size()) push_back((mod-f[size()])%mod);
        while(size()&&at(size()-1)==0) pop_back();
    }
};
struct matrix{
    poly a,b,c,d;
    inline matrix(){}
    inline matrix(const matrix&)=default;
    inline matrix(const poly& A,const poly& B,const poly& C,const poly& D):
        a(A),b(B),c(C),d(D){};
    inline void add(const poly& p){
        a.swap(c),b.swap(d);
        c-=poly(p,a),d-=poly(p,b);
    }
    inline matrix(const matrix& p,const matrix& q):
        a(p.a,q.a),b(p.a,q.b),c(p.c,q.a),d(p.c,q.b){//矩阵乘法
        a+=poly(p.b,q.c),b+=poly(p.b,q.d);
        c+=poly(p.d,q.c),d+=poly(p.d,q.d);
    }
}const I(poly({1}),poly(),poly(),poly({1}));
struct vector{
    poly f,g;
    inline vector(){}
    inline vector(const vector&)=default;
    inline vector(const poly& F,const poly& G):f(F),g(G){}
    inline vector(const matrix& M,const vector& p):
        f(M.a,p.f),g(M.c,p.f){//矩阵乘向量
        f+=poly(M.b,p.g),g+=poly(M.d,p.g);
    }
    poly div(){//(f,g)<-(g,f mod g), return f div g
        if(g.size()==0) perror("div 0");
        poly ans(f.size()>=g.size()? f.size()-g.size()+1:0);
        g.swap(f);
        if(g.size()<f.size()) return ans;
        int size=ans.size();
        while(size!=lowbit(size)) size+=lowbit(size);
        memset(eax,0,size<<2);
        for(word i=0;i<f.size()&&i<size;++i)
            eax[i]=f[f.size()-1-i];
        _1(size);
        memset(eax,0,size<<3);
        for(word i=0;i<g.size()&&i<size;++i)
            eax[i]=g[g.size()-1-i];
        ecx(size<<1,eax),edx(size<<1,ebx);
        conv(size<<1,ecx,edx,ebx);
        FOR(ans.size()) ans[i]=ebx[ans.size()-1-i];
        return g-=poly(f,ans),ans;
    }
    matrix hgcd()const{
        const word m=f.size()>>1;
        if(g.size()<=m) return I;
        vector p;
        for(word i=m;i<f.size();++i) p.f.push_back(f[i]);
        for(word i=m;i<g.size();++i) p.g.push_back(g[i]);
        matrix R=p.hgcd();
        p=vector(R,*this);
        if(p.g.size()<=m) return R;
        poly h=p.div();
        R.add(h);
        if(p.g.size()<=m) return R;
        const word k=(m<<1)-p.f.size()+1;
        h.clear(),h.swap(p.f);
        for(word i=k;i<h.size();++i) p.f.push_back(h[i]);
        h.clear(),h.swap(p.g);
        for(word i=k;i<h.size();++i) p.g.push_back(h[i]);
        return matrix(p.hgcd(),R);
    }
    matrix cogcd(){//(f,g)<-(gcd(f,g),0),return exgcd matrix M
        matrix ans=I;
        while(1){
            matrix M=hgcd();
            *this=vector(M,*this),ans=matrix(M,ans);
            if(g.size()==0) return ans;
            ans.add(div());
            if(g.size()==0) return ans;
        }
    }
};