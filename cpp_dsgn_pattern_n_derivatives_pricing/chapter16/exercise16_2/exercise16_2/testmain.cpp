//test main

//test pimpl idiom with call option

/*
1>               1541 ms  Build                                      1 calls
1>
1>Target Performance Summary:
1>        0 ms  AfterBuild                                 1 calls
1>        0 ms  ComputeManifestGeneratedLinkerInputs       1 calls
1>        0 ms  ResolveReferences                          1 calls
1>        0 ms  SelectClCompile                            1 calls
1>        0 ms  GetCopyToOutputDirectoryXamlAppDefs        1 calls
1>        0 ms  _CheckForCompileOutputs                    1 calls
1>        0 ms  GetResolvedWinMD                           1 calls
1>        0 ms  _Manifest                                  1 calls
1>        0 ms  _SelectedFiles                             1 calls
1>        0 ms  _PrepareForBuild                           1 calls
1>        0 ms  PostBuildEvent                             1 calls
1>        0 ms  _Midl                                      1 calls
1>        0 ms  SelectCustomBuild                          1 calls
1>        0 ms  _ClCompile                                 1 calls
1>        0 ms  GetReferenceAssemblyPaths                  1 calls
1>        0 ms  CreateCustomManifestResourceNames          1 calls
1>        0 ms  ResolveAssemblyReferences                  1 calls
1>        0 ms  BeforeLink                                 1 calls
1>        0 ms  ComputeCLInputPDBName                      1 calls
1>        0 ms  AfterBuildCompileEvent                     1 calls
1>        0 ms  ComputeCLCompileGeneratedXDCFiles          1 calls
1>        0 ms  AfterBuildGenerateSources                  1 calls
1>        0 ms  BuildCompileTraverse                       1 calls
1>        0 ms  ExpandSDKReferences                        1 calls
1>        0 ms  BuildGenerateSources                       1 calls
1>        0 ms  _CopySourceItemsToOutputDirectory          1 calls
1>        0 ms  ComputeLinkImportLibraryOutputsForClean    1 calls
1>        0 ms  GetFrameworkPaths                          1 calls
1>        0 ms  AfterResourceCompile                       1 calls
1>        0 ms  _Xsd                                       1 calls
1>        0 ms  ComputeCustomBuildOutput                   1 calls
1>        0 ms  MakeDirsForBscMake                         1 calls
1>        0 ms  _GenerateSatelliteAssemblyInputs           1 calls
1>        0 ms  _BuildLinkAction                           1 calls
1>        0 ms  MakeDirsForResourceCompile                 1 calls
1>        0 ms  ComputeLinkInputsFromProject               1 calls
1>        0 ms  Build                                      1 calls
1>        0 ms  _Link                                      1 calls
1>        0 ms  BuildLinkTraverse                          1 calls
1>        0 ms  ComputeManifestInputsTargets               1 calls
1>        0 ms  ComputeRCOutputs                           1 calls
1>        0 ms  _XdcMake                                   1 calls
1>        0 ms  CreateSatelliteAssemblies                  1 calls
1>        0 ms  CopyFilesToOutputDirectory                 1 calls
1>        0 ms  _ResourceCompile                           1 calls
1>        0 ms  BeforeResourceCompile                      1 calls
1>        0 ms  ComputeMIDLGeneratedCompileInputs          1 calls
1>        0 ms  PreLinkEvent                               1 calls
1>        0 ms  AfterResolveReferences                     1 calls
1>        0 ms  AfterMidl                                  1 calls
1>        0 ms  DoLinkOutputFilesMatch                     1 calls
1>        0 ms  ComputeReferenceCLInput                    1 calls
1>        0 ms  PrepareForRun                              1 calls
1>        0 ms  PreBuildEvent                              1 calls
1>        0 ms  MakeDirsForMidl                            1 calls
1>        0 ms  _BscMake                                   1 calls
1>        0 ms  BeforeClCompile                            1 calls
1>        0 ms  _Appverifier                               1 calls
1>        0 ms  _BuildGenerateSourcesAction                1 calls
1>        0 ms  BuildLink                                  1 calls
1>        0 ms  ComputeCLCompileGeneratedSbrFiles          1 calls
1>        0 ms  ResolveSDKReferences                       1 calls
1>        0 ms  _ALink                                     1 calls
1>        0 ms  ComputeCLGeneratedLinkInputs               1 calls
1>        0 ms  _SplitProjectReferencesByFileExistence     1 calls
1>        0 ms  BuildGenerateSourcesTraverse               1 calls
1>        0 ms  RegisterOutput                             1 calls
1>        0 ms  AfterBuildGenerateSourcesEvent             1 calls
1>        0 ms  BeforeResolveReferences                    1 calls
1>        0 ms  AfterLink                                  1 calls
1>        0 ms  _Deploy                                    1 calls
1>        0 ms  _PrepareForReferenceResolution             1 calls
1>        0 ms  BeforeBuildGenerateSources                 1 calls
1>        0 ms  PrepareResourceNames                       1 calls
1>        0 ms  PlatformPrepareForBuild                    1 calls
1>        0 ms  MakeDirsForXdcMake                         1 calls
1>        0 ms  GetInstalledSDKLocations                   1 calls
1>        0 ms  AfterClCompile                             1 calls
1>        0 ms  AssignProjectConfiguration                 1 calls
1>        0 ms  SplitResourcesByCulture                    1 calls
1>        0 ms  BuildCompile                               1 calls
1>        0 ms  _BuildCompileAction                        1 calls
1>        0 ms  ComputeRCGeneratedLinkInputs               1 calls
1>        1 ms  ComputeLinkSwitches                        1 calls
1>        1 ms  AssignTargetPaths                          1 calls
1>        1 ms  ComputeLegacyManifestEmbedding             1 calls
1>        1 ms  WarnCompileDuplicatedFilename              1 calls
1>        1 ms  ResolvedXDCMake                            1 calls
1>        1 ms  MakeDirsForCl                              1 calls
1>        1 ms  ResolveProjectReferences                   1 calls
1>        1 ms  GetCopyToOutputDirectoryItems              1 calls
1>        1 ms  ComputeCLOutputs                           1 calls
1>        2 ms  SetBuildDefaultEnvironmentVariables        1 calls
1>        2 ms  MakeDirsForLink                            1 calls
1>        3 ms  _CheckForInvalidConfigurationAndPlatform   1 calls
1>        3 ms  FinalizeBuildStatus                        1 calls
1>        3 ms  PrepareForBuild                            1 calls
1>        4 ms  InitializeBuildStatus                      1 calls
1>       22 ms  SetCABuildNativeEnvironmentVariables       1 calls
1>      674 ms  ClCompile                                  1 calls
1>      812 ms  Link                                       1 calls
1>
1>Build succeeded.
1>
1>Time Elapsed 00:00:01.53

*/

#include <iostream>
#include <memory>
#include"VanillaOption.h"

using namespace std;

int main(){

	double Strike(100.0); cout << "Strike : " << Strike << endl;
	double Expiry(.25); cout << "Expiry : " << Expiry << endl;

	cout << "option 1 call ";
	unique_ptr<VanillaOption> myOption(new VanillaOption(new PayOffCall(Strike), Expiry));

	cout << "payoff with spot 110 : ";
	cout << myOption->OptionPayOff(110.0) << endl;

	cout << "option 2 call ";
	unique_ptr<VanillaOption> myOption1(new VanillaOption(new PayOffCall(Strike), Expiry));

	cout << "payoff with spot 120 : ";
	cout << myOption1->OptionPayOff(120.0) << endl;

	double tmp;
	cin >> tmp;

	return 0;
}