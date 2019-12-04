CPPFLAGS=-I/opt/opencv/include 
CXXFLAGS=-Wall -Wextra #-Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui


OBJ= common.o
BIN=threshold\

.PHONY: all 
all: $(BIN)

$(BIN): common.o

.PHONY: test
test:
	./threshold ../data/log1/001-rgb.png

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o
