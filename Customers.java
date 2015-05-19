
import java.io.*;
import java.sql.*;
import java.util.Random;
import java.util.Scanner;
import java.util.ArrayList;

public class Customers extends MarketBasket {
    
    private ArrayList<MarketBasket> cart; 
    
    public Customers (){
        cart = new ArrayList<MarketBasket>();
        Scanner myScanner = new Scanner (System.in);
        
    }
    
    public static void main (String[] arg) throws SQLException, IOException, java.lang.ClassNotFoundException{
        Customers cust = new Customers();
        cust.run();
    }
    
    //this method runs the interface for a customer
    public void run() throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        System.out.println("Enter 1 for online orders, 0 will send you to a store");
        int answer = getInt(0,1);
        
        
        if(answer == 1)
            store(true);
        
        else
            store(false);
    }
    
    //code for online orders
    private void store(boolean b) throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Random rand  = new Random();
        boolean checkout = false; //boolean to check for checkout
        int store_ID = 0; 
        
        if(b)
            store_ID = 27092;  //placeholder to make sure only online store is accessed
        
        else
            store_ID = getStoreID();
        
        
        double totalCost = 0;
        int transID = rand.nextInt(99999) + 10000;
        
        while(!checkout){
            System.out.println("What are you looking for:  clothing, shoes, or sports_eq");
            Scanner myScanner = new Scanner (System.in);
            String type = "";
            do{
                
                if(myScanner.hasNextInt()){
                    System.out.println("Error: Invaild input");
                    System.out.println("Enter clothing, shoes, or sports_eq"); 
                    myScanner.next();
                }
                
                if(myScanner.hasNext()){
                    type = myScanner.nextLine();//checks to see if user entered a string
                    
                    if(type.equals("clothing") || type.equals("shoes") || type.equals("sports_eq"))//checks to see if integer is between 1 and three
                        break;
                    
                    else{
                        System.out.println("Error: Invaild input");
                        System.out.println("Enter clothing, shoes, or sports_eq"); 
                    }
                }
                
                else{
                    System.out.println("Error: Invaild input");
                    System.out.println("Enter clothing, shoes, or sports_eq"); 
                    myScanner.next();
                }
            }while(true);
            
            
            
            
            int counter = 0; //keeps track of where you are in arrayList cart
            
            //selects the inventory for an online selection
            System.out.println("Here is the online selection for " + type);
            
            displayInventory(type,store_ID);
            
            //while loop to check user enters a bar code
            System.out.println("Enter the bar_code of the product you want:");
            int bar_code = getNum();
            
            while(!inTable(type, bar_code)){
                System.out.println("Error Invalid bar_code");
                System.out.println("Enter the bar_code of the product you want:");
                bar_code = getNum();
            }
            
            //get the price based on the given bar code
            int price = getPrice(bar_code,type);
            
            
            System.out.print("How many do you want?");
            
            int quantity = getInt(1, 500);
            
            MarketBasket m = new MarketBasket(bar_code, price, quantity,store_ID);
            cart.add(m);
            counter++;
            
            Class.forName ("oracle.jdbc.driver.OracleDriver");
            Connection con = DriverManager.getConnection
                ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
            
            Statement s = con.createStatement();
            
            String q; 
            ResultSet result;
            totalCost += price * quantity;
            
            q = "insert into Market_Basket values('" + bar_code + "','" + transID + "','" + quantity + "','" + store_ID + "')";
            result = s.executeQuery(q);
            
            q = "update inventory set quantity = quantity - " + quantity + " where bar_code = '" + bar_code + "' and store_id = '" + store_ID + "'";
            result = s.executeQuery(q);
            
            System.out.println("Will that be all? (yes or no)");
            String answer = ""; 
            
            //asks the user if they want to checkout or not
            do{
                
                if(myScanner.hasNextInt()){
                    System.out.println("Error: Invaild input");
                    System.out.println("Enter yes or no"); 
                    myScanner.next();
                }
                
                if(myScanner.hasNext()){
                    answer = myScanner.nextLine();//checks to see if user entered a string
                    
                    if(answer.equals("yes") || answer.equals("no"))
                        break;
                    
                    else{
                        System.out.println("Error: Invaild input");
                        System.out.println("Enter yes or no"); 
                    }
                }
                
                else{
                    System.out.println("Error: Invaild input");
                    System.out.println("yes or no"); 
                    myScanner.next();
                }
            }while(true);
            
            if(answer.equals("yes"))
                checkout = true;  
        }
        
        
        checkout(totalCost);
        
        System.out.println("Will you be paying in cash or credit?");
        int creditCardNum = 0;
        
        if(getString("credit","cash")){
            System.out.println("Would you like to join the Frequent Shopper Program");
            if(yesOrNo())
                freqShopper();
            else{
                System.out.println("Enter your credit card number (less than 9 digits)");
                creditCardNum = getNum();
            }
        }
        
        System.out.println("Thank you for your buisness. Have a good day!");
        
    } 
    
    //asks the user to join the freq shopper program
    private void freqShopper() throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        String freqShop= "";
        
        System.out.println("Enter your credit card number");
        int cardNum = getNum();
        
        System.out.println("Enter your name:");
        String name = getString();    
        
        int customer_id = getId();  
        
        Class.forName ("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        
        String q; 
        ResultSet result;
        
        q = "insert into freq_shopper values('" + customer_id + "','" + name + "','" + cardNum + "')";
        result = s.executeQuery(q);
        //result.next();
        
        
    }
    
    //gets a random storeId
    private int getId(){
        
        Random rand = new Random();
        return rand.nextInt(99999) + 1000;
        
    }
    
    //method for checkout
    private void checkout(double totalCost){
        
        System.out.println("here is you cart:");
        System.out.println("Quantity \t Product \t Price"); 
        for(int i = 0; i < cart.size(); i++){
            System.out.println(cart.get(i).getQuantity() + "\t" + cart.get(i).getProdId() + "\t $" + cart.get(i).getPrice());
        }
        System.out.println("---------------------------------------------------------");
        System.out.println("Cost = $" + totalCost);
        
    }
    
    //checks that the user enters a proper string
    private String getString(){
        
        String w = "";
        Scanner myScanner = new Scanner (System.in);
        
        do{
            
            if(myScanner.hasNextInt() || myScanner.hasNextDouble()){
                System.out.println("Error: Invaild input");
                System.out.println("Enter a your name: "); 
                myScanner.next();
            }
            
            if(myScanner.hasNext()){
                w = myScanner.nextLine();
                return w;
            }
            else{
                System.out.println("Error: Invaild input");
                System.out.println("Enter your name: ");  
                myScanner.next();
            }
        }while(true);
        
        
    }
    
    //checks that the user enters either one of two strings
    private boolean getString(String s1, String s2){
        
        String w = "";
        Scanner myScanner = new Scanner (System.in);
        
        do{
            
            if(myScanner.hasNextInt() || myScanner.hasNextDouble()){
                System.out.println("Error: Invaild input");
                System.out.println("Enter " + s1 + "or" + s2 ); 
                myScanner.next();
            }
            
            if(myScanner.hasNext()){
                w = myScanner.nextLine();//checks to see if user entered a string
                
                if(w.equals(s1) || w.equals(s2) )//checks to see if integer is between 1 and three
                    break;
                
                else{
                    System.out.println("Error: Invaild input");
                    System.out.println("Enter " + s1 + "or" + s2 ); 
                    
                }
            }
            
            else{
                System.out.println("Error: Invaild input");
                System.out.println("Enter " + s1 + "or" + s2 );  
                myScanner.next();
            }
        }while(true);
        
        if(w.equals(s1))
            return true;
        
        else
            return false;
        
    }
    
    //checks to see if user enters yes or no
    private boolean yesOrNo(){
        
        String w;
        Scanner myScanner = new Scanner (System.in);
        do{
            
            if(myScanner.hasNextInt()){
                System.out.println("Error: Invaild input");
                System.out.println("Enter yes or no"); 
                myScanner.next();
            }
            
            if(myScanner.hasNext()){
                w = myScanner.nextLine();//checks to see if user entered a string
                
                if(w.equals("yes") || w.equals("no") )//checks to see if integer is between 1 and three
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
    
    //gets the price of a product
    private int getPrice(int barCode,String table)throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Class.forName ("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        
        String q; 
        ResultSet result;
        
        q = "select price from " + table + " where bar_code = '" + barCode +"'";
        result = s.executeQuery(q);
        ResultSetMetaData output = result.getMetaData();
        result.next();
        
        return Integer.parseInt(result.getNString(1));
        
    }
    
    
    //returns true if the value passed in is in the database
    private boolean inTable(String table, int barCode) throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        
        Class.forName ("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        
        String q; 
        ResultSet result;
        
        q = "select * from " + table + " where bar_code = '" + barCode +"'";
        result = s.executeQuery(q);
        ResultSetMetaData output = result.getMetaData();
        
        if(!result.next())
            return false;
        
        return true;
        
    }
    
    
    //method for getting an integer between two bounds
    private int getInt(int lowerB, int upperB){
        
        Scanner myScanner = new Scanner (System.in); 
        int input; 
        
        do{
            
            if(myScanner.hasNextInt()){
                input = myScanner.nextInt();//checks to see if user entered an integer
                
                if(input >= lowerB && input <= upperB)//checks to see if integer is between 1 and three
                    break;
                
                else{
                    System.out.println("Error: Invaild input");
                    System.out.println("Enter a integer between " + lowerB + " and " + upperB); 
                }
            }
            
            else{
                System.out.println("Error: Invaild input");
                System.out.println("Enter a integer between " + lowerB + " and " + upperB);
                myScanner.next();
            }
        }while(true);
        
        return input;
        
    }
    
    //check method to ensure that the user inputs an integer
    public int getNum(){
        
        Scanner myScanner = new Scanner (System.in); 
        int input; 
        
        do{
            
            if(myScanner.hasNextInt()){
                input = myScanner.nextInt();//checks to see if user entered an integer
                break;
            }
            
            else{
                System.out.println("Error: Invaild input");
                System.out.println("Enter an integer");
                myScanner.next();
            }
            
        }while(true);
        
        return input;
        
    }
    
    //displays the inventory for clothes, shoes, or sports eq_
    private void displayInventory(String type, int store_id) throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Class.forName ("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        String q; 
        ResultSet result;
        
        q = "select * from " + type;
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
    
    //gets all the store_id's and randomly outputs one
    private int getStoreID() throws SQLException, IOException, java.lang.ClassNotFoundException{
        Class.forName("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        String q = "select * from store"; 
        ResultSet result = s.executeQuery(q);
        int[] storeID = new int[150];
        int temp = 0;
        
        for(int i = 0; i<150; i++){
            result.next();
            temp = Integer.parseInt(result.getNString(1)); 
            if(temp != 27092)
                storeID[i] = temp;
        }
        
        Random rand = new Random();
        int select = rand.nextInt(149);
        
        return storeID[select];
    }
    
    
}  


