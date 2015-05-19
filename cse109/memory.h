//Marc Greenspan
//cse 109
//mag216
//p4
//This class represents the header file for a location in memory
//methods are included for getting and setting the value


#ifndef Memory_H
#define Memory_H
#include <iostream>
#include <cstdlib>
using namespace std;

class Memory{

  protected:
  //represents the value of a location 
    int value; 

  public:
    Memory();// no-arg constrcutor, sets value = 0
    Memory(int num); //one arg constructor, sets memory = to num
    Memory(const Memory & mem); //copy constructor
    Memory & set(int num); // sets the value in memory to some int value
    int get() const; //gets the contents of the memory
  void check(bool boolean, string message); //check method
};
#endif
