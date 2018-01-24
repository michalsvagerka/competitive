#include "../l/lib.h"
// #include "../l/mod.h"

class qmoves {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> S(N); cin >> S;
        vector2<int> K(N,N,0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (S[i][j] == 'W') {
                    for (int dx = -1; dx <= 1; ++dx) {
                        for (int dy = -1; dy <= 1; ++dy) {
                            if (dx == 0 && dy == 0) continue;
                            int x = i+dx, y = j+dy;
                            while (in(0,x,N)&&in(0,y,N)&&S[x][y]!='W') {
                                K[x][y]++;
                                if (S[x][y]=='B') break;
                                x += dx;
                                y += dy;
                            }
                        }
                    }
                }
            }
        }

        int a=0,b=0,c=0,d=0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                bool e = S[i][j]=='B';
                if (K[i][j] == 1) ++(e?c:a);
                else (e?d:b)+=K[i][j];
            }
        }
        cout << a << endl << b << endl << c << endl << d << endl;
    }
};
