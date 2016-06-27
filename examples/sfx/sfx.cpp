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
    chip::Chip chip;

    chip::Channel& channel = chip.addChannel();
    channel.volume(0.6);

    chip::WaveTable waveTable(chip::WaveTable::SIZE_8);
    waveTable = { 0.0, 1.0, 0.0, -1.0, 0.0, 1.0, -1.0, 1.0 };

    chip::WaveTable sine(chip::WaveTable::SIZE_2);
    sine[0] = -1.0;
    sine[1] = 1.0;

    chip::Module &envelopeFM = channel.addModule(new chip::EnvelopeADSR());
    //inputs to envelope
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

    chip::Module& fmMult = channel.addModule(new chip::Multiply() );
    fmMult.input(chip::Multiply::IN1) = &envelopeFM;
    fmMult.input(chip::Multiply::IN2) = &channel.addModule(new chip::Value(500) );

    chip::Module &envelopeFMPitch = channel.addModule(new chip::EnvelopeADSR());
    //inputs to envelope
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

    chip::Module& pitchMult = channel.addModule(new chip::Multiply() );
    pitchMult.input(chip::Multiply::IN1) = &envelopeFMPitch;
    pitchMult.input(chip::Multiply::IN2) = &channel.addModule(new chip::Value(400) );

    chip::Oscillator& oscillatorFM = channel.addOscillator(new chip::Oscillator(sine, chip::Oscillator::COSINE));
    oscillatorFM.input(chip::Oscillator::FREQUENCY) = &pitchMult;
    oscillatorFM.input(chip::Oscillator::AMPLITUDE) = &fmMult;

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

    chip::Module& add = channel.addModule(new chip::Add() );
    add.input(chip::Add::IN1) = &channel.input(chip::Channel::NOTE_FREQ);
    add.input(chip::Add::IN2) = &oscillatorFM;

    //first module in chain
    chip::Module &filter = channel.addModule(new chip::FilterLP1Pole() );
    channel.output(&filter);
    //inputs to filter
    chip::Value &cutoff = channel.addParameter(chip::Value(5000), "cutoff");
    filter.input(chip::FilterLP1Pole::CUTOFF) = &cutoff;
    chip::Oscillator &oscillator = channel.addOscillator(new chip::Oscillator(waveTable, chip::Oscillator::COSINE));
    filter.input(chip::FilterLP1Pole::IN) = &oscillator;
    //inputs to oscillator
    oscillator.input(chip::Oscillator::FREQUENCY) = &add;
    chip::Module &envelope = channel.addModule(new chip::EnvelopeADSR() );
    oscillator.input(chip::Oscillator::AMPLITUDE) = &envelope;
    //inputs to envelope
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

    chip.start();

    while(std::cin.get() != 'q')
    {
        if(!channel.noPatterns() )
        {
            channel.removeFirstPattern();
        }
        chip::Pattern& pattern = channel.addPattern(chip::Pattern() );
        pattern.addEvent(chip::Event(chip::NOTE_ON, chip::C1, 1), chip::TimeValue(1, 1, 1, 1) );
        pattern.endPosition(chip::TimeValue(2, 1, 1, 1) );
        channel.restart();
    }

    chip.stop();

    return 0;
}