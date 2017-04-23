import("stdfaust.lib");

// First stage of the series with analog transfer function coefficients
// selected via
//
//     [b0, b1, b2, 1, a1, a2] = sos(1, :)
//
// Note that the function signature for `tf2s` seems to label the coefficients
// in reverse order. Looking at the elliptic filter examples in the filter
// library, the coefficients are passed into `tf2s` in the order returned
// by `zp2sos`, (b0, b1, b2, a1, a2), despite the labeling in the implementation.
s1(fc) = fi.tf2s(b0, b1, b2, a1, a2, w1) with {
  b0 = 0.000015848949555;
  b1 = 0.0;
  b2 = 0.000786144271496;
  a1 = 0.525921318217520;
  a2 = 0.122972664533630;
  w1 = 2 * ma.PI * fc;
};

// Second stage of the series with analog transfer function coefficients
// selected via
//
//     [b0, b1, b2, 1, a1, a2] = sos(2, :)
//
// Note the reversed ordering as explained above.
s2(fc) = fi.tf2s(b0, b1, b2, a1, a2, w1) with {
  b0 = 1.0;
  b1 = 0.0;
  b2 = 3.241841838455698;
  a1 = 0.395086767014789;
  a2 = 0.436970590100401;
  w1 = 2 * ma.PI * fc;
};

// Third stage of the series with analog transfer function coefficients
// selected via
//
//     [b0, b1, b2, 1, a1, a2] = sos(3, :)
//
// Note the reversed ordering as explained above.
s3(fc) = fi.tf2s(b0, b1, b2, a1, a2, w1) with {
  b0 = 1.0;
  b1 = 0.0;
  b2 = 6.579441200694987;
  a1 = 0.223580396610885;
  a2 = 0.801864840956017;
  w1 = 2 * ma.PI * fc;
};

// Fourth stage of the series with analog transfer function coefficients
// selected via
//
//     [b0, b1, b2, 1, a1, a2] = sos(4, :)
//
// Note the reversed ordering as explained above.
s4(fc) = fi.tf2s(b0, b1, b2, a1, a2, w1) with {
  b0 = 1.0;
  b1 = 0.0;
  b2 = 2.490623104289200;
  a1 = 0.069999468351859;
  a2 = 1.014913750494537;
  w1 = 2 * ma.PI * fc;
};

// This module defines an elliptic (cauer) lowpass filter of eighth
// order with 0.4dB of passband ripple, 96.0dB of stopband ripple, and a
// half-band cutoff frequency of (sampleRate / 4), computed in four second-order
// sections. The derivation in GNU Octave is as follows,
//
//     pkg load signal;
//     format long;
//     [z, p, g] = ncauer(0.4, 96.0, 8);
//     sos = zp2sos(z, p, g);
//
// A quick plot of the frequency response in the s-plane can be drawn by
// computing the analog coefficients and analysing them with `freqs`,
//
//     [B, A] = zp2tf(z, p, g);
//     w = linspace(0,4,128);
//     freqs(B, A, w);
//
// Note the normalized cutoff frequency at 1rad/s.
ellip = s1(fc) : s2(fc) : s3(fc) : s4(fc) with {
	fc = ma.SR / 4;
};
