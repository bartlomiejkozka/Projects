#pragma once
#include <iostream>
#include "Vector.h"


class Matrix{
public:
    Matrix(int nRow=2, int nCol=2, double nInitVal=0);
    Matrix(const Matrix &m);

    virtual ~Matrix();

    int getColNo() const;
    int getRowNo() const;

public:
    Matrix& operator = (const Matrix& m);   // v1 = v2 = v3

    //input/output
    friend std::istream& operator >> (std::istream &in, Matrix &m);
    friend std::ostream& operator << (std::ostream &out, const Matrix &m);

    //indexation
    Vector &operator [] (int ix);                                           // v[1] = 2
    const Vector &operator [] (int ix) const;

    operator Vector* () const; //operator rzutowania na wsk. do wektora  (zwraca wsk. do tablicy wektorów)

    friend bool operator == (const Matrix &m1 ,const Matrix &m2);           // v1 == v2
    friend bool operator != (const Matrix &m1 ,const Matrix &m2);           // v1 != v2

    friend const Matrix operator * (const Matrix &m1, const Matrix &m2);          // v1 * v2
    friend const Vector operator * (const Matrix &m, const Vector &v);

private:
    int m_nRow;
    Vector* m_pData;
};



//============INLINE FUNCTION===============

inline int Matrix::getColNo() const{
    return m_pData[0].GetDim();
}
inline int Matrix::getRowNo() const{
    return m_nRow;
}
inline Matrix::operator Vector* () const{
    return m_pData;
}
