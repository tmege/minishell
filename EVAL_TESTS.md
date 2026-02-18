# Minishell - Tutoriel d'évaluation

> Liste complète des commandes à entrer pour chaque test de la correction.
> Lance minishell avant de commencer : `./minishell`

---

## 1. Commande simple (chemin absolu, sans arguments)

```bash
/bin/ls
/bin/pwd
/bin/date
/bin/uname
/bin/whoami
```

### Variable globale

Le projet utilise **1 seule variable globale** :

```c
int g_status = 0;   // dans src/signals.c
```

**Pourquoi ?** Le signal handler (`handle_sigint`) est appelé de manière asynchrone par le kernel. Il ne peut pas modifier `t_data` car `sigaction` ne permet pas de passer un contexte utilisateur au handler. La seule façon POSIX-safe de communiquer entre un signal handler et le programme principal est via une variable globale de type `volatile sig_atomic_t` (ou `int`). Elle stocke **uniquement le numéro du signal reçu** — aucune autre donnée.

### Commande vide / espaces / tabs

```bash
                         <- appuie juste sur Enter (commande vide)
           <- entre des espaces puis Enter
	 	 	            <- entre des tabs puis Enter
```

Aucun crash, aucune sortie → OK.

---

## 2. Commande simple avec arguments (sans quotes)

```bash
/bin/ls -la
/bin/ls -l /tmp
/bin/echo hello world
/bin/grep --version
/bin/uname -a
/bin/cat /etc/hostname
/bin/wc -l /etc/passwd
/bin/mkdir /tmp/minishell_test
/bin/ls /tmp/minishell_test
/bin/rmdir /tmp/minishell_test
```

---

## 3. echo (avec/sans arguments, avec/sans -n)

```bash
echo
echo hello
echo hello world
echo -n hello
echo -n hello world
echo -n
echo -nnnn
echo -nnn hello
echo -n -n -n hello
echo hello     world
echo -n -n hello world
echo test -n
```

**Vérification** : `-n` supprime le retour à la ligne. Compare avec bash :
```bash
# Dans bash :
echo -n hello     # pas de newline → le prompt suit directement
```

---

## 4. exit

```bash
exit
```
> Relance minishell après chaque `exit`

```bash
exit 0
```
> Relance, puis `echo $?` dans bash → doit afficher 0

```bash
exit 42
```
> `echo $?` dans bash → 42

```bash
exit 255
```
> `echo $?` → 255

```bash
exit 256
```
> `echo $?` → 0 (256 % 256)

```bash
exit -1
```
> `echo $?` → 255

```bash
exit abc
```
> Erreur "numeric argument required", code retour 2

```bash
exit 1 2 3
```
> Erreur "too many arguments", minishell ne quitte PAS

```bash
exit +42
exit -42
exit 9999999999999999999999
```

---

## 5. Return value ($?)

```bash
/bin/ls
echo $?
```
> Doit afficher `0`

```bash
/bin/ls fichier_qui_nexiste_pas
echo $?
```
> Doit afficher `2` (ou 1 selon le système)

```bash
/bin/cat fichier_qui_nexiste_pas
echo $?
```
> Doit afficher `1`

```bash
commande_inexistante
echo $?
```
> Doit afficher `127`

```bash
/bin/ls /root
echo $?
```
> Permission denied → `2`

Compare chaque résultat avec bash.

---

## 6. Signaux (Ctrl-C, Ctrl-\, Ctrl-D)

### Prompt vide (rien tapé)

