/** Immutable tree for range queries on idempotent operations (i.e. min, max).
 * Memory O(n log n)
 * Build O(n log n)
 * Query O(1) */
template <typename T, typename Op> class ConstTree {
public:
    explicit ConstTree(const vector<T>&V) : D(logceil(V.size())), N(V.size()), A{V}, L(N,0) {
        for (ui b = 1; b < D; ++b) {
            A.emplace_back(N-(1<<b)+1);
            for (ui i = 0; i + (1<<b) <= N; ++i) {
                A[b][i] = op(A[b-1][i], A[b-1][i+(1<<(b-1))]);
            }
        }
        for (ui i = 2; i < N; ++i) L[i] = L[i-1] + ((1<<L[i-1]) == i/2);
    }

    T get(ui i, ui j) const { //i,j is inclusive
        return op(A[L[j-i]][i], A[L[j-i]][j+1-(1<<L[j-i])]);
    }
private:
    Op op;
    ui D,N;
    vector<vector<T>> A;
    vector<ui> L;
};

template <typename F> struct MinOp { F operator()(F a, F b) const { return std::min(a,b); }};
template <typename F> struct MaxOp { F operator()(F a, F b) const { return std::max(a,b); }};