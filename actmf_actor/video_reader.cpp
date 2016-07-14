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
  vreader = new VideoReader("bbb.mp4");
  //vreader->setVideoFromat(videoFromat);
  //vreader->setInputFormat(inputFormat);
  //vreader->setFramerate(framerate);
  vreader->init();
}

caf::behavior video_reader::awaiting_task()
{
   return {
     [=] (std::string app_name, caf::actor act) {
       next_service[app_name].push_back(act);
     },
     [=](std::string app_name) {
       VideoData data;
       for (int i=0; i<8; i++) {
       
	 data.buffer[i] = new uint8_t;
	 *(data.buffer[i]) = i;
       }
       data.height = 100;
       data.width = 200;
       //RawFrame * data;
       //AVFrame frame;
       //int ret = vreader->readFrame(data); 
       //if (ret == -1) {
	 //video ended
       //}
       for(caf::actor act : next_service[app_name])
         this->send(act, app_name, data);
     },
     caf::after(std::chrono::seconds(3)) >> [=] {
       for (auto serv : next_service) 
          this->send(this, serv.first);
     }
  };
}

video_reader::~video_reader()
{

}

caf::actor video_reader_factory::spawn(caf::actor_system * system)
{
  return system->spawn<video_reader>();
}