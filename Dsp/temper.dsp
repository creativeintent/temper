import("stdfaust.lib");
el = library("./ellip.dsp");

// Pre-filter parameters
pfilterfc = hslider("Cutoff", 16000, 100, 16000, 1.0) : si.smooth(0.995);
pfilterq = hslider("Resonance", 1.0, 1.0, 8, 0.001) : si.smooth(0.995);

// Distortion parameters
pdrive = hslider("Drive", 4.0, -10.0, 10.0, 0.001) : si.smooth(0.995);
psat = hslider("Saturation", 0.0, 0.0, 1.0, 0.001) : si.smooth(0.995);
pcurve = hslider("Curve", 1.0, 0.1, 4.0, 0.001) : si.smooth(0.995);

// Output parameters
pfeedback = hslider("Feedback", -60, -60, -24, 1) : ba.db2linear : si.smooth(0.995);
plevel = hslider("Level", -3, -12, 12, 1) : ba.db2linear : si.smooth(0.995);

// A fairly standard wave shaping curve; we use this to shape the input signal
// before modulating the filter coefficients by this signal. Which shaping curve
// we use here is pretty unimportant; as long as we can introduce higher harmonics,
// the coefficient modulation will react. Which harmonics we introduce here seems
// to affect the resulting sound pretty minimally.
transfer(x) = ma.tanh(pcurve * x) / ma.tanh(pcurve);

// The allpass filter is stable for `|m(x)| <= 1`, but should not linger
// near +/-1.0 for very long. We therefore clamp the driven signal with a tanh
// function to ensure smooth coefficient calculation. We also here introduce
// a modulated DC offset in the signal before the curve.
drive(x) = x : *(pdrive) : +(fol(x)) : ma.tanh with {
	fol = an.amp_follower(0.04);
};

// Our modulated filter is an allpass with coefficients governed by the input
// signal applied through our wave shaper. Before the filter, we mix the dry
// input signal with the raw waveshaper output according to the `psat` parameter.
// Note the constant gain coefficient on the waveshaper tap; that number is to offset
// the global gain from the waveshaper to make sure the shaping process stays
// under unity gain. The maximum differential gain of the waveshaper can be found
// by evaluating the derivative of the transfer function at x0 where x0 is the
// steepest part of the slope. Here that number is ~4, so we multiply by ~1/4.
modfilter(x) = x <: _, tap(x) : *(1.0 - psat), *(psat) : + : fi.tf1(b0(x), b1(x), a1(x)) with {
	b0(x) = m(x);
	b1(x) = 1.0;
	a1(x) = m(x);
	m(x) = drive(x) : transfer;
	tap(x) = m(x) : *(0.24);
};

// We have a resonant lowpass filter at the beginning of our signal chain
// to control what part of the input signal becomes the modulating signal.
filter = fi.resonlp(pfilterfc, pfilterq, 1.0);

// Our main processing block.
main = (+ : modfilter : fi.dcblocker) ~ *(pfeedback) : gain with {
	// This explicit gain multiplier of 4.0 accounts for the loss of gain that
	// occurs from oversampling by a factor of 2, and for the loss of gain that
	// occurs from the prefilter and modulation step. Then we apply the output
	// level parameter.
	gain = *(4.0) : *(plevel);
};

// When this unit processes a block, the block will be a zero-padded input
// signal at a higher sampling rate. We run the elliptic filter immediately
// because that step of zero-padding the input buffer introduces an alias of
// the input signal in the range [sampleRate / 4, sampleRate / 2] which would
// fold back into the audible range upon downsampling, especially if we run
// the main filter on it. Similarly, processing our input signal introduces
// harmonics in the same frequency range [sampleRate / 4, sampleRate / 2] which
// we cut out with the elliptic filter at the end of the chain before we drop
// sample to return to the original sample rate.
process = el.ellip : filter : main : el.ellip;
