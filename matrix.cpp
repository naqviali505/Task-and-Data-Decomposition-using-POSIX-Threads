#include<iostream>
#include<stdlib.h>
#include<pthread.h>
using namespace std;
// int**a1;
// int**a2;
int**a3;
// int row=0;
// int col=0;
struct Arr
{
    int*rowelem;
    int*colelem;
    Arr(int*r,int*c)
    {
        int row=sizeof(r)/sizeof(r[0]);
        rowelem=new int[row];
        for(int i=0;i<row;i++)
        {
            rowelem[i]=r[i];
        }
        int col=sizeof(c)/sizeof(c[0]);
        colelem=new int[col];
        for(int i=0;i<col;i++)
        {
            colelem[i]=c[i];
        }
    }
};
pthread_mutex_t block;
void*tfunc(void*args)
{
    pthread_mutex_lock(&block);
  //  cout<<"Entering thread"<<x++<<"\n";
    Arr*temp;
    
    temp=(Arr*)args;
    int row=sizeof(temp->rowelem)/sizeof(temp->rowelem[0]);
    int col=sizeof(temp->colelem)/sizeof(temp->colelem[0]);
    int p=0;
    int i=0,j=0;
    row++;
    col++;
    for(int i=0;i<row;i++)
    {       
        p=p+temp->rowelem[i]*temp->colelem[i];
               
    }
    if(j==col)
    {
        i++;
        j=0;
    }
    a3[i][j++]=p;
    
    pthread_mutex_unlock(&block);
   // cout<<"Exiting thread"<<"\n";
    pthread_exit(NULL);
}
int main(int argc,char**argv)
{
    if((pthread_mutex_init(&block,NULL)))
	{
        cout<<"Mutex failed to initialize\n";
        return -1;
    }    
    int row=atoi(argv[1]);
    int col=atoi(argv[2]);
    pthread_t t[row];
    int**a1=new int*[row];
    for(int i=0;i<row;i++)
    {
        a1[i]=new int[col];
    }
    int**a2=new int*[row];
    for(int i=0;i<row;i++)
    {
        a2[i]=new int[col];
    }
    int**a3=new int*[row];
    for(int i=0;i<row;i++)
    {
        a3[i]=new int[col];
    }
    cout<<"Enter elememnts for 1st matrix\n";
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cin>>a1[i][j];
        }
    }
    cout<<"Enter elements for 2nd matrix\n";
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cin>>a2[i][j];
        }
    }
    cout<<"Matrix 1\n";
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<a1[i][j]<<" ";
        }
        cout<<endl;
    }
    int*result;
    cout<<"Matrix 2\n";
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<a2[i][j]<<" ";
        }
        cout<<endl;
    }
    int j=0;
    int t1[row];
    for(int i=0;i<row;i++)
    {
        for(int temp=0;temp<row;temp++)
        {
            t1[temp]=a2[temp][j];   
        }
        Arr *obj=new Arr(a1[i],t1);
        pthread_create(&t[i],NULL,&tfunc,(void*)obj);
        j++;
        pthread_join(t[i],NULL);

    }
    cout<<"Resultant Matrix\n";
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<a3[i][j]<<" ";
        }
        cout<<endl;
    }
    pthread_mutex_destroy(&block);
	if(a1)
	{
		for(int i=0;i<row;i++)
			if(a1[i])
	   			free(a1[i]);
	   	free(a1);
	}
	if(a2)
	{
		for(int i=0;i<row;i++)
			if(a2[i])
	   			free(a2[i]);
	   	free(a2);
	}
	if(a3)
	{
		for(int i=0;i<row;i++)
			if(a3[i])
	   			free(a3[i]);
	   	free(a3);
	}
    return 0;
    
}