import("stdfaust.lib");

pdrive = hslider("Drive", 1.0, -10.0, 10.0, 0.001);
poffset = hslider("Offset", 0.0, -1.0, 1.0, 0.001);
psmooth = hslider("Smoothing", 0.5, 0.0, 1.0, 0.001);
ptype = hslider("Filter Type", 0, 0, 1, 1.0);
ptransfer = hslider("Transfer Type", 0, 0, 3, 1.0);

// A hard-coded example of a linear piecewise function from a waveshaper control.
ws = ba.bpf.start(-1.0, -1.0) : ba.bpf.point(-0.6, 0.7) : ba.bpf.point(0.7, -0.6) : ba.bpf.end(1.0, 1.0);

// Currently supporting the identity function, tanh, and two chebychev polynomial
// transfer functions for waveshaping the modulator.
transfer = _ <: _,ma.tanh,ma.chebychev(2),ws : ba.selectn(4, ptransfer);

// Both the one-zero and the allpass filter are stable for `|m(x)| <= 1`, but
// should not linger near +/-1.0 for very long. We therefore clamp the driven
// signal with a tanh function to ensure smooth coefficient calculation.
drive(x) = x : *(pdrive) : +(poffset) : ma.tanh;

// This signal drives the coefficients of the filter.
m(x) = drive(x) : transfer : si.smooth(psmooth);

// Determining the coefficients given the filter type param.
b0(x) = ptype * m(x) + (1.0 - ptype);
b1(x) = ptype + m(x) * (1.0 - ptype);
a1(x) = ptype * m(x);

filter(x) = x : fi.tf1(b0(x), b1(x), a1(x)) : fi.dcblocker;

process = filter,filter;
