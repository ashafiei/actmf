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

  caf::actor env = caf::io::remote_actor("localhost", 5000);
  
  actmf::application app;
  actmf::component gen_num(std::string("gen_num"), actmf::gen_num::value);
  actmf::component addition(std::string("addition"), actmf::addition::value);
  actmf::component disp_num(std::string("disp_num"), actmf::disp_num::value);
  
  app.add_component(gen_num);
  app.add_component(addition);
  app.add_component(disp_num);
  
  app.add_link("gen_num", "addition");
  app.add_link("addition", "disp_num");
  
  caf::anon_send(env, actmf::create_app_atom::value, app);
  caf::await_all_actors_done();
  caf::shutdown();
  
  return 0;
}