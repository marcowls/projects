/*Marc Greenspan
  mag216
  cse109
  p6
*/

#include "table.h"
#include <cstdlib>

//pre-condition: table is defined
//deconstructor for table, deletes every pointer in the table if it is
//not already null. The deletes the pointer to the table
Table::~Table(){

  for(int i = 0; i < size; i++){
    if(table[i] != NULL)
      delete table[i];
    }
  delete [] table;
}

//pre-condtion: 
//One-arg constructor for Table, which takes in a size for the
//table. It increments the size until it is a prime number and creates
//a table with each poitner set to null
Table::Table(int num){

  while(!isPrime(num))
    num++;

  size = num; 
  table = new Rek*[size];

  for(int i = 0; i < size; i++)
    table[i] = NULL;
}

//precondition: a valid key is
//given. creates a new rek if a key is given that is
//not in the array
//postcondition:allows the user to set the data value. Outputs an
//&int value. 
int & Table::operator [](const Key &k){

  Rek r(k);
  int hash = k.hash() % size;
  if(!inTable(r.getKey())){
    Rek * temp = table[hash];
  table[hash] = new Rek(r);
  table[hash]->next = temp;
  }

  if(inTable(r.getKey())){

    Rek *temp = table[hash];
    while(temp != NULL && temp->getKey() != k){
       temp= temp->next;
    }
    return temp->data;
  }
  
  return table[hash]->data; 
}

//precondition: a valid key is
//given. Crashes if a key is given that is
//not in the array
//postcondition:allows the user to set the data value. Outputs an
//int value.
int Table::operator [](const Key &k)const {

  Rek r(k);
  int hash = k.hash() % size;
  
    if(inTable(r.getKey())){

      Rek *temp = table[hash];
      while(temp != NULL && temp->getKey() != k){
	temp= temp->next;
      }
      return temp->data;
    }

    else{
      cout<<"Error[Table]: Missing key"<<endl;
      exit(1);
    }
    
    return 0;
}

//check method for table
void check(bool b, string mess){

  if(!b){
    cout<<mess<<endl;
    exit(1);
  }
}

//pre-condition; the table inputed is defined
//runs through each element of the table and checks to see if the
//table has a value, if so output it
ostream & operator <<(ostream & out,const Table & t){
  
  double listSize = 0;
  double entries = 0;
  out<<"-------------------"<<endl;
  
  for(int i = 0; i<t.size; i++){
    if(t.table[i] != NULL){
      entries++;
      out<<i;
      Rek *temp =t.table[i];
      while(temp != NULL){
	listSize++;
	out<<*temp;
	temp = temp->next;
      }
      out<<endl;
    }
  }
  
  out<<"--------------------"<<endl;
  out<<"There are "<<entries<<" entries, requiring an average of "<<listSize/entries<< " looks to find"<<endl;

  return out;
  
}

//pre-conditon: a vaild number is put int as an integer
//cheks to see if the number inputed is prime
bool Table::isPrime(int num){

  int counter = 0;
  for(int i = 2; i < num; i++){
    if(num % i == 0)
      counter++;
  }

  if(counter > 0)
    return false;

  else
    return true; 
}

//precondition: a valid k(key) is put in
//postcondition:a true is output if the k(key) is found in the
//dynamic array. A false is output if it is not found
bool Table::inTable(const Key &k)const{

  int hash = k.hash() % size;
  bool found = false;
  Rek * temp = table[hash];
  while(temp != NULL && !found){
    if(temp->getKey() == k)
      found = true;
    else
      temp = temp->next;
  }

     return found;
}
