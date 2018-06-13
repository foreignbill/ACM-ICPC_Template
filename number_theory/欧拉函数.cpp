int getphi(int p){
    int phi = p, m = p, k = 2;
    while (k * k <=m) {
        if (m % k == 0) {
            phi /= k;
            phi *= (k-1);
            while (m % k == 0)
                m /= k;
        }
        ++k;
    }
    if (m != 1) {
        phi /= m;
        phi *= (m-1);
    }
    return phi;
}