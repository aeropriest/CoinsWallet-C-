//
//  DistributionTest.h
//  HexTest
//
//  Created by Ashok Jaiswal on 21/7/2021.
//

#ifndef DistributionTest_h
#define DistributionTest_h

void DistributionTests(){
    
    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"Test coin distribution in buckets" <<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;

    Wallet wallet = Wallet();
    for(int j=0; j<MAX_POWER; j++){
        MAX_LONG low = pow(BUCKET_STEP,j), high = pow(BUCKET_STEP,1+j)-1, coin_val = 0;
        for(int i=0; i<MAX_POWER;i++){
            coin_val = rand() % high + low;
            wallet.add(coin_val);
        }
    }
    
    Distributor distributor(wallet.get_coins());
    BucketMap    buckets = distributor.distribute();

    cout << "Test Case 5.1 ";
    short ret = buckets.size();
    ret != MAX_POWER ? cout << "\tFAILED  \u2718 " : cout << "\tPASSED \u2714 ";
    cout << "\t[ This distribution should have "<<MAX_POWER<<" buckets  ]"<<endl;
    

    cout << "Test Case 5.2";
    bool result = true;
    
    for (BucketMap::iterator bucket = buckets.begin(); bucket != buckets.end(); ++bucket){
        if( bucket->second.size() != MAX_POWER ){
            result = false;
            break;
        }
    }
    
    !result ? cout << "\tFAILED  \u2718 " : cout << "\tPASSED \u2714 ";
    cout << "\t[ Each bucket should have "<<MAX_POWER<<" coins  ]"<<endl;


    int index = 2;
    for (BucketMap::iterator bucket = buckets.begin(); bucket != buckets.end(); ++bucket){
        cout << "Test Case 5."<<1+index++;
        MAX_LONG low = pow(BUCKET_STEP,index-3),
                 high = pow(BUCKET_STEP,1+index-3),
                 min = *min_element(bucket->second.begin(), bucket->second.end()),
                 max = *max_element(bucket->second.begin(), bucket->second.end());
        min >= low && max < high && max < high && max >= low ? cout << "\tPASSED \u2714 " : cout << "\tFAILED  \u2718 ";
        
        cout << "\t[ Min " << min << " Max " << max << " should be in bucket range " << low << " ... "<<high<<endl;
    }
    
    cout << "Test Case 5.8";
    MAX_LONG available_before = wallet.available();
    MAX_LONG in_bucket_before = 0;
    MAX_LONG coin_count_before = 0;
    for (BucketMap::iterator bucket = buckets.begin(); bucket != buckets.end(); ++bucket){
        for (MaxLongVector::iterator coin = bucket->second.begin(); coin != bucket->second.end(); ++coin){
            in_bucket_before += *coin;
            coin_count_before++;
        }
    }
    
    in_bucket_before == available_before ? cout << "\tPASSED \u2714 " : cout << "\tFAILED  \u2718 ";
    cout << "\t[ Value of coins in wallet " << available_before << " should be sum of coins in buckets " << in_bucket_before <<" ]" << endl;

    cout << "Test Case 5.10";
    MAX_LONG low = pow(BUCKET_STEP,0), high = pow(BUCKET_STEP,1+MAX_POWER);
    MAX_LONG coin_val = rand() % high + low;

    wallet.spend(coin_val);
    
    Distributor distributor_after(wallet.get_coins());
    BucketMap    buckets_after = distributor_after.distribute();

    MAX_LONG available_after = wallet.available();
    MAX_LONG in_bucket_after = 0;
    MAX_LONG coin_count_after = 0;
    for (BucketMap::iterator bucket = buckets_after.begin(); bucket != buckets_after.end(); ++bucket){
        for (MaxLongVector::iterator coin = bucket->second.begin(); coin != bucket->second.end(); ++coin){
            in_bucket_after += *coin;
            coin_count_after++;
        }
    }
    coin_count_before > coin_count_after ? cout << "\tPASSED \u2714 " : cout << "\tFAILED  \u2718 ";
    cout << "\t[ After spending  " << coin_val << " coins in bucket reduced from " << coin_count_before << " to " << coin_count_after << " ]" << endl;

    cout << "Test Case 5.11";
    available_before > available_after ? cout << "\tPASSED \u2714 " : cout << "\tFAILED  \u2718 ";
    cout << "\t[ After spending  " << coin_val << " value in buckets reduced from " << available_before << " to " << available_after << " ]" << endl;

}

#endif /* DistributionTest_h */
