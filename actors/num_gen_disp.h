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

#ifndef ACTMF_NUM_GEN_DISP_H
#define ACTMF_NUM_GEN_DISP_H

#include "actmf/abstract_actor.h"

namespace actmf {
  
  class num_gen_disp : public actmf::abstract_actor
  {
  private:
  protected:
    virtual caf::behavior awaiting_task() {
      return {
	[=]() {
	  int a = rand() % 10;
	  caf::aout(this) << "random number= " << a << std::endl;
	},
	caf::after(std::chrono::seconds(3)) >> [=] {
	  this->send(this);
	}	
      };
    }
  public:
    num_gen_disp(const std::string& host, int16_t port) : abstract_actor(host, port) {};
    ~num_gen_disp() {}
  };
 
}

#endif // ACTMF_NUM_GEN_DISP_H