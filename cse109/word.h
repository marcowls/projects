/*Marc Greenspan
  mag216
  cse109
  program 5
*/ 

//wrapper class for strings
//better   great exercise with pointers, text reading
#include <iostream>
#include <cstring>
using namespace std;

class Word{
private:

  //pointer to create a dynamic array of chars
  char *wd;

  //int that holds the number of letters in Word
  int size;

  //check method for Word
  static void check(bool b, const char * mess);
public:

  //no arg constructor
  Word();

  //one arg construcotr with a word passed in
  Word(const Word &w);

  //one arg constructor with a char passed in
  Word(const char *ch);
  // Word(int n);      nice ideas from class, but we will ignore
  //  Word(string st);

  //one arg constructor for a single char
  Word(char ch);

  //destructor for Word
  //precondition: wd is defined 
  ~Word();

  //overlaods the [] operator
  char & operator[](int n);

  //overlaods the [] operator with the object beiing called remaingn unchanged
  char operator[](int n)const;

  //overloads the < operator to allow word comparision
  friend bool operator<(const Word &a,const Word &b);

  //overloads the  = operator
  const Word & operator=(const Word & w);

  //overloads the >> operator for input
  friend istream & operator>>(istream &in,Word & w);

  //overlaods the > operator
  friend bool operator >(const Word &a, const Word&b);

  //overloads the <= operator
  friend bool operator <=(const Word &a, const Word &b);

  //overloads the >= operator
  friend bool operator >=(const Word &a, const Word &b);

  //overloads the == operator
  friend bool operator ==(const Word &a, const Word &b);

  //overloads the != operator
  friend bool operator !=(const Word &a, const Word &b);

  //overloads the << operator
  friend ostream & operator <<(ostream &out,const Word &w);

  //returns a pointer to a string of characters as arguments
  char* toString();

  //returns the int corresponding to the given index
  int toInt();

  //returns a word corresponding to a positive int passed to it
  Word & fromInt(int num);

  //returns the number of characters in a Word object
  int length();
  //terminator

  //copy method that makes a deep copy of an array
private:
  void copy(const char * str);
};
