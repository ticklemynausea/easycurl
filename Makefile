all:
	cd entities; make; cd ..
	g++ -c -Wall easycurl.cpp -o easycurl.o
	g++ -c -Wall stripper.cpp -o stripper.o
	g++ -lboost_regex -lcurl -shared easycurl.o stripper.o entities/entities.o -o libeasycurl.so

test: all
	g++ -Wall -leasycurl test.cpp -o test
	
clean:
	cd entities; make clean; cd ..
	rm *.o
	rm test

install:
	cp easycurl.h /usr/include/
	cp libeasycurl.so /usr/lib/
	chmod 0755 /usr/lib/libeasycurl.so
	ldconfig

uninstall:
	cp /usr/include/easycurl.h 
	cp /usr/lib/libeasycurl.so 

