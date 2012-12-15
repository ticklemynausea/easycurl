all:
	cd entities; make; cd ..
	g++ -Wall -lboost_regex -lcurl ./entities/entities.o easycurl.cpp test.cpp -o easycurl
	
clean:
	cd entities; make clean; cd ..
	rm easycurl
