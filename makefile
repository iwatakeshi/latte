# LIB=-L/usr/informix/lib/c++
INC=./buckaroo/github/iwatakeshi/to_string/
INC_PARAMS=$(foreach d, $(INC), -I$d)

all:	main.cpp
	# @echo $(INC_PARAMS)
	g++ -g -std=c++17 $(INC_PARAMS) main.cpp

clean:
	rm -r a.out