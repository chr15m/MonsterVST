# change this to the location of your unpacked VST SDK:
VSTSDKDIR = ../vstsdk2.4
PLUGINNAME = $(shell basename $(shell pwd))

CPP = i586-mingw32msvc-g++
LD = i586-mingw32msvc-ld
OBJCOPY = i586-mingw32msvc-objcopy
OBJ = $(PLUGINNAME).o $(VSTSDKDIR)/public.sdk/source/vst2.x/vstplugmain.o $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffect.o $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffectx.o
LIBS = -L. --add-stdcall-alias -lole32 -lkernel32 -lgdi32 -luuid -luser32 --no-export-all-symbols --def $(PLUGINNAME).def   
CXXINCS = -I"$(VSTSDKDIR)/pluginterfaces/vst2.x" -I"$(VSTSDKDIR)/public.sdk/source/vst2.x" -I"$(VSTSDKDIR)" -I"$(VSTSDKDIR)/vstgui.sf/vstgui" -I.
BIN = $(PLUGINNAME).dll
CXXFLAGS = $(CXXINCS) -DBUILDING_DLL=1 -mwindows -O3
RM = rm -f

.PHONY: all clean

all: $(PLUGINNAME).dll

clean: 
	${RM} data.o $(OBJ) $(BIN) lib$(PLUGINNAME)_dll.a

DLLWRAP   = i586-mingw32msvc-dllwrap
DEFFILE   = lib$(PLUGINNAME).def
STATICLIB = lib$(PLUGINNAME).a

# if there is a data object to embed, do so
ifeq ($(wildcard data.txt),) 
    DATAOBJ =
else 
    DATAOBJ = data.o
endif

$(DATAOBJ): data.txt
	# $(OBJCOPY) --input binary --output-target elf32-i386 --binary-architecture i386 data.txt data.o
	$(LD) -r -b binary -o data.o data.txt

$(BIN): $(OBJ) $(DATAOBJ)
	# $(DLLWRAP) --output-def $(DEFFILE) --driver-name c++ --implib $(STATICLIB) $(OBJ) $(LIBS) -o $(BIN)
	$(CPP) -shared -o $(PLUGINNAME).dll $(OBJ) $(DATAOBJ) $(LIBS) -Wl,--out-implib,lib$(PLUGINNAME)_dll.a

$(PLUGINNAME).o: $(PLUGINNAME).cpp
	$(CPP) -c $(PLUGINNAME).cpp -o $(PLUGINNAME).o $(CXXFLAGS)

$(VSTSDKDIR)/public.sdk/source/vst2.x/vstplugmain.o: $(VSTSDKDIR)/public.sdk/source/vst2.x/vstplugmain.cpp
	$(CPP) -c $(VSTSDKDIR)/public.sdk/source/vst2.x/vstplugmain.cpp -o $(VSTSDKDIR)/public.sdk/source/vst2.x/vstplugmain.o $(CXXFLAGS)

$(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffect.o: $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffect.cpp
	$(CPP) -c $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffect.cpp -o $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffect.o $(CXXFLAGS)

$(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffectx.o: $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffectx.cpp
	$(CPP) -c $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffectx.cpp -o $(VSTSDKDIR)/public.sdk/source/vst2.x/audioeffectx.o $(CXXFLAGS)
