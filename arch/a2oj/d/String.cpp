#include "../l/lib.h"
 #include "../l/suffixarray.h"


class String {
public:
void solve(istream& cin, ostream& cout) {
    string S; cin >> S;
    S += '$';
    SuffixArray<int, true> SA(S);
    vector<pii> D{{0, 0}};

//    cout << SA.LCP << SA.S;

    ll ans = 0;
    for (int i = 1; i < S.size(); ++i) {
//        cout << "Index " << SA.S[i] << endl;

        int b = i;

        while (!D.empty() && D.back().x > SA.LCP[i]) {
            pii r = D.back();
            b = r.y;
            D.pop_back();
//            cout << (r.x - max(D.back().x, SA.LCP[i])) << ' ' << i - r.y + 1 << endl;
            ans += (r.x - max(D.back().x, SA.LCP[i])) * ll(i - r.y + 1) * ll(i - r.y + 2) / 2;
        }

//        cout << S.size() - (SA.S[i] + max(SA.LCP[i], SA.LCP[i-1]) + 1) << ' ' << 1 << endl;
        ans += S.size() - (SA.S[i] + max(SA.LCP[i], SA.LCP[i-1]) + 1);
        D.push_back({SA.LCP[i], b});
    }

    cout << ans << endl;
}
};
