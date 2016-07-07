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

#include "num_disp.h"

using namespace actmf;

num_disp_factory Factory;

num_disp::num_disp(caf::actor_config& cfg): abstract_service(cfg)
{

}

caf::behavior num_disp::awaiting_task()
{
  return {
    [=](int app_id, int d) {
      caf::aout(this) << "n = " << d << std::endl; 
    }
  };
}

num_disp::~num_disp()
{

}

caf::actor num_disp_factory::spawn(caf::actor_system& system)
{
  return system.spawn<num_disp>();
}
