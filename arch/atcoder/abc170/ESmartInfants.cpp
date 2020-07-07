#include "../../../l/lib.h"
constexpr int MX = 2e5+1;


class ESmartInfants {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<pii> A(N); cin >> A;
        multiset<int> cur;
        vector<multiset<int>> X(MX);
        for (int i = 0; i < N; ++i) {
            swap(A[i].x, A[i].y);
            A[i].x--;
            X[A[i].x].insert(A[i].y);
        }
        for (int i = 0; i < MX; ++i) {
            if (!X[i].empty()) {
                cur.insert(*X[i].rbegin());
            }
        }

        for (int i = 0; i < Q; ++i) {
            int a, b; cin >> a >> b;
            --a; --b;

            int c = A[a].x;
            if (b == c) {
                cout << *cur.begin() << '\n';
                continue;
            }
            cur.erase(cur.find(*X[c].rbegin()));
            if (!X[b].empty()) cur.erase(cur.find(*X[b].rbegin()));
            X[c].erase(X[c].find(A[a].y));
            A[a].x = b;
            X[b].insert(A[a].y);
            cur.insert(*X[b].rbegin());
            if (!X[c].empty()) cur.insert(*X[c].rbegin());

            cout << *cur.begin() << '\n';
        }


    }
};
