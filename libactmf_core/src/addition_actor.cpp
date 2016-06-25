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

#include "actmf/addition_actor.h"

using namespace actmf;

using direct_atom = caf::atom_constant<caf::atom("direct")>;
using add_atom = caf::atom_constant<caf::atom("add")>;

caf::behavior addition_actor::awaiting_task()
{
    return {
      [=](add_atom add, int x, int y) {
	
       
      },
      [=](direct_atom direct, const std::string& host, int16_t port) {
       
      }
    };
}

