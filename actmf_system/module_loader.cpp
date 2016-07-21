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
void module_loader::load_application(const std::__cxx11::string& app)
{
  app_parser.parse(app);
  
  std::string app_name = app_parser.get_app_name();
  std::cout << "application:" << app_name << std::endl;
  
  std::vector<std::string> nodes = app_parser.get_nodes();
  for (auto n : nodes) {
    std::cout << "node:" << n << std::endl;
    if (registry.find(n) == registry.end()) {
      
      load_module(n);
      std::cout << "module loaded:" << n << std::endl;
    }
  }
  for (auto n : nodes) {
    std::vector<std::string> connections = app_parser.get_connections(n);
    for (auto c : connections) {
      caf::anon_send(registry[n]->get_actor(), 
		     app_name , registry[c]->get_address(), 
		     registry[c]->get_port()
		    );
    }
  }
}

service * module_loader::load_module(const std::__cxx11::string& module)
{
  
  service * serv = registry[module];
  if (serv != nullptr)
    return serv;
  serv = new service();
  
  serv->set_address("127.0.0.1");
  serv->set_port(cur_port++);
  
  std::string module_file = "../lib/lib"+module+".so";
  void *handl = dlopen(module_file.c_str(), RTLD_NOW);
  if(handl == nullptr){
    std::cout << dlerror() << std::endl;
    return nullptr;
  }
  
  abstract_service_factory *serv_factory = (abstract_service_factory*)dlsym(handl, "Factory");
  if (serv_factory == nullptr) {
    std::cout << dlerror() << std::endl;
    return nullptr;
  }
  auto act = serv_factory->spawn(system);
  
  serv->set_actor(act);
  
  if (!serv->has_actor()) {
    std::cout << "abstract_actor is not created" << std::endl;
    return nullptr;
  }
  
  system->middleman().publish(serv->get_actor(), serv->get_port());
  
  registry[module] = serv;
  
  return serv;
}


module_loader::~module_loader()
{

}
