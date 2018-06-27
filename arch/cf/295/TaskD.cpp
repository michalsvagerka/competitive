#include "../../../l/lib.h"
 #include "../../../l/frac.h"

struct Type {
    vector<pii> add;
    pii ass;
};

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int K,N,M; cin >> K >> N >> M;
    vector<ll> A(K); cin >> A;

    vector<Type> T(K, {{},{-1, -1}});
    vector<int> Q(N);
    vector<pii> MLT;
    for (int i = 0; i < N; ++i) {
        int t,j,b; cin >> t >> j >> b;
        --j;
        Q[i] = t;
        if (t == 1) T[j].ass = max(T[j].ass, {b,i});
        if (t == 2) T[j].add.push_back({b,i});
        if (t == 3) MLT.push_back({b,i});
    }


    vector<pair<Fraction,int>> H;
    for (pii mult: MLT) H.push_back({{mult.x}, mult.y});
    for (int i = 0; i < K; ++i) {
        if (T[i].ass.x > A[i]) {
            T[i].add.push_back({T[i].ass.x - A[i], T[i].ass.y});
        }

        sort(T[i].add.begin(),T[i].add.end());
        reverse(T[i].add.begin(),T[i].add.end());
        for (pii a:T[i].add) {
            H.push_back({{A[i] + a.x, A[i]}, a.y});
            A[i] += a.x;
        }
    }

    sort(H.begin(),H.end());
    reverse(H.begin(),H.end());
    vector<bool> U(N, false);
    for (int i = 0; i < min(M,(int)H.size()); ++i) {
        U[H[i].y] = true;
    }

    vector<int> Ans;
    for (int i = 1; i <= 3; ++i) {
        for (int t = 0; t < N; ++t) {
            if (U[t] && Q[t] == i) Ans.push_back(t+1);
        }
    }
    cout << Ans.size() << '\n';
    cout << Ans;
}
};
