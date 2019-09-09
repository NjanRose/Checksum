#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <conio.h>
#include <windows.h>
#include "Receiver_header.h"
using namespace std;

//ADDS 2 BINARY NUMBERS[here 16 bit datawords]: [IF CARRY GENERATED--- WRAPS IT AND THEN ONLY RETURNS SUM.
//This function is defined in receiver.h

//STRING DATA====>ASCII VALUE====>BINARY VALUE
string my_Binary(string s)
{
    string x="";
    int n = s.length();
    for (int i = 0; i <= n; i++)//char by char of string
    {
        int val = int(s[i]); //ASCII value
        string bin="";
        while (val > 0) //Normal way
        {
            (val % 2)? bin.push_back('1') :
            bin.push_back('0');
            val /= 2;
        }
        reverse(bin.begin(), bin.end());
        x+=bin;
    }
    return x;
}








//REPEATS A STRING 'n' NUMBER OF TIMES[used in code to fill '0' string in case the string not multiple of 16]
string repeat(string s, int n)
{
    string s1 = s;
    for (int i=1; i<n; i++)
        s += s1;
    return s;
}






int main()
{
    //Introduction
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"                                    ____     _   _     _____      ____     _  __    ____      _   _     __  __ "<<endl;
    cout<<"                                   / ___|   | | | |   | ____|    / ___|   | |/ /   / ___|    | | | |   |  \\/  |"<<endl;
    cout<<"                                  | |       | |_| |   |  _|     | |       |   /    \\___ \\    | | | |   | |\\/| |"<<endl;
    cout<<"                                  | |___    |  _  |   | |___    | |___    |   \\     ___) |   | |_| |   | |  | |"<<endl;
    cout<<"                                   \\____|   |_| |_|   |_____|    \\____|   |_|\\_\\   |____/     \\___/    |_|  |_|"<<endl<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<endl<<"                                       Demonstration of simple checksum method - 1's complement method"<<endl;




    //basic initializations
    string n;//Store user's original data
    string k;//Store BINARY form of data
    int len_of_k;//Length of binary string
    int new_len;//Length after appending required 0s
    int size_of_array;//size of array of 16 bit datawords
    string result=repeat("0",16);//store sum of addition of datawords
    string checksum="";//store checksum
    string send_data="";//final data to send to reciever with checksum attached


    //read user data
    cout<<endl<<endl<<"                                                             S E N D E R - S I D E :"<<endl;
    cout <<endl<<             "           STEP 1:    Enter the data   :    " ;
    cin >> n;
    k=my_Binary(n);
    cout<<endl<<endl<<endl<<  "                      Convert to binary: "<<k<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    getch();

    //fill 0s if binary string not multiple of 16
    len_of_k=k.length();
    if(len_of_k%16!=0)
    {
        k=repeat("0",16-len_of_k%16)+k;
    }


    //Divide into 16 bit datawords
    new_len=k.length();
    size_of_array=new_len/16;
    string data[size_of_array]= {" "};//STORES DATAWORDS
    int p=0;
    for(int i=0; i<size_of_array; i++)
    {
        data[i]=k.substr(p,16);
        p=p+16;
    }

    cout<<endl<<    "           STEP 2:    Divide into 16-bit datawords:              "<<data[0]<<endl;
    //printing datawords
    for(int i=1; i<size_of_array; i++)
        cout<<endl<<"                                                                 "<<data[i]<<"   "<<endl;
    cout<<          "                                                               + "<<endl;
    cout<<          "                                                               ----------------------"<<endl;
    //Add up the datawords[Wrap any carry if occurs]

    for(int i=0; i<size_of_array; i++)
    {
        result=add_my_bits(result,data[i]);
    }
    cout<<"           STEP 3:    Add the datawords(Wrap around extra bits): "<<result<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
   getch();

    //complement result for checksum
    for(int i=0;i<result.length();i++)
        {
            if(result[i]=='0')
                checksum+='1';
            else
                checksum+='0';
        }
    cout<<"           STEP 4:    Complement of added sum: "<<checksum<<endl<<endl;

    //printing checksum
    cout<<"           Hence,     required CHECKSUM      : "<<checksum<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;

    getch();
    cout<<"           NOW:Appending checksum to end of original data and SENDING."<<endl<<endl;
;
    //Append checksum to original data n send
    send_data=k+checksum;


    //printing final data to send
    cout<<"           SENDING DATA         :"<<send_data<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;

    getch();
    cout<<"       SENDER"<<endl;
    cout<<"      _________"<<endl;
    cout<<"     |          |"<<endl;
    cout<<"     |          |"<<endl;
    cout<<"     |__________|"<<endl;
    cout<<"         /__\\     ";
    for( int i=0;i< 8;i++)
    {
        cout<<"    ---->    ";
        //Sleep(1500);
    }
    cout<<endl<<endl<<"    REACHES  RECEIVER"<<endl;
    cout<<"      __________"<<endl;
    cout<<"     |          |"<<endl;
    cout<<"     |          |"<<endl;
    cout<<"     |__________|"<<endl;
    cout<<"         /__\\   "<<endl<<endl;Sleep(1550);
    cout<<"Successful transmission."<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    int r = receiver(send_data);
    return 0;
}
