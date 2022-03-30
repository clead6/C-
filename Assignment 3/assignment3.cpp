// PHYS 30762 Programming in C++
// Assignment 3
// Clea Dronne - 11/03/2022
// Simple demonstration of a C++ class

// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>

std::vector<std::string> hubble_type_names = {"E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr"};
class galaxy
{
private:
    std::string hubble_type {"Default"};
    double redshift {0.0};
    double total_mass {0.0};
    double stellar_mass_fraction {0.0};
    std::vector <galaxy> satellites;

public:
    // Constructors
    galaxy() = default;
    galaxy(std::string galaxy_hubble_type, double galaxy_redshift, double galaxy_total_mass, double galaxy_stellar_mass_fraction) :
        hubble_type{galaxy_hubble_type}, redshift{galaxy_redshift}, total_mass{galaxy_total_mass}, 
        stellar_mass_fraction{galaxy_stellar_mass_fraction} {
        
        // Check values of hubble type, and ranges of redshift, total mass and stellar mass fraction
        if (std::find(hubble_type_names.begin(), hubble_type_names.end(), hubble_type) == hubble_type_names.end()) {
            throw std::invalid_argument("Invalid Hubble type");
        }
        if (redshift>10 || redshift<0) {
            throw std::invalid_argument("Redshift is out of range");
        }
        if (total_mass<10e7 || total_mass>10e12) {
            throw std::invalid_argument("Total mass is out of range");
        }
        if (stellar_mass_fraction<0 || stellar_mass_fraction>0.05) {
            throw std::invalid_argument("Stellar mass fraction is out of range");
        }        
    }

    // Destructor
    ~galaxy(){std::cout<<"Destroying "<<hubble_type<<std::endl;}

    // Return stellar mass (M_* = f_* x M_tot)
    double stellar_mass() {return stellar_mass_fraction*total_mass;}

    // Change galaxy's Hubble type
    void change_type(std::string new_type);

    // Prototype for function to print out an object's data
    void print_data();

    // Add satellite galaxy
    void add_satellite_galaxy(galaxy &new_galaxy) {satellites.push_back(new_galaxy);}
};
// Change galaxy's Hubble type
void galaxy::change_type(std::string new_type) 
{
    if (std::find(hubble_type_names.begin(), hubble_type_names.end(), hubble_type) == hubble_type_names.end()) {
        throw std::invalid_argument("Invalid Hubble type");
    }
    hubble_type=new_type;
}

// Print out an object's data
void galaxy::print_data()
{
    std::cout.precision(3); // 3 significant figures
    std::cout<<"\nGalaxy type is "<<hubble_type<<", its redshift "<< redshift <<", its total mass "<<total_mass<<
        "M_Sun and its stellar mass fraction "<< stellar_mass_fraction<<". It has "<< satellites.size() << " satellites." << std::endl;
    if (satellites.size()>0) {
        int counter {0};
        std::cout << "Its satellite(s) is(are): " << std::endl; 
        for (std::vector<galaxy>::iterator galaxies_it = satellites.begin() ; galaxies_it != satellites.end(); ++galaxies_it) {      
            counter+=1;
            std::cout << "\t Satellite "<<counter<<": galaxy type is "<<galaxies_it->hubble_type<<", its redshift "<<
                galaxies_it->redshift <<", its total mass "<<galaxies_it->total_mass<<
                "M_Sun and its stellar mass fraction "<<galaxies_it->stellar_mass_fraction<<"."<< std::endl;
      }
    }
    return;
}
// End of class and associated member functions

// Main program
int main()
{
    std::vector<galaxy> galaxies;

    // Example using default constructor
    galaxy galaxy1; 
    galaxies.push_back(galaxy1);

    // Example using parameterised constructor
    galaxy galaxy2("Sb",0,1.5e12,0.015);
    galaxies.push_back(galaxy2);

    // Print out data
    for (std::vector<galaxy>::iterator galaxies_it = galaxies.begin() ; galaxies_it != galaxies.end(); ++galaxies_it) {
        galaxies_it->print_data();
    }

    // Get and print out stellar mass
    std::cout.precision(3);
    std::cout << "This galaxy has stellar mass " << galaxies[1].stellar_mass() << "M_Sun." <<std::endl;

    // Change Hubble type from Irr to S0
    galaxies[1].change_type("SBb");
    galaxies[1].print_data();
    
    // Add satellite galaxies
    galaxy satellite_galaxy1("Sb",0.000123,2e10,0.0004);
    galaxy satellite_galaxy2("Irr",0.000527,7e9,0.0007);

    galaxies[1].add_satellite_galaxy(satellite_galaxy1);
    galaxies[1].add_satellite_galaxy(satellite_galaxy2);

    // Print out data
    for (std::vector<galaxy>::iterator galaxies_it = galaxies.begin() ; galaxies_it != galaxies.end(); ++galaxies_it) {
        galaxies_it->print_data();
    }  

    return 0;
}