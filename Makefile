FAUST := $(shell command -v faust 2> /dev/null)

# Assuming the `faust` directory is a sibling of this directory, and that you've
# successfully compiled faust, you should be able to get this running with something
# like this:
# PATH=/Users/nick/Dev/faust/build/bin/:$PATH make

# Pretty hacky; assumes that the `faust` directory is a sibling of the `temper`
# directory. This is with Faust on `master-dev` at v2.5.2.
./Source/TemperDsp.cpp: ./Dsp/temper.dsp
ifndef FAUST
	$(error "Faust not found; please install: http://faust.grame.fr/download/")
endif
	faust -A ../faust/architecture/ -I ../faust/libraries/ -a minimal-effect.cpp -cn TemperDsp -o ./Source/TemperDsp.cpp ./Dsp/temper.dsp

prototype:
	# ln -s ~/SDKs/VST3\ SDK/ /usr/local/include/vstsdk2.4
	faust2vst ./Dsp/temper.dsp
	rm -r ~/Library/Audio/Plug-Ins/VST/temper.vst
	mv ./Dsp/temper.vst ~/Library/Audio/Plug-Ins/VST/

test:
	auval -v aufx Tmpr Cvin

.PHONY: test prototype
