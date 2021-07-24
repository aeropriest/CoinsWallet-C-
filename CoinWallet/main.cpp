//
//  main.cpp
//  HexTest
//
//  Created by homi on 19/7/2021.
//

#include <iostream>     // std::cout
#include <algorithm>    // std::lower_bound, std::upper_bound, std::sort
#include <vector>       // std::vector

#include "Defines.h"
#include "Wallet.h"
#include "Distributor.h"
#include "AddTests.h"
#include "SpendTests.h"
#include "ReserveTests.h"
#include "DistributionTests.h"

int main(int argc, const char * argv[]) {
    
    AddTests();
    SpendTests();
    ReserveTest();
    DistributionTests();

    return 0;
}
