CPPFLAGS=-I/opt/opencv/include 
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui\
	-lopencv_features2d\
  	-lopencv_nonfree\
  	-lopencv_calib3d


OBJ=\
	common.o\
	morphology.o\
	compare.o

BIN=\
	threshold-opening\
	threshold-medianfilter\
	threshold-medianfilter-video\
	threshold-medianfilter-video-interests


.PHONY: all 
all: $(BIN)

$(BIN): $(OBJ)

.PHONY: test-opening
test-opening:
	./threshold-opening

.PHONY: test-medianfilter
test-medianfilter:
	./threshold-medianfilter ../data/output_log1.mp4

.PHONY: test-medianfilter-video
test-medianfilter-video:
	./threshold-medianfilter-video ../data/output_log1.mp4

.PHONY: test-medianfilter-video-interests
test-medianfilter-video-interests:
	./threshold-medianfilter-video-interests ../data/output_log1.mp4

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o
