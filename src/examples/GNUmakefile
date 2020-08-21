

PROGS			= \
			  example-ipset \
			  example-nfqueue

CFLAGS			= -Wall -Werror
LDFLAGS			= 
CC			= gcc


.PHONY: all clean


all: $(PROGS)


example-ipset: example-ipset.o
	$(CC) $(LDFLAGS) -lmnl -lipset -o $(@) $(^)


example-nfqueue: example-nfqueue.o
	$(CC) $(LDFLAGS) -lnetfilter_queue -o $(@) $(^)


clean:
	rm -f *.o $(PROGS)


# end of makefile
