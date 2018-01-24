#include "../l/lib.h"
// #include "../l/mod.h"
#include <thread>

class TaskA {
public:
    struct Calc {
		string S; int K;
		int ans;
        void calc() {
			int N = S.size();
			bool sw = false;
			ans = 0;
			for (int i = 0; i < N-K+1; ++i) {
				if (S[i] == '-') {
					for (int j = i; j < i+K; ++j) {
						S[j] = "-+"[S[j] == '-'];
					}
					++ans;
				}
			}

			for (int i = N-K+1; i < N; ++i) {
				if (S[i] == '-') {
					ans = -1;
				}
			}
        }

        void read(istream& cin) {
            cin >> S; cin >> K;
        }

        void write(ostream &cout) {
            if (ans == -1) cout << "IMPOSSIBLE";
			else cout << ans;
            cout << endl;
        }
    };


	void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
		vector<Calc> C(T);
		for (auto &c: C) c.read(cin);

		std::atomic_int currentTest{0};
		vector<std::thread> threads;
		for (ui i = 0; i < 4; ++i) {
			threads.emplace_back(std::thread{[&]() mutable {
				int testId;
				while ((testId = currentTest++) < T) C[testId].calc();
			}});
		}

		for (auto & t : threads) t.join();

		for (int t = 0; t < T; ++t) {
            cout << "Case #" << t+1 << ": ";
			C[t].write(cout);
		}
	}
};
