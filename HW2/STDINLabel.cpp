#include "STDINLabel.h"

STDINLabel::STDINLabel(size_t timeout) : timeout(timeout){

}

void STDINLabel::enterText() {
	std::string str;
	std::cout << "Please, enter text\n";
	std::getline(std::cin, str);

	label.value = str;
	numberOfCalls = 0;
}

std::string STDINLabel::getText() {
	if (numberOfCalls < 0) {
		enterText();
	}

	else if (numberOfCalls >= timeout) {
		std::cout << "Would you like to enter the string again?\nEnter 'y' for 'yes' and 'n' for 'no'.\n";
		char ans;
		std::cin >> ans;
		// using cin and getline() together can cause issues otherwise 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (ans) {
		case 'y':
		case 'Y':
			enterText();
			std::cout << "New label was saved\n";
			break;
		case 'N':
		case 'n':
			std::cout << "No change requested\n";
			numberOfCalls = 0; // the user will be asked again after 'timeout' requests  
			break;
		default:
			std::cerr << "Invalid command\n";

		}
	}
	numberOfCalls++;
	return label.getText();
}