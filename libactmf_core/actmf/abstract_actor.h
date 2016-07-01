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

#ifndef ACTOR_H
#define ACTOR_H

#include "caf/all.hpp"
#include "caf/io/all.hpp"

namespace actmf {

  using direct_atom = caf::atom_constant<caf::atom("direct")>;
  
  using generate_atom = caf::atom_constant<caf::atom("generate")>;  
  using add_atom = caf::atom_constant<caf::atom("add")>;
  using disp_num_atom = caf::atom_constant<caf::atom("dis_num")>;
  
  using register_atom = caf::atom_constant<caf::atom("register")>;
  using create_app_atom = caf::atom_constant<caf::atom("create_app")>;

  struct remote_actor {
    int id;
    caf::actor act;
    std::string addr;
    int16_t port;
  };
  
  class abstract_actor : public caf::event_based_actor
  {
  protected:
    std::string type;
    virtual caf::behavior awaiting_task() = 0;
    caf::behavior awaiting_direction();
    std::string host;
    uint16_t port;
    std::map<int, std::vector<remote_actor>> next_actors;
  public:
    abstract_actor(const std::string& host, int16_t port);
    caf::behavior make_behavior() override;
    void append_remote_actor(int app_id, int id, const std::string& addr, int16_t port);   
    void clear_actors();
    ~abstract_actor();
    
  };
  
}

#endif // ACTOR_H
