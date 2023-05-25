/*
Number 1:
Without compiling and running it, write an expression (in a cpp file as comments) that can be
used to access (or print) the structure members in each of the following:
a) planets_name of structure planets_record.
    planets_record.planets_name = new char[15];
    strcpy(planets_record.planets_name, "Mars");
    cout << planets_record.planets_name << endl;

b) planets_name of member structure pointed to by planets_ptr.
    planets_ptr->planets_name = new char[15];
    strcpy(planets_ptr->planets_name, "Venus");
    cout << planets_ptr->planets_name << endl;
  
c) planets_distance of structure planets_record.
    planets_record.planets_distance = 10.0;
    cout << planets_record.planets_distance << endl;
  
d) planets_distance of the structure pointed to by planets_ptr.
    planets_ptr->planets_distance = 20.0;
    cout << planets_ptr->planets_distance << endl;
  
e) mass of the structure member facts of structure planets_record.
    planets_record.facts.mass = 100.0;
    cout << planets_record.facts.mass << endl;
  
f) mass of member pointed to by facts_ptr of the structure pointed to by planets_ptr.
    planets_ptr->facts->mass = 200.0;
    cout << planets_ptr->facts->mass << endl;

g) galaxy_system of the structure member facts of structure planets_record.
    strcpy(planets_record.facts.galaxy_system, "Milky Way");
    cout << planets_record.facts.galaxy_system << endl;

h) galaxy_system of member pointed to by facts_ptr of the structure pointed to by planets_ptr.
    strcpy(planets_ptr->facts->galaxy_system, "Milky Way");
    cout << planets_ptr->facts->galaxy_system << endl;

Number 2:
I got f and h wrong, but everything else correct. The syntax errors that I 
made for f and h were caused by the incorrect usage of my variables. I was using
the variable facts when I was suppose to use the variable that points to facts
named facts_ptr for f and h. The code did not run properly because of an member
reference type error.
*/
#include <iostream>
#include <cstring>

using namespace std;

struct planets {
    char* planets_name;
    double planets_distance;
    struct {
        char galaxy_system[13];
        double mass;
    } facts, *facts_ptr;
} planets_record, *planets_ptr = &planets_record, all_records[5];

int main() {
    // initialize planets_record
    planets_record.planets_name = new char[15];
    strcpy(planets_record.planets_name, "Mars");
    planets_record.planets_distance = 10.0;
    strcpy(planets_record.facts.galaxy_system, "Milky Way");
    planets_record.facts.mass = 100.0;
    planets_record.facts_ptr = &planets_record.facts;

    // print the planets_record
    cout << "planets name: " << planets_record.planets_name << endl;
    cout << "planets distance: " << planets_record.planets_distance << endl;
    cout << "galaxy system: " << planets_record.facts.galaxy_system << endl;
    cout << "mass: " << planets_record.facts.mass << endl;
    cout << endl;

    // create for loop to intialize all_records
    for (int i = 0; i < 5; i++) {
        all_records[i].planets_name = new char[15];
        strcpy(all_records[i].planets_name, ("planets" + to_string(i + 1)).c_str());
        all_records[i].planets_distance = (i + 1) * 10.0;
        strcpy(all_records[i].facts.galaxy_system, "Milky Way");
        all_records[i].facts.mass = (i + 1) * 100.0;
        all_records[i].facts_ptr = &all_records[i].facts;
    }

    // printing planets for all_records
    for (int i = 0; i < 5; i++) {
        cout << "planets name: " << all_records[i].planets_name << endl;
        cout << "planets distance: " << all_records[i].planets_distance << endl;
        cout << "galaxy system: " << all_records[i].facts.galaxy_system << endl;
        cout << "mass: " << all_records[i].facts.mass << endl;
        cout << endl;
    }

    // pointer to dynamically allocate records of 5 new planets
    struct planets* ptr_records = new struct planets[5];

    // Initialize the members of the dynamically allocated array
    for (int i = 0; i < 5; i++) {
        ptr_records[i].planets_name = new char[15];
        strcpy(ptr_records[i].planets_name, ("planets" + to_string(i + 6)).c_str());
        ptr_records[i].planets_distance = (i + 6) * 20.0;
        strcpy(ptr_records[i].facts.galaxy_system, "Whirlpool");
        ptr_records[i].facts.mass = (i + 6) * 150.0;
        ptr_records[i].facts_ptr = &ptr_records[i].facts;
    }

    // Printing members of the dynamically allocated array
    for (int i = 0; i < 5; i++) {
        cout << "planets name: " << ptr_records[i].planets_name << endl;
        cout << "planets distance: " << ptr_records[i].planets_distance << endl;
        cout << "galaxy system: " << ptr_records[i].facts.galaxy_system << endl;
        cout << "mass: " << ptr_records[i].facts.mass << endl;
        cout << endl;
    }

    // Deallocating memory for planets_record
    delete[] planets_record.planets_name;

    // Deallocating memory for all_records
    for (int i = 0; i < 5; i++) {
        delete[] all_records[i].planets_name;
    }

    // Deallocating memory for the dynamically allocated array
    delete[] ptr_records;

    return 0;
}