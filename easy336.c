#include <stdio.h>

//gets inputs from command line and stores in the arrays you pass to it
void GetInputs(int numvals, int numqueries,int valarray[],int queryarray[])
{
    int i=0; 
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
//end of quicksort


//actual code for cannibal numbers starts here
void LeftoverHandler(int leftovers[],int left,int right,int query, int* answer)
{
    //how many numbers we have to consume to be >= the query
    int needed = query - leftovers[right]; 
    //numbers available to consume
    int avail = right - left;
    if(avail>=needed)
    {
    //add 1 to answer and run again with fewer numbers now available
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
        //counte number of values greater than query
        if (valarray[i]>=query)
        {
            ++answer;
        }
        //if less than query add to new array
        else
        {
            leftovers[counter]=valarray[i];
            ++counter;
        }
    }
    //sort low to high and let leftoverhandler deal with it
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
