//-----------------------------------------------------------------------------
// Project     : VST SDK
//
// Category    : Validator
// Filename    : validator.cpp
// Created by  : Steinberg, 04/2005
// Description : VST 3 Plug-in Validator class
//
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2017, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation 
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this 
//     software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#include "validator.h"
#include "public.sdk/source/vst/hosting/plugprovider.h"

#include "public.sdk/source/vst/hosting/stringconvert.h"

#include "pluginterfaces/vst/ivstcomponent.h"
#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "pluginterfaces/vst/ivsthostapplication.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"
#include "pluginterfaces/vst/ivstunits.h"

#include "base/source/fcommandline.h"

namespace Steinberg {
FUnknown* gStandardPluginContext = nullptr;
}

#if WINDOWS
#include <windows.h>
#include <conio.h>
#endif

#include <cstdio>
#include <iostream>

namespace Steinberg {
namespace Vst {

//------------------------------------------------------------------------
// TestSuite
//------------------------------------------------------------------------
class TestSuite : public ITestSuite, public FObject
{
public:
	TestSuite (FIDString _name) : name (_name) {}

	tresult PLUGIN_API addTest (FIDString name, ITest* test) SMTG_OVERRIDE
	{
		tests.push_back (IPtr<Test> (NEW Test (name, test), false));
		return kResultTrue;
	}

	tresult PLUGIN_API addTestSuite (FIDString name, ITestSuite* testSuite) SMTG_OVERRIDE
	{
		testSuites.push_back (std::make_pair (name, testSuite));
		return kResultTrue;
	}

	tresult PLUGIN_API setEnvironment (ITest* environment) SMTG_OVERRIDE
	{
		return kNotImplemented;
	}

	int32 getTestCount () const { return static_cast<int32> (tests.size ()); }

	tresult getTest (int32 index, ITest*& test, std::string& name) const
	{
		Test* _test = tests.at (index);
		if (_test)
		{
			test = _test->test;
			name = _test->name;
			return kResultTrue;
		}
		return kResultFalse;
	}

	tresult getTestSuite (int32 index, ITestSuite*& testSuite, std::string& name) const
	{
		if (index < 0 || index >= testSuites.size ())
			return kInvalidArgument;
		const TestSuitePair& ts = testSuites[index];
		name = ts.first;
		testSuite = ts.second;
		return kResultTrue;
	}

	ITestSuite* getTestSuite (FIDString name) const
	{
		for (TestSuiteVector::const_iterator it = testSuites.cbegin (), end = testSuites.cend ();
		     it != end; ++it)
		{
			if (it->first == name)
				return it->second;
		}
		return nullptr;
	}

	const std::string& getName () const { return name; }
	OBJ_METHODS(TestSuite, FObject)
	REFCOUNT_METHODS(FObject)
	DEF_INTERFACES_1(ITestSuite, FObject)
protected:
	class Test : public FObject
	{
	public:
		Test (FIDString _name, ITest* _test) : name (_name), test (_test) {}
		
		std::string name;
		IPtr<ITest> test;
	};
	std::string name;
	std::vector<IPtr<Test> > tests;

