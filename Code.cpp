#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
string temp_name,temp_pass,temp_confirmpass,temp_email,temp_mobile;
string user_id,temp_id,temp_val,f_name,f_price;
string u_count,v_price;
string food_choicee,food_count,total;
int choice,food_choice,countt=0,caps=0,num=0,special_characters=0,s=0;
int qstate=0,i;
void swiggy();
void search_by_hotel();
void search_by_food();
void cart();
void insert_cart();
void update_cart();
void display_cart();
void delete_cart();
void total_amt();
void order();
void order_history();
void signup();
int account_check();
int validate();
void insertdatabase();
void login();
void insertdatabase()
{
     stringstream ss;
     ss<<"Insert INTO customer_details(Name,Password,Email,Phone_No) values('" <<temp_name<<"','"<<temp_pass<<"','"<<temp_email<<"','"<<temp_mobile<<"')";
     string query =ss.str();
     const char* q =query.c_str();
     qstate= mysql_query(conn,q);
     if(qstate == 0)
        {
            cout<<"\nSign up successfully....Please login to view your details...\n";
        }
        else
            cout<<"Record insertion in database failed"<<endl;
}

int main()
{
     conn = mysql_init(0);
     conn = mysql_real_connect(conn,"127.0.0.1","deena","dayalan","food_ordering",0,NULL,0);
     if(conn)
        cout<<""<<endl;
     else
        cout<<" Not connected";
    while(1)
	{
		cout<<"\n--------------------------------------------------\n";
		cout<<"\n\t\tWELCOME!!\n";
		cout<<"\n\tSimple Login/Signup Module\n";
		cout<<"\n1)LOGIN\n2)SIGNUP\n3)EXIT\nEnter Your Choice.......";
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				login();
				break;
			}
			case 2:
			{
				signup();
				break;
			}
			case 3:
			{
				exit(1);
			}
			default:
			{
				cout<<"\nPlease enter the valid choice\n";
				break;
			}
		}
	}
}
void login()
{
    cout<<"\n--------------------LOGIN-----------------------\n\n";
    cout<<"Enter your Email Address:\t";
    cin>>temp_email;
    cout<<"Enter your password:\t";
    cin>>temp_pass;
    qstate= mysql_query(conn,"SELECT * FROM customer_details");
    if(qstate==0)
    {
        int flag=0;
        res=mysql_store_result(conn);
        int count=mysql_num_fields(res);
        while(row = mysql_fetch_row(res))
        {
            if(row[3]==temp_email)
            {
                flag=1;
                if(row[2]==temp_pass)
                {
                    cout<<"\nLogin Successful...\n";
                    cout<<"\n\tWelcome "<<row[1];
                    cout<<endl;
                    user_id=row[0];
                    swiggy();
                    break;
                }
                else
                {
                    cout<<"\nInvalid Password..Please enter the crt password!!\n";
                    main();
                    break;
                }
            }
        }
        if(flag==0)
             {
                 cout<<"\nAccount doesn't exists..Please signup...";
                main();
             }
    }
}
void swiggy()
{
    cout<<"\nHere, We provide two ways of search for Food Order\n\n 1) Search_by_hotel\n 2) Search_by_food\n 3) View_Cart\n 4) View_order_history\n 5) Exit\n";
    cout<<"\n\nPlease Enter your choice:";
    cin>>choice;
    switch(choice)
        {
            case 1:
                {
                    search_by_hotel();
                    break;
                }
            case 2:
                {
                    search_by_food();
                    break;
                }
            case 3:
                {
                    display_cart();
                    break;
                }
            case 4:
                {
                    order_history();
                    break;
                }
            case 5:
                {
                    exit(1);
                }
            default:
                {
                    cout<<"Enter the valid choice....";
                    break;
                }
        }
}

