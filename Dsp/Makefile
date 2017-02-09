FAUST := $(shell command -v faust 2> /dev/null)

../Source/MxzDsp.cpp: mxzero.dsp
ifndef FAUST
	$(error "Faust not found; please install: http://faust.grame.fr/download/")
endif
	faust -a minimal-effect.cpp -cn MxzDsp -o ../Source/MxzDsp.cpp mxzero.dsp

all: mxzdsp.cpp
