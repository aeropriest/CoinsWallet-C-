//
//  Defines.h
//  HexTest
//
//  Created by Ashok Jaiswal on 21/7/2021.
//

#ifndef Defines_h
#define Defines_h
#include <cmath>
#include "Coin.h"
#include <vector>


#define BUCKET_STEP     1000
#define COIN_LIMIT      1000000000000000
#define WALLET_LIMIT    1000000000000000000
#define MAX_POWER       5


typedef unsigned long long      MAX_LONG;


using namespace std;
typedef vector<Coin>                        CoinsVector;
typedef vector<MAX_LONG>                    MaxLongVector;
typedef vector<MaxLongVector>            BucketVector;

#endif /* Defines_h */
