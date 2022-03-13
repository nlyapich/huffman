#ifndef BITSTREAM_HPP
#define BITSTREAM_HPP

#include <algorithm>
#include <climits>
#include <fstream>
#include <stdexcept>

#define DEFAULT_BITSREAM_SIZE_BYTES 128

class BitStream
{
public:
  BitStream(std::ofstream* ofs, size_t countBytes = DEFAULT_BITSREAM_SIZE_BYTES);
  BitStream(std::ifstream* ifs, size_t countBytes = DEFAULT_BITSREAM_SIZE_BYTES);
  virtual ~BitStream();

  void clear();
  void write();
  size_t getCurSizeBytes() const;
  void setNextBit(int value);
  unsigned char getCountExtraBitsOfLastByte();

  void read();
  int getNextBit();
  bool isLastByte();
	unsigned int getNumberOfCurBit();

  friend BitStream& operator<<(BitStream& bs, char ch);
  friend BitStream& operator<<(BitStream& bs, const char* str);
  friend BitStream& operator<<(BitStream& bs, const std::string& str);

  friend BitStream& operator<<(BitStream& bs, int n);
  friend BitStream& operator<<(BitStream& bs, unsigned int n);

  friend std::ostream& operator<<(std::ostream& os, const BitStream& bs);

  friend BitStream& operator>>(BitStream& bs, char& ch);
  friend BitStream& operator>>(BitStream& bs, int& n);
  friend BitStream& operator>>(BitStream& bs, unsigned int& n);
private:
  std::ofstream* ofs{nullptr};
  std::ifstream* ifs{nullptr};
  size_t maxSizeBytes;
  char* bitstream;
  size_t curByte{0};
  int curBit{0};
  int modEofSize;
};

BitStream& operator<<(BitStream& bs, char ch);
BitStream& operator<<(BitStream& bs, const char* str);
BitStream& operator<<(BitStream& bs, const std::string& str);

BitStream& operator<<(BitStream& bs, int n);
BitStream& operator<<(BitStream& bs, unsigned int n);

std::ostream& operator<<(std::ostream& os, const BitStream& bs);

BitStream& operator>>(BitStream& bs, char& ch);
BitStream& operator>>(BitStream& bs, int& n);
BitStream& operator>>(BitStream& bs, unsigned int& n);

#endif // BITSTREAM_HPP
