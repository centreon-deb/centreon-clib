/*
** Copyright 2012-2013 Centreon
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

#include <cstdlib>
#include <iostream>
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/io/directory_entry.hh"

using namespace com::centreon;

/**
 *  Check copy object.
 *
 *  @return EXIT_SUCCESS on success.
 */
int main() {
  int ret(EXIT_FAILURE);
  try {
    io::directory_entry e1(".");
    io::directory_entry e2(e1);
    if (e1 != e2)
      throw (basic_error() << "copy constuctor failed");

    io::directory_entry e3 = e1;
    if (e1 != e3)
      throw (basic_error() << "copy operator failed");

    ret = EXIT_SUCCESS;
  }
  catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
  return (ret);
}
