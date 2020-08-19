WARNING = -W -Wall
CC = g++ -std=c++11

CFLAGS  = -g -O2 $(WARNING) $(LCFLAGS)

SRCS = $(foreach dir, $(SUBDIRS), $(wildcard $(dir)/*.cpp))
CPLF = $(foreach dir, $(SUBDIRS), $(wildcard $(dir)/*.o))

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

os:$(OBJS)
	$(CC) -g $(OBJS) -o $@ $(CFLAGS)

%.o:%.cpp
	$(CC) -c -g $< -o $@ $(CFLAGS)

clean:
	rm -rf os *.bin *.exe $(CPLF)
