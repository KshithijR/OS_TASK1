package producer_Consumer;

public class Main {

    public static void main(String[] args) throws InterruptedException {

        int bufferCapacity = 5;
        int itemCount = 10;

        System.out.println("Producer-Consumer Simulation Start ");
        System.out.println("Buffer capacity: " + bufferCapacity + "  Items to process: " + itemCount);

        SharedBuffer sharedBuffer = new SharedBuffer(bufferCapacity);

        Thread producerThread = new Thread(new Producer(sharedBuffer, itemCount), "Producer-Thread");
        Thread consumerThread = new Thread(new Consumer(sharedBuffer, itemCount), "Consumer-Thread");

        producerThread.start();
        consumerThread.start();

        producerThread.join();
        consumerThread.join();

        System.out.println(" Producer-Consumer Simulation Complete ");
        System.out.println("All " + itemCount + " items were produced and consumed successfully.");
    }
}