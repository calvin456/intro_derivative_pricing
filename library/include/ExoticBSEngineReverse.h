//  ExoticBSEngineReverse.h

#ifndef EXOTIC_BS_ENGINE_REVERSE__H
#define EXOTIC_BS_ENGINE_REVERSE_H

#include <ExoticEngine.h>
#include <Random2.h>

#include <ql/quantlib.hpp>

# include <boost/numeric/ublas/matrix.hpp>
# include <boost/numeric/ublas/io.hpp >

using namespace boost::numeric::ublas;
using namespace QuantLib;

class ExoticBSEngineReverse : public ExoticEngine
{
public:

	ExoticBSEngineReverse(const Wrapper<PathDependent>& TheProduct_,
                     const Parameters& R_,
                     const Parameters& D_,
                     const Parameters& Vol_,
                     const Wrapper<RandomBase>& TheGenerator_,
                     double Spot_,
					 bool speed_up_=false);

      virtual void GetOnePath(MJArray& LogSpotValues);
	  virtual ~ExoticBSEngineReverse(){}


private:

    Wrapper<RandomBase> TheGenerator;
    MJArray Drifts;
    MJArray StandardDeviations;
    double LogSpot;
    unsigned long NumberOfTimes;
    MJArray Variates;

	boost::numeric::ublas::matrix<double> A;

};

#endif
