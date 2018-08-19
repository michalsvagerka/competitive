#ifndef MAJK_FACT_H
#define MAJK_FACT_H

#include "random.h"
#include "util.h"


ll findFactor(ll number) {
    random_ll R(2, number-1);
    ll x = R(rng), y = x, d = 1;
    while (d == 1) {
        x = (mulull(x, x, number) + 1) % number;
        y = (mulull(y, y, number) + 1) % number;
        y = (mulull(y, y, number) + 1) % number;
        d = gcd(abs(x - y), number);
    }
    return d == number ? findFactor(number) : d;
}



//    ll x_fixed = 2, x = 2, factor = 1;
//    int cycle_size = 2;
//
//    while (factor == 1) {
//        for (int count=1; count <= cycle_size && factor <= 1;count++) {
//            x = (x*x+1)%number;
//            factor = gcd(abs(x - x_fixed), number);
//        }
//
//        cycle_size *= 2;
//        x_fixed = x;
//    }
//    return factor;
//}

#endif //MAJK_FACT_H
