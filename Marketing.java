import java.io.*;
import java.sql.*;
import java.util.Random;
import java.util.Scanner;

public class Marketing {
    
    public Marketing() { 
        
    }
    
    public static void main (String[] arg) throws SQLException, IOException, java.lang.ClassNotFoundException{
        Marketing m = new Marketing();
        m.run();
    }
    
    public void run() throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        boolean done = false;
        System.out.println("Welcome to marketing!");
        System.out.println("What would you like to do today? ");
        
        while(!done){
            System.out.println("1) Enter 'rank' for ranking of how products sell");
            System.out.println("2) Enter 'store' for most visited stores");
            
            String choice = getString("rank","store");
            if(choice.equals("rank"))
                ranks();
            
            else if (choice.equals("store"))
                stores(); 
            
            System.out.println("Will that be all today?");
            if(yesOrNo())
               done = true;
            
            else
                System.out.println("What else would you like to do today?");
        }
    }
    
    private void ranks()throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        System.out.println("Here is a list of the most sold products so far");
        displayRank();
        
        System.out.println("Is there a product you would like to see how many units were sold");
        if(yesOrNo())
            getUnitsSold();
        
    }
    
    private void stores() throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        System.out.println("Here is a list of the stores that have the highest sales");  
        displayStoreRank();   
            
        
    }
    
    private void displayStoreRank() throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Class.forName ("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        String q; 
        ResultSet result;
        
        q = "select store_id, rank() over (order by count(store_id) desc) as ranking from market_basket group by store_id";
        result = s.executeQuery(q);
        ResultSetMetaData output = result.getMetaData();
        
        for(int i = 0; i < output.getColumnCount(); i++){
            System.out.print( output.getColumnName(i+1) + "\t");
        }
        
        System.out.println();
        
        for(int i = 0; i < output.getColumnCount(); i++){
            System.out.print("-----" + "\t");
        }
        
        System.out.println();
        
        if (!result.next()){
            System.out.println("Empty result.");
        }
        
        else {
            
            do{
                
                for(int i = 1; i < output.getColumnCount() + 1; i++){
                    System.out.print(result.getNString(i) + "\t");
                }
                
                System.out.println();
                
            }while (result.next());
        }
        
        
        
    }
    
    private void getUnitsSold() throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        System.out.println("Enter the bar code of product would you like to view");
        int id = getID();
        
        Class.forName ("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        String q; 
        ResultSet result;
        
        q = "select count(quantity) as NUM_SOLD from market_basket where bar_code = " + id;
        result = s.executeQuery(q);
        ResultSetMetaData output = result.getMetaData();
        
        
        System.out.print("There have been ");
        
        if (!result.next()){
            System.out.println ("Empty result.");
        }
        
        else {
            
            do{
                
                for(int i = 1; i < output.getColumnCount() + 1; i++){
                    System.out.print(result.getNString(i));
                }
                
                System.out.print(" units sold");
                
            }while (result.next());
        }
        
        
    }
    
    private int getID() throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        do{
            int id = getInt();
            
            if(!validBC(id))
                System.out.println("Invalid bar code");
            
            else
                return id;
            
        }while(true);
    }
    
    private boolean validBC(int id) throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Class.forName("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        
        String q; 
        ResultSet result;
        
        q = "select * from market_basket where  bar_code = '" + id +"'";
        result = s.executeQuery(q);
        ResultSetMetaData output = result.getMetaData();
        
        if(!result.next())
            return false;
        
        return true;   
    }
    
    private void displayRank() throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Class.forName ("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        String q; 
        ResultSet result;
        
        q = "select bar_code, rank() over(order by quantity desc) as ranking from market_basket";
        result = s.executeQuery(q);
        ResultSetMetaData output = result.getMetaData();
        
        for(int i = 0; i < output.getColumnCount(); i++){
            System.out.print( output.getColumnName(i+1) + "\t");
        }
        
        System.out.println();
        
        for(int i = 0; i < output.getColumnCount(); i++){
            System.out.print("-----" + "\t");
        }
        
        System.out.println();
        
        if (!result.next()){
            System.out.println ("Empty result.");
        }
        
        else {
            
            do{
                
                for(int i = 1; i < output.getColumnCount() + 1; i++){
                    System.out.print(result.getNString(i) + "\t");
                }
                
                System.out.println();
                
            }while (result.next());
        }
        
        
    }
    
    private String getString(String s1, String s2) throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Scanner myScanner = new Scanner (System.in);
        String answer = "";
        myScanner = new Scanner (System.in);
        
        do{
            
            if(myScanner.hasNext()){
                answer = myScanner.nextLine();//checks to see if user entered a string
                if(answer.equals(s1) || answer.equals(s2)){
                    return answer;
                }
                
                else{
                    System.out.println("Error: Invaild input");
                    System.out.println("Enter " +s1+ " or " +s2); 
                }
            }  
            
            
            
            else{
                System.out.println("Error: Invaild input");
                System.out.println("Enter " +s1+ " or " +s2); 
                myScanner.next();
            }
        }while(true);
        
    }
    
    private boolean yesOrNo(){
        
        String w;
        Scanner myScanner = new Scanner (System.in);
        do{
            
            if(myScanner.hasNextInt() || myScanner.hasNextDouble()){
                System.out.println("Error: Invaild input");
                System.out.println("Enter yes or no"); 
                myScanner.next();
            }
            
            if(myScanner.hasNext()){
                w = myScanner.nextLine();
                
                if(w.equals("yes") || w.equals("no"))
                    break;
                
                else{
                    System.out.println("Error: Invaild input");
                    System.out.println("Enter yes or no"); 
                    
                }
            }
            
            else{
                System.out.println("Error: Invaild input");
                System.out.println("Enter yes or no"); 
                myScanner.next();
            }
        }while(true);
        
        if(w.equals("yes"))
            return true;
        
        else
            return false;
    }
    
    private int getInt()throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Scanner myScanner = new Scanner (System.in); 
        int input; 
        
        do{
            
            if(myScanner.hasNextInt()){
                input = myScanner.nextInt();//checks to see if user entered an integer
                return input;
            }
            
            else{
                System.out.println("Error: Invaild input");
                System.out.println("Enter a number");
                myScanner.next();
            }
            
        }while(true);   
        
    }
    
    
}
