class RoutingMapTree
{
public:   
    Exchange *root;
    MySet<MobilePhone*> all_phones;

//Constructors
    RoutingMapTree()
    {   
        root=new Exchange(0);
    }

    RoutingMapTree(Exchange *e)
    {
        root =e;
    }


//Depth-first search
    bool containsNode(Exchange *root, Exchange *a)
    {
        if(root->equals(a)) return true;
        if(root->numChildren()==0) return false;

        for(int i=0;i<root->numChildren();i++)
        {
            if(containsNode(root->child(i), a) ) return true;
        }
        return false;
    }
//Depth-first search
    Exchange* NodeInTree(Exchange *root, Exchange *a)
    {
        if(root->equals(a)) return root;
        if(root->numChildren()==0) return NULL;

        bool flag = false;
        for(int i=0;i<root->numChildren(); i++)
        {
            Exchange *temp=NodeInTree(root->child(i),a) ;
            if(temp) return temp;
        }
        return NULL;
    }

//Depth-first search
    void switchOff(MobilePhone* a, Exchange *root)
    {
        if(root->numChildren()==0)
        {
            MobilePhone *existing_phone=root->m_set.find(a);
            existing_phone->switchOff();
            return;
        }
        else
        {
            for(int i=0;i<root->numChildren();i++)
            {
                if(root->child(i)->m_set.isMember(a))
                {
                    switchOff(a,root->child(i));
                    return;
                }
            }
        }
    }

//To Move phone from one exchange to another
    void movePhone(MobilePhone *a, Exchange *b)
    {
        MobilePhone *real_phone= root->m_set.find(a);
        Exchange *initial_real_exchange = real_phone->location();
        Exchange *final_real_exchange = NodeInTree(root,b);

        while(initial_real_exchange)
        {
            initial_real_exchange->m_set.deleteNode(real_phone);
            initial_real_exchange=initial_real_exchange->parent();
        }

        real_phone->setLocation(final_real_exchange);
        while(final_real_exchange)
        {
            final_real_exchange->m_set.insert(real_phone);
            final_real_exchange=final_real_exchange->parent();
        }

    }

    Exchange* lowestRouter(Exchange* a, Exchange* b)
    {
        while(!a->equals(b))
        {
            a=a->parent();
            b=b->parent();
        }
        return a;
    }

