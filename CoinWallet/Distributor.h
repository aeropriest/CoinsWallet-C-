//
//  Distributor.h
//  HexTest
//
//  Created by homi on 22/7/2021.
//

#ifndef Distributor_h
#define Distributor_h

class Distributor{
public:
    Distributor(CoinsVector *c) : coins(c){
        
    }
    
    short distribute(BucketVector *buckets){
        
        MaxLongVector     coins_buckets[MAX_POWER];
        for (CoinsVector::iterator coin = coins->begin(); coin != coins->end(); ++coin){
            MAX_LONG value = coin->get_value();
            for( int j=0; j<MAX_POWER; j++){
                MAX_LONG low = pow(BUCKET_STEP,j), high = pow(BUCKET_STEP,j+1);
                if( value >= low && value < high ){
                    coins_buckets[j].push_back(value);
                    break;
                }
            }
        }
        
        for( int j=0; j<MAX_POWER; j++){
            if( coins_buckets[j].size() > 0 ){
                buckets->push_back(coins_buckets[j]);
            }
        }
        return buckets->size();
    }
    
private:
    CoinsVector     *coins;
};
#endif /* Distributor_h */
