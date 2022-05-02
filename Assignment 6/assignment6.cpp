// PHYS 30762 Programming in C++
// Assignment 6
// Clea Dronne - 29/04/2022
// Classes for 2D and 3D Shapes

#include<iostream>
#include<string>
#include<math.h> 

// Base class for shapes
class shape 
{
protected:
    double pi {3.14159265359};
public:
    virtual ~shape(){} 
    virtual double area()=0;
    virtual double volume()=0;
    virtual double perimeter()=0;
    virtual std::string shape_name()=0;
    virtual int dimension()=0;
};

// 2D shape
class shape_2d : public shape
{
public:
    double volume() {return 0;}
    int dimension() {return 2;}
    virtual ~shape_2d(){} 
};

// 3D shape
class shape_3d : public shape
{
public:
    double perimeter() {return 0;}
    virtual ~shape_3d(){} 
    int dimension() {return 3;}
};

// 2D shape: rectangle
class rectangle : public shape_2d
{
private:
    double length{};
    double width{};
public:
    rectangle(double l, double w) : length{l}, width{w} {}
    double area() {return (length*width);}
    double perimeter() {return 2*(length+width);}
    ~rectangle(){}
    std::string shape_name() {return "rectangle";}
};

// 2D shape: square
class square : public rectangle
{
public:
    square(double l) : rectangle(l,l){};
    std::string shape_name() {return "square";}
    ~square(){}
};

// 2D shape: ellipse
class ellipse : public shape_2d
{
private:
    double major_radius{};
    double minor_radius{};
public:
    ellipse(double ma, double mi) : major_radius{ma}, minor_radius{mi} {}
    double area() {return (pi*major_radius*minor_radius);}
    double perimeter() {return 2*pi*pow((pow(major_radius,2)+pow(minor_radius,2))/2.,1./2.);}
    std::string shape_name() {return "ellipse";}
    ~ellipse(){}
};

// 2D shape: circle
class circle: public ellipse
{
public:
    circle(double r) : ellipse(r,r) {};
    std::string shape_name() {return "circle";}
    ~circle(){}
};

// 3D shape: cuboid
class cuboid : public shape_3d
{
private:
    double length{};
    double width{};
    double height{};
public:
    cuboid(double l, double w, double h) : length{l}, width{w}, height{h} {}
    double volume() {return (length*width*height);}
    double area() {return (2*(length*width + length*height + width*height));}
    std::string shape_name() {return "cuboid";}
    ~cuboid(){}
};

// 3D shape: cube
class cube : public cuboid
{
public:
    cube(double l) : cuboid(l,l,l) {};
    std::string shape_name() {return "cube";}
    ~cube(){}
};

// 3D shape: ellipsoid
class ellipsoid : public shape_3d
{
private:
    double major_radius{};
    double minor_radius{};
    double height{};
public:
    ellipsoid(double ma, double mi, double h) : major_radius{ma}, minor_radius{mi}, height{h} {}
    double volume() {return (4./3.)*pi*major_radius*minor_radius*height;}
    double area();
    std::string shape_name() {return "ellipsoid";}
    ~ellipsoid(){}
};

double ellipsoid::area()
{
    double p{1.6075};
    return 4*pi*pow(((pow(major_radius*minor_radius,p)+pow(minor_radius*height,p)+pow(height*major_radius,p))/3.), 1/p);
}

// 3D shape: sphere
class sphere : public ellipsoid
{
private:
    double radius{};
public:
    sphere(double r) : ellipsoid(r,r,r) {};
    std::string shape_name() {return "sphere";}
    ~sphere(){}
};

// 3D shape: prism
class prism : public shape_3d
{
private:
    double height{};
    shape_2d *base{};
public:
    prism(double h, shape_2d *b) : height{h}, base{b} {}
    double volume() {return height*(base->area());}
    double area() {return (2*(base->area())+height*(base->perimeter()));}
    std::string shape_name() {return "prism";}
    ~prism(){delete base;}
};

int main() 
{
    // Initialze all 9 different types of shapes
    shape **shape_array = new shape*[9];
    shape_array[0] = new rectangle{5,7};
    shape_array[1] = new square{5};
    shape_array[2] = new ellipse{6,9};
    shape_array[3] = new circle{3};
    shape_array[4] = new cuboid{2,5,3};
    shape_array[5] = new cube {4};
    shape_array[6] = new ellipsoid {2,5,3};
    shape_array[7] = new sphere {2};
    shape_array[8] = new prism {3, new square{2}};

    // Output shape names, their area and volume
    std::cout.precision(4);
    for (size_t i{0}; i<9; i++) {
        std::cout << shape_array[i]->shape_name()<< ": area " << shape_array[i]->area();
        if (shape_array[i]->dimension()==3) {
            std::cout << ", volume " << shape_array[i]->volume() << std::endl;
        } else {
            std::cout << std::endl;
        }
        delete shape_array[i];
    }
    delete[] shape_array;

    return 0;
}