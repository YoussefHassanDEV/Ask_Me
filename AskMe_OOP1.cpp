#include<iostream>
#include<vector>
using namespace std;
class Ques
{
    private:
    int Ques_ID;
    int User_ID;
    int To_User_ID;
    bool Anynomus;//0 is  normal 1 is anynomus
    string Contex;
    public:
    void Add(int Q_ID,int u_ID,int to_u_ID,bool A ,string Cont)
    {
        Ques_ID=Q_ID;
        User_ID=u_ID;
        To_User_ID=to_u_ID;
        Anynomus=A;
        Contex=Cont;
    }
    int current_Ques_ID()
    {
        return Ques_ID;
    }
    int current_user_Ques_ID()
    {
        return User_ID;
    }
    bool Ques_status()
    {
        return Anynomus;
    }
    string current_contex()
    {
        return Contex;
    }
    Ques()
    {
        int Ques_ID=-1;
        int User_ID=-1;
        int To_User_ID=-1;
        bool Anynomus;
        string Contex="";
    }
};
class Ans
{
    private:
    int user_ID;
    int ans_ID;
    int ques_ID;
    string Contex;
    public:
    void Add(int u_ID,int a_ID , int q_ID , string cont)
    {
        user_ID=u_ID;
        ans_ID=a_ID;
        ques_ID=q_ID;
        Contex=cont;
    }
    Ans()
    {
        user_ID=-1;
        ans_ID=-1;
        ques_ID=-1;
        Contex="";
    }

};
class User
{
    private:
    int ID;
    string Password;
    string Name;
    int len;
    public:
    void Add(int id,string password,string name)
    {
        ID=id;
        Password=password;
        Name=name;
    }
    void Inc_Ques()
    {
        len+=1;
    }
    bool name_user(string name)
    {
        if(name==Name)
            return true;
        else
            return false;
    }
    bool id_user(int id)
    {
        if(id==ID)
            return true;
        else
            return false;
    }
    bool password_user(string password)
    {
        if(password==Password)
            return true;
        else
            return false;
    }
    int current_user_id()
    {
        return ID;
    }
    int user_len()
    {
        return len;
    }
    string current_user_name()
    {
        return Name;
    }
    void Dec_Ques()
    {
        len-=1;
    }
    User()
    {
        ID=-1;
        Password="";
        Name="";
        len=0;
    }
};
User user1;
class System
{
    private:
    int Total_Users;
    int Total_Ques;
    int Total_Ans;
    int current_user_idx;
    int current_user_ID;
    string current_user_name;
    bool user_status=false;    
    bool menu_status=false;
    vector<User> user;
    vector<Ques> ques;
    vector<Ans> ans;
    vector<Ques>::iterator ptr;
    int Menu_1()
    {
        int choice=-1;
        while (choice==-1)
        {
            puts("Enter Ur Choice [1-2]");
            puts("1)Login Enter");
            puts("2)for Signup Enter");
            puts("3)Exit");
            cin>>choice;
            if(choice>3&&choice<1)
            {
                puts("Wrong Choice");
                choice=-1;
            }
        }
        return choice;
    }
    int Menu_2()
    {
        int choice=-1;
        while(choice==-1)
        {
            puts("Enter Ur Choice [1-8]");
            puts("1)Print Questions to Me");
            puts("2)Print Questions from Me");
            puts("3)Answer Question");
            puts("4)Delete Question");
            puts("5)Ask Questions");
            puts("6)List Systems Users");
            puts("7)Feed");
            puts("8)Logout");
            cin>>choice;
            if(choice>8&&choice<1)
            {
                puts("wrong choice try again");
                choice=-1;
            }
        }
        return choice;
    }
    bool Check_Name(string Name)
    {
        if(Total_Users==0)
            return false;
        for(int i=0;i<Total_Users;i++)
            if(user[i].name_user(Name))
                return true;
        return false;
    }
    void Signup()
    {
        string name,password;
        puts("Enter Name");
        cin>>name;
        if(Total_Users!=0||Check_Name(name))
        {
            puts("Already exist");
            return;
        }
        user.push_back(user1);
        puts("Enter Password");
        cin>>password;
        user[Total_Users].Add(Total_Users*Total_Users+1,password,name);
        Total_Users+=1;
    }
    int Find_idx_User_by_name(string Name)
    {
        if(Total_Users==0)
            return -1;
        for(int i=0;i<Total_Users;i++)
            if(user[i].name_user(Name)==true)
                return i;
            return -1;
    }
    int Find_idx_User_by_ID(int id)
    {
        if(Total_Users==0)
            return -1;
        for(int i=0;i<Total_Users;i++)
            if(user[i].id_user(id))
                return i;
        return -1;
    }
    bool Check_Password(int idx,string password)
    {
        if(user[idx].password_user(password))
            return true;
        return false;
    }
    void Signin()
    {
        puts("Enter Username");
        string Name;
        string Password;
        cin>>Name;
        if(Total_Users==0)
        {
            puts("User Does'nt Exist");
            return;
        }
        if(!Check_Name(Name))
        {
            puts("User Does'nt Exist");
            return;
        }
        puts("Enter Password");
        cin>>Password;
        current_user_idx=Find_idx_User_by_name(Name);
        if(!Check_Password(current_user_idx,Password))
        {
            puts("Wrong Password");
            return;
        }
        current_user_name=Name;
        current_user_ID=user[current_user_idx].current_user_id();
        user_status=true;
        puts("user Succesfuly Signed in");
        return;
    }
    void Logout()
    {
        user_status=false;
        puts("user successfully logout");
    }
    void Print_Questions_to_me()
    {
        cout<<"there are "<<Total_Ques-user[current_user_idx].user_len()<<" Questions \n";
        for(int i=0;i<Total_Ques;i++)
        {
            cout<<"Question ID :"<<ques[i].current_Ques_ID()<<' ';
            if(ques[i].Ques_status())
                cout<<"The Questioner is Anynomus ";
            else
                {
                    int idx;
                    idx=Find_idx_User_by_ID(ques[i].current_user_Ques_ID());
                    cout<<"The Questioner Name :"<<user[idx].current_user_name()<<' ';
                }
            cout<<"the Question :"<<ques[i].current_contex()<<"\n";
        }
    }
    void Print_Questions_from_me()
    {
        cout<<"U asked "<<user[current_user_idx].user_len()<<" questions \n";
        for(int i=0;i<Total_Ques;i++)
        {
            if(ques[i].current_user_Ques_ID()!=current_user_ID)
                continue;
            cout<<"asked user ID is "<<ques[i].current_user_Ques_ID()<<"Question :"<<ques[i].current_contex();
        }
    }
    void Answer_Question()
    {
        puts("Enter Question ID's u want Answer");
        int ID;
        cin>>ID;
        if(Total_Ques==0)
        {
            puts("No Questions Avaliable");
            return;
        }
        puts("Enter Ur Answer");
        string contex;
        cin>>contex;
        ans[Total_Ans].Add(current_user_ID,Total_Ans*Total_Ans+1,ID,contex);
        Total_Ans+=1;
    }
    int Find_Question_idx_By_ID(int id)
    {
        for(int i=0;i<Total_Ques;i++)
        {
            if(ques[i].current_Ques_ID()==id)
                return i;
        }
        return -1;
    }
    void Delete_Questions()
    {
        puts("Enter Question ID");
        int id1,id2;
        cin>>id1;
        if(user[current_user_idx].user_len()==0)
        {
            puts("No Questions Avaliable");
            return;
        }
        id2=Find_Question_idx_By_ID(id1);
        if(id2==-1)
        {
            puts("Question doesn't exist");
            return;
        }
        if(ques[id2].current_user_Ques_ID()!=current_user_ID)
        {
            puts("This Question Is'nt urs cant delete");
            return;
        }
        ques.erase(ptr+id2);
        Total_Ques-=1;
        user[current_user_idx].Dec_Ques();
        puts("Question deleted");
    }
    void Ask_Question()
    {
        puts("Ask Ur Question");
        string que;
        cin>>que;
        puts("Who u want to ask?");
        string  Name;
        cin>>Name;
        int asked_user_idx=Find_idx_User_by_name(Name);
        puts("Is it Anynomus(1) Or Normal(0)?");
        bool anynm;
        cin>>anynm;
        ques[Total_Ques].Add(Total_Ques*Total_Ques+1,current_user_ID,asked_user_idx,anynm,que);
        user[current_user_idx].Inc_Ques();
        Total_Ques+=1;
    }
    void List_sys_users()
    {
        cout<<"There are "<<Total_Users<<" Users in the system \n";
        for(int i=0;i<Total_Users;i++)
            cout<<"User Name :"<<user[i].current_user_name()<<" User ID :"<<user[i].current_user_id()<<"\n";
    }
    public:
    void Sys()
    {
        user_status=false;
        int choice;
        while(true)
        {
            menu_status=user_status;
            if(!user_status)
            {
                choice=Menu_1();
                if(choice==1)
                {
                    Signin();
                }
                else if(choice==2)
                    Signup();
                else if(choice ==3)
                {
                    puts("Thanks for using our app");
                    return;
                }
            }
            else
            {  
                choice=Menu_2();
                if(choice==1)
                    Print_Questions_to_me();
                else if(choice==2)
                    Print_Questions_from_me();
                else if(choice==3)
                    Answer_Question();
                else if(choice==4)
                    Delete_Questions();
                else if(choice==5)
                    Ask_Question();
                else if(choice==6)
                    List_sys_users();
                else if(choice==8)
                    Logout();
                
            }
        }
    }
    system()
    {
        Total_Users=0;
        Total_Ques=0;
        Total_Ans=0;
        current_user_idx=0;
        current_user_name="";
        current_user_ID=-1;
        ptr=ques.begin();
    }
};
int main()
{
    System s1;
    s1.Sys();
}