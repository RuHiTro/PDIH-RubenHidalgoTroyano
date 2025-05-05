import com.google.zxing.*;
import com.google.zxing.client.j2se.BufferedImageLuminanceSource;
import com.google.zxing.common.HybridBinarizer;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class LeerCodigoBarras {

    public static void main(String[] args) {
        String archivoImagen = "codigoBarras.png";

        try {
            // Cargar la imagen del código de barras
            BufferedImage imagen = ImageIO.read(new File(archivoImagen));

            // Preparar la imagen para ser procesada
            LuminanceSource fuente = new BufferedImageLuminanceSource(imagen);
            BinaryBitmap bitmap = new BinaryBitmap(new HybridBinarizer(fuente));

            // Intentar decodificar el código de barras
            Result resultado = new MultiFormatReader().decode(bitmap);

            // Mostrar resultado
            System.out.println("Contenido del código de barras: " + resultado.getText());

        } catch (IOException e) {
            System.out.println("Error al leer la imagen.");
            e.printStackTrace();
        } catch (NotFoundException e) {
            System.out.println("No se encontró ningún código de barras en la imagen.");
        }
    }
}

