#include "../l/lib.h"
#include "../l/flow.h"

class rhombina {
public:
    void solve(istream& cin, ostream& cout) {
		int S,V; cin >> S >> V;
		int Z; cin >> Z;
		vector2<bool> U(S,V,true);
		for (int i = 0; i < Z; ++i) {
			int s,v; cin >> s >> v;
			U[s][v] = false;
		}
		PushRelabel<int> R(S*V+2);
		for (int s = 0; s < S; ++s) {
			for (int v = 0; v < V; ++v) {
				if ((s+v)%2 == 0) {
					if (s > 0) R.AddEdge(v*S + s, v*S + s - 1);
					if (s < S-1) R.AddEdge(v*S + s, v*S + s + 1);
					if (v > 0) R.AddEdge(v*S + s, v*S + s - S);
					if (U[s][v]) R.AddEdge(S*V, v*S+s);
				} else if (U[s][v]) R.AddEdge(v*S+s, S*V+1);
			}
		}
		cout << R.GetMaxFlow(V*S, V*S+1) << endl;
    }
};
