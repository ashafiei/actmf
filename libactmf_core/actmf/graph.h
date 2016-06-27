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

#ifndef GRAPH_H
#define GRAPH_H

#include "caf/all.hpp"

namespace actmf {
  
  class node {
  public:
    std::string name;
    caf::atom_value type;
    std::vector<node> next_nodes;
    node() {}
    node(std::string name, caf::atom_value type) {
      this->name = name;
      this->type = type;
    }
  };
  
  class graph
  {
  private:
    std::map<std::string,node> graph_data;
  public:
    graph();
    void add_node(node n);
    void add_link(std::string nbefore, std::string nafter);
    ~graph();
  };
}

#endif // GRAPH_H
