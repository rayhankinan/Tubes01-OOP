#ifndef MATRIX_INTERFACE_HPP
#define MATRIX_INTERFACE_HPP

template<class T>
class Matrix {
    private:
        const int N, M;
        T *buffer;

    public:
        // tidak memerlukan default ctor (tidak ada list of matrix) dan assignment operator (N dan M konstan)
        Matrix(int, int); // user-defined ctor
        Matrix(const Matrix&); // cctor
        ~Matrix(); // dtor

        int getLength() const; // N getter
        int getWidth() const; // M getter
        T& operator()(int i, int j) const; // element getter
};

template<class T>
Matrix<T>::Matrix(int N, int M) : N(N), M(M) {
    this->buffer = new T[this->N][this->M];
}

template<class T>
Matrix<T>::Matrix(const Matrix& MT) : N(MT.N), M(MT.M) {
    this->buffer = new T[this->N][this->M];

    for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->M; j++) {
            this->buffer[i][j] = MT.buffer[i][j];
        }
    }
}

template<class T>
Matrix<T>::~Matrix() {
    delete[] this->buffer;
}

template<class T>
int Matrix<T>::getLength() const {
    return this->N;
}

template<class T>
int Matrix<T>::getWidth() const {
    return this->M;
}

template<class T>
T& Matrix<T>::operator()(int i, int j) const {
    return this->buffer[i][j];
}

#endif