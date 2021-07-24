//
//  Distributor.h
//  HexTest
//
//  Created by homi on 22/7/2021.
//

#ifndef Distributor_h
#define Distributor_h

// Implementation of distributor class to categorize the coins into buckets in the range 10ⁿ3
class Distributor{
public:
    Distributor(MaxLongVector *c) : coins(c){
        
    }
    
    //short distribute(BucketVector *buckets){
    BucketMap distribute(){
        BucketMap   buckets;
        // sanity check if the coins vector pointer was invalid
        if( !coins )
            return buckets;
        
        // going through each coin in the wallet and add the bucket vector sent by caller
        for (MaxLongVectorIt coin = coins->begin(); coin != coins->end(); ++coin){
            for( int j=0; j<MAX_POWER; j++){
                MAX_LONG low = pow(BUCKET_STEP,j), high = pow(BUCKET_STEP,j+1);
                if( *coin >= low && *coin < high ){
                    buckets[j].push_back(*coin);
                    break;
                }
            }
        }
        return buckets;
    }
    
private:
    // Pointer to the coins vector in the wallets
    MaxLongVector     *coins;
};
#endif /* Distributor_h */

