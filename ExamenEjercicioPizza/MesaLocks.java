import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class MesaLocks implements Mesa {

    private Lock lck = new ReentrantLock();
    private int trozosPizza = 8;
    private Condition esperarPizza = lck.newCondition();
    private Condition esperarClientes = lck.newCondition();
    private Condition esperarPagador = lck.newCondition();
    private boolean pizzeroLlamado = false;
    private int idPaga = -1;

    public void nuevaRacion(int id) throws InterruptedException {
        lck.lock();
        try {

            if (trozosPizza == 0) {
                if (!pizzeroLlamado) {
                    pizzeroLlamado = true;
                    idPaga = id;
                    esperarClientes.signal();
                    System.out.println("El estudiante " + id + " llama al pizzero");
                    esperarPagador.await();
                } else {
                    esperarPizza.await();
                }
            }

            trozosPizza--;

            if (idPaga == id) {
                pizzeroLlamado = false;
                idPaga = -1;
                esperarPizza.signalAll();
            }

            System.out.println("El estudiante " + id + " coge un trozo de pizza. Quedan: " + trozosPizza);

        } finally {
            lck.unlock();
        }

    }

    public void nuevoCliente() throws InterruptedException {
        lck.lock();
        try {
            esperarClientes.await();

            System.out.println("El pizzero recibe la llamada");

        } finally {
            lck.unlock();
        }
    }

    public void nuevaPizza() throws InterruptedException {
        lck.lock();
        try {
            trozosPizza = 8;
            System.out.println("El pizzero entrega la pizza");
            esperarPagador.signal();
        } finally {
            lck.unlock();
        }
    }

}
