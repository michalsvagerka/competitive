#include "../l/lib.h"
 #include "../l/random.h"

class BagsAndCoins {
public:
void solve(istream& cin, ostream& cout) {
    int N, S; cin >> N >> S;
    vector<int> A(N); cin >> A;
    if (N == 1) {
        if (A[0] == S) {
            cout << A[0] << " 0\n";
        } else {
            cout << "-1\n";
        }
        return;
    }
    vector<pii> B(N);
    for (int i = 0; i < N; ++i) {
        B[i] = {A[i],i};
    }

    sort(B.begin(),B.end());

    vector<bool> Top(N, false);
    Top[B[N-1].y] = true;
    S -= B.back().x;
    if (S < 0) {
        cout << "-1\n";
        return;
    }

    int blk = 100;
    vector<bitset<70001>> C;
    bitset<70001> cur;
    cur[0] = 1;
    for (int i = 0; i < N-1; i++) {
        if (i%blk == 0) {
            C.push_back(cur);
        }
        cur = cur | (cur << B[i].x);
        if (i == N-2) {
            C.push_back(cur);
        }
    }

    if (!C.back()[S]) {
        cout << "-1\n";
        return;
    }

    int r = S;
    for (int i = (N-2)-(N-2)%blk; i >= 0; i -= blk) {
        vector<bitset<70001>> D{C[i/blk]};
        for (int j = i; j < min(i+blk, N-1); ++j) {
            D.push_back(D.back() | (D.back() << B[j].x));
        }

        for (int j = min(i+blk, N-1)-1; j >= i; --j) {
            if (r >= B[j].x && D[j-i][r - B[j].x]) {
                r -= B[j].x;
                Top[B[j].y] = true;
            }
        }
    }


    vector<pii> Ans(N);
    for (int i = 0; i < N; ++i) {
        if (i == 0 || Top[B[i-1].y]) {
            Ans[B[i].y] = {B[i].x, -1};
        } else {
            Ans[B[i].y] = {B[i].x - B[i-1].x, B[i-1].y};
        }
    }

    for (int i = 0; i < N; ++i) {
        cout << Ans[i].x;
        if (Ans[i].y == -1) cout << " 0 \n";
        else cout << " 1 " << Ans[i].y+1 << '\n';
    }
}
};
