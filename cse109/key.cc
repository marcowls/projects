/*Marc Greenspan
  mag216
  p6
  cse109
*/
  
#include "key.h"
#include <cstdlib>

//one-arg constructor for Word that takes in a Word and calulates the
//hash number for that word
Key::Key(const Word &w){

  key = w;
  hash();

}

//one-arg constructor for Word that takes in an array of chars and
//calls Word's har array constructor to create a word. The hash value
//is then calculated 
Key::Key(const char *ch){

  Word w(ch);
  key = w;
  hash();
  
}

//pre:condition = the key is a set word 
//calculates the hash value for a certain key buy adding the ascii
//value of each letter and multiplying by 257

void Key::hash(){

  hsh = 0;

  for(int i = 0; i < key.length(); i++)
    hsh = (hsh + key[i]) * 257;

  //if the hsh is negative, return the absolute value
  if(hsh < 0)
    hsh *= -1;
  
}

//pre-condtion: the hash value is already set
//returns thr key's hash value
unsigned int Key::hash()const{
  
  return hsh;

}

//pre-condtion: key is already set
//returns the key 
Word Key::getKey(){

  return key;
  
}

//pre-condition: both keys passed in are not null
//checks to see if two keys are equal by calling word's == operator

bool operator ==(const Key &a, const Key &b){

  return a.key == b.key;

}

//pre-condtion: both keys passed in are not null
//checks to see if two keys are not equal by calling words != operator 
bool operator !=(const Key &a, const Key &b){

  return a.key != b.key;

}
//pre-condition: key is not null
//overloads << operator to print out an instance of key's key and hash number
ostream & operator<<(ostream & out, const Key &k){
  return out<<"["<< k.key<<", "<<k.hsh<<"]";
}

