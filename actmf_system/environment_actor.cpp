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

#include "environment_actor.h"

using namespace actmf;

environment_actor::environment_actor(caf::actor_config& cfg): caf::event_based_actor(cfg)
{
    
}

caf::behavior environment_actor::awaiting_task()
{
  std::cout << "In awaiting_task" << std::endl;
  return {
      [=](register_atom reg, caf::atom_value actname, std::string& host, int16_t port) {

      },
      [=](create_app_atom create, std::string app) {
	caf::aout(this) << app << std::endl;
	ml.load_application(app);
	ml.load_module("lib/libnum_gen_disp.so");
    }
  };
}

caf::behavior environment_actor::make_behavior()
{
  this->become(awaiting_task());
  return {};
}

environment_actor::~environment_actor()
{

}
