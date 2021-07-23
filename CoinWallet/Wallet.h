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
    
    bool require(MAX_LONG value){
        return !( value <= 0 || value > WALLET_LIMIT || value > this->total_value );
    }

    bool add(Coin coin){
        
        MAX_LONG value = coin.get_value();
        
        if( value <= 0 || value > COIN_LIMIT || this->total_value+value >= WALLET_LIMIT){
            return false;
        }
        
        this->total_value += value;
        coins.push_back(coin);
        
        return true;
    }
    
    
    MAX_LONG available() const {
        return this->total_value;
    }
    
    bool spend(MAX_LONG value){

        if( !require(value))
            return false;
        
        MAX_LONG total= 0;
        for (CoinsVector::iterator coin = coins.begin(); coin != coins.end(); ++coin){
            total += coin->get_value();
            this->total_value -= coin->get_value();
            coins.erase(coin);
            coin--;
            if( value <= total )
                return true;
        }
        return false;
    }    

    bool reserve(MAX_LONG value){

        if( !require(value))
            return false;

        MAX_LONG total = 0;
        for (CoinsVector::iterator coin = coins.begin() ; coin != coins.end(); ++coin){
            total += coin->get_value();
            if( value <= total ){
                coin->set_reserve(true);
                this->total_value -= total;
                return true;
            }
            coin->set_reserve(true);
        }
        return false;
    }
    
    bool cancel_reserved(){
        for (CoinsVector::iterator coin = coins.begin() ; coin != coins.end(); ++coin){
            if( coin->is_reserverd() ){
                this->total_value += coin->get_value();
                coin->set_reserve(false);
            }
        }
        return true;
    }
    bool spend_reserved(){
        for (CoinsVector::iterator coin = coins.begin() ; coin != coins.end(); ++coin){
            if( coin->is_reserverd() ){
                coins.erase(coin);
                coin--;
            }
        }
        return true;
    }
    CoinsVector *get_coins(){
        return &coins;
    }
private:
    MAX_LONG        total_value;
    CoinsVector     coins;
    CoinsVector     buckets[MAX_POWER];
};

#endif /* Wallet_h */
