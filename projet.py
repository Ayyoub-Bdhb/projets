import random

def conv_lettre_decimal(mot : str ) -> list : 
  lettre_decimal = []
  for i in range (len(mot)):
    lettre_decimal.append(ord(mot[i]))
  return lettre_decimal

# même chose que précédement juste fait l'inverse donc exemple [65,66,67] renvoie ABC
def conv_decimal_lettre( mot : list):
  decimal_lettre = []
  for i in range (len(mot)):
    decimal_lettre.append(chr(mot[i]))
  return decimal_lettre



# faire une fonction qui convertie chaque lettre de la clé en décimale comme pour le mot 
def key(clef : str ) -> list : 
  lettre_decimal = []
  for i in range (len(clef)):
    lettre_decimal.append(ord(clef[i]))
  return lettre_decimal



def chiffrement_xor(mot : str , cle : str):
    mot_decimal = conv_lettre_decimal(mot)
    clef        = key(cle)
    mot_chiffre = []
    j = 0 
    for i in range (len(mot_decimal)):
      mot_chiffre.append(mot_decimal[i] ^ clef[j])
      j += 1 
      if len(cle) - 1 < j :
        j = 0 
    return mot_chiffre

# faire appelle à la fonction key pour mettre la clé sous forme de liste d'entier     
def dechiffrement(mot : list , cle : list ) -> list : 
    mot_dechiffre = []
    j = 0 
    for i in range(len(mot)):
      mot_dechiffre.append(mot[i] ^ cle[j] )   
      j += 1 
      if len(cle) - 1 < j :
        j = 0 
    for k in range (len(mot_dechiffre)):
      mot_dechiffre[k] = chr(mot_dechiffre[k])
    mot_dechiffre="".join(mot_dechiffre)
    return mot_dechiffre
      


# chiffre les lettres dans le sens alphabétique exemple A avec un décallage de 1 devient B 
def chf_cesar_1caractere_droite(lettre : str , decallage : int ):
    lettre_chf = ord(lettre) + decallage
    if lettre_chf > 90:
      lettre_chf -= 26 
    return chr(lettre_chf)

# pareil que précédement mais avec une chaine de caractère 
def chf_cesar_mot_droite(mot : str , decallage : int ):
  mot_chf = []
  for i in range (len(mot)):
      mot_chf.append(chf_cesar_1caractere_droite(mot[i] , decallage))
  mot_chf = "".join(mot_chf)
  return mot_chf
  
def chf_cesar_1caractere_gauche(lettre : str , decallage : int):
    lettre_chf = ord(lettre) - decallage
    if lettre_chf <= 64:
      lettre_chf += 26 
    return chr(lettre_chf)

def chf_cesar_mot_gauche(mot : str , decallage : int ):
  mot_chf = []
  for i in range (len(mot)):
      mot_chf.append(chf_cesar_1caractere_gauche(mot[i] , decallage))
  mot_chf = "".join(mot_chf)
  return mot_chf

# la fonction génère une clé du chiffrement pollux 
def key_pollux() -> dict :
   nbchiffre = 0 
   la_cle = {".": [] , "-" : [], " " : [], "parasite" : []}
   deja_prit = []
   while True: 
      print("entrez un chiffre pour le point " )
      chiffre = int(input())
      if chiffre in deja_prit:
        print("ce chiffre à déjà été prit",deja_prit)
      else:
        deja_prit.append(chiffre)
        la_cle["."].append(chiffre)
        nbchiffre += 1
        if nbchiffre == 2:
          break
   nbchiffre = 0
   while True: 
      print("entrez un chiffre pour le tiret " )
      chiffre = int(input())
      if chiffre in deja_prit:
        print("ce chiffre à déjà été prit",deja_prit)
      else:
        deja_prit.append(chiffre)
        la_cle["-"].append(chiffre)
        nbchiffre += 1
        if nbchiffre == 2:
          break 
   nbchiffre = 0
   while True:
      print("entrez un chiffre pour l'espace " )
      chiffre = int(input())
      if chiffre in deja_prit:
        print("ce chiffre à déjà été prit",deja_prit)
      else:
        deja_prit.append(chiffre)
        la_cle[" "].append(chiffre)
        nbchiffre += 1
        if nbchiffre == 2:
          break
   for i in range(10):
        if i not in deja_prit:
          la_cle["parasite"].append(i)
          deja_prit.append(i)

     
   return la_cle

