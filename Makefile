TARGET = prac2
CC = g++ -std=c++2a
SOURCES = employee.cpp date.cpp main.cpp algorithms.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	 $(CC) $(SOURCES) -o $(TARGET)

clean:
	rm -rf $(TARGET)