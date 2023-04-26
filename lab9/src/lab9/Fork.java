/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab9;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ckelsey
 */
public class Fork {
    Semaphore p = new Semaphore(1);
    int id; 
    
    public Fork(int id){
        this.id = id;
    }
     
    int getId() {
        return (id + 1);
    }
     
    // Everytime a philosopher grabs a fork the semaphore ready gets decremented, 
    // indicating that a resource is used 
    void get_fork() {
        try {
            p.down(); 
        } catch (InterruptedException ex) {
            ex.printStackTrace(System.out);
        }
    }
    // Every time a philosopher puts his fork back, the sempahore is incremented, 
    // indicating that a resource is now available. 
    void put_fork(){
        try {
            p.up();  
        } catch (InterruptedException ex) {
            Logger.getLogger(Fork.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
        
    boolean isFree(){
        return p.getvalue()> 0;
    }
}
