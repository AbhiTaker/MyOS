/* Directory Tree Structure in C++ */
#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;
typedef long long int ll;

struct node{
    vector<ll> dir;
    set<string> file;
};

node List[1000];
vector<string> path;
map<string, ll> mymap;
map<ll, string> mymap2;
string s,s2;
ll cnt=0,vis[1000],flag =0;

void path_store(){
    /* To extract the path of folder/file from string */

    for(ll i=0; i<s.size(); i++){
        string s3="";
        while(s[i]!='/' && i<s.size()){
            s3 += s[i];
            i++;
        }
        path.push_back(s3);
    }
}

void path_print(){
    /* Print the path of folder/file */

    for(ll i=0; i<path.size(); i++)
        cout<<path[i]<<"/";
    cout<<"\n";
}

void Add(ll typ){
    /* To add a file/directory to already existing directory */

    if(typ==1){
        /* for adding directory */
        cnt++;
        mymap[s2] = cnt;
        mymap2[cnt] = s2;
        ll last = mymap[path[path.size()-1]];
        List[last].dir.push_back(cnt);
    }
    else{
        /* for adding file */
        ll last = mymap[path[path.size()-1]];
        List[last].file.insert(s2);
    }

}

void Search(ll x, ll typ){
    /* for searching file/directory (DFS) */

    vis[x] = 1;
    if(typ == 1 && mymap2[x] == s2){
        flag = 1;
        return;
    }
    path.push_back(mymap2[x]);
    if(typ==2 && List[x].file.find(s2)!=List[x].file.end()){
        flag = 1;
        return ;
    }

    for(ll i=0; i<List[x].dir.size(); i++){
        ll node = List[x].dir[i];

        if(!vis[node]){
            Search(node, typ);
            if(flag)
                break;

            path.erase(path.begin() + path.size()-1);
        }
    }

    if(!flag)
        path.erase(path.begin() + path.size()-1);
}

void Remove(ll x, ll typ){
    /* for removing file/directory */

    vis[x] = 1;
    if(typ == 1 && mymap2[x]==s2){
        flag = 1;
        return;
    }
    if(typ==2 && List[x].file.find(s2)!=List[x].file.end()){
        flag = 1;
        List[x].file.erase(List[x].file.find(s2));
        return ;
    }

    for(ll i=0; i<List[x].dir.size(); i++){
        ll node = List[x].dir[i];

        if(!vis[node]){
            Remove(node, typ);
            if(flag==1 && typ==1){
                 flag = 3;
                 List[x].dir.erase(List[x].dir.begin() + i);
                 break;
             }
        }
    }
}

void Print(ll x, ll space){
    /* To print whole directory structure*/

    vis[x] = 1;
    for(ll i=0; i<space; i++)
        cout<<" ";
    cout<<mymap2[x]<<"/ \n";

    set<string>:: iterator it;
    for( it = List[x].file.begin(); it!=List[x].file.end(); it++){

        for(ll j=0; j<space+4; j++)
            cout<<" ";
        cout<<*it<<"\n";
    }

    for(ll i=0; i<List[x].dir.size(); i++){
        ll node = List[x].dir[i];

        if(!vis[node]){
           Print(node, space+4);
        }
    }
}

void Rename(ll x, ll typ){
    /* for renaming file/direcotry */

    if(typ==1 && mymap2[x]==s){
        flag = 1;
        mymap2[x] = s2;
        mymap[s2] = x;
        return ;
    }

    if(typ==2 && List[x].file.find(s)!=List[x].file.end()){
        flag=1;
        List[x].file.erase(List[x].file.find(s));
        List[x].file.insert(s2);
        return ;
    }

    for(ll i=0; i<List[x].dir.size(); i++){
        ll node = List[x].dir[i];

        if(!vis[node]){
           Rename(node, typ);
           if(flag)
            break;
        }
    }
}

int main()
{
    cout<<"Enter the operation you want to perform :\n";
    cout<<"1) Add directory   2) search directory 3)add file\n";
    cout<<"4) search file  5) remove directory 6)remove file\n";
    cout<<"7) List    8) rename file 9)rename directory\n";

    while(1){

        cout<<"\n";
        ll typ;
        path.clear(); flag = 0;
        fill(vis, vis+1000, 0);
        cout<<"Enter the type of operation :\n";
        cin>>typ;

        if(typ==1){
            cout<<"Enter the path of directory : \n";
            cin>>s;
            cout<<"Enter the name of directory to create: \n";
            cin>>s2;
            if(mymap.empty())
            {
                cnt++;
                mymap[s2] = cnt;
                mymap2[cnt] = s2;
                continue;
            }
            path_store();
            Add(1);
        }
        if(typ==2){
            cout<<"Enter the name of directory to search: \n";
            cin>>s2;
            Search(1, 1);
             if(!flag)
                cout<<"directory does not exist\n";
            else{
                cout<<"The path of directory : \n";
                path_print();
            }
        }
        if(typ==3){
            cout<<"Enter the path of directory : \n";
            cin>>s;
            cout<<"Enter the name of file to create : \n";
            cin>>s2;
            path_store();
            Add(2);
        }
        if(typ==4){
            cout<<"Enter the name of file to search : \n";
            cin>>s2;
            Search(1, 2);
            if(!flag)
                cout<<"File does not exist\n";
            else{
                cout<<"The path of directory : \n";
                path_print();
            }
        }
        if(typ==5){
          cout<<"Enter the name of directory to delete: \n";
          cin>>s2;
          Remove(1, 1);
        }
        if(typ==6){
          cout<<"Enter the name of file to delete: \n";
          cin>>s2;
          Remove(1, 2);
        }
        if(typ==7){
            cout<<"\n";
            Print(1, 0);
        }
        if(typ==8){
            cout<<"Enter the name of file to rename :\n";
            cin>>s;
            cout<<"Enter the new name of file:\n";
            cin>>s2;
            Rename(1, 2);
        }
        if(typ==9){
            cout<<"Enter the name of directory to rename :\n";
            cin>>s;
            cout<<"Enter the new name of directory:\n";
            cin>>s2;
            Rename(1, 1);
        }

    }

    return 0;
}
