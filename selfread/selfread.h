#ifndef __testplugin__
#define __testplugin__

#include <stdio.h>
#include "public.sdk/source/vst2.x/audioeffectx.h"

extern char binary_data_txt_start;
extern const void* binary_data_txt_size;
extern char binary_data_txt_end;

//-------------------------------------------------------------------------------------------------------
class SelfRead : public AudioEffectX
{
public:
	SelfRead(audioMasterCallback audioMaster);
	~SelfRead();

	// Processing
	virtual void processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames);
	virtual void processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames);

	// Program
	virtual void setProgramName (char* name);
	virtual void getProgramName (char* name);

	// Parameters
	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index);
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterName (VstInt32 index, char* text);

	virtual bool getEffectName (char* name);
	virtual bool getVendorString (char* text);
	virtual bool getProductString (char* text);
	virtual VstInt32 getVendorVersion ();

protected:
	float fGain;
	char programName[kVstMaxProgNameLen + 1];
	char storeName[kVstMaxProgNameLen + 1];
};

#endif
