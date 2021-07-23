//
//  Coin.h
//  HexTest
//
//  Created by homi on 19/7/2021.
//


#ifndef Coin_h
#define Coin_h


class Coin{
public:
    Coin(unsigned long long value){
        this->value = value;
        this->reserverd = false;
    }
    unsigned long long get_value() const {
        return value;
    }
    void set_value(const unsigned long long value){
        this->value = value;
    }
    void set_reserve(bool value){
        this->reserverd = value;
    }
    bool is_reserverd() const{
        return reserverd;
    }
private:
    unsigned long long value;
    bool reserverd;
};

#endif /* Coin_h */
