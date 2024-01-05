#include <iostream>

#include "Labels.h"
#include "CompositeTransformation.h"
#include "LabelDecorators.h"
#include "STDINLabel.h"
#include "Transformations.h"

using namespace std;

int main() {
    STDINLabel label(1);

    for(int i  = 0; i < 20; i++)
    cout << label.getText() << '\n';
}
