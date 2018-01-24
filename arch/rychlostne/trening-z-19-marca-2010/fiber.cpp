#include "../l/lib.h"
// #include "../l/mod.h"

class fiber {
public:
    struct Block {
        Block(int from, int to) : from(from), to(to), spot(to-from, 0), vacant(to-from) {};
        void put(int a, int b, int c) {
            a = max(a, from);
            b = min(b, to);
            if (a > b) return;
            else if (a == from && b == to) full += c;
            else {
                for (int i = a-from; i < b-from; ++i) {
                    if (!spot[i]) --vacant;
                    spot[i] += c;
                    if (!spot[i]) ++vacant;
                }
            }
        }

        int empty() const {
            return full ? 0 : vacant;
        }

        int from, to;
        int full, vacant;
        vector<int> spot;
    };


    vector<Block> B;
    int N, P;

    void add(int a,int b) {
        if (a < b) {
            for (auto &z:B) z.put(a, b, 1);
        } else {
            for (auto &z:B) z.put(a, N, 1);
            for (auto &z:B) z.put(0, b, 1);
        }
    }

    void remove(int a, int b) {
        if (a < b) {
            for (auto &z:B) z.put(a, b, -1);
        } else {
            for (auto &z:B) z.put(a, N, -1);
            for (auto &z:B) z.put(0, b, -1);
        }
    }

    int count() {
        int ret = 0;
        for (auto &z:B) ret += z.empty();
        return ret;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> P;

        int Q = sqrt(N);
        for (int i = 0; i < N; i+=Q) {
            B.emplace_back(i, min(i+Q, N));
        }
        int S = B.size();

        vector<vector<int>> E(N);
        for (int i = 0; i < P; ++i) {
            int a,b; cin >> a >> b;
            --a; --b;
            if (a>b) swap(a,b);
            E[a].push_back(b);
            E[b].push_back(a);
            add(a,b);
        }

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j : E[i]) {
                remove(i,j);
                add(j,i);
            }
//            cout << N-count() << '\n';
            ans = max(ans, count());
        }

        cout << N - ans << endl;
    }
};
