#include <iostream>

using namespace std;


struct planet {
  char* planet_name;
  double planet_distance;
  struct {
    char galaxy_system [ 13 ];
    double mass;
    } facts, *facts_ptr = &facts;
  } planet_record, *planet_ptr = &planet_record, all_records[5];

int main() {

}