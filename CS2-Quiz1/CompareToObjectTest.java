/* Tanvir Ahmed
1-12-2022
The following code sorts objects and implements customized compareTo andn toString functions
*/


import java.util.Random;
import java.util.Arrays;
//If you need to compare object, it is also possible to implement your own compareTo function in the object. For example: see our Point class and its comareTo function

public class CompareToObjectTest
{
  public static void main(String[] args) 
  {
    Random rand = new Random();
    Point[] points = new Point[5];
    //create each point and fillup x and y with random number
    for(int i = 0; i<5; i++)
      points[i] = new Point(rand.nextInt(100), rand.nextInt(100)); 

    
    //see the points
    for(int i = 0; i<5; i++)
      System.out.print(points[i].toString()); 
    
    Arrays.sort(points);

    System.out.println("======sorted====");
    //see the points
    for(int i = 0; i<5; i++)
      System.out.print(points[i].toString());    

    //testing two pionts with compareTo
    Point p1 = new Point(5, 20);
    Point p2 = new Point(10, 20);
    System.out.println(p1.compareTo(p2));


  }
}


class Point implements Comparable<Point>
{
   int x, y;

   Point(int x, int y)
   {
      this.x = x;
      this.y = y;
   }

   // This method sorts points by x values and, if there is a tie, y
   // values.
   public int compareTo(Point rhs)
   {
      if (x == rhs.x)
         return Integer.compare(y, rhs.y);
      return Integer.compare(x, rhs.x);
      //for your information, compare function returns negative if first number is smaller, returns positive if first number is bigger, and returns 0 if both are same
   }

   public String toString()
   {
     return "x = " + this.x + " y = " + this.y + "\n";
   }
}
