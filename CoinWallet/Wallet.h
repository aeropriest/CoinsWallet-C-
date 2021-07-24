//
//  Wallet.h
//  HexTest
//
//  Created by homi on 19/7/2021.
//

#ifndef Wallet_h
#define Wallet_h

#include <algorithm>    // std::lower_bound, std::upper_bound, std::sort

/*
 Implementation of a Coin Wallet for storing value of up to 10ⁿ18 for coins from value of 0 to 10ⁿ15 (it could be extended as a crypto wallet too)
 Exposes following public methods
 add - for adding coins into the wallet, sanity check is done before adding the coin
 available - returns value of total value of available coins (excluding the reserved coins)
 spend - for actually spending the coins in the wallet, it makes the sanity check (reserved coins are out of available pool for spending)
 reserve - to actually set aside part of the available coins (could be used for cases where a 'contract' must be executed before releasing coin)
 spend / cancel reserved - to actually either release the reserved coins or cancel the reservation (e.g. based on the result of an executed contract)
 */
class Wallet{
public:
    Wallet(){
        total_value = 0;
    }
    
    bool require(MAX_LONG value){
        return !( value <= 0 || value > WALLET_LIMIT || value > this->total_value );
    }

    // add the coin to the wallet coin vecotr and increase the available value of coins
    // do the sanity check - coin should not be valued zeor or is more than the coin's max value
    // wallet does not overflow its capacity
    
    bool add(MAX_LONG value){
        if( value <= 0 || value > COIN_LIMIT || this->total_value+value >= WALLET_LIMIT){
            return false;
        }

        this->total_value += value;
        coins.push_back(value);
        return true;
    }
    
    MAX_LONG available() const {
        return this->total_value;
    }
    
    // spend the coin of requested value, most often value requested might not be exact sum
    // of value of coins so only checking closest possible more than requested value
    // its possible to further go through the reserved coins and bring it closest or exact to
    // coins required to reserve
    
    // validation check is through the 'require' function
/*
    
    MaxLongVectorIt lowest(MAX_LONG value) {
        MaxLongVectorIt it = lower_bound(coins.begin(), coins.end(), value);
        return it;
    }
    
    MaxLongVectorIt highest(MAX_LONG value) {
        MaxLongVectorIt it = upper_bound(coins.begin(), coins.end(), value);
        //if (it == coins.end()) { return 0; }

        return it;
    }
     */
    bool spend(MAX_LONG value){

        if( !require(value))
            return false;

        // sort the coins to find closest value in coins for spending
        sort (coins.begin(), coins.end());
        MaxLongVectorIt lower = lower_bound(coins.begin(), coins.end(), value);
        MaxLongVectorIt upper = upper_bound(coins.begin(), coins.end(), value);
        
        // if no bound found then return the closest can find by sum of values
        if( lower == coins.end() && upper == coins.end() ){
            MAX_LONG total= 0;
            for (MaxLongVectorIt coin = coins.begin(); coin != coins.end(); ++coin){
                total += *coin;
                this->total_value -= *coin;
                coins.erase(coin);
                coin--;
                if( value <= total ){
                    return true;
                }
            }
        }
        
        // if lower not found, check the higher and return
        if( lower == coins.end() && upper != coins.end()){
            this->total_value -= *upper;
            coins.erase(upper);
            return true;
        }
        
        // if uppwer not found, spend the lowest
        if( upper == coins.end() && lower != coins.end() ){
            this->total_value -= *lower;
            coins.erase(lower);
            return true;
        }
                
        // if both bounds are found, return one with closest to spending value i.e. least of 2 bounds
        if( *lower <= *upper ){
            this->total_value -= *lower;
            coins.erase(lower);
            return true;
        }
        if( *lower >= *upper ){
            this->total_value -= *upper;
            coins.erase(upper);
            return true;
        }
        
        return true;
    }    

    // reserve the coin of specified value, most often value requested might not be exact sum
    // of value of coins so only check closest possible more than requested value
    // its possible to further go through the reserved coins and bring it closest or exact to
    // coins required to reserve
    
    // validation check is through the 'require' function
    bool reserve(MAX_LONG value){

        if( !require(value))
            return false;


        // sort the coins to find closest value in coins for spending
        sort (coins.begin(), coins.end());
        MaxLongVectorIt lower = lower_bound(coins.begin(), coins.end(), value);
        MaxLongVectorIt upper = upper_bound(coins.begin(), coins.end(), value);
        
        // if no bound found then return the closest can find by sum of values
        if( lower == coins.end() && upper == coins.end() ){
            MAX_LONG total= 0;
            for (MaxLongVectorIt coin = coins.begin(); coin != coins.end(); ++coin){
                total += *coin;
                this->total_value -= *coin;
                reserved.push_back(*coin);
                coins.erase(coin);
                coin--;
                if( value <= total ){
                    return true;
                }
            }
        }
        
        // if lower not found, check the higher and return
        if( lower == coins.end() && upper != coins.end()){
            this->total_value -= *upper;
            reserved.push_back(*upper);
            coins.erase(upper);
            return true;
        }
        
        // if uppwer not found, spend the lowest
        if( upper == coins.end() && lower != coins.end() ){
            this->total_value -= *lower;
            reserved.push_back(*lower);
            coins.erase(lower);
            return true;
        }
                
        // if both bounds are found, return one with closest to spending value i.e. least of 2 bounds
        if( *lower <= *upper ){
            this->total_value -= *lower;
            reserved.push_back(*lower);
            coins.erase(lower);
            return true;
        }
        if( *lower >= *upper ){
            this->total_value -= *upper;
            reserved.push_back(*upper);
            coins.erase(upper);
            return true;
        }
        
        return true;
    }
    
    // cancel the reserved coins by going through the coins loop, check the coin's reserved flag and
    // increase the total value of the wallet
    bool cancel_reserved(){
        for (MaxLongVectorIt reserve = reserved.begin(); reserve != reserved.end(); ++reserve){
            coins.push_back(*reserve);
            this->total_value += *reserve;
            reserved.erase(reserve);
            reserve--;
        }
        return true;
    }
    
    // spend the reserved coins by going through the coins loop, check the coin's reserved flag
    bool spend_reserved(){
        for (MaxLongVectorIt reserve = reserved.begin(); reserve != reserved.end(); ++reserve){
            reserved.erase(reserve);
            reserve--;
        }
        return true;
    }
    
    // return the pointer of the coins vector for distributor to categorize them into buckets
    // its a point to vector so it would never be null and copy constructor on Coins or vector class would not copy constructor
    MaxLongVector *get_coins(){
        return &coins;
    }
private:
    MaxLongVector       reserved;           // remove the reserved coins from main coin vector and move them into this
                                            // if reserved coins are spent, remove them from this vector
                                            // if reserved coins are cancelled, move them back into main coins vector
    MAX_LONG            total_value;            // save the total value of coins added in the wallet, this avoids processing required
                                            //to calculate the coins value by looping through the coins vector
    
    MaxLongVector     coins;                  // store the coin class variables in a vector, vector is choses over any
                                            //other data type becuase memory for vector is allocated in contiguous memory
    
};

#endif /* Wallet_h */
