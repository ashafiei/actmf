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

#include "actmf/gen_num_actor.h"

using namespace actmf;

caf::behavior gen_num_actor::awaiting_task()
{
  return {
    [=](generate_atom generate) {
       int a = rand() % 10;
       int b = rand() % 10;
       for (remote_actor ract : next_actors)
	 this->send(ract.act, add_atom::value, a, b);
    },
    caf::after(std::chrono::seconds(3)) >> [=] {
      this->send(this, generate_atom::value);
    }
  };
}

