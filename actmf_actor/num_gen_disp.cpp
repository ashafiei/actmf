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

#include "num_gen_disp.h"

using namespace actmf;

num_gen_disp_factory Factory;

caf::result< int > num_gen_disp_bhvr::operator()(bool)
{
  //TODO for loop with delay of 3 seconds.
  int a = rand() % 10;
  caf::aout(servp) << "random number= " << a << std::endl;
  return a;
}
    //TODO caf::after(std::chrono::seconds(3)) >> [=] {
    //  this->send(this, true);
    //}



void num_gen_disp_factory::spawn(caf::actor_system * sys, int port)
{
  auto act = sys->spawn<num_gen_disp_bhvr>();
  sys->middleman().publish(act, port);
}

