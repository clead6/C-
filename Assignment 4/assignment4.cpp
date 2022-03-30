// PHYS 30762 Programming in C++
// Assignment 4
// Clea Dronne - 17/03/2022
// Class for complex numbers

#include<iostream>
#include<cmath>
#include<string>

class complex
{
    // Make function to overload operator << and >> a friend
    friend std::ostream & operator<<(std::ostream &os, const complex &number);
    friend std::istream & operator>>(std::istream &is, complex &number);

private:
    double real, imag;
public:
    // Constructors & destructor
    complex(){real=imag=0;}
    complex(double real_part, double imag_part): real{real_part}, imag{imag_part} {};
    ~complex(){std::cout<< "Destroying" << std::endl;}

    // Return real component
    double get_real() const {return real;}

    // Return imaginary component
    double get_imag() const {return imag;}

    // Return modulus
    double get_modulus() const {return sqrt(pow(real,2)+pow(imag,2));}

    // Return argument
    double get_argument() const {return atan2(imag,real);}

    // Return complex conjugate
    complex get_conjugate() const {return {real,-imag};}
    
    // Overload + operator for addition 
    complex operator+(const complex &number) const 
    {
        return {real+number.real, imag+number.imag};
    }
    
    // Overload - operator for subtraction
    complex operator-(const complex &number) const
    {
        return {real-number.real, imag-number.imag};
    }

    // Overload * operator for multiplication, z1*z2
    complex operator*(const complex &number) const
    {
        return {real*number.real-imag*number.imag, real*number.imag+imag*number.real};
    }

    // Overload / operator for division, z1/z2
    complex operator/(const complex &number) const
    {
        return {((real)*(number.real)+(imag)*(number.imag))/(pow(number.real,2)+pow(number.imag,2)), ((imag)*(number.real)-(real)*(number.imag))/(pow(number.real,2)+pow(number.imag,2))};
    }

};

// Function to overload << operator for complex numbers
std::ostream & operator<<(std::ostream &os, const complex &number)
{
    if (number.imag>=0) {
        os<<number.real<<"+i"<<number.imag;
    } else {
        os<<number.real<<"-i"<<-number.imag;
    }
    return os;
}

// Function to overload >> operator for complex numbers
std::istream & operator>>(std::istream &is, complex &number)
{
    std::cout << "Input the real and imaginary parts of a complex number separated by a space ";
    is >> number.real >> number.imag;
    return is;
}

int main()
{  
    std::cout.precision(3);

    // Create two complex numbers
    complex a{3,4};
    complex b{1,-2};

    // Get real and imaginary component, modulus and argument
    double real_a = a.get_real();
    double imag_a = a.get_imag();
    double modulus_a = a.get_modulus();
    double argument_a = a.get_argument();

    // Get conjugate
    complex conjugate_a = a.get_conjugate();

    // Get sum, difference, product and quotient of a and b
    complex sum {a+b};
    complex difference {a-b};
    complex product {a*b};
    complex division {a/b};

    // Print out results, also demonstrating use of overloaded operator <<
    std::cout << "a=" << a << ": real part is " << real_a << ", imaginary part is "<< imag_a << ", its modulus " << modulus_a << " and argument " << argument_a << " rad." << std::endl;
    std::cout << "b=" << b << ": real part is " << b.get_real() << ", imaginary part is "<< b.get_imag() << ", its modulus " << b.get_modulus() << " and argument " << b.get_argument() << " rad." << std::endl;
    std::cout << conjugate_a << " is the complex conjugate of " << a << std::endl;

    // Show results of overloading arithmetic operators
    std::cout << "a+b=" << sum << std::endl;
    std::cout << "a-b=" << difference << std::endl;
    std::cout << "a*b=" << product << std::endl;
    std::cout << "a/b=" << division << std::endl;

    // Input a complex number, demonstrating use of overloaded operator >>
    complex c{};
    std::cin >> c;
    std::cout << "c=" << c << std::endl;

    return 0;
}