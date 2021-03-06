/*
** Copyright 2011-2013 Centreon
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
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/shared_ptr.hh"

using namespace com::centreon;

/**
 *  Check the shared_ptr clear.
 *
 *  @return 0 on success.
 */
int main() {
  int ret(0);
  try {
    shared_ptr<int> ptr(NULL);
    ptr.clear();
    if (ptr.get())
      throw (basic_error() << "clear null pointer failed");
    ptr = shared_ptr<int>(new int(42));
    ptr.clear();
    if (ptr.get())
      throw (basic_error() << "clear pointer failed");
    shared_ptr<int> ptr2(new int(42));
    ptr = ptr2;
    ptr2.clear();
    if (!ptr.get())
      throw (basic_error() << "clear failed with multiple reference");
  }
  catch (std::exception const& e) {
    ret = 1;
    std::cerr << "error: " << e.what() << std::endl;
  }
  return (ret);
}
