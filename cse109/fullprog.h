/*Marc Greenspan
  cse109
  p9
  kalafut
*/

#include "ProgChip.h"
#include <cstdlib>
#include <cstring>

class FullProg: public ProgChip{
public:
  FullProg();
  ~FullProg();
private:
  virtual void doExpression();
  void doTerm();
  void doFactor();
public:
  void check(bool b, string mess);
};
