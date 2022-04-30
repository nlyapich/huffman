# Huffman Archiver

![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white)

### Description
Archiver for `.txt` files based on Huffman coding. It works well for text files if file size is greater than 1000 bytes. The compression reaches 50% for big files.

# Features
- [How to start](#how-to-start)
- [How to use without GUI](#how-to-use-without-gui)
  - [Compress](#compress)
  - [Decompress](#decompress)
  - [Help](#help)
- [Using with GUI](#using-with-gui)
- [Runnig the tests](#running-the-tests)
- [Built with](#built-with)
- [Build system](#build-system)
- [More information about Huffman's algorithm](#more-information-about-huffman's-algorithm)
- [License](#license)

# How to start
```
$ git clone https://github.com/nlyapich/huffman.git
$ cd ./huffman
$ bash install.sh
$ cd ./build
$ ./Huffman
```

# How to use without GUI
***Compress:***
```
$ ./Huffman --compress="filename.txt"
```
***Decompress:***
```
$ ./Huffman --decompress="filename.huf"
```
***Help:***
```
$ ./Huffman --help
```

# Using with GUI
```
$ ./Huffman
```
![Mainwindow](/images/screenshot_mainwindow.png)

# Running the tests
If you have *`GoogleTest` framework*, you can install this project along with tests and run them:
```
$ bash install.sh -t
$ cd ./build
$ ctest
```
Otherwise, if you don't have this framework, you can install it:
```
$ sudo apt-get install libgtest-dev
$ cd /usr/src/googletest/googletest
$ sudo mkdir build
$ cd build
$ sudo cmake ..
$ sudo make
$ sudo cp libgtest* /usr/lib/
$ cd ..
$ sudo rm -rf build
```
```
$ sudo mkdir /usr/local/lib/googletest
$ sudo ln -s /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
$ sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a
```

### Built with
  * [Boost](https://www.boost.org/)
  * [GoogleTest](https://google.github.io/googletest/)
  * [Qt5](https://doc.qt.io/qt-5/index.html)

### Build system
  * [CMake](https://cmake.org/)

### More information about Huffman's algorithm
* [Wikipedia](https://en.wikipedia.org/wiki/Huffman_coding)

#### License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
