//
//  main.cpp
//  HexTest
//
//  Created by homi on 19/7/2021.
//

#include <iostream>
#include "Defines.h"
#include "Wallet.h"
//#include "Coin.h"
#include "Distributor.h"
#include "AddTests.h"
#include "SpendTests.h"
#include "ReserveTests.h"
#include "DistributionTests.h"


#include <iostream>     // std::cout
#include <algorithm>    // std::lower_bound, std::upper_bound, std::sort
#include <vector>       // std::vector


int main(int argc, const char * argv[]) {
    
    Wallet wallet = Wallet();
    std::vector<MAX_LONG> v;
    srand(time(NULL));
    for(int i=0; i<100; i++){
        MAX_LONG low = pow(BUCKET_STEP,1), high = pow(BUCKET_STEP,2);
        MAX_LONG value = rand() % low + high, total = 0;

        cout << value << ", ";
        v.push_back(value);
    }
    cout<<endl;
      std::sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

      std::vector<MAX_LONG>::iterator low,up;
    //srand(time(NULL));
        MAX_LONG lower = pow(BUCKET_STEP,1), higher = pow(BUCKET_STEP,2);
        MAX_LONG spend = rand() % lower + higher;
      low=std::lower_bound (v.begin(), v.end(), spend); //          ^
      up= std::upper_bound (v.begin(), v.end(), spend); //                   ^

    cout << " spend "<<spend<<endl;
      std::cout << "lower_bound at position " << (low- v.begin()) << " value" << *low << '\n';
      std::cout << "upper_bound at position " << (up - v.begin()) << " value" << *up << '\n';

    AddTests();
    SpendTests();
    ReserveTest();
    DistributionTests();
/*
    Wallet wallet = Wallet();
    for(int j=0; j<MAX_POWER; j++){
        MAX_LONG low = pow(BUCKET_STEP,j), high = pow(BUCKET_STEP,1+j)-1, coin_val = 0;
        for(int i=0; i<5;i++){
            coin_val = rand() % high + low;
            //cout << "LOW "<<low<<" HIGH "<<high<<" VAL "<<coin_val;
            wallet.add(Coin(coin_val));
        }
    }
    
    Distributor distributor(wallet.get_coins());
    BucketVector    buckets;
    int bucket_size = distributor.distribute(&buckets);
    
    cout << "Unpack the bucket now " << bucket_size;
    int i=0;
    for (BucketVector::iterator bucket = buckets.begin(); bucket != buckets.end(); ++bucket){
        i++;
        cout << "Bucket "<<i<<" ";
        for (MaxLongVector::iterator coin = bucket->begin(); coin != bucket->end(); ++coin){
            cout<<*coin<<", ";
        }
        cout<<endl;
    }
    */
    return 0;
}
