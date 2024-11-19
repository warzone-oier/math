## 公平博弈

若一场博弈的整个过程中，左右双方的决策集合总是相同的，则称该博弈为 **公平博弈**。  
具体地，$g=\{L|R\}$ 为公平博弈当且仅当 $L=R$，且 $L$ 中的元素仍为公平博弈。  

例如，$0=\{\varnothing|\varnothing\},*=\{0|0\}$ 都是公平博弈。

由于公平博弈中左右双方没有区分，博弈的结果只有先手必胜和后手必胜两种，  
且公平博弈的反博弈一定是其本身，即对于任意公平博弈 $g$ 有

$$g=-g$$

此外，易得公平博弈的和与积均为公平博弈。  
且可归纳证明 $*$ 为公平博弈的乘法单位元，即对于任意公平博弈 $g=\{S|S\}$ 有

$$g*=\{S*+g0+S0|S*+g0+S0\}=\{S|S\}=g$$

> 求证：对于公平博弈 $g,h$，$gh||0$ 当且仅当 $g||0$ 且 $h||0$。  
> 证明*：考虑归纳，设该命题为 $P(g,h)$，$g=\{S_g|S_g\},h=\{S_h|S_h\}$，并定义
> $$H(g)=\{g\}\cup\bigcup_{s_g\in S_g}H(s_g)$$
> $\qquad\quad$ 假设对于任意的 $(g',h')\in H(g)\cup H(h)$ 且 $(g',h')\not=(g,h)$，$P(g',h')$ 成立，则  
> $\qquad\quad g||0$（即 $g$ 先手必胜）当且仅当存在 $s_g\in S_g$ 满足 $s_g\equiv 0$（即 $s_g$ 后手必胜），  
> $\qquad\quad h||0$（即 $h$ 先手必胜）当且仅当存在 $s_h\in S_h$ 满足 $s_h\equiv 0$（即 $s_h$ 后手必胜）。  
> $\qquad\quad$ 于是若 $g||0$ 且 $h||0$，则有
> $$s_gh+gs_h-(s_gs_h)\equiv 0+0-0=0$$
> $\qquad\quad$ 即，$s_gh+gs_h-(s_gs_h)$ 是先手必败的，故 $gh$ 是先手必胜的（即 $gh||0$）。  
> $\qquad\quad$ 若 $g\equiv 0$ 或 $h\equiv 0$，设 $g\equiv 0$，则对于任意的 $s_g\in S_g$，满足 $s_g||0$（即 $s_g$ 先手必胜），   
> $\qquad\quad$ 此时设 $s_g=\{S_{s_g}|S_{s_g}\}$，则必存在 $s_{s_g}\in S_{s_g}$ 满足 $s_{s_g}\equiv 0$（即 $s_{s_g}$ 后手必胜），此时
> $$\forall s_h\in S_h,s_{s_g}h+s_gs_h-(s_{s_g}s_h)-(s_gs_h)\equiv 0$$
> $\qquad\quad$ 即，$s_{s_g}h+s_gs_h-(s_{s_g}s_h)-(s_gs_h)$ 是后手必胜的。  
> $\qquad\quad$ 根据博弈乘法的定义，$s_{s_g}h+s_gs_h-(s_{s_g}s_h)$ 属于 $s_gh$ 的决策集合，  
> $\qquad\quad$ 故根据博弈加法的定义，$s_{s_g}h+s_gs_h-(s_{s_g}s_h)-(s_gs_h)$ 属于 $s_gh-(s_gs_h)$ 的决策集合，  
> $\qquad\quad$ 因此 $\forall s_h\in S_h$，$s_gh-(s_gs_h)$ 是先手必胜的（即 $s_gh-(s_gs_h)||0$）。于是
> $$\forall s_g\in S_g,s_h\in S_h,s_gh+gs_h-(s_gs_h)\equiv s_gh-(s_gs_h)||0$$
> $\qquad\quad$ 即，$s_gh+gs_h-(s_gs_h)$ 全是先手必胜的，故 $gh$ 是后手必胜的（即 $gh\equiv 0$）。  
> $\qquad\quad$ 综上，$gh||0$ 当且仅当 $g||0$ 且 $h||0$。

由以上定理，即可证明公平博弈满足乘法在 $\equiv$ 意义下的等量代换：

$$g_1\equiv g_2\Leftrightarrow g_1-g_2\equiv 0\Rightarrow (g_1-g_2)h\equiv 0\Leftrightarrow g_1h\equiv g_2h$$