	typedef std::pair<std::string, IPtr<ITestSuite> > TestSuitePair;
	typedef std::vector<TestSuitePair> TestSuiteVector;
	TestSuiteVector testSuites;
};

//------------------------------------------------------------------------
static std::ostream* infoStream = &std::cout;
static std::ostream* errorStream = &std::cout;

//------------------------------------------------------------------------
void printAllInstalledPlugins ()
{
	*infoStream << "Searching installed plug-ins...\n";
	infoStream->flush ();

	auto paths = VST3::Hosting::Module::getModulePaths ();
	if (paths.empty ())
	{
		*infoStream << "No plug-ins found.\n";
		return;
	}
	for (const auto& path : paths)
	{
		*infoStream << path << "\n";
	}
}

//------------------------------------------------------------------------
// Validator
//------------------------------------------------------------------------
Validator::Validator (int argc, char* argv[])
: argc (argc)
, argv (argv)
, testSuite (nullptr)
, numTestsFailed (0)
, numTestsPassed (0)
{ 
	testSuite = new TestSuite ("Tests");
	
	gStandardPluginContext = this->unknownCast ();
	setStandardPluginContext (gStandardPluginContext);
}

//------------------------------------------------------------------------
Validator::~Validator ()
{
    testSuite = nullptr;
    testModule = nullptr;
    module = nullptr;
}

//------------------------------------------------------------------------
void PLUGIN_API Validator::addErrorMessage (const tchar* msg)
{
	if (errorStream)
	{
		auto str = VST3::StringConvert::convert (msg);
		*errorStream << "ERROR: " << str << "\n";
	}
}

//------------------------------------------------------------------------
void PLUGIN_API Validator::addMessage (const tchar* msg)
{
	if (infoStream)
	{
		auto str = VST3::StringConvert::convert (msg);
		*infoStream << "Info:  " << str << "\n";
	}
}

//------------------------------------------------------------------------
tresult PLUGIN_API Validator::getName (String128 name)
{
	VST3::StringConvert::convert ("vstvalidator", name, 127);
	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API Validator::createInstance (TUID cid, TUID iid, void** obj)
{
	FUID classID (cid);
	FUID interfaceID (iid);
	if (classID == IMessage::iid && interfaceID == IMessage::iid)
	{
		*obj = new HostMessage;
		return kResultTrue;
	}
	else if (classID == IAttributeList::iid && interfaceID == IAttributeList::iid)
	{
		*obj = new HostAttributeList;
		return kResultTrue;
	}
    *obj = nullptr;
	return kResultFalse;
}

//------------------------------------------------------------------------
#define kHelpOption	"help"
#define kVersionOption "version"
#define kLocalInstanceOption "l"
#define kSuiteNameOption "suite"
#define kQuietOption "q"
#define kTestComponentPath "test-component"
#define kLookupInstalledPlugIns "list"

//------------------------------------------------------------------------
int Validator::run ()
{
	// defaults
	bool useGlobalInstance = true;
	std::string testSuiteName;

	// parse command line
	CommandLine::Descriptions desc;
	CommandLine::VariablesMap valueMap;
	CommandLine::FilesVector files;
	
	desc.addOptions (kVstVersionString " Plug-in Validator")
		(kHelpOption, CommandLine::Description::kBool, "Print help")
		(kVersionOption, CommandLine::Description::kBool, "Print version")
		(kLocalInstanceOption, CommandLine::Description::kBool, "Use local instance per test")
		(kSuiteNameOption, CommandLine::Description::kString, "[name] Only run a special test suite")
		(kQuietOption, CommandLine::Description::kBool, "Only print errors")
		(kTestComponentPath, CommandLine::Description::kString, "[path] Path to an additional component which includes custom tests")
		(kLookupInstalledPlugIns, CommandLine::Description::kBool, "Show all installed Plug-Ins")
	;
	CommandLine::parse (argc, argv, desc, valueMap, &files);
	if (valueMap.count (kVersionOption))
	{
		std::cout << VALIDATOR_INFO;
		return 0;
	}
	else if (valueMap.count (kLookupInstalledPlugIns))
	{
		printAllInstalledPlugins ();
		return 0;
	}
	else if (valueMap.hasError () || valueMap.count (kHelpOption) || files.size () != 1)
	{
		std::cout << "\n" << desc << "\n";
		std::cout << "Usage: vstvalidator [options] vst3module\n\n";
		return 1;
	}
	
	if (valueMap.count (kLocalInstanceOption))
		useGlobalInstance = false;
	if (valueMap.count (kQuietOption))
        infoStream = nullptr;
	if (valueMap.count (kSuiteNameOption))
		testSuiteName = valueMap[kSuiteNameOption];

	std::string customTestComponentPath;
	if (valueMap.count (kTestComponentPath))
		customTestComponentPath = valueMap[kTestComponentPath];

	const char* path = files.front ().c_str ();

#if WINDOWS
	// TODO: Impl
#else
	std::string absPath;
	// if path is not absolute, create one
	if (path[0] != '/')
	{
		char* realPath = realpath (path, NULL);
		if (realPath)
		{
			absPath.assign (realPath);
			path = absPath.data ();
			free (realPath);
		}
	}
	if (customTestComponentPath.empty () == false && customTestComponentPath[0] != '/')
	{
		char* realPath = realpath (customTestComponentPath.data (), NULL);
		if (realPath)
		{
			customTestComponentPath.assign (realPath);
			free (realPath);
		}
		
	}
#endif

	//---load VST module-----------------
	if (infoStream)
		*infoStream << "* Loading module...\n\n\t" << path << "\n\n";

	std::string error;
	module = Module::create (path, error);
	if (!module)
	{
		*errorStream << "Invalid Module!\n";
		if (!error.empty())
			*errorStream << error << "\n";
		return 0;
	}

	auto factory = module->getFactory ();

	//---print classes-------------------
	if (infoStream)
	{
		*infoStream << "* Scanning classes...\n\n";

		auto factoryInfo = factory.info ();

		*infoStream << "  Factory Info:\n\tvendor = " << factoryInfo.vendor () << "\n\turl = " << factoryInfo.url () << "\n\temail = " << factoryInfo.email () << "\n\n";

		//---print all included Plug-ins---------------
		uint32 i = 0;
		for (auto& classInfo : factory.classInfos ())
		{
			*infoStream << "  Class Info " << i << ":\n\tname = " << classInfo.name () << "\n\tcategory = " << classInfo.category () << "\n\tcid = " << classInfo.ID ().toString() << "\n\n";
			++i;
		}
	}

	typedef std::map<std::string, IPtr<ITestFactory> > TestFactoryMap;
	typedef std::vector<IPtr<PlugProvider> > PlugProviderVector;
	PlugProviderVector plugProviders;
	TestFactoryMap testFactories;

	//---create tests---------------
	if (infoStream)
		*infoStream << "* Creating tests...\n\n";
	for (auto& classInfo : factory.classInfos ())
	{
		if (filterClassCategory (kVstAudioEffectClass, classInfo.category ().data ()))
		{
			PlugProvider* plugProvider = new PlugProvider (factory, classInfo, useGlobalInstance);
			if (plugProvider)
			{
				createTests (plugProvider, classInfo.name ().data ());
				plugProviders.push_back (plugProvider);
				plugProvider->release ();
			}
		}
		else if (filterClassCategory (kTestClass, classInfo.category ().data ()))
		{	// gather test factories supplied by the Plug-in
			if (auto testFactory = factory.createInstance<ITestFactory>(classInfo.ID ()))
			{
				testFactories.insert (std::make_pair (classInfo.name ().data (), testFactory));
			}
		}
	}

	// now check testModule if supplied
	if (customTestComponentPath.empty () == false)
	{
		testModule = Module::create (customTestComponentPath, error);
		if (testModule)
		{
			const auto& factory = testModule->getFactory ();
			for (const auto& classInfo : factory.classInfos ())
			{
				if (filterClassCategory (kTestClass, classInfo.category ().data ()))
				{	// gather test factories supplied by the Plug-in
					if (auto testFactory = factory.createInstance<ITestFactory>(classInfo.ID ()))
					{
						testFactories.insert (std::make_pair (classInfo.name ().data (), testFactory));
					}
				}
			}
		}

	}
	if (infoStream && !testFactories.empty ())
		*infoStream << "* Creating Plug-in supplied tests...\n\n";
	// create Plug-in supplied tests
	for (TestFactoryMap::const_iterator it = testFactories.cbegin (), end = testFactories.cend ();
	     it != end; ++it)
	{
		for (PlugProviderVector::const_iterator it2 = plugProviders.cbegin (),
		                                        end2 = plugProviders.cend ();
		     it2 != end2; ++it2)
		{
			IPtr<TestSuite> plugTestSuite = owned (new TestSuite (it->first.data ()));
			if (it->second->createTests ((*it2)->unknownCast (), plugTestSuite) == kResultTrue)
			{
				testSuite->addTestSuite (plugTestSuite->getName ().data (), plugTestSuite);
			}
		}
	}
	testFactories.clear ();

	//---run tests---------------------------
	if (infoStream)
		*infoStream << "* Running tests...\n\n";

	runTestSuite (testSuite, testSuiteName.empty () ? 0 : testSuiteName.data ());

	if (infoStream)
	{
		*infoStream << SEPARATOR;
		*infoStream << "Result: " << numTestsPassed << " tests passed, " << numTestsFailed << " tests failed\n";
		*infoStream << SEPARATOR;

	#if 0 // WINDOWS && _DEBUG
		// TODO: running the validator as post build step makes the build hang
		*infoStream << "Press any key to continue...";
		getch ();
	#endif
	}
	return numTestsFailed == 0 ? 0 : -1;
}

//------------------------------------------------------------------------
bool Validator::filterClassCategory (FIDString category, FIDString classCategory) const
{
	return strcmp (category, classCategory) == 0;
}

//------------------------------------------------------------------------
namespace { // anonymous

//------------------------------------------------------------------------
template <typename T, typename... Args>
void createTest (ITestSuite* parent, IPlugProvider* plugProvider, Args&&... arguments)
{
	auto test = owned (new T (plugProvider, std::forward<Args> (arguments)...));
	parent->addTest (test->getName (), test);
}

//------------------------------------------------------------------------
void createPrecisionTests (ITestSuite* parent, IPlugProvider* plugProvider, SymbolicSampleSizes sampleSize)
{
	createTest<VstProcessTest> (parent, plugProvider, sampleSize);
	createTest<VstSilenceFlagsTest> (parent, plugProvider, sampleSize);
	createTest<VstSilenceProcessingTest> (parent, plugProvider, sampleSize);
	createTest<VstFlushParamTest> (parent, plugProvider, sampleSize);
	createTest<VstVariableBlockSizeTest> (parent, plugProvider, sampleSize);
	createTest<VstProcessFormatTest> (parent, plugProvider, sampleSize);

	SpeakerArrangement inSpArr = SpeakerArr::kStereo;
	SpeakerArrangement outSpArr = SpeakerArr::kStereo;
	createTest<VstSpeakerArrangementTest> (parent, plugProvider, sampleSize, inSpArr, outSpArr);

	inSpArr = SpeakerArr::kMono;
	outSpArr = SpeakerArr::kMono;
	createTest<VstSpeakerArrangementTest> (parent, plugProvider, sampleSize, inSpArr, outSpArr);

	//int32 everyNSamples, int32 numParams, bool sampleAccuracy;
	createTest<VstAutomationTest> (parent, plugProvider, sampleSize, 100, 1, false);
	createTest<VstAutomationTest> (parent, plugProvider, sampleSize, 100, 1, true);
}

//------------------------------------------------------------------------
} // anonymous

//------------------------------------------------------------------------
void Validator::createTests (IPlugProvider* plugProvider, const ConstString& plugName)
{
	IPtr<TestSuite> plugTestSuite = owned (new TestSuite (plugName));
	
	IPtr<TestSuite> generalTests = owned (new TestSuite ("General Tests"));
	// todo: add tests here!
	createTest<VstEditorClassesTest> (generalTests, plugProvider);
	createTest<VstScanBussesTest> (generalTests, plugProvider);
	createTest<VstScanParametersTest> (generalTests, plugProvider);
	createTest<VstMidiMappingTest> (generalTests, plugProvider);
	createTest<VstUnitInfoTest> (generalTests, plugProvider);
	createTest<VstProgramInfoTest> (generalTests, plugProvider);
	createTest<VstTerminateInitializeTest> (generalTests, plugProvider);
	createTest<VstUnitStructureTest> (generalTests, plugProvider);
	createTest<VstValidStateTransitionTest> (generalTests, plugProvider);
//	createTest<VstInvalidStateTransitionTest> (generalTests, plugProvider);
//	createTest<VstRepeatIdenticalStateTransitionTest> (generalTests, plugProvider);

	createTest<VstBusConsistencyTest> (generalTests, plugProvider);
//	createTest<VstBusInvalidIndexTest> (generalTests, plugProvider);
	createTest<VstBusActivationTest> (generalTests, plugProvider);
	
	createTest<VstCheckAudioBusArrangementTest> (generalTests, plugProvider);

	createTest<VstSuspendResumeTest> (generalTests, plugProvider, kSample32);

	createTest<VstNoteExpressionTest> (generalTests, plugProvider);
	createTest<VstKeyswitchTest> (generalTests, plugProvider);
	
	plugTestSuite->addTestSuite (generalTests->getName ().data (), generalTests);

	IPtr<TestSuite> singlePrecisionTests = owned (new TestSuite ("Single Precision (32 bit) Tests"));
	createPrecisionTests (singlePrecisionTests, plugProvider, kSample32);
	plugTestSuite->addTestSuite (singlePrecisionTests->getName ().data (), singlePrecisionTests);

	IPtr<TestSuite> doublePrecisionTests = owned (new TestSuite ("Double Precision (64 bit) Tests"));
	createPrecisionTests (doublePrecisionTests, plugProvider, kSample64);
	plugTestSuite->addTestSuite (doublePrecisionTests->getName ().data (), doublePrecisionTests);

	testSuite->addTestSuite (plugName, plugTestSuite);
}

//------------------------------------------------------------------------
void Validator::addTest (ITestSuite* testSuite, VstTestBase* testItem)
{
	testSuite->addTest (testItem->getName (), testItem);
	testItem->release ();
}

//------------------------------------------------------------------------
void Validator::runTestSuite (TestSuite* suite, FIDString nameFilter)
{
	std::string name;
    if (nameFilter == nullptr || suite->getName () == nameFilter)
	{
        nameFilter = nullptr; // make sure if suiteName is the namefilter that sub suite will run
        ITest* testItem = nullptr;
		// first run all tests in the suite
		for (int32 i = 0; i < suite->getTestCount (); i++)
		{
			if (suite->getTest (i, testItem, name) == kResultTrue)
			{
				if (infoStream)
					*infoStream << "[" << name << "]\n";

				if (testItem->setup ())
				{
					bool success = testItem->run (this);
					if (success)
					{
						if (infoStream)
							*infoStream << "[Succeeded]\n";
						numTestsPassed++;
					}
					else
					{
						if (infoStream)
							*infoStream << "[XXXXXXX Failed]\n";
						if (errorStream && errorStream != infoStream)
						{
							*errorStream << "Test [" << name << "] ";
							*errorStream << "Failed\n";
						}
						numTestsFailed++;
					}

					if (!testItem->teardown ())
					{
						if (infoStream)
							*infoStream << "Failed to teardown test!\n";
						if (errorStream && errorStream != infoStream)
						{
							*errorStream << "[" << name << "] ";
							*errorStream << "Failed to teardown test!\n";
						}
					}
				}
				else
				{
					testItem->teardown();
					if (infoStream)
						*infoStream << "Failed to setup test!\n";
					if (errorStream && errorStream != infoStream)
					{
						*errorStream << "[" << name << "] ";
						*errorStream << "Failed to setup test!\n";
					}
				}
				if (infoStream)
					*infoStream << "\n";
			}
		}
	}
	// next run sub suites
	int32 subTestSuiteIndex = 0;
    ITestSuite* subSuite = nullptr;
	while (suite->getTestSuite (subTestSuiteIndex++, subSuite, name) == kResultTrue)
	{
		TestSuite* ts = FCast<TestSuite> (subSuite);
		if (ts)
		{
			if (infoStream)
			{
				*infoStream << SEPARATOR;
				*infoStream << "TestSuite : " << ts->getName ().data () << "\n";
				*infoStream << SEPARATOR << "\n";
			}
			runTestSuite (ts, nameFilter);
		}
	}
}


}} // namespaces
