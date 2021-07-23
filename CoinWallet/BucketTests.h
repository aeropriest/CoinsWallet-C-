//
//  BucketTests.h
//  HexTest
//
//  Created by homi on 20/7/2021.
//

#ifndef BucketTests_h
#define BucketTests_h

void BucketUnitTest(short counter, short j){
    {
        Wallet wallet = Wallet();
        MAX_LONG low = pow(BUCKET_STEP,j), high = pow(BUCKET_STEP,j+1)-1, coin_val = 0;
        for(int i=0; i<5;i++){
            coin_val = rand() % high + low;
            //cout << "LOW "<<low<<" HIGH "<<high<<" VAL "<<coin_val;
            wallet.add(Coin(coin_val));
        }

        cout << "Test Case 4." << counter;
        CoinsVector bucket = wallet.get_bucket(j);
        short ret = bucket.size();
        ret == 5 ? cout << "\tPASSED \u2714 " : cout << "\tFAILED \u2718 ";
        cout << "\t[ Wallet has 5 coins in "<< low <<" .. "<<high<<" bucket ]"<<endl;
        
        

        cout << "Test Case 4." << counter+1;
        bool result = true;
        for (vector<Coin>::iterator coin = bucket.begin() ; coin != bucket.end(); ++coin){
            MAX_LONG value = coin->get_value();
            if( value <=low || value >= high){
                result = false;
                break;
            }
        }
        result ? cout << "\tPASSED \u2714 " : cout << "\tFAILED \u2718 ";

        cout << "\t[ ";

        for (vector<Coin>::iterator coin = bucket.begin() ; coin != bucket.end(); ++coin){
            MAX_LONG value = coin->get_value();
            cout << value << ", ";
        }
        cout<<"]"<<endl;
    }
}

void BucketTests(){
    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"Test coin buckets"<<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;

    int count = 1;
    for( short t=0; t<5; t++, count++){
        BucketUnitTest(count,t);
    }
}

#endif /* BucketTests_h */
