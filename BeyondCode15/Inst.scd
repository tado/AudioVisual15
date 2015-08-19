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
	arg lpf=440, rq=0.5, amp=0.8, freq = 16000;
	var in, out;
	in = In.ar(3, 2);
	32.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 1.0) });
	//out = Limiter.ar(MidEQ.ar(in, 14000, 0.5, 8));
	//out = CompanderD.ar(in) * amp;
	out = Limiter.ar(MidEQ.ar(in, freq, 0.7, 8)) * amp;
	Out.ar(0, out);
}).store;

SynthDef("pulse_rhythm", {
	arg amp=1.0, freq = 8000;
	var in1, in2, env, out;
	env = Env.new([0, 1], [30.0]);
	in1 = AllpassC.ar(SinOsc.ar([40, 40.1]).tanh,0.4,TExpRand.ar(2e-4, 2.0,Impulse.ar(8.0)).round([2e-3,4e-3]),2);
	in2 = AllpassC.ar(SinOsc.ar([60, 60.1]).tanh,0.4,TExpRand.ar(2e-4, 2.0,Impulse.ar(8.0)).round([2e-3,4e-3]),2);
	in1 = RLPF.ar(in1, LFNoise1.kr([1.0, 1.5], 3000, 6000), 0.6);
	in2 = RLPF.ar(in2, LFNoise1.kr([3.0, 2.5], 8000, 16000), 0.5);
	out = Limiter.ar(MidEQ.ar(in1 + in2, freq, 0.7, 8)) * EnvGen.kr(env, doneAction:0) * amp;
	Out.ar(0, out);
}).store;
)

//a = Synth("fx_allpass");
//b = Synth("moog");
//c = Synth("pulse_rhythm");