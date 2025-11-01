#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string foodname;
    int quantity;
    float price;
    int data;
    Node *prev;
    Node *next;

    Node(int d, string fname, float p, int q = 0)
    {
        data = d;
        foodname = fname;
        price = p;
        quantity = q;
        prev = next = nullptr;
    }
};

Node *headc = nullptr;
Node *tailc = nullptr;
Node *heada = nullptr;
Node *taila = nullptr;
Node *head_s = nullptr;

void adminmenu()
{
    cout << "\n\t\t\t\t\t\t\t1. View total sales\n";
    cout << "\t\t\t\t\t\t\t2. Add new items in the order menu\n";
    cout << "\t\t\t\t\t\t\t3. Delete items from the order menu\n";
    cout << "\t\t\t\t\t\t\t4. Display order menu\n";
    cout << "\t\t\t\t\t\t\t5. Back To Main Menu \n\n";
    cout << "\t\t\t\t\t\t\t   Enter Your Choice --->";
}

void customermenu()
{
    cout << "\n\t\t\t\t\t\t\t1. Place your order\n";
    cout << "\t\t\t\t\t\t\t2. View your ordered items\n";
    cout << "\t\t\t\t\t\t\t3. Delete an item from order\n";
    cout << "\t\t\t\t\t\t\t4. Display final bill\n";
    cout << "\t\t\t\t\t\t\t5. Back To Main Menu \n\n";
    cout << "\t\t\t\t\t\t\t   Enter Your Choice --->";
}

Node *createadmin(Node *head, int data, string foodname, float price)
{
    Node *newnode = new Node(data, foodname, price);

    if (!head)
    {
        heada = taila = newnode;
    }
    else
    {
        taila->next = newnode;
        newnode->prev = taila;
        taila = newnode;
    }
    return heada;
}

Node *createcustomer(Node *head, int data, int quantity)
{
    Node *temp1 = heada;
    bool found = false;

    while (temp1)
    {
        if (temp1->data == data)
        {
            found = true;
            break;
        }
        temp1 = temp1->next;
    }

    if (found)
    {
        Node *newnode = new Node(data, temp1->foodname, quantity * temp1->price, quantity);

        if (!head)
        {
            headc = tailc = newnode;
        }
        else
        {
            tailc->next = newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }
    }
    else
    {
        cout << "\n\t\t\t\t\t\t\tThis item is not present in the menu!\n";
    }
    return headc;
}

void displayList(Node *head)
{
    Node *temp = head;
    if (!temp)
    {
        cout << "\n\t\t\t\t\t\t\t\tList is empty!!\n\n";
    }
    else
    {
        cout << "\n";
        while (temp)
        {
            if (temp->quantity == 0)
                cout << "\t\t\t\t\t\t\t" << temp->data << "\t" << temp->foodname << "\t" << temp->price << "\n";
            else
                cout << "\t\t\t\t\t\t\t" << temp->data << "\t" << temp->foodname << "\t" << temp->quantity << "\t" << temp->price << "\n";

            temp = temp->next;
        }
        cout << "\n";
    }
}

Node *totalsales(int data, int quantity)
{
    Node *temp1 = heada;
    while (temp1 && temp1->data != data)
    {
        temp1 = temp1->next;
    }

    if (!temp1)
        return head_s;

    Node *newnode = new Node(data, temp1->foodname, quantity * temp1->price, quantity);

    if (!head_s)
    {
        head_s = newnode;
    }
    else
    {
        Node *temp = head_s;
        bool found = false;
        while (temp->next)
        {
            if (temp->data == data)
            {
                found = true;
                break;
            }
            temp = temp->next;
        }

        if (found)
        {
            temp->quantity += newnode->quantity;
            temp->price += newnode->price;
            delete newnode;
        }
        else
        {
            temp->next = newnode;
        }
    }
    return head_s;
}

void calculatetotsales()
{
    Node *temp = headc;
    while (temp)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp = temp->next;
    }
}

Node *deleteNode(int data, Node *head, Node *&tail)
{
    if (!head)
    {
        cout << "\n\t\t\t\t\t\t\tList is empty\n";
        return head;
    }

    Node *temp = head;
    if (data == head->data)
    {
        head = head->next;
        if (head)
            head->prev = nullptr;
        delete temp;
    }
    else if (data == tail->data)
    {
        temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
    }
    else
    {
        while (temp && temp->data != data)
        {
            temp = temp->next;
        }
        if (temp)
        {
            temp->prev->next = temp->next;
            if (temp->next)
                temp->next->prev = temp->prev;
            delete temp;
        }
    }
    return head;
}

