//
//  DistributionTest.h
//  HexTest
//
//  Created by Ashok Jaiswal on 21/7/2021.
//

#ifndef DistributionTest_h
#define DistributionTest_h
void FillWallet(Wallet *wallet){
    //fill the bucket
    for(int j=0; j<MAX_POWER; j++)
    {
        MAX_LONG low = pow(BUCKET_STEP,j), high = pow(BUCKET_STEP,j+1)-1, coin_val = 0;
        int limit = rand() % 6+2;
        for(int i=0; i<limit; i++){
            coin_val = rand() % high + low;
            wallet->add(Coin(coin_val));
        }
    }
}

void TestBucketDistribution(int test_count, int j, Wallet *wallet){

    cout << "Test Case 5." << test_count+1;
    if( !wallet ){
        cout << "\tFAILED \u2718";
        cout << "\t[ No distribution object found ]";
        return;
    }
    CoinsVector bucket = wallet->get_bucket(j);
    bool result = true;
    MAX_LONG low = pow(BUCKET_STEP,j), high = pow(BUCKET_STEP,j+1)-1;
    for (CoinsVector::iterator coin = bucket.begin() ; coin != bucket.end(); ++coin){
        MAX_LONG value = coin->get_value();
        if( value <=low || value >= high){
            result = false;
            break;
        }
    }
    result ? cout << "\tPASSED \u2714 " : cout << "\tFAILED \u2718";
    
    cout << "\t[ ("<<low<<" ... "<<high<<") ";
    
    for (vector<Coin>::iterator coin = bucket.begin() ; coin != bucket.end(); ++coin){
        MAX_LONG value = coin->get_value();
        cout << value << ", ";
    }
    cout<<"]"<<endl;
}

void DistributionTests(){
    Wallet wallet = Wallet();
    
    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"Test coin distribution"<<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;

    FillWallet(&wallet);

    //Distribution *distribution = wallet.get_distribution();
    cout << "Test Case 5.1 ";
    short ret = wallet.buckets_size();
    ret != MAX_POWER ? cout << "\tFAILED  !" : cout << "\tPASSED \u2714 ";
    cout << "\t[ This distribution should have "<<MAX_POWER<<" buckets  ]"<<endl;
    
    for(int count=0; count < MAX_POWER; count++){
        TestBucketDistribution(count+1, count, &wallet);
    }
}

#endif /* DistributionTest_h */
