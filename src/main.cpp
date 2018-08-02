#include <iostream>
#include "node.h"

using namespace std;

int main()
{
    auto my_node = node::node_factory_Sendmmsg();
    my_node->run();
    return 0;
}
