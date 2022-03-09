#include "node.hpp"

Node::Node() = default;
Node::Node(unsigned char uch, int f) : uch{uch}, frequency{f} {};

Node::~Node() = default;

bool Node::isLeaf() const
{
  if (!left && !right)
    return true;

  return false;
};

int Node::getFrequency() const
{
  return frequency;
};

unsigned char Node::getByte() const
{
  return uch;
};

bool Node::operator<(const Node& oth) const
{
  return frequency < oth.frequency;
};

std::ostream& operator<<(std::ostream& os, const Node& node)
{
  return os << "[" << node.uch << "] = " << node.frequency;
};

bool LowestPriority::operator()(const Node& left, const Node& right) const
{
  return left.getFrequency() > right.getFrequency();
};
bool LowestPriority::operator()(const Node::pointer& left, const Node::pointer& right) const
{
  return left->getFrequency() > right->getFrequency();
};
