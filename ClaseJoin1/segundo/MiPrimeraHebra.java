package segundo;

public class MiPrimeraHebra implements Runnable{
    Character myChar;

    public MiPrimeraHebra(Character myChar) {
        this.myChar = myChar;
    }

    @Override
    public void run() {
        for(int i = 0; i<20; i++){
            System.out.print(myChar);
        }
        
    }
}