int deleteadmin()
{
    cout << "\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;

    Node *temp = heada;
    while (temp)
    {
        if (temp->data == num)
        {
            heada = deleteNode(num, heada, taila);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int deletecustomer()
{
    cout << "\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;

    Node *temp = headc;
    while (temp)
    {
        if (temp->data == num)
        {
            headc = deleteNode(num, headc, tailc);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void displaybill()
{
    displayList(headc);
    Node *temp = headc;
    float total_price = 0;
    while (temp)
    {
        total_price += temp->price;
        temp = temp->next;
    }
    cout << "\t\t\t\t\t\t\tTotal price: " << total_price << "\n";
}

Node *deleteList(Node *head)
{
    Node *temp = head;
    while (temp)
    {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
    return nullptr;
}

void admin()
{
    cout << "\n\t\t\t\t\t   ----------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t    ADMIN SECTION\n";
    cout << "\t\t\t\t\t   ----------------------------------------------\n";
    while (true)
    {
        adminmenu();
        int opt;
        cin >> opt;
        if (opt == 5)
            break;

        switch (opt)
        {
        case 1:
            displayList(head_s);
            break;
        case 2:
        {
            cout << "\n\t\t\t\t\t\t\tEnter serial no. of the food item: ";
            int num;
            cin >> num;
            bool exists = false;
            Node *temp = heada;
            while (temp)
            {
                if (temp->data == num)
                {
                    cout << "\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n";
                    exists = true;
                    break;
                }
                temp = temp->next;
            }
            if (exists)
                break;

            cout << "\t\t\t\t\t\t\tEnter food item name: ";
            string name;
            cin.ignore();
            getline(cin, name);
            cout << "\t\t\t\t\t\t\tEnter price: ";
            float price;
            cin >> price;
            heada = createadmin(heada, num, name, price);
            cout << "\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n";
            break;
        }
        case 3:
            if (deleteadmin())
            {
                cout << "\n\t\t\t\t\t\t### Updated list of food items menu ###\n";
                displayList(heada);
            }
            else
                cout << "\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n";
            break;
        case 4:
            cout << "\n\t\t\t\t\t\t\t   ### Order menu ###\n";
            displayList(heada);
            break;
        default:
            cout << "\n\t\t\t\t\t\tWrong Input !! Please choose valid option\n";
            break;
        }
    }
}

void customer()
{
    int flag = 0;
    cout << "\n\t\t\t\t\t   ----------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t    CUSTOMER SECTION\n";
    cout << "\t\t\t\t\t   ----------------------------------------------\n";
    while (true)
    {
        customermenu();
        int opt;
        cin >> opt;
        if (opt == 5)
            break;

        switch (opt)
        {
        case 1:
        {
            displayList(heada);
            cout << "\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ";
            int n;
            cin >> n;
            cout << "\t\t\t\t\t\tEnter quantity: ";
            int quantity;
            cin >> quantity;
            headc = createcustomer(headc, n, quantity);
            break;
        }
        case 2:
            cout << "\n\t\t\t\t\t\t\t  ### List of ordered items ###\n";
            displayList(headc);
            break;
        case 3:
            if (deletecustomer())
            {
                cout << "\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n";
                displayList(headc);
            }
            else
                cout << "\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n";
            break;
        case 4:
            calculatetotsales();
            cout << "\n\t\t\t\t\t\t\t  ### Final Bill ###\n";
            displaybill();
            headc = deleteList(headc);
            cout << "\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t";
            cin.ignore();
            cin.get();
            flag = 1;
            break;
        default:
            cout << "\n\t\t\t\t\t\tWrong Input !! Please choose valid option\n";
            break;
        }
        if (flag == 1)
            break;
    }
}

void mainmenu()
{
    cout << "\n                                 **************************************************************************\n";
    cout << "                                                     WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n";
    cout << "                                 **************************************************************************\n\n\n";
    cout << "\t\t\t\t\t\t\t1. ADMIN SECTION--> \n";
    cout << "\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n";
    cout << "\t\t\t\t\t\t\t3. Exit--> \n\n";
    cout << "\t\t\t\t\t\t\tEnter Your Choice --->";
}

int main()
{
    heada = createadmin(heada, 1, "Hot and Sour Soup", 100);
    heada = createadmin(heada, 2, "Manchow Soup", 200);
    heada = createadmin(heada, 3, "Manchurian Noodles", 150);
    heada = createadmin(heada, 4, "Fried Rice", 180);
    heada = createadmin(heada, 5, "Hakka Noodles", 80);

    while (true)
    {
        mainmenu();
        int choice;
        cin >> choice;

        if (choice == 3)
        {
            cout << "\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n";
            break;
        }

        switch (choice)
        {
        case 1:
            admin();
            break;
        case 2:
            customer();
            break;
        default:
            cout << "\n\t\t\t\t\t\tWrong Input !! Please choose valid option\n";
            break;
        }
    }
    return 0;
}
