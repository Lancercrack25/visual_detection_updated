import os
import cv2
from datetime import datetime


class Logger:
    def __init__(self, log_dir):
        self.log_dir = log_dir
        os.makedirs(log_dir, exist_ok=True)  # Crea el directorio si no existe

    def saveDetection(self, image):
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = os.path.join(self.log_dir, f"detection_{timestamp}.jpg")
        cv2.imwrite(filename, image)