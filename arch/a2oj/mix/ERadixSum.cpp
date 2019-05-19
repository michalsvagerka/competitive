#include "../l/lib.h"
// #include "../l/mod.h"
using namespace std;

template <typename T, int Degree>
class Poly {
public:
    Poly() : X({0}) {}
    Poly(std::initializer_list<T> x) : X({0}) {
        int i = 0;
        for (auto it = x.begin(); it != x.end(); ++it, ++i) X[i] = *it;
    }
    
    Poly& operator+=(const Poly&b) {
        for (int i = 0; i < Degree; ++i) X[i] += b.X[i];
        return *this;
    }

    Poly& operator*=(const Poly&b) {
        Poly c;
        for(int i=0;i<Degree;++i)
            for(int j=0;j<Degree;++j)
                if (i+j<Degree) c.X[i+j]+=X[i]*b.X[j];
                else c.X[i+j-Degree]-=X[i]*b.X[j];
        return *this = c;
    }

    Poly operator*(const Poly&b) const {
        return Poly{*this} *= b;
    }

    template <int S>
    Poly& operator%=(const Poly<T,S>&b) {
        int q = S-1;
        while (b.X[q] == 0) --q;
        for (int i = Degree-1; i >= q; --i) {
            auto d = X[i] / b.X[q];
            for (int j = 0; j <= q; ++j) X[i-j] -= d * b.X[q-j];
        }
        return *this;
    }

    Poly& operator^=(ull p) {
        Poly a = *this;
        Poly c = {1};
        for (;p; a *= a, p /= 2) if(p&1) c *=a;
        return *this = c;
    }

    T& operator[](int x) {
        return X[x];
    }

    void print(ostream&os) const {
        bool first = true;
        for (int i = 0; i < Degree; ++i) {
            if (X[i]) {
                if (X[i] < numeric_limits<T>::max()/2) {
                    if (i == 0 || X[i] != 1) {
                        if (!first) os << '+';
                        os << X[i];
                    }
                } else {
                    if (i == 0 || (ll)X[i] != -1) os << (ll)X[i];
                    else os << '-';
                }

                if (i != 0) {
                    os << 'x';
                    if (i >= 2) {
                        os << '^' << i;
                    }
                }
                first = false;
            }
        }
    }

private:
    array<T, Degree> X;
};

template <typename T, int D>
ostream& operator<<(ostream&os, const Poly<T,D>&p) {
    p.print(os);
    return os;
}

constexpr ull pw(ull a,ull b){
    ull c=1;
    for(;b;a*=a,b/=2) if(b&1)c*=a;
    return c;
}

constexpr int B=10;
constexpr int SZ=5;
constexpr int LG=5;
constexpr int MX=100000; // pow(B, LG)
constexpr ull MOD=(1LL<<58);

using PPP = Poly<ull, SZ>;

constexpr int pws[] = {1, 10, 100, 1000, 10000, 100000};

class ERadixSum {
public:
    using arr=array<PPP, MX>;
    using smarr=array<PPP, B>;

    PPP rts[B][B];
    PPP rts1[B][B];

    void initrts() {
        PPP root = {0,1}; // x

        PPP cur = {1};
        for (int i = 0; i < B; ++i, cur *= root) {
            PPP x = {1};
            for (auto &r: rts[i]) {
                r = x;
                x *= cur;
            }
        }

        root = {0,0,0,0,(ull)-1};  // x^{-4}
        cur = {1};
        for (int i = 0; i < B; ++i, cur *= root) {
            PPP x = {1};
            for (auto &r: rts1[i]) {
                r = x;
                x *= cur;
            }
        }
    }

    inline smarr dft(smarr x, bool inv) {
        smarr ans;
        for (int i = 0; i < B; ++i) {
            for (int j = 0; j < B; ++j) {
                ans[i] += (inv ? rts[i][j] : rts1[i][j]) * x[j];
            }
        }
        return ans;
    }

    void hadamard(arr &a, bool inv) {
        for (int i = 0; i < LG; ++i) {
            for (int j = 0; j < MX; ++j) {
                if (j % pws[i + 1] / pws[i] == 0) {

                    smarr A;
                    for (int k = 0; k < B; ++k) A[k] = a[j + pws[i] * k];
                    A = dft(A, inv);
                    for (int k = 0; k < B; ++k) a[j + pws[i] * k] = A[k];
                }
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        initrts();

        int N;
        cin >> N;
        arr A;
        fill(A.begin(),A.end(),PPP{0});

        for (int i = 0; i < N; ++i) {
            int x;
            cin >> x;
            ++A[x][0];
        }
        hadamard(A, false);
        for (auto&a: A) a ^= N;
        hadamard(A, true);

        ull inv = pw(5, (1ULL<<63)-1);
        inv = pw(inv,LG);
        PPP cyclo = {1,(ull)-1,1,(ull)-1,1};
        for(int i = 0; i < N;++i) {
            A[i] %= cyclo;
            A[i][0] >>= LG;
            A[i][0] *= inv;
            cout<<A[i][0]%MOD<<'\n';
        }
    }
};
