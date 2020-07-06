#include "../l/lib.h"
#include "../l/random.h"

class DMakeEqual {
public:
    int brute(vector<ll> A) {
        sort(A.begin(),A.end());
        int ans = 1e8;
        for (int a = A.back(); a <= 4*A.back(); ++a) {
            int cur = 0;
            for (int b: A) {
                cur += __builtin_popcount(a-b);
            }
            ans = min(ans, cur);
        }
        return ans;
    }

    ll smart(vector<ll> A) {
        int N = A.size();
        vector<ll> D(N+1, 1e18);
        D[0] = 0;
        for (int bit = 0; bit <= 60; ++bit) {
            ll myBit = 1LL<<bit;

            int zero = 0, zeroC = 0, one = 0, oneC = 0;
            for (int i = 0; i < N; ++i) {
                if (A[i]&myBit) one++; else zero++;
            }

            vector<ll> E(N+1, 1e18);
            for (int i = 0; i <= N; ++i) {
                E[oneC] = min(E[oneC], D[i] + oneC + zero);
                E[oneC + zeroC + one] = min(E[oneC + zeroC + one], D[i] + zeroC + one);

                if (i != N) {
                    if (A[i]&myBit) {
                        oneC++;
                        one--;
                    } else {
                        zeroC++;
                        zero--;
                    }
                }
            }
            swap(D,E);

            ll mask = (2LL<<bit)-1;
            sort(A.begin(),A.end(),[&](ll a, ll b) { return (a&mask)<(b&mask); });
            reverse(A.begin(),A.end());
        }
        return D[0];//*min_element(D.begin(),D.end());
    }

    void solve(istream& cin, ostream& cout) {
        random_int RN(50, 100), RA(0,5000);
        int t = 0;
        while (true) {
            int N = RN(rng);
            vector<ll> A(N);
            for (ll&a: A) a = RA(rng);
            auto b = brute(A);
            auto s = smart(A);
            if (s != b) {
                cerr << "FAIL\n";
                cerr << N << '\n' << A;
                cerr << b << ' ' << s << '\n';
                return;
            }
            if (++t%100==0) {
                cerr << ".";
            }
            if (t%10000==0) {
                cerr << '\n';
            }

        }
//        int N; cin >> N;
//        vector<ll> A(N); cin >> A;
//        cout << smart(A) << '\n';
    }
};
