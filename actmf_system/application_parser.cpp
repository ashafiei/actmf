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

#include "application_parser.h"

std::string trim(const std::string& str, char ch)
{
    size_t first = str.find_first_not_of(ch);
    size_t last = str.find_last_not_of(ch);
    return str.substr(first, (last-first+1));
}

std::tuple<std::string, std::string> get_tuple(const std::string& line, const std::string& c) {
  
    char *key = std::strtok(const_cast<char*>(line.c_str()), c.c_str());
    char *val = std::strtok(NULL, c.c_str());
    std::string key_str = trim(key, ' ');
    std::string val_str = trim(val, ' ');
    return std::make_tuple(key_str, val_str);
}


application_parser::application_parser()
{

}

void application_parser::parse(const std::string& conf)
{
  this->conf = conf;
  std::string con_str;
  std::map<std::string, std::string> vars;
  
  std::istringstream f(conf);
  std::string line;    
  while (std::getline(f, line)) {
    if (line.find("=") != std::string::npos) {
      auto line_tok = get_tuple(line, "=");
      std::string key = std::get<0>(line_tok);
      std::string val = std::get<1>(line_tok);
      if (key == "application")
	app_name = trim(val, '\'');
      else if (key == "connections")
	con_str = val;
      else
	vars[key] = trim(val, '\'');
    }
  }
  
  for (auto v : vars) {
    std::vector<std::string> vec;
    data[v.second] = vec;
  }

  std::size_t start_pos = 0;
  con_str.erase(std::find(con_str.begin(), con_str.end(), ']'));
  
  while (true) {
    std::size_t pos_s = con_str.find("(", start_pos);
    std::size_t pos_e = con_str.find(")", start_pos);
    
    if (pos_s == std::string::npos || pos_e == std::string::npos)
      break;
    
    std::string tupstr = con_str.substr(pos_s, pos_e);
    tupstr.erase(std::find(tupstr.begin(), tupstr.end(), '('));
    tupstr.erase(std::find(tupstr.begin(), tupstr.end(), ')'));    
    auto tup = get_tuple(tupstr, ",");
    data[vars[std::get<0>(tup)]].push_back(vars[std::get<1>(tup)]);
    
    start_pos = pos_e + 1;
  }
  
}

std::__cxx11::string application_parser::get_app_name()
{
  return app_name;
}

std::vector< std::__cxx11::string > application_parser::get_nodes()
{
  std::vector<std::string> res;
  for (auto element : data) res.push_back(element.first);
  return res;
}

std::vector< std::__cxx11::string > application_parser::get_connections(std::__cxx11::string node)
{
  return data[node];
}



application_parser::~application_parser()
{

}
