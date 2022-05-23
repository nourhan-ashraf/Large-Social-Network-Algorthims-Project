#include <bits/stdc++.h>
using namespace std;
map<int,int>mapping;

//Time complexity is O(N*log(N))
set<int>adjList[810000];

int k=0;
void buildGraph(int account, int following)   //O(log(N))
{
        
        if(!mapping.count(account)){    //map "count" takes O(log(N))
            k++;
            mapping[account] = k;      //give each vertex an index beside its ID to be more easier to loop on each vertex 
        }
        adjList[mapping[account]].insert(following); //add list of following to each vertex
                                                     //O(log(N))     
        
        //cout<<account<<" "<<mapping[account]<<endl;
    }
	

void searchAccounts(int account)  //O(d*log(d)))
{
		set<int> lst = adjList[mapping[account]];  //list of following
		cout <<"Accounts you may know: ";
        auto itr = lst.begin();
        int cnt=3;
        //O(3*d) -> worst case ,  d is the number of following in the following list
        while(itr != lst.end() && cnt!=0){  //loop on the following list of the account ID
            set<int> follow = adjList[mapping[*itr]]; //following list of each ID in the "user ID" the following list
            int cnt2=3;
            for(auto d = follow.begin() ; d != follow.end() ;++d){  //for each person in the "user ID" following list loop on its following list to find an ID that the "user ID" doesn't follow
                if( (!(lst.count(*d))) && cnt2!=0 && (*d)!=account){ // if an ID is found and it's not equal to the "user ID", print it and decrease the counter to find other one
                    //set "count" complexity is O(log(d))
                    cout << *d<<"  "; //print the suggestion
                    cnt2--;
                } 
            }
            cnt--;
            ++itr;
	    }

}

int main()
{
    /*buildGraph(graph, 4, 1);
    buildGraph(graph, 77, 77);
    buildGraph(graph, 8, 77);
    buildGraph(graph, 8, 4);
    buildGraph(graph, 99, 8);
    buildGraph(graph, 100, 4);*/
    ifstream myFile("C:\\Users\\Noura\\Downloads\\twitter (1).csv"); //open the data file

    if (myFile.is_open())  
    {
        string line;
        while(getline(myFile,line)) //O(Nlog(N)) for N of lines of data
        {
            stringstream ss(line);
			string x;
			string y;
			getline(ss,x,',');    //follower
            getline(ss,y,',');    //account
			int following, account;
			account = stoi(x);  //convert from string to int 
			following = stoi(y);

           buildGraph(account, following); 
        }

    }
	else{
		cout<<"Cannot open the file!"<<endl;
		return 0;
	}


    int ID;
    cout<<"Enter ID account: ";
    cin>>ID;
    bool flag = 0;
    for(int i=1;i<=mapping.size();i++){  //Handle the case if the user entered wrong account ID.
        if(mapping[ID]) {
            flag = 1;
            break;
        }
    }
    if(flag){
	    searchAccounts(ID);  
    }
    else{
        cout<<"This ID doesn't exist!"<<endl;
    }

	return 0;
}
