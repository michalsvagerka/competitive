#include "../l/lib.h"

class ABBAReplace {
public:
    int brute(string S) {
        int a = 0;
        vector<int> A;
        for (char s: S) {
            if (s == 'A') {
                a++;
            } else {
                A.push_back(a);
                a = 0;
            }
        }

        if (A.empty()) return 0;

        int M = A.size();
        int cnt = 0;
        while (true) {
            bool change = false;
            for (int i = M-1; i >= 0; --i) {
                if (A[i]) {
                    change = true;
                    if (i < M-1) {
                        A[i + 1]++;
                    }
                    A[i]--;
                }
            }
            if (change) cnt++;
            else break;
        }
        return cnt;
    }

    int smart(string S) {
        int a = 0;
        vector<int> A;
        for (char s: S) {
            if (s == 'A') {
                a++;
            } else {
                A.push_back(a);
                a = 0;
            }
        }

        if (A.empty()) return 0;

        int M = A.size();
        vector<int> B(M);
        int delay = 0;
        int ans = 0;
        for (int b = M-1; b >= 0; --b) {
            B[b] = A[b] + delay + (M-1-b);
            delay += A[b]-1;
            delay = max(0, delay);
            if (A[b])  ans = max(ans, B[b]);
        }
        return ans;
    }

    int countSteps(string Sprefix, int N, int seed, int threshold) {
        ll state = seed;
        string S = Sprefix;
        while (S.size() < N) {
            state = (state * 1103515245LL + 12345) % (1LL<<31);
            if (state < threshold) S += 'A'; else S += 'B';
        }

        int s = smart(S);
        int b = brute(S);
        if (s != b) {
            cerr << S << ' ' << s << ' ' << b << endl;
        }
        return s;
    }
    void solve(istream& cin, ostream& cout) {
        for (int i = 1; i < 10000; ++i) {
            for (int t = 0; t <= 100; ++t) {
                countSteps("", 1000, i, (1LL<<31)/100*t);
            }
            if (i%100==0) cerr << "seed " << i << endl;
        }

        cout << countSteps("AABABB",6,0,0) << '\n';
        cout << countSteps("",0,4,7) << '\n';
        cout << countSteps("ABBABAABABBBABBBB",17,0,0) << '\n';
        cout << countSteps("AABAA",17,47474747,1000000000) << '\n';
    }
};

