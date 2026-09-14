package producer_Consumer;

public class Consumer implements Runnable {

    private final SharedBuffer sharedBuffer;
    private final int itemsToConsume;

    public Consumer(SharedBuffer sharedBuffer, int itemsToConsume) {
        this.sharedBuffer = sharedBuffer;
        this.itemsToConsume = itemsToConsume;
    }

    @Override
    public void run() {
        try {
            for (int i = 1; i <= itemsToConsume; i++) {
                sharedBuffer.take();
                Thread.sleep(500);
            }
            System.out.println("[Consumer] Done consuming " + itemsToConsume + " items.");
        } catch (InterruptedException e) {
            System.out.println("[Consumer] Got interrupted, stopping.");
            Thread.currentThread().interrupt();
        }
    }
}