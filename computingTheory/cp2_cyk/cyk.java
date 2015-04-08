/* 
 * Michael Duckett
 * CYK algorithm for Context Free Language
 * Author: Chenguang Zhu
 * Stanford University
 * Edited by Shiva Houshmand, Florida State University
 */

import java.io.*;

public class cyk {

    static int ProductionNum = 7; // number of productions
    static int VarNum = 4;  //number of variables
    char[] Variables = new char[VarNum];
    int[][] production = new int[ProductionNum + 1][3];
    //Prouductions in Chomsky Normal Form (CNF)
    //production[i][0] is the variable on the left hand side of the ith production rule
    //production[i][1] is the first variable on the right hand side of the ith production rule
    //production[i][2] is the second variable on the right hand side of the ith production rule
    // production[i][0] = a number between 0 and 3 (0:S, 1:A, 2:B, 3:C)
    //If this production is A->BC (two variables), then production[i][1] and production[i][2] will contain the numbers for these two variables
    //If this production is A->a (a single terminal), then production[i][1] will contain the number for the terminal (0 or 1, 0: a, 1: b), production[i][2]=-1
    
    boolean[][][] V;
    //V[i][j][s]=true if and only if variable s (0~3, 0: S 1: A, 2: B, 3: C) is in V_ij defined in CYK

    //check whether (A,B,C) exists in production
    // This function checks whether A --> BC / or A --> a exists in the production rules
    // To check A-->BC is in production rules call existProd(1, 2, 3)
    // To check A --> a is in production rules call existProd(1, 0, -1)
    boolean existProd(int a, int b, int c) {
        int i;
        for (i = 0; i < production.length; ++i) {
            if ((production[i][0] == a) && (production[i][1] == b) && (production[i][2] == c)) {
                return true;
            }
        }
        return false;
    }

    // CYK algorithm
    // Calculate the array V
    // w is the string to be processed
    void calcCYK(int[] w) {
        int N = w.length;
		V=new boolean [N][N][VarNum];

        //Fill in your program here
		for (int step = 0; step < N; ++step) {
			for (int j = step; j < N; ++j) { // j is the second index of the V array
				int i = j - step; // i is the first index of the V array
				for (int var = 0; var < VarNum; ++var) {
					if (step == 0) {
						V[i][j][var] = existProd(var, w[j], -1); // for when the substring is of length 1 (initial case)
					} else {
						boolean exist = false; // true when production var -> v1 v2 exists
						int k = i; // i <= k < j
						while (!exist && k < j) {
							int v1 = 0;
							while (!exist && v1 < VarNum) {
								int v2 = 0;
								while (!exist && v2 < VarNum) {
									if (V[i][k][v1] == true && V[k + 1][j][v2] == true) { // only check if v1 is in V_ik and v2 is in V_k+1j
										exist = V[i][j][var] = existProd(var, v1, v2); // set exist to true to stop search
									}
									++v2;
								}
								++v1;
							}
							++k;
						}
					}
				}
			}
		}
    }

    public void Print_matrix(String str) {
        int len = str.length();
        System.out.println("Processing " + str + " ...");
        String result = "";
        String dashline = "";
        for (int i = 0; i < VarNum * len + (3 * len); i++) {
            dashline += "-";
        }
        dashline += "\n";
        result = result + dashline;
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                for (int k = 0; k < VarNum; ++k) {
                    if (V[i][j][k]) {
                        result = result + (char) (Variables[k]);
                    } else {
                        result = result + " ";
                    }
                }
                result = result + " | ";
            }
            result = result + "\n" + dashline;  					
        }
        System.out.print(result);
    }

    public void Start(String filename) {
        String result = "";
        //read data case line by line from file
        try {
            FileInputStream fstream = new FileInputStream(filename);
            // Get the object of DataInputStream
            DataInputStream in = new DataInputStream(fstream);
            BufferedReader br = new BufferedReader(new InputStreamReader(in));
            String str; //the string read in

            //example of a grammar 
            Variables = new char[VarNum];
            Variables[0] = 'S';
            Variables[1] = 'A';
            Variables[2] = 'B';
            Variables[3] = 'C';
            production = new int[7][3];
            production[0][0] = 0;   production[0][1] = 1;   production[0][2] = 2;  //S->AB
            production[1][0] = 1;   production[1][1] = 2;   production[1][2] = 3;  //A->BC
            production[2][0] = 1;   production[2][1] = 0;   production[2][2] = -1; //A->a
            production[3][0] = 2;   production[3][1] = 1;   production[3][2] = 3;  //B->AC
            production[4][0] = 2;   production[4][1] = 1;   production[4][2] = -1; //B->b
            production[5][0] = 3;   production[5][1] = 0;   production[5][2] = -1; //C->a
            production[6][0] = 3;   production[6][1] = 1;   production[6][2] = -1; //C->b

            //Read File Line By Line
            while ((str = br.readLine()) != null) {
                int len = str.length();
                int[] w = new int[len];
                for (int i = 0; i < len; ++i) {
                    w[i] = str.charAt(i) - 'a';  //convert 'a' to 0 and 'b' to 1
                }
                //Use CYK algorithm to calculate table V
                calcCYK(w);
               
                //print the full table V
                Print_matrix(str);
                
                
                //check if S exists in V[1][n]
                if (V[0][len - 1][0] == true) {
                    System.out.println(str + ": Yes\n");
                } else {
                    System.out.println(str + ": No\n");
                }
            }
            //Close the input stream
            in.close();

        } catch (Exception e) {//Catch exception if any
            result = result + "error\n";
            System.err.println("Error: " + e.getLocalizedMessage());
        }
    }

    public static void main(String args[]) {
        String filename = args[0];
        new cyk().Start(filename);
    }
}
