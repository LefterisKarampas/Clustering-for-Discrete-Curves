CC = g++
OUT = cluster
FLAG = -g -Wall 

FILES = src/main.cpp src/main_functions.cpp src/Curve.cpp src/Distance.cpp src/Curve_Info.cpp src/Grid.cpp \
src/generator.cpp src/Node.cpp src/List.cpp src/HashTable.cpp src/HashFunctions.cpp src/LSH_Curve.cpp \
src/Cluster.cpp src/Initialization.cpp src/Assignment.cpp src/Update.cpp 

OBJECTS = objects/main.o objects/main_functions.o objects/Curve.o objects/Distance.o objects/Curve_Info.o \
objects/Grid.o objects/generator.o objects/Node.o objects/List.o objects/HashTable.o objects/HashFunctions.o \
objects/LSH_Curve.o objects/Cluster.o objects/Initialization.o objects/Assignment.o objects/Update.o 


all:
	for i in $(FILES); do \
		$(CC) $(FLAG) -c $$i;  \
	done
	mkdir -p objects
	mv *.o objects
	$(CC) $(FLAG) -o $(OUT) $(OBJECTS)
clean:
	rm -rf objects/ $(OUT)