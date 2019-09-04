/*
 * Copyright 2015 Fadri Furrer, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Michael Burri, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Mina Kamel, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Janosch Nikolic, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Markus Achtelik, ASL, ETH Zurich, Switzerland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef magicc_sim_PLUGINS_RANGE_PLUGIN_H
#define magicc_sim_PLUGINS_RANGE_PLUGIN_H

#include <random>

#include <Eigen/Core>
#include <gazebo/common/common.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <ros/callback_queue.h>
#include <ros/ros.h>
#include <sensor_msgs/Range.h>
#include <std_msgs/Float32.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <stdio.h>

#include <boost/bind.hpp>

#include "magicc_sim_plugins/common.h"

namespace gazebo {

class GazeboAltimeterPlugin : public ModelPlugin {
 public:

  GazeboAltimeterPlugin();
  ~GazeboAltimeterPlugin();

 protected:
  void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
  void OnUpdate(const common::UpdateInfo&);

 private:
  // Ros Stuff
  std::string namespace_;
  ros::NodeHandle* node_handle_;
  ros::Publisher alt_pub_;

  // Topic
  std::string alt_topic_;

  // params
  double min_range_;
  double max_range_;
  double error_stdev_;
  double field_of_view_;
  double pub_rate_;
  bool alt_noise_on_;
  bool publish_float_;

  // Random Engine
  std::default_random_engine random_generator_;
  std::normal_distribution<double> standard_normal_distribution_;

  // Gazebo Information
  std::string frame_id_;
  std::string link_name_;
  physics::WorldPtr world_;
  physics::ModelPtr model_;
  physics::LinkPtr link_;
  event::ConnectionPtr updateConnection_;
  common::Time last_time_;

  // Memory
  sensor_msgs::Range alt_message_;
};
}

#endif // magicc_sim_PLUGINS_RANGE_PLUGIN_H
