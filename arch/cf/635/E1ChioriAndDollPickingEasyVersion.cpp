#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class E1ChioriAndDollPickingEasyVersion {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<ll> A(N); cin >> A;
        vector<ll> Base(M, 0);
        int other = 0;
        for (int i = 0; i < N; ++i) {
            ll a = A[i];
            for (int j = M-1; j >= 0; --j) {
                if (a&1LL<<j) a^=Base[j];
            }
            if (a != 0) {
                Base[logceil(a)-1] = a;
            } else {
                other++;
            }
        }

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < i; ++j) {
                if (Base[i]&1LL<<j) Base[i] ^= Base[j];
            }
        }

        int single = 0;
        for (int i = 0; i < M; ++i) {
            if (Base[i] == (1LL<<i)) {
                Base[i] = 0;
                single++;
            }
        }



        int bases = 0;
        vector<int> Bases;
        for (int i = 0; i < M; ++i) {
            if (Base[i] != 0) {
                Bases.push_back(i);
                bases++;
            }
        }

        vector<bool> U(M, false);
        vector<int> Idx;

        cerr << Base;

        for (int i = M-1; i >= 0; --i) {
            if (U[i]) continue;
            if (Base[i] == 0) continue;
            Idx.push_back(i);
            U[i] = true;
//            cerr << "try " << i << endl;
            for (int j = 0; j < M; ++j) {
                if (Base[j] == 0 && Base[i]&1LL<<j && !U[j]) {
//                    cerr << "use " << j << " bit " << endl;
                    U[j] = true;
                    int blow = -1;
                    for (int k = M-1; k >= 0; --k) {
//                        cerr << k << ' ' << !U[k] << ' ' << (Base[k]&1LL<<j) << '\n';
                        if (!U[k] && (Base[k]&1LL<<j)) {
                            blow = k;
                        }
                    }
                    if (blow != -1) {
                        cerr << "blow " << blow << endl;
                        Idx.push_back(blow);
                        U[blow] = true;
                        for (int l = 0; l < M; ++l) {
                            if (!U[l] && Base[l]&(1LL<<j)) {
                                Base[l] ^= Base[blow];
                            }
                        }
                    }
                    Idx.push_back(j);

                    break;
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (!U[i]) Idx.push_back(i);
        }

        cerr << Idx;
        cerr << Base;
//        vector<int> Idx(M);

//        for (int i = 0; i < M; ++i) Idx[i] = i;
        map<pair<int,ll>,ll> X;
        X[{0,0LL}] = 1;
        for (int i: Idx) {
            map<pair<int,ll>, ll> Y;
            if (Base[i] == 0) {
                for (auto x: X) {
                    if (x.x.y&1LL<<i) {
                        Y[{x.x.x+1, x.x.y^1LL<<i}] += x.y;
                    } else {
                        Y[{x.x.x,x.x.y}] += x.y;
                    }
                }
            } else {
                for (auto x: X) {
                    if (x.x.y&1LL<<i) {
                        Y[{x.x.x+1, x.x.y^1LL<<i}] += x.y;
                    } else {
                        Y[{x.x.x,x.x.y}] += x.y;
                    }
                    int c = x.x.x;
                    ll d = x.x.y;
                    d ^= Base[i];
                    if (d&1LL<<i) {
                        c += 1;
                        d ^= 1LL<<i;
                    }
                    Y[{c, d}] += x.y;
                }
            }
            swap(X,Y);
            int tot = 0;
            for (auto x: X) {
                tot += x.y;
            }
        }

        vector<FF> Ans(M+1);
        for (int i = 0; i <= M; ++i) {
            Ans[i] = FF{X[{i,0LL}]%998244353}*FF{2}.pow(other);
        }
        cout << Ans;

        auto F = FF::fact(M+2);
        auto I = FF::invfact(M+2);
        vector<FF> RealAns(M+1);
        for (int i = 0; i <= M; ++i) {
            if (Ans[i] != 0) {
                for (int j = 0; j <= single; ++j) {
                    RealAns[i+j] += Ans[i] * F[single] * I[j] * I[single-j];
                }
            }
        }
        cout << RealAns;
    }
};