且可证明，公平博弈满足乘法在 $\equiv$ 意义下的消去律：

$$
\begin{rcases}
	g_1h\equiv g_2h\Leftrightarrow(g_1-g_2)h\equiv 0\\
	h\not =0
\end{rcases}\Rightarrow g_1-g_2\equiv 0\Leftrightarrow g_1\equiv g_2
$$

### Nim 游戏

Nim 游戏是典型的公平博弈。

设有一列 $n$ 堆石子，双方轮流操作，每次一方选择其中一堆，取走其中任意个石子，但不能不取。  
取走最后一颗石子的人获胜，即面对“每一堆石子均被取完”局面的人落败。

> 求证：设 $n$ 堆石子所含的石子数分别为 $a_1,a_2,\cdots,a_n$，则 Nim 游戏后手必胜当且仅当
> $$a_1\oplus a_2\oplus \cdots\oplus a_n=0$$  
> $\qquad\quad$ 其中 $\oplus$ 为按位异或。  
> 证明：若 $a_1=a_2=\cdots=a_n=0$，显然 $a_1\oplus a_2\oplus \cdots\oplus a_n=0$，且先手必败，即后手必胜。否则，  
> $\qquad 1^\circ$ 若 $a_1\oplus a_2\oplus \cdots\oplus a_n=0$，设先手选择了第 $k$ 堆石子，取完之后第 $k$ 堆还剩 $a_k'$ 个石子，  
> $\qquad\quad$ 那必然有 $a'_k\not =a_k$，即 $a_k\oplus a_k'\not =0$。因此
> $$a_1\oplus a_2\oplus \cdots\oplus a_k'\oplus \cdots\oplus a_n=(a_1\oplus a_2\oplus \cdots\oplus a_k\oplus \cdots\oplus a_n)\oplus a_k\oplus a_k'$$
> $$=0\oplus a_k\oplus a_k'=a_k\oplus a_k'\not=0$$
> $\qquad\quad$ 即，不论先手如何决策，下一个局面必然为 $a_1\oplus a_2\oplus \cdots\oplus a_n\not=0$ 的局面，即先手必胜局面。   
> $\qquad 2^\circ$ 若 $a_1\oplus a_2\oplus \cdots\oplus a_n=s\not=0$，设 $s$ 的最高位为第 $m$ 位，  
> $\qquad\quad$ 那必然存在 $k\in\{1,2,\cdots,n\}$ 使得 $a_k$ 的第 $m$ 位非 $0$。此时
> $$a_k\oplus s<a_k$$
> $\qquad\quad$ 于是先手必然可以选择第 $k$ 堆石子，取走其中 $a_k-(a_k\oplus s)$ 个石子，  
> $\qquad\quad$ 从而使下一个局面为 $a_1\oplus a_2\oplus \cdots\oplus a_n=0$ 的局面，即后手必胜局面。  
> $\qquad$ 综上，Nim 游戏后手必胜当且仅当 $a_1\oplus a_2\oplus \cdots\oplus a_n=0$ 。

这样以来，我们就解决了 Nim 游戏的结果判定问题。

### Nimber

注意到，Nim 游戏实质上是只有若干个只有一堆石子的 Nim 游戏的和博弈。  
这意味着 Nim 游戏关于博弈的加法蕴含着简单而优美的性质。

具体地，我们称只有一堆 $n$ 个石子的 Nim 游戏为 **Nimber**，记为 $*_n$。即

$$*_n=\{\{*_0,*_1,\cdots,*_{n-1}\}|\{*_0,*_1,\cdots,*_{n-1}\}\}$$

显然有 $*_0=0,*_1=*$，且 $\forall n\in\N_+,*_n||0$。对于 Nimber 的和博弈，我们有

> **Sprague–Grundy 定理（SG 定理）**：$*_n+*_m\equiv *_{n\oplus m}$  
> 证明：对于有三堆石子，且三堆石子个数依次为 $n,m,n\oplus m$ 的 Nim 游戏，由于
> $$n\oplus  m\oplus (n\oplus m)=0$$
> $\qquad\quad$ 其一定是后手必胜的，即
> $$*_n+*_m+*_{n\oplus m}\equiv 0$$
> $\qquad\quad$ 因为公平博弈的反博弈为其本身，故
> $$*_n+*_m\equiv *_{n\oplus m}$$

