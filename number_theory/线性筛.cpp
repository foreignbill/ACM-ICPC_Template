/*
p 为是否为素数
prime 为第几个素数
phi 为欧拉函数
mu 为莫比乌斯函数
divnum 为因子 数
nxt 为最小的质因子的编号(*错)
e 为最大的质因子的幂次
d 为 i 除去最小质因子的数
F 为 i 的因数平方和
*/

memset(p, 0, sizeof(p));
phi[1] = 1;
mu[1] = 1;
div_num[1] = 1;
F[1] = 1;
top = 0;
for (i = 2; i <= N; ++i) {
    if (!p[i]) {
        prime[++top] = i;
        mu[i] = -1;
        phi[i] = i-1;
        e[i] = 1;
        div_num[i] = 2;
        d[i] = 1;
        F[i] = ((ll)i * i + 1) % mod;
        nxt[i] = top;//i 最大因子的下标
    }
    for (j = 1; j <= top; ++j) {
        if (i * prime[j] > N)
            break;
        p[i * prime[j]] = 1;
        nxt[i * prime[j]] = j;
        if (i % prime[j] == 0) {
            phi[i * prime[j]] = phi[i] * prime[j];
            div_num[i*prime[j]]=div_num[i]/(e[i]+1)*(e[i]+2);
            e[i*prime[j]]=e[i]+1;
            d[i * prime[j]] = d[i];
            F[i * prime[j]] = (F[i] * ((ll)prime[j] * prime[j] % mod) + F[d[i]]) % mod;
            break;
        }
        phi[i * prime[j]] = phi[i] * phi[prime[j]];
        mu[i * prime[j]] = -mu[i];
        div_num[i*prime[j]]=div_num[i]*div_num[prime[j]];
        e[i*prime[j]] = 1;
        d[i * prime[j]] = i;
        F[i * prime[j]] = F[i] * (((ll)prime[j] * prime[j] + 1) % mod) % mod;
    }
}