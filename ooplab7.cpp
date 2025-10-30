#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>
#include <algorithm>

static double pi = 3.14;

class Shape
{
protected:
    char ner[20];
public:
    Shape(const char* n) {
        strncpy(ner, n, 19);
        ner[19] = '\0';
        std::cout << "Shape('" << ner << "') baiguulagdlaa.\n";
    }

    const char* getName() const { return ner; }

    virtual double findArea() const = 0;
    virtual double findPerimeter() const = 0;

    virtual ~Shape() {
        std::cout << "Shape('" << ner << "') ustlaa.\n";
    }
};

class shape2D : public Shape
{
public:
    shape2D(const char* n) : Shape(n) {
        std::cout << "  shape2D('" << n << "') baiguulagdlaa.\n";
    }

    ~shape2D() {
        std::cout << "  shape2D('" << getName() << "') ustlaa.\n";
    }
};

class Circle : public shape2D
{
private:
    int x, y, radius;
public:
    Circle(int cx, int cy, int r, const char* name) 
        : shape2D(name)  
    {
        x = cx; y = cy; radius = r;
        std::cout << "    Circle('" << name << "', r=" << r << ") baiguulagdlaa.\n";
    }

    double findArea() const override {
        return pi * radius * radius;
    }

    double findPerimeter() const override {
        return 2 * pi * radius;
    }

    ~Circle() {
        std::cout << "    Circle('" << getName() << "') ustlaa.\n";
    }
};

class Square : public shape2D
{
private:
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int side;
public:
    Square(int topLeftX, int topLeftY, int s, const char* name) 
        : shape2D(name)
    {
        side = s;
        x1 = topLeftX;           y1 = topLeftY;
        x2 = topLeftX + s;       y2 = topLeftY;
        x3 = topLeftX + s;       y3 = topLeftY + s;
        x4 = topLeftX;           y4 = topLeftY + s;
        std::cout << "    Square('" << name << "', side=" << s << ") baiguulagdlaa.\n";
    }

    double findArea() const override {
        return side * side;
    }

    double findPerimeter() const override {
        return 4 * side;
    }

    ~Square() {
        std::cout << "    Square('" << getName() << "') ustlaa.\n";
    }
};

class Triangle : public shape2D
{
private:
    int x1, y1, x2, y2, x3, y3;
    int side;
public:
    Triangle(int topX, int topY, int s, const char* name) 
        : shape2D(name)
    {
        side = s;
        double h = (sqrt(3.0)/2.0) * side;
        x1 = topX;                    y1 = topY;
        x2 = topX - side/2;           y2 = topY + (int)h;
        x3 = topX + side/2;           y3 = topY + (int)h;
        std::cout << "    Triangle('" << name << "', side=" << s << ") baiguulagdlaa.\n";
    }

    double findArea() const override {
        double h = (sqrt(3.0)/2.0) * side;
        return 0.5 * side * h;
    }

    double findPerimeter() const override {
        return 3 * side;
    }

    ~Triangle() {
        std::cout << "    Triangle('" << getName() << "') ustlaa.\n";
    }
};

Shape* createShape() {
    int type;
    std::cout << "\nYamar durs uusgeh ve? (1=Toirog, 2=Kvadrat, 3=Gurvaljin): ";
    std::cin >> type;

    int x, y, size;
    char name[20];

    std::cout << "Dursnii bairlaliin x: "; std::cin >> x;
    std::cout << "Dursnii bairlaliin y: "; std::cin >> y;
    std::cout << "Hemjee (radius/tal): "; std::cin >> size;
    std::cout << "Ner: "; std::cin.ignore(); std::cin.getline(name, 20);

    if (type == 1) return new Circle(x, y, size, name);
    else if (type == 2) return new Square(x, y, size, name);
    else if (type == 3) return new Triangle(x, y, size, name);
    else {
        std::cout << "Buruu songolt! Toirog uusgej baina...\n";
        return new Circle(x, y, size, "Aldaatai");
    }
}

int main()
{
    std::vector<Shape*> shapes;
    int n;

    std::cout << "Heden durs uusgeh ve? "; 
    std::cin >> n;

    std::cout << "\n=== Dursuud uusgej baina ===\n";
    for (int i = 0; i < n; i++) {
        std::cout << "\n--- " << (i+1) << "-r durs ---" << std::endl;
        shapes.push_back(createShape());
    }

    std::sort(shapes.begin(), shapes.end(), [](Shape* a, Shape* b) {
        return a->findArea() < b->findArea();
    });

    std::cout << "\n\n=== TAlbaigaar erembelsen dursuud ===\n";
    for (int i = 0; i < shapes.size(); i++) {
        std::cout << (i+1) << ". " << shapes[i]->getName()
                  << " → Talbai = " << shapes[i]->findArea()
                  << " | Perimetr = " << shapes[i]->findPerimeter() << "\n";
    }

    std::cout << "\n=== Dursuud ustgaj baina ===\n";
    for (Shape* s : shapes) {
        delete s;
    }

    return 0;
}