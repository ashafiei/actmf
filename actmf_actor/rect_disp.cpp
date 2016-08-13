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

#include "rect_disp.h"

using namespace actmf;

rect_disp_factory Factory;

caf::result< int > rect_disp_bhvr::operator()(caf::param< std::string > app, caf::param<std::vector<opencv_rect>> rects)
{
  std::vector<opencv_rect> vr = rects.get();
  for (opencv_rect r : vr) {
    caf::aout(self) << "frame " << r.number << ":(" << r->x << "," << r->y << "," 
    << r->width << "," << r->height << ")\n";
  }
  caf::aout(self) << "\n";
  return 0;
}

caf::actor rect_disp_factory::spawn()
{
  auto act = system->spawn<rect_disp_bhvr>();
  return caf::actor_cast<caf::actor>(act);
}