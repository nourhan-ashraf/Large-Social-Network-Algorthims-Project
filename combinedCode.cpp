#include <bits/stdc++.h>
using namespace std;

//Time complexity is O(N*log(n))

//Global variables
int arr[810000];
map<int,int>counter;
map<int,int>mapping;

struct Graph {
	int Vertcies; //number of vertices
	unordered_set<int>* adjList;  //lists of vertices and each vertex has a list (unordered set) of followers
};

Graph* initializeGraph(int Vertcies) //utility function to intialize struct variables
{
	Graph* graph = new Graph;
	graph->Vertcies = Vertcies;
	graph->adjList = new unordered_set<int>[Vertcies];

	return graph;
}


//compare function to sort vector of pairs
bool cmp(pair<int, int>& a, pair<int, int>& b)
{
    return a.second > b.second;      //swaping doesn't affact the complexity remarkably
}

//count the degree(no. of followers) of each account
void followersCount(int account) {   //O(1)for each operation 
    counter[account]++;                   //O(n) for n of data
}



int k=0;
void buildGraph(Graph* graph, int account, int following)   //O(log(n))
{
        
        if(!mapping.count(account)){    //map "count" takes O(log(n))
            k++;
            mapping[account] = k;      //give each vertex an index beside its ID to be more easier to loop on each vertex 
        }
        graph->adjList[mapping[account]].insert(following); //add list of following to each vertex
                                                            //unordered_set insert complexity is O(1)
        
        //cout<<account<<" "<<mapping[account]<<endl;
    }
	

void searchFollowersCount(int account){   //O(nlogn)

	//convert map to vector of pairs so it can be sorted
	vector<pair<int, int>>cp;
	for (auto& it : counter) {
        cp.push_back(it);              //O(n) for n of data
    }
    sort(cp.begin(), cp.end(), cmp);   //O(nlogn) 
	//arr is aray of IDs and their order in descending order
	int i=1;
	 for (auto& it : cp) {
		//i: order
		//it.first: ID
        arr[i] = it.first;           //O(n) for n of data
		i++;
    }
	cout<<"Account ID: "<<arr[account]<<" , "<<"Followers: "<< counter[arr[account]];  
}



void searchAccounts(Graph* graph, int account)  //O(d*d))
{
		unordered_set<int> lst = graph->adjList[mapping[account]];  //list of following
		cout <<"Accounts you may know: ";
        auto itr = lst.begin();
        int cnt=3;
        //O(3*d) -> worst case ,  d is the number of following in the following list
        while(itr != lst.end() && cnt!=0){  //loop on the following list of the account ID
            unordered_set<int> follow = graph->adjList[mapping[*itr]]; //following list of each ID in the "user ID" the following list
            int cnt2=3;
            for(auto d = follow.begin() ; d != follow.end() ;++d){  //for each person in the "user ID" following list loop on its following list to find an ID that the "user ID" doesn't follow
                if( (!(graph->adjList[mapping[account]].count(*d))) && cnt2!=0 && (*d)!=account){ // if an ID is found and it's not equal to the "user ID", print it and decrease the counter to find other one
                    // //unordered_set "count" complexity is O(1) -> avarage , O(d) -> worst case
                    cout << *d<<"  "; //print the suggestion
                    cnt2--;
                }
                cnt--;
                ++itr;
            }
	    }

}

int main()
{
    int Vertcies = 810000;
	struct Graph* graph = initializeGraph(Vertcies);
	ifstream myFile("twitter.csv"); //open the data file
    if (myFile.is_open())
    {
        string line;
        while(getline(myFile,line))   //O(N) for N lines of data
        {
            stringstream ss(line);
			string x;
			string y;
			getline(ss,x,',');    
            getline(ss,y,',');    
			int follow, account;
		    follow = stoi(x);
			account = stoi(y);

            followersCount(account);  
            buildGraph(graph, follow, account); 
        }

    }
	else{
		cout<<"Cannot open the file!"<<endl;
		return 0;
	}

	cout<<"Enter the influncer order: "; //take the input from the user
	int num; cin>>num;
	if(num<1 || num>81305){
		cout<<"Wrong input!"<<endl;
		return 0;
	}
	searchFollowersCount(num);

    cout<<"\n";

    int ID;
    cout<<"Enter ID account: ";
    cin>>ID;
	bool flag = 0;
    for(int i=1;i<=mapping.size();i++){ //Handle the case if the user entered wrong account ID.
        if(mapping[ID]) flag = 1;
    }
    if(flag){
	    searchAccounts(graph,ID);
    }
    else{
        cout<<"This ID doesn't exist!"<<endl;
    }



	return 0;
}
