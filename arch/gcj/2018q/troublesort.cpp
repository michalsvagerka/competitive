#include "../../../l/lib.h"
// #include "../l/mod.h"

class troublesort {
public:
    struct Calc {
        int N, ans; vector<int> V;

        void calc() {
            vector<int> W[2];
            for (int i = 0; i < N; ++i) {
                W[i%2].push_back(V[i]);
            }
            ans = -1;
            sort(W[0].begin(),W[0].end());
            sort(W[1].begin(),W[1].end());
            for (int i = 0; i < N; ++i) {
                V[i] = W[i%2][i/2];
            }
            for (int i = 0; i < N-1; ++i) {
                if (V[i] > V[i+1]) {
                    ans = i;
                    break;
                }
            }
        }

        void read(istream& cin) {
            cin >> N;
            V.resize(N);
            cin >> V;
        }

        void write(ostream &cout) {
            if (ans == -1) cout << "OK";
            else cout << ans;
            cout << endl;
        }
    };


    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
		vector<Calc> C(T);
		for (auto &c: C) c.read(cin);
		for (auto &c: C) c.calc();
		for (int t = 0; t < T; ++t) {
            cout << "Case #" << t+1 << ": ";
			C[t].write(cout);
		}
	}
};
