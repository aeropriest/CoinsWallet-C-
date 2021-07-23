//
//  SpendTests.h
//  HexTest
//
//  Created by homi on 20/7/2021.
//

#ifndef SpendTests_h
#define SpendTests_h

void SpendTests(){

    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"Test coin spending"<<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;

    {
        Wallet wallet = Wallet();
        
        cout << "Test Case 2.1 ";
        bool ret = wallet.spend(100);
        ret ? cout << "\tFAILED \u2718 " : cout << "\tPASSED \u2714 ";
        cout << "\t[ Spending from empty wallet was rejected ]"<<endl;

        int sum = 0;
        for(int i=0; i<10; i++){
            wallet.add(i);
            sum += i;
        }
        cout << "Test Case 2.2 ";
        wallet.available() !=  sum ? cout << "\tFAILED \u2718 ! " : cout << "\tPASSED \u2714 ";
        
        cout << "\t[ Wallet balance of first 10 numbers is "<<wallet.available()<< "]"<<endl;

        cout << "Test Case 2.3 ";
        ret = wallet.spend(-100);
        ret ? cout << "\tFAILED \u2718 !" : cout << "\tPASSED \u2714 ";
        cout << "\t[ Spending negetive value was rejected ]"<<endl;


        cout << "Test Case 2.4 ";
        big_long spend = 22;
        big_long availabel = wallet.available();
        ret = wallet.spend(spend);
        !ret ? cout << "\tFAILED \u2718 !" : cout << "\tPASSED \u2714 ";
        cout << "\t[ Spending ("<<spend<<") less than wallet value "<<availabel<<" was approved]"<<endl;

        cout << "Test Case 2.5 ";
        spend = 55;
        availabel = wallet.available();
        ret = wallet.spend(spend);
        ret ? cout << "\tFAILED \u2718 !" : cout << "\tPASSED \u2714 ";
        cout << "\t[ Spending ("<<spend<<") more than wallet value "<<wallet.available()<<" was rejected]"<<endl;

    }
}

#endif /* SpendTests_h */
