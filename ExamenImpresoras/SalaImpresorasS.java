import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Semaphore;

public class SalaImpresorasS implements SalaImpresoras {

    private int N;
    private List<Integer> impresorasPrestadas = new LinkedList();

    private Semaphore mutex = new Semaphore(1, true);
    private Semaphore espera = new Semaphore(1, true);

    public SalaImpresorasS(
            int N) {
        this.N = N;
        for (int i = 0; i < N; i++) {
            impresorasPrestadas.add(i);
        }
    }

    public int quieroImpresora(int id) throws InterruptedException {
        if (espera.availablePermits() > 1)
            System.out.println("ERROR");

        System.out.println("Cliente " + id + " quiere impresora");

        espera.acquire();

        mutex.acquire();

        if (impresorasPrestadas.size() > 1) {
            espera.release();
        }

        int i = impresorasPrestadas.remove(0);
        System.out.println(
                "        Cliente " + id + " coge impresora " + i + " quedan libres " + impresorasPrestadas.size());

        mutex.release();

        return i;
    }

    public void devuelvoImpresora(int id, int n) throws InterruptedException {

        mutex.acquire();
        if (impresorasPrestadas.size() == 0)
            espera.release();

        if (espera.availablePermits() > 1)
            System.out.println("ERROR");
        impresorasPrestadas.add(n);
        System.out.println(
                "           Cliente " + id + " devuelve la impresora " + n + " quedan libres "
                        + impresorasPrestadas.size());
        mutex.release();

    }
}
