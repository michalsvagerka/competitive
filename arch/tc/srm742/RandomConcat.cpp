#include "../l/lib.h"
#include "../l/string.h"

class RandomConcat {
public:

    double expectation(vector <string> pieces, string needle) {
        int N = pieces.size();
        int M = needle.size();
        KMP<string> K{needle += '$'};

        vector<double> F(N+1, 1);
        for (int i = 1; i <= N; ++i) F[i] = F[i-1] * i;

        vector2<int> T(N, M+1), C(N, M+1);
        vector2<double> W(1<<N, M+1, 0);
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k <= M; ++k) {
                int l = k;
                for (char s : pieces[i]) {
                    l = K.advance(l, s);
                    C[i][k] += l == M;
                }
                T[i][k] = l;
            }
        }

        W[0][0] = 1;
        double ans = 0;
        for (int i = 0; i < (1<<N); ++i) {
            for (int j = 0; j < N; ++j) {
                if (i&(1<<j)) continue;
                for (int k = 0; k <= M; ++k) {
                    ans += C[j][k] * W[i][k] * F[N-1-__builtin_popcount(i)];
                    W[i^(1<<j)][T[j][k]] += W[i][k];
                }
            }
        }
        return ans / F[N];
    }

    void solve(istream& cin, ostream& cout) {
        cout << expectation({"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}, "a") << endl;
        cout << expectation({"hahaha"}, "aha") << ' ' << 2.0 << endl;
        cout << expectation({"hah","ah"}, "aha") << ' ' << 0.5 << endl;
        cout << expectation({"t","o","p","c","o","d","e","r"}, "topcoder") << ' ' << 4.9603174603174596E-5 << endl;
        cout << expectation({"hellotopc","oderhellotop","coderbye"}, "topcoder") << ' ' << 0.6666666666666666 << endl;
        cout << expectation({"aabaa","aabaaaaa","aba","goodluck","havefun"}, "aaaa") << ' ' << 2.8000000000000016 << endl;
        cout << expectation({"a","a","aa","b"}, "aba") << ' ' << 0.5 << endl;
    }
};
