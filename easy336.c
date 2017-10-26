	#include <stdio.h>

	void GetInputs(int numvals, int numqueries,int valarray[],int queryarray[])
	{
	    int i=0; 
	    //getting inputs
	    for(i=0; i<numvals; ++i)
	    {
		scanf("%i",&valarray[i]);
	    }

	    for(i=0; i<numqueries; ++i)
	    {
		scanf("%i",&queryarray[i]);
	    }
	}

	//implments quick sort
	void Swap(int sortarray[],int i, int j)
	{
	    int temp = sortarray[i];
	    sortarray[i]=sortarray[j];
	    sortarray[j] = temp;
	}

	int Partition(int sortarray[],int pivot, int left, int right)
	{
	    int partitionind = left;
	    for(left;left<right;++left) 
	    {
		if(sortarray[left]<pivot)
		{
		    Swap(sortarray,left,partitionind);
		    ++partitionind;
		}
	    }
	    Swap(sortarray,partitionind,right);
	    return partitionind;
	}

	void QuickSort(int sortarray[], int left, int right)
	{
	    int pivot;
	    int partitionind;
	    if(left<right)
	    {
		pivot = sortarray[right];
		partitionind = Partition(sortarray,pivot,left,right);
		QuickSort(sortarray,left,partitionind-1);
		QuickSort(sortarray,partitionind+1,right);
	    }
	}



	void LeftoverHandler(int leftovers[],int left,int right,int query, int* answer)
	{
	    int needed = query - leftovers[right];
	    int avail = right - left;
	    if(avail>=needed)
	    {
		++(*answer);
		LeftoverHandler(leftovers,left+needed,right-1,query,answer);
	    }
	}

	int CannibalCalc(int valarray[], int query, int numvals)
	{
	    int answer=0;
	    int leftovers[numvals];
	    int i=0;
	    int counter=0;

	    for(i=0; i<numvals;++i)
	    {
		if (valarray[i]>=query)
		{
		    ++answer;
		}
		else
		{
		    leftovers[counter]=valarray[i];
		    ++counter;
		}
	    }
	    //leftovers now contains everything less than the query
	    QuickSort(leftovers,0,counter-1);
	    LeftoverHandler(leftovers,0,counter-1,query,&answer);
	    return answer;
	}

	int main()
	{
	    int numvals;
	    int numqueries;
	    int i;
	    int answer=0;
	    scanf("%i %i",&numvals,&numqueries);
	    
	    int valarray[numvals];
	    int queryarray[numqueries];
	    GetInputs(numvals,numqueries,valarray,queryarray);

	    for(i=0;i<numqueries;++i)
	    {
		answer = CannibalCalc(valarray,queryarray[i], numvals);
		printf("answer is %i\n",answer);
	    }
	    return 0;
	}
