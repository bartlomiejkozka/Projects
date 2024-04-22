#include <iostream>
#include "segment.h"


int main(){

    Segment seg1(1, 2, -1,-2);
    std::cout << "seg1 = " << seg1 << std::endl;
    Segment seg2(seg1);
    std::cout << "seg2 = " << seg2 << std::endl;
    std::cout << "Wpisz nowe wspolrzedne odcinka seg2: ";
    std::cin >> seg2;
    std::cout << "seg2 = " << seg2 << std::endl;

    seg1 = seg2;
    std::cout << "nowe wspolrzedne seg1 (rowne seg2) = " << seg1 << std::endl;



//-------------------------------------------------------------
    //obrot odcinka:

    Segment seg;
    std::cout << "Podaj wsp odcinka x1 y1 x2 y2: ";
    std::cin >> seg;
    std::cout << "Podaj kat obrotu w stopniach: " ;
    int alpha = 0;
    std::cin >> alpha;

    std::cout << "Obrot odcinka: " << seg << " o kat " << alpha << std::endl;
    seg.Rotate( alpha );
    std::cout << seg << std::endl;

    Point new_Pt(10,2);
    Point new_Pt1;
    new_Pt1.setPoint(new_Pt);
    std::cout << "newPt1 = " << new_Pt1 << std::endl;
    return 0;
}
