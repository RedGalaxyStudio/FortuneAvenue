import cv2
import numpy as np
import os

# Cargar la imagen con fondo transparente
image_path = 'set-stickers-mexican-pinata-donkey-colorful-toy-with-treats-cactus-maracas-sombrero-flag-garland-child-birthday-viva-mexico-party-celebration-carnival-fiesta-cartoon-vector-patches.png'  # Cambia esto a la ruta de tu imagen
image = cv2.imread(image_path, cv2.IMREAD_UNCHANGED)

# Asegurarse de que la imagen tiene un canal alfa
if image is None or image.shape[2] != 4:
    raise ValueError("La imagen no se pudo cargar o no tiene un canal alfa.")

# Separar el canal alfa
alpha_channel = image[:, :, 3]

# Crear un umbral para detectar los objetos (donde el canal alfa es mayor que 0)
_, thresh = cv2.threshold(alpha_channel, 1, 255, cv2.THRESH_BINARY)

# Encontrar contornos de los objetos
contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Verificar si se encontraron contornos
if len(contours) == 0:
    print("No se encontraron objetos en la imagen.")
else:
    # Crear un directorio para guardar las imágenes
    output_dir = 'objetos_separados'
    os.makedirs(output_dir, exist_ok=True)

    # Guardar cada objeto en un archivo separado
    for i, contour in enumerate(contours):
        # Crear una máscara para cada objeto
        mask = np.zeros_like(image)
        cv2.drawContours(mask, [contour], -1, (255, 255, 255, 255), thickness=cv2.FILLED)

        # Extraer el objeto de la imagen original
        object_image = cv2.bitwise_and(image, mask)

        # Obtener el área de la máscara
        x, y, w, h = cv2.boundingRect(contour)
        object_image_cropped = object_image[y:y+h, x:x+w]

        # Asegurarse de que el objeto no esté vacío antes de guardar
        if np.sum(object_image_cropped[:, :, 3]) > 0:
            # Guardar la imagen del objeto con fondo transparente
            cv2.imwrite(os.path.join(output_dir, f'objeto_{i+1}.png'), object_image_cropped)

    print(f'Se han guardado {len(contours)} objetos en "{output_dir}"')
