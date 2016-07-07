/*
 * Actor Multimedia Framework (actmf)
 * Copyright (C) 2016  Arash Shafiei
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <iostream>
#include <fstream>

#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include "actmf_interface/abstract_service.h"

class config : public caf::actor_system_config {
public:
  uint16_t port = 5000;
  std::string host = "127.0.0.1";
  std::string application = "";

  config() {
    opt_group{custom_options_, "global"}
    .add(port, "port,p", "set port")
    .add(host, "host,h", "set host")
    .add(application, "application,a", "application configuration file");
  }
};

void caf_main(caf::actor_system& system, const config& cfg) {
  
  if (cfg.application == "") {
    std::cout << "Please provide the application configuration file." << std::endl;
    return;
  }
  
  std::ifstream f(cfg.application);
  std::string app((std::istreambuf_iterator<char>(f)),
                 std::istreambuf_iterator<char>());
  
  auto eenv = system.middleman().remote_actor(cfg.host, cfg.port);
  if (!eenv)
    throw std::runtime_error(system.render(eenv.error()));
  caf::actor env = std::move(*eenv);
  caf::anon_send(env, actmf::create_app_atom::value, app);
  system.await_all_actors_done();
}

CAF_MAIN(caf::io::middleman)