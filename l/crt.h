#ifndef MAJK_CRT
#define MAJK_CRT

#include "lib.h"
//#include "bigint.h"
#include "mod.h"

template<ui N> class Chinese {
public:
    Chinese(const std::array<ui,N> &p, int M) : P(1), M(M), p(p) {
        for(int i=0;i<N;++i)P*=p[i];
        for(int i=0;i<N;++i){ F[i]=P/p[i]; }
        for(int i=0;i<N;++i) { T[i]=Ring::div(1, (F[i]%p[i]), p[i]);}
    }

    ui operator()(const std::array<ui,N> &R) {
        __int128 X = 0;
        for (int i=0;i<N;++i) X += F[i] * ((ull(R[i])*T[i])%p[i]);
        X %= P;
        X %= M;
        return ui(X);
    }
private:
    __int128 P;
    int M;
    std::array<__int128,N> F;
    std::array<ui,N> T,p;
};



#endif //MAJK_CRT_H
