// Copyright 2021 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef KNOWLEDGE_GRAPH_TERMINAL__TERMINAL_HPP_
#define KNOWLEDGE_GRAPH_TERMINAL__TERMINAL_HPP_

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"

#include "knowledge_graph_msgs/msg/edge.hpp"
#include "knowledge_graph_msgs/msg/graph.hpp"
#include "knowledge_graph_msgs/msg/graph_update.hpp"
#include "knowledge_graph_msgs/msg/node.hpp"

#include "knowledge_graph/graph_utils.hpp"
#include "knowledge_graph/knowledge_graph.hpp"

namespace knowledge_graph_terminal {

std::vector<std::string> tokenize(const std::string &text,
                                  const std::string delim = " ");
void pop_front(std::vector<std::string> &tokens);
char *completion_generator(const char *text, int state);
char **completer(const char *text, int start, int end);

class Terminal : public rclcpp::Node {
public:
  Terminal();

  virtual void run_console();

protected:
  virtual void clean_command(std::string &command);
  virtual void process_command(std::string &command, std::ostringstream &os);

  virtual void process_add(std::vector<std::string> &command,
                           std::ostringstream &os);
  virtual void process_add_node(std::vector<std::string> &command,
                                std::ostringstream &os);
  virtual void process_add_edge(std::vector<std::string> &command,
                                std::ostringstream &os);

  virtual void process_remove(std::vector<std::string> &command,
                              std::ostringstream &os);
  virtual void process_remove_node(std::vector<std::string> &command,
                                   std::ostringstream &os);
  virtual void process_remove_edge(std::vector<std::string> &command,
                                   std::ostringstream &os);

  virtual void process_get(std::vector<std::string> &command,
                           std::ostringstream &os);
  virtual void process_get_node(std::vector<std::string> &command,
                                std::ostringstream &os);
  virtual void process_get_edge(std::vector<std::string> &command,
                                std::ostringstream &os);
  virtual void process_get_nodes(std::vector<std::string> &command,
                                 std::ostringstream &os);
  virtual void process_get_edges(std::vector<std::string> &command,
                                 std::ostringstream &os);

  std::optional<knowledge_graph_msgs::msg::Edge>
  get_edge(const std::string &edge_class, const std::string &source,
           const std::string &target);

  void process_print(std::vector<std::string> &command, std::ostringstream &os);

private:
  std::shared_ptr<knowledge_graph::KnowledgeGraph> graph_;
};

} // namespace knowledge_graph_terminal

#endif