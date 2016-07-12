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

#ifndef APPLICATION_PARSER_H
#define APPLICATION_PARSER_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

class application_parser
{
private:
  std::string conf;
  std::string app_name;
  std::map<std::string, std::vector<std::string>> data;
  
public:
  application_parser();
  void parse(const std::string& conf);
  std::string get_app_name();
  std::vector<std::string> get_nodes();
  std::vector<std::string> get_connections(std::string node);
  ~application_parser();
};

#endif // APPLICATION_PARSER_H
