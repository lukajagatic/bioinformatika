CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		bioinformatika.o

LIBS =

TARGET =	bioinformatika

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
