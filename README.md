# Temper

> Modern digital distortion. 

![Temper Plugin](/screenshot.jpg?raw=true "Temper running inside FL Studio 12.")

Temper is a digital distortion audio plugin targeting VST, VST3, and AU
for OS X and Windows. It builds upon traditional waveshaping techniques using
modulated filter coefficients to produce a unique phase distortion. The primary
signal processing loop is written with Faust, and compiled with JUCE for the
various build targets.

## Dependencies
* Faust (v2.5.32)
* JUCE (v5.3.0)
* VST SDK (v3.6.7)

## Usage
Temper can run inside any plugin host that supports VST, VST3, or AU, such as
[Audacity](http://www.audacityteam.org/) (Free) or [FL Studio](https://www.image-line.com/flstudio/) (Paid).

### Parameters

**Cutoff**: The signal chain contains a simple resonant lowpass filter before the distortion unit. This parameter sets the
cutoff frequency of that filter.

**Resonance**: This parameter sets the corner resonance of the lowpass filter mentioned above.

**Curve**: The first of the three parameters that control the distortion unit, Curve sets the shape of the waveshaper curve
used to saturate the input signal before the phase distortion module.

**Drive**: Like a traditional overdrive, Temper includes a gain step before the waveshaper. Drive determines the gain applied
at that step.

**Saturation**: The Saturation parameter controls the Dry/Wet mix of the waveshaper output; at 0.0, the dry input signal goes
into the phase distortion module with the shaped signal modulating the phase offset. At 1.0, the wet waveshaper signal goes
into the phase distortion module which is shaped by the same wet signal.

**Feedback**: The signal chain includes a feedback loop, taking the output of the distortion unit and feeding it back right
before the distoriton unit again (after the filter). Feedback here decides the gain multiplier on that feedback loop.

**Level**: This simply adjusts the output level.

## Contributing
If you find any weird or buggy behavior, please open an issue! We will also happily accept pull requests implementing
bug fixes or compatibility support. We may refuse pull requests or feature suggestions that change product direction, but
we would love to hear your ideas so don't be shy.

### Building
This project is built with both JUCE and Faust, but we commit the result of the Faust compilation to enable maintaining
a repository state that can be built on a new machine with minimal configuration.

Hence, with Visual Studio 2017, you should be able to just open the file `Builds/VisualStudio2017/Temper.sln` and build one
of the three available configurations. Similarly, on OS X, open `Builds/MacOSX/Temper.xcodeproj` with XCode.

If you're interested in modifying the Faust DSP code, or compiling the DSP again, consult the Makefile for instructions. We
have unfortunately hard-coded some assumptions into the Makefile, but you will notice the expected compilation command:

```bash
$ faust -A ../faust/architecture/ -I ../faust/libraries/ -a minimal-effect.cpp -cn TemperDsp -o ./Source/TemperDsp.cpp ./Dsp/temper.dsp
```

If you have `faust` on your `$PATH`, the above command (corrected for the appropriate paths to the library and architecture
files) will recompile the `temper.dsp` file to C++.

If you have any trouble building, please file an issue.

## License

Copyright (C) 2017 Creative Intent, LLC

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
