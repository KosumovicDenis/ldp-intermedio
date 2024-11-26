# Laboratorio di Programmazione - Prova Intermedia 2024/25

Sviluppo di un modulo C++ per la gestione dei dati provenienti da un LIDAR.

## Per eseguire il codice

Deve essere installato CMake >= 3.11 e un compilatore C++11

1. Configurare il progetto con CMake:

``` bash
./scripts/configure.sh
```

2. Eseguire la compilazione:

``` bash
./scripts/build.sh
```
L'eseguibile compilato è ora nella cartella `build/` chiamato `ldp-intermedio`

3. Eseguire il programma tramite lo script 

``` bash
./scripts/run.sh
```

O alternativamente esegue il file `ldp-intermedio`

> In alternativa al Step 2 e 3, si può usare lo script `./scripts/buildandrun.sh` per compilare e subito dopo eseguire il codice.

## Membri del gruppo "Kosumovic - Rorato":

- Toni Kosumovic - Definizione LidarDriver.h e implementazione parziale classe
- Denis Kosumovic - Completamento della classe LidarDriver e creazione del main con test
- Davide Rorato - Configurazione CMake e creazione script + input da file di testo
