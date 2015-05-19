/*Marc Greenspan
  mag216
  cse109
  p6
*/

#include "rek.h"

//get method for key. returns key
const Key & Rek::getKey()const{ return key;}

//two are constructor for rek that initalizes the key and data. This
//also sets the next pointer to null 
Rek::Rek(const Key&k,int d):key(k),data(d){next=NULL;}

//outputs the key and data for an instance of rek
ostream & operator<<(ostream & out, const Rek&r){
  return out<<"{"<<r.key<<", "<<r.data<<"}";
}
