#include "../l/lib.h"
// #include "../l/mod.h"

class twowords {
public:
void solve(istream& cin, ostream& cout) {
    vector<string> x(7);
    x[1] = "adeinorst";
    x[2] = "gmpu";
    x[3] = "bcfhlwy";
    x[4] = "kv";
    x[5] = "j";
    x[6] = "qxz";

    vector<int> C(128, 0);
    for (int i = 1; i <= 6; ++i) {
        for (char c:x[i]) {
            C[c] = i;
        }
    }

    int N; cin >> N;
    vector<string> W(N); cin >> W;
    vector<int> P(N, 0);
    unordered_map<string, int> Z;
    for (int i = 0; i < N; ++i) {
        for (char w:W[i]) P[i] += C[w];
        P[i] *= W[i].size();
        Z[W[i]] = P[i];
    }

    auto score = [&](const string &w) {
        auto it = Z.find(w);
        if (it == Z.end()) return -10000;
        else return it->y;
    };

    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        string B, R; cin >> B >> R;
        string S = B;
        sort(S.begin(),S.end());
        vector<int> Q(27, 0);
        for (char r:R) {
            if (r == '.') Q[26]++;
            else Q[r-'a']++;
        }

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            string &w = W[i];

            for (int j = 0; j <= int(w.size())-int(B.size()); ++j) {
                vector<int> L(26, 0);
                int stays = 0;
                for (int k = 0; k < w.size(); ++k) {
                    int d = k - j;
                    if (d < 0 || d >= int(B.size()) || B[d] != w[k]) {
                        L[w[k] - 'a']++;
                    } else {
                        stays++;
                    }
                }

                int miss = 0;
                for (int j = 0; j < 26; ++j) for (int k = Q[j]; k < L[j]; ++k) miss++;
                if (miss <= Q[26] && w != B) {
//                    cout << w << endl;
                    ans = max(ans, 20*(w.size()==7+stays) + (P[i]+1)/2);
                }
            }

            vector<int> L(26, 0);
            for (char ww:w) L[ww-'a']++;
            string miss;
            for (int j = 0; j < 26; ++j) for (int k = Q[j]; k < L[j]; ++k) miss += char('a'+j);

            if (miss.size() > Q[26]+1) continue;
            if (miss.size() <= Q[26]) {
                // cover a letter
                for (int j = 0; j < B.size(); ++j) {
                    char orig = B[j];
                    for (char ww:w) {
                        if (orig != ww) {
                            B[j] = ww;
                            ans = max(ans, 20*(w.size()==7) + P[i] + (score(B)+1)/2);
                        }
                    }
                    B[j] = orig;
                }

                // prepend
                for (char ww:w) {
                    string D = string(1, ww) + B;
                    ans = max(ans, 20*(w.size()==7) + P[i] + (score(D)+1)/2);
                }

                // append
                for (char ww:w) {
                    string D = B + string(1, ww);
                    ans = max(ans, 20*(w.size()==7) + P[i] + (score(D)+1)/2);
                }

                int l = -int(w.size())+1, r = B.size();
                string T(2, ' ');
                for (int d = l; d < r; ++d) {
                    int left = 20*(w.size()==7) + P[i], right = left;
                    for (int i = 0; i < w.size(); ++i) {
                        int b = i + d;
                        if (b >= 0 && b < int(B.size())) {
                            // to the left
                            T[0] = w[i]; T[1] = B[b];
                            left += score(T);

                            // to the right
                            T[0] = B[b]; T[1] = w[i];
                            right += score(T);
                        }
                    }
                    ans = max(ans, left);
                    ans = max(ans, right);
                }
            }

            // try any crossing
            string Z;
            set_intersection(S.begin(),S.end(),miss.begin(),miss.end(),back_inserter(Z));
            if (!Z.empty()) ans = max(ans, P[i] + 20*(w.size()==8));
        }

        cout << ans << endl;
    }


}
};
