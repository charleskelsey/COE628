/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab7;

/**
 *
 * @author ckelsey
 */
public class Main {
    public static void main(String[] args) throws InterruptedException {
        Counter counter = new Counter();
        Thread threadA = new CounterThread(counter,10);
        Thread threadB = new CounterThread(counter,11);
        System.out.println("Starting A");
        threadA.start();
        System.out.println("Starting B");
        threadB.start();
        threadB.join(); //Wait for B to finish if commented the 55 loops of threadB wont be executed, only 45 of threadA
        threadA.join(); //Wait for A to finish if commented, still get complete output
        System.out.println("count: " + counter.count);
    }
}
