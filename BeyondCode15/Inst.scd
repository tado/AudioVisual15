(
SynthDef("moog", {
	arg nth = 0, freq = 40, cutoff = 100, amp = 0.5, gain = 3.0;
	var in, env;
	env = Env.new([0, 1], [10.0]);
	in = MoogFF.ar(
		Pulse.ar([freq, freq * 1.01] * (1.5 ** nth), [0.3, 0.2]),
		LFNoise1.kr([0.5, 0.52], 1.0, [3.0, 4.0]) * LFNoise1.kr([1.2, 1.3], cutoff, cutoff * 1.5),
		gain,
		mul:amp
	);
	in = in * EnvGen.kr(env, doneAction:0);
	Out.ar(3, in);
}).store;

SynthDef("fx_allpass", {
	arg lpf=440, rq=0.5, amp=0.8;
	var in, out;
	in = In.ar(3, 2);
	32.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 1.0) });
	//8.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 1.0) });
	out = CompanderD.ar(in) * amp;
	Out.ar(0, out);
}).store;
)

//a = Synth("fx_allpass");
//b = Synth("moog");