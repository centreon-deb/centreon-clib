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

#include <limits>
#ifdef _WIN32
#  define NOMINMAX
#  include <windows.h>
#else
#  include <sys/time.h>
#  include <ctime>
#endif // Windows or POSIX.
#include "com/centreon/timestamp.hh"

using namespace com::centreon;

/**************************************
*                                     *
*           Public Methods            *
*                                     *
**************************************/

/**
 *  Default constructor.
 *
 *  @param[in] secs   Set the seconds.
 *  @param[in] usecs  Set the microseconds.
 */
timestamp::timestamp(time_t secs, int usecs)
  : _secs(0), _usecs(0) {
  add_seconds(secs);
  add_useconds(usecs);
}

/**
 *  Copy constructor.
 *
 *  @param[in] right  The object to copy.
 */
timestamp::timestamp(timestamp const& right) {
  _internal_copy(right);
}

/**
 *  Destructor.
 */
timestamp::~timestamp() throw () {}

/**
 *  Assignment operator.
 *
 *  @param[in] right  The object to copy.
 *
 *  @return This object.
 */
timestamp& timestamp::operator=(timestamp const& right) {
  if (this != &right)
    _internal_copy(right);
  return (*this);
}

/**
 *  Compare if two object are equal.
 *
 *  @param[in] right  The object to compare.
 *
 *  @return True if equal, otherwise false.
 */
bool timestamp::operator==(timestamp const& right) const throw () {
  return (_secs == right._secs && _usecs == right._usecs);
}

/**
 *  Compare if two object are not equal.
 *
 *  @param[in] right  The object to compare.
 *
 *  @return True if not equal, otherwise false.
 */
bool timestamp::operator!=(timestamp const& right) const throw () {
  return (!operator==(right));
}

/**
 *  Compare if this is less than an object.
 *
 *  @param[in] right  The object to compare.
 *
 *  @return True if less, otherwise false.
 */
bool timestamp::operator<(timestamp const& right) const throw () {
  return (_secs < right._secs
          || (_secs == right._secs && _usecs < right._usecs));
}

/**
 *  Compare if this if less or equal than an object.
 *
 *  @param[in] right  The object to compare.
 *
 *  @return True if less or equal, otherwise false.
 */
bool timestamp::operator<=(timestamp const& right) const throw () {
  return (operator<(right) || operator==(right));
}

/**
 *  Compare if this if greater than an object.
 *
 *  @param[in] right  The object to compare.
 *
 *  @return True if greater, otherwise false.
 */
bool timestamp::operator>(timestamp const& right) const throw () {
  return (!operator<=(right));
}

/**
 *  Compare if this is greater or equal than an object.
 *
 *  @param[in] right  The object to compare.
 *
 *  @return True if greater or equal, otherwise false.
 */
bool timestamp::operator>=(timestamp const& right) const throw () {
  return (!operator<(right));
}

/**
 *  Add timestamp.
 *
 *  @param[in] right  The object to add.
 *
 *  @return The new timestamp.
 */
timestamp timestamp::operator+(timestamp const& right) const {
  timestamp ret(*this);
  ret += right;
  return (ret);
}

/**
 *  Substract timestamp.
 *
 *  @param[in] right  The object to substract.
 *
 *  @return The new timestamp.
 */
timestamp timestamp::operator-(timestamp const& right) const {
  timestamp ret(*this);
  ret -= right;
  return (ret);
}

/**
 *  Add timestamp.
 *
 *  @param[in] right  The object to add.
 *
 *  @return This object.
 */
timestamp& timestamp::operator+=(timestamp const& right) {
  add_seconds(right._secs);
  add_useconds(right._usecs);
  return (*this);
}

/**
 *  Substract timestamp.
 *
 *  @param[in] right  The object to substract.
 *
 *  @return This object.
 */
timestamp& timestamp::operator-=(timestamp const& right) {
  add_seconds(-right._secs);
  add_useconds(-static_cast<long>(right._usecs));
  return (*this);
}

/**
 *  Add milliseconds to this object.
 *
 *  @param[in] msecs  Time in milliseconds.
 */
void timestamp::add_mseconds(long msecs) {
  add_useconds(msecs * 1000);
  return ;
}

/**
 *  Add seconds to this object.
 *
 *  @param[in] secs  Time in seconds.
 */
void timestamp::add_seconds(time_t secs) {
  _secs += secs;
  return ;
}

/**
 *  Add microseconds to this object.
 *
 *  @param[in] usecs  Time in microseconds.
 */
void timestamp::add_useconds(long usecs) {
  long long us(_usecs);
  us += usecs;
  if (us < 0) {
    _secs += (us / 1000000); // Will be negative.
    us %= 1000000;
    if (us) { // Non zero means negative value.
      --_secs;
      us += 1000000;
    }
  }
  _usecs = static_cast<unsigned int>(us);
  _transfer(&_secs, &_usecs);
  return ;
}

/**
 *  Reset timestamp.
 */
void timestamp::clear() throw () {
  _secs = 0;
  _usecs = 0;
}

/**
 *  Get the maximum time.
 *
 *  @return Maximum time.
 */
timestamp timestamp::max_time() throw () {
  timestamp t;
  t._secs = std::numeric_limits<time_t>::max();
  t._usecs = 999999;
  return (t);
}

/**
 *  Get the minimum time.
 *
 *  @return Minimum time.
 */
timestamp timestamp::min_time() throw () {
  timestamp t;
  t._secs = std::numeric_limits<time_t>::min();
  t._usecs = 0;
  return (t);
}

