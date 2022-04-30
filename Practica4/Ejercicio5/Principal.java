package Ejercicio5;

public class Principal {
    
    public static void main(String[] args) {
        long n = 10;
        Nodo fibThread = new Nodo(n);
        System.out.println("El numero de fibonacci "+n);

        fibThread.start();

        try {
            fibThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println(fibThread.getFib());
    }
}
