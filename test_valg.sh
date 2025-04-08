#!/bin/bash
# Ce script teste toutes les maps (.cub) dans les sous-dossiers de maps
# pour chaque map, il exécute ./cub3d avec valgrind et capture la sortie dans un fichier "out_put".
# Une fenêtre s'ouvre à chaque exécution. Vous devez la fermer avant d'appuyer sur Entrée.

OUTPUT_FILE="out_put"
TMP_FILE="tmp_output.txt"
VALGRIND_LOG="valgrind_log.txt"

# Vider (ou créer) le fichier de sortie
> "$OUTPUT_FILE"
> "$VALGRIND_LOG"

# Parcourir tous les fichiers .cub dans maps/*/
for mapfile in maps/*/*.cub; do
    echo "-----------------------------" | tee -a "$OUTPUT_FILE"
    echo "Test de la map: $mapfile" | tee -a "$OUTPUT_FILE"
    
    # Exécute le binaire avec valgrind en arrière-plan en redirigeant la sortie vers un fichier temporaire
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file="$VALGRIND_LOG" ./cub3d "$mapfile" > "$TMP_FILE" 2>&1 &
    PID=$!
    
    echo "Une fenêtre s'est ouverte pour la map: $mapfile."
    echo "Fermez la fenêtre puis appuyez sur Entrée pour continuer..."
    read -r
    
    # Si le processus est encore actif, on le termine
    if kill -0 "$PID" 2>/dev/null; then
        kill "$PID"
    fi
    
    # Attendre que le processus se termine
    wait "$PID" 2>/dev/null

    # Ajouter la sortie de valgrind au fichier de sortie
    cat "$VALGRIND_LOG" >> "$OUTPUT_FILE"
    cat "$TMP_FILE" >> "$OUTPUT_FILE"
    echo "" >> "$OUTPUT_FILE"
    
    # Réinitialiser le fichier de log pour valgrind
    > "$VALGRIND_LOG"
done

rm -f "$TMP_FILE"
echo "Tests terminés. Voir les résultats dans le fichier '$OUTPUT_FILE'."