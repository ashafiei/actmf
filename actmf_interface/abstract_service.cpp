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

frame::frame()
{
  number = 0;
}

frame::frame(const frame& x)
{
  number = x.number;
}

cv::Mat* opencv_mat::operator->()
{
  return mat;
}

cv::Mat* opencv_mat::get_mat()
{
  return mat;
}

opencv_mat::opencv_mat():frame()
{
}

opencv_mat::opencv_mat(const opencv_mat& x):frame(x)
{
  mat = new cv::Mat(*(x.mat));
}

void opencv_mat::set_mat(cv::Mat * x)
{
  mat = x;
  number ++;
}

std::vector< uchar >& opencv_mat::get_data()
{
  for (long int i=0; i< mat->rows * mat->cols * 3 ; i++) {
    data.push_back(mat->data[i]);
  }
  return data;
}

void opencv_mat::set_data(std::vector< uchar > data, int rows, int cols, int type)
{
  mat = new cv::Mat(rows, cols, type);
  
  for (long int i=0; i< rows * cols * 3; i++) {
    mat->data[i] = data[i];
  }
}

opencv_mat::~opencv_mat()
{
  delete mat;
}

cv::Rect* opencv_rect::operator->()
{
  return rect;
}

opencv_rect::opencv_rect():frame()
{
  rect = new cv::Rect();
}

opencv_rect::opencv_rect(const opencv_rect& x):frame(x)
{
  rect = new cv::Rect(*(x.rect));
}

void opencv_rect::set_data(int x, int y, int width, int height)
{
  rect->x = x; rect->y = y; rect->width = width; rect->height = height;
}

opencv_rect::opencv_rect(const cv::Rect& r)
{
  rect->x = r.x; rect->y = r.y; rect->width = r.width; rect->height = r.height;
}

caf::result< int > abstract_service_bhvr::operator()(caf::param< std::string > app, caf::param< std::string > host, int16_t port)
{
  service * serv = new service;
  auto eact = self->system().middleman().remote_actor(host, port);
  if (!eact)
    throw std::runtime_error(self->system().render(eact.error()));
  caf::actor act = caf::actor_cast<caf::actor>(std::move(*eact));
  serv->set_address(host);
  serv->set_port(port);
  serv->set_actor(act);
  next_service[app.get()].push_back(serv);
  return 0;
}


