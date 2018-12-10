#include "../l/lib.h"
// #include "../l/mod.h"
#include <numeric>
class P3 {
public:
    void solve(istream& cin, ostream& cout) {
        vector<int> X(64);
        for (int i = 0; i < 64; ++i) X[i] = i;
        string S;
        while (getline(cin, S)) {
            for (int i = 0; i < 63; ++i) {
                if (S[2*i+1] == '_') {
                    swap(X[63-i],X[63-(i+1)]);
                }
            }
        }

        bitset<64> B{(ull(42)<<32)+ull(42)};
        bitset<64> Z;
        while (true) {
            auto u = Z.to_ullong();
            auto adam = u>>32;
            if (adam == 16641) {
                cout << (u << 32 >> 32) << endl;
                break;
            }

            for (int i = 0; i < 64; ++i) {
                Z[X[i]] = B[i];
            }
            swap(Z,B);
        }
    }
};














/*
scol 0
srow 2
acol -1
write1
scol 0
srow 0
read 1 8
srow 1
read 1 8
srow 2
read 1 37
write0
acol 1
jump -8
srow 1
read 1 6
srow 2
read 1 32
write1
acol 1
jump -15
srow 2
read 1 25
write0
acol 1
jump 1
srow 0
read 1 8
srow 1
read 1 8
srow 2
read 1 18
write1
acol 1
jump -29
srow 1
read 1 6
srow 2
read 1 9
write0
acol 1
jump -15
srow 2
read 1 6
write1
acol 1
jump -20
write0
end
write1
end
        */
