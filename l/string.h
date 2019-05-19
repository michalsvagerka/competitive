#ifndef MAJK_STRING_H
#define MAJK_STRING_H

template <typename Input> struct KMP {
    explicit KMP(const Input&W) : W(W), T(W.size(),-1) {
        for (int p=1,c=0; p<W.size(); ++p,++c) {
            if(W[p]==W[c]){T[p]=T[c];}
            else {T[p]=c;while(c>=0&&W[p]!=W[c])c=T[c];}
        }
    }

    vector<ui> search(const Input&S) {
        vector<ui> M;
        for (ui m=0,i=0; m+i < S.size();) {
            if (W[i] == S[m+i]) { if (i + 1 < W.size()) { ++i; continue; } else M.push_back(m); }
            m += i - T[i];
            i = ui(max(T[i],0));
        }
        return M;
    }

    template <typename Character>
    int advance(int i, Character ch) {
        while (i != -1) {
            if (W[i] == ch) return i+1;
            i = T[i];
        }
        return 0;
    }

    Input W;
    vector<int> T;
};

template <typename Input>
vector<int> PrefixFunction(const Input &S) {
    int N = S.length();
    vector<int> P(N);
    for (int i = 1; i < N; i++) {
        int j = P[i-1];
        while (j > 0 && S[i] != S[j]) j = P[j-1];
        j += (S[i] == S[j]);
        P[i] = j;
    }
    return P;
}

#endif //MAJK_STRING_H
