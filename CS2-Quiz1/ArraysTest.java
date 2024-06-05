/* Tanvir Ahmed
1-12-2022
The following codes tests some functionalities of Arrays in java
*/

import java.util.Arrays;
import java.util.Collections;


class ArraysTest {
  
  public static void main(String[] args) {
    
    int a[];
    a = new int[10];

    //Arrays.fill(array, someValue);
    Arrays.fill(a, -1); //initialize all the array elements to -1

    //see the array using toString
    System.out.print("\na initialized to -1: " + Arrays.toString(a)); 

    ////If you have an object, in that case you need to have a toString method that will print the string representation of your object
    
    //Arrays.fill(array, fromInclusive, toExclusive, value);
    Arrays.fill(a, 2, 5, 0); //change the index from 2 to 4 to 0

    System.out.print("\na's 2 to 4 initialized to 0: " + Arrays.toString(a)); //see the array

// Arrays.copyOf(array, length);
    int b[] = Arrays.copyOf(a, 6); //copying first 6 elements from a 

    System.out.println();
    System.out.print("\nb array (copied from a's first 6 elements): " +Arrays.toString(b)); //see the array

   
//Arrays.copyOfRange(array, fromInclusive, toExclusive);

    int c[] = Arrays.copyOfRange(a, 2, 6); //copying index 2 ot 5 from a 
 
    System.out.print("\nc array (copied from a' 2 to 5): " + Arrays.toString(c)); //see the array

//Arrays.sort(array); //sort in ascending order for premetive data type
//run-time O(n log n)
    Arrays.sort(a);
    System.out.print("\nSorted a: " +Arrays.toString(a));

//Arrays.sort(array, fromInclusive, toExclusive);

  int d[] = {10, 5, 3, 4, 2, 100, 9};
  System.out.print("\nd array: " +Arrays.toString(d));
  Arrays.sort(d, 1, 5); //sort from index 1 to 4
  System.out.print("\nSorted d from index 1 to 4: " +Arrays.toString(d));

  //Unfortunately, you cannot change the order arrays of premetive data type. If you would like to sort it in descending order, you use the Collections.reverseOrder function and you have to use object instead of premetive type

  Integer[] e = {150, 15, 10, 39, 78, 2, 9};
  Arrays.sort(e, Collections.reverseOrder());
  System.out.print("\nSorted e in reverse order: " + Arrays.toString(e));


  //System.out.println(Integer.compare(500,500));



  










  }
}