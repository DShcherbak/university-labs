import java.util.Random;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;


public class SkipList {
    private static class Node{
        final public int value;
        final public AtomicReference<Node>[] next;
        final public int level;

        public Node(int value, int level, int maxLevels) {
            this.value = value;
            this.level = level;
            this.next = (AtomicReference<Node>[])new AtomicReference<?>[maxLevels];
            for(int i=0;i<maxLevels;++i)
                this.next[i]=null;
        }

    }

    final int maxLevels;
    final int probability = 50;
    final public AtomicInteger size = new AtomicInteger(0);
    final AtomicInteger levels = new AtomicInteger(0);
    final AtomicReference<Node> head;

    public SkipList(int maxLevels) {
        this.maxLevels = maxLevels;
        this.head = new AtomicReference<Node>(new Node(Integer.MIN_VALUE,0,maxLevels));
    }

    private int chooseRandomLevel() {
        int newLevel = 0;
        while (newLevel < maxLevels - 1 && new Random().nextInt(100) < this.probability) {
            newLevel += 1;
        }
        return newLevel;
    }

    public void add(int value) {
        AtomicReference<Node> currentPointer = head;
        Node currentNode = currentPointer.get();
        Node[] update = new Node[maxLevels];
        int currentLevel = levels.get();

        for(int i = currentLevel; i >= 0; i--) {
            currentPointer = head;
            currentNode = currentPointer.get();
            while(currentNode.next[i] != null && currentNode.next[i].get().value < value) {
                currentPointer = currentNode.next[i];
                currentNode = (Node) currentPointer.get();
            }
            update[i] = currentNode;
        }
        currentPointer = currentNode.next[0];
        if(currentPointer != null)
            currentNode = (Node) currentPointer.get();

        if(currentPointer == null || currentNode.value != value) {
            int rLevel = chooseRandomLevel();
            if(rLevel > currentLevel) {
                for(int i=currentLevel+1;i<=rLevel;++i)
                    update[i]=head.get();

                levels.compareAndSet(currentLevel, rLevel);
            }

            Node newNode = new Node(value,rLevel,maxLevels);

            for(int i=0;i<=rLevel;++i) {
                newNode.next[i] = update[i].next[i];
                update[i].next[i]= new AtomicReference<Node>(newNode);
            }

            size.incrementAndGet();
        }
    }

    public AtomicReference<Node> getCurrentPointer(int value, Node[] update){
        AtomicReference<Node> currentPointer = head;
        Node current = (Node) currentPointer.get();
        int currentLevel = levels.get();
        for(int i = currentLevel; i>=0;i--) {
            while(current.next[i] != null && current.next[i].get().value < value) {
                currentPointer = current.next[i];
                current = (Node) currentPointer.get();
            }
            update[i] = current;
        }
        currentPointer = current.next[0];
        return currentPointer;
    }

    public void remove(int value) {
        Node[] update = new Node[maxLevels];
        int currentLevel = levels.get();
        AtomicReference<Node> ref = getCurrentPointer(value, update);
        if(ref == null)
            return;
        Node currentNode = ref.get();
        if(currentNode.value==value) {
            for(int i = 0; i <= currentLevel; ++i) {
                if(update[i].next[i]==null || update[i].next[i].get() != currentNode)
                    break;
                update[i].next[i]= currentNode.next[i];
            }

            int level = levels.get();
            while(level>0 && head.get().next[level] == null) {
                --level;
            }
            levels.compareAndSet(currentLevel, level);
            size.decrementAndGet();
        }
    }

    public boolean contains(int value) {
        Node[] update = new Node[maxLevels];
        int currentLevel = levels.get();
        AtomicReference<Node> currentPointer = getCurrentPointer(value, update);
        if(currentPointer == null)
            return false;
        return currentPointer.get().value == value;
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();

        int l = levels.get();
        for(int i = l;i >= 0; --i) {
            AtomicReference<Node> currentPointer = head.get().next[i];
            Node currentNode = currentPointer.get();
            while(currentPointer != null) {
                str.append(" ").append(currentNode.value);
                currentPointer = currentNode.next[i];
                if(currentPointer!=null)
                    currentNode = (Node) currentPointer.get();
            }
            str.append('\n');
        }

        return str.toString();
    }

}
