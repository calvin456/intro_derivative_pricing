// FPSetup.cpp

/* Reproduced from 13.8 Floating point exceptions, p.187-192, C++ Design Patterns and Derivatives Pricing,
2nd ed, Mark S. Joshi, 2008
*/

#include "FPSetup.h"
#include <float.h>

void se_fe_trans_func(unsigned int u,
	EXCEPTION_POINTERS* pExp)
{
	switch (u)
	{
	case STATUS_FLOAT_DENORMAL_OPERAND:
		throw fe_denormal_operand();
	case STATUS_FLOAT_DIVIDE_BY_ZERO:
		throw fe_divide_by_zero();
	case STATUS_FLOAT_INEXACT_RESULT:
		throw fe_inexact_result();
	case STATUS_FLOAT_INVALID_OPERATION:
		throw fe_invalid_operation();
	case STATUS_FLOAT_OVERFLOW:
		throw fe_overflow();
	case STATUS_FLOAT_UNDERFLOW:
		throw fe_underflow();
	case STATUS_FLOAT_STACK_CHECK:
		throw fe_stack_check();
		
	};

	throw float_exception();

}

void EnableFloatingPointExceptions()
{
	_set_se_translator(se_fe_trans_func);
	_controlfp(_EM_INVALID, _MCW_EM); //_controlfp_ deprecated. Use _controlfp_s
}
