#ifndef MAJK_SUBSET_H
#define MAJK_SUBSET_H

class SubsetIterator {
public:
    SubsetIterator(int mask, int submask) : mask(mask), submask(submask) {}
    SubsetIterator& operator++() { submask = (submask - 1) & mask; return *this; }
    inline bool operator==(const SubsetIterator& o) const { return submask == o.submask; }
    inline bool operator!=(const SubsetIterator& o) const { return submask != o.submask; }
    inline int operator*() const { return mask^submask; }
private:
    int mask, submask;
};

class SubsetRange {
public:
    explicit SubsetRange(int mask) : mask(mask) {}
    SubsetIterator begin() const { return SubsetIterator(mask, mask); }
    SubsetIterator end() const { return SubsetIterator(mask, 0); }
private:
    int mask;
};

SubsetRange subsets(int mask) { return SubsetRange(mask); }

template <typename T>
void zetaTransform(vector<T>&A, int N = 0) {
    while ((1<<N) < int(A.size())) ++N;
    assert((1<<N) == int(A.size()));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < (1<<N); ++j) {
            if (j&1<<i) A[j] += A[j^1<<i];
        }
    }
}

template <typename T>
void oddNegateTransform(vector<T>&A) {
    for (int i = 0; i < int(A.size()); ++i) if (__builtin_popcount(i)&1) A[i] = -A[i];
}

template <typename T>
void moebiusTransform(vector<T>&A, int N = 0) {
    oddNegateTransform(A);
    zetaTransform(A);
    oddNegateTransform(A);
}

template <typename T>
vector<vector<T>> rankBySize(const vector<T>& A, int N = 0) {
    while ((1<<N) < int(A.size())) ++N;
    assert((1<<N) == int(A.size()));

    vector2<T> B(N+1, 1<<N);
    for (int i = 0; i < (1<<N); ++i) B[__builtin_popcount(i)][i] = A[i];
    return B;
}

template <typename T>
vector<vector<T>> rankedZetaTransform(const vector<T>&A, int N = 0) {
    while ((1<<N) < int(A.size())) ++N;
    assert((1<<N) == int(A.size()));

    auto B = rankBySize(A);
    for (auto &BB: B) zetaTransform(BB);
    return B;
}

template <typename T>
vector<T> subsetConvolution(const vector<T>&A, const vector<T>&B, int N = 0) {
    while ((1<<N) < int(A.size())) ++N;
    assert((1<<N) == int(A.size()));
    assert(int(A.size()) == int(B.size()));

    auto rankedA = rankBySize(A);
    auto rankedB = rankBySize(B);
    for (auto & AA: rankedA) zetaTransform(AA);
    for (auto & BB: rankedB) zetaTransform(BB);

    vector2<T> C(N+1, 1<<N);
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j+i <= N; ++j) {
            for (int k = 0; k < 1<<N; ++k) {
                C[j+i][k] += rankedA[i][k] * rankedB[j][k];
            }
        }
    }

    for (auto &CC: C) moebiusTransform(CC);

    vector<T> Answer(1<<N);
    for (int i = 0; i < 1<<N; ++i) Answer[i] = C[__builtin_popcount(i)][i];
    return Answer;
}

#endif //MAJK_SUBSET_H
