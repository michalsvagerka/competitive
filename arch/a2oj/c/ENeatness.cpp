#include "../l/lib.h"

class ENeatness {
public:
    int N, A, B, X, Y;
    string Sol;
    vector<vector<bool>> L, V;
    vector<int> LOX, HIX, LOY, HIY;

    constexpr char op(char c) {
        switch (c) {
            case 'L': return 'R';
            case 'R': return 'L';
            case 'D': return 'U';
            case 'U': return 'D';
            case '1': return '2';
            case '2': return '1';
            default: return 'x';
        }
    }

    void goUp() {
        if (A == 0) return;

        while (B > 0 && L[A][B-1]) {
            add('L');
            --B;
        }
        while (B < N-1 && !L[A-1][B] && L[A][B+1]) {
            add('R');
            ++B;
        }

        if (L[A-1][B]) {
            --A;
            add('U');
            goUp();
        }
    }

    void goDown() {
        if (A == N-1) return;

        while (B > 0 && L[A][B-1]) {
            add('L');
            --B;
        }
        while (B < N-1 && !L[A+1][B] && L[A][B+1]) {
            add('R');
            ++B;
        }

        if (L[A+1][B]) {
            ++A;
            add('D');
            goDown();
        }
    }

    void turnOffAndDown() {
        if (A == X) return;

        int b = -1;

        for (int i = 0; i < N; ++i) {
            if (L[A][i] && L[A+1][i]) {
                b = i;
            }
        }

        while (B > 0 && L[A][B-1]) { add('L'); --B; }
        while (B < N-1 && L[A][B+1]) {
            if (B != b) {
                add('2');
                L[A][B] = false;
            }
            add('R');
            ++B;
        }
        if (B != b) { add('2'); L[A][B] = false; }
        while (B != b) { add('L'); --B; }
        add('2'); L[A][B] = false;
        add('D'); ++A;
        turnOffAndDown();
    }


    void turnOffAndUp() {
        int b = Y;

        if (A != X) {
            for (int i = 0; i < N; ++i) {
                if (L[A][i] && L[A-1][i]) {
                    b = i;
                }
            }
        }

        while (B > 0 && L[A][B-1]) { add('L'); --B; }
        while (B < N-1 && L[A][B+1]) {
            if (B != b) {
                add('2');
                L[A][B] = false;
            }
            add('R');
            ++B;
        }
        if (B != b) { add('2'); L[A][B] = false; }
        while (B != b) { add('L'); --B; }
        add('2'); L[A][B] = false;
        if (A == X) return;
        add('U'); --A;
        turnOffAndUp();
    }


    void add(char c) {
        if (!Sol.empty() && Sol.back() == op(c)) Sol.pop_back();
        else Sol.push_back(c);
    }

    void bfs(int i, int j) {
        if (V[i][j]) return;
        V[i][j] = true;
        if (!L[i][j]) {
            add('1');
            L[i][j] = true;
            LOX[i] = min(LOX[i], j);
            HIX[i] = max(HIX[i], j);
            LOY[j] = min(LOY[j], i);
            HIY[j] = max(HIY[j], i);
        }

        if (LOX[i] < j) {
            add('L');
            bfs(i,j-1);
            add('R');
        }
        if (HIX[i] > j) {
            add('R');
            bfs(i,j+1);
            add('L');
        }
        if (LOY[j] < i) {
            add('U');
            bfs(i-1,j);
            add('D');
        }
        if (HIY[j] > i) {
            add('D');
            bfs(i+1,j);
            add('U');
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> A >> B;
        L = vector2<bool>(N, N);
        V = vector2<bool>(N, N, false);
        for (auto &l: L) {
            for (int i = 0; i < N; ++i) {
                bool c; cin >> c;
                l[i] = c;
            }
        }

        LOX.assign(N, N);
        LOY.assign(N, N);
        HIX.assign(N, -1);
        HIY.assign(N, -1);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (L[i][j]) {
                    LOX[i] = min(LOX[i], j);
                    HIX[i] = max(HIX[i], j);
                    LOY[j] = min(LOY[j], i);
                    HIY[j] = max(HIY[j], i);
                }
            }
        }

        --A; --B;
        X = A; Y = B;
        bfs(A,B);
        goUp();
        turnOffAndDown();
        goDown();
        turnOffAndUp();

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (L[i][j]) {
                    cout << "NO\n"; return;
                }
            }
        }
        cout << "YES\n" << Sol << '\n';
    }
};
