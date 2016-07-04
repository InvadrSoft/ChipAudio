CHORD_SHAPES =
{ 	
	{0, 2, 4, 7, 12},
	{0, 2, 3, 7, 12},
	{0, 4, 7, 11, 12} 
};
	
CHORDS = 
{	
	{1, Notes.C3},
	{2, Notes.A2},
	{1, Notes.C3},
	{2, Notes.A2},
	{1, Notes.F2},
	{1, Notes.G2},
	{3, Notes.Ab2},
	{3, Notes.Bb2}
};

chip = Chip.new();
chip:tempo(88);

for channelNum = 1, 2 do
	channel = chip:addChannel();
	channel:setVolume(0.5);
	channel:setPan(-0.1);

	wavetable = WaveTable.new(WaveTable.SIZE_32);
	for i = 0, 31 do
		if i < (31 / 2) then
			wavetable:set(i, 1.0)
		else
			wavetable:set(i, -1.0)
		end
	end

	oscillator = channel:addOscillator(newOscillator(wavetable, Oscillator.COSINE) );
	channel:output(oscillator)
	moduleInput(oscillator, Oscillator.FREQUENCY, channel:input(Channel.NOTE_FREQ) );

	envelope = channel:addModule(newEnvelope() );
	moduleInput(oscillator, Oscillator.AMPLITUDE, envelope);

	moduleInput(envelope, EnvelopeADSR.GATE, channel:input(Channel.GATE_IN) );

	attack = channel:addParameter(Value.new(0.001), "attack");
	moduleInput(envelope, EnvelopeADSR.ATTACK, attack);
	decay = channel:addParameter(Value.new(0.28), "decay");
	moduleInput(envelope, EnvelopeADSR.DECAY, decay);
	sustain = channel:addParameter(Value.new(0.1), "sustain");
	moduleInput(envelope, EnvelopeADSR.SUSTAIN, sustain);
	release = channel:addParameter(Value.new(0.01), "release");
	moduleInput(envelope, EnvelopeADSR.RELEASE, release);
	
	if channelNum == 2 then
		channel:setVolume(0.35);
		channel:setPan(0.2);
		delay = channel:addPattern(Pattern.new() );
		delay:endPosition(TimeValue.new(1, 1, 1, 200) );
		channel:setLoopStart(1);
	end

	pattern = channel:addPattern(Pattern.new() );
	currentTime = TimeValue.new(1, 1, 1, 1);
	noteDuration = TimeValue.new(0, 0, 0, 200);

	for i = 1, 8 do
		root = CHORDS[i][2];
		chordShape = CHORD_SHAPES[CHORDS[i][1] ];
	
		for j = 1, 4 do
			for k = 1, 4 do
				note = (root + ( (j - 1) * 12) + chordShape[k]);
				pattern:addEvent(Event.new(EventType.NOTE_ON, note, 1, ""), currentTime);
				pattern:addEvent(Event.new(EventType.NOTE_OFF, 0, 0, ""), currentTime + noteDuration);
				currentTime = currentTime + TimeValue.new(0, 0, 1, 0);
			end
		end
	
		for j = 4, 1, -1 do
			for k = 5, 2, -1 do
				note = (root + ( (j - 1) * 12) + chordShape[k]);
				pattern:addEvent(Event.new(EventType.NOTE_ON, note, 1, ""), currentTime);
				pattern:addEvent(Event.new(EventType.NOTE_OFF, 0, 0, ""), currentTime + noteDuration);
				currentTime = currentTime + TimeValue.new(0, 0, 1, 0);
			end
		end
	end
	
	pattern:endPosition(TimeValue.new(17, 1, 1, 1) );
	channel:setLoop(true);
end

chip:start();

io.read();

chip:stop();

