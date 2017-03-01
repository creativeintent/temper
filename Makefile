FAUST := $(shell command -v faust 2> /dev/null)

./Source/MxzDsp.cpp: ./Dsp/mxzero.dsp
ifndef FAUST
	$(error "Faust not found; please install: http://faust.grame.fr/download/")
endif
	faust -a minimal-effect.cpp -cn MxzDsp -o ./Source/MxzDsp.cpp ./Dsp/mxzero.dsp

prototype:
	# ln -s ~/SDKs/VST3\ SDK/ /usr/local/include/vstsdk2.4
	faust2vst ./Dsp/mxzero.dsp
	rm -r ~/Library/Audio/Plug-Ins/VST/mxzero.vst
	mv ./Dsp/mxzero.vst ~/Library/Audio/Plug-Ins/VST/

test:
	auval -v aufx Mxzo Cvin

.PHONY: test prototype
all: mxzdsp.cpp
