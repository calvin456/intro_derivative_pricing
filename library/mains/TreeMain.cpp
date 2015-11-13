//
//
//                      TreeMain.cpp
//
//
//      
/*
requires
    Arrays.cpp
    BinomialTree.cpp
    BlackScholesFormulas.cpp
    Normals.cpp
    Parameters.cpp
    PayOff3.cpp
    PayOffBridge.cpp
    PayOffForward.cpp
    TreeAmerican.cpp
    TreeEuropean.cpp
    TreeMain.cpp
    TreeProducts.cpp
  */

//Minor editing

/*

ex 16.1 use as benchmark

1>               7464 ms  Build                                      1 calls
1>
1>Target Performance Summary:
1>        0 ms  AfterBuild                                 1 calls
1>        0 ms  ComputeManifestGeneratedLinkerInputs       1 calls
1>        0 ms  ResolveReferences                          1 calls
1>        0 ms  GetCopyToOutputDirectoryXamlAppDefs        1 calls
1>        0 ms  _CheckForCompileOutputs                    1 calls
1>        0 ms  GetResolvedWinMD                           1 calls
1>        0 ms  _Manifest                                  1 calls
1>        0 ms  _SelectedFiles                             1 calls
1>        0 ms  PostBuildEvent                             1 calls
1>        0 ms  AfterBuildGenerateSources                  1 calls
1>        0 ms  _Midl                                      1 calls
1>        0 ms  _ClCompile                                 1 calls
1>        0 ms  CreateCustomManifestResourceNames          1 calls
1>        0 ms  ResolveAssemblyReferences                  1 calls
1>        0 ms  BeforeLink                                 1 calls
1>        0 ms  ComputeCLInputPDBName                      1 calls
1>        0 ms  AfterBuildCompileEvent                     1 calls
1>        0 ms  _BuildLinkAction                           1 calls
1>        0 ms  BeforeResourceCompile                      1 calls
1>        0 ms  SelectCustomBuild                          1 calls
1>        0 ms  AfterMidl                                  1 calls
1>        0 ms  MakeDirsForCl                              1 calls
1>        0 ms  ExpandSDKReferences                        1 calls
1>        0 ms  BuildGenerateSources                       1 calls
1>        0 ms  _CopySourceItemsToOutputDirectory          1 calls
1>        0 ms  GetFrameworkPaths                          1 calls
1>        0 ms  AfterResourceCompile                       1 calls
1>        0 ms  _Xsd                                       1 calls
1>        0 ms  ComputeCustomBuildOutput                   1 calls
1>        0 ms  MakeDirsForBscMake                         1 calls
1>        0 ms  _GenerateSatelliteAssemblyInputs           1 calls
1>        0 ms  BuildCompileTraverse                       1 calls
1>        0 ms  _ResourceCompile                           1 calls
1>        0 ms  Build                                      1 calls
1>        0 ms  _Link                                      1 calls
1>        0 ms  BuildLinkTraverse                          1 calls
1>        0 ms  ComputeManifestInputsTargets               1 calls
1>        0 ms  ComputeRCOutputs                           1 calls
1>        0 ms  _XdcMake                                   1 calls
1>        0 ms  CreateSatelliteAssemblies                  1 calls
1>        0 ms  CopyFilesToOutputDirectory                 1 calls
1>        0 ms  ComputeLinkInputsFromProject               1 calls
1>        0 ms  PreLinkEvent                               1 calls
1>        0 ms  ComputeMIDLGeneratedCompileInputs          1 calls
1>        0 ms  _PrepareForReferenceResolution             1 calls
1>        0 ms  BeforeResolveReferences                    1 calls
1>        0 ms  _Deploy                                    1 calls
1>        0 ms  ComputeReferenceCLInput                    1 calls
1>        0 ms  PrepareForRun                              1 calls
1>        0 ms  PreBuildEvent                              1 calls
1>        0 ms  MakeDirsForMidl                            1 calls
1>        0 ms  _BscMake                                   1 calls
1>        0 ms  _Appverifier                               1 calls
1>        0 ms  AfterResolveReferences                     1 calls
1>        0 ms  RegisterOutput                             1 calls
1>        0 ms  BuildLink                                  1 calls
1>        0 ms  ComputeCLCompileGeneratedSbrFiles          1 calls
1>        0 ms  ResolveSDKReferences                       1 calls
1>        0 ms  _ALink                                     1 calls
1>        0 ms  ComputeCLGeneratedLinkInputs               1 calls
1>        0 ms  _SplitProjectReferencesByFileExistence     1 calls
1>        0 ms  BuildGenerateSourcesTraverse               1 calls
1>        0 ms  ComputeLegacyManifestEmbedding             1 calls
1>        0 ms  _BuildGenerateSourcesAction                1 calls
1>        0 ms  BeforeClCompile                            1 calls
1>        0 ms  DoLinkOutputFilesMatch                     1 calls
1>        0 ms  PrepareResourceNames                       1 calls
1>        0 ms  PlatformPrepareForBuild                    1 calls
1>        0 ms  MakeDirsForXdcMake                         1 calls
1>        0 ms  AfterBuildGenerateSourcesEvent             1 calls
1>        0 ms  GetInstalledSDKLocations                   1 calls
1>        0 ms  _BuildCompileAction                        1 calls
1>        0 ms  ResolvedXDCMake                            1 calls
1>        0 ms  BeforeBuildGenerateSources                 1 calls
1>        0 ms  AssignProjectConfiguration                 1 calls
1>        0 ms  ComputeRCGeneratedLinkInputs               1 calls
1>        0 ms  SplitResourcesByCulture                    1 calls
1>        0 ms  AfterLink                                  1 calls
1>        0 ms  BuildCompile                               1 calls
1>        0 ms  AfterClCompile                             1 calls
1>        1 ms  _PrepareForBuild                           1 calls
1>        1 ms  GetReferenceAssemblyPaths                  1 calls
1>        1 ms  ComputeCLOutputs                           1 calls
1>        1 ms  ComputeLinkImportLibraryOutputsForClean    1 calls
1>        1 ms  ResolveProjectReferences                   1 calls
1>        1 ms  GetCopyToOutputDirectoryItems              1 calls
1>        1 ms  AssignTargetPaths                          1 calls
1>        1 ms  ComputeLinkSwitches                        1 calls
1>        1 ms  SetBuildDefaultEnvironmentVariables        1 calls
1>        1 ms  ComputeCLCompileGeneratedXDCFiles          1 calls
1>        1 ms  SelectClCompile                            1 calls
1>        1 ms  MakeDirsForResourceCompile                 1 calls
1>        2 ms  MakeDirsForLink                            1 calls
1>        3 ms  FinalizeBuildStatus                        1 calls
1>        3 ms  WarnCompileDuplicatedFilename              1 calls
1>        3 ms  PrepareForBuild                            1 calls
1>        3 ms  _CheckForInvalidConfigurationAndPlatform   1 calls
1>        3 ms  InitializeBuildStatus                      1 calls
1>       14 ms  SetCABuildNativeEnvironmentVariables       1 calls
1>     1921 ms  Link                                       1 calls
1>     5495 ms  ClCompile                                  1 calls
1>
1>Build succeeded.
1>
1>Time Elapsed 00:00:07.46

*/

