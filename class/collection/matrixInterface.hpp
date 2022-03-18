#ifndef MATRIX_INTERFACE_HPP
#define MATRIX_INTERFACE_HPP

#include "../exception/matrixExceptionInterface.hpp"
// #include "extractNumber.hpp"
#include <string>
using namespace std;

template<class T>
class Matrix {
    private:
        int N, M;
        T **buffer;

    public:
        Matrix(); // default ctor
        Matrix(int, int); // user-defined ctor
        Matrix(const Matrix&); // cctor
        ~Matrix(); // dtor

        int getLength() const; // N getter
        int getWidth() const; // M getter
        void setELmt(int row, int col, T elmt); // set ELMT
        T& operator()(int, int) const; // element getter
        Matrix<T>& operator=(const Matrix<T>&);
        // T& virtual void operator[](string) const = 0; // element getter with slotID
};

template<class T>
Matrix<T>::Matrix() {
    this->N = 0;
    this->M = 0;
}

template<class T>
Matrix<T>::Matrix(int N, int M) : N(N), M(M) {
    this->buffer = new T*[N];

    for (int i = 0; i < N; i++) {
        this->buffer[i] = new T[M];
    }
}

template<class T>
Matrix<T>::Matrix(const Matrix& MT) : N(MT.N), M(MT.M) {
    this->buffer = new T*[this->N];

    for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->M; j++) {
            this->buffer[i][j] = MT.buffer[i][j];
        }
    }
}

template<class T>
Matrix<T>::~Matrix() {
    if (this->N == 0 || this->M == 0) {
        for (int i = 0; i < this->N; i++) {
            delete[] this->buffer[i];
        }
        delete[] this->buffer;
    }
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
void Matrix<T>::setELmt(int row, int col, T elmt){
    this->buffer[row][col] = elmt;
}

template<class T>
T& Matrix<T>::operator()(int i, int j) const {
    if (i >= this->N || j >= this->M) {
        // throw MatrixException(0);
        return this->buffer[i][j];
        
    } else {
        return this->buffer[i][j];
    }
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m) {
    this->N = m.getLength();
    this->M = m.getWidth();
    this->buffer = new T*[m.getLength()];
    for (int i = 0; i < this->N; i++) {
        this->buffer[i] = new T[m.getWidth()];
    }
    
    for (int i = 0; i < m.getLength(); i++) {
        for (int j = 0; j < m.getWidth(); j++) {
            this->buffer[i][j] = m.buffer[i][j];
        }
    }
    
    return *this;
}

#endif
