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

cv::Mat* opencv_mat::operator->()
{
  return mat;
}

cv::Mat* opencv_mat::get_mat()
{
  return mat;
}

opencv_mat::opencv_mat()
{
  number = 0;
}

opencv_mat::opencv_mat(const opencv_mat& x)
{
  mat = new cv::Mat(*(x.mat));
  number = x.number;
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

void opencv_mat::set_data(std::vector< uchar > data, int rows, int cols, int type, int number)
{
  mat = new cv::Mat(rows, cols, type);
  
  for (long int i=0; i< rows * cols * 3; i++) {
    mat->data[i] = data[i];
  }
  this->number = number;
}

int opencv_mat::get_number()
{
  return number;
}

void opencv_mat::set_number(int number)
{
  this->number = number;
}

opencv_mat::~opencv_mat()
{
  delete mat;
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


