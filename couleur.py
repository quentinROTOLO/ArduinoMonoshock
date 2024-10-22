#!/usr/bin/env python3
# coding=UTF-8

import cgi
import cgitb
from operator import truediv; cgitb.enable()
from posixpath import dirname
from os import makedirs


isconnected = True
form = cgi.FieldStorage()
selected = form.getvalue('couleur', str)

couleur = [
    "Joueur 1",
    "Joueur 2",
    "Joueur 3"
]

print("Content-type: text/html; charset=UTF-8\n")

print("""
<html>
    <head>
        <title>Choisir la couleur Arduino</title>
    </head>
    <body>""")
if isconnected:
    print("<h1>Choisir la couleur Arduino</h1>")
    print("""
    <form method="post" action="?">
    <select name="couleur", size="3">""")
    for j in couleur:
        ajout = f'<option value="{j[-1]}"'
        if j == selected:
            ajout += f' selected="selected"'
        ajout +=f" >{j}</option>"
        print(ajout)
    print("""</select>
    <input type="submit" name="submit" value="ok" align="center"/>
    """)
else:  
    print("<h1>Manette non connectée</h1>")

if len(selected) > 0:
    makedirs("../../arduino", exist_ok=True)
    f = open ("../../arduino/couleur.txt", "w")
    f.write(selected)
    f.close
    couleurs = f"Vous avez sélectionné Joueur {selected}"
    print(f'<pre>{couleurs}</pre>')

print("""    </body>
</html>
""")