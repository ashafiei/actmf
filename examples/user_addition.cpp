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

#include <iostream>
#include "actmf/all.h"

int main(int argc, char ** argv) {

  actmf::graph g;
  actmf::node gen_num(std::string("gen_num"), actmf::gen_num::value);
  actmf::node addition(std::string("addition"), actmf::addition::value);
  actmf::node disp_num(std::string("disp_num"), actmf::disp_num::value);
  
  g.add_node(gen_num);
  g.add_node(addition);
  g.add_node(disp_num);
  
  g.add_link("gen_num", "addition");
  g.add_link("addition", "disp_num");
  
  return 0;
}