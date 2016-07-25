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

#include "video_reader.h"

using namespace actmf;

video_reader_factory Factory;

video_reader_bhvr::video_reader_bhvr()
{
  
}

caf::result< int > video_reader_bhvr::operator()(caf::param< std::string > app)
{
  
  for(service * serv : next_service[app.get()]) {
    caf::anon_send(serv->get_actor(), app.get(), image);
    std::cout << "sending frame number:" << image.get_number() << "\n";
  }
}

   //TODO return {
   //  caf::after(std::chrono::seconds(1)) >> [=] {
   //    for (auto serv : next_service) 
   //       this->send(this, serv.first);
   //  }
   //};

caf::actor video_reader_factory::spawn()
{
  auto act = system->spawn<video_reader_bhvr>();
  return caf::actor_cast<caf::actor>(act);
}