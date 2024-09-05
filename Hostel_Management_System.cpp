#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<dos.h>
 
class hostel
{
    int room_no;
    char name[30];
    char address[50];
    char phone[10];
    
    public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
};
 
void hostel::main_menu()
{
    int choice;
    
    while(choice!=5)
    {
        clrscr();
        cout<<"\n\t\t\t\t*************";
        cout<<"\n\t\t\t\t* MAIN MENU *";
        cout<<"\n\t\t\t\t*************";
        cout<<"\n\n\n\t\t\t1.Book A Room";
    cout<<"\n\t\t\t2.Student Record";
        cout<<"\n\t\t\t3.Rooms Allotted";
        cout<<"\n\t\t\t4.Edit Record";
        cout<<"\n\t\t\t5.Exit";
        cout<<"\n\n\t\t\tEnter Your Choice: ";
        cin>>choice;
        
        switch(choice)
        {
            case 1: add();
                    break;
            case 2: display();
                    break;
            case 3: rooms();
                    break;
            case 4: edit();
                    break;
            case 5: break;
            default:
                    {
                        cout<<"\n\n\t\t\tWrong choice!!!";
                        cout<<"\n\t\t\tPress any key to continue!!";
                        getch();
                    }
        }
    }
}
 
void hostel::add()
{
    clrscr();
    int r,flag;
    ofstream fout("student.txt",ios::app);

    cout<<"\n Enter Customer Detalis";
    cout<<"\n **********************";
    cout<<"\n\n Room no: ";
    cin>>r;
    flag=check(r);

    if(flag)
    cout<<"\n Sorry..!!!Room is already booked";
    else
    {
    room_no=r;
    cout<<" Name: ";
    gets(name);
    cout<<" Address: ";
    gets(address);
    cout<<" Phone No: ";
    gets(phone);
    fout.write((char*)this,sizeof(hostel));
    cout<<"\n Room is booked!!!";
    }

    cout<<"\n Press any key to continue!!";
    getch();
    fout.close();
}

void hostel::display()
{
    clrscr();
    ifstream fin("student.txt",ios::in);
    int r,flag;
    cout<<"\n Enter room no: ";
    cin>>r;

    while(!fin.eof())
    {
    fin.read((char*)this,sizeof(hostel));
    if(room_no==r)
    {
        clrscr();
        cout<<"\n Cusromer Details";
        cout<<"\n ****************";
        cout<<"\n\n Room no: "<<room_no;
        cout<<"\n Name: "<<name;
        cout<<"\n Address: "<<address;
        cout<<"\n Phone no: "<<phone;
        flag=1;
        break;
    }
    }

    if(flag==0)
    cout<<"\n Sorry Room no. not found or vacant!!";

    cout<<"\n\n Press any key to continue!!";
    getch();
    fin.close();
}

void hostel::rooms()
{
    clrscr();
    ifstream fin("student.txt",ios::in);
    cout<<"\n\t\t\tList Of Rooms Allotted";
    cout<<"\n\t\t\t*********************";
    cout<<"\n\n Room No.\tName\t\tAddress\t\tPhone No.\n";

    while(!fin.eof())
    {
    fin.read((char*)this,sizeof(hostel));
    cout<<"\n\n "<<room_no<<"\t\t"<<name;
    cout<<"\t\t"<<address<<"\t\t"<<phone;
    }

    cout<<"\n\n\n\t\t\tPress any key to continue!!";
    getch();
    fin.close();
}

void hostel::edit()
{
    clrscr();
    int choice,r;

    cout<<"\n EDIT MENU";
    cout<<"\n *********";
    cout<<"\n\n 1.Modify Customer Record";
    cout<<"\n 2.Delete Customer Record";

    cout<<"\n Enter your choice: ";
    cin>>choice;

    clrscr();
    cout<<"\n Enter room no: ";
    cin>>r;

    switch(choice)
    {
    case 1: modify(r);
        break;
    case 2: delete_rec(r);
        break;
    default: cout<<"\n Wrong Choice!!";
    }

    cout<<"\n Press any key to continue!!!";
    getch();
}

int hostel::check(int r)
{
    int flag=0;
    ifstream fin("student.txt",ios::in);
    while(!fin.eof())
    {
    fin.read((char*)this,sizeof(hostel));
    if(room_no==r)
    {
        flag=1;
        break;
    }
    }

    fin.close();
    return(flag);
}

void hostel::modify(int r)
{
    long pos,flag=0;
    fstream file("student.txt",ios::in|ios::out|ios::binary);

    while(!file.eof())
    {
    pos=file.tellg();
    file.read((char*)this,sizeof(hostel));
    if(room_no==r)
    {
        cout<<"\n Enter New Details";
        cout<<"\n *****************";
        cout<<"\n Name: ";
        gets(name);
        cout<<" Address: ";
        gets(address);
        cout<<" Phone no: ";
        gets(phone);
        file.seekg(pos);
        file.write((char*)this,sizeof(hostel));
        cout<<"\n Record is modified!!";
        flag=1;
        break;
    }
    }

    if(flag==0)
    cout<<"\n Sorry Room no. not found or vacant!!";

    file.close();
}

void hostel::delete_rec(int r)
{
    int flag=0;
    char ch;
    ifstream fin("student.txt",ios::in);
    ofstream fout("temp.txt",ios::out);

    while(!fin.eof())
    {
    fin.read((char*)this,sizeof(hostel));
    if(room_no==r)
    {
        cout<<"\n Name: "<<name;
        cout<<"\n Address: "<<address;
        cout<<"\n Pone No: "<<phone;
        cout<<"\n\n Do you want to delete this record(y/n): ";
        cin>>ch;

        if(ch=='n')
        fout.write((char*)this,sizeof(hostel));

        flag=1;
    }
    else
        fout.write((char*)this,sizeof(hostel));
    }

    fin.close();
    fout.close();

    if(flag==0)
    cout<<"\n Sorry room no. not found or vacant!!";
    else
    {
    remove("student.txt");
    rename("temp.txt","student.txt");
    }
}

void main()
{
    hostel h;
    textmode(C80);
    textbackground(BLACK);
    textcolor(WHITE);

    clrscr();
    cout<<"\n\t\t\t****************************";
    cout<<"\n\t\t\t* HOSTEL MANAGEMENT PROJECT *";
    cout<<"\n\t\t\t****************************";
    sleep(1);

    cout<<"\n\n\n\n\t\tMade By:";
    sleep(1);
    cout<<" GPA SOFTWARE PVT LTD AWASARI...!!!";
    sleep(1);
    cout<<"\n\n\n\n\n\t\t\t\tPress any key to continue!!";
    getch();
    h.main_menu();
