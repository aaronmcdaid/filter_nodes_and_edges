#include "cmdline.h"
#include <iostream>
#include <cstdlib>
#include <memory>
#include "pp.hpp"
// #include "graph/network.hpp"
#include "graph/loading.hpp"

using namespace std;

int main(int argc, char **argv) {
	gengetopt_args_info args_info;

	// there shouldn't be any errors in processing args
	if (cmdline_parser (argc, argv, &args_info) != 0)
		exit(1) ;
	// .. and there should be exactly one non-option arg
	if(args_info.inputs_num != 1) {
		cmdline_parser_print_help();
		exit(1);
	}

	const char * edgeListFileName   = args_info.inputs[0];
	PP(edgeListFileName);

        std :: auto_ptr<graph :: NetworkInterfaceConvertedToString > network;
	if(args_info.stringIDs_flag) {
		network	= graph :: loading :: make_Network_from_edge_list_string(edgeListFileName, 0, 0);
	} else {
		network	= graph :: loading :: make_Network_from_edge_list_int64(edgeListFileName, 0, 0);
	}
	PP2(network->numNodes(), network->numRels());
}
