#include "../l/lib.h"

class CPerfectTriples {
public:
    vector<ll> solve(ll j) {
        ll lo = 0;
        ll pow4 = 1;
        ll left = j;
        int s = 0;
        while (left >= lo + pow4) {
            lo += pow4;
            pow4 *= 4;
            s++;
        }
        ll ss = j - lo;
        vector<int> D, E(s), F(s);
        for (int x = 0; x < s; ++x) {
            D.push_back(ss%4);
            ss /= 4;
        }
        for (int x = 0; x < s; ++x) {
            switch (D[x]) {
                case 0: E[x] = F[x] = 0; break;
                case 1: E[x] = 2; F[x] = 3; break;
                case 2: E[x] = 3; F[x] = 1; break;
                case 3: E[x] = 1; F[x] = 2; break;
            }
        }
        ll e = 0;
        ll f = 0;
        for (int x = 0; x < s; ++x) {
            e = 4*e + E[s-1-x];
            f = 4*f + F[s-1-x];
        }
        return {pow4 + j - lo,2*pow4 + e,3*pow4 + f};
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            ll N; cin >> N;
            N--;
            auto SS = solve(N/3);
            cout << SS[N%3] << '\n';
        }
//        int MX = 1023;
//        vector<bool> U(MX+1, true);
//        vector<int> Ans, Syn(300);
//        for (int j = 0; j < 100; ++j) {
//            // 0     2^0 + x - lo
//            // 1-4   2^2 + x - lo
//            // 5-20  2^4 + x - lo
//            // 21-84 2^6 + x - lo
//            // 85-.. 2^8 + x - lo
//            ll lo = 0;
//            ll pow4 = 1;
//            ll left = j;
//            int s = 0;
//            while (left >= lo + pow4) {
//                lo += pow4;
//                pow4 *= 4;
//                s++;
//            }
//            ll ss = j - lo;
//            vector<int> D, E(s), F(s);
//            for (int x = 0; x < s; ++x) {
//                D.push_back(ss%4);
//                ss /= 4;
//            }
//            for (int x = 0; x < s; ++x) {
//                switch (D[x]) {
//                    case 0: E[x] = F[x] = 0; break;
//                    case 1: E[x] = 2; F[x] = 3; break;
//                    case 2: E[x] = 3; F[x] = 1; break;
//                    case 3: E[x] = 1; F[x] = 2; break;
//                }
//            }
//            ll e = 0;
//            ll f = 0;
//            for (int x = 0; x < s; ++x) {
//                e = 4*e + E[s-1-x];
//                f = 4*f + F[s-1-x];
//            }
//            Syn[3*j] = pow4 + j - lo;
//            Syn[3*j+1] = 2*pow4 + e;
//            Syn[3*j+2] = 3*pow4 + f;
//        }
//        for (int i = 0; i < 100; ++i) {
//            bool found = false;
//            for (int a = 1; a <= MX && !found; ++a) {
//                if (!U[a]) continue;
//                for (int b = a+1; b <= MX && !found; ++b) {
//                    if (!U[b]) continue;
//                    int c = a^b;
//                    if (c > b && U[c]) {
//                        Ans.push_back(a);
//                        Ans.push_back(b);
//                        Ans.push_back(c);
//                        U[a] = U[b] = U[c] = false;
//                        found = true;
////                        cout << (2*a == b) << ' ';
//                    }
//                }
//            }
//        }
//        cout << endl;
//        for (int i = 0; i < Ans.size(); i += 3) {
//            cout << i/3 << ' ' << Ans[i]-Syn[i] << ' ' << Ans[i+1]-Syn[i+1] << ' ' << Ans[i+2]-Syn[i+2] << endl;
//        }
    }
};