#include <BinomialTree.h>
#include <TreeAmerican.h>
#include <TreeEuropean.h>

#include <BlackScholesFormulas.h>
#include <PayOffForward.h>

#include <iostream>
using namespace std;
#include <cmath>

int main()
{

	double Expiry;
	double Strike;
	
	double Spot; 
	double Vol; 
	double r;
    double d;
	unsigned long Steps;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nStrike\n";
	cin >> Strike;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

    cout << "\nd\n";
    cin >> d;

    cout << "\nNumber of steps\n";
	cin >> Steps;

    PayOffCall thePayOff(Strike);
	
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);

    TreeEuropean europeanOption(Expiry,thePayOff);
    TreeAmerican americanOption(Expiry,thePayOff);

    SimpleBinomialTree theTree(Spot,rParam,dParam,Vol,Steps,Expiry);
    double euroPrice = theTree.GetThePrice(europeanOption);
    double americanPrice = theTree.GetThePrice(americanOption);

    cout << endl << "euro price " << euroPrice << " amer price " << americanPrice << "\n";

    double BSPrice = BlackScholesCall(Spot,Strike,r,d,Vol,Expiry);
	cout << endl << "BS formula euro price " << BSPrice << "\n";
    
    PayOffForward forwardPayOff(Strike);
    TreeEuropean forward(Expiry,forwardPayOff);

    double forwardPrice = theTree.GetThePrice(forward);
	cout << endl << "forward price by tree " << forwardPrice << "\n";

    double actualForwardPrice = exp(-r*Expiry)*(Spot*exp((r-d)*Expiry)-Strike);
	cout << endl << "forward price " << actualForwardPrice << "\n";

	cout << endl << "Add 1 step " << endl;

    Steps++; // now redo the trees with one more step
    SimpleBinomialTree theNewTree(Spot,rParam,dParam,Vol,Steps,Expiry);

    double euroNewPrice = theNewTree.GetThePrice(europeanOption);
    double americanNewPrice = theNewTree.GetThePrice(americanOption);

	cout << endl << "euro new price " << euroNewPrice << " amer new price " << americanNewPrice << "\n";

    double forwardNewPrice = theNewTree.GetThePrice(forward);

	cout << endl << "forward price by new tree " << forwardNewPrice << "\n";

    double averageEuro = 0.5*(euroPrice + euroNewPrice);
    double averageAmer = 0.5*(americanPrice + americanNewPrice);
    double averageForward = 0.5*(forwardPrice + forwardNewPrice);

	cout << endl << "euro av price " << averageEuro << " amer av price " << averageAmer << "\n";
	cout << endl << "av forward " << averageForward << "\n";

    double tmp;
    cin >> tmp;

	return 0;
}

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