# la fonction chiffre le mot avec la clé du chiffrement pollux
def chiffrement_pollux(mot : str , cle : dict):
    mot_morse = []
    morse_dict = {
    'A': '.-',    'B': '-...',  'C': '-.-.',  'D': '-..',
    'E': '.',     'F': '..-.',  'G': '--.',   'H': '....',
    'I': '..',    'J': '.---',  'K': '-.-',   'L': '.-..',
    'M': '--',    'N': '-.',    'O': '---',   'P': '.--.',
    'Q': '--.-',  'R': '.-.',   'S': '...',   'T': '-',
    'U': '..-',   'V': '...-',  'W': '.--',   'X': '-..-',
    'Y': '-.--',  'Z': '--..'
}
    # passage du mot en caractère alphanumérique  en morse 
    for i in range(len(mot)):
       if mot[i] in morse_dict:
          mot_morse.append(morse_dict[mot[i]]) 
          mot_morse.append(" ")





    mot_chiffre = []
    for j in range(len(mot_morse)):
       for k in range(len(mot_morse[j])): 
        if mot_morse[j][k] == ".":
            random.shuffle(cle["."])
            mot_chiffre.append(cle["."][0])
        if mot_morse[j][k] == "-":
            random.shuffle(cle["-"])
            mot_chiffre.append(cle["-"][0])
        if mot_morse[j][k] == " ":
            random.shuffle(cle[" "])
            mot_chiffre.append(cle[" "][0])
   
        
    return mot_chiffre

          

def dechiffrement_pollux_morse(mot : list , cle : dict) -> str:
    mot_dechiffre = []
    for i in range(len(mot)):
        if mot[i] in cle["."]:
            mot_dechiffre.append(".")
        if mot[i] in cle["-"]:
            mot_dechiffre.append("-")
        if mot[i] in cle[" "]:
            mot_dechiffre.append(" ")
    print(mot_dechiffre)
    return "".join(mot_dechiffre)


def dechiffrement_pollux_passage_morse_a_alphabet (mot : str):
    morse_dict = {
    '.-': 'A',   '-...': 'B',  '-.-.': 'C',  '-..': 'D',
    '.': 'E',    '..-.': 'F',  '--.': 'G',   '....': 'H',
    '..': 'I',   '.---': 'J',  '-.-': 'K',   '.-..': 'L',
    '--': 'M',   '-.': 'N',    '---': 'O',   '.--.': 'P',
    '--.-': 'Q', '.-.': 'R',   '...': 'S',   '-': 'T',
    '..-': 'U',  '...-': 'V',  '.--': 'W',   '-..-': 'X',
    '-.--': 'Y', '--..': 'Z'
}
    mot_dechiffre = []
    mot = mot.split(" ")
    mot.remove("") 
    print(mot)
    for i in range(len(mot)):
        if mot[i] in morse_dict:
            mot_dechiffre.append(morse_dict[mot[i]])
    
    
    return "".join(mot_dechiffre)



 

# a = chiffrement_pollux("CHATGPT", key_pollux())
# print(a)
# b = dechiffrement_pollux_morse(a, key_pollux())
# print(b)       

# c = dechiffrement_pollux_passage_morse_a_alphabet(b)

# print(c)

# #  teste XOR pour plus de détail voir partie 9 
a = "abc"
b = "AB"

mot  = chiffrement_xor(a,b)
print(mot)
print(dechiffrement(mot,key(b)))
   


