/* Tanvir Ahmed
1-12-2022
The following codes tests some functionalities of ArrayList in java
*/

import java.util.ArrayList;
import java.util.Iterator;

public class ArrayListTest{
   public static void main(String[] args) {

      // create an empty array list with an initial capacity
      ArrayList<Integer> myList = new ArrayList<Integer>(); //default initial capacity. you can also pass an initial capacity

      // use add() method to add elements in the list
      myList.add(10);
      myList.add(5);
      myList.add(16);
      myList.add(25);

      // adding element 35 at third position
      myList.add(2,35);

//It is also worth noting that all Collections in java have a toString method that behaves similar to Arrays.toString(). 
      System.out.println(myList);
      //get item from a specific position
      Integer val = myList.get(3);
      System.out.println("Item at index 2 = " + val);

        
      // let us print all the elements available in list and we can also unbox Integer to int here
      for (int number : myList) {
         System.out.println("Number = " + number);
      }  

      //all java collection you can obtain iterator
      //the above loop has used iterator implicitely 
      Iterator<Integer> it = myList.iterator(); //myList was declare already
      //the following loop iterate through the list and remove the evennumbers
      while (it.hasNext())
      {
        int curValue = it.next();
        if (curValue % 2 == 0)
            it.remove();
      }

       System.out.println(myList);
  //indexOf method search for a given data and returns the index. 
       System.out.println("Index of 35: "+  myList.indexOf(35));
       System.out.println("Index of -350: "+  myList.indexOf(-35)); //returns -1 as -35 does not exist in the list


   }
}   