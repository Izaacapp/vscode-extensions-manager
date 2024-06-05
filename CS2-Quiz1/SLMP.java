/*
this code implements three versions of SLMP and does some experiment on number of steps
*/

class SLMP {
	
	//declaring steps counter to keep track how many steps are taken by each approach
  static int cntlinearsearch = 0,cntbinSearchIter = 0, cnttwoTracker = 0;

  public static void main(String[] args) {
//example arrays, Please play with different numbers in the array to do more experiments
    int[] l1 = {10, 20, 30, 35, 40, 45, 50, 55, 60, 65 };

    int[] l2 = {12, 15, 20, 25, 40, 50, 52, 60, 62, 70};
	
    printMatchesN2(l1, l2);
    System.out.println("Steps by linear search: " + cntlinearsearch);

    printMatchesBinIter(l1, l2);
    System.out.println("Steps by binary search iter approach: " + cntbinSearchIter);

    slmplinear(l1, l2);
    System.out.println("Steps by two trackers approach approach: " + cnttwoTracker);

  }

//O(n^2) SLMP brute force approach
  static void printMatchesN2(int list1[], int list2[]) 
  { 
    int i,j; 
    for (i=0; i < list1.length; i++)
    {
      for (j=0; j<list2.length; j++) //linear search
      {
        cntlinearsearch++;
        if (list1[i] == list2[j])
        {	
          System.out.println(list1[i]);
          break;
        }
      }
    }
  }

  
  //O(n log n) approach
  static void printMatchesBinIter(int list1[], int list2[]) 
  { 
    int i; 
    for (i=0; i < list1.length; i++)
    {
      if(binSearchIter(list2, list1[i]) != -1) //call binary search
        System.out.println(list1[i]);
    }
  }


  //Binary search iterative approach
    static int binSearchIter(int list[], int item)
    {
      int l = 0, h = list.length - 1;
      int mid;
      while (l <= h)
      {
          cntbinSearchIter++;
          mid = (l + h) / 2;
          // Check if item is present at mid
          if (list[mid] == item)
              return mid;
          // If item greater, ignore left half
          if (list[mid] < item)
              l = mid + 1;

          // If item is smaller, ignore right half
          else
              h = mid - 1;
      }
      // if we reach here, then element was
      // not present
      return -1;

  } 

  //linear SLMP using two different trackers (one for each array)
  static void slmplinear(int list1[], int list2[]) {

    int i = 0, j = 0;
    int m = list1.length, n = list2.length;

    // Go while we still have numbers in both lists.
    while (i < m && j < n) {
        cnttwoTracker++;

        // Safe to advance list 1 pointer.
        if (list1[i] < list2[j]) i++;

        // Safe to advance list 2 pointer.
        else if (list2[j] < list1[i]) j++;

        // Match!
        else {
            System.out.println(list1[i]);
            i++;
            j++;
        }
    }
}
}