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

#include <iostream>

#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include "environment_actor.h"

void caf_main(caf::actor_system& system) {
  
  caf::actor env = system.spawn<actmf::environment_actor>();
  system.middleman().publish(env, 5000);

  system.await_all_actors_done();
}

CAF_MAIN(caf::io::middleman)

