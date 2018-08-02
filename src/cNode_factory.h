#ifndef CNODE_FACTORY_H
#define CNODE_FACTORY_H

#include "node.h"
#include <boost/program_options.hpp>

class cNode_factory
{
public:
	cNode_factory() = default;
	
	std::unique_ptr<node> create_node( const boost::program_options::variables_map & vm );
};

#endif // CNODE_FACTORY_H
