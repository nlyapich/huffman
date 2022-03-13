#include "huffman.hpp"

#define BUF_SIZE 4096
#define SIZE_CHAR 256
#define SIZE_BYTE 8

Huffman::Huffman(const std::string fileName) : fileName{fileName}{};
Huffman::~Huffman() = default;

std::ifstream::pos_type Huffman::getSize(const std::string& fn)
{
	std::ifstream ifs(fn, std::ifstream::ate);
	std::ifstream::pos_type size = ifs.tellg();
	ifs.close();
	return size;
};

std::vector<size_t> Huffman::getFrequency(std::ifstream& ifs)
{
	std::vector<size_t> frequency(SIZE_CHAR, 0);
	while (!ifs.eof())
	{
		char ch;
		ifs.read(&ch, 1);

		if (ifs.eof())
			break;

		frequency[static_cast<unsigned char>(ch)]++;
	}

	return frequency;
};

void Huffman::fillQueue(std::vector<size_t>& frequency, queue_t& queue)
{
	for (unsigned int i = 0; i < (frequency.size()); ++i)
	{
		if (frequency[i])
		{
			// Node::pointer node = std::make_shared<Node>(static_cast<unsigned char>(i), frequency[i]);
			Node::pointer node = new Node(static_cast<unsigned char>(i), frequency[i]);
			queue.push(node);
		}
	}
};

void Huffman::buildTree(queue_t& queue)
{
	while(queue.size() > 1)
	{
		Node::pointer x = queue.top();
		queue.pop();

		Node::pointer y = queue.top();
		queue.pop();

		Node::pointer z = new Node(0, x->getFrequency() + y->getFrequency());

		z->left = x;
		z->right = y;

		x->parent = z;
		y->parent = z;

		queue.push(z);
	}
};

void Huffman::makeCode(const Node::pointer& node, std::vector<std::string>& codes, std::string str)
{
	if (node->left)
		makeCode(node->left, codes, str + "0");

	if (node->right)
		makeCode(node->right, codes, str + "1");

	if (!node->left && !node->right)
	{
		// node->code(str);
		codes[node->getByte()] = str;
		// std::cout << "leaf: " << *node << " code: " << node->code() << std::endl;
	}
};

void Huffman::writeZipCode(std::ifstream& ifs, BitStream& bs, const std::vector<std::string>& codes)
{
  while (true)
  {
    char ch;
    ifs.read(&ch, 1);

    if(ifs.eof())
      break;

    for (char i : codes[static_cast<unsigned char>(ch)])
    {
      bs.setNextBit(i - '0');
    }
    // std::cout << codes[static_cast<unsigned char>(ch)] + '|';
  }
  // std::cout << std::endl;
};

void Huffman::writeTree(BitStream& bs, const Node::pointer& node)
{
	if (node->isLeaf())
	{
		bs.setNextBit(1);
		for (int i = CHAR_BIT - 1; i >= 0; --i)
		{
			bs.setNextBit((node->getByte() >> i) & 1);
		}
	}
	else
	{
		bs.setNextBit(0);
		if (node->left)
			writeTree(bs, node->left);
		if (node->right)
			writeTree(bs, node->right);
	}
};

unsigned int Huffman::getCountSymbols(const std::vector<size_t>& frequency) const
{
	unsigned int count = 0;
	for (auto i : frequency)
	{
		if (i)
			count++;
	}
	return count;
};

void Huffman::writeCountUniqueSymbols(BitStream& bs, const std::vector<size_t>& frequency) const
{
	bs << getCountSymbols(frequency);
};

void Huffman::writeMod(std::ofstream& ofs, unsigned char mod)
{
	ofs.seekp(0);
	ofs << static_cast<char>(mod); // возможно кастовать не надо
	//встать в начало файл и записать один байт: mod (не забыть поправить открытие файла в zip())
};

void Huffman::encodeFile(std::ifstream& ifs, std::ofstream& ofs, const std::vector<size_t>& frequency, const Node::pointer& root)
{
	BitStream bs{&ofs, BUF_SIZE};

	for (int i = 0; i < SIZE_BYTE; ++i)
	{
		bs.setNextBit(0);
	}

	writeCountUniqueSymbols(bs, frequency);
	writeTree(bs, root);

	std::vector<std::string> codes(SIZE_CHAR, "");
  makeCode(root, codes);

	writeZipCode(ifs, bs, codes);

	unsigned char mod = bs.getCountExtraBitsOfLastByte();
	for (unsigned char i = 0; i < mod; ++i)
	{
		bs.setNextBit(0);
	}
	bs.write();

	writeMod(ofs, mod);
};

