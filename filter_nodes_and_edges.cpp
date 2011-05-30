#include "cmdline.h"
#include <iostream>
#include <cstdlib>
#include "pp.hpp"

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
	cout << "filter_nodes_and_edges: nothing implemented yet" << endl;
	PP(edgeListFileName);
}
