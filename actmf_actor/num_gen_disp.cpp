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

caf::result< int > num_gen_disp_bhvr::operator()(bool b)
{
  num = rand() % 10;
  std::cout << "random number = " << num << std::endl;
  self->delayed_anon_send(self, std::chrono::seconds(3), true);
  return num;
}

void num_gen_disp_factory::init(caf::actor act) {
  caf::anon_send(act, true);
}

caf::actor num_gen_disp_factory::spawn()
{
  auto act = system->spawn<num_gen_disp_bhvr>();
  return caf::actor_cast<caf::actor>(act);
}