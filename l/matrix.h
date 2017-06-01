#ifndef MAJK_MATRIX
#define MAJK_MATRIX
#include "lib.h"

template <typename T> class Matrix {
public:
	Matrix(size_t R, size_t C, T t=T()) : R(R), C(C), A(R,vector<T>(C,t)), def(t) {}
	size_t rows() const { return R; }
	size_t columns() const { return C; }
	bool isSquare() const { return R*C; }
	bool isIdentity() const {
		for (int i = 0; i < min(R,C); ++i) {
			for (int j = 0; j < min(R,C); ++j) {
				if (i == j && A[i][j] != 1) return false;
				if (i != j && A[i][j] != 0) return false;
			}
		}
		return true;
	}

	void addColumnsRight(size_t add, T t=T()) {
		for (int i = 0; i < R; ++i) {
			A[i].resize(C + add);
			for (size_t j = C; j < C+add; ++j) A[i][j] = t;
		}
		C += add;
	}

	void removeColumnsLeft(size_t rem) {
		for (size_t i = 0; i < R; ++i) A[i].erase(A[i].begin(), rem > A[i].size() ? A[i].end() : A[i].begin()+rem);
	}

	T determinant() const {
		if (!isSquare()) { throw std::runtime_error("Cannot compute determinant of a rectangular matrix"); }
		Matrix<T> tmp(*this);
		T ans = tmp.toReducedRowEchelon();
		if (tmp.isIdentity()) return ans;
		else return 0;
	}

	vector<int> solveFor(const vector<int> &b) {
		if (!isSquare()) { throw std::runtime_error("Cannot solve a rectangular matrix"); }
		if (b.size() != R) throw new std::runtime_error("Unable to solve linear equation, dimensions do not match");
		Matrix<T> tmp(*this);
		for (int i = 0; i < R; ++i) tmp.A[i].push_back(b[i]);
		++tmp.C;
		tmp.toReducedRowEchelon();
		if (!tmp.isIdentity()) throw std::runtime_error("Cannot solve a singular matrix");
		vector<int> Ans(R);
		for (int j = 0; j < R; ++j) Ans[j] = tmp.A[j].back();
		return Ans;
	}


	Matrix<T> & operator+=(const Matrix<T>&m) {
		if (R != m.R) throw std::runtime_error("Cannot add matrices of different height");
		if (C != m.C) throw std::runtime_error("Cannot add matrices of different width");
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				A[i][j] += m.A[i][j];
			}
		}
		return *this;
	}

	Matrix<T> & operator-=(const Matrix<T>&m) {
		if (R != m.R) throw std::runtime_error("Cannot substract matrices of different height");
		if (C != m.C) throw std::runtime_error("Cannot substract matrices of different width");
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				A[i][j] -= m.A[i][j];
			}
		}
		return *this;
	}

	Matrix<T> operator*(const Matrix<T>&m) const {
		if (C != m.R) throw std::runtime_error("Matrices incompatible for multiplication");
		Matrix<T> Ans(R, m.C, T(0));
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < m.C; ++j) {
				for (int k = 0; k < C; ++k) {
					Ans[i][j] += A[i][k] * m.A[k][j];
				}
			}
		}
		return Ans;
	}

	class Row {
	public:
		Row(Matrix<T>*M, size_t row) : M(M), row(row) {}
		T &operator[](size_t col) {
			if (col < 0 || col >= M->C) throw std::out_of_range("Invalid column ID");
			return M->A[row][col];
		}
		const T &operator[](size_t col) const {
			if (col < 0 || col >= M->C) throw std::out_of_range("Invalid column ID");
			return M->A[row][col];
		}
	private:
		Matrix<T> *M; size_t row;
	};

	Row operator[](size_t row) {
		if (row < 0 || row >= R) throw std::out_of_range("Invalid row ID");
		return Row(this, row);
	}

	const Row operator[](size_t row) const {
		if (row < 0 || row >= R) throw std::out_of_range("Invalid row ID");
		return Row(const_cast<Matrix<T>*>(this), row);
	}

	Matrix<T> transposed() const {
		Matrix<T> M(*this);
		M.transpose();
		return M;
	}

	Matrix<T> inverted() const {
		if (R != C) throw std::runtime_error("Matrix not square");
		Matrix<T> M(*this);
		M.invert();
		return M;
	}

	Matrix<T> &transpose() {
		A.resize(max(R,C));
		for (size_t i = 0; i < C; ++i) A[i].resize(max(R,C));
		for (size_t i = 0; i < R; ++i) {
			for (size_t j = i+1; j < C; ++j) swap(A[i][j], A[j][i]);
		}
		for (size_t i = 0; i < C; ++i) A[i].resize(R);
		A.resize(C);
		return *this;
	}

	Matrix<T> &invert() {
		addColumnsRight(C, def);
		for (size_t i = 0; i < R; ++i) A[i][R + i] = 1;
		toReducedRowEchelon();
		if (!isIdentity()) throw std::runtime_error("Matrix not invertible");
		removeColumnsLeft(C/2);
		return *this;
	}


private:
	T toReducedRowEchelon() {
		size_t pivot = 0;
		T factor = 1;
		for (size_t i = 0; i < C && pivot < R; ++i) {
			pair<T, size_t> Q = {A[pivot][i], pivot};
			for (size_t j = pivot+1; j < R; ++j) if (A[j][i] != 0) Q = {A[j][i], j};
			if (Q.x == 0) continue;
			if (Q.y != i) swap(A[Q.y], A[pivot]);
			for (size_t j = i+1; j < C; ++j) A[pivot][j] /= A[pivot][i];
			factor /= A[pivot][i];
			A[pivot][i] = 1;

			for (size_t j = 0; j < R; ++j) {
				if (j != pivot) {
					for (size_t k = i + 1; k < C; ++k) A[j][k] -= A[pivot][k] * A[j][i];
					A[j][i] = 0;
				}
			}

			++pivot;
		}
		return factor;
	}

	size_t R, C;
	vector<vector<T>> A;
	T def;
};

template<typename T>std::ostream &operator<<(std::ostream&os,const Matrix<T>&m) {
	for (size_t r = 0; r < m.rows(); ++r) for (size_t c = 0; c < m.columns(); ++c) os << m[r][c] << " \n"[c == m.columns()-1];
	return os;
}

#endif