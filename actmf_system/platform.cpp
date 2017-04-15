#include <iostream>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

class config : public caf::actor_system_config {
public:
  uint16_t port = 6000;

  config() {
    opt_group{custom_options_, "global"}
    .add(port, "port,p", "set port");
  }
};

void caf_main(caf::actor_system& system, const config& cfg) {
  
  system.middleman().open(cfg.port);
  
}

CAF_MAIN(caf::io::middleman)