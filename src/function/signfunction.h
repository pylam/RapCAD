#ifndef SIGNFUNCTION_H
#define SIGNFUNCTION_H

#include "function.h"
#include "context.h"

class SignFunction : public Function
{
public:
	SignFunction();
	decimal sign(decimal);
	Value* evaluate(Context*);
};

#endif // SIGNFUNCTION_H
