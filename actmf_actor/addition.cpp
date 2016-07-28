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

#include "addition.h"

using namespace actmf;

addition_factory Factory;

caf::result< int > addition_bhvr::operator()(caf::param< std::string > app, int x, int y)
{
  int res = x + y;
  for(service * serv : next_service[app.get()])
    caf::anon_send(serv->get_actor(), app.get(), res);
  return res;
}

caf::actor addition_factory::spawn()
{
  auto act = system->spawn<addition_bhvr>();
  return caf::actor_cast<caf::actor>(act);
}