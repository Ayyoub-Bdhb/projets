from PyQt6.QtWidgets import (
    QApplication, QLineEdit, QPushButton,
    QVBoxLayout, QWidget, QHBoxLayout, QComboBox, QLabel
)
from PyQt6.QtCore import Qt
import sys
import projet

def traitement_chiffrement():
    texte = mot.text()
    algorithme = selecteur.currentText()
    cle = champ_cle.text()
    
    resultat = ""

    if algorithme == "César":
        texte = texte.upper()
        try:
            decalage = int(cle)
            if direction_cesar.currentText() == "Droite":
                resultat = projet.chf_cesar_mot_droite(texte, decalage)
            else:
                resultat = projet.chf_cesar_mot_gauche(texte, decalage)
        except ValueError:
            resultat = "Clé invalide (entrez un nombre)."
    
    elif algorithme == "XOR":
        valeurs = projet.chiffrement_xor(texte, cle)
        resultat = " ".join(map(str, valeurs))
        # resultat = "".join(chr(v) for v in valeurs)  # version texte lisible
    
    elif algorithme == "Pollux":
        texte = texte.upper()
        try:
            cle_pollux = {
                ".": [int(p_point1.text()), int(p_point2.text())],
                "-": [int(p_tiret1.text()), int(p_tiret2.text())],
                " ": [int(p_espace1.text()), int(p_espace2.text())]
            }
            deja_pris = cle_pollux["."] + cle_pollux["-"] + cle_pollux[" "]
            cle_pollux["parasite"] = [i for i in range(10) if i not in deja_pris]

            resultat = projet.chiffrement_pollux(texte, cle_pollux)
            resultat = " ".join(map(str, resultat))
        except ValueError:
            resultat = "Clé Pollux invalide (entrez uniquement des chiffres)."

    label_resultat.setText(f"Résultat : {resultat}")
    

def affichage_champs_pollux():
    champs_pollux.setVisible(selecteur.currentText() == "Pollux")
    direction_cesar.setVisible(selecteur.currentText() == "César")

# --- Application ---
app = QApplication(sys.argv)

win = QWidget()
win.setWindowTitle("Projet cryptographie")
win.setGeometry(600, 250, 750, 500)

# --- Widgets ---
mot = QLineEdit()
mot.setPlaceholderText("Entrez le mot à chiffrer")
mot.setFixedHeight(30)
mot.setFixedWidth(250)

champ_cle = QLineEdit()
champ_cle.setPlaceholderText("Clé (César /XOR)")
champ_cle.setFixedHeight(30)
champ_cle.setFixedWidth(200)

selecteur = QComboBox()
selecteur.addItems(["XOR", "César", "Pollux"])
selecteur.setFixedHeight(30)
selecteur.setFixedWidth(150)
selecteur.currentIndexChanged.connect(affichage_champs_pollux)

bouton_valider = QPushButton("Valider")
bouton_valider.setFixedHeight(30)
bouton_valider.setFixedWidth(100)
bouton_valider.clicked.connect(traitement_chiffrement)

label_resultat = QLabel("Résultat :")
label_resultat.setWordWrap(True)

# Choix direction pour César
direction_cesar = QComboBox()
direction_cesar.addItems(["Droite", "Gauche"])
direction_cesar.setFixedHeight(30)
direction_cesar.setFixedWidth(100)
direction_cesar.setVisible(False)

# Champs clé Pollux
p_point1 = QLineEdit(); p_point1.setPlaceholderText(". chiffre 1"); p_point1.setFixedWidth(60)
p_point2 = QLineEdit(); p_point2.setPlaceholderText(". chiffre 2"); p_point2.setFixedWidth(60)
p_tiret1 = QLineEdit(); p_tiret1.setPlaceholderText("- chiffre 1"); p_tiret1.setFixedWidth(60)
p_tiret2 = QLineEdit(); p_tiret2.setPlaceholderText("- chiffre 2"); p_tiret2.setFixedWidth(60)
p_espace1 = QLineEdit(); p_espace1.setPlaceholderText("espace 1"); p_espace1.setFixedWidth(60)
p_espace2 = QLineEdit(); p_espace2.setPlaceholderText("espace 2"); p_espace2.setFixedWidth(60)

layout_pollux = QHBoxLayout()
layout_pollux.addWidget(p_point1)
layout_pollux.addWidget(p_point2)
layout_pollux.addWidget(p_tiret1)
layout_pollux.addWidget(p_tiret2)
layout_pollux.addWidget(p_espace1)
layout_pollux.addWidget(p_espace2)

champs_pollux = QWidget()
champs_pollux.setLayout(layout_pollux)
champs_pollux.setVisible(False)

# --- Layouts ---
navbar = QHBoxLayout()
navbar.setSpacing(15)
navbar.addWidget(mot)
navbar.addWidget(champ_cle)
navbar.addWidget(selecteur)
navbar.addWidget(direction_cesar)   
navbar.addWidget(bouton_valider)
navbar.setAlignment(Qt.AlignmentFlag.AlignCenter)

layout_principal = QVBoxLayout()
layout_principal.addLayout(navbar)
layout_principal.addWidget(champs_pollux)
layout_principal.addWidget(label_resultat)
layout_principal.addStretch()

win.setLayout(layout_principal)

win.show()

sys.exit(app.exec())
