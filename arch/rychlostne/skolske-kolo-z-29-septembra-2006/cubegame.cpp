#include "../../../l/lib.h"
// #include "../l/mod.h"

class cubegame {
public:
    typedef vector<pair<char,int>> state;
    vector<int> B;

    pair<state,int> addTo(state s, int pos, char c) {
        if (s[pos].x == c) { s[pos].y = min(5,s[pos].y+1); return {s,0}; }
        else {
            int score = B[s[pos].y];
            s.erase(s.begin()+pos);
            s.push_back({c,1});
            sort(s.begin(),s.end());
            return {s,score};
        }
    }

    void solve(istream& cin, ostream& cout) {
        B.resize(6);
        for (int i = 0; i < 5; ++i) cin >> B[i+1];
        int N; cin >> N;
        map<state,int> M;
        M[{{' ',0},{' ',0},{' ',0}}] = 0;
        string S; cin >> S;
        for (char s:S) {
            map<state,int> W;
            for (auto&m:M) {
                for (int i = 0; i < 3; ++i) {
                    auto w = addTo(m.x, i, s);
                    W[w.x] = max(W[w.x], m.y + w.y);
                }
            }
            swap(W,M);
        }

        int ans = 0;
        for (auto&m:M) {
            int score = m.y;
            for (int i = 0; i < 3; ++i) {
                score += B[m.x[i].y];
            }
            ans = max(ans, score);
        }
        cout << ans << endl;
    }
};
