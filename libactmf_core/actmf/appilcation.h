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

#ifndef APPLICATION_H
#define APPLICATION_H

#include "caf/all.hpp"

namespace actmf {
  
  class component {
  public:
    std::string name;
    caf::atom_value type;
    std::vector<component> next_components;
    component() {}
    component(std::string name, caf::atom_value type) {
      this->name = name;
      this->type = type;
    }
  };
  
  class application 
  {
  private:
    std::map<std::string,component> application_data;
  public:
    application();
    void add_component(component c);
    void add_link(std::string cbefore, std::string cafter);
    ~application();
  };
}

#endif // APPLICATION_H
