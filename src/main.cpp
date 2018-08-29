#include <iostream>
#include "cNode_factory.h"
#include <boost/program_options.hpp>
#include <sodium.h> // TODO

using namespace std;
namespace po = boost::program_options;

int main(int argc, char *argv[])
{
	if (sodium_init() == -1) throw std::runtime_error("sodium_init error"); // TODO move this into crypto classes
	try {
		// Declare the supported options.
		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "Produce help message")
			("address", po::value<std::string>()->required(), "Address (required)")
			("threads", po::value<int>()->default_value(0), "Number threads for crypto and send UDP, if 0 then disable threadpool")
			("UDP", po::value<std::string>()->required(), "UDP type (Asio, Sendmmsg, Empty) (required)")
			("crypto", po::value<std::string>()->required(), "Crypto type (Secretbox, X_salsa_20, Empty) (required)")
			("tun", po::value<std::string>()->required(), "Tun type (LinuxNormal, LinuxWeld) (required)")
			("tunMtu", po::value<int>()->required(), "MTU size to set on our Tun (typial 9000, 8972, 1500, 1472) (required)")
			("tunAddr", po::value<std::string>()->default_value("fd44"), "First two bytes to tun addres in hex (default: fd44)")
			("tunMultiThread", po::value<int>()->implicit_value(2), "Number threads for tun (if not set then is 1 thread)")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		
		if (vm.count("help")) {
			cout << desc << "\n";
			return 0;
		}
		
		po::notify(vm);

		if (vm.count("threads") && !vm["threads"].defaulted() 
			&& vm.count("tunMultiThread"))
			throw logic_error(string("Conflicting options '") 
							  + "threads" + "' and '" + "tunMultiThread" + "'.");
		
		cNode_factory factory;
		auto my_node = factory.create_node( vm );
		my_node->run();
	} catch (std::exception &e) {
		std::cout << e.what() << "\n";
	} catch ( ... ) {
		std::cout << "Uknown error." << "\n";
	}
			
    return 0;
}
