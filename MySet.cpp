template <typename T> class MySet{
public:
    list<T> l;
    bool isEmpty() {
        return l.empty();
    }

    bool isMember(T o) {
        auto it = l.begin();  
        while(it!=l.end())
        {
            if(o->equals(*it)) return true;
            it++;
        }
       
        return false;  
    }

    void insert(T o)     
    {
        if(!isMember(o))     
            l.push_back(o);     
    }

    void deleteNode( T o)     
    {
        if(isEmpty())          
            cout<<"Empty Set"<<endl;        
        else //     else {
        {
            auto it = l.begin();  
            while(it!=l.end())
            {
                if(o->equals(*it)) break;
                it++;
            }
              if(it==l.end())  cout<<"Element Not Found";
              else  l.erase(it);
        }
     }

    MySet<T> unionSet(MySet<T> a)
    {
        MySet<T> u = *this;
        auto it = a.l.begin();
        while(it!=a.l.end())     
        {                                                           
            T obj = *it;            
            if(!u.isMember(obj))    
                 u.insert(obj);
            it++;
        }
        return u;
    }

    MySet<T> intersection(MySet<T> a)
    {
         MySet<T> u ;
        auto it = a.l.begin();
        while(it!=a.l.end())
        {
            T obj=*it;
            if(isMember(obj))  
                u.insert(obj);
            it++;
        }
        return u;
    }

    T find( T o)
    {
        auto it = l.begin();  
        while(it!=l.end())
        {
            if(o->equals(*it)) return *it;
            it++;
        }
        return NULL;  
    }
    void print();
};