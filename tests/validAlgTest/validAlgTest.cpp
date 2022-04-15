#include <algorithm>
#include <boost/filesystem.hpp>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

#include "./../../src/huffman.hpp"

#define SIZE_BUF 2048

std::streampos getSizeFile(const std::string& fileName)
{
  std::fstream file(fileName);
  file.seekp(0, std::ios::end);
  std::streampos size = file.tellg();
  file.close();

  return size;
}

bool lessSizeFile(const std::string& firstFileName, const std::string& secondFileName)
{
  auto firstSize = getSizeFile(firstFileName);
  auto secondSize = getSizeFile(secondFileName);

  return firstSize < secondSize;
}

bool compareDataFiles(const std::string& firstFileName, const std::string& secondFileName)
{

  std::ifstream file1(firstFileName);
  char buffer1[SIZE_BUF + 1];
  std::fill(buffer1, buffer1 + SIZE_BUF, '\0' /* this is faster then 0 */);

  std::ifstream file2(secondFileName);
  char buffer2[SIZE_BUF + 1];
  std::fill(buffer2, buffer2 + SIZE_BUF, '\0' /* this is faster then 0 */);

  bool status = true;
  while(!file1.eof() && !file2.eof())
  {
    file1.read(buffer1, SIZE_BUF - 1);
    file2.read(buffer2, SIZE_BUF - 1);

    if (std::strcmp(buffer1, buffer2) != 0)
    {
      status = false;
      break;
    }
  }
  status = status && file1.eof() && file2.eof();

  file1.close();
  file2.close();

  if (status) return true;

  return false;
}

TEST(ValidAlgTest, dataLossCheckTest)
{
  auto zipUnzipData = [](const std::string& fileName, const std::string& filePath)
  {
    const std::string copyFile = filePath + "copy" + fileName;
    boost::filesystem::copy_file(
        filePath + fileName,
        copyFile
    );

    Huffman huffmanZip(copyFile);
    huffmanZip.zip();

    Huffman huffmanUnzip(copyFile + ".huf");
    huffmanUnzip.unzip();

    EXPECT_TRUE(lessSizeFile(copyFile + ".huf", filePath + fileName));
    EXPECT_TRUE(compareDataFiles(copyFile, filePath + fileName));

    remove((copyFile + ".huf").c_str());
    remove((copyFile).c_str());
  };

  const std::string pathTestFiles("./testTextFiles/");
  const std::vector<std::string> dataList = {
    "text1.txt",
    "text2.txt",
    "text3.txt",
    "text4.txt"
  };

  for(auto& fileName : dataList)
  {
    zipUnzipData(fileName, pathTestFiles);
  }
}
