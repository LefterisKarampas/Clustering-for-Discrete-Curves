CC = g++
OUT = cluster
FLAG = -g -Wall 
FILES = src/main.cpp src/main_functions.cpp src/Curve.cpp src/Distance.cpp src/Curve_Info.cpp
OBJECTS = objects/main.o objects/main_functions.o objects/Curve.o objects/Distance.o objects/Curve_Info.o

all:
	for i in $(FILES); do \
		$(CC) $(FLAG) -c $$i;  \
	done
	mkdir -p objects
	mv *.o objects
	$(CC) $(FLAG) -o $(OUT) $(OBJECTS)
clean:
	rm -rf objects/ $(OUT)