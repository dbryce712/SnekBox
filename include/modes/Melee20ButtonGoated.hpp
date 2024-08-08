#ifndef _MODES_MELEE20BUTTONGOATED_HPP
#define _MODES_MELEE20BUTTONGOATED_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

typedef struct {
    bool crouch_walk_os = false;
} Melee20ButtonGoatedOptions;

class Melee20ButtonGoated : public ControllerMode {
  public:
    Melee20ButtonGoated(socd::SocdType socd_type, Melee20ButtonGoatedOptions options = {});

  protected:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);

  private:
    Melee20ButtonGoatedOptions _options;
    bool _horizontal_socd;

    void HandleSocd(InputState &inputs);
};

#endif