    MySet<Exchange*> routeCallPath(MobilePhone *phone_a, MobilePhone *phone_b)
    {
        Exchange *a= phone_a->location();
        Exchange *b= phone_b->location();
        
        MySet<Exchange*> list_a, list_b;
        while(  !(a->equals(b))  )
        {
            list_a.insert(a);
            list_b.insert(b);
            a=a->parent();
            b=b->parent();
        }

        list_a.insert(b);
        for(auto i:list_b.l)
        {
            list_a.insert(i);
        }
        return list_a;
    }

//Main Function handling all kind off inputs
    string performAction(string message)
    {
        int i=0;
        while(message[i]!=' '){ i++; }
        string command=message.substr(0,i);
        if(command=="addExchange")
        {
            int j=i+1;
            while(message[j]!=' ') j++;
            int a=stoi(message.substr(i+1,j-i+1));
            int b=stoi(message.substr(j+1));
    
            Exchange *a_temp= new Exchange(a);
            Exchange *b_temp = new Exchange(b);
            if(containsNode(root, a_temp))
            {
                //cout<<"continsNode"<<endl;
                Exchange *real_parent=NodeInTree(root,a_temp);
                b_temp->setParent(real_parent);
                real_parent->addChild(b_temp);
            }
            else
                return "Parent do not exist\n";
        }

        if(command=="switchOnMobile")
        {
            int j=i+1; 
            while(message[j]!=' ') j++;
            int mob_num_identifier=stoi(message.substr(i+1,j-i+1));
            int mob_exchange_identifier=stoi(message.substr(j+1));
            //cout<<endl<<mob_num_identifier<<" " <<mob_exchange_identifier<<endl;

            Exchange *a_temp = new Exchange(mob_exchange_identifier);

            if(containsNode(root,a_temp))
            {   
                Exchange *real_parent=NodeInTree(root,a_temp);
                MobilePhone *phone_temp=  new MobilePhone(mob_num_identifier);
                //cout<<real_parent->m_set.isMember(phone_temp)<<" ";
                if( real_parent->m_set.isMember(phone_temp) )
                {
                    MobilePhone *existing_phone = real_parent->m_set.find(phone_temp);
                    //cout<<phone_temp->number<<" ";
                    existing_phone->switchOn();
                }
                else
                {
                    phone_temp->setLocation(real_parent);
                    while(real_parent)
                    {
                        real_parent->m_set.insert(phone_temp);
                        real_parent=real_parent->parent();
                    }
                    all_phones=root->m_set;
                }
            }
            else return "Mobile Base/Exchange in invalid/n";
        }


        if(command=="switchOffMobile")
        {
            int mob_num_identifier = stoi(message.substr(i+1));
            MobilePhone* temp_phone =new MobilePhone(mob_num_identifier);
            if(root->m_set.isMember(temp_phone))
            {
                switchOff(temp_phone, root);
            }
            else return "Input number " + to_string(mob_num_identifier)+" do not exist\n";
        }

        if(command=="queryNthChild")
        {
            int j=i+1; 
            while(message[j]!=' ') j++;
            int exchange_identifier=stoi(message.substr(i+1,j-i+1));
            int child_num=stoi(message.substr(j+1));
            
            Exchange* a_temp = new Exchange(exchange_identifier);
            if(containsNode(root,a_temp))
            {
                Exchange *real_exchange=NodeInTree(root,a_temp);
                if(real_exchange==NULL) return "This should be a bug\n";
                string ans = message + ": ";
                if(real_exchange->numChildren()<=child_num) return "Child Overflow\n";

                ans= ans + to_string(real_exchange->child(child_num)->number);
                return ans+"\n";

            }
            return "Query Exchange do not Exist\n";
        }

        if(command == "queryMobilePhoneSet")
        {
            int exchange_identifier = stoi(message.substr(i+1));
            string ans= message +": ";

            Exchange *a_temp = new Exchange(exchange_identifier);
            if(containsNode(root,a_temp))
            {
                Exchange *real_exchange = NodeInTree(root,a_temp);
                for(auto i:real_exchange->m_set.l)
                {
                    //cout<<i->status()<<" "<<i->number<<"    ";
                    if(i->status()) ans=ans+to_string(i->number)+" ";
                }
                return ans+"\n";
            }
            return "Query Exchange does not exist\n";
        }

        if(command == "findPhone")
        {
            int mob_num_identifier = stoi(message.substr(i+1));
            string ans= message + ": ";

            MobilePhone *a_temp=new MobilePhone(mob_num_identifier);
            MobilePhone *real_phone = root->m_set.find(a_temp);
            if(real_phone)
            {
                if(real_phone->status())
                    ans=ans+ to_string(real_phone->location()->number);
                else ans="Phone is switched off";
                return ans+"\n";
            }
            return "No such phone exist\n";
        }

        if(command=="movePhone")
        {
            int j=i+1; 
            while(message[j]!=' ') j++;
            int phone_num_identifier=stoi(message.substr(i+1,j-i+1));
            int exchange_identifier=stoi(message.substr(j+1));
            MobilePhone *temp_phone = new MobilePhone(phone_num_identifier);
            Exchange *a_temp= new Exchange(exchange_identifier);
               
            if(containsNode(root,a_temp) && root->m_set.isMember(temp_phone))
            {
                 movePhone(temp_phone,a_temp);
            }
            else 
                return "Exchange/Phone Combination do not exist\n";
        }

        if(command=="lowestRouter")
        {
            int j=i+1; 
            while(message[j]!=' ') j++;
            int exchange_1_identifier=stoi(message.substr(i+1,j-i+1));
            int exchange_2_identifier=stoi(message.substr(j+1));

            Exchange *a_temp = new Exchange(exchange_1_identifier);            
            Exchange *b_temp = new Exchange(exchange_2_identifier);

            Exchange *real_1 = NodeInTree(root,a_temp);            
            Exchange *real_2 = NodeInTree(root,b_temp);
            Exchange *LCA = lowestRouter(real_1, real_2);            
            
            string ans=message +": " + to_string(LCA->number);
            return ans+"\n";
        }

        if(command=="findCallPath")
        {
            int j=i+1; 
            while(message[j]!=' ') j++;
            int mob_1_identifier=stoi(message.substr(i+1,j-i+1));
            int mob_2_identifier=stoi(message.substr(j+1));
            //cout<<mob_1_identifier<<" "<<mob_2_identifier<<" "; 

            MobilePhone *temp_phone_1= new MobilePhone(mob_1_identifier);
            MobilePhone *temp_phone_2 =new MobilePhone(mob_2_identifier);

            if(!root->m_set.isMember(temp_phone_1) || !root->m_set.isMember(temp_phone_2))
                return "Number do not exist\n";


            MobilePhone *real_phone_1 = root->m_set.find(temp_phone_1);
            MobilePhone *real_phone_2 = root->m_set.find(temp_phone_2);



            if(!real_phone_1->status() || !real_phone_2->status()  ) return "Mobile Phone is switched off\n";

            // cout<<real_phone_1->number<<" "<<real_phone_1->location()->number<<"    "; 
            // cout<<real_phone_2->number<<" "<<real_phone_2->location()->number; 


            MySet<Exchange*> path = routeCallPath(real_phone_1, real_phone_2);
            string ans=message+": ";
            for(auto i:path.l)
            {
                ans=ans+to_string(i->number)+" ";
            }
            return ans+"\n";
        }
        return "";
    }

    void print();
    

};