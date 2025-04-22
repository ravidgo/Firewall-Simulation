CXX=g++
CXXLINK=$(CC)
CXXFLAGS=-std=c++11 -g -Wall
OBJS=string.o ip.o port.o
EXEC=firewall.exe
RM=rm -rf


all:  $(EXEC) libfirewall.so 

#linkaging main with firewall.exe
$(EXEC): main.o libfirewall.so libinput.so
	$(CXX) main.o -o $(EXEC) -lfirewall -linput -L.

#create our library of libfirewall
libfirewall.so: $(OBJS) 
	$(CXXLINK) -shared $(OBJS) -o libfirewall.so -L. 	


#contents of firewall(generic field.h is implictly used in ip.h, port.h

main.o: main.cpp input.h ip.h port.h generic-field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp

ip.o: ip.cpp ip.h generic-field.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.cpp port.h generic-field.h
	$(CXX) $(CXXFLAGS) -c -fpic  port.cpp

string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic  string.cpp


clean:
	$(RM) *.o *.exe


