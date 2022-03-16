#ifndef MATRIX_INTERFACE_HPP
#define MATRIX_INTERFACE_HPP

#include "../exception/matrixExceptionInterface.hpp"
#include "extractNumber.hpp"
#include <string>
using namespace std;

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
        T& getElement(int, int) const; // element getter
        T& getSlot(string slotID) const; // slot getter
        void setElement(int, int, T); // element setter
        T& operator()(int, int) const; // element getter
        T& operator[](string) const; // element getter with slotID
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

//getter element matrix
template<class T>
T& Matrix<T>::getElement(int i, int j) const {
    if (i < 0 || i >= this->N || j < 0 || j >= this->M) {
        throw MatrixIndexOutOfBoundsException(i, j);
    }
    else{
        return this->buffer[i][j];
    }
}
template<class T>
T& Matrix<T>::getSlot(string slotID) const {
    int slot = getNumberFromString(slotID);
    int i = slotID/9;
    int j = slotID%9;

    if (i >= this->N || j >= this->M) {
        throw MatrixException(0);
        
    } else {
        return this->buffer[i][j];
    }
}

//setter element matrix row i col j
template<class T>
void Matrix<T>::setElement(int i, int j, T value) {
    if (i < 0 || i >= this->N || j < 0 || j >= this->M) {
        throw MatrixIndexOutOfBoundsException(i, j);
    }
    else{
        this->buffer[i][j] = value;
    }
}

template<class T>
T& Matrix<T>::operator()(int i, int j) const {
    if (i >= this->N || j >= this->M) {
        throw MatrixException(0);
        
    } else {
        return this->buffer[i][j];
    }
}

template<class T>
T& Matrix<T>::operator[](string slotID) const {

}

#endif