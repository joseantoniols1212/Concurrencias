package primero;

//https://docs.oracle.com/javase/8/docs/api/java/lang/Process.html
import java.io.File;
import java.io.IOException;

public class ProcesosDinamicos {

    public static void main(String[] args) throws IOException, InterruptedException {
        ProcessBuilder pb = new ProcessBuilder("./descifrar", "./imagen/imagen2Encriptadaa.png",
                "./imagen/imagen2.png");

        pb.redirectError(new File("SalidaError.txt"));
        pb.redirectOutput(new File("SalidaNormal.txt"));

        Process p = pb.start();

        p.waitFor();
        System.out.print("Salida "+p.exitValue());
    }
}