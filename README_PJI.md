Ceci est le dépot de mon Projet Individuel de Master pour l'Université de Lille

Le code écrit pour ce projet se situe dans :
 - `/App/*`
 - `/drivers/stbm271/*`

Configuration
=============

Pour exécuter et tester le code, un ESP32 et un STBM271 sont nécessaires.
Afin de pouvoir se connecter au Wi-Fi les credentials (ssid et wpa) sont
nécessaire. Pour cela il faut modifier le fichier `/App/creds.mk` avec
les informations nécessaires. Attention la plupart des caractères non-alphanumériques
doivent être échappés.

Une fois les identifiants Wi-Fi configurés, il est possible de configurer
l'adresse IP et le port du serveur distant. Cela se fait dans le fichier
`/App/Makefile`. Il faut décommenter les CFLAGS ajoutant les macro `SERVER_ADDR`
et `SERVER_PORT`, et modifier l'exemple de manière appropriée. Encore une fois,
la plupart des caractère non-alphanumériques doivent être échappés.

Le signal PWM du STBM271 doit être branché sur le pin 18 de l'esp32 pour pouvoir
lire les données.

Compilation
===========

Pour compiler, flasher la carte et ouvrir une connexion série :
```
cd App
make flash term
```

Contribution
============

Le projet en l'état ne respecte pas suffisament les conventions de RIOT pour
pouvoir être accepté en tant que contribution (pour le driver du STBM271).
L'un des principal problème vient de la nature de résultat renvoyé par
le capteur. RIOT exige qu'un driver doit renvoyé une valeur physique concrète.
Ici, pour un capteur de particules fines, l'unité cohérente serait le mg/m3.
Cependant la documentation du STBM271 n'est pas assez explicite sur la
transposition des valeurs PWM à des valeurs concrètes. Elle ne donne également
aucune information sur la calibration du capteur.

D'autres optimisations seraient également souhaitables, tel que ne pas utiliser
de calcul flottant pour calculer le ratio, mais plutôt utiliser une lookup
table, plus accessible pour beaucoup de micro-contrôleurs.

