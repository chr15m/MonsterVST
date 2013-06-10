#include "testplugin.h"

AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new TestPlugin (audioMaster);
}

TestPlugin::TestPlugin (audioMasterCallback audioMaster)
: AudioEffectX (audioMaster, 1, 1)	// 1 program, 1 parameter only
{
	setNumInputs (2);		// stereo in
	setNumOutputs (2);		// stereo out
	setUniqueID ('TestGainPlugin');	// identify
	canProcessReplacing ();	// supports replacing output
	canDoubleReplacing ();	// supports double precision processing

	fGain = 1.f;			// default to 0 dB
	vst_strncpy (programName, "Default", kVstMaxProgNameLen);	// default program name
}

TestPlugin::~TestPlugin ()
{
	// nothing to do here
}

void TestPlugin::setProgramName (char* name)
{
	vst_strncpy (programName, name, kVstMaxProgNameLen);
}

void TestPlugin::getProgramName (char* name)
{
	vst_strncpy (name, programName, kVstMaxProgNameLen);
}

void TestPlugin::setParameter (VstInt32 index, float value)
{
	fGain = value;
}

float TestPlugin::getParameter (VstInt32 index)
{
	return fGain;
}

void TestPlugin::getParameterName (VstInt32 index, char* label)
{
	vst_strncpy (label, "TestGainPlugin", kVstMaxParamStrLen);
}

void TestPlugin::getParameterDisplay (VstInt32 index, char* text)
{
	dB2string (fGain, text, kVstMaxParamStrLen);
}

void TestPlugin::getParameterLabel (VstInt32 index, char* label)
{
	vst_strncpy (label, "dB", kVstMaxParamStrLen);
}

bool TestPlugin::getEffectName (char* name)
{
	vst_strncpy (name, "TestGainPlugin", kVstMaxEffectNameLen);
	return true;
}

bool TestPlugin::getProductString (char* text)
{
	vst_strncpy (text, "TestGainPlugin", kVstMaxProductStrLen);
	return true;
}

bool TestPlugin::getVendorString (char* text)
{
	vst_strncpy (text, "chris@mccormick.cx", kVstMaxVendorStrLen);
	return true;
}

VstInt32 TestPlugin::getVendorVersion ()
{ 
	return 0001;
}

void TestPlugin::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

    while (--sampleFrames >= 0)
    {
        (*out1++) = (*in1++) * fGain;
        (*out2++) = (*in2++) * fGain;
    }
}

void TestPlugin::processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames)
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];
	double dGain = fGain;

    while (--sampleFrames >= 0)
    {
        (*out1++) = (*in1++) * dGain;
        (*out2++) = (*in2++) * dGain;
    }
}
