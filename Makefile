EXE = helloworld
GCC = g++
SUBDIR = src 
CPP_SOURCES = $(foreach dir, $(SUBDIR), $(wildcard $(dir)/*.cpp))
CPP_OBJECTS = $(patsubst %.cpp, %.o, $(CPP_SOURCES))
DEP_FILES = $(patsubst %.o, %.d, $(CPP_OBJECTS))
$(EXE): $(CPP_OBJECTS)
	$(GCC) $(CPP_OBJECTS) -o $@
%.o: %.cpp
	$(GCC) -c -MMD $< -o $@
-include $(DEP_FILES)
clean:
	rm $(CPP_OBJECTS) $(EXE) $(DEP_FILES)
