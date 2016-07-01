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

#include <dlfcn.h>
#include "environment_actor.h"

using namespace actmf;

environment_actor::environment_actor()
{

}

void environment_actor::spawn()
{
  act_handle = caf::spawn<environment_actor>();
}

environment_actor::~environment_actor()
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
	
	void *handl = dlopen("libnum_gen_disp.so", RTLD_NOW);
	if(handl == nullptr){
	  caf::aout(this) << dlerror() << std::endl;
	  exit(-1);
	}
	actor_factory *act_factory = (actor_factory*)dlsym(handl, "Factory");
	if (act_factory == nullptr) {
	  std::cout << "act_factory is not created" << std::endl;
	  exit(-1);
	}
	abstract_actor * act = act_factory->create_actor();
	if (act == nullptr) {
	  std::cout << "abstract_actor is not created" << std::endl;
	  exit(-1);
	}
	act->spawn();
	act->publish("127.0.0.1", 4000);
	
	//act->spawn("127.0.0.1", 4000);
	//abstract_actor *gendisp = static_cast<abstract_actor *()>(gendisp_hdl)();
	//this->append_app(app);
	//std::vector<component *> components = app.get_components();
	//for (auto comp : components) {
	//  comp->spawn("localhost", 4000);
	//}
      }
    };
}