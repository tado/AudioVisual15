(
SynthDef("moog", {
	arg nth = 0, freq = 20, cutoff = 100, amp = 0.4, gain = 3.5;
	var in;
	in = MoogFF.ar(
		Pulse.ar([freq, freq * 1.01] * (1.5 ** nth), [0.3, 0.2]),
		LFNoise1.kr([0.1, 0.12], 1.0, [3.0, 4.0]) * LFNoise1.kr([0.2, 0.3], cutoff, cutoff * 2.0),
		gain,
		mul:0.4
	);
	Out.ar(3, in);
}).store;

SynthDef("fx_allpass", {
	arg lpf=440, rq=0.5, amp=0.8;
	var in, out;
	in = In.ar(3, 2);
	32.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 4.0) });
	out = CompanderD.ar(in) * amp;
	Out.ar(0, out);
}).store;
)

//a = Synth("fx_allpass");
//b = Synth("moog");