/*#include <iostream>
#include <fstream>

using namespace std;

struct node
{
	int number;
	float arrivalIime, burstTime, waitingTime, processComplete, turn_aroundTime, responseTime,
	rd;
	struct node *next;
};
struct node * createNode(int);
struct node * insertNode(struct node *, int )*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

 
struct schedule {
	
	string processID;
	int arrivalTime;
	int burstTime;
	int priority;
	
};


void swapBurst(int *x_process, int *y_process) {
 
    int temp = *x_process; 
    *x_process = *y_process; 
    *y_process = temp; 
} 


void swapArrival(int *x_process, int *y_process) {
 
    int temp = *x_process; 
    *x_process = *y_process; 
    *y_process = temp;
	 
} 


void SortFCFS(struct schedule s[], int n) {
 
   int i, j; 
   
   bool swapped; 
   for (i = 0; i < n-1; i++) {
    
     swapped = false; 
     for (j = 0; j < n-i-1; j++) {
	  
        if (s[j].arrivalTime > s[j+1].arrivalTime) {
		 
          swapArrival(&s[j].arrivalTime, &s[j+1].arrivalTime);
		       swapBurst(&s[j].burstTime, &s[j+1].burstTime);
		       s[j].processID.swap(s[j+1].processID); 
           swapped = true; 
           
        } 
     } 
       
     if (swapped == false) 
        break; 
   } 
}


void SortSJF(struct schedule s[], int v,int e) {
 
   int i, j; 
   int z = 0;
   bool swapped; 
   
   for (i = v; i < e-1; i++) {
    
     swapped = false;
	  
     for (j = v; j < e-z-1; j++) {
	  
        if (s[j].burstTime > s[j+1].burstTime) {
		 
           swapArrival(&s[j].arrivalTime, &s[j+1].arrivalTime);
		       swapBurst(&s[j].burstTime, &s[j+1].burstTime);
		       s[j].processID.swap(s[j+1].processID); 
           swapped = true; 
           
        } 
     } 
  
      
     if (swapped == false) 
        break; 
        
    z++;
   } 
}

void FCFS(struct schedule s[],int number){
	
	float avgturn = 0, avgwait = 0;
	int exit[number];
	int l = s[0].arrivalTime;
	int responseTime =0;
	
	
   ofstream file;
   file.open("output.txt");
   file << "Scheduling Method: First Come First Served"<<endl;
   file << "Order Of Process Execution \t Time Interval"<<endl;
	
	for(int i=0; i < number; i++){
		
		exit[i] = l + s[i].burstTime;
		
		if(responseTime < s[i].arrivalTime){
			
			file << " CPU is on hold  \t\t\t " << responseTime << "-" << s[i].arrivalTime << endl;
			
			if(i==0)
				responseTime = s[i].arrivalTime;
			
			exit[i] = exit[i] + s[i].arrivalTime - responseTime;
			file << s[i].processID << "\t\t\t\t" << l + s[i].arrivalTime - responseTime << "-" << exit[i] << endl;
		}
		
		else{
			
			file << s[i].processID << "\t\t\t\t" << l << "-" << exit[i] <<endl;
			
		}
		
		l = exit[i];
		responseTime = exit[i];
		
	}
	
	file << endl;

	file << "Process Waiting Times: " <<endl;
	
	for(int i=0; i < number; i++){
		
		file << s[i].processID<< ":  "<< exit[i] - s[i].arrivalTime - s[i].burstTime << "ms" << endl;
	//	avgturn = avgturn + exit[i] - s[i].arrivalTime;
		avgwait = avgwait + exit[i] - s[i].arrivalTime - s[i].burstTime;              
		
	}
	file << endl;
	//cout << "Average Turnaround Time Is : " << avgturn/number <<endl;
	file << "Average Waiting Time Is : " << avgwait/number <<endl;      
	
	file <<endl;
	file <<endl;
	
	file.close();
	std::cin.get();
}


void SJF(struct schedule s[],int number){
	
	int waiting = 0;
	int count = 0;
	int sum = 0;
	int i;
	int v = 0, e = 0;
	bool fl = false;
	
	ofstream file;
	file.open("output.txt");
	for(int j=0;j<number;j++){
		
		v += count;
		count = 0;
		sum = 0;
		
		for(i = v; i<number; i++){
			
			if(s[i].arrivalTime <= waiting){
				
				sum += s[i].burstTime;	
				count = count++;
				
		}
			else
				break;
		}
		
	
		if(count > 0){
		
			waiting += sum;
			e = count;
			SortSJF(s,v,v+e);
	
		}
		
		else{
			
			waiting = s[i].arrivalTime;
			
		}
	
	}
	
	FCFS(s,number);

}



int main(void)
{
	int n;
	cout <<"Enter Number Of Process To Be Executed : ";
	cin >> n;
	
	schedule method_1[n], method_2[n];

	for(int i = 0; i < n; i++){
		cout<<"Enter Process ID Of Process "<<i+1<<" : ";
		cin.ignore();
		getline(cin,method_1[i].processID);
		
		method_2[i].processID = method_1[i].processID;
		
		cout << "Enter Arrival Time Of Process "<<i+1<<" : ";
		cin >> method_1[i].arrivalTime;
		
		method_2[i].arrivalTime = method_1[i].arrivalTime;
		
		cout << "Enter Burst Time Of Process " << i + 1 << " : ";
		cin >> method_1[i].burstTime;
		
		method_2[i].burstTime = method_1[i].burstTime;
	}
	
// loop for the scheduling options. Options will still appear even after user has chosen.

	int choose;
// try and catch for easy detection of errors.	
	try
	{
			while(true){
	        cout<<"Enter : \n 1 For First Come First Serve Scheduling \n " << "2 For Shortest Job First (Non Pre-emptive) Scheduling \n" <<" 3  To Exit"<<endl;
			cout<<"Enter Your Option : ";
			cin>>choose;
			
		if(choose==1){
			cout << endl;
			cout << "Scheduling Method: First Come First Served"<<endl;
			cout << endl;
			
			SortFCFS(method_1,n);
			FCFS(method_1,n);
		}
		
		else if(choose == 2){
			cout << endl;
			cout << "Scheduling Method: Shortest Job First (Non Pre-emptive)"<<endl;
			
		    SortFCFS(method_2,n);
			SJF(method_2,n);
		}
		
		
		else if(choose == 3){  // code for exiting the menu
				
			break;
		}
		else
		{
			throw (choose);
		}	
	}

	}
	catch(...){
			
			cout<<"Invalid Option"<<endl;
		}
	
	cout<<"Program Exited";
	
	
	return 0;
}
