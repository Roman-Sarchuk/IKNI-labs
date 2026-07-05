package lab1.part1;

import java.util.List;
import java.util.Queue;
import java.util.LinkedList;
import java.util.Random;

class CPU {
    int id;
    Process process = null;
    public int completedProcessCount = 0;

    CPU(int id) {
        this.id = id;
    }

    public boolean isFree() { return process == null; }

    public void setProcess(Process process) { 
        this.process = process; 
        System.out.println("[CPU" + id + "]: Take process #" + process.id);
    }

    public void tick() {
        if (process == null) { return; }

        process.step();

        if (process.isCompleted()) { 
            System.out.println("[CPU" + id + "]: Process #" + process.id + " is completed");
            process = null;
            completedProcessCount++;
            return;
        }

        System.out.println("[CPU" + id + "]: Process #" + process.id + " left " + process.timeLeft);
    }
}


class Process {
    int id;
    int timeRequired;
    int timeLeft;

    Process(int id, int timeRequired) {
        this.id = id;
        this.timeRequired = timeRequired;
        timeLeft = timeRequired;
    }

    public void step() { timeLeft--; }

    public boolean isCompleted() { return timeLeft <= 0; }
}


class PCSystem {
    int processCount = 10;
    int queueLimit = 2;
    List<Process> processes = new LinkedList<>();
    Queue<Process> processQueue = new LinkedList<>();
    CPU cpu1 = new CPU(1);
    CPU cpu2 = new CPU(2);
    
    boolean isProcessesCompleted() {
        for (Process process : processes) {
            if(!process.isCompleted()) {
                return false;
            }
        }
        return true;
    }

    void handleNewProcess(Process process) {
        if (cpu1.isFree()) {
            cpu1.setProcess(process);
        }
        else if (processQueue.size() >= queueLimit && cpu2.isFree()) {
            cpu2.setProcess(process);
        }
        else {
            processQueue.add(process);
            System.out.println("[SYSTEM]: Process #" + process.id + " add in the queue. Queue size: " + processQueue.size());
        }
    }

    void handleProcesses() {
        // processing
        cpu1.tick();
        cpu2.tick();

        // handle processes in quequ
        if (processQueue.size() != 0) {
            if (cpu1.isFree()) {
                cpu1.setProcess(processQueue.poll());
            }
            else if (processQueue.size() >= queueLimit && cpu2.isFree()) {
                cpu2.setProcess(processQueue.poll());
            }
        }
    }

    public void run() {
        Random rand = new Random();
        int newProcessId = 1;
        System.out.println("===== START =====");
        do {
            // generate a new process
            if (newProcessId <= processCount) {
                Process process = new Process(newProcessId, rand.nextInt(3) + 1);
                processes.add(process);

                // handle the new process
                handleNewProcess(process);

                newProcessId++;
            }

            // handle curent processes
            handleProcesses();
        } while (!isProcessesCompleted());
        System.out.println("===== END =====");
        System.out.println("\n--- INFO ---");
        System.out.println("Process count: " + processCount);
        System.out.println("CPU1: " + (cpu1.completedProcessCount * 100 / processCount) + "%");
        System.out.println("CPU2: " + (cpu2.completedProcessCount * 100 / processCount) + "%");
    }
}


public class Main {
    public static void main(String[] args) {
        PCSystem system = new PCSystem();
        system.run();
    }
}