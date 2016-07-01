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

#ifndef ACTMF_ENVIRONMENT_H
#define ACTMF_ENVIRONMENT_H

#include "actmf/abstract_actor.h"
#include <vector>


namespace actmf {
  
  class environment_actor : public actmf::abstract_actor
  {
  private:
    int cur_app_id;
  protected:
    virtual caf::behavior awaiting_task();
  public:
    environment_actor(const std::string& host, int16_t port) : abstract_actor(host, port) {
      cur_app_id = 1;
    };
    ~environment_actor() {}
  };
}

#endif // ACTMF_ENVIRONMENT_H
