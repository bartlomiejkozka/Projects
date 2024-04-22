#include <iostream>
#pragma once

#ifndef M_PI
    #define M_PI 3.141592653589793
#endif

struct Point{
    double mx;
    double my;

    //Point();
    Point(double x=0, double y=0);
    Point(const Point &p);  //new //do kopiowania

    void setX(double x);
    void setY(double y);

    void setPoint(const Point &p);  //new
    void setPoint(double x, double y);

    int getX() const;
    int getY() const;

    void Turn(double alpha);

    void Move( double vx, double vy);
    void Move(const Point &vecotr);     //new

    friend std::ostream& operator <<(std::ostream& out, const Point& point);
    friend std::istream& operator >>(std::istream& in, Point& point);
};


class Segment{

private:
    Point mPt1;
    Point mPt2;

public:
    //Segment();
    Segment(double x1=0, double y1=0, double x2=0, double y2=0);
    Segment(const Point &pt1, const Point &pt2);    //new //ustawianie wartosic na podtawie dwoch juz istniejacych ptk.
    Segment(const Segment &seg);    //new do kopiowania

    void setPt1(double x1, double y1);
    void setPt1(const Point &pt1);    //new

    void setPt2(const Point &pt2);    //new
    void setPt2(double x2, double y2);

    void setSegm(double x1, double y1, double x2, double y2);
    void setSegm(const Point &pt1, const Point &pt2);   //new

    const Point &getPt1() const;
    const Point &getPt2() const;

    void Move(double vx,double vy);
    void Move(const Point &p);

    void Rotate(int alpha);     //w stopniach

    friend std::ostream& operator <<(std::ostream& out, const Segment& seg);
    friend std::istream& operator >>(std::istream& in, Segment& seg);

    Segment& operator = (const Segment &seg);   //new

private:
    double Convert_deg_to_rad(int degrees);
    Point Midpoint() const;

};


//INLINE FUNCTIONS

inline void Point::setX(double x){
    mx = x;
}

inline void Point::setY(double y){
    my = y;
}

inline int Point::getX() const{
    return mx;
}

inline int Point::getY() const{
    return my;
}

//---------------------------------------------------

inline void Segment::setPt1(double x1, double y1){
    mPt1.mx = x1;
    mPt1.my = y1;
}

inline void Segment::setPt1(const Point &pt1){   //new
    mPt1 = pt1;
}

inline void Segment::setPt2(double x2, double y2){
    mPt2.mx = x2;
    mPt2.my = y2;
}

inline void Segment::setPt2(const Point &pt2){    //new
    mPt2 = pt2;
}

inline const Point& Segment::getPt1() const{
    return mPt1;
}

inline const Point& Segment::getPt2() const{
    return mPt2;
}

inline double Segment::Convert_deg_to_rad(int degrees){
    return degrees * (M_PI / 180.0);
}