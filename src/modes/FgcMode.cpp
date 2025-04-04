#include "modes/FgcMode.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

FgcMode::FgcMode() : ControllerMode() {}

void FgcMode::UpdateDigitalOutputs(const InputState &inputs, OutputState &outputs) {
    // Directions
    outputs.dpadLeft = inputs.lf3;
    outputs.dpadRight = inputs.lf1;
    outputs.dpadDown = inputs.lf2;
    outputs.dpadUp = inputs.lt1 || inputs.lf5 || inputs.rt4;

    // L3 & R3
    outputs.leftStickClick = inputs.lt4 || inputs.rt3; 
    outputs.rightStickClick = inputs.rt2;                       

    // Menu keys
    outputs.start = inputs.mb1;
    outputs.select = inputs.mb3;
    outputs.home = inputs.mb2;

    // Activate select/home by holding Mod Y
    if ((inputs.lt2)) {
        outputs.select = inputs.mb1;
        outputs.home = inputs.rt1;
    }

    // Right hand bottom row
    outputs.a = inputs.rf1;
    outputs.b = inputs.rf2;
    outputs.triggerRDigital = inputs.rf3;
    outputs.triggerLDigital = inputs.rf4;

    // Right hand top row
    outputs.x = inputs.rf5;
    outputs.y = inputs.rf6;
    outputs.buttonR = inputs.rf7;
    outputs.buttonL = inputs.rf8;

    // Turns off Start / LB when holding Mod Y
    if ((inputs.lt2)) {
        outputs.start = false;
        outputs.a = false;
        // Turn off DPad 
        outputs.dpadLeft = false;
        outputs.dpadRight = false;
        outputs.dpadDown = false;
        outputs.dpadUp = false;
        outputs.leftStickClick = false;
        outputs.rightStickClick = false;
    }    
}

void FgcMode::UpdateAnalogOutputs(const InputState &inputs, OutputState &outputs) {
    outputs.leftStickX = 128;
    outputs.leftStickY = 128;
    outputs.rightStickX = 128;
    outputs.rightStickY = 128;
    outputs.triggerLAnalog = outputs.triggerLDigital ? 255 : 0;
    outputs.triggerRAnalog = outputs.triggerRDigital ? 255 : 0;

    //Hold Mod Y to use analog input.
    if ((inputs.lt2)) {
    UpdateDirections(
    inputs.lf3,
    inputs.lf1,
    inputs.lf2,
    inputs.lf5,
    inputs.rt3,
    inputs.rt5,
    inputs.rt2,
    inputs.rt4,
    ANALOG_STICK_MIN,
    ANALOG_STICK_NEUTRAL,
    ANALOG_STICK_MAX,
    outputs);
    }
}
