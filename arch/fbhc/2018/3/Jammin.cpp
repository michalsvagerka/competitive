#include "../l/lib.h"
// #include "../l/mod.h"

class Jammin {
public:
//    void go(string &S, int dir, int &p, int &a, int &i, bool backing) {
//        int N = S.size();
//        while (true) {
//            if (0 <= i + dir && i + dir < N) {
//                if (S[i + dir] == '.') i += dir;
//                else if (S[i + dir] == '*') {
//                    i += dir;
//                    a = max(a, ++p);
//                    S[i + dir] = '.';
//                    if (backing) return;
//                }
//                else if (S[i + dir] == '#') {
//                    int j = i + dir + dir;
//                    int k = j + dir;
//                    if (0 <= j && j < N) {
//                        if (S[j] == '*') {
//                            i = j;
//                            a = max(a, ++p);
//                            S[j] = '.';
//                        } else {
//                            if (p == 0) return;
//                            if (0 <= k && k < N) {
//                                if (S[k] == '#' || S[k] == '.') return;
//                                S[i] = '*';
//                                S[k] = '.';
//                                i = k;
//                            } else {
//                                return;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
    

//    int brute(string S) {
//        int N = S.size();
//        int a = 0, p = 0, i = 0;
//        while (true) {
//            if (i < N-1) {
//                if (S[i+1] == '.') ++i;
//                else if (S[i+1] == '*') { ++i; a=max(a,++p); }
//                
//            }
//        }
//    }
    
void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        string C;
        cin >> C;
        int p = 0, a = 0, b = 0, b2 = 0;

        int N = C.size();
        for (int j = 0; j < N; ) {
            if (C[j] == '*') {
                p += 1;
                if (p >= 2) {
                    p += b2;
                    b = b2 = 0;
                } else {
                    p += b;
                    b2 -= b;
                    b = 0;
                    if (p >= 2) { p += b2; b2 = 0; }
                }
                a = max(a,p);
                ++j;
            } else if (C[j] == '#') {
                int c = 0;
                while (j+c < N && C[j+c] == '#') ++c;
                if (c >= 3) break;
                else if (c == 2) {
                    if (p > 0 && (j+c<N && C[j+c] == '*')) { --p; j += c; } else break;
                } else {
                    if (j+1<N && C[j+1] == '*') {
                        ++j;
                        b = 0;
                        // we nom it later
                    } else if (p == 0) {
                        break;
                    } else if (p == 1) {
                        --p;
                        ++b; // place backref
                        ++b2;
                        ++j;
                    } else  { 
                        // just cross
                        ++j;
                    }
                }
            } else {
                ++j;
            }
            
            
//            cout << j << ' ' << a << ' ' << b << ' ' << p << ' ' << endl;
        }

        cout << "Case #" << t+1 << ": " << a << '\n';
    }

}
};
