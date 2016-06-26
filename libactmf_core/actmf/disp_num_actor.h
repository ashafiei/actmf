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

#ifndef ACTMF_DISP_NUM_ACTOR_H
#define ACTMF_DISP_NUM_ACTOR_H

#include "actmf/abstract_actor.h"

namespace actmf {
  
  class disp_num_actor : public actmf::abstract_actor
  {
  private:
  protected:
    virtual caf::behavior awaiting_task();
  public:
    disp_num_actor(const std::__cxx11::string& host, int16_t port) : abstract_actor(host, port) {};
    ~disp_num_actor() {}
  };
 
}

#endif // ACTMF_DISP_NUM_ACTOR_H