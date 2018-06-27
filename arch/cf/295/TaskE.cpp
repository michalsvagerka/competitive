#include "../../../l/lib.h"
#include "../../../l/bridges.h"

class TaskE {
public:

    bool find_cycle(map<int,vector<int>> &E, int target, int cur, vector<int> &path, set<int> &visited) {
        if (cur == target) return path.size() > 2;
        if (visited.find(cur) != visited.end()) return false;

        visited.insert(cur);
        path.push_back(cur);
        for (int q: E[cur]) {
            if (find_cycle(E, target, q, path, visited)) return true;
        }

        path.pop_back();
        return false;
    }

    bool find_path_to(map<int,vector<int>> &E, set<int> &target, int forbidden, int cur, vector<int> &path, set<int> &visited) {
        if (cur == forbidden) return false;
        if (target.find(cur) != target.end()) {
            path.push_back(cur);
            return true;
        }

        if (visited.find(cur) != visited.end()) return false;

        path.push_back(cur);
        visited.insert(cur);
        for (int q: E[cur]) {
            if (find_path_to(E,target,forbidden,q,path,visited)) return true;
        }

        path.pop_back();
        return false;
    }
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<vector<int>> E(N);
    for (int i = 0; i < M; ++i) {
        int u,v; cin >> u >> v; --u; --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    Graph G(E);
    vector<vector<pii>> B;
    bool found = false;
    auto lambda = [&](vector<pii>::iterator b,vector<pii>::iterator e) {
        if (found) return false;

        map<int,vector<int>> edges;
        for (auto it=b;it!=e;++it) {
            edges[it->x].push_back(it->y); edges[it->y].push_back(it->x);
        }


        int source = -1;
        for (auto&q:edges) if (q.y.size() >= 3) { source = q.x; break; }
        if (source == -1) return false;

        vector<int> cycle{source};
        set<int> visited,targets;
        find_cycle(edges, source, edges[source][0], cycle, visited);
        for (int vertex:cycle) targets.insert(vertex);

        for (int nextNeighbor:edges[source]) {
            if (cycle[1] != nextNeighbor && cycle.back() != nextNeighbor && !found) {
                vector<int> otherPath{source};
                visited.clear();
                find_path_to(edges, targets, source, nextNeighbor, otherPath, visited);

                int target = otherPath.back();
                vector<int> P1,P2,P3;
                int p = 0;
                while (cycle[p] != target) P1.push_back(cycle[p++]+1);
                P1.push_back(target+1);

                while (p < cycle.size()) P2.push_back(cycle[p++]+1);
                P2.push_back(source+1);
                reverse(P2.begin(),P2.end());

                for (int&t:otherPath) P3.push_back(t+1);

                cout << "YES\n";
                cout << P1.size() << ' ' << P1;
                cout << P2.size() << ' ' << P2;
                cout << P3.size() << ' ' << P3;
                return found = true;
            }
        }
        return false;
    };
    G.bicon(lambda);

    if (!found) {
        cout << "NO\n";
    }

}
};
