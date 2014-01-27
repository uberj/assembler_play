CXX=g++
OPTS=-g3
OUT=run
CXXFLAGS=
SEQ_FILE="data/Brucella_suis_1330/closure.seq"

all: run
	echo "Done!"

build:
	$(CXX) $(CXXFLAGS) $(OPTS) main.cpp -o $(OUT)

run: build
	./$(OUT) $(SEQ_FILE)

debug: clean build
	gdb

clean:
	rm -f $(OUT)
