#include "VMObject.h"
#include <cstring>
VMObject::VMObject()
{
	memset(this, 0, sizeof(VMObject));
}
