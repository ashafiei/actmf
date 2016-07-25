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

video_reader::video_reader(caf::actor_config& cfg): abstract_service(cfg)
{
  cap = new cv::VideoCapture("/home/sh/Videos/bbb.mp4");
  if(!cap->isOpened())  // check if we succeeded
    std::cout << "Cannot open the camera.\n";
}

caf::behavior video_reader::awaiting_task()
{
   return {
     [=] (std::string app_name, std::string host, int16_t port) {
       insert_service(app_name, host, port);
     },
     [=](std::string app_name) {
       *cap >> frame; // get a new frame from camera
       image.set_mat(&frame);
       
       for(service * serv : next_service[app_name]) {
         this->send(serv->get_actor(), app_name, image);
	 caf::aout(this) << "sending frame number:" << image.get_number() << "\n";
       }
     },
     caf::after(std::chrono::seconds(1)) >> [=] {
       for (auto serv : next_service) 
          this->send(this, serv.first);
     }
  };
}

video_reader::~video_reader()
{

}

caf::actor video_reader_factory::spawn()
{
  return system->spawn<video_reader>();
}