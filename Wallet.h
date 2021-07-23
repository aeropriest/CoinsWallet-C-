//
//  Wallet.h
//  HexTest
//
//  Created by homi on 19/7/2021.
//

#ifndef Wallet_h
#define Wallet_h


class Wallet{
public:
    Wallet(){
        total_value = 0;
    }
    bool add(Coin coin){

        big_long value = coin.get_value();
        
        if( value <= 0 || value > COIN_LIMIT || total_value+value >= WALLET_LIMIT){
            return false;
        }
        /*
         for( big_long j=0; j<MAX_POWER; j++){
         big_long low = pow(BUCKET_STEP,j), high = pow(BUCKET_STEP,j+1);
         
         if( value >= low && value < high ){
         buckets[j].push_back(coin);
         return true;
         }
         }*/
        bool ret = false;
        if( value >= pow(BUCKET_STEP,0) && value < pow(BUCKET_STEP,1) ){
            ret = true;
            buckets[0].push_back(coin);
        }else if( value >= pow(BUCKET_STEP,1) && value < pow(BUCKET_STEP,2) ){
            ret = true;
            buckets[1].push_back(coin);
        }else if( value >= pow(BUCKET_STEP,2) && value < pow(BUCKET_STEP,3) ){
            ret = true;
            buckets[2].push_back(coin);
        }else if( value >= pow(BUCKET_STEP,3) && value < pow(BUCKET_STEP,4) ){
            ret = true;
            buckets[3].push_back(coin);
        }else if( value >= pow(BUCKET_STEP,4) && value < pow(BUCKET_STEP,5) ){
            ret = true;
            buckets[4].push_back(coin);
        }else {
            return false;
        }

        total_value += value;
        coins.push_back(coin);
        return ret;
    }
    
    CoinsVector get_bucket(short index){
        //return distribution.get_bucket(index);
        return buckets[index];
    }
    
    short buckets_size() const{
        return MAX_POWER;
    }
    
    big_long available() const {
        return total_value;
    }

    
    bool spend(big_long _value){

        if( _value <= 0 || _value > WALLET_LIMIT || _value > this->total_value ){
            return false;
        }
        big_long _total_value= 0;
        for (CoinsVector::iterator coin = coins.begin() ; coin != coins.end(); ++coin){
            _total_value += coin->get_value();
            this->total_value -= coin->get_value();
            coins.erase(coin);
            coin--;
            if( _value <= _total_value )
                return true;
        }
        return false;
    }
    
    bool reserve(big_long _value){
        if( _value <= 0 || _value > WALLET_LIMIT || _value > this->total_value ){
            return false;
        }

        big_long _total_value= 0;
        //cout << " reserve now " << _value << "  " << _total_value << endl;
        for (CoinsVector::iterator coin = coins.begin() ; coin != coins.end(); ++coin){
            _total_value += coin->get_value();
            //cout << " reserve now " << _value << "  " << _total_value << endl;
            if( _value <= _total_value ){
                coin->set_reserve(true);
                this->total_value -= _total_value;
                return true;
            }
            coin->set_reserve(true);
        }
        return false;
    }
    
    bool cancel_reserverved(){
        for (CoinsVector::iterator coin = coins.begin() ; coin != coins.end(); ++coin){
            if( coin->is_reserverd() ){
                this->total_value += coin->get_value();
                coin->set_reserve(false);
            }
        }
        return true;
    }
    bool spend_reservered(){
        for (CoinsVector::iterator coin = coins.begin() ; coin != coins.end(); ++coin){
            if( coin->is_reserverd() ){
                coins.erase(coin);
                coin--;
            }
        }
        return true;
    }
private:
    big_long        total_value;
    CoinsVector     coins;
    CoinsVector     buckets[MAX_POWER];
};

#endif /* Wallet_h */