### SG 函数

Nim 游戏的结论能否推广到一般的公平博弈中呢？  
对于 $S\subseteq\N$，定义 $\operatorname{mex} S$ 为 $S$ 中未出现的最小自然数，如

$$\operatorname{mex}\{0,1,3\}=2$$

对于有限公平博弈 $g=\{S|S\}$，定义 **SG 函数**

$$SG(g)=\operatorname{mex}\{SG(a)|a\in S\}$$

则

$$g\equiv *_{SG(g)}$$

> 证明：设 $SG(g)=n$，相当于证明 $g+*_n\equiv 0$，即 $g+*_n$ 是后手必胜的。  
> $\qquad$ 考虑归纳，设 $\forall a\in S,a\equiv *_{SG(a)}$。考虑 $g+*_n$ 中先手的所有决策，  
> $\qquad 1^\circ$ 若先手先操作 $*_n$，使得 $*_n$ 变为了 $*_m\ (m<n)$。根据 $\operatorname{mex}$ 的定义，  
> $\qquad\quad$ 必然存在 $a\in S$ 使得 $SG(a)=m$，即后手接下来可以通过操作 $g$ 使得 $g$ 变为 $a$，  
> $\qquad\quad$ 使得先手下一步要面对局面 $a+*_m$，因为 $a+*_m\equiv 0$，这是一个后手必胜的局面。  
> $\qquad 2^\circ$ 若先手先操作 $g$，使得 $g$ 变为 $a$，根据 $\operatorname{mex}$ 的定义，$SG(a)\not=n$，故根据 SG 定理有
> $$a+*_n\equiv *_{SG(a)}+*_n\equiv *_{SG(a)\oplus  n}||0$$
> $\qquad\quad$ 即，后手接下来要面对的局面 $a+*_n$ 是一个先手必胜的局面。  
> $\qquad$ 综上，不论先手如何操作，后手接下来必然面对一个先手必胜的局面，故 $g+*_n$ 是后手必胜的。

进一步地，易证明 $*_{SG(g)}$ 就是 $g$ 的最简形。  
这样一来，任意有限公平博弈均可化简为 Nimber，进而用 SG 定理解决和博弈问题。无限的公平博弈是类似的。

### 高维 Nim 游戏与 Nim 积

Nim 游戏规则可以抽象为如下形式：

> 有由 $n$ 个自然数所组成的可重集 $S$。双方轮流操作，每一回合玩家的操作流程为：
> 1. 选取 $S$ 的某个元素 $a$ 以及自然数 $k<a$。
> 2. 将 $a$ 从 $S$ 中删除，再将 $k$ 添加进 $S$ 中。 
>  
> 所在回合不能操作的一方失败。

那么相应地，定义二维 Nim 游戏的规则如下：

> 有由 $n$ 个有序对 $(x,y)\ (x,y\in\N)$ 所组成的可重集 $S$。双方轮流操作，每一回合玩家的操作流程为：
> 1. 选取 $S$ 的某个元素 $(x,y)$ 以及自然数 $x'<x,y'<y$。
> 2. 将 $(x,y)$ 从 $S$ 中删除，再将 $(x',y),(x,y'),(x',y')$ 添加进 $S$ 中。
>   
> 所在回合不能操作的一方失败。

易发现，因为公平博弈的反博弈等于其本身，根据和博弈的意义与积博弈的定义，  
对于 $S$ 中只含一个有序对 $(a,b)$ 的二维 Nim 游戏，其形式为

$$*_a*_b=\{T|T\},T=\{*_i*_b+*_j*_a+*_i*_j|i\in[0,a)\cup\N,j\in[0,b)\cup\N\}$$

更进一步地，定义 $m$ 维 Nim 游戏的规则如下：

