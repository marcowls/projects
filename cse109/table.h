/*Marc Greenspan
  mag216
  cse109
  p6

 This class represents a hash table of reks. It allows for hashing
 data values and quick acess of memory 
*/

//#ifndef Table_H
//#define Table_H
#include "rek.h"

class Table{
  //Array of pointers to rek objects. this array acts as the hashing table
  Rek **table;

  //variable for holding the size of the table
  int size;
  
public:
  //check method
  static void check(bool b, string mess);

  //one are-constructor for Table, which takes int a size
  Table(int num);

  //deconstructor for table
  ~Table();

  //overloads the [] operator for a table
  int & operator [](const Key &k);

  //overloads the [] operator for table
  int operator [](const Key &k)const;

  //method cheks if the key passed in is in the table
  bool inTable(const Key &k)const;

  //checks if the number passed in is prime
  bool isPrime(int num);

  //overloads the << operator for Table
  friend ostream & operator <<(ostream & out,const Table &t);

};

//#endif
