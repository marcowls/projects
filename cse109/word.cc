/*Marc Greenspan
  mag216
  program 5
  cse109
*/


#include "word.h"
#include <cstdlib>

//deconstrctor for Word. deletes the char array 
Word::~Word(){
  delete [] wd;
}

//no arg constructor
//calls the copy method with an empty string passed to it
//pre: copy is a working method
Word::Word(){
  copy("");
}

//one arg constructor for a word passed in
//calls copy with the wd pointer passed in
//pre: copy is a working method
Word::Word(const Word & w){
  copy(w.wd);
}

//one arg constructor for a char array
//checks to see if a null is passed in, or calls copy with the array
//pre: copy is a working method
Word::Word(const char *ch){

  if(ch == NULL)
    copy("");

  else
    copy(ch);
}

//constructor for a single char passed in
//creates a two element array with the first element being a the char
//and the secdong being the end character \0
Word::Word(char ch){

  //cout << "ch constructor" <<endl;
  wd = new char(2);
  wd[0] = ch;
  wd[1] = '\0';
}

//copy method created in class
//creates a new dyamic array and uses the predefined string copy
//method
//pre-condition: strcpy is a working method
void Word::copy(const char * str){
  wd=new char[strlen(str)+1];
  check(wd!=NULL,"Heap overlow");
  strcpy(wd,str);
  size=strlen(wd);
}

//check method for Word
void Word::check(bool b, const char * mess){
  if(b)
    return;

  else{
    cout << mess << endl;
    exit(1);
    return;
  }
}

//overloads the < operator by calling the string compare method
//pre: both words dont have null pointers
 bool operator<(const Word &a,const Word &b){
   return strcmp(a.wd,b.wd)<0;
 }

//overlaods the = operator by copying the right hand side to the left
//hand side 
const Word & Word::operator=(const Word & w){

  if(this!=&w){
  delete[] wd;
  copy(w.wd);
  }
  return *this;
}


//overalods the >> operator 
istream & operator>>(istream &in,Word & w){ //eoln or eof as
					    //terminator
  char *temp,ch;
  int tempSize,loc;
  tempSize=10;
  temp=new char[tempSize+1];
  Word::check(temp!=NULL,"Heap overflow");
  ch=in.get();
  loc=0;
  while(in.good() && ch!='\n'){
    if(loc==tempSize){
      char *tempA;
      tempA=new char[2*tempSize+1];
      Word::check(tempA!=NULL,"Heap overflow");
      for(int j=0;j<tempSize;j++)
	tempA[j]=temp[j];
      delete[]temp;
      temp=tempA;
      tempSize*=2;
    }
    temp[loc]=ch;
    loc++;
    ch=in.get();
  }
  temp[loc]='\0';
  delete [] w.wd;
  w.wd=temp;
  w.size=strlen(temp);
  return in;
}

//overloads the [] operator by returing the numth element fo the char array
char & Word :: operator [](int num){
  
  check(num < size, "Error, Heap overflow");
  return wd[num];

}

//overloads the [] operator by returning the numth element of the char array
char Word :: operator [](int num)const{

  check(num < size, "Error Heap overflow");
  return wd[num];

}

//overloads the << operator 
ostream &  operator <<(ostream &out, const Word &w){

   return out<<w.wd;

}

//overloads the > operator by using the strcmp method and returning a
//boolean 
bool operator >(const Word &a, const Word &b){

  return strcmp(a.wd,b.wd) > 0;

}

//overlaods the <= method by calling strcmp and returing the result >= 0
bool operator <=(const Word &a, const Word &b){

  return strcmp(a.wd,b.wd) <= 0;
  
}

//overloads the >= operator by calling the strcmp method 
bool operator >=(const Word &a, const Word &b){

  return strcmp(a.wd,b.wd) >= 0;
  
}

//overloads the == operator by calling the strcmp method
bool operator ==(const Word &a, const Word &b){

  return strcmp(a.wd,b.wd) == 0;
  
}

//overloads the != operator by calling the strcmp method 
bool operator !=(const Word &a, const Word &b){

  return strcmp(a.wd,b.wd) != 0;
  
}

//returns a pointer to the string containing the characters in Word
//pre: wd is defined
char* Word :: toString(){

  return wd;

}

//returns the int corresponidng to the letters in Word but crashes if
//the letters are not in the form of an unsigned int
int Word :: toInt(){

  int num = 0;

  for(int i = 0; i < size; i++)
    num = (num * 10) + (wd[i] - '0');
  
  check(num > 0, "Error input is a signed integer");  
  return num;
}

//returns a word corresponding to the letters in Word but crashes if
//the letters are not in the form of an unsigned int
Word &  Word :: fromInt(int num){

  check(num > 0, "Error, illegal input");

  int digit = num;
  int intLength = 0;

  //calculates the length of num
    while(digit > 0){
      digit /= 10;
      intLength++;
    }

  char* temp = new char[intLength];
  int counter = intLength - 1;
  
  for(int i = 0; i < intLength; i++){
    temp[counter] = num % 10 + '0'; // takes the last decimal place
				    // and places it in temp as a char
    num /= 10;
    counter--;
  }

  copy(temp);
  return *this;
}

//returns the number of letters in word
//pre: wd is defined
int Word :: length(){
  return size;
}


