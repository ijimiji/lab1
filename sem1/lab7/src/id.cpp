#include "id.h"
int UniqueID::nextID = 0;

UniqueID::UniqueID() {
   value = ++nextID;
}

