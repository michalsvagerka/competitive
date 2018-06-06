#ifndef MAJK_MINCOST_MAXFLOW
#define MAJK_MINCOST_MAXFLOW
#include "lib.h"

// MIN-COST MAX-FLOW ALGORITHM. LOOK ELSEWHERE
template<typename T> struct MinCostMaxFlow {
    ui V, E;
    std::vector<ui> LastEdge, EdgeToProcess, BfsDistance, PrevEdge, EdgeTarget;
    std::vector<T> Capacity, Residual, Cost;

    MinCostMaxFlow(ui v, ui e = 0) : V(v), E(0), LastEdge(V, ui(-1)), BfsDistance(V), EdgeToProcess(V) {
        Capacity.reserve(2*e);
        Residual.reserve(2*e);
        EdgeTarget.reserve(2*e);
        PrevEdge.reserve(2*e);
        Cost.reserve(2*e);
    }

    void AddEdge(ui x, ui y, T capacity = 1, T cost = 0) {
        EdgeTarget.push_back(y);
        Capacity.push_back(capacity);
        Residual.push_back(capacity);
        Cost.push_back(cost);
        PrevEdge.push_back(LastEdge[x]);
        LastEdge[x] = E++;
        EdgeTarget.push_back(x);
        Capacity.push_back(0);
        Residual.push_back(0);
        Cost.push_back(-cost);
        PrevEdge.push_back(LastEdge[y]);
        LastEdge[y] = E++;
    }

    pair<T,T> push(ui source, ui sink) {
        minheap<pair<T,ui>> Q;
        vector<ui> ParentEdge(V, -1);
        vector<T> Distance(V, std::numeric_limits<T>::max());
        Q.push({0,source});
        Distance[source] = 0;
        while (!Q.empty()) {
            ui u = Q.top().y;
            T d = Q.top().x;
            Q.pop();
            if (u == sink) break;
            if (Distance[u] != d) continue;
            for (ui e = LastEdge[u]; e != -1; e = PrevEdge[e]) {
                int v = EdgeTarget[e];
                if (Residual[e] > 0 && Distance[v] > d + Cost[e]) {
                    Distance[v] = d + Cost[e];
                    ParentEdge[v] = e;
                    Q.push({Distance[v], v});
                }
            }
        }
        
        if (Distance[sink] == std::numeric_limits<T>::max()) return {0,0};
        T flow = std::numeric_limits<T>::max(), cost = 0;
        for (ui e = ParentEdge[sink]; e != -1; e = ParentEdge[EdgeTarget[e^1]]) {
            cost += Cost[e];
            flow = min(flow, Residual[e]);
        }

        for (ui e = ParentEdge[sink]; e != -1; e = ParentEdge[EdgeTarget[e^1]]) {
            Residual[e] -= flow;
            Residual[e^1] += flow;
        }

        return {flow,flow*cost};
    }

    pair<T,T> GetMaxFlow(int u, int v) {
        pair<T,T> ret = {0,0};
        while (true) {
            pair<T,T> f = push(u, v);
            if (f.x == 0) break;
            ret.x += f.x;
            ret.y += f.y;
        }

        return ret;
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
#endif