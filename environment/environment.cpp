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
#include "environment_actor.h"

int main(int argc, char ** argv) {

  std::string host = "127.0.0.1";
  int16_t port = 5000;
  //actmf::environment_actor env;
  //env.spawn();
  //env.publish(host, port);
  caf::actor ac = caf::spawn<actmf::environment_actor>();
  caf::io::publish(ac, port, host.c_str());
  
  caf::await_all_actors_done();
  caf::shutdown();
  
  return 0;
}