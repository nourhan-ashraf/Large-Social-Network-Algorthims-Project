#include <bits/stdc++.h>
using namespace std;

//Time complexity is O(N)

//Global variables
int arr[810000];
map<int,int>counter;


//compare function to sort vector of pairs
bool cmp(pair<int, int>& a, pair<int, int>& b)
{
    return a.second > b.second;      //swaping doesn't affact the complexity remarkably
}

//count the degree(no. of followers) of each account
void followersCount(int account) {   //O(1)for each call 
    counter[account]++;                  
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


int main()
{
    //set<int>s1;
    //set<int>s2;
	ifstream myFile("twitter.csv"); //open the data file
    if (myFile.is_open())
    {
        string line;
        while(getline(myFile,line))   //O(N) for N lines of data
        {
            stringstream ss(line);
			string x;
			string y;
			getline(ss,x,',');    //follower
            getline(ss,y,',');    //account
			int follower, account;
			//follower = stoi(x);
			account = stoi(y);
            //s1.insert(follower);
            //s2.insert(account);

            followersCount(account);   //O(1) for each account
			//cout<<account<<" "<<follower<<endl;
        }

    }
	else{
		cout<<"Cannot open the file!"<<endl;
		return 0;
	}

    //cout<<s1.size()<<" "<<s2.size()<<endl;
	cout<<"Enter the influncer order: "; //take the input from the user
	int num; cin>>num;
	if(num<1 || num>81305){
		cout<<"Wrong input!"<<endl;
		return 0;
	}
	searchFollowersCount(num);  //O(n*log(n))

	return 0;
}
