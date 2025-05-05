import com.google.zxing.BarcodeFormat;
import com.google.zxing.WriterException;
import com.google.zxing.common.BitMatrix;
import com.google.zxing.client.j2se.MatrixToImageWriter;
import com.google.zxing.oned.Code128Writer;

import java.io.IOException;
import java.nio.file.FileSystems;
import java.nio.file.Path;

public class GenerarCodigoBarras {

    public static void main(String[] args) {
        String texto = "123456789012"; 
        int ancho = 400;  // Ancho de la imagen
        int alto = 150;   // Alto de la imagen
        String nombreArchivo = "codigoBarras.png";

        Code128Writer barcodeWriter = new Code128Writer();
        try {
            BitMatrix matriz = barcodeWriter.encode(texto, BarcodeFormat.CODE_128, ancho, alto);
            Path ruta = FileSystems.getDefault().getPath(nombreArchivo);
            MatrixToImageWriter.writeToPath(matriz, "PNG", ruta);
            System.out.println("Código de barras generado correctamente.");
        } catch (IOException e) {
            System.out.println("Error al generar el código de barras:");
            e.printStackTrace();
        }
    }
}
