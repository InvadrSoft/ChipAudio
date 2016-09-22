/*! \file
 *  \brief SFX example
 *
 *  Sound effect example, inputting 'q' causes program to exit, any other
 *  input causes sound effect to play.
 *
 *  \include sfx.cpp
 */

#include <iostream>
#include "chipaudio.hpp"
#include "chipmodules.hpp"

int main()
{
    //create the chip object
    chip::Chip chip;

    //add a new channel to the chip
    chip::Channel& channel = chip.addChannel();

    //set the channel's volume
    channel.volume(0.6);

    //set the channel to remove patterns after they finish
    channel.consumePatterns(true);

    //create a wavetable with an asymmetrical shape
    chip::WaveTable waveTable(chip::WaveTable::SIZE_8);
    waveTable = { 0.0, 1.0, 0.0, -1.0, 0.0, 1.0, -1.0, 1.0 };

    //create another wavetable with a sine shape (when smoothed with cosine interpolation)
    chip::WaveTable sine(chip::WaveTable::SIZE_2);
    sine[0] = -1.0;
    sine[1] = 1.0;

    //this envelope will be used for the modulator signal
    chip::Module &envelopeFM = channel.addModule(new chip::EnvelopeADSR());
    envelopeFM.input(chip::EnvelopeADSR::GATE) = &channel.input(chip::Channel::GATE_IN);
    chip::Module &attackFM = channel.addParameter(chip::Value(0), "attackFM");
    envelopeFM.input(chip::EnvelopeADSR::ATTACK) = &attackFM;
    chip::Module &decayFM = channel.addParameter(chip::Value(0.50), "decayFM");
    envelopeFM.input(chip::EnvelopeADSR::DECAY) = &decayFM;
    chip::Module &sustainFM = channel.addParameter(chip::Value(0), "sustainFM");
    envelopeFM.input(chip::EnvelopeADSR::SUSTAIN) = &sustainFM;
    chip::Module &releaseFM = channel.addParameter(chip::Value(0), "releaseFM");
    envelopeFM.input(chip::EnvelopeADSR::RELEASE) = &releaseFM;
    envelopeFM.input(chip::EnvelopeADSR::RESTART) = &channel.input(chip::Channel::NEW_NOTE);

    //use a multiply module to amplify the modulator signal
    chip::Module& fmMult = channel.addModule(new chip::Multiply() );
    fmMult.input(chip::Multiply::IN1) = &envelopeFM;
    fmMult.input(chip::Multiply::IN2) = &channel.addModule(new chip::Value(500) );

    //this envelope will be used for the pitch of the modulator signal
    chip::Module &envelopeFMPitch = channel.addModule(new chip::EnvelopeADSR());
    envelopeFMPitch.input(chip::EnvelopeADSR::GATE) = &channel.input(chip::Channel::GATE_IN);
    chip::Module &attackFMPitch = channel.addParameter(chip::Value(0), "attackFMPitch");
    envelopeFMPitch.input(chip::EnvelopeADSR::ATTACK) = &attackFMPitch;
    chip::Module &decayFMPitch = channel.addParameter(chip::Value(0.3), "decayFMPitch");
    envelopeFMPitch.input(chip::EnvelopeADSR::DECAY) = &decayFMPitch;
    chip::Module &sustainFMPitch = channel.addParameter(chip::Value(0), "sustainFMPitch");
    envelopeFMPitch.input(chip::EnvelopeADSR::SUSTAIN) = &sustainFMPitch;
    chip::Module &releaseFMPitch = channel.addParameter(chip::Value(0), "releaseFMPitch");
    envelopeFMPitch.input(chip::EnvelopeADSR::RELEASE) = &releaseFMPitch;
    envelopeFMPitch.input(chip::EnvelopeADSR::RESTART) = &channel.input(chip::Channel::NEW_NOTE);

    //calculate the final pitch by multiplying the envelope with a constant value
    chip::Module& pitchMult = channel.addModule(new chip::Multiply() );
    pitchMult.input(chip::Multiply::IN1) = &envelopeFMPitch;
    pitchMult.input(chip::Multiply::IN2) = &channel.addModule(new chip::Value(400) );

    //create the modulator signal
    chip::Oscillator& oscillatorFM = channel.addOscillator(new chip::Oscillator(sine, chip::Oscillator::COSINE));
    oscillatorFM.input(chip::Oscillator::FREQUENCY) = &pitchMult;
    oscillatorFM.input(chip::Oscillator::AMPLITUDE) = &fmMult;

    //this envelope will be used for the pitch of the carrier signal
    chip::Module &pitchEnv = channel.addModule(new chip::EnvelopeADSR() );
    pitchEnv.input(chip::EnvelopeADSR::GATE) = &channel.input(chip::Channel::NOTE_FREQ);
    chip::Module &pitchAttack = channel.addParameter(chip::Value(0), "pitchattack");
    pitchEnv.input(chip::EnvelopeADSR::ATTACK) = &pitchAttack;
    chip::Module &pitchDecay = channel.addParameter(chip::Value(0.50), "pitchdecay");
    pitchEnv.input(chip::EnvelopeADSR::DECAY) = &pitchDecay;
    chip::Module &pitchSustain = channel.addParameter(chip::Value(0), "pitchsustain");
    pitchEnv.input(chip::EnvelopeADSR::SUSTAIN) = &pitchSustain;
    chip::Module &pitchRelease = channel.addParameter(chip::Value(0), "pitchrelease");
    pitchEnv.input(chip::EnvelopeADSR::RELEASE) = &pitchRelease;
    pitchEnv.input(chip::EnvelopeADSR::RESTART) = &channel.input(chip::Channel::NEW_NOTE);

    //add the channel's note frequency to the pitch envelope
    chip::Module& add = channel.addModule(new chip::Add() );
    add.input(chip::Add::IN1) = &channel.input(chip::Channel::NOTE_FREQ);
    add.input(chip::Add::IN2) = &oscillatorFM;

    //use a filter as the last module in the chain
    chip::Module &filter = channel.addModule(new chip::FilterLP1Pole() );
    channel.output(&filter);
    chip::Value &cutoff = channel.addParameter(chip::Value(5000), "cutoff");
    filter.input(chip::FilterLP1Pole::CUTOFF) = &cutoff;

    //create the carrier signal
    chip::Oscillator &oscillator = channel.addOscillator(new chip::Oscillator(waveTable, chip::Oscillator::COSINE));
    //and use it as the the input to the filter
    filter.input(chip::FilterLP1Pole::IN) = &oscillator;

    //use the result of the add as the frequency input
    oscillator.input(chip::Oscillator::FREQUENCY) = &add;

    //this envelope will be used for the amplitude of the carrier signal
    chip::Module &envelope = channel.addModule(new chip::EnvelopeADSR() );
    oscillator.input(chip::Oscillator::AMPLITUDE) = &envelope;
    envelope.input(chip::EnvelopeADSR::GATE) = &channel.input(chip::Channel::GATE_IN);
    chip::Module &attack = channel.addParameter(chip::Value(0.01), "attack");
    envelope.input(chip::EnvelopeADSR::ATTACK) = &attack;
    chip::Module &decay = channel.addParameter(chip::Value(0.28), "decay");
    envelope.input(chip::EnvelopeADSR::DECAY) = &decay;
    chip::Module &sustain = channel.addParameter(chip::Value(0), "sustain");
    envelope.input(chip::EnvelopeADSR::SUSTAIN) = &sustain;
    chip::Module &release = channel.addParameter(chip::Value(0), "release");
    envelope.input(chip::EnvelopeADSR::RELEASE) = &release;
    envelope.input(chip::EnvelopeADSR::RESTART) = &channel.input(chip::Channel::NEW_NOTE);

    //start playback
    chip.start();

    //while there is an input and it is not 'q'
    while(std::cin.get() != 'q')
    {
        //create a new pattern
        chip::Pattern pattern;

        //add a note on representing the start of the sound effect
        pattern.addEvent(chip::Event(chip::NOTE_ON, chip::C1, 1), chip::TimeValue(1, 1, 1, 1) );

        //set the end of the pattern
        pattern.endPosition(chip::TimeValue(1, 1, 1, 2) );

        //add the pattern to the channel in a thread-safe manner
        channel.enqueuePattern(pattern);
    }

    //stop playback
    chip.stop();

    return 0;
}