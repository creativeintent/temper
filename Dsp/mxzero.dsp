import("stdfaust.lib");

pdrive = hslider("drive", 1.0, -10.0, 10.0, 0.001) : si.smooth(0.995);
poffset = hslider("offset", 0.0, 0.0, 1.0, 0.001) : si.smooth(0.995);
ptype = hslider("filterType", 0.5, 0.0, 1.0, 0.001) : si.smooth(0.995);
ptransfer = hslider("transferType", 0.0, 0.0, 3.0, 0.001) : si.smooth(0.995);
pmix = hslider("mix", 0.5, 0.0, 1.0, 0.001) : si.smooth(0.995);
pbandpassfc = hslider("bandpassfc", 200, 20, 800, 1.0) : si.smooth(0.995);
pbandpassq = hslider("bandpassq", 0.1, 0.1, 4, 0.001) : si.smooth(0.995);

// A utility function which creates a triangular window of width 2 and height 1
// centered about `c` with zero value everywhere outside the window.
triwinat(c, x) = max(0, 1 - abs(x - c));

// Our wave shaping curve is a chebychev polynomial with coefficients decided
// by the `ptransfer` input control applied through a series of triangular
// window functions.
transfer = ma.chebychevpoly((0, 0, w1, w2, w3, w4)) with {
	w1 = triwinat(0, ptransfer);
	w2 = triwinat(1, ptransfer);
	w3 = triwinat(2, ptransfer);
	w4 = triwinat(3, ptransfer);
};

// Both the one-zero and the allpass filter are stable for `|m(x)| <= 1`, but
// should not linger near +/-1.0 for very long. We therefore clamp the driven
// signal with a tanh function to ensure smooth coefficient calculation.
drive(x) = x : *(pdrive) : +(poffset) : ma.tanh;

// This signal drives the coefficients of the filter.
m(x) = drive(x) : transfer;

// Determining the coefficients given the filter type param.
b0(x) = ptype * m(x) + (1.0 - ptype);
b1(x) = ptype + m(x) * (1.0 - ptype);
a1(x) = ptype * m(x);

filter(x) = x : fi.tf1(b0(x), b1(x), a1(x)) : fi.dcblocker;

process = _ <: _, (fi.resonbp(pbandpassfc, pbandpassq, 1.0) : filter) : *(1.0 - pmix), *(pmix) : +;
