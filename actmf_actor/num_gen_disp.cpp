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

#include "num_gen_disp.h"

using namespace actmf;

num_gen_disp_factory Factory;

num_gen_disp::num_gen_disp(caf::actor_config& cfg): abstract_service(cfg)
{

}

caf::behavior num_gen_disp::awaiting_task()
{
  return {
    [=](bool) {
      int a = rand() % 10;
      caf::aout(this) << "random number= " << a << std::endl;
    },
    caf::after(std::chrono::seconds(3)) >> [=] {
      this->send(this, true);
    }
  };
}

num_gen_disp::~num_gen_disp()
{

}

caf::actor num_gen_disp_factory::spawn(caf::actor_system * system)
{
  return system->spawn<num_gen_disp>();
}

