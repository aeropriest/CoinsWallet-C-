//
//  AddTests.h
//  HexTest
//
//  Created by homi on 20/7/2021.
//

#ifndef AddTests_h
#define AddTests_h

void AddTests(){
    

    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"Test Boundry Values"<<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;

    {
        Wallet wallet = Wallet();
        cout << "Test Case 1.1 ";
        wallet.available() > 0 ? cout << "\tFAILED \u2718 " : cout << "\tPASSED \u2714 ";
        cout << "\t[ When wallet created, it should be empty ]"<<endl;
    }
    {
        Wallet wallet = Wallet();

        bool ret = wallet.add(0);

        cout << "Test Case 1.2 ";
        ret ? cout << "\tFAILED  !" : cout << "\tPASSED \u2714";
        cout << "\t[ Wallet should reject coin of value 0 ]"<<endl;
        
        cout << "Test Case 1.3 ";
        wallet.available() > 0 ? cout << "\tFAILED \u2718" : cout << "\tPASSED \u2714";
        cout << "\t[ Wallet should not add coin of value 0 ]"<<endl;
    }
        
    {
        Wallet wallet = Wallet();

        bool ret = wallet.add(-10);

        cout << "Test Case 1.4 ";
        ret ? cout << "\tFAILED  !" : cout << "\tPASSED \u2714";
        cout << "\t[ Wallet should not add coin of negetive value ]"<<endl;

        cout << "Test Case 1.5 ";
        wallet.available() < 0 ? cout << "\tFAILED \u2718 " : cout << "\tPASSED \u2714 ";
        cout << "\t[ Wallet balance should not be negetive]"<<endl;
    }
    {
        Wallet wallet = Wallet();

        bool ret = wallet.add(COIN_LIMIT+1);

        cout << "Test Case 1.6 ";
        ret ? cout << "\tFAILED  !" : cout << "\tPASSED \u2714";
        cout << "\t[ Wallet should reject coin of value more than 10 ~ 15 ]"<<endl;
        
    }
    {
        Wallet wallet = Wallet();
        bool ret = wallet.add(COIN_LIMIT-1);
        cout << "Test Case 1.7 ";
        ret ? cout << "\tPASSED \u2714" : cout << "\tFAILEDD  !";
        cout << "\t[ Wallet added value less than 10 ~ 15 ]"<<endl;
        
        cout << "Test Case 1.8 ";
        big_long availble = wallet.available();
        availble != COIN_LIMIT-1 ? cout << "\tFAILED \u2718 " : cout << "\tPASSED \u2714 ";
        cout << "\t[ Wallet balance "<<availble<<" is less than 1000000000000000]"<<endl;
    }
    {
        Wallet wallet = Wallet();
        big_long availble = 0;
        big_long low = pow(BUCKET_STEP,3), high = pow(BUCKET_STEP,4)-1000;
        
        //for(int i=0; i<10; i++){
        big_long value = rand() % low + high, total = 0;
        
        do{
            value = rand() % low + high;
            total += value;
            wallet.add(value);
        }while(total < WALLET_LIMIT+1);
        
        cout << "Test Case 1.9 ";
        availble = wallet.available();
        availble >= COIN_LIMIT-1 ? cout << "\tPASSED \u2714 " : cout << "\tFAILED \u2718 ";
        cout << "\t[ Wallet value " << availble;
        cout<<", rejected coin after "<<WALLET_LIMIT-1 <<" ]"<<endl;
    }
}
#endif /* AddTests_h */
