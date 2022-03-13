#include <boost/program_options.hpp>
#include <iostream>

#include "huffman.hpp"

namespace opt = boost::program_options;

int main(int argc, char *argv[])
{
	opt::options_description desc("All options");

	desc.add_options()
		("compress,c", opt::value<std::string>(), "what is the name of file to compress")
		("decompress,d", opt::value<std::string>(), "what is the name of .huf file to decompress")
		("help,h", "produce help message")
	;

	opt::variables_map vm;
	opt::store(opt::parse_command_line(argc, argv, desc), vm);
	opt::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;

		return 0;
	}
	if (vm.count("compress"))
	{
		std::cout << "compress: " << vm["compress"].as<std::string>() << std::endl;
		Huffman huffmanZip{vm["compress"].as<std::string>()};
		huffmanZip.zip();

		return 0;
	}
	if (vm.count("decompress"))
	{
		std::cout << "decompress: " << vm["decompress"].as<std::string>() << std::endl;
		Huffman huffmanUnzip{vm["decompress"].as<std::string>()};
		huffmanUnzip.unzip();

		return 0;
	}

	return 0;
}
