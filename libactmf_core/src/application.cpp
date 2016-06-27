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

#include "actmf/appilcation.h"

using namespace actmf;

application::application()
{

}

void application::add_component(component c)
{
   application_data[c.name] = c;
}

void application::add_link(std::__cxx11::string cbefore, std::__cxx11::string cafter)
{
  component cb = application_data[cbefore];
  component ca = application_data[cafter];
  cb.next_components.push_back(ca);
}

application::~application()
{

}

