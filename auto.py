import subprocess

def run_command(command):
    try:
        # Exécuter la commande
        result = subprocess.run(command, capture_output=True, text=True, check=True)
        # Afficher la sortie standard
        #?print("Output:\n", result.stdout)
        # Rechercher et afficher la ligne contenant "Nombre de Legos"
        for line in result.stdout.splitlines():
            if "Nombre de Legos" in line:
                print("Nombre de Legos e:", line)
                nb_lego = line.split(":")[1].strip()
        print(nb_lego, command[1], command[2])
        # Afficher les erreurs s'il y en a
        if result.stderr:
            print("Errors:\n", result.stderr)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e}")
    return {"nb_lego": nb_lego, "seuil": command[1], "thresh": command[2]}

if __name__ == "__main__":
    # Commande à exécuter
    min_seuil = 0
    max_seuil = 250
    step = 10
    min_thresh = 0
    max_thresh = 250
    result = []
    for seuil in range(min_seuil, max_seuil+step, step):
        for thresh in range(min_thresh, max_thresh+step, step):
            command = ["./visionArti.exe", str(seuil), str(thresh)]
            result.append(run_command(command))

    # enregistre result dans un fichier json
    import json
    with open("result.json", "w") as f:
        json.dump(result, f)