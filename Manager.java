import java.util.Scanner;
import java.io.*;
import java.sql.*;
import java.util.Random;
import java.util.Scanner;
import java.util.ArrayList;

public class Manager {
    
    int storeID;
    Scanner myScanner;
    
    public Manager(){
        
    }
    
    public static void main(String[] args) throws SQLException, IOException, java.lang.ClassNotFoundException { 
        
        Manager man = new Manager();
        man.run();
    }
    
    public void run() throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        boolean done = false;
        System.out.println("Enter the id of your store");
        storeID = getStoreID();
        
        while(!done){
            System.out.println("What would you like to do today? ");
            System.out.println("1) Enter 'prices' to change prices ");
            System.out.println("2) Enter 'inventory' to check inventory ");
            
            String choice = getString("prices", "inventory");
            
            if(choice.equals("prices"))
                updatePrice();
            
            else if(choice.equals("inventory"))  
                checkInventory(storeID);  
            
            System.out.println("Is there anything else you would like to do today?");
            if(!yesOrNo())
                done = true;
        }
    }
    
    private void checkInventory(int store_ID) throws SQLException, IOException, java.lang.ClassNotFoundException {
        
        System.out.println("Here is the current inventory in your store");
        displayStock(store_ID);
        
        System.out.println("Would you like to restock any products?");
        if(yesOrNo())
            reOrders(store_ID);  
    }
    
    private void reOrders(int store_ID)throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        boolean finish = false;
        
        while(!finish){
            System.out.println("Which product do you want to restock?");
            int id = getID(store_ID);
            
            System.out.println("There are currently " + getCurrentStock(id,store_ID) + " left");
            System.out.println("How many would you like to order: ?");
            int newStock = getInt();
            reStock(newStock,store_ID,id);
            
            System.out.println("Do you want to restock anything? (yes or no)");
            if(!yesOrNo())
                finish = true;
        }
    }
    
    private void updatePrice() throws SQLException, IOException, java.lang.ClassNotFoundException{ 
            
        String type = getProductType();
        displayInventory(type,storeID); 
        
        System.out.println("Enter the ID of the product you want to change");
        int id = getInt(type);
        
        System.out.println("Enter the new price: ");
        int newPrice = getInt();
        
        Class.forName ("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        int oldPrice = getPrice(id,type);
        
        ResultSet result;
        Statement s = con.createStatement();
        String q = "update " + type + " set price = " +newPrice + " where price = " + oldPrice;
        result = s.executeQuery(q);
        
        System.out.println("The price has changed from " + oldPrice + " to " + newPrice); 
        
    }
    
    private void displayStock(int store_id) throws SQLException, IOException, java.lang.ClassNotFoundException {
        
       Class.forName ("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        String q; 
        ResultSet result;
        
        q = "select * from inventory where store_id = " + store_id;
        result = s.executeQuery(q);
        ResultSetMetaData output = result.getMetaData();
        
        for(int i = 1; i < output.getColumnCount(); i++){
            System.out.print( output.getColumnName(i+1) + "\t");
        }
        
        System.out.println();
        
        for(int i = 1; i < output.getColumnCount(); i++){
            System.out.print("-------" + "\t");
        }
        
        System.out.println();
        
        if (!result.next()){
            System.out.println ("Empty result.");
        }
        
        else {
            
            do{
                
                for(int i = 2; i < output.getColumnCount() + 1; i++){
                    System.out.print(result.getNString(i) + "\t");
                }
                
                System.out.println();
                
            }while (result.next());
        }
        
    }
    
    private void reStock(int num, int store_id, int bar_code) throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Class.forName("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        
        String q; 
        ResultSet result;
        
        q = "update inventory set quantity = quantity + " + num + " where store_id = " + store_id + " and bar_code = " +bar_code;
        result = s.executeQuery(q);
        result.next();
        
        System.out.println("Your order was sucessfully placed"); 
        
    }
    
    private int getCurrentStock(int id, int store_id)throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Class.forName("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        
        String q; 
        ResultSet result;
        
        q = "select quantity from inventory where store_id = '" + store_id +"' and bar_code = '" + id + "'";
        result = s.executeQuery(q);
        result.next();
        
       return Integer.parseInt(result.getNString(1));
    }

    private int getID(int store_id) throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        do{
            int id = getInt();
            
            if(!validBC("products",id))
                System.out.println("Invalid bar code");
            
            else
                return id;
            
        }while(true);
    }
    
    
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
                
                if(w.equals("yes") || w.equals("no") )
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
    
    private int getInt(String type) throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Scanner myScanner = new Scanner (System.in); 
        int input; 
        
        do{
            
            if(myScanner.hasNextInt()){
                input = myScanner.nextInt();//checks to see if user entered an integer
                
                if(validBC(type,input))//checks to see if integer is between 1 and three
                    break;
                
                else{
                    System.out.println("Error: Invaild input");
                    System.out.println("Enter a valid id"); 
                }
            }
            
            else{
                System.out.println("Error: Invaild input");
                System.out.println("Enter a valid id");
                myScanner.next();
            }
        }while(true);
        
        return input;
    }
    private String getProductType(){
        System.out.println("What are you looking for: clothing, shoes, or sports_eq");
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
                    return type;
                
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
    }
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

    
    private String getString(String s1, String s2){
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
                        System.out.println("Enter" +s1+ " or " +s2); 
                    }
                }  
                
                
             
                else{
                    System.out.println("Error: Invaild input");
                    System.out.println("Enter" +s1+ " or " +s2); 
                    myScanner.next();
                }
            }while(true);
        
    }
    
    //returns a valid store id while checking for user input
    private int getStoreID()throws SQLException, IOException, java.lang.ClassNotFoundException{
        int input = 0;
        myScanner = new Scanner (System.in);
        do{
            
            if(myScanner.hasNextInt()){
                input = myScanner.nextInt();//checks to see if user entered an integer
                
                if(validID("store",input))
                    return input;
                
                else{
                    System.out.println("Error: Invaild store id");
                    System.out.println("Enter a valid store_id:"); 
                }
            }
            
            else{
                System.out.println("Error: Invaild store id");
                System.out.println("Enter a valid store_id"); 
                myScanner.next();
            }
            
        }while(true);
        
    }
    
    private boolean validBC(String table, int id) throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Class.forName("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        
        String q; 
        ResultSet result;
        
        q = "select * from " + table + " where  bar_code = '" + id +"'";
        result = s.executeQuery(q);
        ResultSetMetaData output = result.getMetaData();
        
        if(!result.next())
            return false;
        
        return true;   
    }
    
    private boolean validID(String table, int id)throws SQLException, IOException, java.lang.ClassNotFoundException{
        
        Class.forName("oracle.jdbc.driver.OracleDriver");
        Connection con = DriverManager.getConnection
            ("jdbc:oracle:thin:@edgar1.cse.lehigh.edu:1521:cse241","mag216","famguy4");
        
        Statement s = con.createStatement();
        
        String q; 
        ResultSet result;
        
        q = "select * from " + table + " where store_id = '" + id +"'";
        result = s.executeQuery(q);
        ResultSetMetaData output = result.getMetaData();
        
        if(!result.next())
            return false;
        
        return true;
        
        
    }
    
}