> 有由 $n$ 个有序对 $(x_1,x_2,\cdots,x_m)\ (x_1,x_2,\cdots,x_m\in\N)$ 所组成的可重集 $S$。  
> 双方轮流操作，每一回合玩家的操作流程为：
> 1. 选取 $S$ 的某个元素 $(x_1,x_2,\cdots,x_m)$ 以及自然数 $x'_1<x_1,x_2'<x_2,\cdots,x'_n<x_n$。
> 2. 将 $(x_1,x_2,\cdots,x_m)$ 从 $S$ 中删除，再将除 $(x_1,x_2,\cdots,x_m)$ 外，  
> $(x_1,x_2,\cdots,x_m)$ 与 $(x_1',x_2',\cdots,x_m')$ 所张成的 $m$ 维超立方体的所有顶点添加进 $S$ 中。  
> 
> 所在回合不能操作的一方失败。

那么相应地，对于 $S$ 中只含一个有序对 $(x_1,x_2,\cdots,x_m)$ 的 $m$ 维 Nim 游戏，其形式为

$$*_{x_1}*_{x_2}\cdots *_{x_n}$$

------------------------------------

由于高维 Nim 博弈依然是公平博弈，其 SG 函数值必定存在，故定义 **Nim 积**

$$a\otimes b=\operatorname{mex}\{i\otimes b\oplus a\otimes j\oplus i\otimes j|i\in[0,a)\cup\N,j\in[0,b)\cup\N\}\quad(a,b\in\N)$$

则 $*_a*_b\equiv *_{a\otimes b}$，且 $\otimes$ 与公平博弈的乘法一样，满足

- 封闭性：$\forall a,b\in\N,a\otimes b\in\N$
- 交换律：$a\otimes b=b\otimes a$
- 结合律：$(a\otimes b)\otimes c=a\otimes(b\otimes c)$
- 零元：$a\otimes 0=0$
- 单位元：$a\otimes 1=1$
- $a\otimes b=0$ 当且仅当 $a=0$ 或 $b=0$
- 消去律：若 $c\not =0,a\otimes c=b\otimes c$，则 $a=b$

由于公平博弈满足乘法在 $\equiv$ 意义下的等量代换，  
我们一样可以将一般的有限公平博弈化简为 Nimber，进而用 Nim 积解决积博弈问题。

如何计算 Nim 积？我们有

1. 若 $a,b<2^{2^n}\ (n\in\N)$ 则 $a\otimes b<2^{2^n}$
2. 若 $a<2^{2^n}\ (n\in\N)$，则 $a\otimes 2^{2^n}=a\times 2^{2^n}$
3. $\forall n\in\N,2^{2^n}\otimes 2^{2^n}=3\times 2^{2^n-1}$
4. **平方根**：若 $x<2^{2^n}$，则存在唯一的 $a<2^{2^n},a\otimes a=x$（此时记 $a=\sqrt[\otimes]{x}$）
5. 若 $a<2^{2^n}$，则 $a\otimes(a\oplus 1)<2^{2^n-1}$

由性质 1.，2.，3.，即可得到求解 Nim 积的算法。对于 $a,b<2^{2^n}$，设

$$
a=a_0+a_1\times 2^{2^{n-1}}\ (a_0,a_1\in[0,2^{2^{n-1}})\cap\N)\\
b=b_0+b_1\times 2^{2^{n-1}}\ (b_0,b_1\in[0,2^{2^{n-1}})\cap\N)
$$

则

$$
a\otimes b=(a_0\oplus a_1\otimes 2^{2^{n-1}})\otimes(b_0\oplus b_1\otimes 2^{2^{n-1}})\\
=a_0\otimes b_0\oplus(a_0\otimes b_1\oplus a_1\otimes b_0)\otimes 2^{2^{n-1}}\oplus a_1\otimes b_1\otimes (3\times 2^{2^{n-1}-1})\\
=a_0\otimes b_0\oplus a_1\otimes b_1\otimes 2^{2^{m-1}-1}\oplus(a_0\otimes b_1\oplus a_1\otimes b_0\oplus a_1\otimes b_1)\otimes 2^{2^{n-1}}\\
=a_0\otimes b_0\oplus a_1\otimes b_1\otimes 2^{2^{n-1}-1}\oplus((a_0\otimes b_1\oplus a_1\otimes b_0\oplus a_1\otimes b_1)\times 2^{2^{n-1}})\\
=a_0\otimes b_0\oplus a_1\otimes b_1\otimes 2^{2^{n-1}-1}\oplus(((a_0\oplus a_1)\otimes(b_0\oplus b_1)\oplus a_0\otimes b_0)\times 2^{2^{n-1}})
$$

于是欲计算 $a\otimes b$，只需要计算

$$a_0\otimes b_0,a_1\otimes b_1\otimes 2^{2^{n-1}-1},(a_0\oplus a_1)\otimes(b_0\oplus b_1)$$

即可，复杂度为 $\Theta(2^{2n})$。

> 性质的证明*：我们同时对 1.，2.，3.，4.，5. 进行归纳。$n=0$ 时，可求得
> $$0\otimes 2=0,1\otimes 2=1,2\otimes 2=3$$
> $$\sqrt[\otimes]{0}=0,\sqrt[\otimes]{1}=1,0\otimes(0\oplus 1)=1\otimes(1\oplus 1)=0$$
> $\qquad n=m\in\N_+$ 时，设 $n=m-1$ 时，以上命题均成立。  
> $\qquad$ 首先证明 $n=m$ 时 1. 成立。设 $a=a_0+a_1\times 2^{2^{m-1}},b=b_0+b_1\times 2^{2^{m-1}}$  
> $\qquad(a_0,a_1,b_0,b_1\in[0,2^{m-1})\cap\N)$，则因为 $n=m-1$ 时 2.、3. 成立，参考 Nim 积的求解算法得
> $$
> a\otimes b=a_0\otimes b_0\oplus a_1\otimes b_1\otimes 2^{2^{m-1}-1}\oplus(((a_0\oplus a_1)\otimes(b_0\oplus b_1)\oplus a_0\otimes b_0)\times 2^{2^{m-1}})
> $$
> $\qquad$ 因为 $n=m-1$ 时 1. 成立，故
> $$a_0\otimes b_0,a_1\otimes b_1\otimes 2^{2^{n-1}-1},(a_0\oplus a_1)\otimes(b_0\oplus b_1)<2^{2^{m-1}}$$
> $\qquad$ 即可证明 $a\otimes b<2^{2^m}$。
> 
> -------
> $\qquad$ 有了 1.，即可归纳证明 2. 了。对于 $a<2^{2^m}$，设 $\forall i\in[0,a)\cap\N,i\otimes 2^{2^m}=i\times 2^{2^m}$，则
> $$
> a\otimes 2^{2^m}=\operatorname{mex}\{i\otimes 2^{2^m}\oplus a\otimes j\oplus i\otimes j|i\in[0,a)\cap\N,j\in[0,2^{2^{m}})\cap\N\}\\
> =\operatorname{mex}\{(i\times 2^{2^m})\oplus (a\oplus i)\otimes j|i\in[0,a)\cap\N,j\in[0,2^{2^{m}})\cap\N\}
> $$
> $\qquad$ 因为 $i<a<2^{2^m}$，故 $0<a\oplus i<2^{2^m}$。又因为 $n=m$ 时 1. 成立，故 $(a\oplus i)\otimes j<2^{2^m}$，   
> $\qquad$ 再根据 Nim 积的消去律，即可得到 $((a\oplus i)\otimes)$ 为 $[0,2^{2^m})\cap\N$ 上的置换，于是
> $$a\otimes 2^{2^m}=\operatorname{mex}\{(i\times 2^{2^m})\oplus j|i\in[0,a)\cap\N,j\in[0,2^{2^{m}})\cap\N\}=a\times 2^{2^m}$$
> -----  
> $\qquad$ 接下来证明 4. 成立。设 $F(x)=x\otimes x$，则若 $F(a)=F(b)$，
> $$
> a\otimes a=b\otimes b\\
> a\otimes a\oplus b\otimes b=0\\
> a\otimes a\oplus a\otimes b\oplus b\otimes a\oplus b\otimes b=0\\
> (a\oplus b)\otimes (a\oplus b)=0\\
> a\oplus b=0\\
> a=b
> $$
> $\qquad$ 于是 $F$ 是单射。又由 $n=m$ 时 1. 成立，即可得到 $F$ 是 $[0,2^{2^m})$ 上的置换，由此得 4. 成立。  
> 
> -------
> $\qquad$ 5. 的证明与 1. 类似。对于任意的 $x\in [0,2^{2^m})\cup\N$，  
> $\qquad$ 设 $x=x_0+x_1\times 2^{2^{m-1}}\ (x_0,x_1\in [0,2^{2^{m-1}}))$，参考 Nim 积的求解算法得  
> $$x\otimes (x\oplus 1)=x_0\otimes(x_0\oplus 1)\oplus x_1\otimes x_1\otimes 2^{2^{m-1}-1}\oplus((x_0\otimes x_1\oplus x_1\otimes (x_0\oplus 1)\oplus x_1\otimes x_1)\times 2^{2^{m-1}})\\
> =x_0\otimes(x_0\oplus 1)\oplus x_1\otimes x_1\otimes 2^{2^{m-1}-1}\oplus((x_0\otimes x_1\oplus x_1\otimes x_0\oplus x_1\oplus x_1\otimes x_1)\times 2^{2^{m-1}})\\
> =x_0\otimes(x_0\oplus 1)\oplus x_1\otimes x_1\otimes 2^{2^{m-1}-1}\oplus((x_1\otimes(x_1\oplus 1))\times 2^{2^{m-1}})
> $$
> $\qquad$ 因为 $n=m-1$ 时 1.,5. 均成立，故
> $$
> x_0\otimes(x_0\oplus 1),x_1\otimes x_1\otimes 2^{2^{m-1}-1}<2^{2^{m-1}}\\
> x_1\otimes(x_1\oplus 1)<2^{2^{m-1}-1}
> $$
> $\qquad$ 即可证明 $x\otimes (x\oplus 1)<2^{2^{m}-1}$。
>
> -----
>
> $\qquad$ 最后证明 3. 成立。由 $n=m$ 时 1. 2. 成立得
> $$
> 2^{2^m}\otimes 2^{2^m}=\operatorname{mex}\{i\otimes 2^{2^m}\oplus 2^{2^m}\otimes j\oplus i\otimes j|i,j\in[0,2^{2^m})\cap\N\}\\
> =\operatorname{mex}\{(i\oplus j)\otimes 2^{2^m}\oplus i\otimes j|i,j\in[0,2^{2^m})\cap\N\}\\
\forall i,j\in[0,2^{2^m})\cap\N,i\otimes j\in[0,2^{2^m})\cap\N
> $$
> $\qquad$ 若 $i\oplus j\ge 2$，则显然 $(i\oplus j)\otimes 2^{2^m}\oplus i\otimes j\ge 2^{2^{m}+1}$。  
> $\qquad$ 若 $i\oplus j=0$，即 $i=j$，则 $(i\oplus j)\otimes 2^{2^m}\oplus i\otimes j=i\otimes i=F(i)$，  
> $\qquad$ 由 4. 的证明我们已经知道了 $F$ 是 $[0,2^{2^m})\cap\N$ 上的置换，于是
> $$\{(i\oplus j)\otimes 2^{2^m}\oplus i\otimes j|i,j\in[0,2^{2^m})\cap\N,i\oplus j=0\}=[0,2^{2^m})\cap\N$$
> $\qquad$ 若 $i\oplus j=1$，即 $j=i\oplus 1$，则 $(i\oplus j)\otimes 2^{2^m}\oplus i\otimes j=2^{2^m}\oplus i\otimes (i\oplus 1)$，  
> $\qquad$ 与 4. 的证明类似地，设 $G(x)=x\otimes (x\oplus 1)$，则因为 $n=m$ 时 5. 成立，
> $$\{G(x)|x\in[0,2^{2^m})\cap\N\}\subseteq [0,2^{2^{m}-1})\cap\N$$
> $\qquad$ 同时，若 $G(a)=G(b)$，则
> $$
> a\otimes(a\oplus 1)=b\otimes (b\oplus 1)\\
> a\otimes a\oplus a=b\otimes b\oplus b\\
> a\otimes a\oplus b\otimes b=a\oplus b\\
> a\otimes a\oplus a\otimes b\oplus b\otimes a\oplus b\otimes b=a\oplus b\\
> (a\oplus b)\otimes (a\oplus b)=a\oplus b\\
> (a\oplus b)\otimes (a\oplus b\oplus 1)=0\\
> a\oplus b=0\texttt{ 或 } a\oplus b\oplus 1=0\\
> a=b\texttt{ 或 } a=b\oplus 1
> $$
> $\qquad$ 于是 $\{G(x)|x\in[0,2^{2^m})\cap\N\}=[0,2^{2^{m}-1})\cap\N$，故
> $$\{(i\oplus j)\otimes 2^{2^m}\oplus i\otimes j|i,j\in[0,2^{2^m})\cap\N,i\oplus j=1\}=[2^{2^{m}},3\times 2^{2^m-1})\cap\N$$
> $\qquad$ 综上，根据 $\operatorname{mex}$ 的定义，即可得到
> $$2^{2^m}\otimes 2^{2^m}=\operatorname{mex}([0,2^{2^m})\cup[2^{2^{m}},3\times 2^{2^m-1})\cup[2^{2^m+1},+\infty))\cap\N=3\times 2^{2^m-1}$$

