#include "caf/all.hpp"
#include "caf/io/all.hpp"

using namespace caf;
using namespace std;

using add_atom = atom_constant<atom("add")>;
using sub_atom = atom_constant<atom("sub")>;

// class-based, dynamically typed, event-based API
class calculator : public event_based_actor {
public:
  calculator(actor_config& cfg) : event_based_actor(cfg) {
    // nop
  }

  behavior make_behavior() override {
    return behavior{
     [](add_atom, int a, int b) {
       return a + b;
     },
     [](sub_atom, int a, int b) {
       return a - b;
     }
  }; 
  }
};

class config : public caf::actor_system_config {
public:
  string host = "127.0.0.1";
  uint16_t port = 6000;

  config() {
    opt_group{custom_options_, "global"}
    .add(host, "host,h", "set host")
    .add(port, "port,p", "set port");
  }
};

void caf_main(caf::actor_system& system, const config& cfg) {

  auto node = system.middleman().connect(cfg.host, cfg.port);
  if (!node) {
    cerr << "*** connect failed: "
         << system.render(node.error()) << endl;
    return;
  }
  auto type = "calculator"; // type of the actor we wish to spawn
  auto args = make_message(); // arguments to construct the actor
  auto tout = std::chrono::seconds(30); // wait no longer than 30s
  auto worker = system.middleman().remote_spawn<calculator>(*node, type,
                                                            args, tout);
  if (!worker) {
    cerr << "*** remote spawn failed: "
         << system.render(worker.error()) << endl;
    return;
  }

  // start using worker in main loop
  //client_repl(make_function_view(*worker));
  
}

CAF_MAIN(caf::io::middleman)
