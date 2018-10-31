#ifndef MAJK_MINCOST_MAXFLOW
#define MAJK_MINCOST_MAXFLOW
#include "lib.h"

// MIN-COST MAX-FLOW ALGORITHM. LOOK ELSEWHERE
template<typename T = int, typename U = int>
struct MinCostMaxFlow{
    struct Edge{
        U c; T f; int to, rev;
        Edge(int _to, U _c, T _f, int _rev):c(_c), f(_f), to(_to), rev(_rev){}
    };
    static constexpr U INFCOST = numeric_limits<U>::max()/2;
    U eps, minEps;
    int N, source, sink;
    vector<vector<Edge>> G;
    vector<vector<int>> hs;
    vector<int> isq, cur, co, he;
    vector<T> ex;
    vector<U> h;
    MinCostMaxFlow(int N, int source, int sink): eps(0), minEps(std::numeric_limits<U>::max()), N(N), source(source), sink(sink), G(N){}
    void addEdge(int a, int b, T cap, U cost){
        eps = max(eps, abs(cost));
        if (cost != 0) minEps = min(minEps, abs(cost));
        G[a].emplace_back(b, cost, cap, G[b].size());
        G[b].emplace_back(a, -cost, 0, G[a].size()-1);
    }
    void add_flow(Edge& e, T f) {
        Edge &back = G[e.to][e.rev];
        if (!ex[e.to] && f) hs[he[e.to]].push_back(e.to);
        e.f -= f; ex[e.to] += f;
        back.f += f; ex[back.to] -= f;
    }
    T max_flow() {
        ex.assign(N, 0); he.assign(N, 0);
        hs.resize(2*N); co.assign(2*N, 0); cur.assign(N, 0);
        he[source] = N;
        ex[sink] = 1;
        co[0] = N-1;
        for(auto &e:G[source]) add_flow(e, e.f);
        if(hs[0].size())
            for (int hi = 0; hi>=0; ) {
                int u = hs[hi].back();
                hs[hi].pop_back();
                while (ex[u] > 0) { // discharge u
                    if (cur[u] == G[u].size()) {
                        he[u] = std::numeric_limits<int>::max();
                        for(int i=0;i<G[u].size();++i){
                            auto &e = G[u][i];
                            if (e.f && he[u] - 1 > he[e.to]){
                                he[u] = he[e.to] + 1, cur[u] = i;
                            }
                        }
                        if (++co[he[u]], !--co[hi] && hi < N)
                            for(int i=0;i<N;++i)
                                if (hi < he[i] && he[i] < N){
                                    --co[he[i]];
                                    he[i] = N + 1;
                                }
                        hi = he[u];
                    } else if (G[u][cur[u]].f && he[u] == he[G[u][cur[u]].to]+1)
                        add_flow(G[u][cur[u]], min(ex[u], G[u][cur[u]].f));
                    else ++cur[u];
                }
                while (hi>=0 && hs[hi].empty()) --hi;
            }
        return -ex[source];
    }
    void push(Edge &e, T amt){
        if(e.f < amt) amt=e.f;
        e.f-=amt; ex[e.to]+=amt;
        G[e.to][e.rev].f+=amt; ex[G[e.to][e.rev].to]-=amt;
    }
    void relabel(int vertex){
        U newHeight = -INFCOST;
        for(int i=0;i<G[vertex].size();++i){
            Edge const&e = G[vertex][i];
            if(e.f && newHeight < h[e.to] - e.c){
                newHeight = h[e.to] - e.c;
                cur[vertex] = i;
            }
        }
        h[vertex] = newHeight - eps;
    }
    pair<T, U> minCostMaxFlow(){
        U retCost = 0;
        for(int i=0;i<N;++i)
            for(Edge &e:G[i])
                retCost += e.c*(e.f);
        //find max-flow
        T retFlow = max_flow();
        h.assign(N, 0); ex.assign(N, 0);
        isq.assign(N, 0); cur.assign(N,0);
        queue<int> q;
        minEps = min(1e-9, minEps/1e9);
        for(;eps>minEps;eps/=2){
            //refine
            fill(cur.begin(), cur.end(), 0);
            for(int i=0;i<N;++i)
                for(auto &e:G[i])
                    if(h[i] + e.c - h[e.to] < 0 && e.f) push(e, e.f);
            for(int i=0;i<N;++i){
                if(ex[i]>0){
                    q.push(i);
                    isq[i]=1;
                }
            }
            // make flow feasible
            while(!q.empty()){
                int u=q.front();q.pop();
                isq[u]=0;
                while(ex[u]>0){
                    if(cur[u] == G[u].size())
                        relabel(u);
                    for(int &i=cur[u], max_i = G[u].size();i<max_i;++i){
                        Edge &e=G[u][i];
                        if(h[u] + e.c - h[e.to] < 0){
                            push(e, ex[u]);
                            if(ex[e.to]>0 && isq[e.to]==0){
                                q.push(e.to);
                                isq[e.to]=1;
                            }
                            if(ex[u]==0) break;
                        }
                    }
                }
            }
        }
        for(int i=0;i<N;++i){
            for(Edge &e:G[i]){
                retCost -= e.c*(e.f);
            }
        }
        return {retFlow, retCost/2};
    }
    T getFlow(Edge const &e){
        return G[e.to][e.rev].f;
    }
};
// DINIC MAX-FLOW ALGORITHM
#endif