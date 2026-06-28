#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
using namespace std;

struct Product{
    int id;
    string name;
    string category;
    double price;
    int quantity;
    string supplier_name;
};

void saveToFile(const vector<Product>& inventory){
    ofstream file("inventory.csv");
    
    for(const auto& p: inventory){
        file<<p.id<<","<<p.name<<","<<p.category<<","<<p.price<<","<<p.quantity<<","<<p.supplier_name<<"\n";
    }
    file.close();
}
void loadFromFile(vector<Product>& inventory){
    ifstream file("inventory.csv");
    if(!file.is_open())return;

    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string token;
        Product p;
        getline(ss,token,',');p.id=stoi(token);
        getline(ss,p.name,',');
        getline(ss,p.category,',');
        getline(ss,token,',');p.price=stod(token);
        getline(ss,token,',');p.quantity=stoi(token);
        getline(ss,p.supplier_name,',');
        inventory.push_back(p);
    }
    file.close();
}
void addProduct(vector<Product>& inventory){
    Product p;
    cout<<"\nn---ADD NEW PRODUCT---\n";
    cout<<"Enter Product ID: ";cin>>p.id;
    cin.ignore();
    cout<<"Enter Product Name: ";getline(cin,p.name);
    cout<<"Enter Product Category: ";getline(cin,p.category);
    cout<<"Enter Product Price: ";cin>>p.price;
    cout<<"Enter Product Quantity: ";cin>>p.quantity;
    cin.ignore();
    cout<<"Enter Supplier Name: ";getline(cin,p.supplier_name);
    inventory.push_back(p);
    saveToFile(inventory);
    cout<<"Product added and saved successfully! \n";
}
void displayInventory(const vector<Product>& inventory){
    if(inventory.empty()){
        cout<<"No Products are available! \n";return;
    }
    cout<<left<<setw(5)<<"ID"<<setw(15)<<"NAME"<<setw(15)<<"CATEGORY"<<setw(10)<<"PRICE"<<setw(8)<<"QUANTITY"<<setw(15)<<"SUPPLIER NAME"<<setw(15)<<"STATUS"<<"\n";
    for(const auto& p: inventory){
        cout<<left<<setw(5)<<p.id<<setw(15)<<p.name<<setw(15)<<p.category<<setw(10)<<p.price<<setw(8)<<p.quantity<<setw(15)<<p.supplier_name<<setw(15);
        if(p.quantity==0)cout<<"Out Of Stock!"<<"\n";
        else if(p.quantity<=5)cout<<"Low Stock!"<<"\n";
        else cout<<"In Stock!"<<"\n";
    }
}
void sortInventory(vector<Product>& inventory){
    sort(inventory.begin(),inventory.end(),
    [](const Product& a,Product& b){
        return a.id<b.id;
    });
}
void searchProduct(vector<Product>& inventory){
    sortInventory(inventory);
    int ID;
    cout<<"Enter The Product ID: ";cin>>ID;
    bool found=false;
    int low=0,high=inventory.size()-1;
    while(low<=high){
        int mid=low+(high-low)/2;
        if(inventory[mid].id==ID){
            found=true;
            break;
        }
        else if(inventory[mid].id<ID)low=mid+1;
        else high=mid-1;
    }
    if(!found)cout<<"Product Not Found!\n";
    else cout<<"Found\n";
}
void deleteProduct(vector<Product>& inventory){
    if(inventory.size()==0){cout<<"Inventory is already empty!\n";return;}
    int id;
    cout<<"Enter The ID: ";cin>>id;
    size_t size_i=inventory.size();
    inventory.erase(
        remove_if(inventory.begin(),inventory.end(),
            [id](const Product& p){return p.id==id;}),
            inventory.end()
    );
    if(inventory.size()<size_i)cout<<"Product Deleted Successfully\n";
    else cout<<"Product Not Found To Delete!";

}

int main(){
    vector<Product>inventory;
    loadFromFile(inventory);
    int choice=-1;
    while(choice!=5){
        cout<<"1.Add Product\n2.Display Inventory\n3.Search Product\n4.Delete Product\n5.Exit\n";
        cin>>choice;
        switch(choice){
            case 1: addProduct(inventory);break;
            case 2: displayInventory(inventory);break;
            case 3: searchProduct(inventory);break;
            case 4: deleteProduct(inventory);break;
            case 5: cout<<"Goodbye!\n";break;
            default: cout<<"Invalid Option!\n";break;
        }
    }

    return 0;
}