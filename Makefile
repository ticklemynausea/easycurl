all:
	cd entities; make; cd ..
	g++ -c -Wall easycurl.cpp -o easycurl.o
	
test: all
	g++ -Wall -lboost_regex -lcurl easycurl.o ./entities/entities.o test.cpp -o test
	
clean:
	cd entities; make clean; cd ..
	rm *.o
	rm test
