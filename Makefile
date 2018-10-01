# compiler
CC = gcc
CXX = g++

# compiler flags
CPPFLAGS = -g -Wall

# build target executable
TARGET = starx
SRCS = main.cpp exosuit.cpp arduinomicro.cpp converter.cpp pid.cpp serial.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

# remove
RM = rm -rf

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp exosuit.h arduinomicro.h converter.h pid.h serial.h
	$(CXX) $(CPPFLAGS) -c $(SRCS)

exosuit.o: exosuit.cpp exosuit.h arduinomicro.h converter.h pid.h serial.h
	$(CXX) $(CPPFLAGS) -c exosuit.cpp arduinomicro.cpp converter.cpp pid.cpp serial.cpp

converter.o: converter.cpp converter.h
	$(CXX) $(CPPFLAGS) -c converter.cpp

pid.o: pid.cpp pid.h
	$(CXX) $(CPPFLAGS) -c pid.cpp

arduinomicro.o: arduinomicro.cpp arduinomicro.h serial.h
	$(CXX) $(CPPFLAGS) -c arduinomicro.cpp serial.cpp

serial.o: serial.cpp serial.h
	$(CXX) $(CPPFLAGS) -c serial.cpp

clean:
	$(RM) $(TARGET) *.o *~