void search_by_hotel()
{
    cout<<"\nList of available hotels...\n\n";
    cout<<"    "<<"Hotel_id"<<"\t  "<<"Hotel_name\n\n";
    qstate=mysql_query(conn,"select *from hotel_details");
    if(!qstate)
    {
        res=mysql_store_result(conn);
        int count=mysql_num_fields(res);
        while(row=mysql_fetch_row(res))
        {
            for(int i=0;i<count;i++)
                cout<<"\t"<<row[i];
            cout<<endl;
        }
        cout<<"\nEnter the hotel_id from the above(GoBack-0)";
        cin>>temp_id;
        if(temp_id[0]=='0')
            swiggy();
        else if(temp_id[0]>'0' && temp_id[0]<='5')
        {
            cout<<"List of available foods "<<endl<<endl;
            cout<<"     "<<"Food_id"<<"\t"<<"Food_name"<<"\t"<<"Food_price\n"<<endl;
            temp_id="select food_id,food_name,food_price from food_details where hotel_id= "+temp_id;
            qstate=mysql_query(conn,temp_id.c_str());

            if(!qstate)
            {
                res=mysql_store_result(conn);
                while(row=mysql_fetch_row(res))
                {
                    cout<<"\t"<<row[0]<<"\t";
                    cout.width(18);
                    cout<<left<<row[1];
                    cout.width(18);
                    cout<<left<<row[2];
                   cout<<endl;
                    temp_val=row[0];
                }
                    cout<<endl<<"Enter the food_id (Goback-0): ";
                    cin>>food_choice;
                    stringstream ss(temp_val);
                    int p;
                    ss>>p;
                    if(food_choice==0)
                        swiggy();
                    else if(food_choice>=p-2 && food_choice<=p)
                        {
                            cart();
                        }
                    else
                        {
                            cout<<"Enter a valid choice";
                            search_by_hotel();
                        }
            }
             else
            {
                cout<<"connection problem"<<endl;
            }
        }
        else
        {
            cout<<"\nEnter the valid hotel_id";
            search_by_hotel();
        }
    }
    else
        cout<<"Connection problem"<<endl;
}

void search_by_food()
{
     cout<<"    "<<"Food_id"<<"\t"<<"Food_name"<<"\t"<<"Food_price\n"<<endl;
     qstate=mysql_query(conn,"select food_id,food_name,food_price from food_details");
     if(!qstate)
     {
         res=mysql_store_result(conn);
         while(row=mysql_fetch_row(res))
         {
                cout<<"\t"<<row[0]<<"\t";
                cout.width(18);
                cout<<left<<row[1];
                cout.width(18);
                cout<<left<<row[2];
            cout<<endl;
         }
         cout<<"\nEnter the food_id (GoBack-0) :";
         cin>>food_choice;
         if(food_choice==0)
            swiggy();
         else if(food_choice>0 && food_choice<=15)
         {
             cart();
         }
         else
         {
             cout<<"Please enter valid choice \n";
             search_by_food();
         }

     }
     else
     {
         cout<<"connection problem"<<endl;
     }
}

void cart()
{
     cout<<"\nEnter the count of the food : ";
     cin>>food_count;
     stringstream s;
     s<<food_choice;
     s>>food_choicee;
      string sqlquery="select food_name,food_price from food_details where food_id= "+food_choicee;
        int qstate=mysql_query(conn,sqlquery.c_str());
        if(!qstate)
        {
             res=mysql_store_result(conn);
             while(row=mysql_fetch_row(res))
             {
                 f_name=row[0];
                 f_price=row[1];
             }
             insert_cart();

        }
        else
        {
            cout<<"Connection problem";
        }
}

void insert_cart()
{
    int flag=0;
    int qstate= mysql_query(conn,"SELECT * FROM order_details");
    if(qstate==0)
    {
        res=mysql_store_result(conn);
        while(row = mysql_fetch_row(res))
        {
            if(row[0]==user_id)
            {
                if(row[1]==food_choicee)
                {
                   flag=1;
                   u_count=row[3];
                   v_price=row[4];
                   update_cart();
                   break;
                }
            }
        }
    }
    if(flag==0)
    {
        int var1,var2;
        stringstream s1(food_count);
        s1>>var1;
        stringstream s2(f_price);
        s2>>var2;
        int temp=var1*var2;
        string price;
        stringstream s3;
        s3<<temp;
        s3>>price;
        stringstream ss;
        ss<<"insert into order_details(customer_id,food_id,food_name,food_quantity,food_price) values('" <<user_id<<"','"<<food_choicee<<"','"<<f_name<<"','"<<food_count<<"','"<<price<<"')";
        string query =ss.str();
        const char* q =query.c_str();
        qstate= mysql_query(conn,q);
        if(qstate == 0)
            {
                cout<< "Record Inserted in order table...."<<endl;
                swiggy();
            }
         else
             cout<<"Record insertion in database failed"<<endl;
    }
}

