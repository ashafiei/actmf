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

#include "actmf/graph.h"

using namespace actmf;

graph::graph()
{

}

void graph::add_node(node n)
{
  graph_data[n.name] = n;
}


void graph::add_link(std::__cxx11::string nbefore, std::__cxx11::string nafter)
{
  node nb = graph_data[nbefore];
  node na = graph_data[nafter];
  nb.next_nodes.push_back(na);
}


graph::~graph()
{

}
