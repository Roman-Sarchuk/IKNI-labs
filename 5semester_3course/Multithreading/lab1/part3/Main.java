package lab1.part3;


class Callme {
    public void call(String msg) {
        System.out.print("[" + msg);
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            System.out.println("Interrupted");
        }
        System.out.println("]");
    }
}


class Caller implements Runnable  {
    String msg;
    Callme target;
    public Thread t;

    Caller(Callme target, String msg) {
        this.target = target;
        this.msg = msg;
        t = new Thread(this);
        t.start();
    }

    public void run() {
        synchronized (target) {
            target.call(msg);
        }
    }
}


public class Main {
    public static void main(String[] args) {
        Callme target = new Callme();

        // set messages
        String[] msgs = {"Sarchuk", "Roman", "PP-34", "02.12.2006", "174 sm"};

        Caller[] callers = new Caller[msgs.length];

        // init callers
        for (int i = 0; i < msgs.length; i++) {
            callers[i] = new Caller(target, msgs[i]);
        }

        // wait for threads to finish
        for (int i = 0; i < msgs.length; i++) {
            try {
                callers[i].t.join();
            } catch(InterruptedException e) {
                System.out.println("Interrupted");
            }
        }

    }
}
