#include "selfread.h"

AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new SelfRead (audioMaster);
}

SelfRead::SelfRead (audioMasterCallback audioMaster)
: AudioEffectX (audioMaster, 1, 1)	// 1 program, 1 parameter only
{
	const size_t len = (size_t)&binary_data_txt_size;
	vst_strncpy(storeName, &binary_data_txt_start, len+1);
	
	setNumInputs(2);		// stereo in
	setNumOutputs(2);		// stereo out
	setUniqueID('SelfRead');	// identify
	canProcessReplacing();	// supports replacing output
	canDoubleReplacing();	// supports double precision processing

	fGain = 1.f;		// default to 0 dB
	vst_strncpy (programName, storeName, kVstMaxProgNameLen);	// default program name
}

SelfRead::~SelfRead ()
{
	// nothing to do here
}

void SelfRead::setProgramName (char* name)
{
	vst_strncpy (programName, name, kVstMaxProgNameLen);
}

void SelfRead::getProgramName (char* name)
{
	vst_strncpy (name, programName, kVstMaxProgNameLen);
}

void SelfRead::setParameter (VstInt32 index, float value)
{
	fGain = value;
}

float SelfRead::getParameter (VstInt32 index)
{
	return fGain;
}

void SelfRead::getParameterName (VstInt32 index, char* label)
{
	vst_strncpy (label, "Delay", kVstMaxParamStrLen);
}

void SelfRead::getParameterDisplay (VstInt32 index, char* text)
{
	dB2string (fGain, text, kVstMaxParamStrLen);
}

void SelfRead::getParameterLabel (VstInt32 index, char* label)
{
	vst_strncpy (label, "Db", kVstMaxParamStrLen);
}

bool SelfRead::getEffectName (char* name)
{
	vst_strncpy (name, storeName, kVstMaxEffectNameLen);
	return true;
}

bool SelfRead::getProductString (char* text)
{
	vst_strncpy (text, storeName, kVstMaxProductStrLen);
	return true;
}

bool SelfRead::getVendorString (char* text)
{
	vst_strncpy (text, "chris@mccormick.cx", kVstMaxVendorStrLen);
	return true;
}

VstInt32 SelfRead::getVendorVersion ()
{ 
	return 0001;
}

void SelfRead::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
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

void SelfRead::processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames)
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
