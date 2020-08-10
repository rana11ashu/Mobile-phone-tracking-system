class Exchange
{
public:
    int number; 
    Exchange *par;
    list<Exchange*> children;
    MySet<MobilePhone*> m_set;
    

    Exchange(int num){
        number=num;
        par=NULL;
    }

    void setParent(Exchange *a){
         par=a;
    }

    Exchange* parent(){
          return par;}

    int numChildren(){
        return children.size();
    }

    Exchange* child(int i){
        auto it=children.begin();
        while(i--) it++;
         return *it;
     }

    bool isRoot(){
     return (par==NULL);
     }

    void addChild(Exchange *b){
        children.push_back(b);
        m_set=m_set.unionSet(b->m_set);
    }

    MySet<MobilePhone*> residentSet(){
        return m_set;//returns the resident set of the exchange which has all the mobile phones that come under this exchange;
    }
    
    //Function to check equality of two pointers
    bool equals(Exchange *other){
        return number==other->number;  //the two mobile phones are equal if their numbers are the same
    }

    //Operator overloading
    bool operator == ( Exchange *other)
    {
        return number==other->number;
    }
    
};