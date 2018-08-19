#include "../l/lib.h"
 #include "../l/geo.h"

#include "../l/string.h"

class TaskE {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<Point<ll>> A(N), B(M);
    cin >> A >> B;
    Polygon<ll> C = convexhull(A);
    Polygon<ll> D = convexhull(B);

    if (C.doubleSignedArea() != D.doubleSignedArea() || C.size() != D.size()) {
        cout << "NO\n";
        return;
    }

    auto perform = [&](Polygon<ll> &P) {
        vector<ll> E;
        for (int i = 0; i < P.size(); ++i) {
            auto p = P[i], q = P[(i+1)%P.size()], r = P[(i+2)%P.size()];
            E.push_back(p.squaredDistance(q));
            E.push_back(p.squaredDistance(r));
            E.push_back(q.squaredDistance(r));
            E.push_back(-1);
        }
        return E;
    };

    auto E = perform(C), F = perform(D);
    for (int i = 0; i < 4*C.size(); ++i) E.push_back(E[i]);
    
    KMP<vector<ll>> K(F);
    auto Occ = K.search(E);
    
    cout << (Occ.empty() ? "NO\n" : "YES\n") << '\n';
}
};
