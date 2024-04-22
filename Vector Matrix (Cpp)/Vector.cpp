#include "Vector.h"

Vector::Vector(int nSize/* = 2*/, double nInitVal/* = 0*/){
    createVec(nSize);
    for(int i = 0; i < nSize; i++)
        m_pCoord[i] = nInitVal;
}

Vector::Vector(const Vector& v){
    m_pCoord = nullptr;     //nulptr == NULL
    m_nDim = 0;
    *this = v;
}

Vector::~Vector(){
    delete [] m_pCoord;
}

Vector& Vector::operator = (const Vector& v){
    if(this->GetDim() != v.GetDim()){
        //if(m_pCoord) delete [] m_pCoord; if statement is unnecessary - delete na wsk nullptr nie powoduje bledow
        delete [] m_pCoord;
        createVec(v.GetDim());
    }
    if(this == &v){
        std::cerr << "You have copied data from the same vector you have wanted to be copied to!!!\n"; //moglo by to
        return *this;                               //spowodowac nie obliczalne zachowanie kompiltora.
    }                                               //funkcja memcpy gdy kopjuje obiekt do tego samego obiektu powoduje
    copyVec(v);                                     //nieobliczalne zachowanie
    return *this;
}

std::istream& operator >> (std::istream &in, Vector &v){    //own
    double x;

    for(int i = 0; i<v.GetDim(); i++){
        in >> x;
        v.m_pCoord[i] = x;
    }

    return in;
}

std::ostream& operator << (std::ostream &out, const Vector &v){
    out << '[';
    for( int i=0; i<v.GetDim(); i++)
        out << v.m_pCoord[i] << ((i<v.GetDim()-1) ? "," : "");
    out << ']';

    return out;
}

const Vector operator + (const Vector &v1, const Vector &v2){
    Vector res(v1);
    return res += v2;
}

const Vector operator + (const Vector &v, double x){
    Vector res(v);
    return res += x;
}

const Vector operator + (double x, const Vector &v){    //możemy skorzystać z operatora "+" który powyżej
    return v + x;                                       // zdefiniowaliśmy.
}

Vector& Vector::operator += (const Vector& v){
    if(this->GetDim() != v.GetDim()){
        std::cerr << "operator: invalid vector sizes\n";
        return *this;
    }
    for(int i = 0; i < GetDim(); i++)
        m_pCoord[i] += v.m_pCoord[i];
    return *this;
}

Vector& Vector::operator += (double x){
    for(int i = 0; i < GetDim(); i++)
        m_pCoord[i] += x;

    return *this;
}

const Vector operator - (const Vector &v1, const Vector &v2){       //own
    Vector res(v1);
    return res -= v2;
}

const Vector operator - (const Vector &v, double x){            //own
    Vector res(v);
    return res -= x;
}

Vector& Vector::operator -= (const Vector& v){                  //own
    if(GetDim() != v.GetDim()){
        std::cerr << "operator: invalid vector sizes\n";
        return *this;
    }
    for(int i = 0; i<GetDim(); i++)
        m_pCoord[i] -= v.m_pCoord[i];
    return *this;
}

Vector& Vector::operator -= (double x){                     //own
    for(int i = 0; i<GetDim(); i++)
        m_pCoord[i] -= x;
    return *this;
}

const Vector operator - (const Vector &v){              //-v np. a = -b     //own
    Vector res(v);
    for(int i = 0; i<v.GetDim(); i++)
        res.m_pCoord[i] = -v.m_pCoord[i];
    return res;
}

const Vector operator * (const Vector &v, double x){    //own
    Vector res(v);
    return res *= x;
}

const Vector operator * (double x, const Vector &v){ //rowniez korzystamy z operatora "*" zdefiniowanego powyzej
    return v * x;
}

Vector& Vector::operator *= (double x){
    for(int i = 0; i<GetDim(); i++)
        m_pCoord[i] *= x;
    return *this;
}

/*const Vector*/double operator * (const Vector &v1, const Vector &v2){       //mnozenie skalarne         //own
    if(v1.GetDim() != v2.GetDim()){
        std::cerr << "operator: invalid vector sizes\n";
        return /*v1*/0.0;
    }
    double res = 0.0;
    for( int i = 0; i<v1.GetDim(); i++)
        res += v1.m_pCoord[i] * v2.m_pCoord[i];
    return res;
}

double& Vector::operator [] (int ix){       // v[1] = 2
    return m_pCoord[ix];
}

const double& Vector::operator [] (int ix) const{      // x = v[2]
    return m_pCoord[ix];
}

bool operator == (const Vector &v1 ,const Vector &v2) {   // v1 == v2
    if (v1.GetDim() != v2.GetDim()) {
        return false;
    }
    for (int i = 0; i <v1.GetDim(); i++){
        if(abs(v1.m_pCoord[i] - v2.m_pCoord[i]) < eps)
            continue;
        else return false;
    }
    return true;
}

bool operator != (const Vector &v1 ,const Vector &v2){     // v1 != v2
    return !(v1 == v2);
}



