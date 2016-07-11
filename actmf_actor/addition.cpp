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
     [=] (int app_id, caf::actor act) {
       next_service[app_id].push_back(act);
     },
     [=](int app_id, int x, int y) {
       int res = x + y;
       for(caf::actor act : next_service[app_id])
         this->send(act, app_id, res);
     }
  };
}

addition::~addition()
{

}

caf::actor addition_factory::spawn(caf::actor_system * system)
{
  return system->spawn<addition>();
}