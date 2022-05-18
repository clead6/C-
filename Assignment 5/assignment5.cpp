// PHYS 30762 Programming in C++
// Assignment 5
// Clea Dronne - 01/04/2022
// Class for matrices

#include<iostream>
#include<cmath>
#include<string>

class matrix
{
    friend std::ostream & operator<<(std::ostream &os, const matrix &mat);
    friend std::istream & operator>>(std::istream &is, matrix &mat);

private:
    size_t row_number{0};
    size_t column_number{0};
    size_t size {row_number*column_number};
    double *data{nullptr};

public:
    matrix()=default; // default constructor
    matrix(size_t row, size_t column); // parameterized constructor
    ~matrix(); // destructor

    matrix(const matrix&); // copy constructor
    matrix& operator=(const matrix&); // copy assignment operator

    matrix(matrix&&); // move constructor
    matrix& operator=(matrix&&); // move assignment operator

    size_t index(size_t i, size_t j) const; // for a given matrix element returns index in array of data
    double & operator()(const size_t i, const size_t j) const; // overloaded operator () to get access to matrix elements
    matrix operator+(const matrix &mat) const; // overload addition operator
    matrix operator-(const matrix &mat) const; // overload substraction operator
    matrix operator*(const matrix &mat) const; // overload multiplication operator

    matrix delete_ij(const size_t i, const size_t j) const; // delete i'th row and j'th column
    double determinant(matrix &mat) const; // calculate determinant

};

// Parameterised constructor
matrix::matrix(size_t row, size_t column)
{ 
    std::cout << "Parameterised constructor" << std::endl;
    row_number = row;
    column_number = column;
    size = row_number*column_number;
    data = new double[row_number*column_number]{0};
    for(size_t i{0}; i<size; i++) {
        data[i]=0;
    }
}

// Destructor
matrix::~matrix()
{
    std::cout << "Destructor" << std::endl;
    row_number=0;
    column_number=0;
    size=0;
    delete[] data;
}

// Copy constructor using deep copying
matrix::matrix(const matrix &to_copy)
{
    std::cout << "Copy constructor" << std::endl;
    data = nullptr;
    size = to_copy.size;
    row_number = to_copy.row_number;
    column_number = to_copy.column_number;

    if (size>0) {    
        data = new double[size];
        for(size_t i{1};i<=row_number;i++) {
            for (size_t j{1};j<=column_number;j++){
                data[index(i,j)] = to_copy(i,j);
            }            
        }
    }      
}

// Move constructor
matrix::matrix(matrix &&to_move)
{
    std::cout <<"Move constructor" << std::endl;
    row_number=to_move.row_number;
    column_number=to_move.column_number;
    size=to_move.size;
    data=to_move.data;
    to_move.row_number=0;
    to_move.column_number=0;
    to_move.size=0;
    to_move.data=nullptr;
}

// Assignment operator using deep copying
matrix & matrix::operator=(const matrix &rhs)
{
    if (&rhs==this) {
        return *this;
    }

    std::cout << "Copy assignment" << std::endl;
    delete[] data; 
    data=nullptr; 
    size=0;
    row_number=0;
    column_number=0;

    size=rhs.size;
    row_number=rhs.row_number;
    column_number=rhs.column_number;
    if(size>0) {
        data=new double[size];
        for (size_t i{1}; i<=row_number; i++) {
            for (size_t j{1}; j<=column_number; j++) {
                data[index(i,j)] = rhs(i,j);
            }
        }
    }
    return *this;
}

// Move assignment operator
matrix & matrix::operator=(matrix&& rhs)
{
    std::cout << "Move assignment" << std::endl;
    std::swap(size,rhs.size);
    std::swap(row_number,rhs.row_number);
    std::swap(column_number,rhs.column_number);
    std::swap(data,rhs.data);
    return *this;
}

// Returns index of data array for a given matrix element
size_t matrix::index(size_t i, size_t j) const
{
    if(i<=0 || i>row_number || j<=0 || j>column_number) {
        std::cout << "Element out of bounds" << std::endl;
        throw;
    }
    return (j-1)+(i-1)*column_number;
}

// Overload element () to get access to a certain element of the matrix
double &matrix::operator()(const size_t i, const size_t j) const
{
    return data[index(i,j)];
}

// Overload addition operator
matrix matrix::operator+(const matrix &mat) const
{
    if (row_number==mat.row_number && column_number==mat.column_number) {
        matrix addition(row_number,column_number);
        for (size_t i{1}; i<=row_number; i++) {
            for (size_t j{1}; j<=column_number;j++){
                addition.data[index(i,j)]=mat(i,j)+data[index(i,j)];
            }
        }
        return addition;
    } else {
        std::cout << "Operation not possible, matrices must be the same size." << std::endl;
        throw;
    }
}

// Overload substraction operator
matrix matrix::operator-(const matrix &mat) const 
{
    if (row_number==mat.row_number && column_number==mat.column_number) {
        matrix substraction(row_number,column_number);
        for (size_t i{1}; i<=row_number; i++) {
            for (size_t j{1}; j<=column_number;j++){
                substraction.data[index(i,j)]=data[index(i,j)]-mat(i,j);
            }
        }
        return substraction;
    } else {
        std::cout << "Operation not possible, matrices must be the same size." << std::endl;
        throw;
    }
}

