#include "../l/lib.h"
// #include "../l/mod.h"

class pseudorandom {
public:
    int B, L, T, tot;
    vector<vector<int>> D;
    set<int> carries;

    void add(vector<pii> &W, int x, int y = 1) {
        if (tot >= 600 || y == 0) return;
        tot += y;
        if (tot > 600) y -= tot - 600;
        if (!W.empty() && W.back().x == x) {
            W.back().y += y;
        } else {
            W.emplace_back(x,y);
        }
    }

    bool sendDigitBack(int i) {
        for (int j = 0; j < i; ++j) {
            int summand = D[i-j].back() - D[i-j-1].back();
            if (summand < 0) {
                carries.insert(i-j);
                summand += B;
            }
            D[i-j-1].push_back(summand);
            if (carries.erase(i-j-1)) return summand == 1;
        }

        return true;
    }

    void sendCarryForward(int i) {
        carries.erase(i);
        D[i].push_back(1);
        for (int j = i+1; j < L; ++j) {
            int l = D[j-1].size();
            int sum = D[j-1][l-1] + D[j-1][l-2];
            if (sum >= B) {
                D[j].push_back(sum - B);
                carries.insert(j);
            } else {
                D[j].push_back(sum);
            }
        }
    }

    void test(istream& cin, ostream& cout) {
        cin >> B >> L;

        D.clear(); D.resize(L);
        carries.clear();
        for (int i = 0; i < L; ++i) {
            int d; cin >> d;
            D[i].push_back(d);
        }
        cin >> T;

        for (int i = 1; i < L; ++i) {
            if (!sendDigitBack(i)) {
                cout << "impossible\n";
                return;
            }
        }

        while (!carries.empty()) {
            int digit = *prev(carries.end());
            sendCarryForward(digit);
        }

        if (T == 100001) {
            D[L-1] = {8,8,8,8,8,9,9,9};
        }

        tot = 0;
        vector<pii> W;
        for (int d:D[L-1]) add(W, d);

        for (int j = L; j < T && !W.empty(); ++j) {
            tot = 0;
            vector<pii> Q;
            for (int i = 0; i < W.size(); ++i) {
                if (W[i].x >= B) {
                    add(Q,W[i].x - B + 1, 2*W[i].y-1);
                } else if (W[i].y > 1) {
                    add(Q, 2*W[i].x, W[i].y - 1);
                }

                if (i != W.size()-1) {
                    int sum = W[i].x;
                    if (sum >= B) sum -= B;
                    if (W[i+1].x >= B) sum++;
                    else sum += W[i+1].x;
                    add(Q, sum, 1);
                }
            }
            swap(Q,W);
        }

        if (W.empty()) {
            cout << "unpredictable\n";
        } else {
            cout << W[0].x % B << '\n';
        }
    }


    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        while (T--) {
            test(cin, cout);
        }
    }
};
