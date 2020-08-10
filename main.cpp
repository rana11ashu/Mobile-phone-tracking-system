#include<bits/stdc++.h>
using namespace std;

class Exchange;
class MobilePhone;
template <typename T> class MySet;


#include"MySet.cpp"
#include"Exchange.cpp"
#include"MobilePhone.cpp"
#include"RoutingMapTree.cpp"
#include"Debug.cpp"

int main()
{
    //cout<<"Yeah its working go ahead"<<endl<<endl;
    RoutingMapTree r;
    for(int loop=0;loop<150;loop++)
    {
        string s; getline(cin,s);
        //cout<<s<<"\t\t"<<
        string temp=r.performAction(s);
        if(temp=="") cout<<s<<endl;
        cout<<r.performAction(s);
        //<<endl;
        //r.print();
        //cout<<endl;
    }


    // MySet<check> temp;
    // check obj(1,2,3); 
    // temp.insert(obj);

//FOR MYSET TESTING
    // MySet<int> temp;
    // cout<<temp.isEmpty()<<" ";  for(int i=0;i<10;i++) temp.insert(i);   cout<<temp.isEmpty()<<endl;
    // cout<<temp.isMember(5)<<" ";   temp.deleteNode(5);  cout<<temp.isMember(5)<<endl;
    
    // MySet<int> temp2;
    // for(int i=5;i<15;i++) temp2.insert(i); 

    // MySet<int> temp3=    temp.unionSet(temp2); 
    // MySet<int> temp4=    temp.intersection(temp2);

    // temp.print();
    // temp2.print();
    // temp3.print(); 
    // temp4.print();
    // cout<<endl; 





}