/**
 *  Get the current system time.
 *
 *  @return The current timestamp.
 */
timestamp timestamp::now() throw () {
#ifdef _WIN32
  // Convert Epoch to FILETIME.
  SYSTEMTIME st_epoch;
  st_epoch.wYear = 1970;
  st_epoch.wMonth = 1;
  st_epoch.wDay = 1;
  st_epoch.wHour = 0;
  st_epoch.wMinute = 0;
  st_epoch.wSecond = 0;
  st_epoch.wMilliseconds = 0;
  FILETIME ft_epoch;
  SystemTimeToFileTime(&st_epoch, &ft_epoch);

  // Get current time as FILETIME.
  FILETIME ft_now;
  GetSystemTimeAsFileTime(&ft_now);

  // Move times to 64-bit integers.
  ULARGE_INTEGER large_epoch;
  ULARGE_INTEGER large_now;
  large_epoch.LowPart = ft_epoch.dwLowDateTime;
  large_epoch.HighPart = ft_epoch.dwHighDateTime;
  large_now.LowPart = ft_now.dwLowDateTime;
  large_now.HighPart = ft_now.dwHighDateTime;
  large_now.QuadPart -= large_epoch.QuadPart;
  // Time is now expressed in units of 100ns since Unix Epoch.
  return (timestamp(
            large_now.QuadPart / (10 * 1000000),
            (large_now.QuadPart % (10 * 1000000)) / 10));
#else
  timeval tv;
  gettimeofday(&tv, NULL);
  return (timestamp(tv.tv_sec, tv.tv_usec));
#endif // Windows or POSIX.
}

/**
 *  Substract milliseconds from this object.
 *
 *  @param[in] msecs  Time in milliseconds.
 */
void timestamp::sub_mseconds(long msecs) {
  add_mseconds(-msecs);
  return ;
}

/**
 *  Substract seconds from this object.
 *
 *  @param[in] secs  Time in seconds.
 */
void timestamp::sub_seconds(time_t secs) {
  add_seconds(-secs);
  return ;
}

/**
 *  Substract microseconds from this object.
 *
 *  @param[in] usecs  Time in microseconds.
 */
void timestamp::sub_useconds(long usecs) {
  add_useconds(-usecs);
  return ;
}

/**
 *  Get the time in milliseconds.
 *
 *  @return The time in milliseconds.
 */
long long timestamp::to_mseconds() const throw () {
  return (_secs * 1000ll + _usecs / 1000);
}

/**
 *  Get the time in seconds.
 *
 *  @return The time in seconds.
 */
time_t timestamp::to_seconds() const throw () {
  return (_secs);
}

/**
 *  Get the time in microseconds.
 *
 *  @return The time in microseconds.
 */
long long timestamp::to_useconds() const throw () {
  return (_secs * 1000000ll + _usecs);
}

/**
 *  Is this timestamp null (default initialized)?
 *
 *  @return  True if this timestamp is null.
 */
bool timestamp::is_null() const throw () {
  return (_secs == 0 && _usecs == 0);
}

/**
 *  Get an utc formatted string from a timestamp.
 *
 *  @return  The utc formatted string.
 */
std::string timestamp::to_utc() const {
  struct tm time;
  time_t t = to_seconds();
  ::gmtime_r(&t, &time);
  char buff[512];
  size_t ret = ::strftime(buff, 512, "Y-%m-%dT%h:%M:%SZ", &time);
  buff[ret] = '\0';
  return (std::string(buff));
}

/**
 *  Get a timestamp from a utc formatted string.
 *
 *  @param[in] utc  The utc formatted string.
 *
 *  @return         The timestamp, or a zero timestamp.
 */
timestamp timestamp::from_utc(std::string const& utc) {
  struct tm time;
  ::strptime(utc.c_str(), "%Y-%m-%dT%h:%M:%SZ", &time);
  time_t ts = ::mktime(&time);
  return (timestamp(ts));
}

/**
 *  Stream operator for timestamp.
 *
 *  @param[in] oss  The output stream.
 *  @param[in] ts   The timestamp.
 *
 *  @return         Reference to the output stream.
 */
std::ostream& com::centreon::operator<<(
                               std::ostream& oss,
                               timestamp const& ts) {
  oss << ts.to_seconds();
  return (oss);
}

/**
 *  Stream operator for timestamp.
 *
 *  @param[in] oss  The input stream.
 *  @param[in] ts   The timestamp.
 *
 *  @return         Reference to the input stream.
 */
std::istream& com::centreon::operator>>(
                               std::istream& iss,
                               timestamp& ts) {
  time_t tmp = 0;
  iss >> tmp;
  ts = timestamp(tmp);
  return (iss);
}

/**************************************
*                                     *
*           Private Methods           *
*                                     *
**************************************/

/**
 *  Internal copy.
 *
 *  @param[in] right  The object to copy.
 */
void timestamp::_internal_copy(timestamp const& right) {
  _usecs = right._usecs;
  _secs = right._secs;
  return ;
}

/**
 *  Transfer microseconds to seconds if possible.
 *  @remark This function is static.
 *
 *  @param[in,out] secs   The seconds.
 *  @param[in,out] usecs  The microseconds.
 */
void timestamp::_transfer(time_t* secs, unsigned int* usecs) {
  // Transforms unnecessary microseconds into seconds.
  *secs += (*usecs / 1000000);
  *usecs %= 1000000;
  return ;
}
