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

#ifndef MODULE_LOADER_H
#define MODULE_LOADER_H

#include "actmf_interface/abstract_service.h"
#include "application_parser.h"
#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include <dlfcn.h>

namespace actmf {
  
  struct service {
    caf::actor * act;
    std::string addr;
    int16_t port;
  };
  
  class module_loader
  {
  private:
    int cur_port;
    caf::actor_system_config cfg;
    caf::actor_system * system;
    std::map<std::string, service *> registry;
    application_parser app_parser;
  public:
    module_loader();
    void load_application(const std::string& app);
    service * load_module(const std::string& module);
    ~module_loader();
  };
}

#endif // MODULE_LOADER_H
