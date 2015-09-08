/*Test American knock-in option

American option pricing higher than European
use trinomial tree

*/
#include<TreeAmerican.h>
#include<TreeEuropean.h>
#include<BarrierOption.h>
#include<TreeBarrier.h>
#include<TreeAmericanBarrier.h>

#include<TrinomialTree.h>

#include <iostream>
#include <vector>

using namespace std;


#include <iostream>
using namespace std;
#include <cmath>
int main()
{

	double Expiry;
	double Strike(100.0);

	double Barrier(100.0);

	double Spot(100.0);
	double Vol;
	double r;
	double d;
	unsigned long Steps;

	cout << "ATM KI options with 15% barrier from strike" << endl;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	//cout << "\nStrike\n";
	//cin >> Strike;

	//cout << "\nBarrier\n";
	//cin >> Barrier;

	//cout << "\nEnter spot\n";
	//cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

	cout << "\nd\n";
	cin >> d;

	cout << "\nNumber of steps\n";
	cin >> Steps;
	cout << endl;

	PayOffCall thePayOffCall(Strike);
	PayOffPut thePayOffPut(Strike);

	PayOffKOCall thePayOffKOCall(Barrier*1.15, Strike);
	PayOffKOPut thePayOffKOPut(Barrier*.85, Strike);

	PayOffKICall thePayOffKICall(Barrier*1.15, Strike);
	PayOffKIPut thePayOffKIPut(Barrier*.85, Strike);

	ParametersConstant rParam(r);
	ParametersConstant dParam(d);

	//pricing american ki options
	TreeAmericanBarrier americanKICall(Expiry, thePayOffKICall);
	TreeAmericanBarrier americanKIPut(Expiry, thePayOffKIPut);
	//pricing american ko options
	TreeAmericanBarrier americanKOCall(Expiry, thePayOffKOCall);
	TreeAmericanBarrier americanKOPut(Expiry, thePayOffKOPut);

	TreeAmerican americanCall(Expiry, thePayOffCall);
	TreeAmerican americanPut(Expiry, thePayOffPut);

	TrinomialTree theTree(Spot, rParam, dParam, Vol, Steps, Expiry);

	double americanKICall1 = theTree.GetThePrice(americanKICall);

	double americanKIPut1 = theTree.GetThePrice(americanKIPut);

	cout << "trinomial tree pricing:" << endl;
	cout << "American KI call " << americanKICall1 << endl;
	cout << "American KI put " << americanKIPut1 << endl;
	cout << endl;

	//test ki + ko = plain American option

	double americanKOCall1 = theTree.GetThePrice(americanKOCall);

	double americanKOPut1 = theTree.GetThePrice(americanKOPut);

	double americanCall1 = theTree.GetThePrice(americanCall);

	double americanPut1 = theTree.GetThePrice(americanPut);

	/*
	ko + ki does not equal kncokless for American options.

	Pricing and hedging of American ki options, Farid AitSahlia, Lorens Imhof, and Tze Leung Lai

	available at bear.warrington.ufl.edu/aitsahlia/AIL_JOD_04.pdf

	Since the suprema in Equations (2)-(4) are attained
	at different stopping times, the price of a standard American
	option cannot be decomposed as in (1) into the sum
	of the corresponding American knock-in and knock-out
	options.

	*/

	cout << "trinomial tree pricing:" << endl;
	cout << "American  call " << americanCall1 << endl;
	cout << "American  KO call " << americanKOCall1 << endl;
	cout << "American KO + KI call " << americanKOCall1 + americanKICall1 << endl;
	cout << endl;
	cout << "American  put " << americanPut1 << endl;
	cout << "American  KO put " << americanKOPut1 << endl;
	cout << "American KO + KI put " << americanKOPut1 + americanKIPut1 << endl;

	cout << endl;
	//----------------------------------------------------------------------------------
	//pricing american ki options
	TreeBarrier europeanKICall(Expiry, thePayOffKICall);
	TreeBarrier europeanKIPut(Expiry, thePayOffKIPut);
	//pricing american ko options
	TreeBarrier europeanKOCall(Expiry, thePayOffKOCall);
	TreeBarrier europeanKOPut(Expiry, thePayOffKOPut);

	TreeEuropean europeanCall(Expiry, thePayOffCall);
	TreeEuropean europeanPut(Expiry, thePayOffPut);

	double europeanKICall1 = theTree.GetThePrice(europeanKICall);

	double europeanKIPut1 = theTree.GetThePrice(europeanKIPut);

	cout << "trinomial tree pricing:" << endl;
	cout << "European KI call " << europeanKICall1 << endl;
	cout << "European KI put " << europeanKIPut1 << endl;
	cout << endl;

	//test ki + ko = plain American option

	double europeanKOCall1 = theTree.GetThePrice(europeanKOCall);

	double europeanKOPut1 = theTree.GetThePrice(europeanKOPut);

	double europeanCall1 = theTree.GetThePrice(europeanCall);

	double europeanPut1 = theTree.GetThePrice(europeanPut);

	cout << "trinomial tree pricing:" << endl;
	cout << "European  call " << europeanCall1 << endl;
	cout << "European KO + KI call " << europeanKOCall1 + europeanKICall1 << endl;
	cout << "European  put " << europeanPut1 << endl;
	cout << "European KO + KI put " << europeanKOPut1 + europeanKIPut1 << endl;

	cout << endl;
	//------------------------------------------------------------------------------------


	double tmp;
	cin >> tmp;

	return 0;
}
