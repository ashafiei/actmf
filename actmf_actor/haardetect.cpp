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

#include "haardetect.h"

using namespace actmf;

haardetect_factory Factory;

haardetect_bhvr::haardetect_bhvr()
{
  if( !cascade.load( "/usr/share/opencv/haarcascades/haarcascade_fullbody.xml" ) ) {
    caf::aout(self) << "error while loading the cascade\n";
  };
}

caf::result< int > haardetect_bhvr::operator()(caf::param<std::string> app, caf::param<opencv_mat> mat)
{
  std::vector<opencv_rect> rects;
  opencv_mat omat = mat.get();
  cv::Mat * m = omat.get_mat();
  cv::cvtColor( *m, gray, CV_BGR2GRAY );
  cv::equalizeHist(gray, gray);

  cascade.detectMultiScale( gray, objects, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );
  caf::aout(self) << "objects: " << objects.size() << "\n";
  for (auto b : objects) {
    opencv_rect r(b);
    r.number = omat.number;
    rects.push_back(r);
  }
  
  for(service * serv : next_service[app.get()])
    caf::anon_send(serv->get_actor(), app.get(), rects);
  return 0;
}

caf::actor haardetect_factory::remote_spawn(caf::expected<caf::node_id> node,
					  caf::message args, 
					  caf::duration tout)
{
  auto type = "haardetect_actor";
  auto act = system->middleman().remote_spawn<haardetect_bhvr>(node.value(), type, args, tout);
  //return caf::actor_cast<caf::actor>(act);
  auto ac = system->spawn<haardetect_bhvr>();
  return caf::actor_cast<caf::actor>(ac);
}
