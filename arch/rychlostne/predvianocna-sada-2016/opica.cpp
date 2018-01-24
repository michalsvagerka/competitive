#include "../l/lib.h"
#include "../l/util.h"

class opica {
public:


    vector<int> bestTime;
    vector<vector<int>> doubleEdges;
    vector<vector<int>> childCosts;

    int calcWorst(int vertex, int parent) {
        int ans = bestTime[vertex];
        for (int child : doubleEdges[vertex]) {
            if (child != parent) {
                int a = calcWorst(child, vertex) + 1;
                ans = max(ans, a);
                childCosts[vertex].push_back(a);
            }
        }
        // bestTime[vertex] = ans;
        return ans;
    }

    void propagate(int vertex, int parent, int fromParent) {
        fromParent = max(fromParent, bestTime[vertex]);
        bestTime[vertex] = max(bestTime[vertex], fromParent);
        int j = childCosts[vertex].size();
        if (j == 0) return;
        vector<int> pref(j,0), suf(j,0);
        for (int i = 1; i < j; ++i) {
            pref[i] = max(pref[i-1],childCosts[vertex][i-1]);
            suf[j-i-1] = max(suf[j-i], childCosts[vertex][j-i]);
        }

        int x = 0;
        for (int child : doubleEdges[vertex]) {
            if (child != parent) {
                propagate(child, vertex, max(fromParent, max(pref[x], suf[x])) + 1);
                x++;
            }
        }

        bestTime[vertex] = max(bestTime[vertex], *max_element(childCosts[vertex].begin(),childCosts[vertex].end()));
    }

    void solve(istream& cin, ostream& cout) {
        int N,M; cin >> N >> M;
        UnionFind U(N);
        vector<vector<int>> singleEdges(N);
        doubleEdges.resize(N);
        childCosts.resize(N);
        for (int i = 0; i < M; ++i) {
            int u, v, t; cin >> u >> v >> t;
            --u; --v;
            if (t == 1) {
                singleEdges[v].push_back(u);
            } else {
                doubleEdges[v].push_back(u);
                doubleEdges[u].push_back(v);
                if (!U.unite(u,v)) {
                    cout << "Infinite\n";
                    return;
                }
            }
        }

        vector<int> componentId(N);
        vector<vector<int>> component(N);
        for (int i = 0; i < N; ++i) {
            componentId[i] = U.find(i);
            component[componentId[i]].push_back(i);
        }

        vector<int> countOutgoing(N, 0);
        for (int u = 0; u < N; ++u) {
            for (int v : singleEdges[u]) {
                countOutgoing[componentId[v]]++;
            }
        }

        queue<int> Q;
        bestTime = vector<int>(N, -1);
        for (int i = 0; i < N; ++i) {
            if (i == componentId[i] && countOutgoing[i] == 0) {
                Q.push(i);
                for (int vertex:component[i]) {
                    bestTime[vertex] = 0;
                }
            }
        }

        while (!Q.empty()) {
            int I = Q.front(); Q.pop();
            int j = component[I].size();
            if (j > 1) {
                calcWorst(component[I][0], -1);
                propagate(component[I][0], -1, 0);
            }

            for (int vertex : component[I]) {
                for (int neighbor : singleEdges[vertex]) {
                    bestTime[neighbor] = max(bestTime[neighbor], bestTime[vertex]+1);
                    int target_comp = componentId[neighbor];
                    if (!--countOutgoing[target_comp]) {
                        Q.push(target_comp);
                    }
                }
            }
        }

        if (*min_element(bestTime.begin(),bestTime.end()) == -1) {
            cout << "Infinite\n";
            return;
        }

        cout << *max_element(bestTime.begin(),bestTime.end()) << endl;
    }
};
