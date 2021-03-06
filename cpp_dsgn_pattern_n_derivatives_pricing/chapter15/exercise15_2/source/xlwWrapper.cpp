//// 
//// Autogenerated by xlw 
//// Do not edit this file, it will be overwritten 
//// by InterfaceGenerator 
////

#include "xlw/MyContainers.h"
#include <xlw/CellMatrix.h>
#include "cppinterface.h"
#include <xlw/xlw.h>
#include <xlw/XlFunctionRegistration.h>
#include <stdexcept>
#include <xlw/XlOpenClose.h>
#include <xlw/HiResTimer.h>
using namespace xlw;

namespace {
const char* LibraryName = "152Library";
};


// registrations start here


namespace
{
XLRegistration::Arg
_BlackScholesCallArgs[]=
{
{ "Spot","too lazy to comment this one ","B"},
{ "Strike","too lazy to comment this one ","B"},
{ "r","too lazy to comment this one ","B"},
{ "d","too lazy to comment this one ","B"},
{ "Vol","too lazy to comment this one ","B"},
{ "Expiry","too lazy to comment this one ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
register_BlackScholesCall("xl_BlackScholesCall",
"_BlackScholesCall",
"too lazy to comment this function ",
LibraryName,
_BlackScholesCallArgs,
6
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xl_BlackScholesCall(
double Spot,
double Strike,
double r,
double d,
double Vol,
double Expiry)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);







double result(
	_BlackScholesCall(
		Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
_BlackScholesPutArgs[]=
{
{ "Spot","too lazy to comment this one ","B"},
{ "Strike","too lazy to comment this one ","B"},
{ "r","too lazy to comment this one ","B"},
{ "d","too lazy to comment this one ","B"},
{ "Vol","too lazy to comment this one ","B"},
{ "Expiry","too lazy to comment this one ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
register_BlackScholesPut("xl_BlackScholesPut",
"_BlackScholesPut",
"too lazy to comment this function ",
LibraryName,
_BlackScholesPutArgs,
6
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xl_BlackScholesPut(
double Spot,
double Strike,
double r,
double d,
double Vol,
double Expiry)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);







double result(
	_BlackScholesPut(
		Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
_BlackScholesDigitalCallArgs[]=
{
{ "Spot","too lazy to comment this one ","B"},
{ "Strike","too lazy to comment this one ","B"},
{ "r","too lazy to comment this one ","B"},
{ "d","too lazy to comment this one ","B"},
{ "Vol","too lazy to comment this one ","B"},
{ "Expiry","too lazy to comment this one ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
register_BlackScholesDigitalCall("xl_BlackScholesDigitalCall",
"_BlackScholesDigitalCall",
"too lazy to comment this function ",
LibraryName,
_BlackScholesDigitalCallArgs,
6
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xl_BlackScholesDigitalCall(
double Spot,
double Strike,
double r,
double d,
double Vol,
double Expiry)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);







double result(
	_BlackScholesDigitalCall(
		Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
_BlackScholesDigitalPutArgs[]=
{
{ "Spot","too lazy to comment this one ","B"},
{ "Strike","too lazy to comment this one ","B"},
{ "r","too lazy to comment this one ","B"},
{ "d","too lazy to comment this one ","B"},
{ "Vol","too lazy to comment this one ","B"},
{ "Expiry","too lazy to comment this one ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
register_BlackScholesDigitalPut("xl_BlackScholesDigitalPut",
"_BlackScholesDigitalPut",
"too lazy to comment this function ",
LibraryName,
_BlackScholesDigitalPutArgs,
6
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xl_BlackScholesDigitalPut(
double Spot,
double Strike,
double r,
double d,
double Vol,
double Expiry)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);







double result(
	_BlackScholesDigitalPut(
		Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
_BlackScholesCallVegaArgs[]=
{
{ "Spot","too lazy to comment this one ","B"},
{ "Strike","too lazy to comment this one ","B"},
{ "r","too lazy to comment this one ","B"},
{ "d","too lazy to comment this one ","B"},
{ "Vol","too lazy to comment this one ","B"},
{ "Expiry","too lazy to comment this one ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
register_BlackScholesCallVega("xl_BlackScholesCallVega",
"_BlackScholesCallVega",
"too lazy to comment this function ",
LibraryName,
_BlackScholesCallVegaArgs,
6
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xl_BlackScholesCallVega(
double Spot,
double Strike,
double r,
double d,
double Vol,
double Expiry)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);







double result(
	_BlackScholesCallVega(
		Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

//////////////////////////
// Methods that will get registered to execute in AutoOpen
//////////////////////////

//////////////////////////
// Methods that will get registered to execute in AutoClose
//////////////////////////

