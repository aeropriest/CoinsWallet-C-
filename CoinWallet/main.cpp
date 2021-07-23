//
//  main.cpp
//  HexTest
//
//  Created by homi on 19/7/2021.
//

#include <iostream>
#include "Defines.h"
#include "Wallet.h"
#include "Coin.h"
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
