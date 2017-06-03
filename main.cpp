#include "Diabeetus.h"

int main(int argc, char** argv) {

	Diabeetus d;
	d.Init();

	while (!d.Done()) {
		d.Input();
		d.Render();
		d.Update();
	}

	d.Clean();

	return 0;
}
