class MobilePhone{
public: 
    int number;  //the field element of the class
    bool stat; //this defines the switched on/switched off state of the mobile phone. true= switched on and false=switched off
    Exchange *base; //the base to which the mobile phone is connected
    MobilePhone(int num){
        number=num;
        stat=true;//originally sqitched on
    }
    bool status(){
        return stat;
    }
    void switchOn(){
        stat=true;
    }
    void switchOff(){
        stat=false;
    }
    Exchange* location(){
         return base;
     }

    void setLocation(Exchange *location){
        base=location;
    }
    
    //Function to check equality and == used in find
    bool equals(MobilePhone *other){
        return number==other->number;  //the two mobile phones are equal if their numbers are the same
    }
    bool operator == ( MobilePhone *other)
    {
        return number==other->number;
    }
};
