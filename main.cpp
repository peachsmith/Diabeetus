#include "Diabeetus.h"

int main(int argc, char** argv) {

	Diabeetus d;
	d.init();

	while (!d.isDone()) {
		d.input();
		d.render();
		d.update();
	}

	d.clean();

	return 0;
}
