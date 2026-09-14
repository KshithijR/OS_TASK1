package producer_Consumer;
import java.util.ArrayDeque;
import java.util.Deque;

public class SharedBuffer {

    private final Deque<Integer> buffer = new ArrayDeque<>();
    private final int capacity;

    public SharedBuffer(int capacity) {
        this.capacity = capacity;
    }

    public synchronized void put(int item) throws InterruptedException {
        while (buffer.size() == capacity) {
            System.out.println("[Producer] Buffer is full (" + buffer.size() + "/" + capacity + "), waiting.");
            wait();
        }

        buffer.addLast(item);
        System.out.println("[Producer] Produced " + item + " -> buffer now " + buffer + " (" + buffer.size() + "/" + capacity + ")");

        notifyAll();
    }

    public synchronized int take() throws InterruptedException {
        while (buffer.isEmpty()) {
            System.out.println("[Consumer] Buffer is empty, waiting.");
            wait();
        }

        int item = buffer.removeFirst();
        System.out.println("[Consumer] Consumed " + item + " -> buffer now " + buffer + " (" + buffer.size() + "/" + capacity + ")");

        notifyAll();

        return item;
    }
}