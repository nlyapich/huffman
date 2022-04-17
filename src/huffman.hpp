#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

#include "bitstream.hpp"
#include "node.hpp"

using queue_t = std::priority_queue<Node::pointer, std::vector<Node::pointer>, LowestPriority>;

class InterfaceProgressBar
{
public:
  virtual ~InterfaceProgressBar(){};

  virtual void setValue(int) = 0;
};

class Huffman
{
public:
  Huffman(std::string filePath);
  virtual ~Huffman();

  void zip(InterfaceProgressBar* progressBar = nullptr);
  void unzip(InterfaceProgressBar* progressBar = nullptr);
private:
  const std::string filePath;

  std::ifstream::pos_type getSize(const std::string& fn);

  std::vector<size_t> getFrequency(std::ifstream& ifs);
  void fillQueue(std::vector<size_t>& frequency, queue_t& queue);
  void buildTree(queue_t& queue);
  void makeCode(const Node::pointer& node, std::vector<std::string>& codes, std::string str = "");

  unsigned int getCountSymbols(const std::vector<size_t>& frequency) const;
  void writeCountUniqueSymbols(BitStream& bs, const std::vector<size_t>& frequency) const;
  void writeZipCode(std::ifstream& ifs, BitStream& bs, const std::vector<std::string>& codes);
  void writeTree(BitStream& bs, const Node::pointer& node);
  void writeMod(std::ofstream& ofs, unsigned char mod);
  void encodeFile(std::ifstream& ifs, std::ofstream& ofs, const std::vector<size_t>& frequency, const Node::pointer& root);

  unsigned char readMod(BitStream& bs);
  unsigned int readCountUniqueSymbols(BitStream& bs);
  Node::pointer writeNode(BitStream& bs);
  void readTree(BitStream& bs, Node::pointer& cur, unsigned int* curCountUniqueSymbols);
  Node::pointer readTree(BitStream& bs, unsigned int countUniqueSymbols);
  Node::pointer goToTree(Node::pointer& node, int status);
  void decodeFile(std::ofstream& ofs, const Node::pointer& root, unsigned char mod, BitStream& bs);
};

#endif // HUFFMAN_HPP
