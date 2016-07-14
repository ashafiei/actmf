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
  
  struct VideoData {
    uint8_t * buffer[8];
    int width;
    int height;
  };
  
  template <class Inspector>
  typename Inspector::result_type inspect(Inspector& f, VideoData& x) {
    return f(caf::meta::type_name("VideoData"));
  }
  
  using direct_atom = caf::atom_constant<caf::atom("direct")>;
  
  using generate_atom = caf::atom_constant<caf::atom("generate")>;  
  using add_atom = caf::atom_constant<caf::atom("add")>;
  using disp_num_atom = caf::atom_constant<caf::atom("dis_num")>;
  using gen_disp_atom = caf::atom_constant<caf::atom("gen_disp")>;
  
  using register_atom = caf::atom_constant<caf::atom("register")>;
  using create_app_atom = caf::atom_constant<caf::atom("create_app")>;
  
  class abstract_service : public caf::event_based_actor
  {
  protected:
    virtual caf::behavior awaiting_task() = 0;
    caf::behavior awaiting_direction();
    std::map<std::string, std::vector<caf::actor>> next_service;
  public:
    abstract_service(caf::actor_config& cfg);
    caf::behavior make_behavior() override; 
    ~abstract_service();
    
  };
  
  class abstract_service_factory {
  public:
    virtual caf::actor spawn(caf::actor_system * system) = 0;
  };

}

#endif // ABSTRACT_SERVICE_H