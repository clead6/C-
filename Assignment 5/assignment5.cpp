#include<iostream>
#include<cmath>
#include<string>

class matrix_2d
{
    friend std::ostream & operator<<(std::ostream &os, const matrix_2d &matrix);
    friend std::istream & operator>>(std::istream &is, matrix_2d &matrix);

private:
    int row_number;
    int column_number;
    int matrix_size {row_number*column_number};
    double *array{nullptr};

public:
    matrix_2d()=default; // constructor matrix with n rows and m columns
    matrix_2d(int row, int column): array{new double[row*column]{0}},row_number{row},column_number{column},matrix_size{row*column} {
        for(size_t i{0}; i<row*column; i++) {
            array[i]=0;
        }
    }
    ~matrix_2d();
    matrix_2d& operator=(matrix_2d&);
    int length() const {return matrix_size;}
    double & operator[](int i);
    double get_element(int i,int j) const 
    {
        if (i>row_number || i<1 || j>column_number || j<1) {
            std::cout<<"Error: trying to access array element out of bounds"<<std::endl;
            throw("Out of Bounds error");
        }
        return array[(j-1)+(i-1)*column_number];  // (i-1)*n and (j-1) terms are due to fact that C++ arrays start at zero, while the indices of our matrices start at 1!
    }
};

matrix_2d & matrix_2d::operator=(matrix_2d &rhs)
// Assignment operator using deep copying
{
    if(&rhs == this) return *this; // no self assignment
    // First delete this object's array
    delete[] array; array=nullptr; rhs.matrix_size=0;
    // Now copy size and declare new array
    rhs.matrix_size=rhs.length();
    if(rhs.matrix_size>0) {
        array=new double[rhs.matrix_size];
        // Copy values into new array
        for(size_t i{};i<rhs.matrix_size;i++) array[i] = rhs[i];
    }
    return *this; // Special pointer!!!
}

matrix_2d::~matrix_2d(){
    std::cout <<" deleting data\n";
    row_number=0;
    column_number=0;
    delete[] array;
}

// Overloaded element [] operator implementation with bounds checking
double &matrix_2d::operator[](int i) // change this to do as a vector
{
    if(i<0 || i>=matrix_size) {
        std::cout<<"Error: trying to access array element out of bounds"<<std::endl;
        throw("Out of Bounds error");
    }
    return array[i];
}  

// Overload cout << operator to output
std::ostream & operator<<(std::ostream &os, const matrix_2d &matrix)
{
    for (int i{0};i<matrix.row_number*matrix.column_number;i++) {
        if ((i%matrix.column_number)==0) {
            os << "\n";
        }
        os<<matrix.array[i]<<" ";
    }
    os << "\n";
    return os;
}

// Overload cin operator >> to input
std::istream & operator>>(std::istream &is, matrix_2d &matrix)
{
    std::cout << "Enter your matrix as a grid of elements separated by spaces" << std::endl;
    for (int i{0};i<matrix.row_number*matrix.column_number;i++) {
        is>>matrix.array[i];
    }
    std::cout << std::endl;
    return is;
}


int main(){
    matrix_2d A{2,3};
    std::cout << "A = " << A << std::endl;
    std::cin >> A;
    std::cout << "A = " << A << std::endl;
    std::cout << A.get_element(2,1) << std::endl;
    A[1]=10;
    std::cout << "A = " << A << std::endl;

}

