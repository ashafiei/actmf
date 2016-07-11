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

#include "num_gen.h"

using namespace actmf;

num_gen_factory Factory;

num_gen::num_gen(caf::actor_config& cfg): abstract_service(cfg)
{

}

caf::behavior num_gen::awaiting_task()
{
  return {
    [=] (int app_id, caf::actor act) {
      next_service[app_id].push_back(act);
    },
    [=](int app_id) {
     int a = rand() % 10;
     int b = rand() % 10;
     for (caf::actor act : next_service[app_id])
     this->send(act, app_id, a, b);
     
    },
    caf::after(std::chrono::seconds(3)) >> [=] {
     for (auto serv : next_service) 
      this->send(this, serv.first);
    }
  };
}

num_gen::~num_gen()
{

}

caf::actor num_gen_factory::spawn(caf::actor_system * system)
{
  return system->spawn<num_gen>();
}
