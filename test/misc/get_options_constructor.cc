/*
** Copyright 2011-2014 Centreon
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
** For more information : contact@centreon.com
*/

#include <iostream>
#include <string>
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/misc/get_options.hh"

using namespace com::centreon::misc;

/**
 *  @class my_options
 *  @brief litle implementation of get_options to test it.
 */
class my_options : public get_options {
public:
      my_options(std::vector<std::string> const& args)
    : get_options() {
    _arguments['a'] = argument("arg", 'a', "", argument::multiple);
    _arguments['c'] = argument("cold", 'c', "", argument::multiple);
    _arguments['t'] = argument("test", 't', "", argument::multiple);
    _arguments['h'] = argument("help", 'h');
    _arguments['d'] = argument(
                        "default",
                        'd',
                        "",
                        argument::multiple);
    _arguments['d'].add_value("def");
    _parse_arguments(args);
  }
      ~my_options() throw () {}
};

/**
 *  Check the get_options constructor.
 *
 *  @return 0 on success.
 */
int main() {
  try {
    std::vector<std::string> args;
    args.push_back("-c1");
    args.push_back("--test=1");
    args.push_back("-h");
    args.push_back("--arg");
    args.push_back("2");
    args.push_back("param1");
    args.push_back("param2");
    args.push_back("param3");

    my_options opt(args);
    if (opt.get_parameters().size() != 3
        || opt.get_arguments().size() != 5)
      throw (basic_error() << "constructor failed");
  }
  catch (std::exception const& e) {
    std::cerr << "error: " << e.what() << std::endl;
    return (1);
  }
  return (0);
}
