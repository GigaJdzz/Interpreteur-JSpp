# Interpréteur JS++

###### Projet par: Jad FAWAZ & Sam HAJJ ASSAF

On a implémenté un interpréteur pour notre langage de programmation JS++ avec analyse
lexicale, syntaxique et sémantique à l’aide d’arbres abstraits (Ast).


## Expressions arithmétiques générales (EAG)

Du plus au moins prioritaire, puis de gauche à droite:

 - Parenthèses : (1 + 2)
 - Multiplications et divisions : 5 * 6 / 2
 - Additions et soustractions : 2 + 3 - 1


## Fonctionnalités

 - x = eag; : affecte la valeur de l’EAG à la variable x
 - lire(x); : lit une valeur dans le stdin et la mets dans la variable x
 - ecrire(x); : écrit la valeur de x dans le stdout
 - si condition alors 1 sinon 2 fsi; : exécute le bloc de code 1 si la condition est vraie, le bloc de code 2 sinon
 - tantque condition faire 1 fait; : exécute le bloc de code 1 tant que la condition est vraie


## Conditions
 - x == y
 - x != y
 - x < y
 - x > y
 - x <= y
 - x >= y

(avec x et y des variables ou des entiers)


## Exemple

Fichier fibonacci.jspp

```C
lire(n);
a = 0;
b = 1;
c = 0;
i = 2;
si n == 0 alors
    ecrire(a);
sinon
    tantque i <= n faire
        c = a + b;
        a = b;
        b = c;
        i = i + 1;
    fait;
fsi;
ecrire(b);
```

Résulat fibonacci.jspp

```
---------- debut du programme ----------
8
21
----------- Fin du programme -----------
--> Listes variables:
i = 9;
c = 21;
b = 21;
a = 13;
n = 8;
```

---

## Compilation

Pour compiler le programme il suffit d'executer dans le terminal:

```
make
```

Pour effacer les fichiers compilés:

```
make clean
```

## Exécution

Pour exécuter des fichiers type `.jspp` il suffit d'exécuter:

```
./jspplang [nom du fichier]
```

---
