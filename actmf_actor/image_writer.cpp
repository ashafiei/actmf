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

#include "image_writer.h"

using namespace actmf;

image_writer_factory Factory;

image_writer_bhvr::image_writer_bhvr()
{
  iwriter = new ImageWriter(1280, 720, AV_PIX_FMT_YUV420P);
  iwriter->setPath("/home/sh/Videos/");
}

caf::result< int > image_writer_bhvr::operator()(caf::param< string > app, caf::param< RawFrame > frame)
{
  RawFrame f = frame.get();
  caf::aout(servp) << "writing frame number:" << f.getNumber() << "\n";        
  iwriter->writeImage(&f);
}

void image_writer_factory::spawn(caf::actor_system * sys, int port)
{
  auto act = sys->spawn<image_writer_bhvr>();
  sys->middleman().publish(act, port);
}