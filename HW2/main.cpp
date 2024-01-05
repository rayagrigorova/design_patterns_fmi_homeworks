#include <iostream>

#include "Labels.h"
#include "CompositeTransformation.h"
#include "LabelDecorators.h"
#include "STDINLabel.h"
#include "Transformations.h"
#include "CensorTransformationFactory.h"

using namespace std;

int main() {
        CensorTransformationFactory factory;

        const CensorTransformation& shortWordTrans = factory.getFlyweight("test");
        const CensorTransformation& longWordTrans = factory.getFlyweight("testing");

         cout << (shortWordTrans.transform("This is a test sentence."));
         cout << (longWordTrans.transform("testing this sentence.") );
}
