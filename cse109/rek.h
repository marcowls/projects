/*Marc Greenspan
  mag216
  cse109
  p6

 this class represents a record of a table that holds a key and a data
 value. This program also allows for a linked list of reks to be
 created
*/ 
#ifndef REK_H
#define REK_H
#include "key.h"

class Rek{
  //the key for each rek
  Key key;
  //no-arg constructor
  Rek();
public:
  //the data value stored in each memory location
  int data;

  //get method for key
  const Key & getKey()const;

  //two-arg constructor for Rek that takes in a key and a data value
  Rek(const Key &k,int d=int(0));

  //pointer for poiting to the next element of a linked list
  Rek *next;
  //overlaods the << operator
  friend ostream & operator<<(ostream &out,const Rek&r);
};

#endif
