#include "bitstream.hpp"

BitStream::BitStream(std::ofstream* ofs, size_t countBytes): ofs{ofs}, maxSizeBytes{countBytes}
{
  if (!countBytes)
    throw std::invalid_argument("BitStream::BitStream()");

  bitstream = new char[countBytes]{0};
};

BitStream::BitStream(std::ifstream* ifs, size_t countBytes): ifs{ifs}, maxSizeBytes{countBytes}
{
  if (!countBytes)
    throw std::invalid_argument("BitStream::BitStream()");

  bitstream = new char[countBytes]{0};

  int curPos = ifs->tellg();
  ifs->seekg(0, std::ios_base::end);
  modEofSize = (static_cast<int>(ifs->tellg()) - curPos) % maxSizeBytes;
  ifs->seekg(curPos, std::ios_base::beg);
};

BitStream::~BitStream()
{
  delete[] bitstream;
};

void BitStream::clear()
{
    std::fill(bitstream, bitstream + curByte + (curBit ? 1 : 0), '\0' /* this is faster then 0 */);
    curByte = 0;
    curBit = 0;
};

void BitStream::write()
{
  if (!ofs)
    throw std::logic_error("Can't write to std::ofstream: BitStream::write()");

  *ofs << *this;
};
void BitStream::read()
{
  if (!ifs)
    throw std::logic_error("Can't read from std::ifstream: BitStream::read()");

  ifs->read(bitstream, maxSizeBytes);

  if (ifs->eof())
  {
    maxSizeBytes = static_cast<size_t>(modEofSize);
  }
};

int BitStream::getNextBit()
{
  if (curBit == CHAR_BIT)
  {
    curBit = 0;
    curByte++;
  }

  if (curByte == maxSizeBytes)
  {
    if (ifs->eof()) return -1;
    clear();
    read();
  }

  int nextBit = (bitstream[curByte] & (1 << (CHAR_BIT - curBit - 1))) ? 1 : 0;
  curBit++;

  return nextBit;
};

size_t BitStream::getCurSizeBytes() const
{
  return curByte + (curBit ? 1 : 0);
};

void BitStream::setNextBit(int value)
{
  if (curBit == CHAR_BIT)
  {
    curBit = 0;
    curByte++;
  }
  if (curByte == maxSizeBytes)
  {
    write();
    clear();
  }

  bitstream[curByte] = bitstream[curByte] | ((value ? 1 : 0) << (CHAR_BIT - curBit - 1));
  curBit++;
};

unsigned char BitStream::getCountExtraBitsOfLastByte()
{
  return (CHAR_BIT - curBit) % CHAR_BIT;
};

BitStream& operator<<(BitStream& bs, char ch)
{
  for (int i = 0; i < CHAR_BIT; ++i)
  {
    int nextBit = (ch >> (CHAR_BIT - i - 1)) & 1;
    bs.setNextBit(nextBit);
  }
  return bs;
};

bool BitStream::isLastByte()
{
  if (!ifs)
    throw std::invalid_argument("input stream is not defined");
  return (ifs->eof() && curByte + 1 == maxSizeBytes);
};

unsigned int BitStream::getNumberOfCurBit()
{
    return curBit;
};

BitStream& operator<<(BitStream& bs, const char* str)
{
  if (!str)
    return bs;

  while (*str != '\0')
  {
    bs << *str;
    str++;
  }

  return bs;
};

BitStream& operator<<(BitStream& bs, const std::string& str)
{
  const char* char_str = str.c_str();

  bs << char_str;

  return bs;
};
BitStream& operator<<(BitStream& bs, int n)
{
  char* tmp = reinterpret_cast<char*>(&n);
  for (size_t i = 0; i < sizeof(int); ++i)
  {
    bs << *(tmp + i);
  }
  return bs;
};
BitStream& operator<<(BitStream& bs, unsigned int n)
{
  return bs << static_cast<int>(n);
};

std::ostream& operator<<(std::ostream& os, const BitStream& bs)
{
  os.write(bs.bitstream, bs.curByte + (bs.curBit ? 1 : 0));
  return os;
};

BitStream& operator>>(BitStream& bs, char& ch)
{
  for (int i = 0; i < CHAR_BIT; ++i)
  {
    ch = ch | ((bs.getNextBit() ? 1 : 0) << (CHAR_BIT - i - 1));
  }
  return bs;
};

BitStream& operator>>(BitStream& bs, int& n)
{
  char* tmp = reinterpret_cast<char*>(&n);
  for (size_t i = 0; i < sizeof(int); ++i)
  {
    bs >> *(tmp + i);
  }

  n = *(reinterpret_cast<int*>(tmp));

  return bs;
};

BitStream& operator>>(BitStream& bs, unsigned int& n)
{
  int tmp = static_cast<int>(n);
  bs >> tmp;
  n = tmp;

  return bs;
};
