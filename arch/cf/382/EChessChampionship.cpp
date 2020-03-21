#include "../l/lib.h"

class EChessChampionship {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> M >> N;
        ll W = ll(M)*ll(M-1);
        vector<pii> Pts(M);
        for (int i = 0; i < N; ++i) {
            cin >> Pts[i].x;
            W -= Pts[i].x;
            if (W < ll(M-i-1)*ll(M-i-2)) {
                cout << "no\n";
                return;
            }
            Pts[i].y = i;
        }

        for (int i = N; i < M; ++i) {
            Pts[i].x = min(ll(Pts[i-1].x), W - ll(M-i-1)*ll(M-i-2));
            Pts[i].y = i;
            W -= Pts[i].x;
        }


        if (W != 0) {
            cout << "no\n";
            return;
        }


        vector<string> S(M, string(M, '?'));
        for (int i = 0; i < M; ++i) S[i][i] = 'X';
        for (int i = 0; i < M; ++i) {
            sort(Pts.begin(),Pts.end());
            
            int left = M - i - 1;
            pii use = Pts.back();
            Pts.pop_back();

            for (int j = 0; j < use.x/2; ++j) {
                S[use.y][Pts[j].y] = 'W';
                S[Pts[j].y][use.y] = 'L';
            }

            if (use.x % 2 == 1) {
                S[use.y][Pts[use.x/2].y] = S[Pts[use.x/2].y][use.y] = 'D';
                Pts[use.x/2].x--;
            }

            for (int j = use.x/2 + use.x%2; j < left; ++j) {
                S[use.y][Pts[j].y] = 'L';
                S[Pts[j].y][use.y] = 'W';
                Pts[j].x -= 2;
            }
        }

        cout << "yes\n";
        for (string&s: S) cout << s << '\n';
    }
};
