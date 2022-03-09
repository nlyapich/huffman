#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <memory>
#include <string>

class Node
{
public:
  using pointer = std::shared_ptr<Node>;

  pointer left{nullptr};
  pointer right{nullptr};
  pointer parent{nullptr};

  Node();
  Node(unsigned char uch, int f);
  virtual ~Node();

  bool isLeaf() const;
  int getFrequency() const;
  unsigned char getByte() const;

  bool operator<(const Node& oth) const;

  friend std::ostream& operator<<(std::ostream& os, const Node& node);
private:
  unsigned char uch{0};
  int frequency{0};
};

std::ostream& operator<<(std::ostream& os, const Node& node);

class LowestPriority
{
public:
  bool operator()(const Node& left, const Node& right) const;
  bool operator()(const Node::pointer& left, const Node::pointer& right) const;
};

#endif // NODE_HPP
