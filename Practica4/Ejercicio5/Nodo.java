package Ejercicio5;

public class Nodo extends Thread{
    private long prevFib, fib, i;

    public Nodo(long n){
        this.i = n;
        this.prevFib = 0;
        this.fib = 0;
    }

    public long getPrevFib(){
        return this.prevFib;
    }

    public long getFib(){
        return this.fib;
    }

    public void setPrevFib(long prevFib){
        this.prevFib = prevFib;
    }

    public void setFib(long fib){
        this.fib = fib;
    }

    public void run(){
        if(i == 0){
            this.fib = 0;
        } else if(i == 1){
            this.prevFib = 0;
            this.fib = 1;
        } else {
            Nodo nodo = new Nodo(i-1);

            nodo.start();
            
            try {
                nodo.join();
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }

            this.prevFib = nodo.getFib();
            this.fib = nodo.getFib()+nodo.getPrevFib();
        }
    }


}

