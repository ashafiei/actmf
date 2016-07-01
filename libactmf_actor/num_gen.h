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

#ifndef ACTMF_NUM_GEN_H
#define ACTMF_NUM_GEN_H

#include "abstract_actor.h"

namespace actmf {
  
  class num_gen : public abstract_actor
  {
  private:
  protected:
    virtual caf::behavior awaiting_task() {
      return {
	[=](int app_id) {
	  int a = rand() % 10;
	  int b = rand() % 10;
	  for (remote_actor ract : next_actors[app_id])
	   this->send(ract.act, app_id, a, b);
	  
	},
	caf::after(std::chrono::seconds(3)) >> [=] {
	  for (auto r : next_actors) 
	    this->send(this, r.first);
	}	
      };
    }
  public:
    num_gen(const std::string& host, int16_t port) : abstract_actor(host, port) {};
    virtual void spawn(const std::string& host, int16_t port) {
      act_handle = caf::spawn<num_gen>(host, port);
    }
    ~num_gen() {}
  };
 
}

#endif // ACTMF_NUM_GEN_H