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

#ifndef ACTMF_ENVIRONMENT_ACTOR_H
#define ACTMF_ENVIRONMENT_ACTOR_H

#include <iostream>
#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include "actmf_interface/abstract_service.h"
#include "module_loader.h"

namespace actmf {
  
  class environment_actor : public caf::event_based_actor
  {
  private:
    module_loader ml;
    caf::behavior awaiting_task();
  public:
    environment_actor(caf::actor_config& cfg);
    virtual caf::behavior make_behavior();
    ~environment_actor();
  };
}

#endif // ACTMF_ENVIRONMENT_ACTOR_H
