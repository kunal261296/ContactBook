#include<iostream>
#include<fstream>
#include<cctype>
#include<stdlib.h>
#include<iomanip>
#include<ctime>
#include<windows.h>
using namespace std;
class account               //CLASS ACOUNT DECLARATION
{
    int acno;
    char name[50];
    int deposit;
    char type;
    public:
        void create_account();
        void show_account() const;
        void modify();
        void dep(int);
        void draw(int);
        void report() const;
        int retacno() const;
        int retdeposit() const;
        char rettype() const;
};

void account::create_account()
{
    char ch;
    srand(time(NULL));
    acno=rand()%10000;
    srand(time(NULL));
    cout<<"YOUR ACCOUNT NUMBER:"<<acno;
    cout<<"\n\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nEnter Type of The account C-Current  S-Savings : ";
    cin>>type;
    type=toupper(type);
    do{
        cout<<"\nEnter The Initial amount  : ";
        cin>>deposit;
        try{
            if(type=='C'||type=='c')
            {
                if(deposit<1000)
                throw 1;
            }
         if(type=='S'||type=='s')
            {
                if(deposit<500)
                throw ch;
            }
            int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow);
            MessageBox(NULL, "ACCOUNT CREATED SUCCESSFULLY", "SUCCESSFUL", MB_OK);
        }

        catch(int i){
            int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow);
            MessageBox(NULL, "DEPOSIT CANT BE LESS THAN 1000", "WARNING", MB_OK);
        }
        catch(const char a){
             int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow);
            MessageBox(NULL, "DEPOSIT CANT BE LESS THAN 500", "WARNING", MB_OK);
            }


        }while(deposit<1000);

}

void account::show_account() const
{
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nAccount Holder Name :"<<name;
    cout<<"\nType of Account : "<<type;
    cout<<"\nBalance amount : "<<deposit;
}
void account::modify()
{
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nModify Type of Account : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify Balance amount : ";
    cin>>deposit;
}
void account::dep(int x)
{
    deposit+=x;
}
void account::draw(int x)
{
    deposit=deposit-x;
}
void account::report() const
{

    cout<<acno<<" \t\t"<<name<<"\t\t "<<type<<"\t\t"<<deposit<<endl<<endl;
}
int account::retacno() const
{
    return acno;
}
int account::retdeposit() const
{
    return deposit;
}
char account::rettype() const
{
    return type;
}



class file:public account                   //CLASS FILE PUBLIC INHERITED FROM ACCOUNT CLASS
{
    account ac;
    ofstream outFile;
    ifstream inFile;
    fstream File;
    public:void write_account()
            {
                outFile.open("account.dat",ios::binary|ios::app);
                ac.create_account();
                outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
                outFile.close();
            }
            void display_sp(int n)
            {
                bool flag=false;
                inFile.open("account.dat",ios::binary);
                if(!inFile)
                {
                    cout<<"File could not be open. Press any Key...";
                    return;
                }
                cout<<"\nBALANCE DETAILS\n";

                    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
                    {
                        if(ac.retacno()==n)
                        {
                            ac.show_account();
                            flag=true;
                        }
                    }
                inFile.close();
                if(flag==false)
                cout<<"\n\nINVALID ACCOUNT NUMBER";
            }
    void modify_account(int n)
    {
        bool found=false;
        File.open("account.dat",ios::binary|ios::in|ios::out);
        if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        while(!File.eof() && found==false)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(account));
            if(ac.retacno()==n)
            {
                ac.show_account();
                cout<<"\nEnter The New Details of account"<<endl;
                ac.modify();
                int pos=(-1)*static_cast<int>(sizeof(account));
                File.seekp(pos,ios::cur);
                File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                cout<<"\n Details Updated";
                found=true;
              }
        }
        File.close();
        if(found==false)
        cout<<"\nn Record Not Found ";
    }
    void delete_account(int n)
    {
        inFile.open("account.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        outFile.open("Temp.dat",ios::binary);
        inFile.seekg(0,ios::beg);
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
        {
            if(ac.retacno()!=n)
            {
                outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
            }
        }
        inFile.close();
        outFile.close();
        remove("account.dat");
        rename("Temp.dat","account.dat");
        cout<<"\n\n\tRecord Deleted ..";
    }
    void display_all()
    {

        inFile.open("account.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
        cout<<"A/c no." <<"\t\t" <<" NAME"<<"\t\t"<<"Type"<<"\t\t"<< "Balance\n";
        cout<<"------------------------------------------------------\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
        {
            ac.report();
        }
        inFile.close();
    }

    void deposit_withdraw(int n, int option)
    {
        int amt;
        bool found=false;

        File.open("account.dat", ios::binary|ios::in|ios::out);
        if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        while(!File.eof() && found==false)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(account));
            if(ac.retacno()==n)
            {
                ac.show_account();
                if(option==1)
                {
                    cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                    cout<<"\n\nEnter The amount to be deposited:-";
                    cin>>amt;
                    ac.dep(amt);
                }
                if(option==2)
                {
                    cout<<"\n\n\tTO WITHDRAW AMOUNT ";
                    cout<<"\n\nEnter The amount to be withdraw:-";
                    cin>>amt;
                    int bal=ac.retdeposit()-amt;
                    if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                        cout<<"Insufficienct balance";

                    else
                        ac.draw(amt);
                }
                int pos=(-1)*static_cast<int>(sizeof(ac));
                File.seekp(pos,ios::cur);
                File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                cout<<"\n\n\t Record Updated";
                found=true;
               }
             }
        File.close();
        if(found==false)
        cout<<"\n\n Record Not Found ";
    }
};


int main()
{
    char ch;
    int num;
    file f1;
    system("color fc");
    do
    {
        system("cls");                                                                          //MENU DRIVEN PROGRAM
        cout<<"\t\tWELCOME TO BMS BANK\n";
        cout<<"\n\n1. NEW ACCOUNT";
        cout<<"\n\n2. DEPOSIT AMOUNT";
        cout<<"\n\n3. WITHDRAW AMOUNT";
        cout<<"\n\n4. BALANCE ENQUIRY";
        cout<<"\n\n5. ALL ACCOUNT HOLDER LIST";
        cout<<"\n\n6. CLOSE AN ACCOUNT";
        cout<<"\n\n7. MODIFY AN ACCOUNT";
        cout<<"\n\n8. EXIT";
        cout<<"\n\n\nENTER YOUR CHOICE:-";
        cin>>ch;
        system("cls");
        switch(ch)
        {
            case '1':
                f1.write_account();
                break;
            case '2':
                cout<<"\nEnter The account No. : "; cin>>num;
                f1.deposit_withdraw(num, 1);
                break;
            case '3':
                cout<<"\nEnter The account No. : "; cin>>num;
                f1.deposit_withdraw(num, 2);
                break;
            case '4':
                cout<<"\nEnter The account No. : "; cin>>num;
                f1.display_sp(num);
                break;
            case '5':
                f1.display_all();
                break;
            case '6':
                cout<<"\nEnter The account No. : "; cin>>num;
                f1.delete_account(num);
                break;
             case '7':
                cout<<"\nEnter The account No. : "; cin>>num;
                f1.modify_account(num);
                break;
             case '8':
                cout<<"\nThanks for banking with bms\n";
                exit(0);
             default :cout<<"a";
        }
        cin.ignore();
        cin.get();
    }while(ch!='8');
    return 0;
}


