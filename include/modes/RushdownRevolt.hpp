#ifndef _MODES_RUSHDOWNREVOLT_HPP
#define _MODES_RUSHDOWNREVOLT_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class RushdownRevolt : public ControllerMode {
  public:
    RushdownRevolt(socd::SocdType socd_type);

  private:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
