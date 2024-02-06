#include "Application.h"

int main() {
	std::shared_ptr<Application> app = std::make_shared<Application>();
	app->run();
}