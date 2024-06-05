
/* Tanvir Ahmed
1-12-2022
The following codes tests the way of comparing Integers instead of int
We have also seen in class with another example in the slide that did this mistake in ArrayDeQueue
*/



class PitFallsTest {
  public static void main(String[] args) {
    Integer x = 5;
    Integer y = 5;
    
    if(x==y)
      System.out.println("same"); //it works for the range [-128, 127]
    else
      System.out.println("not same");

    x = 500;
    y = 500;

    if(x==y) //it is actually comparing object reference!
      System.out.println("same");
    else
      System.out.println("not same"); //it will print not same!
    
    //One Solution
    if(x.equals(y))
      System.out.println("same");
    else
      System.out.println("not same");

      //another solution
    if(x.intValue() == y.intValue())
      System.out.println("same");
    else
      System.out.println("not same");
  }
}