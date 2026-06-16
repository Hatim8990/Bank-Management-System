#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Account {
    int Accountno;
    char Name[100];
    char Type[50];
    float Balance;
};
Account accounts[100];
int totalaccounts =0;

void saveTofile() {
    ofstream file("accounts.dat", ios::binary | ios::trunc);
    if (!file.is_open()) {cout<<"Error: Could not save!"<<endl; return; }
    file.write((char*)&totalaccounts, sizeof(totalaccounts));
    file.write((char*)accounts, sizeof(Account) * totalaccounts);
    file.close();
}

void loadfromfile() {
    ifstream file("accounts.dat", ios::binary);
    if(!file.is_open()) { totalaccounts=0; return; }
    file.read((char*)&totalaccounts, sizeof(totalaccounts));
    file.read((char*)accounts, sizeof(Account)*totalaccounts);
    file.close();
}
void createaccount () {
    Account a;

    a.Accountno = 1001 + totalaccounts;

    cout<<"Enter Your Name: ";
    cin.ignore();
    cin.getline(a.Name,100);
    
    cout<<"Enter Account Type(Savings/Current):";
    cin.getline(a.Type,50);

    cout<<"Enter Initial Deposit Amount: ";
    cin>>a.Balance;
    
    accounts[totalaccounts] = a;
    totalaccounts++;
    saveTofile();

    cout<<"\n Account created Successfully!"<< endl;
    cout<<"Your Account Number is: "<<a.Accountno << endl;
}

void deposit() {
    int accNo;
    cout<<"\nEnter Account Number: ";
    cin>> accNo;

    int index = -1;
    for(int i = 0;i< totalaccounts; i++) {
        if (accounts[i].Accountno == accNo) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout<<"Account not found!" <<endl;
        return;
    }

    float amount;
    cout<<"Enter Amount to deposit: ";
    cin>> amount;

    if (amount <=0) {
        cout<<"invalid amount!"<<endl;
        return;
    }

    accounts[index].Balance += amount;
    saveTofile();
    cout<< "\nDeposit Successfull!" << endl;
    cout<< "New Balance: " << accounts[index].Balance << endl;

}

void withdraw() {
    int accNo;
    cout<< "\nEnter Account Number:  ";
    cin>>accNo;

    int index = -1;
    for(int i=0;i< totalaccounts;i++) {
        if (accounts[i].Accountno == accNo) {
            index = i;
            break;
        }
    }

    if (index == -1) {cout <<"Account not Found!" <<endl; return;}

    float amount;
    cout<< "Enter Amount to withdraw: ";
    cin>> amount;
    if (amount <=0) {cout << "Invalid amount!"<<endl;return;}
    if (amount > accounts[index].Balance) {cout <<"Insufficient balance!"<<endl; return;}

    accounts[index].Balance -= amount;
    saveTofile();
    cout<< "\nWithdrawl Successfull!"<< endl;
    cout<< "Reamining Balance:  Rs." << accounts[index].Balance << endl;

}

void checkbalance() {
    int accNo;
    cout <<"\nEnter Account Number:  ";
    cin>> accNo;

    int index = -1;
    for(int i=0;i<totalaccounts;i++) {
        if(accounts[i].Accountno == accNo) {
            index = i;
            break;
        }
    }
    if(index == -1) {
        cout << "Account not found!"<<endl;
        return;
    }
    cout<< "\n----Account Details----"<<endl;
    cout<<"Name  :"<<accounts[index].Name<<endl;
    cout<<"Type  :"<<accounts[index].Type<<endl;
    cout<<"Balance : Rs."<<accounts[index].Balance<<endl;

}

void transfermoney() {
    int fromAcc, toAcc;
    cout<<"\nEnter Your Account Number:  ";
    cin>> fromAcc;

    int fromindex = -1;
    for (int i = 0;i<totalaccounts;i++) {
        if (accounts[i].Accountno == fromAcc) {
            fromindex = i;
            break;

        }
    }
    if(fromindex == -1) {cout<<"Account not found!"<< endl; return;}

    cout<<"Enter Reciever Account Number:  ";
    cin>> toAcc;

    int toindex = -1;
    for(int i = 0; i < totalaccounts; i++) {
        if (accounts[i].Accountno == toAcc) {
            toindex = i;
            break;
        }
    }
    if(toindex == -1) {cout<< "Reciever Not Found!"<< endl; return; }
    if (fromAcc == toAcc) { cout << "Cannot Transfer to same account"<<endl; return;}

    float amount;
    cout<<"Enter Amount to transfer: ";
    cin >> amount;

    if (amount <= 0) {cout << "Invalid amount!" << endl; return; }
    if (amount >accounts[fromindex].Balance) { cout << "Insufficient Balance!" <<endl; return; }

    accounts[fromindex].Balance -= amount;
    accounts[toindex].Balance += amount;
    saveTofile();

    cout<< "\nTransfer Successful!"<< endl;
    cout<< "Rs." << amount <<" Sent to Account" << toAcc << endl;
    cout<< "Your Remaining Balance: Rs. " <<accounts[fromindex].Balance << endl;
    
}

int main () {
    loadfromfile();
    int choice;
    do{
        cout<<"\n====================="<<endl;
        cout<<"    BANK MANAGEMENT SYSTEM"<<endl;
        cout<<"==========================="<<endl;
        cout<<"1. Create Account"<<endl;
        cout<<"2. Deposit"<<endl;
        cout<<"3. Withdraw"<<endl;
        cout<<"4. Check Balance"<<endl;
        cout<<"5. Transfer Money"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"========================"<<endl;
        cout<<"Enter Your Choice:";
        cin>>choice;

        switch(choice){
            case 1: createaccount(); break;
            case 2: deposit ();break;
            case 3: withdraw (); break;
            case 4: checkbalance (); break;
            case 5: transfermoney (); break;
            case 6: cout<<"Goodbye!"<<endl;break;
            default: cout<< "Invalid choice! Try again. "<< endl;

        }

        
        }while (choice !=6);
        


    return 0;
}

