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

#include "abstract_service.h"

using namespace actmf;

caf::result< int > abstract_service_bhvr::operator()(caf::param< string > app, caf::param< string > host, int16_t port)
{
  service * serv = new service;
  auto eact = servp->system().middleman().remote_actor(host, port);
  if (!eact)
    throw std::runtime_error(servp->system().render(eact.error()));
  caf::actor act = caf::actor_cast<caf::actor>(std::move(*eact));
  serv->set_address(host);
  serv->set_port(port);
  serv->set_actor(act);
  next_service[app.get()].push_back(serv);
  return 0;
}

