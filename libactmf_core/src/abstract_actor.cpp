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

#include "actmf/abstract_actor.h"

using namespace actmf;

using direct_atom = caf::atom_constant<caf::atom("direct")>;

abstract_actor::abstract_actor(const std::string& host, int16_t port)
{
  this->host = host;
  this->port = port;
  caf::io::publish(this, port, host.c_str());
}

caf::behavior abstract_actor::make_behavior()
{
  this->become(awaiting_task());
  this->become(caf::keep_behavior, awaiting_direction());
  return {};
}

caf::behavior abstract_actor::awaiting_direction()
{
    return {
      [=](direct_atom direct, const std::string& host, int16_t port) {
       
	this->unbecome();
      }
    };
}


abstract_actor::~abstract_actor()
{
  
}


