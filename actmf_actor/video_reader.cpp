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
  cap = new cv::VideoCapture("/home/sh/Videos/bbb.mp4");
  if(!cap->isOpened())  // check if we succeeded
    std::cout << "Cannot open the camera.\n";
}

caf::result< int > video_reader_bhvr::operator()(bool b)
{
  *cap >> frame; // get a new frame from camera
  image.set_mat(&frame);
  for (auto ns : next_service) {
    for (service * serv : ns.second) {
    caf::anon_send(serv->get_actor(), ns.first, image);
    std::cout << "sending frame number:" << image.get_number() << "\n";
    }
  }
  self->delayed_anon_send(self, std::chrono::seconds(1), true);
  return 0;
}

void video_reader_factory::init(caf::actor act) {
  caf::anon_send(act, true);
}

caf::actor video_reader_factory::spawn()
{
  auto act = system->spawn<video_reader_bhvr>();
  return caf::actor_cast<caf::actor>(act);
}