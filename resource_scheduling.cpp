#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct node{
    int id,state,arv,use,resrc, start;
    node()
    {
        state = -1;
    }
};

node List[1000];
int n;

void display(int ctr)
{
    cout<<"\n TASKS STATE AT TIME : "<<ctr<<"\n";
    for(int i=0; i<n; i++)
    {
       if(ctr<List[i].arv)
            break;
        if(List[i].state ==1)
        {
            cout<<"id - state - arrival time - start time - end time : \n";
            cout<<"P"<<List[i].id<<" - COMPLETE - "<<List[i].arv<<"  -   "<<List[i].start<<"    -  "<<List[i].start + List[i].use<<"\n";
        }
        else if(List[i].state ==2 )
        {
             cout<<"id - state - arrival time - start time : \n";
             cout<<"P"<<List[i].id<<" - RUNNING    -   "<<List[i].arv<<"    -    "<<List[i].start<<"\n";
        }
        else
        {
           cout<<"id - state - arrival time \n";
            cout<<"P"<<List[i].id<<" - IN QUEUE - "<<List[i].arv<<"\n";
        }
    }
}

int main()
{
    int i,k,avail;
    cout<<"Enter the number of processes : ";
    cin>>n;
    cout<<"Enter the number of resources available : ";
    cin>>k;

    for(i=0; i<n; i++)
    {
        cout<<" Id - arrival time - use time - resource needed : \n";
        cin>>List[i].id>>List[i].arv>>List[i].use>>List[i].resrc;
    }

    vector<int> que,run,comp;
    run.push_back(0);
    int ctr = List[0].arv , node = 1;
    List[0].start = List[0].arv;
    avail = k - List[0].resrc;

    while(!run.empty())
    {
        ctr++;
       int flag = 0;
        for(i=0 ; i<(signed)run.size(); i++)
        {
            int id = run[i];
            if(ctr == List[id].start + List[id].use)
            {
                avail += List[id].resrc;
                List[id].state = 1;
                run.erase(run.begin() + i);
                i--;
                flag = 1;
            }
        }

        for(i=0 ; i<(signed)que.size(); i++)
        {
            int id = que[i];
            if( avail >= List[id].resrc)
            {
                List[id].start = ctr;
                avail -= List[id].resrc;
                run.push_back(id);
                List[id].state = 2;
                que.erase(que.begin()+i);
                i--;
                continue;
            }
        }


        for( ; node<n; node++)
        {
            if(ctr != List[node].arv)
                break;

            if( avail >= List[node].resrc)
            {
                List[node].start = ctr;
                avail -= List[node].resrc;
                run.push_back(node);
                List[node].state = 2;
            }
            else{
                que.push_back(node);
                List[node].state = 0;
            }
        }
        if(flag)
            display(ctr);

    }

    cout<<"\nFINAL : \n";
    for(i=0; i<n; i++){
        cout<<"P"<<List[i].id<<" "<<List[i].arv<<" "<<List[i].start<<" "<<List[i].start-List[i].arv<<"\n";
    }


    return 0;
}