void update_cart()
{
    int var1,var2,var3;
    stringstream s1(food_count);
    s1>>var1;
    stringstream s2(f_price);
    s2>>var2;
    stringstream s3(u_count);
    s3>>var3;
    int temp1,temp2;
    temp1=var1+var3;
    temp2=temp1*var2;
    string alt_count,alt_price;
    stringstream s5;
    s5<<temp1;
    s5>>alt_count;
    stringstream s6;
    s6<<temp2;
    s6>>alt_price;
    string sqlquery="update order_details set food_quantity= "+alt_count+" ,food_price= "+alt_price+" WHERE customer_id= "+user_id+" and food_id= "+food_choicee;
    qstate=mysql_query(conn,sqlquery.c_str());
    if(!qstate)
    {
        cout<<"Updated\n";
        swiggy();
    }
    else
    {
        cout<<"COnnection problem";
        main();
    }
}
void display_cart()
{
    cout<<"\n\n----------------------------CART----------------------------\n\n";
    cout.width(16);
    cout<<left<<"Food_id";
    cout.width(15);
    cout<<left<<"Food_name";
    cout.width(15);
    cout<<left<<"Food_count";
    cout.width(15);
    cout<<left<<"Food_price\n";
    cout<<endl;
     string sqlquery="select food_id,food_name,food_quantity,food_price from order_details where customer_id= "+user_id;
     qstate=mysql_query(conn,sqlquery.c_str());
     if(!qstate)
     {
         int flag=0;
         res=mysql_store_result(conn);
         int count=mysql_num_fields(res);
         while(row=mysql_fetch_row(res))
         {
             flag=1;
            for(int i=0;i<count;i++)
          {
                cout.width(17);
                cout<<left<<row[i];
          }
            cout<<endl;
         }
         if(flag==0)
         {
             cout<<"\n\nOOPS!! Your cart is empty...Please select the food to order\n";
             swiggy();
         }
         total_amt();
     }
     else
     {
         cout<<"connection problem";
     }

}
void total_amt()
{
    string sqlquery="select sum(food_price) from order_details where customer_id= "+user_id;
     qstate=mysql_query(conn,sqlquery.c_str());
     if(!qstate)
     {
         res=mysql_store_result(conn);
         row=mysql_fetch_row(res);
         total=row[0];
         cout<<"\n\nYour Total Order Amount is: "<<total;
         cout<<endl;
         order();
     }
     else
     {
         cout<<"Connection problem";
     }
}

void order()
{
    int option;
    cout<<"\nDo you want to add more items in the cart(Y-1/N-0): ";
    cin>>choice;
    if(choice==1)
        swiggy();
    else if(choice==0)
    {
        cout<<"\nDo you wish to order(Y-1/N-0): ";
        cin>>option;
        if(option==1)
        {
            stringstream ss;
            ss<<"insert into order_table(customer_id,total_amt) values('" <<user_id<<"','"<<total<<"')";
            string query =ss.str();
            const char* q =query.c_str();
            int qstate= mysql_query(conn,q);
            if(!qstate)
                cout<<"Inserted";
            else
                cout<<"connection problem";
                    string sqlquery="select order_id,total_amt from order_table order by order_id desc limit 1";
                    int qs=mysql_query(conn,sqlquery.c_str());
                    cout<<"\n\n-------------BILLING----------------------\n";
                    cout<<endl<<"    "<<"ORDER_ID"<<"   "<<"TOTAL AMOUNT"<<endl<<endl;
                    if(!qs)
                    {
                        res=mysql_store_result(conn);
                        while(row=mysql_fetch_row(res))
                        {
                            cout<<"\t"<<row[0]<<"\t"<<row[1];
                        }
                        cout<<"\n\nThank You for your order!! Your Food is on the way. Welcome again!!\n\n";
                        exit(1);
                    }
                    else
                    {
                        cout<<"connection problem";
                    }

        }
        else if(option==0)
        {
            cout<<"\nDo you want to exit -1 or go back -0 :";
            cin>>choice;
            if(choice==1)
                exit(1);
            else if(choice==0)
            {
                cout<<"\nDo you want to delete the existing Cart(Y=1/N=0) :";
                cin>>option;
                if(option==1)
                {
                    delete_cart();
                }
            }

        }
        else
        {
            cout<<"\nEntered option is invalid\n";
            main();
        }
    }
    else
    {
        cout<<"\nyou entered the invalid choice...Pls enter the valid choice\n";
        order();
    }
}
void delete_cart()
{
    string sqlquery="delete from order_details where customer_id= "+user_id;
     qstate=mysql_query(conn,sqlquery.c_str());
     if(!qstate)
     {
         cout<<"\nExisting cart is deleted......\n";
         main();
     }
     else
     {
         cout<<"Delete connection problem";
     }
}

