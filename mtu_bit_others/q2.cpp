#include<iostream>
using namespace std;
int main()
{
	int option;
	string data;
	cout<<"Enter the option to perform an action\n1) Stuffing the data\n2) Un-stuffing the data"<<endl;
	cin>>option;
	switch(option)
	{
		case 1:{
				cout<<"Enter the data string for stuffing"<<endl;
				cin>>data;
				int a = 0,len_add = 0;
				for(int i=0;i<data.length();i++)
				{
					if(data[i] == '1')
					a++;
					else 
					a = 0;
					if(a==5)
					{
						for(int j = data.length()+len_add-1;j>i;j--)
						{
							data[j+1] = data[j];
						}
						data[i+1] = '0';
						len_add++;
						a = 0;	
						
					}
				}
				cout<<"The stuffed data is ";
				for(int k=0;k<data.length()+len_add;k++)
				cout<<data[k];
				break;
		       }
		case 2:{
				cout<<"Enter the data string for un-stuffing"<<endl;
				cin>>data;
				int a = 0;
				for(int i=0;i<data.length();i++)
				{
					
					if(data[i] == '1')
					a++;
					else 
					a = 0;
					if(a==5)
					{
						for(int j = i+1;j<data.length()-1;j++)
						{
							data[j] = data[j+1];
						}
						data[data.length()-1] = '\0';
						a = 0;
					}
				}
				cout<<"The unstuffed data is "<<data<<endl;
				break;
		       }
		default:{
				cout<<"You have entered a wrong option!"<<endl;
				break;
			  }		
	}
	return 0;
}