void Huffman::zip()
{
  std::ifstream ifs(fileName, std::ifstream::binary);

  /*
    если размер файла сильно большой, int не потянет, будет переполнение;
    надо переделать обработку ошибок открытия файла
  */
  if (getSize(fileName) < 0 || !ifs)
	{
		throw std::ifstream::failure("Error with opening file: zip()");
	}

  std::vector<size_t> frequency = getFrequency(ifs);
  ifs.close();

	queue_t queue;
	fillQueue(frequency, queue);
  buildTree(queue);

  Node::pointer root = queue.top();
  queue.pop();

  ifs = std::ifstream(fileName, std::ifstream::binary);
	std::ofstream ofs(fileName + ".huf", std::ofstream::out | std::ofstream::binary);
	//std::ofstream::out | std::ofstream::in | std::ofstream::binary /* for adding new byte in middle of file */

	encodeFile(ifs, ofs, frequency, root);

	delete root;

  ifs.close();
	ofs.close();
};

unsigned char Huffman::readMod(BitStream& bs)
{
	char mod = 0;
	bs >> mod;
	return static_cast<unsigned char>(mod);
};

unsigned int Huffman::readCountUniqueSymbols(BitStream& bs)
{
	unsigned int countUniqueSymbols = 0;
	bs >> countUniqueSymbols;

	return countUniqueSymbols;
};

Node::pointer Huffman::writeNode(BitStream& bs)
{
	char tmp = 0;
	for (int i = 0; i < CHAR_BIT; ++i)
	{
		tmp = (tmp << 1) | bs.getNextBit();
	}
	Node::pointer node = new Node(static_cast<unsigned char>(tmp), 0);

	return node;
};

void Huffman::readTree(BitStream& bs, Node::pointer& cur, unsigned int* curCountUniqueSymbols)
{
	int curBit = bs.getNextBit();
	if (curBit)
	{
		Node::pointer newNode = writeNode(bs);
		*curCountUniqueSymbols -= 1;
		cur = newNode;
	}
	else
	{
		cur = new Node(0, 0);

		if (*curCountUniqueSymbols == 0) return;
		readTree(bs, cur->left, curCountUniqueSymbols);
		if (*curCountUniqueSymbols == 0) return;
		readTree(bs, cur->right, curCountUniqueSymbols);
	}
};
Node::pointer Huffman::readTree(BitStream& bs, unsigned int countUniqueSymbols)
{
	Node::pointer root = nullptr;
	readTree(bs, root, &countUniqueSymbols);
	return root;
};

Node::pointer Huffman::goToTree(Node::pointer& node, int status)
{
	if (status && node->right) return node->right;
	else if (!status && node->left) return node->left;
	else return node;
};

void Huffman::decodeFile(std::ofstream& ofs, const Node::pointer& root, unsigned char mod, BitStream& bs)
{
	Node::pointer curNode = root;

	/*
		may be must to add && mod != 0
	*/
	while(!(bs.isLastByte() && (bs.getNumberOfCurBit() == SIZE_BYTE - static_cast<unsigned int>(mod))))
	{
		int status;
		if ((status = bs.getNextBit()) == -1) break;

		curNode = goToTree(curNode, status);

		if (curNode->isLeaf())
		{
			/*
			тоже сделать буфер для вывода
			*/
			ofs << curNode->getByte();
			curNode = root;
		}
	}
};

void Huffman::unzip()
{
	std::ifstream ifs(fileName, std::ifstream::binary);

	/*
		сделать проверку на корректность открытия файла
	*/
	BitStream bs{&ifs, BUF_SIZE};
	bs.read();

	unsigned char mod = readMod(bs);

	unsigned int countUniqueSymbols = readCountUniqueSymbols(bs);
	Node::pointer root = readTree(bs, countUniqueSymbols);

	std::ofstream ofs("unzip" + fileName.substr(0, fileName.size() - std::string(".huf").size()), std::ofstream::out | std::ofstream::binary);

	decodeFile(ofs, root, mod, bs);

	delete root;

	ifs.close();
	ofs.close();
};
