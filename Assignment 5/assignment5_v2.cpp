#include<iostream>
#include<cmath>
#include<string>

class matrix
{
    friend std::ostream & operator<<(std::ostream &os, const matrix &mat);
    friend std::istream & operator>>(std::istream &is, matrix &mat);

private:
    size_t row_number;
    size_t column_number;
    size_t size {row_number*column_number};
    double *data{nullptr};

public:
    matrix()=default; // default constructor
    matrix(size_t row, size_t column); // parameterized constructor
    ~matrix(); // destructor

    matrix(matrix&); // copy constructor
    matrix& operator=(matrix&); // copy assignment operator

    matrix(matrix&&); // move constructor
    matrix& operator=(matrix&&); // move assignment operator

    size_t index(size_t i, size_t j);
    double & operator()(size_t i, size_t j); // overloaded operator () to get access to matrix elements
    matrix operator+(matrix &mat); // overload addition operator
    matrix operator-(matrix &mat); // overload substraction operator
    matrix operator*(matrix &mat); // overload multiplication operator

    matrix delete_ij(size_t i, size_t j); // delete i'th row and j'th column
    double determinant(matrix &mat);

};

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
matrix::~matrix(){
    std::cout << "Destructor" << std::endl;
    row_number=0;
    column_number=0;
    size=0;
    delete[] data;
}

// Copy constructor using deep copying
matrix::matrix(matrix &to_copy)
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
// Move constructor
{ // steal the data
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
matrix & matrix::operator=(matrix &rhs)
{
    if (&rhs==this) {
        return *this; // no self assignment
    }

    std::cout << "Copy assignment" << std::endl;
    // First delete this object's array
    delete[] data; 
    data=nullptr; 
    size=0;
    row_number=0;
    column_number=0;

    // Now copy size and declare new array
    size=rhs.size;
    if(size>0) {
        data=new double[size];

        // Copy values size_to new array
        for (size_t i{1}; i<=row_number; i++) {
            for (size_t j{1}; j<=column_number; j++) {
                data[index(i,j)] = rhs(i,j);
            }
        }
    }
    return *this; // Special posize_ter!!!
}

// Move assignment operator
matrix & matrix::operator=(matrix&& rhs)
{
    std::cout << "Move assignment" << std::endl;
    std::swap(size,rhs.size);
    std::swap(data,rhs.data);
    std::swap(row_number,rhs.row_number);
    std::swap(column_number,rhs.column_number);
    return *this; // Special posize_ter!!!
}


// Returns index of data array for a given matrix element
size_t matrix::index(size_t i, size_t j) {
    if(i<=0 || i>row_number || j<=0 || j>column_number) {
        std::cout << "Element out of bounds" << std::endl;
        throw;
    }
    return (j-1)+(i-1)*column_number;
}

// Overload element () to get access to a certain element of the matrix
double &matrix::operator()(size_t i, size_t j)
{
    return data[index(i,j)];
}

// Overload addition operator
matrix matrix::operator+(matrix &mat) 
{
    if (row_number==mat.row_number && column_number==mat.column_number) {
        matrix addition(row_number,column_number);
        for (size_t i{1}; i<=row_number; i++) {
            for (size_t j{1}; j<=column_number;j++){
                addition.data[index(i,j)]=mat(i,j)+data[index(i,j)];
            }
        }
        return addition;
    }
    else {
        std::cout << "Operation not possible, matrices must be the same size." << std::endl;
        throw;
    }
}

// Overload substraction operator
matrix matrix::operator-(matrix &mat) 
{
    if (row_number==mat.row_number && column_number==mat.column_number) {
        matrix substraction(row_number,column_number);
        for (size_t i{1}; i<=row_number; i++) {
            for (size_t j{1}; j<=column_number;j++){
                substraction.data[index(i,j)]=data[index(i,j)]-mat(i,j);
            }
        }
        return substraction;
    }
    else {
        std::cout << "Operation not possible, matrices must be the same size." << std::endl;
        throw;
    }
}

// Overload multiplication operator
matrix matrix::operator*(matrix &mat) {
    if (column_number==mat.row_number) {
        matrix multiplication(row_number,mat.column_number);
        for (size_t i{1}; i<=row_number; i++) {
            for (size_t j{1}; j<=mat.column_number;j++){
                for (size_t k{1}; k<=column_number;k++) {
                    multiplication.data[index(i,j)]+=data[index(i,k)]*mat(k,j);
                }
            }
        }
        return multiplication;
    }
    else {
        std::cout << "Operation not possible, the column number of the first matrix must be the same as the row number of the second one." << std::endl;
        throw; 
    }
}


matrix matrix::delete_ij(size_t m, size_t n)
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

double matrix::determinant(matrix &mat) 
{
    double determinant;
    matrix temp{mat.row_number-1, mat.column_number-1};

    for (size_t j{1}; j<=column_number; j++) {
        temp = mat.delete_ij(1, j);
        if (j%2==0) {
            determinant-=mat.data[index(1,j)]*(temp(1,1)*temp(2,2)-temp(1,2)*temp(2,1));
        } else {
            determinant+=mat.data[index(1,j)]*(temp(1,1)*temp(2,2)-temp(1,2)*temp(2,1));
        }
        
        std::cout << determinant << std::endl;
    }
    return determinant;
}

// Overload cout << operator to output
std::ostream & operator<<(std::ostream &os, const matrix &mat)
{
    for (size_t i{1};i<=mat.row_number;i++) {
        os << "\n";
        for (size_t j{1};j<=mat.column_number;j++) {
            os<<mat.data[(j-1)+(i-1)*mat.column_number]<<" "; // how to use matrix index function here?
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


int main(){
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

    matrix A{3,3};
    std::cout << "A = " << A << std::endl;
    std::cin >> A;
    std::cout << "A = " << A << std::endl;
    std::cout << A(2,1) << std::endl;

    matrix D{A};
    D(1,2)=10;
    std::cout << "D = " << D << std::endl;

    double det_A{};
    det_A=A.determinant(A);    
    std::cout << "Determinant of A = " << det_A << std::endl;

    matrix E{3,3};
    E=A.delete_ij(3,3);
    std::cout << "E = " << E << std::endl;


    matrix B{3,3};
    std::cin >> B;
    std::cout << "B = " << B << std::endl;

    std::cout << "A+B = " << A+B << std::endl;

    std::cout << "A-B = " << A-B << std::endl;

    matrix C{2,3};
    std::cin >> C;
    std::cout << "C*B = " << C*B << std::endl;

}