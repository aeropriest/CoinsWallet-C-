//
//  main.cpp
//  HexTest
//
//  Created by homi on 19/7/2021.
//

#include <iostream>
#include "Defines.h"
#include "Wallet.h"
#include "AddTests.h"
#include "SpendTests.h"
#include "ReserveTests.h"
#include "BucketTests.h"
#include "DistributionTests.h"

int main(int argc, const char * argv[]) {
    
    AddTests();
    SpendTests();
    ReserveTest();
    BucketTests();
    DistributionTests();

    return 0;
}
