![Contributors][contributors-shield]

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://www.youtube.com/watch?v=dQw4w9WgXcQ?autoplay=1">
    <img src="/robotics.png" alt="Logo" width="80" height="80">
  </a>
  <h3 align="center">Learning Automata en Markov Games</h3>
</p>

<!-- TABLE OF CONTENTS -->
## Inhoudstafel

* [Over het Project](#about-the-project)
* [Voorbeeld Omgeving](#voorbeeld-van-een-omgeving)
* [Getting Started](#getting-started)
* [Gebruik](#usage)
* [Resultaten](#results)
* [Contact](#contact)


<!-- ABOUT THE PROJECT -->
## Over het Project
Ons project gaat over 'Learning Automata en Markov Games'.
Zoals de naam al verraadt zijn learning automata simpelweg automaten die kunnen leren.
Markov games zijn spellen gebaseerd op een Markov decision process (ookwel MDP genoemd). MDPs kunnen tal van maatschappelijke toepassingen beschrijven,
wij hebben er specifiek voor gekozen om een Markov game te bestuderen. De markov game die wij beschouwen is simpel. We genereren een gerandomiseerde 2D gridworld, onze agent wordt willekeurig in deze omgeving geplaatst en moet zijn huis terugvinden. Als hij zijn huis vindt krijgt hij een positieve beloning. Echter worden er ook obstakels en niet-deterministische elementen geplaatst in deze wereld die het de agent moeilijker maken aan zijn huis te geraken.

### Gemaakt met
* [QT](https://www.qt.io/)
* [CATCH2](https://github.com/catchorg/Catch2)

## Voorbeeld van een Omgeving

<br />
<p >
  <a href="https://www.youtube.com/watch?v=dQw4w9WgXcQ?autoplay=1">
    <img src="/7.png" alt="Monte Carlo learning per epsilon graph" width="777" height="457">
  </a>
</p>

<br />
<p >
  <a href="https://www.youtube.com/watch?v=dQw4w9WgXcQ?autoplay=1">
    <img src="/5.png" alt="Monte Carlo learning per epsilon graph" width="777" height="457">
  </a>
</p>

<!-- GETTING STARTED -->
## Getting Started

Installer CMake, Make, C++17+ en QT 5.12+.

Download het project.

Ga naar de downloads folder en voer deze commando's uit.


```bash
mkdir build && cd build
cmake .
make
```
Om het programma uit te voeren moet men enkel dit volgende commando uitvoeren:


```bash
./TO_Groep
```
<!-- USAGE EXAMPLES -->
## Gebruik
In de algorithms directory staan de twee learning algoritme.

In de data directory worden de saves van de environment en LA in opgeslagen.

In de datastructures directory staat de LA, State, Environment en MDPState klasse.

In de parser directory staat de TiXML parser library en onze parser klasse.

In de procederual-generation staan de klasse die opgeroepen worden tijdens het genereren van een niet-deterministische omgeving.

In de random directory staat de eigen random klasse gemaakt voor dit project.

In de tests directory staat alles wat nodig is voor de testen te runnen.

In de visualisatie directory staan alle bestanden van de GUI.

## Resultaten
<br />
<p >
  <a href="https://www.youtube.com/watch?v=dQw4w9WgXcQ?autoplay=1">
    <img src="/MC.png" alt="Monte Carlo learning per epsilon graph" width="777" height="457">
  </a>
</p>

<br />
<p>
  <a href="https://www.youtube.com/watch?v=dQw4w9WgXcQ?autoplay=1">
    <img src="/Qlearn.png" alt="Q-Learning vs Monte Carlo Control graph" width="769" height="459">
  </a>
</p>



<!-- CONTACT -->
## Contact

Jens Leysen - Jens.Leysen@student.uantwerpen.be

Dries De Maeseneer - Dries.DeMaeseneer@student.uantwerpen.be

Lars De Leeuw - Lars.DeLeeuw@student.uantwerpen.be

<!-- ZET NAMEN HIER -->

[contributors-shield]: https://img.shields.io/github/contributors/UAntwerpen/groep-ta-2020-2021-jens-lars-en-dries
