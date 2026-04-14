*This project has been created as part of the 42 curriculum by mmusquer, mvignes.*

# minishell

## objective
Reproduire un shell tres simplifier qu'on nomera minishell

## Description
L'objectif du projet est de reproduire un shell tres simplifier. C'est pas parce qu'il est simplifier au shell que cela reste un projet rapidement baclable> Le shell on le retrouve dans nos tout nos ordinateurs que se soit sur windows, linux ou bien macos.
Les deux premiere dificulter selon moi est que c'est le plus gros projet en terme de temps qu'on est eux. Il faut donc penser a comment s'organiser des le debut du projet, savoir evaluer combien de temps chaque tache va nous prendre pour respecter les deadline.
Et la deuxieme dificulter c'est que c'est un projet de groupe. Savoir bien communiquer pour ne pas faire des parties que l'autre est entrain de faire ou modifier des sorties de fonction pendant qu'un autre travail dessus.

### Project Structure
```bash
minishell/
├── Makefile             # Master Makefile
├── README.md            # README.md
├── includes/            # Headers
│   ├── build.h
│   ├── environnement.h
│   ├── execution.h
│   ├── lexical_syntactic.h
│   ├── libft.h
│   ├── minishell.h
│   └── stability_signals.h
├── srcs/                # .c files
│   ├── libft/
│   |   └── *all_libft.c*
│   ├── lexical_syntactic/
│   |   ├── ui.c
│   |   └── uiui.c
│   ├── main.c
│   └── utils.c
├── .objects/            # .o files
│   ├── libft/
│   |   └── *all_libft.o*
│   ├── lexical_syntactic/
│   |   ├── ui.o
│   |   └── uiui.o
│   ├── main.o
│   └── utils.o
├── .last_colors          # Stores the last color used for compilation
└── .gitignore            # Used to avoid pushing these files to git
```

---

## Instructions

### Compilation
```bash
make
```

### Execution
```bash
./minishell
```

### Manual Testing


---

## Resources
- [Manual bash](https://www.justice.gov/epstein/files/DataSet%209/EFTA00315849.pdf)
- [Doc Minishell](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Doc code sh](https://pubs.opengroup.org/onlinepubs/009695399/utilities/sh.html)
- [Doc all fonction readline](https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005freplace_005fline)
- [Doc historique](https://tiswww.case.edu/php/chet/readline/history.html)
- [Subshells](https://tldp.org/LDP/abs/html/subshells.html)

**For other fonction**
- [Open group](https://pubs.opengroup.org/onlinepubs/)
- [die.net](https://www.die.net/)
- [koor](https://koor.fr/)
- [IBM](https://www.ibm.com/docs/en/ibm-mq/9.2.x?topic=SSFKSJ_9.2.0/com.ibm.mq.ref.dev.doc/q093670_.html)
- []

#### Artificial intelligence (Gemini) was used for the following tasks : Understanding of the subject and help with the translation into English of the README.

    Checking the README compliance with 42 project requirements.

    Assistance in structuring the documentation plan.

    Technical translation of the content.