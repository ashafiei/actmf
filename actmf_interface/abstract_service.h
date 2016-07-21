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

#ifndef ABSTRACT_SERVICE_H
#define ABSTRACT_SERVICE_H

#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include "tmmp/all.h"

namespace actmf {
  
  using direct_atom = caf::atom_constant<caf::atom("direct")>;
  
  using generate_atom = caf::atom_constant<caf::atom("generate")>;  
  using add_atom = caf::atom_constant<caf::atom("add")>;
  using disp_num_atom = caf::atom_constant<caf::atom("dis_num")>;
  using gen_disp_atom = caf::atom_constant<caf::atom("gen_disp")>;
  
  using register_atom = caf::atom_constant<caf::atom("register")>;
  using create_app_atom = caf::atom_constant<caf::atom("create_app")>;
  
  class service {
  private:
    caf::actor * act;
    std::string addr;
    int16_t port;
  public:
    void set_actor(const caf::actor& act) {
      this->act = new caf::actor(act);
    }
    void set_address(std::string addr) {
      this->addr = addr;
    }
    void set_port(int16_t port) {
      this->port = port;
    }
    bool has_actor() { return act != nullptr; }
    caf::actor get_actor() { return *act; }
    std::string get_address() { return addr; }
    int16_t get_port() { return port; }
  };
  
  using abstract_service_actor = 
  caf::typed_actor<caf::replies_to<string, string, int>::with<int>>;

  class abstract_service_bhvr : 
  public caf::composable_behavior<abstract_service_actor> {
  protected:
    std::map<std::string, std::vector<service *>> next_service;
    abstract_service_actor::pointer servp;
  public:
    caf::result<int> operator()(caf::param<string>, caf::param<string>, int) override;
    
  };
  
  class abstract_service_factory {
  public:
    virtual void spawn(caf::actor_system * sys, int port) = 0;
  };

}

#endif // ABSTRACT_SERVICE_H