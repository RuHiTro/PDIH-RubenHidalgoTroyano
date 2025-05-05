import com.google.zxing.BarcodeFormat;
import com.google.zxing.WriterException;
import com.google.zxing.qrcode.QRCodeWriter;
import com.google.zxing.common.BitMatrix;
import com.google.zxing.client.j2se.MatrixToImageWriter;

import java.io.IOException;
import java.nio.file.FileSystems;
import java.nio.file.Path;

public class GenerarQR {
    public static void main(String[] args) {
        String texto = "https://etsiit.ugr.es/"; 
        int ancho = 300;
        int alto = 300;
        String nombreArchivo = "codigoQR.png";

        QRCodeWriter qrWriter = new QRCodeWriter();
        try {
            BitMatrix matriz = qrWriter.encode(texto, BarcodeFormat.QR_CODE, ancho, alto);
            Path ruta = FileSystems.getDefault().getPath(nombreArchivo);
            MatrixToImageWriter.writeToPath(matriz, "PNG", ruta);
            System.out.println("Código QR generado correctamente.");
        } catch (WriterException | IOException e) {
            System.out.println("Error al generar el código QR:");
            e.printStackTrace();
        }
    }
}




