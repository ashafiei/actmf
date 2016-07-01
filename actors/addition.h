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

#ifndef ACTMF_ADDITION_H
#define ACTMF_ADDITION_H

#include "actmf/abstract_actor.h"

namespace actmf {
  
  class addition : public abstract_actor 
  {
  private:
  protected:
    virtual caf::behavior awaiting_task() {
      return {
      [=](int app_id, int x, int y) {
	int res = x + y;
	for(remote_actor ract : next_actors[app_id])
	  this->send(ract.act, app_id, res);
      }
      };
    }
  public:
    addition(const std::string& host, int16_t port) : abstract_actor(host, port) {};
    ~addition() {}
  };
 
}

#endif // ACTMF_ADDITION_H
