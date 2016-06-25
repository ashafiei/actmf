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

#include "actmf/environment_actor.h"

using namespace actmf;

using register_atom = caf::atom_constant<caf::atom("register")>;
using create_app_atom = caf::atom_constant<caf::atom("create_app")>;

caf::behavior environment_actor::awaiting_task()
{
    return {
      [=](register_atom reg, caf::atom_value actname, std::string& host, int16_t port) {
       
      },
      [=](create_app_atom create, const std::string& conf) {
       
      }
    };
}