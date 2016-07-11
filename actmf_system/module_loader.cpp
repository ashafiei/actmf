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

#include "module_loader.h"

using namespace actmf;

module_loader::module_loader()
{
  this->cfg.load<caf::io::middleman>();
  system = new caf::actor_system(this->cfg);
  cur_port = 6000;
}

service * module_loader::load_module(const std::__cxx11::string& module)
{
  
  service * serv = registry[module];
  if (serv != nullptr)
    return serv;
  serv = new service();
  
  serv->addr = "127.0.0.1";
  serv->port = cur_port++;
  serv->type = module;
  
  void *handl = dlopen(module.c_str(), RTLD_NOW);
  if(handl == nullptr){
    std::cout << dlerror() << std::endl;
    return nullptr;
  }
  
  abstract_service_factory *serv_factory = (abstract_service_factory*)dlsym(handl, "Factory");
  if (serv_factory == nullptr) {
    std::cout << dlerror() << std::endl;
    return nullptr;
  }
  caf::actor act = serv_factory->spawn(system);
  serv->act = &act;
  if (serv->act == nullptr) {
    std::cout << "abstract_actor is not created" << std::endl;
    return nullptr;
  }
  
  registry[module] = serv;
  
  system->middleman().publish(*(serv->act), serv->port);
  
  return serv;
}


module_loader::~module_loader()
{

}
