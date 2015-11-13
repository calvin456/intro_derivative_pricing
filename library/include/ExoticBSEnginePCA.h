//  ExoticBSEnginePCA.h

#ifndef EXOTIC_BS_ENGINE_PCA_H
#define EXOTIC_BS_ENGINE_PCA_H

#include <ExoticEngine.h>
#include <Random2.h>

#include <ql/quantlib.hpp>

# include <boost/numeric/ublas/matrix.hpp>
# include <boost/numeric/ublas/io.hpp >

using namespace boost::numeric::ublas;


class ExoticBSEnginePCA : public ExoticEngine
{
public:

      ExoticBSEnginePCA(const Wrapper<PathDependent>& TheProduct_,
						const Parameters& R_,
						const Parameters& D_,
						const Parameters& Vol_,
						const Wrapper<RandomBase>& TheGenerator_,
						double Spot_,
						bool speed_up_=false);

      virtual void GetOnePath(MJArray& LogSpotValues);
      virtual ~ExoticBSEnginePCA(){}


private:

    Wrapper<RandomBase> TheGenerator;
    MJArray Drifts;
    MJArray StandardDeviations;
    double LogSpot;
    unsigned long NumberOfTimes;
    MJArray Variates;

    matrix<double> A;

};

#endif
