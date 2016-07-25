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

caf::result< int > num_disp_bhvr::operator()(bool b)
{
  while (true) {
    std::cout << "called...\n";
    int a = rand() % 10;
    int b = rand() % 10;
    for (auto ns : next_service) {
      std::cout << ns.first << std::endl;
      for (service * serv : ns.second) {
	std::cout << "send to " << serv->get_address() 
	<< serv->get_port() << ns.first << std::endl;
	caf::anon_send(serv->get_actor(), ns.first, a, b);
      }
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }
  
  return 0;
}

void num_gen_factory::init(caf::actor act) {
  caf::anon_send(act, true);
}

caf::actor num_gen_factory::spawn()
{
  auto act = system->spawn<num_disp_bhvr>();
  return caf::actor_cast<caf::actor>(act);
}
