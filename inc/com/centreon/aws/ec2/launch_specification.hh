/*
** Copyright 2015 Centreon
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

#ifndef CC_AWS_EC2_LAUNCH_SPECIFICATION_HH
#  define CC_AWS_EC2_LAUNCH_SPECIFICATION_HH

#  include <memory>
#  include <string>
#  include <vector>
#  include "com/centreon/aws/ec2/network_interface.hh"
#  include "com/centreon/aws/ec2/block_device_mapping.hh"
#  include "com/centreon/aws/ec2/security_group.hh"
#  include "com/centreon/json/json_serializable.hh"
#  include "com/centreon/namespace.hh"

CC_BEGIN()

namespace aws {
  namespace ec2 {
    /**
     *  @class launch_specification launch_specification.hh "com/centreon/aws/ec2/launch_specification.hh"
     *  @brief aws ec2 launch specification structure wrapper.
     */
    class                    launch_specification : public json::json_serializable {
    public:
                             launch_specification();
                             launch_specification(
                               launch_specification const& other);
      virtual                ~launch_specification();
      launch_specification&  operator=(launch_specification const& other);

      std::string const&     get_image_id() const throw();
      std::string const&     get_key_name() const throw();
      std::vector<security_group> const&
                             get_security_groups() const throw();
      std::string const&     get_user_data() const throw();
      std::string const&     get_instance_type() const throw();
      std::string const&     get_placement_availability_zone() const throw();
      std::string const&     get_placement_group_name() const throw();
      std::string const&     get_kernel_id() const throw();
      std::string const&     get_ramdisk_id() const throw();
      std::vector<block_device_mapping> const&
                             get_block_device_mappings() const throw();
      std::string const&     get_subnet_id() const throw();
      std::vector<network_interface> const&
                             get_network_interfaces() const throw();
      std::string const&     get_iam_instance_profile_arn() const throw();
      std::string const&     get_iam_instance_profile_name() const throw();
      bool                   get_ebs_optimized() const throw();
      bool                   get_monitoring_enabled() const throw();

      void                   set_image_id(std::string const& val);
      void                   set_key_name(std::string const& val);
      void                   add_security_groups(security_group const& val);
      void                   add_security_group_ids(security_group const& val);
      void                   set_user_data(std::string const& val);
      void                   set_instance_type(std::string const& val);
      void                   set_placement_availability_zone(std::string const& val);
      void                   set_placement_group_name(std::string const& val);
      void                   set_kernel_id(std::string const& val);
      void                   set_ramdisk_id(std::string const& val);
      void                   add_block_device_mappings(block_device_mapping const& val);
      void                   set_subnet_id(std::string const& val);
      void                   add_network_interfaces(network_interface const& val);
      void                   set_iam_instance_profile_arn(std::string const& val);
      void                   set_iam_instance_profile_name(std::string const& val);
      void                   set_ebs_optimized(bool val);
      void                   set_monitoring_enabled(bool val);

    private:
      std::string            _image_id;
      std::string            _key_name;

      std::vector<security_group>
                             _security_groups;
      std::vector<security_group>
                             _security_group_ids;

      std::string            _user_data;
      std::string            _instance_type;
      std::string            _placement_availability_zone;
      std::string            _placement_group_name;
      std::string            _kernel_id;
      std::string            _ramdisk_id;
      std::vector<block_device_mapping>
                             _block_device_mappings;
      std::string            _subnet_id;
      std::vector<network_interface>
                             _network_interfaces;
      std::string            _iam_instance_profile_arn;
      std::string            _iam_instance_profile_name;
      bool                   _ebs_optimized;
      bool                   _monitoring_enabled;

      void                   _init_bindings();
      void                   _internal_copy(launch_specification const& other);
    };
  } // namespace ec2
} // namespace aws

CC_END()

#endif // !CC_AWS_EC2_LAUNCH_SPECIFICATION_HH
