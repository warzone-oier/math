#include<stdio.h>
#include<string.h>
#include<time.h>
#include<vector>
typedef unsigned long long ull;
typedef unsigned int word;
typedef unsigned char byte;
const word siz=1<<22;
word block;
struct BIT{
    ull sum[siz];
#define lowbit(x) ((x)&-(x))
    inline void plus(int id,const ull num){
        for(;id<block;id+=lowbit(id)) sum[id]+=num;
    }
    inline ull operator()(int id)const{
        ull ans=0;
        for(;id;id&=~lowbit(id)) ans+=sum[id];
        return ans;
    }
    inline void init(){
        for(int i=1;i<block;++i) if(i+lowbit(i)<block)
            sum[i+lowbit(i)]+=sum[i];
    }
}tree;
word prime[siz],ptop,lpf[siz],bef[siz];
byte lpfc[siz];
std::vector<word> pos[siz];
inline void dfsp(word num,word step,word before,word cnt=1){
    lpf[num]=step;
    bef[num]=before,lpfc[num]=cnt;
    for(word i=1;i<step&&1ull*num*prime[i]<siz;++i)
        dfsp(num*prime[i],i,num);
    if(1ull*num*prime[step]<siz)
        dfsp(num*prime[step],step,before,cnt+1);
}
struct READ{
    char c;
    inline READ(){//线性筛部分
        prime[0]=1;
        for(word i=2;i<siz;++i){
            if(lpf[i]==0) prime[++ptop]=i,dfsp(i,ptop,1);
            pos[lpf[i]].push_back(i);
        }
        c=getchar();
    }
    template<typename type>
    inline READ& operator >>(type& num){
        while('0'>c||c>'9') c=getchar();
        for(num=0;'0'<=c&&c<='9';c=getchar())
            num=num*10+(c-'0');
        return *this;
    }
}cin;
ull n,val[siz];
struct min25{
    ull small[1<<20],large[1<<20];
    inline ull& operator[](ull id){
        if(id<=n/id) return small[id];
        return large[n/id];
    }
    inline ull operator[](ull id)const{
        if(id<=n/id) return small[id];
        return large[n/id];
    }
    template<typename type1,typename type2>
    inline void getprime(const type1& f,const type2& pre){
        //用已知的前缀和求出质数处的值
        //f 点值，pre 前缀和
        for(word i=2;1ull*i*i<=n;++i) small[i]=pre(i)-pre(1);
        for(word i=1;1ull*i*i<n;++i) large[i]=pre(n/i)-pre(1);
        for(word i=2;i<block;++i)
            tree.sum[i]=f(i);
        tree.sum[1]=0,tree.init();
        word m=1;
        for(;1ull*prime[m]*prime[m]<=n;++m){// m->m+1
            for(const auto k:pos[m]) if(k<block)
                tree.plus(k,-f(k));
            else break;
            auto Sm_1=[&](ull n)->ull{
                if(n>=1ull*prime[m]*prime[m])
                    return n<block? tree(n):(*this)[n];
                return (*this)[n]-small[prime[m]];
                };
            //实际数组在 <p_m^2 时存储 S_prime（包括 <siz 的）,>=p_m^2 时存储 S_m/S_{m+1}（不包括 <siz 的）
            ull i=1;
            while(i<n/i&&(n/i)>=1ull*prime[m]*prime[m]&&n/i>=block) ++i;
            while(--i){
                ull get=large[i]-f(prime[m]);
                for(ull prod=prime[m];prime[m]<=(n/i)/prod;){
                    get-=f(prod)*Sm_1((n/i)/prod);
                    prod*=prime[m],get-=f(prod);
                }
                large[i]=get;
            }
            for(ull i=1ull*prime[m]*prime[m];
                i<1ull*prime[m+1]*prime[m+1]&&i<=n/i;++i)
                small[i]=tree(i)+small[prime[m]];
            for(i=1;i<n/i&&(n/i)>=1ull*prime[m]*prime[m];) ++i;
            while(--i,i&&(n/i)<1ull*prime[m+1]*prime[m+1])
                large[i]=(n/i<block? tree(n/i):large[i])+small[prime[m]];
        }
    }
    template<typename type>
    inline void operator()(const type& f,const min25& Sp){
        //用点值和质数处的和求前缀和（S' 而非 S）
        //f(prime[m]^c,m,c) prime[m]^c 处的点值
        word m=1;
        while(1ull*prime[m]*prime[m]<=n) ++m;
        for(word i=1;1ull*i*i<=n;++i)
            small[i]=large[i]=0;
        tree.sum[1]=0;
        for(word i=2;i<block;++i)
            tree.sum[i]=lpf[i]>=m? f(i):0;
        tree.init();
        auto Sm_1=[&](ull n)->ull{
            if(n<prime[m+1]) return 0;
            else if(n<block) return tree(n);
            return (*this)[n]+Sp[n]-Sp.small[prime[m]];
            };
        word cnt=1;
        while(--m){
            for(word i=1;i<n/i&&1ull*prime[m]*prime[m]<=n/i&&n/i>=block;++i){
                ull get=large[i];
                for(ull prod=prime[m],c=1;prime[m]<=(n/i)/prod;){
                    get+=f(prod,m,c)*Sm_1((n/i)/prod);
                    prod*=prime[m],++c,get+=f(prod,m,c);
                }
                large[i]=get;
            }
            for(const auto k:pos[m]) if(k<block)
                tree.plus(k,f(k));
            else break;
        }
        //for(word i=1;i<n/i;++i) //需要多点值则填写此项
        // if(n/i<block) large[i]=tree(n/i)-Sp[n/i]+Sp.small[prime[0]];
        //for(word i=1;i<=n/i;++i) //需要多点值则填写此项
        // small[i]=tree(i)-Sp[i]+Sp.small[prime[0]];
    }
}f,Sp;