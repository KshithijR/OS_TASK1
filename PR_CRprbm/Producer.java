package producer_Consumer;

public class Producer implements Runnable {

    private final SharedBuffer sharedBuffer;
    private final int itemsToProduce;

    public Producer(SharedBuffer sharedBuffer, int itemsToProduce) {
        this.sharedBuffer = sharedBuffer;
        this.itemsToProduce = itemsToProduce;
    }

    @Override
    public void run() {
        try {
            for (int i = 1; i <= itemsToProduce; i++) {
                sharedBuffer.put(i);
                Thread.sleep(300);
            }
            System.out.println("[Producer] Done producing " + itemsToProduce + " items.");
        } catch (InterruptedException e) {
            System.out.println("[Producer] Got interrupted, stopping.");
            Thread.currentThread().interrupt();
        }
    }
}