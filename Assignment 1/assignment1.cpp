// Assignment 1
// Clea Dronne - 16/02/2022
// Program to calculate transition energy using simple Bohr formula

#include<iostream>
#include<iomanip>
#include<string>

double square(int value) 
{
    return value*value;
}

void energy_output(int atomic_number, int initial_state, int final_state) 
{
    const double joules_per_ev {1.602176634e-19};
    double energy_in_ev;
    double energy_in_joules;
    std::string ev_to_joules;

    energy_in_ev = 13.6*square(atomic_number)*(1/square(final_state)-1/square(initial_state));
    energy_in_joules = energy_in_ev*joules_per_ev;

    while (ev_to_joules!="e" && ev_to_joules!="J") {
        std::cout << "Do you want the result in eV or in J (enter e for electron-volts or J for Joules): ";
        std::cin >> ev_to_joules;
    }
    if (ev_to_joules=="e") {
        std::cout << "The result is " << std::setprecision(3) << energy_in_ev << " eV." << std::endl;
    } else if (ev_to_joules=="J") {
        std::cout << "The result is " << std::setprecision(3) << energy_in_joules << " J." << std::endl;
    } 
}

int main() 
{ 
    int initial_state; 
    int final_state;
    int atomic_number {0};
    std::string continue_yes_no;

    while (true) {
        while (initial_state<=final_state) {
            std::cout << "Enter the atomic number: "; // Needs to be >= 1
            std::cin >> atomic_number;
            while (std::cin.fail() || atomic_number<1) {
                std::cout << "Invalid input, atomic number must be an integer greater or equal to 1: "; // Needs to be >= 1
                std::cin.clear();
                std::cin.ignore();
                std::cin >> atomic_number;
            }
            
            std::cout << "Enter the initial quantum number: "; // Needs to be >= 1, and final > initial
            std::cin >> initial_state;
            while (std::cin.fail() || initial_state<1) {
                std::cout << "Invalid input, initial quantum number must be an integer greater or equal to 1. Enter the initial quantum number: "; // Needs to be >= 1
                std::cin.clear();
                std::cin.ignore();
                std::cin >> initial_state;     
            }

            std::cout << "Enter the final quantum number: ";
            std::cin >> final_state;
            while (std::cin.fail() || final_state<1) {
                std::cout << "Invalid input, final quantum number must be an integer greater or equal to 1. Enter the final quantum number: "; // Needs to be >= 1
                std::cin.clear();
                std::cin.ignore();
                std::cin>> final_state;       
            }
            if (initial_state<=final_state) {
                std::cout << "Make sure that your initial quantum number is greater than the final one." << std::endl;
            }             
        }

        energy_output(atomic_number, initial_state, final_state);

        while (continue_yes_no!="y" && continue_yes_no!="n") {
            std::cout << "Do you want to keep using this program (y/n)? ";
            std::cin >> continue_yes_no;
        }
        if (continue_yes_no=="y") {
            continue_yes_no=" ";
            initial_state=0;
            final_state=0;
            continue;
        } else if (continue_yes_no=="n") {
            break;
        }
    }
    return 0; 
} 