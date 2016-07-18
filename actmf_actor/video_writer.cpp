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

#include "video_writer.h"

using namespace actmf;

video_writer_factory Factory;

video_writer::video_writer(caf::actor_config& cfg): abstract_service(cfg)
{
  vwriter = new VideoWriter();
  vwriter->init("/home/sh/Videos/bbb2.mp4", 640, 480);
}

caf::behavior video_writer::awaiting_task()
{
   return {
     [=](std::string app_name, RawFrame data) {
       caf::aout(this) << "data is received\n";
       AVFrame * f = data.getFrame();
       caf::aout(this) << "width--- " << f->width << " ---\n";
       //vwriter->write(&data);
       caf::aout(this) << "data is written\n";       
       //caf::aout(this) << *(data.data->data[0]) << data.data->width << std::endl;
       //caf::aout(this) << *(data.buffer[0]) << *(data.buffer[1])
       //<< *(data.buffer[2]) << *(data.buffer[3]) << *(data.buffer[4])
       //<< data.height << data.width << std::endl;
     }
  };
}

video_writer::~video_writer()
{

}

caf::actor video_writer_factory::spawn(caf::actor_system * system)
{
  return system->spawn<video_writer>();
}