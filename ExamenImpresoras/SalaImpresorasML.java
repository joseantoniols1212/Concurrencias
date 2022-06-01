import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SalaImpresorasML implements SalaImpresoras {

    private int N;
    private List<Integer> impresorasPrestadas = new LinkedList();
    private List<Integer> cola = new LinkedList();
    private Lock lck = new ReentrantLock();
    private Condition esperaLibre = lck.newCondition();

    public SalaImpresorasML(int N) {
        this.N = N;
        for (int i = 0; i < N; i++) {
            impresorasPrestadas.add(i);
        }
    }

    @Override
    public int quieroImpresora(int id) throws InterruptedException {
        lck.lock();
        try {

            System.out.println("Cliente " + id + " quiere impresora");

            cola.add(id);

            while (impresorasPrestadas.size() == 0 || id != cola.get(0)) {
                esperaLibre.await();
            }

            cola.remove((Integer) id);

            int i = impresorasPrestadas.remove(0);

            System.out.println(
                    "        Cliente " + id + " coge impresora " + i + " quedan libres " + impresorasPrestadas.size());

            return i;
        } finally {
            lck.unlock();
        }
    }

    @Override
    public void devuelvoImpresora(int id, int n) throws InterruptedException {
        lck.lock();
        try {

            if (impresorasPrestadas.size() == 0)
                esperaLibre.signalAll();

            impresorasPrestadas.add(n);
            System.out.println(
                    "           Cliente " + id + " devuelve la impresora " + n + " quedan libres "
                            + impresorasPrestadas.size());
        } finally {
            lck.unlock();
        }
    }

}
