#include <iostream>
#include "Vector.h"
#include "Matrix.h"

int main() {
    //test operatora przypisania "=" (kopia wketora)
    Vector v1(3,1);
    Vector v2(v1);
    std::cout << "Vector v1: "<< v1 << " = " << "Vector v2: " << v2 << std::endl;


    //test operatorow wej/wyj
    Vector v3(3,0);
    std::cout << "Podaj dane do wektora: ";
    std::cin >> v3;
    std::cout << "Nowo utworzony wktor v3 = " << v3 << std::endl;


    //test operator dodawania
    Vector v4(5, 2);
    Vector v5(5, 3);
    Vector v6 = v4 + v5;
    std::cout << v4 << " + " << v5 << " = " << v6 << std::endl;
    Vector v7 = v4 + 10;
    std::cout << v4 << " + 10 = " << v7 << std::endl;


    //test operatora odejmowania
    Vector v8(3, 2);
    Vector v9(3, 3);
    Vector v10 = v9 - v8;
    std::cout << v9 << " - " << v8 << " = " << v10 << std::endl;
    Vector v11 = v9 - 3;
    std::cout << v9 << " - 3 = " << v11 << std::endl;

    //test operatora mnozenia
    double x = v8 * v9;
    std::cout << v8 << " * " << v9 << " = " << x << std::endl;
    Vector v12 = v9 * 5;
    std::cout << v9 << " * 5 = " << v12 << std::endl;


    //rzutowanie
    double *p = (double*)v3;
    std::cout << "\nrzutowanie na p -- p[i] = " << *(p+1) << std::endl;


    //test indeksowanie
    Vector v13(6, 9);
    std::cout << "v13 = " << v13 << std::endl;
    v13[0] += 1;
    std::cout << "v13[0] + 1 = " << v13[0] << std::endl;
    v13[1] = v13[0] + v13[5];
    std::cout << "v13[1] = v13[0](value = 10) + v13[5](value = 9) = " << v13[1] << std::endl;


    //test operatora prownania
    Vector v14(10, 10);
    Vector v15(10, 10);
    bool y = v14 == v15;
    std::cout << "if " << v14 << " == " << v15 << " ?: " << y << std::endl;

    std::cout << "\n\n\n";
    //===================MATRIX=====================

    Matrix m1(4, 4, 7);
    Matrix m4(4,4,2);
    Matrix m2(4,2, 1);
    Matrix m5(m1);
    std::cout << m5 << std::endl;
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    std::cout << m4 << std::endl;
    m4 = m2;
    std::cout << m4 << std::endl;
    Matrix mnozenie = m1 * m4;
    std::cout << mnozenie << std::endl;
    return 0;
}
