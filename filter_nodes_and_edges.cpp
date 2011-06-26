#include "cmdline.h"
#include "pp.hpp"
#include "graph/network.hpp"
#include "graph/loading.hpp"
#include "graph/stats.hpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
	gengetopt_args_info args_info;

	// there shouldn't be any errors in processing args
	if (cmdline_parser (argc, argv, &args_info) != 0)
		exit(1) ;
	// .. and there should be exactly one non-option arg
	if(args_info.inputs_num != 2) {
		cmdline_parser_print_help();
		exit(1);
	}

	const char * edgeListFileName   = args_info.inputs[0];
	const char * output_file_name   = args_info.inputs[1];
	const bool flag_skiploops = args_info.skip_self_loops_flag;
	PP2(edgeListFileName, output_file_name);

        std :: auto_ptr<graph :: NetworkInterfaceConvertedToString > network;
	if(args_info.stringIDs_flag) {
		network	= graph :: loading :: make_Network_from_edge_list_string(edgeListFileName, 0, 0, flag_skiploops);
	} else {
		network	= graph :: loading :: make_Network_from_edge_list_int64(edgeListFileName, 0, 0, flag_skiploops, 0);
	}
	PP2(network->numNodes(), network->numRels());
	const graph :: VerySimpleGraphInterface * const vsg = network->get_plain_graph();

	const int32_t max_degree_in_input = graph :: stats :: get_max_degree(vsg);
	const int32_t max_allowed_degree = args_info.max_degree_arg == -1 ? max_degree_in_input : args_info.max_degree_arg;
	PP2(max_degree_in_input, max_allowed_degree);
	assert(max_allowed_degree >= 0);

	ofstream f(output_file_name);
	assert(f.good());

	for(int r = 0; r < network->numRels(); r++) {
		const pair<int32_t, int32_t> eps = vsg->EndPoints(r);
		const int32_t node_id_1 = eps.first;
		const int32_t node_id_2 = eps.second;
		const int32_t degree_1 = vsg->degree(node_id_1);
		const int32_t degree_2 = vsg->degree(node_id_2);
		if(degree_1 <= max_allowed_degree && degree_2 <= max_allowed_degree) {
			if(args_info.renumber_flag) {
				f << node_id_1 << "\t" << node_id_2 << endl;
			} else {
				const string name_1 = network->node_name_as_string(node_id_1);
				const string name_2 = network->node_name_as_string(node_id_2);
				f << name_1 << "\t" << name_2 << endl;
			}
		}
	}

	f.close();
}
