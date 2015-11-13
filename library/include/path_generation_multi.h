//path_generation_multi.h

/*
use of ublas - lu vs cholesky
*/

#ifndef PATH_MULTI_H
#define PATH_MULTI_H

#include <path_generation.h>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>

using namespace boost::numeric::ublas;

class PathGenerationMulti: public PathGeneration
{
//Generate vector of correl. asset prices

public:
		PathGenerationMulti(shared_ptr<RandomBase>& TheGenerator_,
												const MJArray& Spot0_,
												double T_,
												const MJArray& r0_,
												unsigned long steps_,
												matrix<double> cov_);
		 ~PathGenerationMulti(){}
		 unsigned long GetSize() const { return Spot0.size(); }

		 virtual void SetSteps(unsigned long steps_);

		 double GetOnePath(args& args_) const;
		 MJArray GetWholePath(args& args_);

		 MJArray GetOnePathMulti(args& args_) const;
		 matrix<double> GetWholePathMulti(args& args_);

private:
		MJArray Spot0;
		MJArray drift;
		MJArray r;

		matrix<double> cov;
		matrix<double> A; //pseudo-square mat
};

#endif
