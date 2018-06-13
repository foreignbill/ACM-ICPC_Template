ll Mul(ll a,ll b,ll base){
    ll ans = 0;
    a %= base;b %= base;
    ll now = b;
    while (a != 0){
        ans += now * (a % 2);
        ans %= base;
        now *= 2;
        now %= base;
        a = a / 2;
    }
    return ans;
}
// a * b % base (base 1e18)