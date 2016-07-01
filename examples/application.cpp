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
#include <fstream>

#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include "actmf/all.h"

int main(int argc, char ** argv) {

  if (argc < 2) {
    std::cout << "Usage:" << argv[0] << " <application>" << std::endl;
    return 0;
  }
  
  std::ifstream f(argv[1]);
  std::string app((std::istreambuf_iterator<char>(f)),
                 std::istreambuf_iterator<char>());
  
  caf::actor env = caf::io::remote_actor("127.0.0.1", 5000);

  caf::anon_send(env, actmf::create_app_atom::value, app);
  caf::await_all_actors_done();
  caf::shutdown();
  
  return 0;
}