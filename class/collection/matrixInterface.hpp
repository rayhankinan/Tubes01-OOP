#ifndef MATRIX_INTERFACE_HPP
#define MATRIX_INTERFACE_HPP

#include "../exception/matrixExceptionInterface.hpp"
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
        T& operator()(int, int) const; // index-based element getter
        T& operator[](string) const; // slotID-based element getter
        
        void setElmt(int, int, T); // index-based element setter
        void setElmt(string, T); // slotID-based element setter

        Matrix<T>& operator=(const Matrix<T>&); // assignment operator

        
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
T& Matrix<T>::operator()(int i, int j) const {
    if (i < 0 || i >= this->N || j < 0 || j >= this->M) {
        throw MatrixException(0);
    } else {
        return this->buffer[i][j];
    }
}

template<class T>
T& Matrix<T>::operator[](string slotID) const {
    char type = slotID[0];
    int num = stoi(slotID.erase(0,1));
    if (type == 'C' && 0 <= num && num <= 8) {
        int row = num / 3;
        int col = num % 3;
        return this->buffer[row][col];
    }
    else if (type == 'I' && 0 <= num && num <= 26) {
        int row = num / 9;
        int col = num % 9;
        return this->buffer[row][col];
    }
    else {
        throw MatrixException(1);
    }
}

template<class T>
<<<<<<< HEAD
void Matrix<T>::setElmt(int row, int col, T elmt) {
    if (row >= this->N || col >= this->M) {
=======
void Matrix<T>::setELmt(int row, int col, T elmt) {
    if (row < 0 || row >= this->N || col < 0 || col >= this->M) {
>>>>>>> edc0d30c79c63f9539270d79b31eddc27ef5d256
        throw MatrixException(0);
    } else {
        this->buffer[row][col] = elmt;
    }
}

template<class T>
void Matrix<T>::setElmt(string slotID, T elmt) {
    char type = slotID[0];
    int num = stoi(slotID.erase(0,1));
    if (type == 'C' && 0 <= num && num <= 8) {
        int row = num / 3;
        int col = num % 3;
        this->buffer[row][col] = elmt;
    }
    else if (type == 'I' && 0 <= num && num <= 26) {
        int row = num / 9;
        int col = num % 9;
        this->buffer[row][col] = elmt;
    }
    else {
        throw MatrixException(1);
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
