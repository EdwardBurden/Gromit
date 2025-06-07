#include "ExampleApplication.h"

int main() {
	ExampleApplication* app = new ExampleApplication();
	app->StartUp();

	delete app;
}