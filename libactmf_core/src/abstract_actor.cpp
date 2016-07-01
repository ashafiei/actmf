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

abstract_actor::abstract_actor(const std::string& host, int16_t port)
{
  this->host = host;
  this->port = port;
  caf::io::publish(this, port, host.c_str());
  caf::aout(this) << "actor is listening on " << host << " on port " << port << std::endl;
}

caf::behavior abstract_actor::make_behavior()
{
  this->become(awaiting_task());
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

void abstract_actor::append_remote_actor(int app_id, int id, const std::string& addr, int16_t port)
{
  caf::actor act = caf::io::remote_actor(addr.c_str(), port);
  remote_actor r_act = {.id = id, .act = act, .addr = addr, .port = port};
  this->next_actors[app_id].push_back(r_act);
}


void abstract_actor::clear_actors()
{
  this->next_actors.clear();
}

abstract_actor::~abstract_actor()
{
  caf::io::unpublish<caf::actor>(this, port);
}


