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
    Coin(unsigned long long _value){
        this->value = _value;
        this->reserverd = false;
        bucket_id = 0;
    }
    unsigned long long get_value() const {
        return value;
    }
    void set_value(const unsigned long long _value){
        this->value = _value;
    }
    void set_reserve(bool _value){
        this->reserverd = _value;
    }
    bool is_reserverd() const{
        return reserverd;
    }
private:
    unsigned long long value;
    bool reserverd;
    int bucket_id;
};

#endif /* Coin_h */
