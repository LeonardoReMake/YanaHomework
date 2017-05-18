#include <iostream>

using namespace std;

class Point {
private:
    
    double x, y;
    static double dx, dy;
    
public:
    // дефолтный конструктор, для чтения с консоли
    Point(): x(0), y(0) {}
    
    Point(const double & _x, const double & _y): x(_x), y(_y) {}
    
    // конструктор копирования
    Point(const Point & pnt);
    
    // оператор присваивания
    Point & operator =(const Point & pnt);
    
    // операции
    Point operator +(const Point & pnt) const;
    Point operator -(const Point & pnt) const;
    
    // сокращенное присваивание
    Point & operator +=(const Point & pnt);
    Point & operator -=(const Point & pnt);
    
    // инекременты
    Point & operator ++(); // префиксный
    const Point operator ++(int); // постфиксный
    
    // декрименты
    Point & operator --(); // префиксный
    const Point operator --(int); // постфиксный
    
    // сеттеры
    void setX(const double & _x);
    void setY(const double & _y);
    
    // геттеры
    double getX() const;
    double getY() const;
    
    // операторы ввывода
    friend istream & operator >>(istream & in, Point & pnt);
    friend ostream & operator <<(ostream & in, const Point & pnt);
    
};

// POINT REALESATION

Point::Point(const Point & pnt) {
    this->x = pnt.x;
    this->y = pnt.y;
}

Point & Point::operator =(const Point & pnt) {
    if (this == &pnt)
        return *this;
    
    this->x = pnt.x;
    this->y = pnt.y;
    
    return *this;
}

Point Point::operator +(const Point & pnt) const {
    return Point((this->x + pnt.x), (this->y + pnt.y));
}

Point Point::operator -(const Point & pnt) const {
    return Point((this->x - pnt.x), (this->y - pnt.y));
}

Point & Point::operator +=(const Point & pnt) {
    this->x += pnt.x;
    this->y += pnt.y;
    return *this;
}

Point & Point::operator -=(const Point & pnt) {
    this->x -= pnt.x;
    this->y -= pnt.y;
    return *this;
}

Point & Point::operator ++() {
    this->x += Point::dx;
    this->y += Point::dy;
    return *this;
}

const Point Point::operator ++(int n) {
    Point pnt = *this;
    ++(*this);
    return pnt;
}

Point & Point::operator --() {
    this->x -= Point::dx;
    this->y -= Point::dy;
    return *this;
}

const Point Point::operator --(int n) {
    Point pnt = *this;
    --(*this);
    return pnt;
}

void Point::setX(const double & _x) {
    this->x = _x;
}

void Point::setY(const double & _y) {
    this->y = _y;
}

double Point::getX() const {
    return this->x;
}

double Point::getY() const {
    return this->y;
}

istream & operator >>(istream & in, Point & pnt) {
    in >> pnt.x;
    in >> pnt.y;
    return in;
}

ostream & operator <<(ostream & out, const Point & pnt) {
    out << "(" << pnt.x << ";" << pnt.y << ")";
    return out;
}


class Figura {
    // protected - потому что мы будем наследовать от этого класса фигуры
    // у которых будут общие поля
protected:
    
    Point cg, cz;
    
public:
    
    // конструктор
    Figura(const Point & p): cg(p), cz(p) {};
    
    // конструктор копирования
    Figura(const Figura & _figura) {
        this->cg = _figura.cg;
        this->cz = _figura.cz;
    };
    
    // оператор присваивания
    Figura & operator =(const Figura & _figura);
    
    // виртуальный метод
    virtual void show() {};
    
    void hide() {};
    
    void move(const Point &) {};
    
    void move() {};
    
    void trek() {};
    
    // обязательно должен быть виртуальный деструктор
    // чтобы при полиморфизме вызывался деструктор того класса
    // которым объект является на самом деле
    virtual ~Figura() {};
};

// FIGURA REALESATION

Figura & Figura::operator =(const Figura & _figura) {
    if (this == &_figura)
        return *this;
    
    this->cg = _figura.cg;
    this->cz = _figura.cz;
    
    return *this;
}


class Krug: public Figura {
private:
    
    double r;
    
public:
    
    // в списке инициализации можно указывать конструкторы базвого класса
    // в нашем случаи будет вызвать конструктор Figura и заполнять поля точек
    Krug(const Point & _p, const double & _r): Figura(_p), r(_r) {};
    
    Krug(const Krug & kr);
    
    Krug & operator =(const Krug & kr);
    
    virtual void show() {};
    
    void setR(const double & _r);
    
    double getR() const;
    
    ~Krug() {};
};

// KRUG REALESATION

Krug::Krug(const Krug & kr): Figura(kr.cg) {
    this->r = kr.r;
}

Krug & Krug::operator =(const Krug & kr) {
    // проверка на самоприсваивание
    if (this == &kr)
        return *this;
    
    this->cz = kr.cz;
    this->cg = kr.cg;
    this->r = kr.r;
    
    return *this;
}

void Krug::setR(const double & _r) {
    r = _r;
}

double Krug::getR() const {
    return r;
}


class Ellipse: public Figura {
private:
    
    double rx, ry;
    
public:
    
    Ellipse(const Point & _p, const double & _rx, const double & _ry): Figura(_p), rx(_rx), ry(_ry) {};
    
    Ellipse(const Ellipse & ellipse);
    
    Ellipse & operator =(const Ellipse & ellipse);
    
    virtual void show() {};
    
    void setRx(const double & _rx);
    void setRy(const double & _ry);
    
    double getRx() const;
    double getRy() const;
    
    ~Ellipse() {};
    
};

// ELLIPSE REALESATION

Ellipse::Ellipse(const Ellipse & ellipse): Figura(ellipse.cz), rx(ellipse.rx), ry(ellipse.ry) {}

Ellipse & Ellipse::operator =(const Ellipse & ellipse) {
    if (this == &ellipse)
        return *this;
    
    this->cg = ellipse.cg;
    this->cz = ellipse.cz;
    this->rx = ellipse.rx;
    this->ry = ellipse.ry;
    
    return *this;
}

void Ellipse::setRx(const double & _rx) {
    this->rx = _rx;
}

void Ellipse::setRy(const double & _ry) {
    this->ry = _ry;
}

double Ellipse::getRx() const {
    return this->rx;
}

double Ellipse::getRy() const {
    return this->ry;
}



class Box: public Figura {
private:
    
    double a, b;
    
public:
    
    Box(const Point & _p, const double & _a, const double & _b): Figura(_p), a(_a), b(_b) {};
    
    Box(const Box & box);
    
    Box & operator =(const Box & box);
    
    virtual void show() {};
    
    void setA(const double & _a);
    void setB(const double & _b);
    
    double getA() const;
    double getB() const;
    
    ~Box() {};
    
};

// BOX REALESATION

Box::Box(const Box & box): Figura(box.cg), a(box.a), b(box.b) {}

Box & Box::operator =(const Box & box) {
    if (this == &box)
        return *this;
    
    this->cg = box.cg;
    this->cz = box.cz;
    this->a = box.a;
    this->b = box.b;
    
    return *this;
}

void Box::setA(const double & _a) {
    this->a = _a;
}

void Box::setB(const double & _b) {
    this->b = _b;
}

double Box::getA() const {
    return this->a;
}

double Box::getB() const {
    return this->b;
}

// статические поля должны обязательно инициализированны глобально
double Point::dx = 1e-5;
double Point::dy = 1e-5;

int main(int argc, const char * argv[]) {
    
    return 0;
}
