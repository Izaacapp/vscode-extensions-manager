class NQueen {
  public static int N = 4;
  /* A utility function to print solution */
void printSolution(int board[][])
{
    System.out.format("Printing in matrix format: \n");
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			System.out.format(" %d ", board[i][j]);
		System.out.format("\n");
	}

	System.out.format("Printing in Queen format: \n");

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
            if (board[i][j] == 1)
                 System.out.format("Q%d ", i+1);

             // No queen here, so print a blank.
             else
                 System.out.format("_  ");
			//System.out.format(" %d ", board[i][j]);
		System.out.format("\n");
	}
}

/* check to see if it is save to put the queen in x,y position */
boolean isSafe(int board[][], int x, int y)
{
   int XminusY = x - y;
   int XplusY = x + y;
   for(int i=0; i<N; i++)  //need some optimization
   {
    for (int j=0; j<N; j++)
    {
        if(i==x && j == y ) return true; //Optimization, as we are only interested in the queens before this cell
        if (i==x || j==y || (i-j) == XminusY || (i+j) == XplusY) //if in same row or same column or left/right diagonal as we learned in the class
        {
               if(board[i][j] == 1)
                  return false;
        }
    }
   }
	return true;
}

/* A recursive utility function to solve N
Queen problem */
boolean solveNQUtil(int n, int row, int board[][])
{
	/* base case: If all queens are placed
	then return true */
	if (row == n)
		return true;

	/* Consider this column and try placing
	this queen in all rows one by one */

	int col;
	for (col = 0; col < n; col++) { //try each column of this row
            if (isSafe(board, row, col))
            {
                board[row][col] = 1;
                if (solveNQUtil(n, row+1, board)) //try for the next row
                    return true;
                board[row][col] = 0; //if not successful unmark that place to 0
            }
	}
	/* If the queen cannot be placed in any any columns  in
		this row then return false */
	return false;
}

/* This function solves the N Queen problem using
Backtracking. It mainly uses solveNQUtil() to
solve the problem. It returns false if queens
cannot be placed, otherwise, return true and
prints placement of queens in the form of 1s.
Please note that there may be more than one
solutions, this function prints one of the
feasible solutions.*/
public int solveNQ()
{
  int i, j;
	int[][] board = new int[N][N]; //initialize all the positions to 0 by default

	if (solveNQUtil(N, 0, board) == false) {
		System.out.println("Solution does not exist");
		return 0;
	}

	printSolution(board);
	return 1;
}
  public static void main(String[] args) {

    NQueen m = new NQueen();
    m.solveNQ();

  }
}