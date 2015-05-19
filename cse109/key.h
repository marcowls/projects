/* Marc Greenspan
   mag216
   cse109
   p6

this class represents a key as well as the hash number for storing
data in a hash table. The key class inherits the word class
*/

#ifndef KEY_H
#define KEY_H

#include "word.h"
#include <iostream>
using namespace std;

class Key{
  //key that represents a word to describe each data member
  Word key;

  //hash number to define each word in a numerical data type
  int hsh;

  //no arg-constructor
  Key();

  //check method
  static void check(bool b, string mess);
public:
  //one-arg constructor for Key that takes in a word 
  Key(const Word &w);

  //one-arg constructor for Key that takes in a char array
  Key(const char *ch);

  //calculates the hash number for a certain key and returns it
  void hash();

  //retuns the key
  Word getKey();

  //get method for hsh
  unsigned int hash()const;

  //overloads the << operator
  friend ostream & operator<<(ostream & out,const Key &k);

  //overloads the == operator to check if two keys are equal
  friend bool operator ==(const Key &a,const Key & b);

  //overloads the != to check if two keys are not equal
  friend bool operator !=(const Key &a, const Key &b);
  
};

#endif
