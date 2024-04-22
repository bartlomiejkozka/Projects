#include "Matrix.h"

Matrix::Matrix(int nRow, int nCol, double nInitVal){
    m_nRow = nRow;
    m_pData = new(std::nothrow) Vector[nRow];
    if(!m_pData) std::cerr << "create Matrix: allocation error";

    for(int i = 0; i < nRow; i++)
        m_pData[i] = Vector(nCol, nInitVal);
}

Matrix::Matrix(const Matrix &m){
    m_pData = nullptr;
    m_nRow = 0;
    *this = m;

}

Matrix::~Matrix() {
    delete[] m_pData;
}

Matrix& Matrix::operator = (const Matrix& m){
    if(this->getRowNo() != m.getRowNo() || this->getColNo() != m.getColNo()){
        delete[] m_pData;
        m_pData = new(std::nothrow) Vector[m.getRowNo()];
        m_nRow = m.m_nRow;
    }

    for(int i = 0; i < getRowNo(); i++)
        m_pData[i] = m.m_pData[i];

    return *this;
}

std::istream& operator >> (std::istream &in, Matrix &m){
    double x;

    for(int i = 0; i < m.getColNo(); i++)
        for(int j = 0; j < m.getRowNo(); j++){
            in >> x;
            m.m_pData[i][j] = x;
        }

    //for(int i = 0; i < m.getRowNo(); i++){
        //in >> x;
        //m.m_pData[i] = x;
    //}

    return in;
}

std::ostream& operator << (std::ostream &out, const Matrix &m){
    out << '[';
    for(int i = 0; i < m.getRowNo(); i++) {
        out << m.m_pData[i] << ((i < m.getColNo() - 1) ? "," : "");
    }
    out << ']';
    return out;
}

Vector& Matrix::operator [] (int ix){
    return m_pData[ix];
}

const Vector& Matrix::operator [] (int ix) const{
    return m_pData[ix];
}

bool operator == (const Matrix &m1 ,const Matrix &m2){
    if(m1.getRowNo() != m2.getRowNo() || m1.getColNo() != m2.getColNo()){
        return false;
    }
    for(int i = 0; i < m1.getRowNo(); i++){
        if(m1[i] == m2[i]){
            continue;
        }
        else return false;
    }
    return true;
}

bool operator != (const Matrix &m1 ,const Matrix &m2){
    return !(m1 == m2);
}

const Matrix operator * (const Matrix &m1, const Matrix &m2){
    if(m1.getColNo() != m2.getRowNo()) {
        std::cerr << "multiplication: The matrix does not meet the condition to multiply\n";
        return 0;
    }
    Matrix res(m1.getRowNo(), m1.getColNo(), 0);
    for(int i = 0; i < m1.getRowNo(); i++)
        for(int j = 0; j < m2.getColNo(); j++)
            for(int k = 0; k < m2.getRowNo(); k++)
                res.m_pData[i][j] += m1.m_pData[i][k] * m2.m_pData[k][j];
    return res;
}

const Vector operator * (const Matrix &m, const Vector &v){
    if(m.getColNo() != v.GetDim()) {
        std::cerr << "multiplication: The matrix does not meet the condition to multiply\n";
        return 0;
    }
    Vector res(v.GetDim(), 0);
    for(int i = 0; i < m.getRowNo(); i++)
        for(int k = 0; k < m.getColNo(); k++)
            res[i] += m.m_pData[i][k] * v[k];

    return res;
}
