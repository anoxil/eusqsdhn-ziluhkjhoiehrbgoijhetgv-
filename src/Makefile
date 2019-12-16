CPPFLAGS=-I/opt/opencv/include 
CXXFLAGS=-Wall -Wextra #-Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui


OBJ=\
	common.o\
	morphology.o\
	compare.o

BIN=\
	threshold\
	threshold-medianfilter\
	threshold-medianfilter-video\
	threshold-opening

.PHONY: all 
all: $(BIN)

$(BIN): $(OBJ)

.PHONY: test
test:
	./threshold ../data/log1/001-rgb.png

.PHONY: test-opening
test-opening:
	./threshold-opening ../data/log1/001-rgb.png

.PHONY: test-medianfilter
test-medianfilter:
	./threshold-medianfilter ../data/log1/027-rgb.png

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o