void order_history()
{
    cout<<"\n-------------------------ORDER HISTORY---------------------\n\n";
    string sqlquery="select order_id,total_amt from order_table where customer_id= "+user_id;
     qstate=mysql_query(conn,sqlquery.c_str());
     cout<<"    "<<"ORDER_ID"<<"    "<<"TOTAL AMOUNT"<<endl;
     int flag=0;
     if(!qstate)
     {
         res=mysql_store_result(conn);
         int count=mysql_num_fields(res);
         while(row=mysql_fetch_row(res))
         {
             flag=1;
            for(int i=0;i<count;i++)
                cout<<"\t"<<row[i];
            cout<<endl;
         }
     }
     if(flag==0)
     {
         cout<<"\nOOPs you didn't order anything....Please order the food\n";
         swiggy();
     }
     swiggy();
}
void signup()
{
    int a,b;
    cout<<"\n--------SIGNUP--------\n\n";
    cout<<"Enter your Name:\t";
    cin>>temp_name;
    cout<<"Enter your password:\t";
    cin>>temp_pass;
    cout<<"Confirm your password:\t";
    cin>>temp_confirmpass;
    cout<<"Enter your Email Address:\t";
    cin>>temp_email;
    cout<<"Enter your Mobile number:\t";
    cin>>temp_mobile;
    a=account_check();
    b=validate();
    if(a==1 && b==1)
    {
        insertdatabase();
    }
}

int account_check()
{
    qstate=0;
    qstate= mysql_query(conn,"SELECT Email,Password FROM customer_details");
    if(qstate==0)
    {
        res=mysql_store_result(conn);
        while(row = mysql_fetch_row(res))
        {
            if(row[0]==temp_email)
            {
                if(row[1]==temp_pass)
                {
                    cout<<"\nAccount already existed...Please login!!\n";
                    main();
                }
                else
                {
                    cout<<"\nAccount already existed with this mail Id...Please login!!\n";
                    main();
                }
            }
        }
        return 1;
    }
}

int validate()
{
    int num=0,special_characters=0;
    for(i=0;temp_name[i]!='\0';i++)
    {
        if(!((temp_name[i]>='a' && temp_name[i]<='z')|| (temp_name[i]>='A' && temp_name[i]<='Z')))
        {
            countt=0;
            cout<<"\n\nInvalid Name....Please enter the valid name.....\n\n";
            main();
        }
        else
            countt=1;
    }
    if(countt==1)
    {
        caps=0;s=0;num=0;special_characters=0;
        for(i=0;temp_pass[i]!='\0';i++)
        {
            if(temp_pass[i]>='A' && temp_pass[i]<='Z')
                caps++;
            else if(temp_pass[i]>='a' && temp_pass[i]<='z')
                s++;
            else if(temp_pass[i]=='@' || temp_pass[i]=='#' || temp_pass[i]=='&' || temp_pass[i]=='*' || temp_pass[i]=='.')
                special_characters++;
            else if(temp_pass[i]>='0' && temp_pass[i]<='9')
                num++;
        }
        if(caps>=1 && s>=3 && special_characters>=1 && num>=3)
        {
            countt=1;
        }
        else
        {
            countt=0;
            cout<<"\n\nThe password you enter is weak...Please enter the strong password....\n\n";
            main();
        }
    }
    if(countt==1)
    {
        for(i=0;temp_pass[i]!='\0';i++)
        {
            if(temp_pass[i]!=temp_confirmpass[i])
            {
                countt=0;
                cout<<"\n Password did not match...Please try again!!";
                main();
                break;
            }
            else
                countt=1;
        }
    }
    if(countt==1)
    {
        int at=0,dot=0;
        s=0;num=0;
        for(i=0;temp_email[i]!='\0';i++)
        {
            if(temp_email[i]=='@')
                at++;
            else if(temp_email[i]=='.')
                dot++;
            else if(temp_email[i]>='a' && temp_email[i]<='z')
                s++;
            else if(temp_email[i]>='0' && temp_email[i]<='9')
                num++;
            else
            {
                cout<<"\nEnter valid mail address...\n";
                main();
            }
        }
        if(at==1 && dot==1 && s>=5)
            {
                countt=1;
            }
        else
        {
            countt=0;
            cout<<"\nPlease enter the valid mail address...\n";
            main();
        }
    }
    if(countt==1)
    {
        num=0;
        for(i=0;temp_mobile[i]!='\0';i++)
        {
            if(!(temp_mobile[i]>='0' && temp_mobile[i]<='9'))
                {
                    cout<<"Enter valid number";
                    main();
                }
                else
                    num++;
        }
        if(num==10 &&temp_mobile[0]!='0')
        {
            return 1;
        }
        else
        {
            cout<<"\nPlease enter the valid Mobile number...\n";
            main();
        }
    }
}




