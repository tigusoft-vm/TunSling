#include <iostream>
#include "node.h"
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

int main(int argc, char *argv[])
{
	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("address", po::value<std::string>(), "Address")
		("threds", po::value<int>(), "Number threds")
	;
	
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    
	
	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}
	
	if (vm.count("compression")) {
		cout << "Compression level was set to " 
	 << vm["compression"].as<int>() << ".\n";
	} else {
		cout << "Compression level was not set.\n";
	}
	
    auto my_node = node::node_factory_Sendmmsg();
    my_node->run();
    return 0;
}
