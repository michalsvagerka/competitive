#include "lib.h"

// DINIC MAX-FLOW ALGORITHM. LOOK ELSEWHERE
template<typename T> struct Dinic {
	ui V, E;
	std::vector<ui> LastEdge, EdgeToProcess, BfsDistance, PrevEdge, EdgeTarget;
	std::vector<T> Capacity, Residual;

	Dinic(ui v, ui e = 0) : V(v), E(0), LastEdge(V, ui(-1)), BfsDistance(V), EdgeToProcess(V) {
		Capacity.reserve(2*e);
		Residual.reserve(2*e);
		EdgeTarget.reserve(2*e);
		PrevEdge.reserve(2*e);
	}

	void AddEdge(ui x, ui y, T c1 = 1, T c2 = 0) {
		EdgeTarget.push_back(y);
		Capacity.push_back(c1);
		Residual.push_back(c1);
		PrevEdge.push_back(LastEdge[x]);
		LastEdge[x] = E++;
		EdgeTarget.push_back(x);
		Capacity.push_back(c2);
		Residual.push_back(c2);
		PrevEdge.push_back(LastEdge[y]);
		LastEdge[y] = E++;
	}

	T push(int x, int v, T flow) {
		if (x == v) return flow;
		for (ui &e = EdgeToProcess[x]; e != -1; e = PrevEdge[e]) {
			ui y = EdgeTarget[e];
			if (Residual[e] && BfsDistance[x] + 1 == BfsDistance[y]) {
				if (T f = push(y, v, min(flow, Residual[e]))) {
					Residual[e] -= f;
					Residual[e ^ 1] += f;
					return f;
				}
			}
		}
		return 0;
	}

	T GetMaxFlow(int u, int v) {
		T ret = 0;
		while (true) {
			fill(BfsDistance.begin(), BfsDistance.end(), (ui)-1);
			BfsDistance[u] = 0;
			std::queue<int> Q{{u}};
			while (!Q.empty()) {
				int x = Q.front(); Q.pop();
				for (int e = LastEdge[x]; e != ui(-1); e = PrevEdge[e]) {
					ui y = EdgeTarget[e];
					if (Residual[e] && BfsDistance[y] == ui(-1)) {
						Q.push(y);
						BfsDistance[y] = BfsDistance[x] + 1;
					}
				}

			}

			if (BfsDistance[v] == ui(-1)) break;
			copy(LastEdge.begin(), LastEdge.end(), EdgeToProcess.begin());
			while (T f = push(u, v, std::numeric_limits<T>::max())) ret += f;
		}

		return ret;
	}

	std::vector<bool> GetMinCut(int u) {
		std::queue<int> Q;
		Q.push(u);
		vector<bool> R(V, false);
		R[u] = true;
		while (!Q.empty()) {
			int x = Q.front();
			Q.pop();
			for (int e = LastEdge[x]; e != -1; e = PrevEdge[e]) {
				int y = EdgeTarget[e];
				if (!R[y] && Residual[e] > 0) {
					Q.push(y);
					R[y] = true;
				}
			}
		}
		return R;
	}

	vector<std::tuple<ui, ui, T>> GetEdgesWithFlow() {
		vector<std::tuple<ui, ui, T>> Ans;
		for (ui u = 0; u < V; ++u) {
			for (ui e = LastEdge[u]; e != ui(-1); e = PrevEdge[e]) {
				if (Residual[e] < Capacity[e]) {
					Ans.push_back({u, EdgeTarget[e], Capacity[e] - Residual[e]});
				}
			}
		}
		return Ans;
	};
};
// DINIC MAX-FLOW ALGORITHM