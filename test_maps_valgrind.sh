#!/bin/bash
# Ce script teste toutes les maps (.cub) dans les sous-dossiers de maps
# pour chaque map, il exécute valgrind --leak-check=full ./cub3d et capture les sorties séparément.
# Sortie normale du programme : out_put
# Sortie Valgrind : output_val
# Une fenêtre s'ouvre à chaque exécution. Vous devez la fermer avant d'appuyer sur Entrée.

OUTPUT_FILE="out_put"
VALGRIND_OUTPUT_FILE="output_val"
TMP_FILE="tmp_output.txt"
TMP_VALGRIND_FILE="tmp_valgrind.txt"

# Vider (ou créer) les fichiers de sortie
> "$OUTPUT_FILE"
> "$VALGRIND_OUTPUT_FILE"

echo "=== DÉBUT DES TESTS AVEC VALGRIND ===" | tee -a "$OUTPUT_FILE" "$VALGRIND_OUTPUT_FILE"
echo "Date: $(date)" | tee -a "$OUTPUT_FILE" "$VALGRIND_OUTPUT_FILE"
echo "" | tee -a "$OUTPUT_FILE" "$VALGRIND_OUTPUT_FILE"

# Parcourir tous les fichiers .cub dans maps/*/
for mapfile in maps/*/*; do
    echo "-----------------------------" | tee -a "$OUTPUT_FILE" "$VALGRIND_OUTPUT_FILE"
    echo "Test de la map: $mapfile" | tee -a "$OUTPUT_FILE" "$VALGRIND_OUTPUT_FILE"
    echo "Commande: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./cub3d \"$mapfile\"" | tee -a "$VALGRIND_OUTPUT_FILE"
    echo ""
    
    # Exécute Valgrind en arrière-plan
    # Sortie normale (stdout) -> tmp_output.txt
    # Sortie Valgrind (stderr) -> tmp_valgrind.txt
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./cub3d "$mapfile" > "$TMP_FILE" 2> "$TMP_VALGRIND_FILE" &
    PID=$!
    
    echo "Une fenêtre s'est ouverte pour la map: $mapfile."
    echo "Fermez la fenêtre puis appuyez sur Entrée pour continuer..."
    read -r
    
    # Si le processus est encore actif, on le termine
    if kill -0 "$PID" 2>/dev/null; then
        kill "$PID"
        sleep 1
    fi
    
    # Attendre que le processus se termine
    wait "$PID" 2>/dev/null

    # Ajouter la sortie normale au fichier out_put
    echo "=== SORTIE PROGRAMME ===" >> "$OUTPUT_FILE"
    cat "$TMP_FILE" >> "$OUTPUT_FILE"
    echo "" >> "$OUTPUT_FILE"
    
    # Ajouter la sortie Valgrind au fichier output_val
    echo "=== RAPPORT VALGRIND ===" >> "$VALGRIND_OUTPUT_FILE"
    cat "$TMP_VALGRIND_FILE" >> "$VALGRIND_OUTPUT_FILE"
    echo "" >> "$VALGRIND_OUTPUT_FILE"
    
    echo "✓ Test terminé pour $mapfile"
    echo ""
done

# Nettoyage des fichiers temporaires
rm -f "$TMP_FILE" "$TMP_VALGRIND_FILE"

echo "=== RÉSUMÉ FINAL ===" | tee -a "$OUTPUT_FILE" "$VALGRIND_OUTPUT_FILE"
echo "Tests terminés. Résultats disponibles dans :" | tee -a "$OUTPUT_FILE" "$VALGRIND_OUTPUT_FILE"
echo "- Sortie des programmes : '$OUTPUT_FILE'" | tee -a "$OUTPUT_FILE" "$VALGRIND_OUTPUT_FILE"
echo "- Rapports Valgrind : '$VALGRIND_OUTPUT_FILE'" | tee -a "$OUTPUT_FILE" "$VALGRIND_OUTPUT_FILE"
echo "Date de fin: $(date)" | tee -a "$OUTPUT_FILE" "$VALGRIND_OUTPUT_FILE"

# Afficher un résumé des fuites trouvées
echo ""
echo "=== RÉSUMÉ DES FUITES MÉMOIRE ==="
echo "Recherche des fuites dans $VALGRIND_OUTPUT_FILE..."
grep -c "definitely lost\|indirectly lost\|possibly lost\|still reachable" "$VALGRIND_OUTPUT_FILE" > /dev/null
if [ $? -eq 0 ]; then
    echo "Fuites détectées :"
    grep -n "definitely lost\|indirectly lost\|possibly lost\|still reachable" "$VALGRIND_OUTPUT_FILE" | head -10
    echo ""
    echo "Voir le fichier '$VALGRIND_OUTPUT_FILE' pour les détails complets."
else
    echo "Aucune fuite mémoire détectée ! ✅"
fi

