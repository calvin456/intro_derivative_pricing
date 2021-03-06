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
#include <xlw/ArgList.h>

using namespace xlw;

namespace {
const char* LibraryName = "MyRNGLibrary";
};


// registrations start here


namespace
{
XLRegistration::Arg
GetUniformsArgs[]=
{
{ "RandomTable"," table for RNG ","XLF_OPER"},
{ "seed","too lazy to comment this one ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerGetUniforms("xlGetUniforms",
"GetUniforms",
" generate pseudo random numbers using spec generator ",
LibraryName,
GetUniformsArgs,
2
,true
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
xlGetUniforms(
LPXLFOPER RandomTablea,
double seed)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper RandomTableb(
	(RandomTablea));
CellMatrix RandomTablec(
	RandomTableb.AsCellMatrix("RandomTablec"));
ArgumentList RandomTabled(
	ArgumentList(RandomTablec,"RandomTabled"));
Wrapper<RandomBaseXlw> RandomTable(
	GetFromFactory<RandomBaseXlw>(RandomTabled));


 HiResTimer t;
CellMatrix result(
	GetUniforms(
		RandomTable,
		seed)
	);
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t.elapsed();
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
GetGaussiansArgs[]=
{
{ "RandomTable"," table for RNG ","XLF_OPER"},
{ "seed","too lazy to comment this one ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerGetGaussians("xlGetGaussians",
"GetGaussians",
" generate pseudo random number using spec generator ",
LibraryName,
GetGaussiansArgs,
2
,true
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
xlGetGaussians(
LPXLFOPER RandomTablea,
double seed)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper RandomTableb(
	(RandomTablea));
CellMatrix RandomTablec(
	RandomTableb.AsCellMatrix("RandomTablec"));
ArgumentList RandomTabled(
	ArgumentList(RandomTablec,"RandomTabled"));
Wrapper<RandomBaseXlw> RandomTable(
	GetFromFactory<RandomBaseXlw>(RandomTabled));


 HiResTimer t;
CellMatrix result(
	GetGaussians(
		RandomTable,
		seed)
	);
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t.elapsed();
resultCells.PushBottom(time);
return XlfOper(resultCells);
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

