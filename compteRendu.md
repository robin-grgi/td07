# TD 7 Signaux
## Manipulations élémentaires de signaux
### Exercice 1
- La commande xeyes bloque l'utilisation du terminal.
- Le raccourci ```Ctrl+Z``` permet d'avoir à nouveau accès à la ligne de commande et suspend l'exécution de xeyes , laissant sa fenêtre ouverte.
- La commande ```bg``` reprends l'exécution de xeyes mais en arrière-plan ce qui permets de continuer l'exécution de la ligne de commande.
- ```
	 ⚙ robin@RG-Recoil-III-GTX  ~/Insync/georgi.robin@gmail.com/Google Drive/Polytech/S6/OS/TD7/td07  ps
    PID TTY          TIME CMD
   4074 pts/0    00:00:00 zsh
   5072 pts/0    00:00:03 xeyes
   5726 pts/0    00:00:00 ps
   ```
xeyes est associé à un PID de 5072.

- la commande ```kill -SIGSTOP 5072``` suspend l'exécution de xeyes et sa fenêtre reste ouverte. On peut donc associer cette commande au raccourci ```Ctrl+Z```

- le numéro associé à CONT est 18 (fun fact : dans le terminal zsh, seuls les noms des signaux sont affichés lors de l'exécution de ```kill -l``` les numéros ne sont pas affichés).

- La commande à exécuter pour quitter xeyes avec son nom est ```pkill -SIGQUIT xeyes```
## Mise en œuvre élémentaire de signaux
### Exercice 4
le signal SIGINT arrête complètement l'exécution du programme. Cela s'explique car,, comme le décrit la page de manuel de la fonction ```sleep```, l'attente est interrompue par la réception d'un signal.

```
DESCRIPTION
       sleep() causes the calling thread to sleep either until the number of real-time seconds specified in seconds have elapsed or until a signal arrives which is not ignored.
```

### Exercice 5
Après une compilation en mode ansi on remarque que le second signal SIGINT mets fin à l'exécution du programme.

Quant à la compilation de tst_sigaction.c, comme prévu, une erreur est générée car sigaction ne peut pas être utilisé dans le mode ansi : 

```
tst_sigaction.c:23:22: erreur: la taille de stockage de « act » est inconnue
   23 |     struct sigaction act;
      |                      ^~~
```

### Exercice 6

On conclut que l'utilisation de sigaction dans le but d'ignorer un signal doit se faire avec un handler pour être efficace lors d'une utilisation en programme asynchrone. Si on utilise sigaction sans handler ou avec un handler vide alors le signal est pris en compte et le sleep est annulé. Ainsi lors d'une utilisation avec plusieurs threads ou processus, il vaut mieux utiliser un handler pour gérer les signaux.


## Communication inter-processus
### Exercice 7
Ayant utilisé des variables globales pour stocker les PID des fils, je n'ai pas eu de problème pour les interchanger. En revanche si on n'utilise pas de variables globales alors l'ordre ne peut pas être changé sans utiliser de méthodes spécifiques comme ```getppid()```