import subprocess
import json

def run_command(command):
    nb_lego = None
    simylarity = None
    try:
        # Exécuter la commande
        result = subprocess.run(command, capture_output=True, text=True, check=True)
        # Afficher la sortie standard
        for line in result.stdout.splitlines():
            if "Nombre de Legos" in line:
                print(line)
                nb_lego = line.split(":")[1].strip()
            if "Similarite" in line:
                print(line)
                simylarity = line.split(":")[1].strip()
        if nb_lego is None:
            print("Erreur : Nombre de Legos non trouvé dans la sortie.")
        print(nb_lego, command[1], command[2], command[4])
        # Afficher les erreurs s'il y en a
        if result.stderr:
            print("Errors:\n", result.stderr)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e}")
    return {"nb_lego": nb_lego, "seuil": command[1], "displayImage": command[2], "blur": command[4], "simylarity": simylarity}

if __name__ == "__main__":
    # Commande à exécuter
    min_seuil = 0
    max_seuil = 250
    step = 10
    result = []
    for seuil in range(min_seuil, max_seuil + step, step):
        for blur in range(1, 6):  # Valeurs de blur de 1 à 5
            command = ["./reel3.exe", str(seuil), str(0), str(1001), str(blur)]
            result.append(run_command(command))

    # Enregistrer les résultats dans un fichier JSON
    with open("result.json", "w") as f:
        json.dump(result, f)