import os
import sys
import subprocess

def main():
    # Ruta al entorno virtual
    venv_python = "/home/luis/my_venv/bin/python"
    
    # Ruta absoluta al script principal
    script = os.path.join(os.path.dirname(__file__), "detection_node.py")

    # Ejecutar el nodo dentro del entorno virtual
    subprocess.run([venv_python, script] + sys.argv[1:])

