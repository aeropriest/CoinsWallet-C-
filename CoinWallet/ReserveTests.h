//
//  ReserveTests.h
//  HexTest
//
//  Created by homi on 20/7/2021.
//

#ifndef ReserveTests_h
#define ReserveTests_h

void ReserveTest(){

    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"Test coin reservation"<<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;

    {
        Wallet wallet = Wallet();
        
        cout << "Test Case 3.1 ";
        bool ret = wallet.reserve(100);
        !ret ? cout << "\tPASSED \u2714 " : cout << "\tFAILED \u2718 ";
        cout << "\t[ Reserving from empty wallet was rejected ]"<<endl;

        int sum = 0;
        for(int i=0; i<10; i++){
            wallet.add(i);
            sum += i;
        }
        
        cout << "Test Case 3.2 ";
        ret = wallet.reserve(-100);
        !ret ? cout << "\tPASSED \u2714 " : cout << "\tFAILED \u2718";
        cout << "\t[ Reserving negetive value was rejected ]"<<endl;


        cout << "Test Case 3.3 ";
        ret = wallet.reserve(WALLET_LIMIT);
        !ret ? cout << "\tPASSED \u2714 " : cout << "\tFAILED \u2718";
        cout << "\t[ Reserving more than wallet limit was rejected]"<<endl;
        
        
        cout << "Test Case 3.4 ";
        ret = wallet.reserve(20);
        wallet.available() !=  24 ? cout << "\tFAILED \u2718 " : cout << "\tPASSED \u2714 ";
        cout << "\t[ Balance after reserving coin worth 20 is "<<wallet.available()<< "]"<<endl;

        
        
        cout << "Test Case 3.5 ";
        ret = wallet.cancel_reserved();
        wallet.available() !=  sum ? cout << "\tFAILED \u2718 " : cout << "\tPASSED \u2714 ";
        cout << "\t[ Reservation cancelled, balance is "<<wallet.available()<< "]"<<endl;

        cout << "Test Case 3.6 ";
        ret = wallet.reserve(20);
        ret = wallet.spend_reserved();
        wallet.available() !=  24 ? cout << "\tFAILED \u2718 " : cout << "\tPASSED \u2714 ";
        cout << "\t[ Balance after spending reserved coin worth 20 is "<<wallet.available()<< "]"<<endl;

    }
}

#endif /* ReserveTests_h */