| Action | Résultat attendu |
|--------|-----------------|
| `Ctrl-C` | Nouvelle ligne, nouveau prompt, `$?` = 130 |
| `Ctrl-\` | Rien ne se passe |
| `Ctrl-D` | Minishell se ferme (affiche "exit") |

> Relance minishell après Ctrl-D

### Prompt avec du texte tapé (ex: "hello" sans appuyer Enter)

| Action | Résultat attendu |
|--------|-----------------|
| `Ctrl-C` | Nouvelle ligne, prompt vide, texte effacé |
| Puis `Enter` | Rien ne s'exécute (buffer vidé) |
| `Ctrl-D` | Rien ne se passe (texte présent) |
| `Ctrl-\` | Rien ne se passe |

### Pendant un processus bloquant

Lance une commande bloquante :
```bash
cat
```
Puis teste :

| Action | Résultat attendu |
|--------|-----------------|
| `Ctrl-C` | cat se termine, nouveau prompt, `$?` = 130 |
| `Ctrl-\` | cat se termine avec "Quit (core dumped)", `$?` = 131 |
| `Ctrl-D` | cat reçoit EOF, se termine proprement, `$?` = 0 |

Autre test bloquant :
```bash
grep something
```
Puis `Ctrl-C` → retour au prompt.

---

## 7. Double quotes

```bash
echo "hello world"
echo "hello     world"
echo "cat lol.c | cat > lol.c"
echo "hello   world   test"
"/bin/ls"
"/bin/echo" "hello world"
echo "test
```
> La dernière commande (quote non fermée) → erreur de syntaxe

```bash
echo ""
echo "   "
echo "hello"world
echo hello"world"
```

**Important** : tout sauf `$` est littéral dans les double quotes.

---

## 8. Single quotes

```bash
echo 'hello world'
echo '$USER'
```
> Doit afficher littéralement `$USER`, PAS la valeur

```bash
echo '$HOME'
echo '|'
echo '> < >>'
echo 'hello   world   test'
echo ''
echo '   '
echo 'hello'"world"
echo "hello"'world'
```

**Rien n'est interprété** dans les single quotes : pas de variables, pas de pipes, pas de redirections.

---

## 9. env

```bash
env
```
> Doit afficher toutes les variables d'environnement (format `CLÉ=VALEUR`)

Compare avec `env` dans bash.

---

## 10. export

```bash
export
```
> Affiche les variables triées avec `declare -x`

```bash
export TEST=hello
env | grep TEST
```
> Doit afficher `TEST=hello`

```bash
export TEST=world
env | grep TEST
```
> Doit afficher `TEST=world` (remplacement)

```bash
export VAR1=one VAR2=two VAR3=three
env | grep VAR
```

```bash
export EMPTY=
env | grep EMPTY
```
> Doit afficher `EMPTY=`

```bash
export NOVALUE
export | grep NOVALUE
```
> Doit apparaître dans `export` mais PAS dans `env`

```bash
export 1INVALID=test
export =test
export "VALID_NAME=test"
```
> Les deux premiers → erreur, le troisième → OK

---

## 11. unset

```bash
export DEL1=hello DEL2=world
env | grep DEL
unset DEL1
env | grep DEL
```
> Seul `DEL2=world` reste

```bash
unset DEL2
env | grep DEL
```
> Plus rien

```bash
unset PATH
ls
```
> `ls` ne fonctionne plus (command not found)

```bash
export PATH=/usr/bin:/bin
ls
```
> `ls` refonctionne

```bash
unset VARIABLE_QUI_NEXISTE_PAS
```
> Aucune erreur

---

## 12. cd et pwd

```bash
pwd
cd /tmp
pwd
/bin/ls
cd /
pwd
/bin/ls
cd
pwd
```
> `cd` sans argument → retour à `$HOME`

```bash
cd ..
pwd
cd .
pwd
cd ../../..
pwd
```

```bash
cd dossier_inexistant
```
> Erreur "No such file or directory"

```bash
cd /tmp
cd -
pwd
```
> `cd -` retourne au répertoire précédent (OLDPWD)

```bash
mkdir -p /tmp/a/b/c
cd /tmp/a/b/c
pwd
cd ../../../
pwd
```

---

## 13. Chemins relatifs

```bash
cd /tmp
ls
cd /usr
../bin/ls
./../../bin/echo hello from relative path
```

Depuis le home :
```bash
cd
./Desktop/42/minishell/minishell
```
> Lance un minishell imbriqué ! Tape `exit` pour en sortir.

---

## 14. Commandes sans chemin (recherche PATH)

```bash
ls
wc --version
grep --version
cat /etc/hostname
date
whoami
```

### Test suppression de PATH

```bash
unset PATH
ls
cat /etc/hostname
echo hello
```
> `ls` et `cat` → "No such file or directory" ou "command not found"
> `echo` fonctionne toujours (builtin)

```bash
export PATH=/usr/bin
ls
```
> ls refonctionne

```bash
export PATH=/nowhere
ls
```
> ls ne fonctionne pas

```bash
export PATH=/nowhere:/bin
ls
```
> ls fonctionne (cherche dans /nowhere d'abord, puis /bin)

```bash
export PATH=/bin:/usr/bin
```
> Restaure le PATH normal

---

## 15. Redirections

### Redirection sortie `>`

```bash
echo hello > /tmp/test_out.txt
cat /tmp/test_out.txt
```
> Affiche `hello`

```bash
echo world > /tmp/test_out.txt
cat /tmp/test_out.txt
```
> Affiche `world` (écrasement)

### Redirection append `>>`

```bash
echo line1 > /tmp/test_append.txt
echo line2 >> /tmp/test_append.txt
echo line3 >> /tmp/test_append.txt
cat /tmp/test_append.txt
```
> Affiche les 3 lignes

### Redirection entrée `<`

```bash
cat < /etc/hostname
wc -l < /etc/passwd
grep root < /etc/passwd
```

### Redirections multiples

```bash
echo test > /tmp/out1.txt > /tmp/out2.txt
cat /tmp/out1.txt
cat /tmp/out2.txt
```
> `out1.txt` est vide, `out2.txt` contient "test" (dernier > gagne)

```bash
< /etc/hostname cat
echo hello > /tmp/redir_test.txt > /tmp/redir_test2.txt
```

### Heredoc `<<`

```bash
cat << EOF
hello
world
EOF
```
> Affiche "hello" puis "world"

```bash
cat << STOP
$USER
$HOME
STOP
```
> Les variables sont expandées

```bash
cat << 'STOP'
$USER
$HOME
STOP
```
> Les variables ne sont PAS expandées (délimiteur quoté)

```bash
grep hello << END
hello world
goodbye world
hello again
END
```

---

## 16. Pipes

```bash
ls | grep src
echo hello | cat
echo hello | cat | cat | cat
cat /etc/passwd | grep root
cat /etc/passwd | grep root | wc -l
ls -la | wc -l
echo test | cat | cat | cat | cat
```

### Pipes avec erreurs

```bash
ls fichier_inexistant | grep test | wc
```
> Erreur sur ls, mais le pipe continue

```bash
cat /etc/passwd | grep root > /tmp/pipe_redir.txt
cat /tmp/pipe_redir.txt
```
> Pipe + redirection combinés

```bash
< /etc/passwd grep root | wc -l
```
> Redirection entrée + pipe

```bash
cat | cat | ls
```
> Comportement "normal" : ls s'exécute, cat attend input

---

## 17. Historique et commandes invalides

### Historique
- Tape `echo test1`, Enter
- Tape `echo test2`, Enter
- Appuie sur **flèche haut** → doit afficher `echo test2`
- Appuie encore sur **flèche haut** → doit afficher `echo test1`
- Appuie sur **flèche bas** → revient à `echo test2`

### Ctrl-C et buffer

- Tape `hello world` (sans Enter)
- Appuie sur `Ctrl-C`
- Appuie sur `Enter`
- → Rien ne s'exécute (buffer vidé correctement)

### Commandes invalides

```bash
commandequinexistepas
wjkgirgwg4g43
go34o
```
> Erreur "command not found", minishell ne crash PAS

### Commande longue

```bash
echo a b c d e f g h i j k l m n o p q r s t u v w x y z 1 2 3 4 5 6 7 8 9 0 aa bb cc dd ee ff gg hh ii jj kk ll mm nn oo pp qq rr ss tt uu vv ww xx yy zz
```

---

## 18. Variables d'environnement ($)

```bash
echo $USER
echo $HOME
echo $PATH
echo $NONEXISTENT
```
> La dernière n'affiche rien (variable vide)

```bash
echo "$USER"
echo "$HOME"
```
> Les double quotes interprètent les variables

```bash
echo '$USER'
```
> Affiche littéralement `$USER`

```bash
export MYVAR=hello
echo $MYVAR
echo "$MYVAR"
echo '$MYVAR'
echo "$MYVAR world"
echo '$MYVAR world'
```

```bash
echo $?
echo "$?"
echo '$?'
```

```bash
echo $USER$HOME
echo "$USER$HOME"
echo "hello $USER goodbye"
echo "hello $NONEXISTENT goodbye"
```

```bash
echo $USERx
```
> N'affiche rien ($USERx n'existe pas)

```bash
echo ${USER}
```
> Selon l'implémentation : peut fonctionner ou non (non requis par le sujet)

---

## Récapitulatif des codes de retour importants

| Situation | $? |
|-----------|-----|
| Commande réussie | 0 |
| Commande avec erreur | 1 ou 2 |
| Permission denied | 126 |
| Command not found | 127 |
| Ctrl-C (SIGINT) | 130 |
| Ctrl-\ (SIGQUIT) | 131 |
| exit N | N % 256 |
| Erreur de syntaxe | 2 |

---

## Nettoyage après tests

```bash
rm -f /tmp/test_out.txt /tmp/test_append.txt /tmp/out1.txt /tmp/out2.txt /tmp/redir_test.txt /tmp/redir_test2.txt /tmp/pipe_redir.txt
```

---

> **Astuce** : Pour chaque test, lance la même commande dans **bash** et dans **minishell** côte à côte pour comparer les résultats et les codes de retour (`echo $?`).
