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

#include "addition.h"

using namespace actmf;

addition_factory Factory;

addition::addition(caf::actor_config& cfg): abstract_service(cfg)
{
}

caf::behavior addition::awaiting_task()
{
   return {
     [=] (std::string app_name, std::string host, int16_t port) {
       insert_service(app_name, host, port);
     },
     [=](std::string app_name, int x, int y) {
       int res = x + y;
       for(service * serv : next_service[app_name])
         this->send(serv->get_actor(), app_name, res);
     }
  };
}

addition::~addition()
{

}

caf::actor addition_factory::spawn()
{
  return system->spawn<addition>();
}