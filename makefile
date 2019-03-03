# LIB=-L/usr/informix/lib/c++
BUCKAROO_PATH= ./buckaroo/github/iwatakeshi
INC=$(BUCKAROO_PATH)/to_string/ $(BUCKAROO_PATH)/bench/
INC_PARAMS=$(foreach d, $(INC), -I$d)

all:	main.cpp
	# @echo $(INC_PARAMS)
	g++ -g -std=c++17 $(INC_PARAMS) main.cpp 

clean:
	rm -r a.out