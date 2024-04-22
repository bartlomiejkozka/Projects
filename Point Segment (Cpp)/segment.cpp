#include "segment.h"


//Point::Point(){
//}

Point::Point(double x, double y){
    setPoint(x,y);
}

Point::Point(const Point &p){ //gdy chcemy aby nowy obiekt klasy byl kopia juz istniejacego //new
    *this = p;      //bieżacy obiekt =
}

void Point::setPoint(double x, double y){
    setX(x);
    setY(y);
}

void Point::setPoint(const Point &p){   //new //gdy kopiujemy wartosci z istniejacego obiektu do nowego
    setX(p.getX());
    setY(p.getY());
}

void Point::Turn(double alpha){                      //trnasformacja rotacji (macierz obrotu)
    double x = mx * cos(alpha) - my * sin(alpha);           //obrot w przeciwnym ruchu niz
    double y = mx * sin(alpha) + my * cos(alpha);           //do wskazowek zegara
    mx = x;
    my = y;
}

void Point::Move(double vx, double vy){
    mx += vx;
    my += vy;
}

void Point::Move(const Point &p){   //new //przesuniecie wzgledem innego punktu juz istiejacego
    //mx += v.mx;
    //my += v.my;
    setX(getX() + p.getX());
    setY(getY() + p.getY());
}

std::ostream& operator <<(std::ostream& out, const Point &point){
    out << '[' << point.getX() << ',' << point.getY() << ']';
    return out;
}
std::istream& operator >>(std::istream& in, Point& point){
    double x;
    in >> x, point.setX( x );
    in >> x, point.setY( x );
    return in;
}



//=====================================================



//Segment::Segment(){
//}

Segment::Segment(double x1, double y1, double x2, double y2){
    setSegm(x1, y1, x2, y2);
}

Segment::Segment(const Point &pt1, const Point &pt2)    //new   //lista inicjalizacyjna
        : mPt1(pt1), mPt2(pt2)    //poleklasy( wartosc ), poleklasy( wartosc )
{
    //mPt1 = pt1;
    //mPt2 = pt2;
}

Segment::Segment(const Segment &seg){   //new
    *this = seg;
}

void Segment::setSegm(double x1, double y1, double x2, double y2){
    setPt1(x1, y1);
    setPt2(x2, y2);
}

void Segment::setSegm(const Point &pt1, const Point &pt2){
    setPt1(pt1.mx, pt1.my);
    setPt2(pt2.mx, pt2.my);
}

void Segment::Move(double vx,double vy){
    mPt1.Move(vx, vy);
    mPt2.Move(vx, vy);

    //~ mPt1.mx += vx;
    //~ mPt1.my += vy;
    //~ mPt2.mx += vx;
    //~ mPt2.my += vy;
}

void Segment::Move(const Point &p){
    setPt1(getPt1().mx + p.mx, getPt1().my + p.my);
    setPt2(getPt2().mx + p.mx, getPt2().my + p.my);
}

void Segment::Rotate(int alpha){
    double radians = Convert_deg_to_rad(alpha);

    Point mp = Midpoint();
    mp.Turn(M_PI);

    mPt1.Move(mp);
    mPt2.Move(mp);

    mPt1.Turn(radians);
    mPt2.Turn(radians);


    mPt1.Move(mp);
    mPt2.Move(mp);
}

std::ostream& operator <<(std::ostream& out, const Segment& seg){
    out << "[" << seg.getPt1().mx << "," << seg.getPt1().my << "]--[" << seg.getPt2().mx << "," << seg.getPt2().my << "]";
    return out;
}
std::istream& operator >>(std::istream& in, Segment& seg){
    double x; double y;
    in >> x >> y;
    seg.setPt1(x, y);
    in >> x >> y;
    seg.setPt2(x, y);
    return in;
}

Point Segment::Midpoint() const{
    return Point(
            (mPt1.mx + mPt2.mx)/2,
            (mPt1.my + mPt2.my)/2
            );
}

Segment& Segment::operator = (const Segment &seg){
    mPt1 = seg.mPt1;
    mPt2 = seg.mPt2;
    return *this;
}