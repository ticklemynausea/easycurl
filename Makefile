all:
	cd entities; make; cd ..
	g++ -c -Wall easycurl.cpp -o easycurl.o
	g++ -c -Wall stripper.cpp -o stripper.o
	
test: all
	g++ -Wall -lboost_regex -lcurl stripper.o easycurl.o ./entities/entities.o test.cpp -o test
	
clean:
	cd entities; make clean; cd ..
	rm *.o
	rm test