// Overload multiplication operator
matrix matrix::operator*(const matrix &mat) const
{
    if (column_number==mat.row_number) {
        matrix multiplication(row_number,mat.column_number);
        for (size_t i{1}; i<=row_number; i++) {
            for (size_t j{1}; j<=mat.column_number;j++){
                for (size_t k{1}; k<=column_number;k++) {
                    //multiplication.data[index(i,j)]+=data[index(i,k)]*mat(k,j);
                    multiplication(i,j)+=data[index(i,k)]*mat(k,j);
                }
            }
        }
        return multiplication;
    } else {
        std::cout << "Operation not possible, the column number of the first matrix must be the same as the row number of the second one." << std::endl;
        throw; 
    }
}

// Delete m'th row and n'th column of matrix
matrix matrix::delete_ij(const size_t m, const size_t n) const
{
    matrix new_matrix{row_number-1,column_number-1};
    size_t x{0};
    size_t y{0};

    for (size_t i{1}; i<=row_number; i++) {
        if (i!=m) {
            x++;
        }
    
        for (size_t j{1}; j<=column_number; j++) {
            if (i!=m && j!=n) {
                y++;
                new_matrix.data[y-1+(x-1)*new_matrix.column_number]=data[j-1+(i-1)*(new_matrix.column_number+1)];
            }
        }
        y=0;
    }

    return new_matrix;
}

// Calculate determinant of function
double matrix::determinant(matrix &mat) const
{
    if (row_number!=column_number) {
        std::cout << "Matrix must be square to calculate determinant." << std::endl;
        throw;
    }
    double determinant;
    if (mat.row_number==2 && mat.column_number==2) {
        return (mat(1,1)*mat(2,2)-mat(1,2)*mat(2,1));
    } else {    
        for (size_t j{1}; j<=mat.column_number;j++) {
            matrix temp(mat.delete_ij(1,j));
            determinant+=pow(-1,j+1)*mat(1,j)*mat.determinant(temp);
        }
        return determinant;
    }
}

// Overload cout << operator to output
std::ostream & operator<<(std::ostream &os, const matrix &mat)
{
    if (mat.row_number==0 || mat.column_number==0) {
        os << "Matrix is empty" << std::endl;
        return os;
    }

    for (size_t i{1};i<=mat.row_number;i++) {
        os << "\n";
        for (size_t j{1};j<=mat.column_number;j++) {
            os<<mat.data[(j-1)+(i-1)*mat.column_number]<<" ";
        }
    }
    os << "\n";
    return os;
}

// Overload cin operator >> to input
std::istream & operator>>(std::istream &is, matrix &matrix)
{
    std::cout << "Enter your matrix as a grid of elements separated by spaces" << std::endl;
    for (size_t i{0};i<matrix.size;i++) {
        is>>matrix.data[i];
    }
    std::cout << std::endl;
    return is;
}

int main() {
    /*
    Matrices to input
    A =
    1 2 3
    9 8 7
    4 2 6

    B =
    5 5 4
    1 2 3
    6 9 8

    C = 
    3 4 1 
    2 5 6

    */

    // Initialise and input matrices
    matrix A{3,3};
    std::cout << "A = " << A << std::endl;
    std::cout << "Input matrix A" << std::endl;
    std::cin >> A;
    std::cout << "A = " << A << std::endl;

    matrix B{3,3};
    std::cout << "Input matrix B" << std::endl;
    std::cin >> B;
    std::cout << "B = " << B << std::endl;

    matrix C{2,3};
    std::cout << "Input matrix C" << std::endl;
    std::cin >> C;

    // Arithmetic operations
    std::cout << "A+B = " << A+B << std::endl;

    std::cout << "A-B = " << A-B << std::endl;

    std::cout << "A*B = " << A*B << std::endl;

    std::cout << "C*B = " << C*B << std::endl;

    // Determinants
    std::cout << "\nCalculate determinants: \n" << std::endl;
    double det_A{};
    det_A=A.determinant(A);    
    std::cout << "\nDeterminant of A = " << det_A << std::endl;
    std::cout << std::endl;

    double det_B{};
    det_B=B.determinant(B);    
    std::cout << "\nDeterminant of B = " << det_B << std::endl;
    std::cout << std::endl;

    // Copy constructor
    matrix A2{A};
    std::cout << "Change element row 1, column 2 of A, showing A2 does not change." << std::endl;
    A(0,2)=10;
    std::cout << "A = " << A << std::endl;
    std::cout << "A2 = " << A2 << std::endl;

    // Copy assignment operator
    matrix A3;
    A3=A2;
    std::cout << "A3 copy of A2" << std::endl;
    std::cout << "A3 = " << A3 << std::endl;

    // Move constructor
    matrix A4{std::move(A2)};
    std::cout << "Move A2 to A4." << std::endl;
    std::cout << "A4 = " << A4 << std::endl;
    std::cout << "A2 = " << A2 << std::endl;

    // Move assignment operator
    matrix A5;
    A5 = std::move(A3);
    std::cout << "Move A3 to A5." << std::endl;
    std::cout << "A5 = " << A5 << std::endl;
    std::cout << "A3 = " << A3 << std::endl;   

    std::cout << "Back to arithmetics, show impossibility of B*C:" << std::endl;
    std::cout << "B*C = " << B*C << std::endl;

}