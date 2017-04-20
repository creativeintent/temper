FAUST := $(shell command -v faust 2> /dev/null)

./Source/TemperDsp.cpp: ./Dsp/temper.dsp
ifndef FAUST
	$(error "Faust not found; please install: http://faust.grame.fr/download/")
endif
	faust -a minimal-effect.cpp -cn TemperDsp -o ./Source/TemperDsp.cpp ./Dsp/temper.dsp

prototype:
	# ln -s ~/SDKs/VST3\ SDK/ /usr/local/include/vstsdk2.4
	faust2vst ./Dsp/temper.dsp
	rm -r ~/Library/Audio/Plug-Ins/VST/temper.vst
	mv ./Dsp/temper.vst ~/Library/Audio/Plug-Ins/VST/

test:
	auval -v aufx Mxzo Cvin

.PHONY: test prototype
