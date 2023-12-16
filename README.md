# Dokumentácia Projektu

## Úloha
Tento projekt sa zameriava na vývoj nástroja pre kompresiu a dekompresiu súborov pomocou algoritmov Huffmanovho kódovania a behovej dĺžky (RLE). Nástroj poskytuje rozhranie príkazového riadka, ktoré umožňuje používateľom komprimovať a dekomprimovať súbory pomocou týchto algoritmov.

## Funkcionalita
- **Kompresia**: Program dokáže komprimovať súbory pomocou Huffmanovho kódovania alebo algoritmu RLE. Huffmanovo kódovanie je efektívne pre súbory, v ktorých sa určité znaky vyskytujú častejšie než iné, zatiaľ čo RLE je jednoduchý a efektívny pre dáta s veľkým množstvom opakujúcich sa sekvencií.
- **Dekompresia**: Program dokáže dekomprimovať súbory, ktoré boli predtým komprimované pomocou tých istých algoritmov, čím ich obnoví do ich pôvodného stavu.

## Popis Riešenia
- Projekt je implementovaný v jazyku C a pozostáva z viacerých modulov:
  - `compressor.h` a `compressor.c` obsahujú deklarácie a implementácie funkcií kompresie a dekompresie.
  - `main.c` implementuje hlavnú funkciu a rozhranie príkazového riadka.
- Huffmanovo kódovanie je implementované vytvorením tabuľky frekvencií, zostavením Huffmanovho stromu na základe frekvencií a generovaním jedinečných binárnych kódov pre každý znak.
- RLE je implementované čítaním sekvencií opakujúcich sa znakov a kódovaním ich ako jediného znaku nasledovaného jeho počtom.

## Podmienky Prevádzky
- Program je navrhnutý tak, aby bežal na systémoch s C kompilátorom, ako je GCC.
- Vyžaduje dostatočnú pamäť a úložný priestor na zvládnutie operácií so súbormi zahrnutých v procesoch kompresie a dekompresie.
- Program očakáva argumenty príkazového riadka na špecifikáciu operácie (kompresia alebo dekompresia), algoritmu (Huffman alebo RLE) a mien vstupných/výstupných súborov.

## Kompilácia Projektu
Projekt môžete skompilovať pomocou priloženého `Makefile`. Stačí spustiť nasledujúci príkaz v adresári projektu:  
make
Tento príkaz vytvorí spustiteľný súbor, ktorý môžete použiť na kompresiu alebo dekompresiu súborov.

## Spustenie Programu
Po skompilovaní môžete program spustiť nasledovne:  
./program -c|-d -h|-r input_file output_file
Kde:
- `-c` značí kompresiu
- `-d` značí dekompresiu
- `-h` použiť Huffmanovo kódovanie
- `-r` použiť RLE kódovanie
- `input_file` je meno vstupného súboru
- `output_file` je meno výstupného súboru

## Referencie
- Algoritmy pre Huffmanovo kódovanie a RLE boli založené na štandardných implementáciách, ako sú popísané v rôznych učebniciach informatiky a online zdrojoch.
- Dokumentácia a tutoriály z [cplusplus.com](https://www.cplusplus.com) a [Stack Overflow](https://stackoverflow.com) boli použité pre špecifické implementačné detaily v jazyku C.
