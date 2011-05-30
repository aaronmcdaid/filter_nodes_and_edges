CC=g++
PROFILE= -O3 #-ggdb -pg #-DNDEBUG # http://linux.die.net/man/1/gcc
CFLAGS=   \
          -Wmissing-field-initializers   \
          -Wsign-compare   \
          -Wunused-parameter    \
          -Wunused             \
          -Wnon-virtual-dtor \
          -Wall -Wformat -Werror ${PROFILE} -Wextra -Wconversion
CXXFLAGS= ${CFLAGS}

filter_nodes_and_edges: filter_nodes_and_edges.o cmdline.o graph/loading.o graph/network.o graph/graph.o graph/weights.o graph/bloom.o

cmdline.c.FORCE:      
	# remake cmdline.c . But it's OK unless you change the .ggo file. You'll need gengetopt(1) to be able to run this.
	gengetopt  --unamed-opts < cmdline.ggo
cmdline.o: cmdline.c
	gcc cmdline.c -o cmdline.o -c
