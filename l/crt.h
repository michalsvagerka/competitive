#ifndef MAJK_CRT
#define MAJK_CRT

#include "lib.h"
#include "bigint.h"
#include "mod.h"

class Chinese {
public:
    Chinese(const vector<ll> &p, ll M) : P(1), M(M), F(p.size()), T(p.size()), p(p) {
        for(int i=0;i<p.size();++i) P*=p[i];
        for(int i=0;i<p.size();++i) F[i]=P/p[i];
        for(int i=0;i<p.size();++i) T[i]=Ring::div(1, (F[i]%p[i]).to_longlong(), p[i]);
    }

    ll operator()(const vector<ll> &R) {
//#ifdef __SIZEOF_INT128__
//        __int128 X = 0;
//#else
        Num X = 0;
//#endif
        for (int i=0;i<R.size();++i) X += F[i] * ((Num{T[i]} * R[i])%p[i]);
        X %= P;
        X %= M;
        return X.to_longlong();
    }
private:
//    __int128 P;
    Num P;
    ll M;
    vector<Num> F;
    vector<ll> T,p;
};



#endif //MAJK_CRT_H
