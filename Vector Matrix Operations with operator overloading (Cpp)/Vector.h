#pragma once
#include <iostream>

#ifndef eps
    #define eps 1e-6
#endif

#define VERROR                  0x00
#define INDEX_OUT_OF_RANGE      0x01
#define ALLOCATION_ERROR        0x02
#define INCOMATTIBLE_SIZES      0x04

class Vector{
public: //constructor/destructor
    Vector(int nSize = 2, double nInitVal = 0);
    Vector(const Vector& v);
    virtual ~Vector();      //What is this?

    int GetDim() const;

public: //assignment
    Vector& operator = (const Vector& v);   // v1 = v2 = v3

    //input/output
    friend std::istream& operator >> (std::istream &in, Vector &v);
    friend std::ostream& operator << (std::ostream &out, const Vector &v);

    //============== operators
    // addition
    friend const Vector operator + (const Vector &v1, const Vector &v2);    // v = v1 + v2
    friend const Vector operator + (const Vector &v, double x);             // v + x
    friend const Vector operator + (double x, const Vector &v);             // x + v
    Vector &operator += (const Vector& v);                                  // v1 += v2
    Vector &operator += (double x);                                         // v1 += x

    //subtraction
    friend const Vector operator - (const Vector &v1, const Vector &v2);    // v = v1 - v2
    friend const Vector operator - (const Vector &v, double x);             // v - x
    Vector &operator -= (const Vector& v);                                  // v1 -= v2
    Vector &operator -= (double x);                                         // v1 -= x

    //unary minus
    friend const Vector operator - (const Vector &v);                       //-v

    //multiplication
    friend const Vector operator * (const Vector &v, double x);             // v * x
    friend const Vector operator * (double x, const Vector &v);             // x * v
    Vector &operator *= (double x);

    //scalar multiplication
    friend /*const Vector*/double operator * (const Vector &v1, const Vector &v2);    // v1 * v2

    //indexation
    double &operator [] (int ix);                                           // v[1] = 2
    const double &operator [] (int ix) const;                               // x = v[2]

    //comparison
    friend bool operator == (const Vector &v1 ,const Vector &v2);           // v1 == v2
    friend bool operator != (const Vector &v1 ,const Vector &v2);           // v1 != v2

    //cast
    operator double* () const;

private:
    int m_nDim;         //vector dimension
    double* m_pCoord;    //vector coordinates
    void createVec(int nDim);
    void copyVec(const Vector &v);
};







//===============INLINE FUNCTIONS

inline Vector::operator double* () const{
    return m_pCoord;
}
inline int Vector::GetDim() const{
    return m_nDim;
}
inline void Vector::createVec(int nDim) {
    if (nDim >= 2) {
        m_nDim = nDim;
        m_pCoord = new(std::nothrow) double[nDim];   //bez wyjatkow     //co to nothrow, cerr
        if(!m_pCoord) std::cerr << "createVec(): Allocation error\n";
    }
    else{
        std::cerr << "createVec(): invalid vector dimension";
        m_nDim = 0;
        m_pCoord = nullptr;
    }
}
inline void Vector::copyVec(const Vector &v){
    //for(int i = 0; i < GetDim(); i++)
        //m_pCoord[i] = v.m_pCoord[i];
    memcpy(m_pCoord, (double*)v, m_nDim*sizeof(double));
}

