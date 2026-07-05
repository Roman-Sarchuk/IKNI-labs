package ua.lvivpoly;


public class ThreadPool {
    Thread[] pool;

    ThreadPool(int size) {
        pool = new Thread[size];
    }

    public void start(int i, Runnable task) {
        pool[i] = new Thread(task);
        pool[i].start();
    }

    public void cycleJoin(int start, int end) {
        for (int i = start; i < end; i++) {
            join(i);
        }
    }

    public void cycleJoin(int count) {
        cycleJoin(0, count);
    }
    

    public void join(int i) {
        try {
            pool[i].join();
        } catch (InterruptedException e) {
            e.printStackTrace();
            Thread.currentThread().interrupt();
        }
    }
}

