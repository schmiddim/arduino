#include <Charliplexing.h>
#include <led7Segment.h>

void setup(){
	LedSign::Init( GRAYSCALE);
}

void loop() {
	displayDigit(0,0, 3);

	displayDigit(5,0, 6);

	displayDigit(0,8, 3);

	displayDigit(5,8, 0);

}
