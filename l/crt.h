#ifndef MAJK_CRT
#define MAJK_CRT

#include "lib.h"
#include "bigint.h"
#include "mod.h"

template<ui N,ui M> class Chinese {
public:
    Chinese(const std::array<ui,N> &p) : P(1), p(p) {
        for(int i=0;i<N;++i)P*=p[i];
        for(int i=0;i<N;++i){ F[i]=P/p[i]; }
        for(int i=0;i<N;++i) { T[i]=Ring::div(1, (F[i]%p[i]).to_longlong(), p[i]);}
    }

    ui operator()(const std::array<ui,N> &R) {
        Num X = 0;
        for (int i=0;i<N;++i) X += F[i] * ((ull(R[i])*T[i])%p[i]);
        X %= P;
        X %= M;
        return X.to_longlong();
    }
private:
    Num P;
    std::array<Num,N> F;
    std::array<ui,N> T,p;
};



#endif //MAJK_CRT_H
