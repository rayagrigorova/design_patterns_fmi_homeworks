#include <iostream>

#include "Labels.h"
#include "CompositeTransformation.h"
#include "LabelDecorators.h"
#include "STDINLabel.h"
#include "Transformations.h"

int main() {
	STDINLabel l(0);
	for (int i = 0; i < 100; i++)
		std::cout << l.getText() << "\n";
}
