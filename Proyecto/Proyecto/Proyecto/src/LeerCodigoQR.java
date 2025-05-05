import com.google.zxing.*;
import com.google.zxing.client.j2se.BufferedImageLuminanceSource;
import com.google.zxing.client.j2se.MatrixToImageWriter;
import com.google.zxing.common.HybridBinarizer;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class LeerCodigoQR {

    public static void main(String[] args) {
        String archivoImagen = "codigoQR.png"; 

        try {
            // Leer la imagen del QR
            BufferedImage imagen = ImageIO.read(new File(archivoImagen));

            // Preparar la imagen para decodificación
            LuminanceSource fuente = new BufferedImageLuminanceSource(imagen);
            BinaryBitmap bitmap = new BinaryBitmap(new HybridBinarizer(fuente));

            // Leer el QR con ZXing
            Result resultado = new MultiFormatReader().decode(bitmap);

            // Mostrar el contenido del QR
            System.out.println("Contenido del código QR: " + resultado.getText());

        } catch (IOException e) {
            System.out.println("Error al leer la imagen.");
            e.printStackTrace();
        } catch (NotFoundException e) {
            System.out.println("No se encontró ningún código QR en la imagen.");
        }
    }
}


