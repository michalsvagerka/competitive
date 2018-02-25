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

#endif //MAJK_STRING_H
