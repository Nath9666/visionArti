import xmltodict
import json
import os

# Chemin du dossier contenant les fichiers XML
input_folder = 'c:/Users/Nathan/Documents/Projet/visionArti/data/results'

# Parcourir tous les fichiers dans le dossier
for filename in os.listdir(input_folder):
    if filename.endswith('.xml'):
        # Chemin complet du fichier XML
        xml_file_path = os.path.join(input_folder, filename)
        
        # Lire le fichier XML
        with open(xml_file_path, 'r') as file:
            xml_content = file.read()
        
        # Convertir le XML en dictionnaire
        xml_dict = xmltodict.parse(xml_content)
        
        # Convertir le dictionnaire en JSON
        json_content = json.dumps(xml_dict, indent=4)
        
        # Chemin complet du fichier JSON de sortie
        json_file_path = os.path.join(input_folder, filename.replace('.xml', '.json'))
        
        # Écrire le JSON dans un fichier
        with open(json_file_path, 'w') as json_file:
            json_file.write(json_content)
        
        print(f"Converti {filename} en {filename.replace('.xml', '.json')}")