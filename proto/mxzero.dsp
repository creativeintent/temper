import("stdfaust.lib");

pdrive = hslider("Drive", 1.0, 0.0, 4.0, 0.001);
poffset = hslider("Offset", 0.0, -1.0, 1.0, 0.001);
psmooth = hslider("Smoothing", 0.5, 0.0, 1.0, 0.001);
ptype = hslider("Filter Type", 0, 0, 2, 1.0);
ptransfer = hslider("Transfer Type", 0, 0, 3, 1.0);
 
// Maybe min/max at +/- 0.9999? The one-pole is unstable only for |a1| < 1.
drive(x) = x : *(pdrive) : +(poffset) : min(1.0) : max(-1.0);

transfer = _ <: _,ma.tanh,ma.chebychev(2),ma.chebychev(4) : ba.selectn(4, ptransfer);
m(x) = drive(x) : transfer : si.smooth(psmooth);

// These could all be implemented as a `tf1`, and just map the coefficients according
// to the ptype value?
mzero(x) = x : fi.zero(m(x));

// If we do this, should probably set b0 to `1 - |a1|` or something to enforce
// that peak gain is 1, otherwise this could be instant clipping.
mpole(x) = x : fi.pole(m(x));

mallpass(x) = x : fi.tf1(m(x), 1.0, m(x));

mfilter = _ <: select3(ptype, mzero, mallpass, mpole);

process = mfilter,mfilter;
