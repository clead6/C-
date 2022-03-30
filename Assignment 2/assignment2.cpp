// PHYS 30762 Programming in C++
// Assignment 2
// Clea Dronne - 04/03/2022
// Program to compute mean, standard deviation and standard error of the a set of courses. Data is read from file

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm> 

// Functions to compute the mean, standard deviation and standard error
double mean(std::vector <double>& marks)
{
    double sum {0.0};
    for (int i {0}; i < marks.size(); i++) {
      sum += marks[i];
    }
    return sum/marks.size();
}

double standard_deviation(std::vector <double>& marks) 
{
    double sum {0.0};
    for (int i{0}; i < marks.size(); i++) {
      sum += pow(marks[i] - mean(marks), 2);
    }
    return sqrt(sum/(marks.size()-1));
}

double standard_error_mean(std::vector <double>& marks) 
{
    return standard_deviation(marks)/sqrt(marks.size());
}

// Function to calculate number of lines of file
int file_length(std::ifstream& file) 
{
    int number {0};
    std::string line;
    while (std::getline(file, line)) {
        number++;
    }
    return number;
}

// Function to ascendingly sort course codes
bool compare_code(std::string string1, std::string string2) 
{
    std::string course_name_1 = string1.substr(5);
    std::string course_name_2 = string2.substr(5);
    return (course_name_1<course_name_2);
}

// Function to alphabetically sort course names
bool compare_name(std::string string1, std::string string2) 
{
    std::string course_name_1 = string1.substr(11);
    std::string course_name_2 = string2.substr(11);
    return (course_name_1<course_name_2);
}

// Function to output the course list either sorted by course code or course name
void course_list_output(std::vector <std::string>& course_list) 
{
    std::string sort_choice;
    std::cout << "Do you want to sort with respect to course code (enter 'code') or course name (enter 'name'): ";
    std::cin >> sort_choice;

    if (sort_choice == "code") {
        std::sort (course_list.begin(), course_list.end(), compare_code);
        for (std::vector<std::string>::iterator it = course_list.begin() ; it != course_list.end(); ++it) {
            std::cout << *it << std::endl;
        }
    } else if (sort_choice == "name") {
        std::sort (course_list.begin(), course_list.end(), compare_name);
        for (std::vector<std::string>::iterator it = course_list.begin() ; it != course_list.end(); ++it) {
            std::cout << *it << std::endl;
        }
    } else {
        std::cout << "Incorrect input, course list not printed." << std::endl;
    }

    std::cout << "There are " << course_list.size() << " courses in this list." << std::endl;
}

// Main function
int main()
{
    std::string data_file;
    std::cout << "Enter data filename: ";
    std::cin >> data_file;

    // Check file validity
    std::ifstream course_stream(data_file);
    while(!course_stream.good()) {
        std::cerr <<"Error: file could not be opened, enter new file name: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> data_file;
        course_stream.clear();
        course_stream.open(data_file);
        }
    
    // Output file length and put pointer back at the beginning of the file
    std::cout << "There are " << file_length(course_stream) << " lines in this file." << std::endl;
    course_stream.clear();
    course_stream.std::istream::seekg(0, std::ios::beg);

    std::string line;
    std::vector <double> marks;
    std::vector <int> course_codes;
    std::vector <std::string> course_names;

    // Choose if courses should be viewed for all years or a particular one
    char year;
    std::cout << "Do you want to view marks for all years (enter 0) or for a particular year (enter 1, 2, 3, 4): ";
    std::cin >> year;

    if (year=='0') {
        std::vector <std::string> full_course_list;
        while (getline(course_stream, line)) {
            std::string mark = line.substr(0,line.find(" "));
            marks.push_back(std::stod(mark));

            std::string code = line.substr(line.find(" ")+1,line.find("   ")-line.find(" ")-1);
            course_codes.push_back(std::stoi(code));

            std::string name = line.substr(line.find("   ")+line.find(" ")-1);
            course_names.push_back(name);

            // Stringstream to combine the integer course code and title, this gets stored in a vector
            std::stringstream sstream; 
            sstream << "PHYS " << code << " " << name; 
            
            full_course_list.push_back(sstream.str());
            sstream.str("");
        }

        course_list_output(full_course_list);
        course_stream.close();

    } else if (year == '1' || year == '2' || year == '3' || year == '4') {
        std::vector <std::string> course_list_year;

        while (getline(course_stream, line)) {
            int code = std::stoi(line.substr(line.find(" ")+1,line.find("   ")-line.find(" ")-1));
            course_codes.push_back(code);

            std::string name = line.substr(line.find("   ")+line.find(" ")-1);
            course_names.push_back(name);

            // Stringstream to combine the integer course code and title
            std::stringstream sstream;
            sstream << "PHYS " << code << " " << name;    

            // For the chosen year, the stringstreams and marks get stored in a vector
            if (year == '1' && 10000<code && code<20000) {
                course_list_year.push_back(sstream.str());
                std::string mark = line.substr(0,line.find(" "));
                marks.push_back(std::stod(mark));
            } else if (year == '2' && 20000<code && code<30000) {
                course_list_year.push_back(sstream.str());
                std::string mark = line.substr(0,line.find(" "));
                marks.push_back(std::stod(mark));
            } else if (year == '3' && 30000<code && code<40000) {
                course_list_year.push_back(sstream.str());
                std::string mark = line.substr(0,line.find(" "));
                marks.push_back(std::stod(mark));
            } else if (year == '4' && 40000<code) {
                course_list_year.push_back(sstream.str());
                std::string mark = line.substr(0,line.find(" "));
                marks.push_back(std::stod(mark));
            }            
            sstream.str("");
        }

        course_list_output(course_list_year);
        course_stream.close();
        
    } else {
        std::cout << "Incorrect input." << std::endl;
        return 0;
    }

    // Compute mean, standard deviation and standard error of mean
    double mean_marks = mean(marks);
    double standard_deviation_marks = standard_deviation(marks);
    double standard_error_mean_marks = standard_error_mean(marks);

    std::cout.setf(std::ios::fixed,std::ios::floatfield); 
    std::cout << "The mean mark was " << std::setprecision(2) << mean_marks <<", its standard deviation " << standard_deviation_marks << " and the standard error " << standard_error_mean_marks << std::endl;
    return 0;
}